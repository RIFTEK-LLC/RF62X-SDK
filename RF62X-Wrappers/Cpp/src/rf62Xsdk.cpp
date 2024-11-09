#include "rf62Xsdk.h"

#include <memory>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iterator>
#include <time.h>
#include <thread>

#include "rf62Xcore.h"
#include "rf62Xversion.h"
#include "rf62Xtypes.h"

extern "C" {
#include "rf62X_sdk.h"
#include "netwok_platform.h"
#include "utils.h"
}






#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#else
#include <arpa/inet.h>
typedef int BOOL;
#define INVALID_SOCKET          (-1)
#define SOCKET_ERROR            (-1)
#define TRUE 1
#define FALSE 0
#endif


extern BOOL EnumAdapterAddresses();
extern void FreeAdapterAddresses();
extern int GetAdaptersCount();
extern const char* GetAdapterAddress(int index);
/* windows sockets tweaks */
extern BOOL WinSockInit();
extern void WinSockDeinit();
extern const char* GetAdapterMasks(int index);


std::string SDK::SCANNERS::RF62X::sdk_version()
{
    return RF62X_SDK_VERSION;
}

static bool is_initialized = false;
bool SDK::SCANNERS::RF62X::sdk_init()
{   
    if (!is_initialized)
    {
        is_initialized = SDK::CORES::RF62X::init();
        return is_initialized;
    }else
        return is_initialized;
}

namespace SDK {
namespace SCANNERS {
namespace RF62X {

class convert{
    public:
    static std::string to_hex(int to_convert, int precision_specifier, bool uppercase = false)
    {
        std::string hex_result = "";
        std::string value;
        std::stringstream ss;
        ss << std::hex <<to_convert;
        ss >> value;
        for (size_t i = 0; i < (precision_specifier - value.size()); i++)
            hex_result+="0";

        if (uppercase)
        {
            // convert string to upper case
            std::for_each(value.begin(), value.end(), [](char & c){
                c = ::toupper(c);
            });
        }

        hex_result += value;
        return hex_result;
    }


    static std::string to_oct(int to_convert){
        std::string result;
        std::stringstream ss;
        ss << std::oct << to_convert;
        ss >> result;
        return result;
    }

    static std::string to_bin(int to_convert){
        return int_to_bin(to_convert);
    }
    private:
          static std::string int_to_bin(int number){
              std::string result;
              int level = 0;
              level++;
              if (number > 0){
                  result += (number % 2 == 0) ? "0" : "1";
                  int_to_bin(number / 2);
                  level--;
              }
              if (level == 1) return reverse(result);
              return result;
          }

          static std::string reverse(std::string to_reverse){
              std::string result;
              for (int i = to_reverse.length()-1; i >=0 ; i--)
                  result += to_reverse[i];
              return result;
          }
};

frame::frame(void* frame_base)
{
    m_FrameBase = frame_base;
    rf627_frame_t* _frame = (rf627_frame_t*)m_FrameBase;
    if (_frame != nullptr)
    {
        switch (_frame->type) {
        case kRF627_OLD:
        {
            m_Data = _frame->rf627old_frame->data;
            m_DataSize = _frame->rf627old_frame->data_size;
            m_PixelSize = _frame->rf627old_frame->pixel_size;
            m_FrameWidth = _frame->rf627old_frame->width;
            m_FrameHeight = _frame->rf627old_frame->height;

            m_RoiActive = _frame->rf627old_frame->user_roi_active;
            m_RoiEnabled = _frame->rf627old_frame->user_roi_enabled;
            m_RoiPos = _frame->rf627old_frame->user_roi_pos;
            m_RoiSize = _frame->rf627old_frame->user_roi_size;
            break;
        }
        case kRF627_SMART:
        {
            m_Data = _frame->rf627smart_frame->data;
            m_DataSize = _frame->rf627smart_frame->data_size;
            m_PixelSize = _frame->rf627smart_frame->pixel_size;
            m_FrameWidth = _frame->rf627smart_frame->frame_width;
            m_FrameHeight = _frame->rf627smart_frame->frame_height;

            m_RoiActive = _frame->rf627smart_frame->user_roi_active;
            m_RoiEnabled = _frame->rf627smart_frame->user_roi_enabled;
            m_RoiPos = _frame->rf627smart_frame->user_roi_pos;
            m_RoiSize = _frame->rf627smart_frame->user_roi_size;
            m_SensorWidth = _frame->rf627smart_frame->fact_sensor_width;
            m_SensorHeight = _frame->rf627smart_frame->fact_sensor_height;
            break;
        }
        }
    }else
    {
        throw std::invalid_argument("frame_base == nullptr!");
    }
}

frame::~frame()
{
    rf627_frame_t* _frame = (rf627_frame_t*)m_FrameBase;
    if (_frame != nullptr)
    {
        switch (_frame->type) {
        case kRF627_OLD:
        {
            if(_frame->rf627old_frame->data != nullptr)
                free(_frame->rf627old_frame->data);
            free(_frame->rf627old_frame);
            break;
        }
        case kRF627_SMART:
        {
            if(_frame->rf627smart_frame->data != nullptr)
                free(_frame->rf627smart_frame->data);
            free(_frame->rf627smart_frame);
            break;
        }
        }
        free(_frame);
    }
}

std::vector<char> frame::getData()
{
    std::vector<char> v(m_Data, m_Data + m_DataSize);
    return v;
}

uint32_t frame::getDataSize()
{
    return m_DataSize;
}

uint8_t frame::getPixelSize()
{
    return m_PixelSize;
}

uint32_t frame::getFrameWidth()
{
    return m_FrameWidth;
}

uint32_t frame::getFrameHeight()
{
    return m_FrameHeight;
}

bool frame::getRoiActive()
{
    return m_RoiActive;
}

bool frame::getRoiEnabled()
{
    return m_RoiEnabled;
}

uint32_t frame::getRoiPos()
{
    return m_RoiPos;
}

uint32_t frame::getRoiSize()
{
    return m_RoiSize;
}

uint32_t frame::getSensorWidth()
{
    return m_SensorWidth;
}

uint32_t frame::getSensorHeight()
{
    return m_SensorHeight;
}


calib_table::calib_table(void* table_base)
{
    m_CalibTableBase = table_base;
    rf627_calib_table_t* _calib_table = (rf627_calib_table_t*)m_CalibTableBase;
    if (_calib_table != nullptr)
    {
        switch (_calib_table->type) {
        case kRF627_OLD:
        {
            break;
        }
        case kRF627_SMART:
        {
            m_Type = _calib_table->rf627smart_calib_table->m_Type;
            m_CRC16 = _calib_table->rf627smart_calib_table->m_CRC16;
            m_Serial = _calib_table->rf627smart_calib_table->m_Serial;
            m_DataRowLength = _calib_table->rf627smart_calib_table->m_DataRowLength;
            m_Width = _calib_table->rf627smart_calib_table->m_Width;
            m_Height = _calib_table->rf627smart_calib_table->m_Height;
            m_MultW = _calib_table->rf627smart_calib_table->m_MultW;
            m_MultH = _calib_table->rf627smart_calib_table->m_MultH;
            m_TimeStamp = _calib_table->rf627smart_calib_table->m_TimeStamp;

            m_Data = std::vector<uint8_t>(_calib_table->rf627smart_calib_table->m_Data,
                                          _calib_table->rf627smart_calib_table->m_Data +
                                          _calib_table->rf627smart_calib_table->m_DataSize);

            break;
        }
        }
    }
}

calib_table::~calib_table()
{
    rf627_calib_table_t* _calib_table = (rf627_calib_table_t*)m_CalibTableBase;
    if (_calib_table != nullptr)
    {
        switch (_calib_table->type) {
        case kRF627_OLD:
        {
            break;
        }
        case kRF627_SMART:
        {
            if (_calib_table->rf627smart_calib_table != nullptr)
            {
                if(_calib_table->rf627smart_calib_table->m_Data != nullptr)
                {
                    free(_calib_table->rf627smart_calib_table->m_Data);
                    _calib_table->rf627smart_calib_table->m_Data = nullptr;
                    _calib_table->rf627smart_calib_table->m_DataSize = 0;
                }
                free(_calib_table->rf627smart_calib_table);
                _calib_table->rf627smart_calib_table = nullptr;
            }
            break;
        }
        }
        free(_calib_table);
    }
}

std::shared_ptr<calib_table> calib_table::read_from_file(std::string file_name)
{
    std::ifstream input(file_name, std::ios::binary);
    std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
    return parse_from_bytes(buffer);
}

std::shared_ptr<calib_table> calib_table::parse_from_bytes(std::vector<char> bytes)
{
    rf627_calib_table_t* _table =
            convert_calibration_table_from_bytes(bytes.data(), bytes.size());

    std::shared_ptr<calib_table> table = std::make_shared<calib_table>(_table);

    table->m_Zd.resize(2*table->m_Height * table->m_Width);
    table->m_Xd.resize(2*table->m_Height * table->m_Width);
    // Copy tables
    for (size_t iRow = 0; iRow < 2*table->m_Height; iRow++) // x2 resolution in vertical
    {
        for (size_t iCol = 0; iCol < table->m_Width; iCol++)
        {
            int16_t valZ;
            int16_t valX;

            memcpy(&valZ, &table->m_Data[iCol*2048*4 + iRow*4 + 2 + 0], 2);
            memcpy(&valX, &table->m_Data[iCol*2048*4 + iRow*4 + 0], 2);

            table->m_Zd[iRow*table->m_Width + iCol] = valZ;
            table->m_Xd[iRow * table->m_Width + iCol] = valX;
        }
    }

    return table;
}

uint16_t calib_table::getType()
{
    return m_Type;
}
uint16_t calib_table::getCRC16()
{
    return m_CRC16;
}
uint32_t calib_table::getSerial()
{
    return m_Serial;
}

uint32_t calib_table::getDataRowLength()
{
    return m_DataRowLength;
}
uint32_t calib_table::getWidth()
{
    return m_Width;
}
uint32_t calib_table::getHeight()
{
    return m_Height;
}
uint8_t calib_table::getMultWidth()
{
    return m_MultW;
}
uint8_t calib_table::getMultHeight()
{
    return m_MultH;
}
int calib_table::getTimeStamp()
{
    return m_TimeStamp;
}

std::vector<uint8_t> calib_table::getData()
{
    return m_Data;
}

bool calib_table::setData(std::vector<uint8_t> data)
{
    m_Data = data;
    if (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize != 0)
    {
        free (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data);
        ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = 0;
    }
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data
            = (uint8_t*)calloc(m_Data.size(), sizeof (uint8_t));
    memcpy(((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data, m_Data.data(), m_Data.size());
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = m_Data.size();

    uint16_t crc = 0;
    int len = m_Data.size();
    uint16_t* data16 = (uint16_t*)m_Data.data();

    while(len > 1)
    {
        crc += 44111 * *data16++;
        len -= sizeof(uint16_t);
    }
    if (len > 0) crc += *(uint8_t*)data16;
    crc = crc ^ (crc >> 8);
    m_CRC16 = crc;
    return true;
}
bool calib_table::setZ(std::vector<int16_t> Zd)
{
    m_Zd = Zd;
    if(m_Data.size() != 2047*2048*4)
        m_Data.resize(2047*2048*4);

    int16_t NaN = -32768;
    // Copy tables
    for (size_t iRow = 0; iRow < 2*m_Height; iRow++) // x2 resolution in vertical
    {
        for (size_t iCol = 0; iCol < m_Width; iCol++)
        {
            int16_t valZ = Zd[iRow*m_Width + iCol];
            if (valZ != NaN)
            {
                m_Data[iCol*2048*4 + iRow*4 + 2 + 0] = ((uint8_t*)&valZ)[0];
                m_Data[iCol*2048*4 + iRow*4 + 2 + 1] = ((uint8_t*)&valZ)[1];
            }
            else
            {
                m_Data[iCol*2048*4 + iRow*4 + 2 + 0] = ((uint8_t*)&NaN)[0];
                m_Data[iCol*2048*4 + iRow*4 + 2 + 1] = ((uint8_t*)&NaN)[1];
            }
        }
    }

    if (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize != 0)
    {
        free (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data);
        ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = 0;
    }
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data
            = (uint8_t*)calloc(m_Data.size(), sizeof (uint8_t));
    memcpy(((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data, m_Data.data(), m_Data.size());
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = m_Data.size();

    uint16_t crc = 0;
    int len = m_Data.size();
    uint16_t* data16 = (uint16_t*)m_Data.data();

    while(len > 1)
    {
        crc += 44111 * *data16++;
        len -= sizeof(uint16_t);
    }
    if (len > 0) crc += *(uint8_t*)data16;
    crc = crc ^ (crc >> 8);
    m_CRC16 = crc;

    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_CRC16 = m_CRC16;

    return true;
}

std::vector<int16_t> calib_table::getZ()
{
    return m_Zd;
}

bool calib_table::setX(std::vector<int16_t> Xd)
{
    m_Xd = Xd;
    if(m_Data.size() != 2047*2048*4)
        m_Data.resize(2047*2048*4);

    int16_t NaN = -32768;
    // Copy tables
    for (size_t iRow = 0; iRow < 2*m_Height; iRow++) // x2 resolution in vertical
    {
        for (size_t iCol = 0; iCol < m_Width; iCol++)
        {
            int16_t valX = Xd[iRow * m_Width + iCol];
            if (valX != NaN)
            {
                m_Data[iCol*2048*4 + iRow*4 + 0] = ((uint8_t*)&valX)[0];
                m_Data[iCol*2048*4 + iRow*4 + 1] = ((uint8_t*)&valX)[1];
            }
            else
            {
                m_Data[iCol*2048*4 + iRow*4 + 0] = ((uint8_t*)&NaN)[0];
                m_Data[iCol*2048*4 + iRow*4 + 1] = ((uint8_t*)&NaN)[1];
            }
        }
    }

    if (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize != 0)
    {
        free (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data);
        ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = 0;
    }
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data
            = (uint8_t*)calloc(m_Data.size(), sizeof (uint8_t));
    memcpy(((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data, m_Data.data(), m_Data.size());
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = m_Data.size();

    uint16_t crc = 0;
    int len = m_Data.size();
    uint16_t* data16 = (uint16_t*)m_Data.data();

    while(len > 1)
    {
        crc += 44111 * *data16++;
        len -= sizeof(uint16_t);
    }
    if (len > 0) crc += *(uint8_t*)data16;
    crc = crc ^ (crc >> 8);
    m_CRC16 = crc;

    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_CRC16 = m_CRC16;

    return true;
}

std::vector<int16_t> calib_table::getX()
{
    return m_Xd;
}
bool calib_table::setZX(std::vector<int16_t> Zd, std::vector<int16_t> Xd)
{
    m_Zd = Zd;
    m_Xd = Xd;

    if(m_Data.size() != 2047*2048*4)
        m_Data.resize(2047*2048*4);

    int16_t NaN = -32768;
    // Copy tables
    for (size_t iRow = 0; iRow < 2*m_Height; iRow++) // x2 resolution in vertical
    {
        for (size_t iCol = 0; iCol < m_Width; iCol++)
        {
            int16_t valX = Xd[iRow*m_Width + iCol];
            int16_t valZ = Zd[iRow*m_Width + iCol];
            if (valZ != NaN)
            {
                m_Data[iCol*2048*4 + iRow*4 + 0] = ((uint8_t*)&valX)[0];
                m_Data[iCol*2048*4 + iRow*4 + 1] = ((uint8_t*)&valX)[1];
                m_Data[iCol*2048*4 + iRow*4 + 2 + 0] = ((uint8_t*)&valZ)[0];
                m_Data[iCol*2048*4 + iRow*4 + 2 + 1] = ((uint8_t*)&valZ)[1];
            }
            else
            {
                m_Data[iCol*2048*4 + iRow*4 + 0] = ((uint8_t*)&NaN)[0];
                m_Data[iCol*2048*4 + iRow*4 + 1] = ((uint8_t*)&NaN)[1];
                m_Data[iCol*2048*4 + iRow*4 + 2 + 0] = ((uint8_t*)&NaN)[0];
                m_Data[iCol*2048*4 + iRow*4 + 2 + 1] = ((uint8_t*)&NaN)[1];
            }
        }
    }

    if (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize != 0)
    {
        free (((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data);
        ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = 0;
    }
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data
            = (uint8_t*)calloc(m_Data.size(), sizeof (uint8_t));
    memcpy(((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_Data, m_Data.data(), m_Data.size());
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_DataSize = m_Data.size();

    uint16_t crc = 0;
    int len = m_Data.size();
    uint16_t* data16 = (uint16_t*)m_Data.data();

    while(len > 1)
    {
        crc += 44111 * *data16++;
        len -= sizeof(uint16_t);
    }
    if (len > 0) crc += *(uint8_t*)data16;
    crc = crc ^ (crc >> 8);
    m_CRC16 = crc;

    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_CRC16 = m_CRC16;

    return true;

}

bool calib_table::updateTimeStamp()
{
    m_TimeStamp = time(nullptr);
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_TimeStamp = m_TimeStamp;
    return true;
}

bool calib_table::setTimeStamp(int value)
{
    m_TimeStamp = value;
    ((rf627_calib_table_t*)m_CalibTableBase)->rf627smart_calib_table->m_TimeStamp = m_TimeStamp;
    return true;
}

bool calib_table::save_to_file(std::string file_name)
{
    FILE* pFile;
    pFile = fopen(file_name.c_str(), "wb");

    std::vector<char> bytes;

    if (this->convert_to_bytes(bytes))
    {
        char* data = bytes.data();
        fwrite(data, 1, bytes.size(), pFile);
        fclose(pFile);
        return true;
    }
    else
    {
        return false;
    }
}

bool calib_table::convert_to_bytes(std::vector<char>& bytes)
{

    uint32_t data_size = 0;
    char* data = nullptr;
    bool result = convert_calibration_table_to_bytes(
                (rf627_calib_table_t*)m_CalibTableBase, &data, &data_size);

    if (result && data_size > 0)
    {
        bytes = std::vector<char>(data, data + data_size);
        free(data);
        return true;
    }
    else
        return false;
}

ApproxTable::ApproxTable() : SettingsModel()
{
    m_approxTableBase = new rf627_approx_table_t();
}

ApproxTable::~ApproxTable()
{
    delete (rf627_approx_table_t*)m_approxTableBase;
}

ApproxTable_v6::ApproxTable_v6() : ApproxTable_v6(nullptr)
{

}

ApproxTable_v6::ApproxTable_v6(void* base) : ApproxTable()
{
    ((rf627_approx_table_t*)m_approxTableBase)->version = 6;

    addProperty("version", (unsigned int)6);
    addProperty("crc_x", (unsigned int)0, (unsigned int)0, (unsigned int)65535);
    addProperty("crc_z", (unsigned int)0, (unsigned int)0, (unsigned int)65535);
    addProperty("serial", (unsigned int)0);
    addProperty("width", (unsigned int)32, (unsigned int)32, (unsigned int)65535);
    addProperty("height", (unsigned int)32, (unsigned int)32, (unsigned int)65535);
    addProperty("scaling_factor", (float)0.0);
    addProperty("polynomial_degree_x", (unsigned int)2, (unsigned int)2, (unsigned int)8);
    addProperty("polynomial_degree_z", (unsigned int)2, (unsigned int)2, (unsigned int)8);
    addProperty("time_stamp", (unsigned int)0);
    addProperty("poly_coef_x", std::vector<std::vector<float>>());
    addProperty("poly_coef_z", std::vector<std::vector<float>>());

    if (base != nullptr)
        convertFromBase(base);
}

ApproxTable_v6::~ApproxTable_v6()
{
}

std::string ApproxTable_v6::getVersion()
{
    return std::to_string(props("version")->getValue<unsigned int>());
}

bool ApproxTable_v6::readFromFile(std::string fileName){
    std::ifstream input(fileName, std::ios::binary);
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});
    return parseFromBytes(buffer);
}

bool ApproxTable_v6::saveToFile(std::string fileName)
{
    std::vector<uint8_t> bytes = convertToBytes();

    if (bytes.size() > 0)
    {
        std::ofstream file(fileName, std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        file.close();
        return true;
    }

    return false;
 }

bool ApproxTable_v6::parseFromBytes(std::vector<uint8_t> bytes)
{
    convert_approximation_table_from_bytes(
                (rf627_approx_table_t*)m_approxTableBase, (char*)bytes.data(), (uint32_t)bytes.size());

    return convertFromBase(m_approxTableBase);
}

std::vector<uint8_t> ApproxTable_v6::convertToBytes()
{
    uint32_t data_size = 0;
    char* data = nullptr;

    convertToBase(m_approxTableBase);

    bool result = convert_approximation_table_to_bytes(
                (rf627_approx_table_t*)m_approxTableBase, &data, &data_size);

    std::cout << data_size << std::endl;
    if (result && data_size > 0)
    {
        auto bytes = std::vector<uint8_t>(data, data + data_size);
        free(data);
        return bytes;
    }
    else
        return std::vector<uint8_t>();
}

bool ApproxTable_v6::setSerial(unsigned int value)
{
    return setProperty("serial", value);
}

bool ApproxTable_v6::setWidth(unsigned int value)
{
    return setProperty("width", value);
}

bool ApproxTable_v6::setHeight(unsigned int value)
{
    return setProperty("height", value);
}

bool ApproxTable_v6::setScalingFactor(float value)
{
    return setProperty("scaling_factor", value);
}

bool ApproxTable_v6::setPolyDegreeX(unsigned int value)
{
    return setProperty("polynomial_degree_x", value);
}

bool ApproxTable_v6::setPolyDegreeZ(unsigned int value)
{
    return setProperty("polynomial_degree_z", value);
}

bool ApproxTable_v6::updateTimeStamp()
{
    return setProperty("time_stamp", (unsigned int)time(nullptr));
}

bool ApproxTable_v6::setPolyCoeffsX(std::vector<std::vector<float>> value)
{
    props("crc_x")->setValue(crc16(value));
    return setProperty("poly_coef_x", value);
}

bool ApproxTable_v6::setPolyCoeffsZ(std::vector<std::vector<float>> value)
{
    props("crc_z")->setValue(crc16(value));
    return setProperty("poly_coef_z", value);
}

unsigned int ApproxTable_v6::getCrcX()
{
    return props("crc_x")->getValue<unsigned int>();
}

unsigned int ApproxTable_v6::getCrcZ()
{
    return props("crc_z")->getValue<unsigned int>();
}

unsigned int ApproxTable_v6::getSerial()
{
    return props("serial")->getValue<unsigned int>();
}

unsigned int ApproxTable_v6::getWidth()
{
    return props("width")->getValue<unsigned int>();
}

unsigned int ApproxTable_v6::getHeight()
{
    return props("height")->getValue<unsigned int>();
}

float ApproxTable_v6::getScalingFactor()
{
    return props("scaling_factor")->getValue<float>();
}

unsigned int ApproxTable_v6::getPolyDegreeX()
{
    return props("polynomial_degree_x")->getValue<unsigned int>();
}

unsigned int ApproxTable_v6::getPolyDegreeZ()
{
    return props("polynomial_degree_z")->getValue<unsigned int>();
}

unsigned int ApproxTable_v6::getTimeStamp()
{
    return props("time_stamp")->getValue<unsigned int>();
}

std::vector<std::vector<float>> ApproxTable_v6::getPolyCoeffsX()
{
    return props("poly_coef_x")->getValue<std::vector<std::vector<float>>>();
}

std::vector<std::vector<float> > ApproxTable_v6::getPolyCoeffsZ()
{
    return props("poly_coef_z")->getValue<std::vector<std::vector<float>>>();
}

bool ApproxTable_v6::convertFromBase(void* base)
{
    if (base != nullptr && ((rf627_approx_table_t*)base)->version == 6 && ((rf627_approx_table_t*)base)->table_v6 != nullptr)
    {
        rf627_smart_approx_table_v6_t* table_v6 = ((rf627_approx_table_t*)base)->table_v6;

        std::vector<std::vector<float>> coeffsX(table_v6->width, std::vector<float>(table_v6->polynomial_degree_x));
        std::vector<std::vector<float>> coeffsZ(table_v6->width, std::vector<float>(table_v6->polynomial_degree_z));
        for (int i = 0; i < table_v6->width; i++){
            if (table_v6->poly_coef_x)
                for (int j = 0; j < table_v6->polynomial_degree_x; j++)
                    coeffsX[i][j] = table_v6->poly_coef_x[(i * table_v6->polynomial_degree_x + j) * sizeof(float)];

            if (table_v6->poly_coef_z)
                for (int j = 0; j < table_v6->polynomial_degree_z; j++)
                    coeffsZ[i][j] = table_v6->poly_coef_z[(i * table_v6->polynomial_degree_z + j) * sizeof(float)];
        }

        setProperty("crc_x", table_v6->crc_x);
        setProperty("crc_z", table_v6->crc_z);
        setProperty("serial", table_v6->serial);
        setProperty("width", table_v6->width);
        setProperty("height", table_v6->height);
        setProperty("scaling_factor", table_v6->scaling_factor);
        setProperty("polynomial_degree_x", table_v6->polynomial_degree_x);
        setProperty("polynomial_degree_z", table_v6->polynomial_degree_z);
        setProperty("time_stamp", table_v6->time_stamp);
        setProperty("poly_coef_x", coeffsX);
        setProperty("poly_coef_z", coeffsZ);
        return true;
    }
    return false;
}

bool ApproxTable_v6::convertToBase(void* base)
{
    if (((rf627_approx_table_t*)base)->table_v6 == nullptr)
    {
        ((rf627_approx_table_t*)base)->table_v6 =
                (rf627_smart_approx_table_v6_t*)calloc(1, sizeof (rf627_smart_approx_table_v6_t));
    }

    rf627_smart_approx_table_v6_t* table = ((rf627_approx_table_t*)base)->table_v6;
    table->version = props("version")->getValue<unsigned int>();
    table->crc_x = props("crc_x")->getValue<unsigned int>();
    table->crc_z = props("crc_z")->getValue<unsigned int>();
    table->serial = props("serial")->getValue<unsigned int>();
    table->width = props("width")->getValue<unsigned int>();
    table->height = props("height")->getValue<unsigned int>();
    table->scaling_factor = props("scaling_factor")->getValue<float>();
    table->polynomial_degree_x = props("polynomial_degree_x")->getValue<unsigned int>();
    table->polynomial_degree_z = props("polynomial_degree_z")->getValue<unsigned int>();
    table->time_stamp = props("time_stamp")->getValue<unsigned int>();

    auto poly_coef_x = props("poly_coef_x")->getValue<std::vector<std::vector<float>>>();
    auto poly_coef_z = props("poly_coef_z")->getValue<std::vector<std::vector<float>>>();


    if (!table->poly_coef_x)
    {
        table->poly_coef_x = (float*)calloc(table->width * table->polynomial_degree_x, sizeof (float));
    }
    if (!table->poly_coef_z)
    {
        table->poly_coef_z = (float*)calloc(table->width * table->polynomial_degree_z, sizeof (float));
    }

    for (int i = 0; i < table->width; i++)
    {
        for (int j = 0; j < table->polynomial_degree_x; j++){
            table->poly_coef_x[i * table->polynomial_degree_x + j] = poly_coef_x[i][j];
        }
        for (int j = 0; j < table->polynomial_degree_z; j++){
            table->poly_coef_z[i * table->polynomial_degree_z + j] = poly_coef_z[i][j];
        }
    }


    return true;
}

bool ApproxTable_v6::clearBase(void* base)
{
    switch (((rf627_approx_table_t*)base)->version) {
    case 6:
        if (((rf627_approx_table_t*)base)->table_v6)
        {
            if (((rf627_approx_table_t*)base)->table_v6->poly_coef_x)
                free(((rf627_approx_table_t*)base)->table_v6->poly_coef_x);
            if (((rf627_approx_table_t*)base)->table_v6->poly_coef_z)
                free(((rf627_approx_table_t*)base)->table_v6->poly_coef_z);
            free(((rf627_approx_table_t*)base)->table_v6);
            ((rf627_approx_table_t*)base)->table_v6 = nullptr;
        }
        return true;
    }
    return false;
}

unsigned int ApproxTable_v6::crc16(std::vector<std::vector<float>> value)
{
    std::vector<float> _vec;

    for (int i = 0; i < value.size(); i++)
        for (int j = 0; j < value[i].size(); j++)
            _vec.push_back(value[i][j]);

    uint16_t crc = 0;
    uint16_t* data16 = (uint16_t*)_vec.data();

    int len = _vec.size();
    while(len > 1)
    {
        crc += 44111 * *data16++;
        len -= sizeof(uint16_t);
    }
    if (len > 0) crc += *(uint8_t*)data16;
    crc = crc ^ (crc >> 8);
    return crc;
}


typedef struct
{
  std::string  name;
  std::string  type;
  std::string  access;
  uint16_t     index;
  uint32_t	   offset;
  uint32_t	   size;
  std::string  units;
  template <typename T>
  auto get_value()->decltype( std::declval<T>().value )
  {
      return ((T*)this)->value;
  }
  template <typename T>
  void set_value(decltype( std::declval<T>().value) value)
  {
      ((T*)this)->value = value;
  }
  template <typename T>
  auto get_min()->decltype( std::declval<T>().min )
  {
      return ((T*)this)->min;
  }
  template <typename T>
  auto get_max()->decltype( std::declval<T>().max )
  {
      return ((T*)this)->max;
  }
  template <typename T>
  auto get_step()->decltype( std::declval<T>().max )
  {
      return ((T*)this)->step;
  }
  template <typename T>
  auto get_default_value()->decltype( std::declval<T>().defaultValue )
  {
      return ((T*)this)->defaultValue;
  }
  template <typename T>
  auto get_values_enum()->decltype( std::declval<T>().valuesEnum )
  {
      return ((T*)this)->valuesEnum;
  }
  template <typename T>
  auto get_units()->decltype( std::declval<T>().units )
  {
      return ((T*)this)->units;
  }
  template <typename T>
  auto get_count()->decltype( std::declval<T>().maxCount )
  {
      return ((T*)this)->maxCount;
  }
  template <typename T>
  auto get_default_count()->decltype( std::declval<T>().defCount )
  {
      return ((T*)this)->defCount;
  }
  template <typename T>
  auto get_max_length()->decltype( std::declval<T>().maxLen )
  {
      return ((T*)this)->maxLen;
  }
}param_t;

typedef struct value_uint32 : param_t
{
  uint32_t    min;
  uint32_t    max;
  uint32_t    defaultValue;
  std::vector <std::tuple<uint32_t, std::string, std::string>> valuesEnum;
  uint32_t    value;
  uint32_t    step;
}value_uint32;

typedef struct value_uint64 : param_t
{
  uint64_t    min;
  uint64_t    max;
  uint64_t    defaultValue;
  std::vector <std::tuple<uint64_t, std::string, std::string>> valuesEnum;
  uint64_t    value;
  uint64_t    step;
}value_uint64;

typedef struct value_int32 : param_t
{
  int32_t     min;
  int32_t     max;
  int32_t     defaultValue;
  std::vector <std::tuple<int32_t, std::string, std::string>> valuesEnum;
  int32_t     value;
  int32_t     step;
}value_int32;

typedef struct value_int64 : param_t
{
  int64_t     min;
  int64_t     max;
  int64_t     defaultValue;
  std::vector <std::tuple<int64_t, std::string, std::string>> valuesEnum;
  int64_t     value;
  int64_t     step;
}value_int64;

typedef struct value_flt : param_t
{
  float        min;
  float        max;
  float        step;
  float        defaultValue;
  float        value;
}value_flt;

typedef struct value_dbl : param_t
{
  double        min;
  double        max;
  double        step;
  double        defaultValue;
  double        value;
}value_dbl;

typedef struct array_uint32 : param_t
{
  uint32_t    min;
  uint32_t    max;
  uint32_t    step;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <uint32_t> defaultValue;
  uint32_t    count;
  std::vector <uint32_t> value;
}array_uint32;

typedef struct array_uint64 : param_t
{
  uint64_t    min;
  uint64_t    max;
  uint64_t    step;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <uint64_t>   defaultValue;
  uint32_t    count;
  std::vector <uint64_t>   value;
}array_uint64;

typedef struct array_int32 : param_t
{
  int32_t     min;
  int32_t     max;
  int32_t     step;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <int32_t> defaultValue;
  uint32_t    count;
  std::vector <int32_t> value;
}array_int32;

typedef struct array_int64 : param_t
{
  int64_t     min;
  int64_t     max;
  int64_t     step;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <int64_t> defaultValue;
  uint32_t    count;
  std::vector <int64_t> value;
}array_int64;

typedef struct array_flt : param_t
{
  float       min;
  float       max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <float> defaultValue;
  uint32_t    count;
  std::vector <float> value;
}array_flt;

typedef struct array_dbl : param_t
{
  double      min;
  double      max;
  uint32_t    maxCount;
  uint32_t    defCount;
  std::vector <double> defaultValue;
  uint32_t    count;
  std::vector <double> value;
}array_dbl;

typedef struct value_str : param_t
{
  uint16_t      maxLen;
  std::string   defaultValue;
  std::string   value;
}value_str;

typedef struct value_raw : param_t
{
  void*         raw_data;
}value_raw;




param_t* create_param_from_type(std::string type)
{
    param_t* p = nullptr;
    if(type == "uint32_t")
    {
        p = new value_uint32();
        p->type = type;
    }else if(type == "uint64_t")
    {
        p = new value_uint64();
        p->type = type;
    }else if(type == "int32_t")
    {
        p = new value_int32();
        p->type = type;
    }else if(type == "int64_t")
    {
        p = new value_int64();
        p->type = type;
    }else if(type == "float_t")
    {
        p = new value_flt();
        p->type = type;
    }else if(type == "double_t")
    {
        p = new value_dbl();
        p->type = type;
    }else if(type == "u32_arr_t")
    {
        p = new array_uint32();
        p->type = type;
    }else if(type == "u64_arr_t")
    {
        p = new array_uint64();
        p->type = type;
    }else if(type == "i32_arr_t")
    {
        p = new array_int32();
        p->type = type;
    }else if(type == "i64_arr_t")
    {
        p = new array_int64();
        p->type = type;
    }else if(type == "flt_array_t")
    {
        p = new array_flt();
        p->type = type;
    }else if(type == "dbl_array_t")
    {
        p = new array_dbl();
        p->type = type;
    }else if(type == "string_t")
    {
        p = new value_str();
        p->type = type;
    }
    return p;
}

template<typename T>
ValueEnum<T>::ValueEnum(std::vector<std::tuple<T, std::string, std::string>> enum_base)
{
    _enum_base = enum_base;
}

template <typename T>
T ValueEnum<T>::getValue(std::string key) const
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(), [key](const std::tuple<T, std::string, std::string>& e) {return std::get<1>(e) == key;});
    if (it != _enum_base.end())
    {
        return std::get<0>(*it);
    }else
    {
        throw "No enum item for the specified key";
    }
}

template <typename T>
std::string ValueEnum<T>::getLabel(std::string key) const
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(), [key](const std::tuple<T, std::string, std::string>& e) {return std::get<1>(e) == key;});
    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw "No enum item for the specified key";
    }
}

template <typename T>
std::string ValueEnum<T>::findLabel(T value) const
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(), [value](const std::tuple<T, std::string, std::string>& e) {return std::get<0>(e) == value;});
    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw "No enum item at the specified value";
    }
}

template <typename T>
std::string ValueEnum<T>::findKey(T value) const
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(), [value](const std::tuple<T, std::string, std::string>& e) {return std::get<0>(e) == value;});
    if (it != _enum_base.end())
    {
        return std::get<1>(*it);
    }else
    {
        throw "No enum item at the specified index";
    }
}

template <typename T>
std::vector<T> ValueEnum<T>::getValueList() const
{
    std::vector<T> result;
    for (auto &item : _enum_base)
        result.push_back(std::get<0>(item));
    return result;
}

template <typename T>
std::vector<std::string> ValueEnum<T>::getKeyList() const
{
    std::vector<std::string> result;
    for (auto &item : _enum_base)
        result.push_back(std::get<1>(item));
    return result;
}

template <typename T>
std::vector<std::string> ValueEnum<T>::getLabelList() const
{
    std::vector<std::string> result;
    for (auto &item : _enum_base)
        result.push_back(std::get<2>(item));
    return result;
}

template <typename T>
std::tuple<T, std::string, std::string> ValueEnum<T>::getItem(uint32_t index) const
{
    if (index < _enum_base.size())
    {
        return _enum_base[index];
    }else
    {
        throw "No enum item at the specified index";
    }
}

template <typename T>
std::vector<std::tuple<T, std::string, std::string>> ValueEnum<T>::getItemList() const
{
    return _enum_base;
}



param::param(void* init_param) : 
    param_base(nullptr)
{
    parameter_t* p = (parameter_t*)init_param;

    if (p != NULL)
    {
        param_base = create_param_from_type(std::string(p->base.type));
        param_t* result = (param_t*)param_base;

        if (result->type == "uint32_t")
        {
            result->set_value<value_uint32>(p->val_uint32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((value_uint32*)result)->defaultValue = p->val_uint32->defValue;
            ((value_uint32*)result)->value = p->val_uint32->value;
            ((value_uint32*)result)->min = p->val_uint32->min;
            ((value_uint32*)result)->max = p->val_uint32->max;
            ((value_uint32*)result)->step = p->val_uint32->step;

            if(p->val_uint32->enumValues != NULL)
            for(int i = 0; i < p->val_uint32->enumValues->recCount; i++)
                ((value_uint32*)result)->valuesEnum.push_back(std::make_tuple(
                            p->val_uint32->enumValues->rec[i].value,
                            p->val_uint32->enumValues->rec[i].key,
                            p->val_uint32->enumValues->rec[i].label));
        }
        else if (result->type == "uint64_t")
        {
            result->set_value<value_uint64>(p->val_uint64->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;
            ((value_uint64_t*)result)->step = p->val_uint64->step;

            ((value_uint64*)result)->defaultValue = p->val_uint64->defValue;
            ((value_uint64*)result)->value = p->val_uint64->value;
            ((value_uint64*)result)->min = p->val_uint64->min;
            ((value_uint64*)result)->max = p->val_uint64->max;

            if(p->val_uint64->enumValues != NULL)
            for(int i = 0; i < p->val_uint64->enumValues->recCount; i++)
                ((value_uint64*)result)->valuesEnum.push_back(std::make_tuple(
                            p->val_uint64->enumValues->rec[i].value,
                            p->val_uint64->enumValues->rec[i].key,
                            p->val_uint64->enumValues->rec[i].label));
        }
        else if (result->type == "int32_t")
        {
            result->set_value<value_int32>(p->val_int32->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((value_int32*)result)->defaultValue = p->val_int32->defValue;
            ((value_int32*)result)->value = p->val_int32->value;
            ((value_int32*)result)->min = p->val_int32->min;
            ((value_int32*)result)->max = p->val_int32->max;
            ((value_int32*)result)->step = p->val_int32->step;

            if(p->val_int32->enumValues != NULL)
            for(int i = 0; i < p->val_int32->enumValues->recCount; i++)
                ((value_int32*)result)->valuesEnum.push_back(std::make_tuple(
                            p->val_int32->enumValues->rec[i].value,
                            p->val_int32->enumValues->rec[i].key,
                            p->val_int32->enumValues->rec[i].label));

        }
        else if (result->type == "int64_t")
        {
            result->set_value<value_int64>(p->val_int64->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((value_int64*)result)->defaultValue = p->val_int64->defValue;
            ((value_int64*)result)->value = p->val_int64->value;
            ((value_int64*)result)->min = p->val_int64->min;
            ((value_int64*)result)->max = p->val_int64->max;
            ((value_int64*)result)->step = p->val_int64->step;

            if(p->val_int64->enumValues != NULL)
            for(int i = 0; i < p->val_int64->enumValues->recCount; i++)
                ((value_int64*)result)->valuesEnum.push_back(std::make_tuple(
                            p->val_int64->enumValues->rec[i].value,
                            p->val_int64->enumValues->rec[i].key,
                            p->val_int64->enumValues->rec[i].label));

        }
        else if (result->type == "float_t")
        {
            result->set_value<value_flt>(p->val_flt->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((value_flt*)result)->defaultValue = p->val_flt->defValue;
            ((value_flt*)result)->value = p->val_flt->value;
            ((value_flt*)result)->min = p->val_flt->min;
            ((value_flt*)result)->max = p->val_flt->max;
            ((value_flt*)result)->step = p->val_flt->step;
        }
        else if (result->type == "double_t")
        {
            result->set_value<value_dbl>(p->val_dbl->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((value_dbl*)result)->defaultValue = p->val_dbl->defValue;
            ((value_dbl*)result)->value = p->val_dbl->value;
            ((value_dbl*)result)->min = p->val_dbl->min;
            ((value_dbl*)result)->max = p->val_dbl->max;
            ((value_dbl*)result)->step = p->val_dbl->step;
        }
        else if (result->type == "u32_arr_t")
        {
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((array_uint32*)result)->step = p->arr_uint32->step;
            for(size_t i = 0; i < p->arr_uint32->defCount; i++)
                ((array_uint32*)result)->defaultValue.push_back(p->arr_uint32->defValue[i]);
            for(size_t i = 0; i < p->arr_uint32->count; i++)
                ((array_uint32*)result)->value.push_back(p->arr_uint32->value[i]);
            ((array_uint32*)result)->min = p->arr_uint32->min;
            ((array_uint32*)result)->max = p->arr_uint32->max;
            ((array_uint32*)result)->maxCount = p->arr_uint32->maxCount;
            ((array_uint32*)result)->defCount = p->arr_uint32->defCount;
            ((array_uint32*)result)->count = p->arr_uint32->count;
        }
        else if (result->type == "u64_arr_t")
        {
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((array_uint64*)result)->step = p->arr_uint64->step;
            for(size_t i = 0; i < p->arr_uint64->defCount; i++)
                ((array_uint64*)result)->defaultValue.push_back(p->arr_uint64->defValue[i]);
            for(size_t i = 0; i < p->arr_uint64->count; i++)
                ((array_uint64*)result)->value.push_back(p->arr_uint64->value[i]);
            ((array_uint64*)result)->min = p->arr_uint64->min;
            ((array_uint64*)result)->max = p->arr_uint64->max;
            ((array_uint64*)result)->maxCount = p->arr_uint64->maxCount;
            ((array_uint64*)result)->defCount = p->arr_uint64->defCount;
            ((array_uint64*)result)->count = p->arr_uint64->count;
        }
        else if (result->type == "i32_arr_t")
        {
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((array_int32*)result)->step = p->arr_int32->step;
            for(size_t i = 0; i < p->arr_int32->defCount; i++)
                ((array_int32*)result)->defaultValue.push_back(p->arr_int32->defValue[i]);
            for(size_t i = 0; i < p->arr_int32->count; i++)
                ((array_int32*)result)->value.push_back(p->arr_int32->value[i]);
            ((array_int32*)result)->min = p->arr_int32->min;
            ((array_int32*)result)->max = p->arr_int32->max;
            ((array_int32*)result)->maxCount = p->arr_int32->maxCount;
            ((array_int32*)result)->defCount = p->arr_int32->defCount;
            ((array_int32*)result)->count = p->arr_int32->count;
        }
        else if (result->type == "i64_arr_t")
        {
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((array_int64*)result)->step = p->arr_int64->step;
            for(size_t i = 0; i < p->arr_int64->defCount; i++)
                ((array_int64*)result)->defaultValue.push_back(p->arr_int64->defValue[i]);
            for(size_t i = 0; i < p->arr_int64->count; i++)
                ((array_int64*)result)->value.push_back(p->arr_int64->value[i]);
            ((array_int64*)result)->min = p->arr_int64->min;
            ((array_int64*)result)->max = p->arr_int64->max;
            ((array_int64*)result)->maxCount = p->arr_int64->maxCount;
            ((array_int64*)result)->defCount = p->arr_int64->defCount;
            ((array_int64*)result)->count = p->arr_int64->count;
        }
        else if (result->type == "flt_array_t")
        {
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            //((array_flt*)result)->step = p->arr_flt->step;
            for(size_t i = 0; i < p->arr_flt->defCount; i++)
                ((array_flt*)result)->defaultValue.push_back(p->arr_flt->defValue[i]);
            for(size_t i = 0; i < p->arr_flt->count; i++)
                ((array_flt*)result)->value.push_back(p->arr_flt->value[i]);
            ((array_flt*)result)->min = p->arr_flt->min;
            ((array_flt*)result)->max = p->arr_flt->max;
            ((array_flt*)result)->maxCount = p->arr_flt->maxCount;
            ((array_flt*)result)->defCount = p->arr_flt->defCount;
            ((array_flt*)result)->count = p->arr_flt->count;
        }
        else if (result->type == "dbl_array_t")
        {
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            //((array_dbl*)result)->step = p->arr_flt->step;
            for(size_t i = 0; i < p->arr_dbl->defCount; i++)
                ((array_dbl*)result)->defaultValue.push_back(p->arr_dbl->defValue[i]);
            for(size_t i = 0; i < p->arr_dbl->count; i++)
                ((array_dbl*)result)->value.push_back(p->arr_dbl->value[i]);
            ((array_dbl*)result)->min = p->arr_dbl->min;
            ((array_dbl*)result)->max = p->arr_dbl->max;
            ((array_dbl*)result)->maxCount = p->arr_dbl->maxCount;
            ((array_dbl*)result)->defCount = p->arr_dbl->defCount;
            ((array_dbl*)result)->count = p->arr_dbl->count;
        }
        else if (result->type == "string_t")
        {
            result->set_value<value_str>(p->val_str->value);
            result->name = p->base.name;
            result->access = p->base.access;
            result->index = p->base.index;
            result->offset = p->base.offset;
            result->size = p->base.size;
            if (p->base.units != nullptr)
                result->units = p->base.units;

            ((value_str*)result)->defaultValue = p->val_str->defValue;
            ((value_str*)result)->value = p->val_str->value;
            ((value_str*)result)->maxLen = p->val_str->maxLen;

//            parse_string_param(p, value_str_t, defaultValue);
//            parse_string_param(p, value_str_t, value);
//            parse_uint16_param(p, value_str_t, maxLen);

        }else if (result->type == "unknown_t")
        {
//            parse_string_param(p, value_raw_t, name);
//            parse_string_param(p, value_raw_t, type);
//            parse_string_param(p, value_raw_t, access);
//            parse_uint16_param(p, value_raw_t, index);
//            parse_uint32_param(p, value_raw_t, offset);
//            parse_uint32_param(p, value_raw_t, size);

//            parse_raw_param(p, value_raw_t);


        }
    }
}

param::~param()
{
        if (((param_t*)param_base)->type == "uint32_t")
        {
            delete ((value_uint32*)param_base);
        }
        else if (((param_t*)param_base)->type == "uint64_t")
        {
            delete ((value_uint64*)param_base);
        }
        else if (((param_t*)param_base)->type == "int32_t")
        {
            delete ((value_int32*)param_base);
        }
        else if (((param_t*)param_base)->type == "int64_t")
        {
            delete ((value_int64*)param_base);
        }
        else if (((param_t*)param_base)->type == "float_t")
        {
            delete ((value_flt*)param_base);
        }
        else if (((param_t*)param_base)->type == "double_t")
        {
            delete ((value_dbl*)param_base);
        }
        else if (((param_t*)param_base)->type == "u32_arr_t")
        {
            delete ((array_uint32*)param_base);
        }
        else if (((param_t*)param_base)->type == "u64_arr_t")
        {
            delete ((array_uint64*)param_base);
        }
        else if (((param_t*)param_base)->type == "i32_arr_t")
        {
            delete ((array_int32*)param_base);
        }
        else if (((param_t*)param_base)->type == "i64_arr_t")
        {
            delete ((array_int64*)param_base);
        }
        else if (((param_t*)param_base)->type == "flt_array_t")
        {
            delete ((array_flt*)param_base);
        }
        else if (((param_t*)param_base)->type == "dbl_array_t")
        {
            delete ((array_dbl*)param_base);
        }
        else if (((param_t*)param_base)->type == "string_t")
        {
            delete ((value_str*)param_base);
        }
}

std::string param::getName()
{
    return ((param_t*)param_base)->name;
}
std::string param::getType()
{
    return ((param_t*)param_base)->type;
}
std::string param::getAccess()
{
    return ((param_t*)param_base)->access;
}
std::string param::getUnits()
{
    return ((param_t*)param_base)->units;
}

uint16_t param::getIndex()
{
    return ((param_t*)param_base)->index;
}
uint32_t param::getOffset()
{
    return ((param_t*)param_base)->offset;
}
uint32_t param::getSize()
{
    return ((param_t*)param_base)->size;
}

template<> uint32_t param::getValue<uint32_t>() const
{
    return ((value_uint32*)param_base)->value;
}
template<> uint32_t param::getDefValue<uint32_t>() const
{
    return ((value_uint32*)param_base)->defaultValue;
}
template<> ValueEnum<uint32_t> param::getEnum<uint32_t>() const
{
    return ValueEnum<uint32_t>(((value_uint32*)param_base)->valuesEnum);
}
template<> bool param::setValue(uint32_t value) const
{
    ((value_uint32*)param_base)->value = value;
    return true;
}
template<> uint32_t param::getMin<uint32_t>() const
{
    return ((value_uint32*)param_base)->min;
}
template<> uint32_t param::getMax<uint32_t>() const
{
    return ((value_uint32*)param_base)->max;
}
template<> uint32_t param::getStep<uint32_t>() const
{
    return ((value_uint32*)param_base)->step;
}


template<> uint64_t param::getValue<uint64_t>() const
{
    return ((value_uint64*)param_base)->value;
}
template<> uint64_t param::getDefValue<uint64_t>() const
{
    return ((value_uint64*)param_base)->defaultValue;
}
template<> ValueEnum<uint64_t> param::getEnum<uint64_t>() const
{
    return ValueEnum<uint64_t>(((value_uint64*)param_base)->valuesEnum);
}
template<> bool param::setValue(uint64_t value) const
{
    ((value_uint64*)param_base)->value = value;
    return true;
}
template<> uint64_t param::getMin<uint64_t>() const
{
    return ((value_uint64*)param_base)->min;
}
template<> uint64_t param::getMax<uint64_t>() const
{
    return ((value_uint64*)param_base)->max;
}
template<> uint64_t param::getStep<uint64_t>() const
{
    return ((value_uint64*)param_base)->step;
}


template<> int32_t param::getValue<int32_t>() const
{
    return ((value_int32*)param_base)->value;
}
template<> int32_t param::getDefValue<int32_t>() const
{
    return ((value_int32*)param_base)->defaultValue;
}
template<> ValueEnum<int32_t> param::getEnum<int32_t>() const
{
    return ValueEnum<int32_t>(((value_int32*)param_base)->valuesEnum);
}
template<> bool param::setValue(int32_t value) const
{
    ((value_int32*)param_base)->value = value;
    return true;
}
template<> int32_t param::getMin<int32_t>() const
{
    return ((value_int32*)param_base)->min;
}
template<> int32_t param::getMax<int32_t>() const
{
    return ((value_int32*)param_base)->max;
}
template<> int32_t param::getStep<int32_t>() const
{
    return ((value_int32*)param_base)->step;
}


template<> int64_t param::getValue<int64_t>() const
{
    return ((value_int64*)param_base)->value;
}
template<> int64_t param::getDefValue<int64_t>() const
{
    return ((value_int64*)param_base)->defaultValue;
}
template<> ValueEnum<int64_t> param::getEnum<int64_t>() const
{
    return ValueEnum<int64_t>(((value_int64*)param_base)->valuesEnum);
}
template<> bool param::setValue(int64_t value) const
{
    ((value_int64*)param_base)->value = value;
    return true;
}
template<> int64_t param::getMin<int64_t>() const
{
    return ((value_int64*)param_base)->min;
}
template<> int64_t param::getMax<int64_t>() const
{
    return ((value_int64*)param_base)->max;
}
template<> int64_t param::getStep<int64_t>() const
{
    return ((value_int64*)param_base)->step;
}


template<> float param::getValue<float>() const
{
    return ((value_flt*)param_base)->value;
}
template<> float param::getDefValue<float>() const
{
    return ((value_flt*)param_base)->defaultValue;
}
template<> bool param::setValue(float value) const
{
    ((value_flt*)param_base)->value = value;
    return true;
}
template<> float param::getMin<float>() const
{
    return ((value_flt*)param_base)->min;
}
template<> float param::getMax<float>() const
{
    return ((value_flt*)param_base)->max;
}
template<> float param::getStep<float>() const
{
    return ((value_flt*)param_base)->step;
}


template<> double param::getValue<double>() const
{
    return ((value_dbl*)param_base)->value;
}
template<> double param::getDefValue<double>() const
{
    return ((value_dbl*)param_base)->defaultValue;
}
template<> bool param::setValue(double value) const
{
    ((value_dbl*)param_base)->value = value;
    return true;
}
template<> double param::getMin<double>() const
{
    return ((value_dbl*)param_base)->min;
}
template<> double param::getMax<double>() const
{
    return ((value_dbl*)param_base)->max;
}
template<> double param::getStep<double>() const
{
    return ((value_dbl*)param_base)->step;
}


template<> std::vector<uint32_t> param::getValue<std::vector<uint32_t>>() const
{
    return ((array_uint32*)param_base)->value;
}
template<> std::vector<uint32_t> param::getDefValue<std::vector<uint32_t>>() const
{
    return ((array_uint32*)param_base)->defaultValue;
}
template<> bool param::setValue(std::vector<uint32_t> value) const
{
    ((array_uint32*)param_base)->value = value;
    return true;
}

template<> std::vector<int32_t> param::getValue<std::vector<int32_t>>() const
{
    return ((array_int32*)param_base)->value;
}
template<> std::vector<int32_t> param::getDefValue<std::vector<int32_t>>() const
{
    return ((array_int32*)param_base)->defaultValue;
}
template<> bool param::setValue(std::vector<int32_t> value) const
{
    ((array_int32*)param_base)->value = value;
    return true;
}

template<> std::vector<uint64_t> param::getValue<std::vector<uint64_t>>() const
{
    return ((array_uint64*)param_base)->value;
}
template<> std::vector<uint64_t> param::getDefValue<std::vector<uint64_t>>() const
{
    return ((array_uint64*)param_base)->defaultValue;
}
template<> bool param::setValue(std::vector<uint64_t> value) const
{
    ((array_uint64*)param_base)->value = value;
    return true;
}


template<> std::vector<int64_t> param::getValue<std::vector<int64_t>>() const
{
    return ((array_int64*)param_base)->value;
}
template<> std::vector<int64_t> param::getDefValue<std::vector<int64_t>>() const
{
    return ((array_int64*)param_base)->defaultValue;
}
template<> bool param::setValue(std::vector<int64_t> value) const
{
    ((array_int64*)param_base)->value = value;
    return true;
}

template<> std::vector<float> param::getValue<std::vector<float>>() const
{
    return ((array_flt*)param_base)->value;
}
template<> std::vector<float> param::getDefValue<std::vector<float>>() const
{
    return ((array_flt*)param_base)->defaultValue;
}
template<> bool param::setValue(std::vector<float> value) const
{
    ((array_flt*)param_base)->value = value;
    return true;
}

template<> std::vector<double> param::getValue<std::vector<double>>() const
{
    return ((array_dbl*)param_base)->value;
}
template<> std::vector<double> param::getDefValue<std::vector<double>>() const
{
    return ((array_dbl*)param_base)->defaultValue;
}
template<> bool param::setValue(std::vector<double> value) const
{
    ((array_dbl*)param_base)->value = value;
    return true;
}

template<> std::string param::getValue<std::string>() const
{
    return ((value_str*)param_base)->value;
}
template<> std::string param::getDefValue<std::string>() const
{
    return ((value_str*)param_base)->defaultValue;
}
template<> bool param::setValue(std::string value) const
{
    ((value_str*)param_base)->value = value;
    return true;
}
template<> bool param::setValue(char const* value) const
{
    ((value_str*)param_base)->value = value;
    return true;
}


template<> const std::string param::getValue<const std::string>() const
{
    return ((value_str*)param_base)->value;
}
template<> const std::string param::getDefValue<const std::string>() const
{
    return ((value_str*)param_base)->defaultValue;
}


std::ostream &operator<<(std::ostream &out, version const &v)
{
    out << std::to_string(v.major) << "."
        << std::to_string(v.minor) << "."
        << std::to_string(v.patch);
    return out;
}

bool operator ==(const version &v1, const version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) ==
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator !=(const version &v1,const  version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) ==
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator <=(const version &v1, const version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) <=
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator >=(const version &v1, const version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) >=
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator <(const version &v1, const version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) <
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}
bool operator >(const version &v1, const version &v2)
{
    return (((v1.major << 24) + (v1.minor << 16) + (v1.patch << 8)) >
            ((v2.major << 24) + (v2.minor << 16) + (v2.patch << 8)) ? true : false);
}

std::string version::to_string() const
{
    std::string s;
    s = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    return s;
}

uint32_t version::to_uint()
{
    return _value;
}

version::version() : version((uint32_t)0)
{
}

version::version(uint32_t value)
{
    major = (((uint8_t*)(void*)(&value))[3]);
    minor = (((uint8_t*)(void*)(&value))[2]);
    patch = (((uint8_t*)(void*)(&value))[1]);
    _value = value;
}

version::version(std::string value)
{
    std::string s = value;
    std::string delimiter = ".";

    size_t pos = s.find(delimiter);
    std::string token;

    token = s.substr(0, pos);
    major =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    pos = s.find(delimiter);
    token = s.substr(0, pos);
    minor =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    pos = s.find(delimiter);
    token = s.substr(0, pos);
    patch =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    _value = (major << 3) + (minor << 2) + (patch << 1);
}

version::version(uint32_t *value)
{
    major = value[0];
    minor = value[1];
    patch = value[2];
    _value = (major << 3) + (minor << 2) + (patch << 1);
}

version::~version()
{

}

const std::string& hello_info::device_name()
{
    return _device_name;
}

const uint32_t& hello_info::serial_number()
{
    return _serial_number;
}

const std::string& hello_info::ip_address()
{
    return _ip_address;
}

const std::string& hello_info::mac_address()
{
    return _mac_address;
}

const uint16_t& hello_info::profile_port()
{
    return _profile_port;
}

const uint16_t& hello_info::service_port()
{
    return _service_port;
}

const version& hello_info::firmware_version()
{
    return _firmware_version;
}

const version& hello_info::hardware_version()
{
    return _hardware_version;
}

const uint32_t& hello_info::z_smr()
{
    return _z_smr;
}

const uint32_t& hello_info::z_mr()
{
    return _z_mr;
}

const uint32_t& hello_info::x_smr()
{
    return _x_smr;
}

const uint32_t& hello_info::x_emr()
{
    return _x_emr;
}

const uint32_t &hello_info::product_code()
{
    return _product_code;
}

hello_info::hello_info(void* info, SCANNER_TYPES type, PROTOCOLS protocol)
{
    switch (type) {
    case SCANNER_TYPES::RF627_OLD:
    {
        switch (protocol) {
        case PROTOCOLS::SERVICE:
        {
            _device_name = ((rf627_old_hello_info_by_service_protocol*)info)->device_name;
            _serial_number = ((rf627_old_hello_info_by_service_protocol*)info)->serial_number;

            in_addr addr = {0};
            uint32_t ip = ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[0] << 24 |
                          ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[1] << 16 |
                          ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[2] << 8 |
                          ((rf627_old_hello_info_by_service_protocol*)info)->ip_address[3];
            addr.s_addr = htonl(ip);
            _ip_address = inet_ntoa(addr);
            _mac_address = "";

            for (int i = 0; i < 6; i++)
            {
                if (i != 0)
                    _mac_address += ":";
                _mac_address += convert::to_hex(((rf627_old_hello_info_by_service_protocol*)info)->mac_address[i], 2);
            }

            _profile_port = ((rf627_old_hello_info_by_service_protocol*)info)->profile_port;
            _service_port = ((rf627_old_hello_info_by_service_protocol*)info)->service_port;

            _firmware_version = version(((rf627_old_hello_info_by_service_protocol*)info)->firmware_version);
            _hardware_version = version(((rf627_old_hello_info_by_service_protocol*)info)->hardware_version);

            _z_smr = ((rf627_old_hello_info_by_service_protocol*)info)->z_begin;
            _z_mr = ((rf627_old_hello_info_by_service_protocol*)info)->z_range;
            _x_smr = ((rf627_old_hello_info_by_service_protocol*)info)->x_begin;
            _x_emr = ((rf627_old_hello_info_by_service_protocol*)info)->x_end;
            _product_code = 627;
            break;
        }
        default:
            break;
        }
        break;
    }
    case SCANNER_TYPES::RF627_SMART:
    {
        switch (protocol) {
        case PROTOCOLS::SERVICE:
        {
            _device_name = ((rf627_smart_hello_info_by_service_protocol*)info)->user_general_deviceName;
            _serial_number = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_serial;
            _ip_address = ((rf627_smart_hello_info_by_service_protocol*)info)->user_network_ip;
            _mac_address = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_network_macAddr;

            _profile_port = ((rf627_smart_hello_info_by_service_protocol*)info)->user_network_hostPort;
            _service_port = ((rf627_smart_hello_info_by_service_protocol*)info)->user_network_servicePort;

            _firmware_version = version(((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_firmwareVer);
            _hardware_version = version(((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_hardwareVer);

            _z_smr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_smr;
            _z_mr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_mr;
            _x_smr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xsmr;
            _x_emr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xemr;
            _product_code = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_productCode;
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

hello_info::~hello_info()
{

}


profile2D::profile2D(void* profile_base)
{
    m_ProfileBase = profile_base;
    rf627_profile2D_t* profile_from_scanner = (rf627_profile2D_t*)profile_base;
    if(profile_from_scanner != nullptr)
    {
        switch (profile_from_scanner->type) {
        case kRF627_OLD:
        {
            if(profile_from_scanner->rf627old_profile2D != NULL)
            {
                m_Header.data_type =
                        profile_from_scanner->rf627old_profile2D->header.data_type;
                m_Header.flags =
                        profile_from_scanner->rf627old_profile2D->header.flags;
                m_Header.device_type =
                        profile_from_scanner->rf627old_profile2D->header.device_type;
                m_Header.serial_number =
                        profile_from_scanner->rf627old_profile2D->header.serial_number;
                m_Header.system_time =
                        profile_from_scanner->rf627old_profile2D->header.system_time;

                m_Header.proto_version_major =
                        profile_from_scanner->rf627old_profile2D->header.proto_version_major;
                m_Header.proto_version_minor =
                        profile_from_scanner->rf627old_profile2D->header.proto_version_minor;
                m_Header.hardware_params_offset =
                        profile_from_scanner->rf627old_profile2D->header.hardware_params_offset;
                m_Header.data_offset =
                        profile_from_scanner->rf627old_profile2D->header.data_offset;
                m_Header.packet_count =
                        profile_from_scanner->rf627old_profile2D->header.packet_count;
                m_Header.measure_count =
                        profile_from_scanner->rf627old_profile2D->header.measure_count;

                m_Header.zmr =
                        profile_from_scanner->rf627old_profile2D->header.v1_0_standart.zmr;
                m_Header.xemr =
                        profile_from_scanner->rf627old_profile2D->header.v1_0_standart.xemr;
                m_Header.discrete_value =
                        profile_from_scanner->rf627old_profile2D->header.v1_0_standart.discrete_value;

                m_Header.exposure_time =
                        profile_from_scanner->rf627old_profile2D->header.exposure_time;
                m_Header.laser_value =
                        profile_from_scanner->rf627old_profile2D->header.laser_value;
                m_Header.step_count =
                        profile_from_scanner->rf627old_profile2D->header.step_count;
                m_Header.dir =
                        profile_from_scanner->rf627old_profile2D->header.dir;
                m_Header.payload_size =
                        profile_from_scanner->rf627old_profile2D->header.payload_size;
                m_Header.bytes_per_point =
                        profile_from_scanner->rf627old_profile2D->header.bytes_per_point;

                switch (m_Header.data_type) {
                case DTY_PixelsNormal:
                case DTY_PixelsInterpolated:
                {
                    m_Pixels.resize(profile_from_scanner->
                                          rf627old_profile2D->pixels_format.pixels_count);

                    for(size_t i = 0; i < m_Pixels.size(); i++)
                    {
                        m_Pixels[i] = profile_from_scanner->
                                rf627old_profile2D->pixels_format.pixels[i];
                    }

                    if(profile_from_scanner->rf627old_profile2D->intensity_count > 0)
                    {
                        m_Intensity.resize(
                                    profile_from_scanner->rf627old_profile2D->intensity_count);
                        for (size_t i = 0; i < m_Intensity.size(); i++)
                            m_Intensity[i] =
                                    profile_from_scanner->rf627old_profile2D->intensity[i];
                    }

                    break;
                }
                case DTY_ProfileNormal:
                case DTY_ProfileInterpolated:
                {
                    m_Points.resize(profile_from_scanner->
                                          rf627old_profile2D->profile_format.points_count);

                    for(size_t i = 0; i < m_Points.size(); i++)
                    {
                        m_Points[i].x = profile_from_scanner->rf627old_profile2D->
                                profile_format.points[i].x;
                        m_Points[i].z = profile_from_scanner->rf627old_profile2D->
                                profile_format.points[i].z;
                    }

                    if(profile_from_scanner->rf627old_profile2D->intensity_count > 0)
                    {
                        m_Intensity.resize(
                                    profile_from_scanner->rf627old_profile2D->intensity_count);
                        for (size_t i = 0; i < m_Intensity.size(); i++)
                            m_Intensity[i] =
                                    profile_from_scanner->rf627old_profile2D->intensity[i];
                    }
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case kRF627_SMART:
        {
            if(profile_from_scanner->rf627smart_profile2D != NULL)
            {
                m_Header.data_type =
                        profile_from_scanner->rf627smart_profile2D->header.data_type;
                m_Header.flags =
                        profile_from_scanner->rf627smart_profile2D->header.flags;
                m_Header.device_type =
                        profile_from_scanner->rf627smart_profile2D->header.device_type;
                m_Header.serial_number =
                        profile_from_scanner->rf627smart_profile2D->header.serial_number;
                m_Header.system_time =
                        profile_from_scanner->rf627smart_profile2D->header.system_time;

                m_Header.proto_version_major =
                        profile_from_scanner->rf627smart_profile2D->header.proto_version_major;
                m_Header.proto_version_minor =
                        profile_from_scanner->rf627smart_profile2D->header.proto_version_minor;
                m_Header.hardware_params_offset =
                        profile_from_scanner->rf627smart_profile2D->header.hardware_params_offset;
                m_Header.data_offset =
                        profile_from_scanner->rf627smart_profile2D->header.data_offset;
                m_Header.packet_count =
                        profile_from_scanner->rf627smart_profile2D->header.packet_count;
                m_Header.measure_count =
                        profile_from_scanner->rf627smart_profile2D->header.measure_count;

                if (m_Header.proto_version_major == 1 && m_Header.proto_version_minor == 0)
                {
                    m_Header.zmr =
                            profile_from_scanner->rf627smart_profile2D->header.v1_0_standart.zmr;
                    m_Header.xemr =
                            profile_from_scanner->rf627smart_profile2D->header.v1_0_standart.xemr;
                    m_Header.discrete_value =
                            profile_from_scanner->rf627smart_profile2D->header.v1_0_standart.discrete_value;
                }else if (m_Header.proto_version_major == 1 && m_Header.proto_version_minor == 1)
                {
                    if (m_Header.data_type == SPDT_v1_1_ProfilePoly)
                    {
                        m_Header.zmr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_1_polynomial.zmr;
                        m_Header.xemr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_1_polynomial.xemr;
                        m_Header.scaling_factor =
                                profile_from_scanner->rf627smart_profile2D->header.v1_1_polynomial.scaling_factor;
                    }else
                    {
                        m_Header.zmr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_1_standart.zmr;
                        m_Header.xemr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_1_standart.xemr;
                        m_Header.discrete_value =
                                profile_from_scanner->rf627smart_profile2D->header.v1_1_standart.discrete_value;
                    }
                }else if (m_Header.proto_version_major == 1 && m_Header.proto_version_minor == 2)
                {
                    if (m_Header.data_type == SPDT_v1_2_ProfilePoly)
                    {
                        m_Header.zmr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_polynomial.zmr;
                        m_Header.xemr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_polynomial.xemr;
                        m_Header.scaling_factor =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_polynomial.scaling_factor;
                    }else
                    {
                        m_Header.zmr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_standart.zmr;
                        m_Header.xemr =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_standart.xemr;
                        m_Header.discrete_value =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_standart.discrete_value;
                        m_Header.alignment_with_sensor =
                                profile_from_scanner->rf627smart_profile2D->header.v1_2_standart.alignment_with_sensor;
                    }
                }

                m_Header.license_hash =
                        profile_from_scanner->rf627smart_profile2D->header.license_hash;

                m_Header.exposure_time =
                        profile_from_scanner->rf627smart_profile2D->header.exposure_time;
                m_Header.laser_value =
                        profile_from_scanner->rf627smart_profile2D->header.laser_value;
                m_Header.step_count =
                        profile_from_scanner->rf627smart_profile2D->header.step_count;
                m_Header.dir =
                        profile_from_scanner->rf627smart_profile2D->header.dir;
                m_Header.payload_size =
                        profile_from_scanner->rf627smart_profile2D->header.payload_size;
                m_Header.bytes_per_point =
                        profile_from_scanner->rf627smart_profile2D->header.bytes_per_point;

                if (m_Header.proto_version_major == 1 && m_Header.proto_version_minor == 0)
                {
                    switch (m_Header.data_type) {
                    case SPDT_v1_0_PixelsNormal:
                    case SPDT_v1_0_PixelsInterpolated:
                    {
                        m_Pixels.resize(profile_from_scanner->
                                              rf627smart_profile2D->pixels_format.pixels_count);

                        for(size_t i = 0; i < m_Pixels.size(); i++)
                        {
                            m_Pixels[i] = profile_from_scanner->
                                    rf627smart_profile2D->pixels_format.pixels[i];
                        }

                        if(profile_from_scanner->rf627smart_profile2D->intensity_count > 0)
                        {
                            m_Intensity.resize(
                                        profile_from_scanner->rf627smart_profile2D->intensity_count);
                            for (size_t i = 0; i < m_Intensity.size(); i++)
                                m_Intensity[i] =
                                        profile_from_scanner->rf627smart_profile2D->intensity[i];
                        }

                        break;
                    }
                    case SPDT_v1_0_ProfileNormal:
                    case SPDT_v1_0_ProfileInterpolated:
                    {
                        m_Points.resize(profile_from_scanner->
                                              rf627smart_profile2D->profile_format.points_count);

                        for(size_t i = 0; i < m_Points.size(); i++)
                        {
                            m_Points[i].x = profile_from_scanner->rf627smart_profile2D->
                                    profile_format.points[i].x;
                            m_Points[i].z = profile_from_scanner->rf627smart_profile2D->
                                    profile_format.points[i].z;
                        }

                        if(profile_from_scanner->rf627smart_profile2D->intensity_count > 0)
                        {
                            m_Intensity.resize(
                                        profile_from_scanner->rf627smart_profile2D->intensity_count);
                            for (size_t i = 0; i < m_Intensity.size(); i++)
                                m_Intensity[i] =
                                        profile_from_scanner->rf627smart_profile2D->intensity[i];
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }else if (m_Header.proto_version_major == 1 && m_Header.proto_version_minor == 1)
                {
                    switch (m_Header.data_type) {
                    case SPDT_v1_1_Pixels:
                    {
                        m_Pixels.resize(profile_from_scanner->
                                              rf627smart_profile2D->pixels_format.pixels_count);

                        for(size_t i = 0; i < m_Pixels.size(); i++)
                        {
                            m_Pixels[i] = profile_from_scanner->
                                    rf627smart_profile2D->pixels_format.pixels[i];
                        }

                        if(profile_from_scanner->rf627smart_profile2D->intensity_count > 0)
                        {
                            m_Intensity.resize(
                                        profile_from_scanner->rf627smart_profile2D->intensity_count);
                            for (size_t i = 0; i < m_Intensity.size(); i++)
                                m_Intensity[i] =
                                        profile_from_scanner->rf627smart_profile2D->intensity[i];
                        }

                        break;
                    }
                    case SPDT_v1_1_ProfilePoly:
                    case SPDT_v1_1_ProfileTable:
                    {
                        m_Points.resize(profile_from_scanner->
                                              rf627smart_profile2D->profile_format.points_count);

                        for(size_t i = 0; i < m_Points.size(); i++)
                        {
                            m_Points[i].x = profile_from_scanner->rf627smart_profile2D->
                                    profile_format.points[i].x;
                            m_Points[i].z = profile_from_scanner->rf627smart_profile2D->
                                    profile_format.points[i].z;
                        }

                        if(profile_from_scanner->rf627smart_profile2D->intensity_count > 0)
                        {
                            m_Intensity.resize(
                                        profile_from_scanner->rf627smart_profile2D->intensity_count);
                            for (size_t i = 0; i < m_Intensity.size(); i++)
                                m_Intensity[i] =
                                        profile_from_scanner->rf627smart_profile2D->intensity[i];
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (m_Header.proto_version_major == 1 && m_Header.proto_version_minor == 2)
                {
                    switch (m_Header.data_type) {
                    case SPDT_v1_2_Pixels:
                    {
                        m_Pixels.resize(profile_from_scanner->
                                              rf627smart_profile2D->pixels_format.pixels_count);

                        for(size_t i = 0; i < m_Pixels.size(); i++)
                        {
                            m_Pixels[i] = profile_from_scanner->
                                    rf627smart_profile2D->pixels_format.pixels[i];
                        }

                        if(profile_from_scanner->rf627smart_profile2D->intensity_count > 0)
                        {
                            m_Intensity.resize(
                                        profile_from_scanner->rf627smart_profile2D->intensity_count);
                            for (size_t i = 0; i < m_Intensity.size(); i++)
                                m_Intensity[i] =
                                        profile_from_scanner->rf627smart_profile2D->intensity[i];
                        }

                        break;
                    }
                    case SPDT_v1_2_ProfilePoly:
                    case SPDT_v1_2_ProfileTable:
                    {
                        m_Points.resize(profile_from_scanner->
                                              rf627smart_profile2D->profile_format.points_count);

                        for(size_t i = 0; i < m_Points.size(); i++)
                        {
                            m_Points[i].x = profile_from_scanner->rf627smart_profile2D->
                                    profile_format.points[i].x;
                            m_Points[i].z = profile_from_scanner->rf627smart_profile2D->
                                    profile_format.points[i].z;
                        }

                        if(profile_from_scanner->rf627smart_profile2D->intensity_count > 0)
                        {
                            m_Intensity.resize(
                                        profile_from_scanner->rf627smart_profile2D->intensity_count);
                            for (size_t i = 0; i < m_Intensity.size(); i++)
                                m_Intensity[i] =
                                        profile_from_scanner->rf627smart_profile2D->intensity[i];
                        }
                        break;
                    }
                    default:
                        break;
                    }
                }

            }
            break;
        }
        }
    }
}

//std::shared_ptr<profile2D> profile2D::read_from_file(std::string file_name)
//{
//    std::ifstream input(file_name, std::ios::binary);
//    std::vector<char> buffer(std::istreambuf_iterator<char>(input), {});
//    return parse_from_bytes(buffer);
//}

std::shared_ptr<profile2D> profile2D::parse_from_bytes(std::vector<char> bytes, int& parsed)
{
   if (bytes.size() > 0)
   {
       rf627_profile2D_t* profile = (rf627_profile2D_t*)calloc(1 ,sizeof(rf627_profile2D_t));
       parsed = convert_profile2D_from_bytes(profile, bytes.data(), bytes.size());
       std::shared_ptr<profile2D> result(new profile2D(profile));
       return result;
   }else
   {
       return nullptr;
   }
}

std::shared_ptr<profile2D> profile2D::parse_from_bytes(char *bytes, int size, int &parsed)
{
    if (size > 0)
    {
        rf627_profile2D_t* profile = (rf627_profile2D_t*)calloc(1 ,sizeof(rf627_profile2D_t));
        parsed = convert_profile2D_from_bytes(profile, bytes, size);
        std::shared_ptr<profile2D> result(new profile2D(profile));
        return result;
    }else
    {
        return nullptr;
    }
}

bool profile2D::save_to_file(std::string file_name, bool append)
{
    FILE* pFile;
    if (append)
        pFile = fopen(file_name.c_str(), "ab");
    else
        pFile = fopen(file_name.c_str(), "wb");

    std::vector<char> bytes;

    if (this->convert_to_bytes(bytes))
    {
        char* data = bytes.data();
        fwrite(data, 1, bytes.size(), pFile);
        fclose(pFile);
        return true;
    }
    else
    {
        return false;
    }
}

bool profile2D::convert_to_bytes(std::vector<char> &bytes)
{
    uint32_t data_size = 0;
    char* data = nullptr;
    bool result = convert_profile2D_to_bytes(
                (rf627_profile2D_t*)m_ProfileBase, &data, &data_size);

    if (result && data_size > 0)
    {
        bytes = std::vector<char>(data, data + data_size);
        free(data);
        return true;
    }
    else
        return false;
}

profile2D::~profile2D()
{
    rf627_profile2D_t* _profile = (rf627_profile2D_t*)m_ProfileBase;
    free_profile2D(_profile);
}

const profile2D::header& profile2D::getHeader()  const noexcept
{
    return m_Header;
}

const std::vector<uint8_t>& profile2D::getIntensity()  const noexcept
{
    return m_Intensity;
}

const std::vector<uint16_t>& profile2D::getPixels()  const noexcept
{
    return m_Pixels;
}

const std::vector<point2D_t>& profile2D::getPoints()  const noexcept
{
    return m_Points;
}

//
// RF627
// old version (v1.x.x)
//


std::vector<std::shared_ptr<rf627old>> rf627old::search(uint32_t timeout, bool only_available_result, PROTOCOLS protocol)
{
    if (!is_initialized)
        throw std::runtime_error("first you should initialize SDK - sdk_init()");

    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        get_search_mutex().lock();
        // Cleaning detected network adapter.
        FreeAdapterAddresses();
        // Retrieving addresses associated with adapters on the local computer.
        EnumAdapterAddresses();

        //Create value for scanners vector's type
        vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));

        //Initialization vector
        vector_init(&scanners);


        // Iterate over all available network adapters in the current operating
        // system to send "Hello" requests.
        uint32_t count = 0;
        for (int i=0; i<GetAdaptersCount(); i++)
        {
            uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
            uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
            // call the function to change adapter settings inside the library.
            set_platform_adapter_settings(host_mask, host_ip_addr);

            // Search for RF627-old devices over network by Service Protocol.
            if (host_ip_addr != 0)
            {
#ifdef NDEBUG
                 search_scanners(scanners, kRF627_OLD, timeout, kSERVICE);
                 count = (int)vector_count(scanners);
#else
                // Get another IP Addr and set this changes in adapter settings.
                printf("Search scanners from:\n "
                       "* IP Address\t: %s\n "
                       "* Netmask\t: %s\n",
                       GetAdapterAddress(i), GetAdapterMasks(i));
                search_scanners(scanners, kRF627_OLD, timeout, kSERVICE);

                // Print count of discovered rf627-old in network by Service Protocol
                printf("Discovered\t: %d RF627-Old\n",(int)vector_count(scanners)-count);
                printf("-----------------------------------------\n");
                count = (int)vector_count(scanners);
#endif
            }
        }

        static std::vector<std::shared_ptr<rf627old>> result;
        if (only_available_result)
        {
            auto it = std::find_if(result.begin(), result.end(), [](const std::shared_ptr<rf627old> obj){
                return obj->_is_connected == false && obj->_is_exist == false;
            });

            while (it != std::end(result))
            {
                int index = std::distance(result.begin(), it);
                result.erase(std::remove(result.begin(), result.end(), result[index]), result.end());
                it = std::find_if(std::next(it), result.end(), [](const std::shared_ptr<rf627old> obj){
                    return obj->_is_connected == false && obj->_is_exist == false;
                });
            }
        }

        std::vector<std::shared_ptr<rf627old>> available_result;

        std::vector<int> non_exist_index = std::vector<int>();
        for (size_t i = 0; i < result.size(); i++)
        {
            non_exist_index.push_back(i);
        }
        //Iterate over all discovered rf627-old in network and push into list.
        for(size_t i = 0; i < vector_count(scanners); i++)
        {
            scanner_base_t* scanner = (scanner_base_t*)vector_get(scanners,i);
            auto it = std::find_if(result.begin(), result.end(), [scanner](const std::shared_ptr<rf627old> obj){
               return scanner->rf627_old->info_by_service_protocol.serial_number == obj->get_info()->serial_number();
            });

            if (it == std::end(result))
            {
                result.push_back(std::shared_ptr<rf627old>(std::make_shared<rf627old>((void*)vector_get(scanners,i))));
                result[result.size() - 1]->current_protocol = PROTOCOLS::SERVICE;
            }else
            {
                int index = std::distance(result.begin(), it);
                result[index]->_is_exist = true;
                non_exist_index.erase(std::remove(non_exist_index.begin(), non_exist_index.end(), index), non_exist_index.end());
            }
        }

        for (size_t i = 0; i < non_exist_index.size(); i++)
        {
            result[non_exist_index[i]]->_is_exist = false;
        }

        if (only_available_result)
        {
            for (size_t i = 0; i < result.size(); i++)
                if (result[i]->_is_exist)
                    available_result.push_back(result[i]);
            get_search_mutex().unlock();
            return available_result;
        }

        get_search_mutex().unlock();
        return result;
        break;
    }
    default:
    {
        std::vector<std::shared_ptr<rf627old>> result;
        return result;
        break;
    }
    }

}

std::shared_ptr<hello_info> rf627old::get_info(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        hello_information info = get_info_about_scanner(((scanner_base_t*)this->scanner_base), kSERVICE);

        std::shared_ptr<hello_info> _hello_info(new hello_info(info.rf627old.hello_info_service_protocol, SCANNER_TYPES::RF627_OLD, PROTOCOLS::SERVICE));

        return _hello_info;
        break;
    }
    default:
        break;
    }

    return nullptr;
}

rf627old::rf627old(void* base)
{
    this->scanner_base = base;
    _is_connected = false;
    _is_exist = true;
}

std::mutex &rf627old::get_search_mutex()
{
    static std::mutex mutex_;
    return mutex_;
}

rf627old::~rf627old()
{
    free_scanner(((scanner_base_t*)this->scanner_base));
}

bool rf627old::connect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        connect_mutex.lock();
        bool result = false;
        if (_is_connected == false)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = connect_to_scanner(
                        ((scanner_base_t*)this->scanner_base), kSERVICE);
            _is_connected = result;
            if (_is_connected)
                read_params();
        }else
        {
            result = _is_connected;
        }
        connect_mutex.unlock();

        return result;
        break;
    }
    default:
        break;
    }

    return false;

}

bool rf627old::check_connection(uint32_t timeout, PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        bool result = false;
        if (_is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = check_connection_to_scanner(
                        ((scanner_base_t*)this->scanner_base), timeout, kSERVICE);
            _is_exist = result;
        }else
        {
            result = _is_connected;
        }

        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

bool rf627old::disconnect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        if (_is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = disconnect_from_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            if (result)
                _is_connected = FALSE;
            else
                _is_connected = TRUE;
        }else
        {
            result = TRUE;
            _is_connected = FALSE;
        }
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

std::shared_ptr<profile2D> rf627old::get_profile2D(
        bool zero_points, bool realtime,
        PROTOCOLS protocol)
{

    profile_mutex.lock();

    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Get profile from scanner's data stream by Service Protocol.
            rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                        (scanner_base_t*)scanner_base, zero_points, realtime, kSERVICE);

            if (profile_from_scanner != nullptr)
            {
                //std::shared_ptr<profile2D> result = std::make_shared<profile2D>(profile_from_scanner);
                std::shared_ptr<profile2D> result(new profile2D(profile_from_scanner));
                profile_mutex.unlock();
                return result;
            }
            free(profile_from_scanner);
            break;
        }
        default:
            break;
        }
    }
    profile_mutex.unlock();
    return nullptr;

}


bool rf627old::read_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            bool result = false;
            param_mutex.lock();
            result = read_params_from_scanner(
                        (scanner_base_t*)scanner_base, 300, kSERVICE);
            param_mutex.unlock();
            return result;
            break;
        }
        default:
            break;
        }
    }
    return false;
}

bool rf627old::write_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        result = write_params_to_scanner(
                    (scanner_base_t*)scanner_base, 300, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

bool rf627old::save_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Establish connection to the RF627 device by Service Protocol.
            bool result = false;
            result = save_params_to_scanner(
                        (scanner_base_t*)scanner_base, 300, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

std::shared_ptr<param> rf627old::get_param(std::string param_name)
{
    parameter_t* p = get_parameter(
                (scanner_base_t*)this->scanner_base, param_name.c_str());

    if (p != nullptr)
    {
        std::shared_ptr<param> result = std::make_shared<param>(p);
        return result;
    }
    return nullptr;
}

parameter_t* create_parameter_from_type(std::string type)
{
    parameter_t* p = NULL;
    if (type == "uint32_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_uint32 = (value_uint32_t*)calloc(1, sizeof (value_uint32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT_PARAM_TYPE].c_str();
    }else if (type == "uint64_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_uint64 = (value_uint64_t*)calloc(1, sizeof (value_uint64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT64_PARAM_TYPE].c_str();
    }else if (type ==  "int32_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_int32 = (value_int32_t*)calloc(1, sizeof (value_int32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT_PARAM_TYPE].c_str();
    }else if (type ==  "int64_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_int64 = (value_int64_t*)calloc(1, sizeof (value_int64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT64_PARAM_TYPE].c_str();
    }else if (type ==  "float_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_flt = (value_flt_t*)calloc(1, sizeof (value_flt_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::FLOAT_PARAM_TYPE].c_str();
    }else if(type ==  "double_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_dbl = (value_dbl_t*)calloc(1, sizeof (value_dbl_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::DOUBLE_PARAM_TYPE].c_str();
    }else if (type ==  "u32_arr_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_uint32 = (array_uint32_t*)calloc(1, sizeof (array_uint32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  "u64_arr_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_uint64 = (array_uint64_t*)calloc(1, sizeof (array_uint64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT64_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  "i32_arr_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_int32 = (array_int32_t*)calloc(1, sizeof (array_int32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT32_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  "i64_arr_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_int64 = (array_int64_t*)calloc(1, sizeof (array_int64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT64_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  "flt_array_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_flt = (array_flt_t*)calloc(1, sizeof (array_flt_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::FLT_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  "dbl_array_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_dbl = (array_dbl_t*)calloc(1, sizeof (array_dbl_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::DBL_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  "string_t")
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_str = (value_str_t*)calloc(1, sizeof (value_str_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::STRING_PARAM_TYPE].c_str();
    }
    return p;
}

bool rf627old::set_param(std::shared_ptr<param> param)
{
    parameter_t* p = create_parameter_from_type(param->getType().c_str());
    if (p != NULL)
    {
        if (strlen(param->getName().c_str()) > 0)
        {
            p->base.name = (char*)calloc(strlen(param->getName().c_str()) + 1, sizeof(char));
            strcpy(p->base.name, param->getName().c_str());
        }
        if (strlen(param->getAccess().c_str()) > 0)
        {
            p->base.access = (char*)calloc(strlen(param->getAccess().c_str()) + 1, sizeof(char));
            strcpy(p->base.access, param->getAccess().c_str());
        }
        if (strlen(param->getUnits().c_str()) > 0)
        {
            p->base.units = (char*)calloc(strlen(param->getUnits().c_str()) + 1, sizeof(char));
            strcpy(p->base.units, param->getUnits().c_str());
        }

        if (param->getType() == "string_t")
        {
            std::string new_value = param->getValue<std::string>();
            delete[] p->val_str->value;
            p->val_str->value = new char[new_value.length() + 1];
            strcpy(p->val_str->value, new_value.c_str());
            p->base.size = new_value.length() + 1;
        }
        else if (param->getType() == "int32_t")
        {
            p->val_int32->value = param->getValue<int32_t>();
        }
        else if (param->getType() == "int64_t")
        {
            p->val_int64->value = param->getValue<int64_t>();
        }
        else if (param->getType() == "uint32_t")
        {
            p->val_uint32->value = param->getValue<uint32_t>();
        }
        else if (param->getType() == "uint64_t")
        {
            p->val_uint64->value = param->getValue<uint64_t>();
        }
        else if (param->getType() == "float_t")
        {
            p->val_flt->value = param->getValue<float>();
        }
        else if (param->getType() ==  "double_t")
        {
            p->val_dbl->value = param->getValue<double>();
        }
        else if (param->getType() ==  "u32_arr_t")
        {
            std::vector<uint32_t> v = param->getValue<std::vector<uint32_t>>();
            p->arr_uint32->value = (rfUint32*)calloc(v.size(), sizeof (rfUint32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint32);
        }
        else if (param->getType() ==  "i32_arr_t")
        {
            std::vector<int32_t> v = param->getValue<std::vector<int32_t>>();
            p->arr_int32->value = (rfInt32*)calloc(v.size(), sizeof (rfInt32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt32);
        }
        else if (param->getType() ==  "u64_arr_t")
        {
            std::vector<uint64_t> v = param->getValue<std::vector<uint64_t>>();
            p->arr_uint64->value = (rfUint64*)calloc(v.size(), sizeof (rfUint64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint64);
        }
        else if (param->getType() ==  "i64_arr_t")
        {
            std::vector<int64_t> v = param->getValue<std::vector<int64_t>>();
            p->arr_int64->value = (rfInt64*)calloc(v.size(), sizeof (rfInt64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt64);
        }
        else if (param->getType() ==  "flt_array_t")
        {
            std::vector<float> v = param->getValue<std::vector<float>>();
            p->arr_flt->value = (rfFloat*)calloc(v.size(), sizeof (rfFloat));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_flt->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfFloat);
        }
        else if (param->getType() ==  "dbl_array_t")
        {
            std::vector<double> v = param->getValue<std::vector<double>>();
            p->arr_dbl->value = (rfDouble*)calloc(v.size(), sizeof (rfDouble));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_dbl->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfDouble);
        }
        param_mutex.lock();
        set_parameter((scanner_base_t*)this->scanner_base, p);
        param_mutex.unlock();
        free_parameter(p, ((scanner_base_t*)this->scanner_base)->type);
        return true;
    }
    return false;
}

bool rf627old::set_param_by_key(std::string name, std::string key)
{
    auto _param = this->get_param(name);
    _param->setValue(_param->getEnum<uint32_t>().getValue(key));
    return set_param(std::move(_param));
}


bool rf627old::send_cmd(std::string command_name,
                        std::vector<uint8_t> input, std::vector<uint8_t>& output)
{


    command2_t cmd = {0};
    const char* command_name_c = command_name.c_str();
    cmd.name = command_name_c;
    cmd.input.size = input.size();
    cmd.input.payload = (rfUint8*)input.data();
    bool result = send_command2((scanner_base_t*)this->scanner_base, &cmd);

    for (int i = 0; i < cmd.output.size; i++)
        output.push_back(((uint8_t*)cmd.output.payload)[i]);

    free(cmd.output.payload);

    return result;
}

bool rf627old::reboot_device(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result = false;
            result = send_reboot_device_request_to_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627old::is_connected()
{
    return _is_connected;
}

bool rf627old::is_available()
{
    return _is_exist;
}

//
// RF627
// smart version (v2.x.x)
//
std::vector<std::shared_ptr<rf627smart>> rf627smart::search(uint32_t timeout, bool only_available_result, PROTOCOLS protocol)
{
    if (!is_initialized)
        throw std::runtime_error("first you should initialize SDK - sdk_init()");

    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        get_search_mutex().lock();
        // Cleaning detected network adapter.
        FreeAdapterAddresses();
        // Retrieving addresses associated with adapters on the local computer.
        EnumAdapterAddresses();

        //Create value for scanners vector's type
        vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));

        //Initialization vector
        vector_init(&scanners);


        static std::vector<std::shared_ptr<rf627smart>> result;
        if (only_available_result && result.size() > 0)
        {
            auto it = std::find_if(result.begin(), result.end(), [](const std::shared_ptr<rf627smart> obj){
                return obj->_is_connected == false && obj->_is_exist == false;
            });

            while (it != std::end(result))
            {
                int index = std::distance(result.begin(), it);
                result.erase(std::remove(result.begin(), result.end(), result[index]), result.end());
                if (result.size() == 0)
                    break;
                it = std::find_if(std::next(it), result.end(), [](const std::shared_ptr<rf627smart> obj){
                    return obj->_is_connected == false && obj->_is_exist == false;
                });
            }
        }

        // Iterate over all available network adapters in the current operating
        // system to send "Hello" requests.
        uint32_t count = 0;
        for (int i=0; i<GetAdaptersCount(); i++)
        {
            uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
            uint32_t host_mask = ntohl(inet_addr(GetAdapterMasks(i)));
            // call the function to change adapter settings inside the library.
            set_platform_adapter_settings(host_mask, host_ip_addr);

            // Search for RF627-Smart devices over network by Service Protocol.
            if (host_ip_addr != 0)
            {
#ifdef NDEBUG
                search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);
                count = (int)vector_count(scanners);
#else
                // Get another IP Addr and set this changes in adapter settings.
                printf("Search scanners from:\n "
                       "* IP Address\t: %s\n "
                       "* Netmask\t: %s\n",
                       GetAdapterAddress(i), GetAdapterMasks(i));
                search_scanners(scanners, kRF627_SMART, timeout, kSERVICE);

                // Print count of discovered rf627-smart in network by Service Protocol
                printf("Discovered\t: %d RF627-Smart\n",(int)vector_count(scanners)-count);
                printf("-----------------------------------------\n");
                count = (int)vector_count(scanners);
#endif

            }
        }

        std::vector<std::shared_ptr<rf627smart>> available_result;

        std::vector<int> non_exist_index = std::vector<int>();
        for (size_t i = 0; i < result.size(); i++)
        {
            non_exist_index.push_back(i);
        }
        //Iterate over all discovered rf627-smart in network and push into list.
        for(size_t i = 0; i < vector_count(scanners); i++)
        {
            scanner_base_t* scanner = (scanner_base_t*)vector_get(scanners,i);
            auto it = std::find_if(result.begin(), result.end(), [scanner](const std::shared_ptr<rf627smart> obj){
               return scanner->rf627_smart->info_by_service_protocol.fact_general_serial == obj->get_info()->serial_number();
            });

            if (it == std::end(result))
            {
                result.push_back(std::shared_ptr<rf627smart>(std::make_shared<rf627smart>((void*)vector_get(scanners,i))));
                result[result.size() - 1]->current_protocol = PROTOCOLS::SERVICE;
            }else
            {
                int index = std::distance(result.begin(), it);
                result[index]->_is_exist = true;
                non_exist_index.erase(std::remove(non_exist_index.begin(), non_exist_index.end(), index), non_exist_index.end());
            }
        }

        for (size_t i = 0; i < non_exist_index.size(); i++)
        {
            result[non_exist_index[i]]->_is_exist = false;
        }

        if (only_available_result)
        {
            for (size_t i = 0; i < result.size(); i++)
                if (result[i]->_is_exist)
                    available_result.push_back(result[i]);
            get_search_mutex().unlock();
            return available_result;
        }

        get_search_mutex().unlock();
        return result;
        break;
    }
    default:
    {
        std::vector<std::shared_ptr<rf627smart>> result;
        return result;
        break;
    }
    }

}

std::shared_ptr<rf627smart> rf627smart::search(
        std::string scanner_ip, std::string host_ip, std::string mask, uint32_t timeout)
{
    get_search_mutex().lock();
    // Cleaning detected network adapter.
    FreeAdapterAddresses();
    // Retrieving addresses associated with adapters on the local computer.
    EnumAdapterAddresses();

    //Create value for scanners vector's type
    vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));

    //Initialization vector
    vector_init(&scanners);


    // Iterate over all available network adapters in the current operating
    // system to send "Hello" requests.
    uint32_t count = 0;
    {
        uint32_t host_ip_addr = ntohl(inet_addr(host_ip.c_str()));
        uint32_t host_mask = ntohl(inet_addr(mask.c_str()));
        // call the function to change adapter settings inside the library.
        set_platform_adapter_settings(host_mask, host_ip_addr);

        // Search for RF627-Smart devices over network by Service Protocol.
        if (host_ip_addr != 0)
        {
            // Get another IP Addr and set this changes in adapter settings.
            printf("Search scanners from:\n "
                   "* IP Address\t: %s\n "
                   "* Netmask\t: %s\n",
                   host_ip.c_str(), mask.c_str());
            search_scanners_by_ip(scanners, kRF627_SMART, (char*)scanner_ip.c_str(), timeout, kSERVICE);

            // Print count of discovered rf627-smart in network by Service Protocol
            printf("Discovered\t: %d RF627-Smart\n",(int)vector_count(scanners)-count);
            printf("-----------------------------------------\n");
            count = (int)vector_count(scanners);
        }
    }

    static std::vector<std::shared_ptr<rf627smart>> result;
    bool only_available_result = true;
    if (only_available_result)
    {
        auto it = std::find_if(result.begin(), result.end(), [](const std::shared_ptr<rf627smart> obj){
            return obj->_is_connected == false && obj->_is_exist == false;
        });

        while (it != std::end(result))
        {
            int index = std::distance(result.begin(), it);
            result.erase(std::remove(result.begin(), result.end(), result[index]), result.end());
            it = std::find_if(std::next(it), result.end(), [](const std::shared_ptr<rf627smart> obj){
                return obj->_is_connected == false && obj->_is_exist == false;
            });
        }
    }

    std::vector<std::shared_ptr<rf627smart>> available_result;

    std::vector<int> non_exist_index = std::vector<int>();
    for (size_t i = 0; i < result.size(); i++)
    {
        non_exist_index.push_back(i);
    }
    //Iterate over all discovered rf627-smart in network and push into list.
    for(size_t i = 0; i < vector_count(scanners); i++)
    {
        scanner_base_t* scanner = (scanner_base_t*)vector_get(scanners,i);
        auto it = std::find_if(result.begin(), result.end(), [scanner](const std::shared_ptr<rf627smart> obj){
           return scanner->rf627_smart->info_by_service_protocol.fact_general_serial == obj->get_info()->serial_number();
        });

        if (it == std::end(result))
        {
            result.push_back(std::shared_ptr<rf627smart>(std::make_shared<rf627smart>((void*)vector_get(scanners,i))));
            result[result.size() - 1]->current_protocol = PROTOCOLS::SERVICE;
        }else
        {
            int index = std::distance(result.begin(), it);
            result[index]->_is_exist = true;
            non_exist_index.erase(std::remove(non_exist_index.begin(), non_exist_index.end(), index), non_exist_index.end());
        }
    }

    for (size_t i = 0; i < non_exist_index.size(); i++)
    {
        result[non_exist_index[i]]->_is_exist = false;
    }

    if (only_available_result)
    {
        for (size_t i = 0; i < result.size(); i++)
            if (result[i]->_is_exist)
                available_result.push_back(result[i]);
        get_search_mutex().unlock();
        auto it = std::find_if(available_result.begin(), available_result.end(),
                               [&scanner_ip](const std::shared_ptr<rf627smart>& obj) {
            return obj->get_info()->ip_address() == scanner_ip;
        });
        if (it != std::end(available_result))
        {
            int index = std::distance(available_result.begin(), it);
            return available_result[index];
        }
        return nullptr;
    }

    get_search_mutex().unlock();
    return nullptr;
}

std::shared_ptr<hello_info> rf627smart::get_info(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        hello_information info = get_info_about_scanner(((scanner_base_t*)this->scanner_base), kSERVICE);

        std::shared_ptr<hello_info> _hello_info(new hello_info(info.rf627smart.hello_info_service_protocol, SCANNER_TYPES::RF627_SMART, PROTOCOLS::SERVICE));

        return _hello_info;
        break;
    }
    default:
        break;
    }

    return nullptr;
}

rf627smart::rf627smart(void* base)
{
    this->scanner_base = base;
    _is_connected = false;
    _is_exist = true;
}

std::mutex& rf627smart::get_search_mutex()
{
    static std::mutex mutex_;
    return mutex_;
}

rf627smart::~rf627smart()
{
    free_scanner(((scanner_base_t*)this->scanner_base));
}

bool rf627smart::is_connected()
{
    return _is_connected;
}

bool rf627smart::is_available()
{
    return _is_exist;
}

bool rf627smart::connect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        connect_mutex.lock();
        bool result = false;
        if (_is_connected == false)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = connect_to_scanner(
                        ((scanner_base_t*)this->scanner_base), kSERVICE);
            _is_connected = result;
            if (_is_connected)
                read_params();
        }else
        {
            result = _is_connected;
        }
        connect_mutex.unlock();

        return result;
        break;
    }
    default:
        break;
    }

    return false;

}

bool rf627smart::check_connection(uint32_t timeout, PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        bool result = false;
        connect_mutex.lock();
        if (_is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = check_connection_to_scanner(
                        ((scanner_base_t*)this->scanner_base), timeout, kSERVICE);
            _is_exist = result;
        }else
        {
            result = _is_connected;
        }
        connect_mutex.unlock();

        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

bool rf627smart::disconnect(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        bool result = false;
        connect_mutex.lock();
        if (_is_connected)
        {
            _is_connected = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            // Establish connection to the RF627 device by Service Protocol.
            result = disconnect_from_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            if (result)
                _is_connected = FALSE;
            else
                _is_connected = TRUE;
        }else
        {
            result = TRUE;
            _is_connected = FALSE;
        }
        connect_mutex.unlock();
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

std::shared_ptr<profile2D> rf627smart::get_profile2D(
        bool zero_points, bool realtime,
        PROTOCOLS protocol)
{

    profile_mutex.lock();

    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Get profile from scanner's data stream by Service Protocol.
            rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                            (scanner_base_t*)scanner_base, zero_points, realtime, kSERVICE);

            if (profile_from_scanner->rf627smart_profile2D != nullptr)
            {
                std::shared_ptr<profile2D> result(new profile2D(profile_from_scanner));
                profile_mutex.unlock();
                return result;
            }else
            {
                free_profile2D(profile_from_scanner);
            }
            break;

        }
        default:
            break;
        }
    }
    profile_mutex.unlock();
    return nullptr;

}

std::shared_ptr<frame> rf627smart::get_frame(
        bool confirm_enabled, uint32_t waiting_time)
{
    if (_is_connected)
    {
        // Establish connection to the RF627 device by Service Protocol.
        rf627_frame_t* _frame = get_frame_from_scanner(
                    (scanner_base_t*)scanner_base, confirm_enabled, waiting_time, kSERVICE);
        if (_frame != nullptr)
        {
            if (_frame->rf627smart_frame != nullptr)
            {
                if (_frame->rf627smart_frame->fact_sensor_width == 0)
                {
                    std::shared_ptr<param> width = get_param("fact_sensor_width");
                    if (width != NULL)
                    {
                        _frame->rf627smart_frame->fact_sensor_width = width->getValue<uint32_t>();
                    }
                }
                if (_frame->rf627smart_frame->fact_sensor_height == 0)
                {
                    std::shared_ptr<param> height = get_param("fact_sensor_height");

                    if (height != NULL)
                    {
                        _frame->rf627smart_frame->fact_sensor_height =
                                height->getValue<uint32_t>();
                    }
                }

                if (_frame->rf627smart_frame->frame_width == 0)
                {
                    _frame->rf627smart_frame->frame_width =
                            _frame->rf627smart_frame->fact_sensor_width;
                }

                if (_frame->rf627smart_frame->frame_height == 0)
                {
                    _frame->rf627smart_frame->frame_height =
                            _frame->rf627smart_frame->user_roi_enabled ?
                                _frame->rf627smart_frame->user_roi_size :
                                _frame->rf627smart_frame->fact_sensor_height;
                }

                if (_frame->rf627smart_frame->data_size ==
                        (_frame->rf627smart_frame->frame_width *
                        _frame->rf627smart_frame->frame_height))
                {
                    _frame->rf627smart_frame->pixel_size = 1;
                }

                if (_frame->rf627smart_frame->pixel_size == 1)
                {
                    std::shared_ptr<frame> result = std::make_shared<frame>(_frame);
                    return result;
                }
                else
                {
                    if(_frame->rf627smart_frame->data != nullptr)
                        free(_frame->rf627smart_frame->data);
                    free(_frame->rf627smart_frame);
                }
            }
            free(_frame);
        }
    }

    return nullptr;
}

bool rf627smart::read_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            bool result = false;
            param_mutex.lock();
            result = read_params_from_scanner(
                        (scanner_base_t*)scanner_base, 300, kSERVICE);
            param_mutex.unlock();
            return result;
            break;
        }
        default:
            break;
        }
    }
    return false;
}

bool rf627smart::write_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            bool result = false;
            param_mutex.lock();
            result = write_params_to_scanner(
                        (scanner_base_t*)scanner_base, 300, kSERVICE);
            param_mutex.unlock();
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::save_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Establish connection to the RF627 device by Service Protocol.
            bool result = false;
            result = save_params_to_scanner(
                        (scanner_base_t*)scanner_base, 2000, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::load_recovery_params(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            bool result = false;
            result = load_recovery_params_from_scanner(
                        (scanner_base_t*)scanner_base, 300, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

std::shared_ptr<param> rf627smart::get_param(std::string param_name)
{
    param_mutex.lock();
    parameter_t* p = get_parameter(
                (scanner_base_t*)this->scanner_base, param_name.c_str());
    if (p != nullptr)
    {
        std::shared_ptr<param> result = std::make_shared<param>(p);
        param_mutex.unlock();
        return result;
    }
    param_mutex.unlock();
    return nullptr;
}

bool rf627smart::set_param(std::shared_ptr<param> param)
{
    parameter_t* p = create_parameter_from_type(param->getType().c_str());
    if (p != NULL)
    {
        if (strlen(param->getName().c_str()) > 0)
        {
            p->base.name = (char*)calloc(strlen(param->getName().c_str()) + 1, sizeof(char));
            strcpy(p->base.name, param->getName().c_str());
        }
        if (strlen(param->getAccess().c_str()) > 0)
        {
            p->base.access = (char*)calloc(strlen(param->getAccess().c_str()) + 1, sizeof(char));
            strcpy(p->base.access, param->getAccess().c_str());
        }
        if (strlen(param->getUnits().c_str()) > 0)
        {
            p->base.units = (char*)calloc(strlen(param->getUnits().c_str()) + 1, sizeof(char));
            strcpy(p->base.units, param->getUnits().c_str());
        }

        if (param->getType() == "string_t")
        {
            std::string new_value = param->getValue<std::string>();
            delete[] p->val_str->value;
            p->val_str->value = new char[new_value.length() + 1];
            strcpy(p->val_str->value, new_value.c_str());
            p->base.size = new_value.length() + 1;
        }
        else if (param->getType() == "int32_t")
        {
            p->val_int32->value = param->getValue<int32_t>();
        }
        else if (param->getType() == "int64_t")
        {
            p->val_int64->value = param->getValue<int64_t>();
        }
        else if (param->getType() == "uint32_t")
        {
            p->val_uint32->value = param->getValue<uint32_t>();
        }
        else if (param->getType() == "uint64_t")
        {
            p->val_uint64->value = param->getValue<uint64_t>();
        }
        else if (param->getType() == "float_t")
        {
            p->val_flt->value = param->getValue<float>();
        }
        else if (param->getType() ==  "double_t")
        {
            p->val_dbl->value = param->getValue<double>();
        }
        else if (param->getType() ==  "u32_arr_t")
        {
            std::vector<uint32_t> v = param->getValue<std::vector<uint32_t>>();
            p->arr_uint32->value = (rfUint32*)calloc(v.size(), sizeof (rfUint32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint32);
        }
        else if (param->getType() ==  "i32_arr_t")
        {
            std::vector<int32_t> v = param->getValue<std::vector<int32_t>>();
            p->arr_int32->value = (rfInt32*)calloc(v.size(), sizeof (rfInt32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt32);
        }
        else if (param->getType() ==  "u64_arr_t")
        {
            std::vector<uint64_t> v = param->getValue<std::vector<uint64_t>>();
            p->arr_uint64->value = (rfUint64*)calloc(v.size(), sizeof (rfUint64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint64);
        }
        else if (param->getType() ==  "i64_arr_t")
        {
            std::vector<int64_t> v = param->getValue<std::vector<int64_t>>();
            p->arr_int64->value = (rfInt64*)calloc(v.size(), sizeof (rfInt64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt64);
        }
        else if (param->getType() ==  "flt_array_t")
        {
            std::vector<float> v = param->getValue<std::vector<float>>();
            p->arr_flt->value = (rfFloat*)calloc(v.size(), sizeof (rfFloat));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_flt->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfFloat);
        }
        else if (param->getType() ==  "dbl_array_t")
        {
            std::vector<double> v = param->getValue<std::vector<double>>();
            p->arr_dbl->value = (rfDouble*)calloc(v.size(), sizeof (rfDouble));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_dbl->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfDouble);
        }
        param_mutex.lock();
        set_parameter((scanner_base_t*)this->scanner_base, p);
        param_mutex.unlock();
        free_parameter(p, ((scanner_base_t*)this->scanner_base)->type);
        return true;
    }
    return false;
}

bool rf627smart::set_param_by_key(std::string name, std::string key)
{
    auto _param = this->get_param(name);
    _param->setValue(_param->getEnum<uint32_t>().getValue(key));
    return set_param(std::move(_param));
}

bool rf627smart::start_dump_recording(uint32_t count_of_profiles)
{
    if (_is_connected)
    {
        // Get parameter of user_dump_capacity
        std::shared_ptr<param> user_dump_capacity = get_param("user_dump_capacity");
        if (user_dump_capacity !=nullptr && user_dump_capacity->getType()=="uint32_t")
        {
            user_dump_capacity->setValue<uint32_t>(count_of_profiles);
            set_param(user_dump_capacity);
        }else
        {
            return false;
        }

        // Get parameter of user_dump_enabled
        std::shared_ptr<param> user_dump_enabled = get_param("user_dump_enabled");
        if (user_dump_enabled !=nullptr && user_dump_enabled->getType()=="uint32_t")
        {
            user_dump_enabled->setValue<uint32_t>(
                        user_dump_enabled->getEnum<uint32_t>().getValue("TRUE"));
            //        std::string s = user_dump_enabled->getEnum<uint32_t>().getLabel("TRUE");
            set_param(user_dump_enabled);
        }else
        {
            return false;
        }

        // Write changes parameters to the device's memory
        if(write_params())
            return true;
        else
            return false;
    }
    return false;
}

bool rf627smart::stop_dump_recording(uint32_t &count_of_profiles)
{
    if (_is_connected)
    {
        // Get parameter of user_dump_enabled
        std::shared_ptr<param> user_dump_enabled = get_param("user_dump_enabled");
        if (user_dump_enabled !=nullptr && user_dump_enabled->getType()=="uint32_t")
        {
            user_dump_enabled->setValue<uint32_t>(
                        user_dump_enabled->getEnum<uint32_t>().getValue("FALSE"));
            set_param(user_dump_enabled);
        }else
        {
            return false;
        }

        // Write changes parameters to the device's memory
        if(!write_params())
            return false;

        // Get parameter of user_dump_size
        std::shared_ptr<param> user_dump_size = get_param("user_dump_size");
        if (user_dump_size !=nullptr && user_dump_enabled->getType()=="uint32_t")
        {
            count_of_profiles = user_dump_enabled->getValue<uint32_t>();
        }else
        {
            return false;
        }
    }

    return true;
}

std::vector<std::shared_ptr<profile2D>> rf627smart::get_dumps_profiles(
        uint32_t index, uint32_t count, uint32_t timeout)
{
    std::vector<std::shared_ptr<profile2D>> result;
    if (_is_connected)
    {
        // Get parameter of fact_dump_unitSize
        std::shared_ptr<param> fact_dump_unitSize = get_param("fact_dump_unitSize");
        if (fact_dump_unitSize !=nullptr && fact_dump_unitSize->getType()=="uint32_t")
        {
            rf627_profile2D_t** dumps =
                    (rf627_profile2D_t**)calloc(count, sizeof (rf627_profile2D_t*));
            uint32_t dump_size = 0;
            uint8_t status = get_dumps_profiles_from_scanner(
                        (scanner_base_t*)scanner_base, index, count, timeout, kSERVICE,
                        dumps, &dump_size, fact_dump_unitSize->getValue<uint32_t>());
            if (status)
            {
                for(uint32_t i = 0; i < dump_size; i++)
                {
                    if (dumps[i]->rf627smart_profile2D != nullptr)
                    {
                        result.emplace_back(new profile2D(dumps[i]));
                    }else
                    {
                        throw ("get_dumps_profiles dump_size exception");
                    }
                }
                free(dumps);
            }
            return result;
        }else
        {
            return result;
        }
    }

    return result;
}

bool rf627smart::start_profile_capturing(uint32_t count_of_profiles)
{
    if (_is_connected)
    {
        return send_profile2D_request_to_scanner(
                    (scanner_base_t*)scanner_base, count_of_profiles, kSERVICE);
    }
    return false;
}

bool rf627smart::get_authorization_token(std::string& token, PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Establish connection to the RF627 device by Service Protocol.
            bool result = false;
            char* c_token = nullptr;
            uint32_t token_size = 0;
            result = get_authorization_token_from_scanner(
                        (scanner_base_t*)scanner_base, &c_token, &token_size, 1000, kSERVICE);
            if (c_token != nullptr)
            {
                int size = strlen(c_token);
                token = c_token;
                free(c_token); c_token = NULL;
            }
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::set_authorization_key(std::string key, PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result = false;
            char* c_key = (char*)key.c_str();
            uint32_t size = key.size();
            result = set_authorization_key_to_scanner(
                        (scanner_base_t*)scanner_base, c_key, size, 3000, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::create_calibration_table()
{
    if (_is_connected)
    {
        return create_calibration_table_for_scanner((scanner_base_t*)scanner_base, 3000);
    }
    return false;
}

std::shared_ptr<calib_table> rf627smart::get_calibration_table()
{
    if (_is_connected)
    {
        // Set authorization key to the RF627 device by Service Protocol.
        rf627_calib_table_t* result;
        result = get_calibration_table_from_scanner(
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        if (result != nullptr)
        {
            std::shared_ptr<calib_table> table = std::make_shared<calib_table>(result);
            return table;
        }else
        {
            return nullptr;
        }
    }

    return nullptr;
}
bool rf627smart::set_calibration_table(std::shared_ptr<calib_table> table)
{
    if (_is_connected)
    {
        bool result = false;

        rf627_calib_table_t* _table = (rf627_calib_table_t*)calloc(1, sizeof (rf627_calib_table_t));
        _table->type = kRF627_SMART;

        _table->rf627smart_calib_table = (rf627_smart_calib_table_t*)calloc(1, sizeof (rf627_smart_calib_table_t));

        _table->rf627smart_calib_table->m_Type = table.get()->getType();
        _table->rf627smart_calib_table->m_CRC16 = table.get()->getCRC16();
        _table->rf627smart_calib_table->m_Serial = table.get()->getSerial();
        _table->rf627smart_calib_table->m_DataRowLength = table.get()->getDataRowLength();
        _table->rf627smart_calib_table->m_Width = table.get()->getWidth();
        _table->rf627smart_calib_table->m_Height = table.get()->getHeight();
        _table->rf627smart_calib_table->m_MultW = table.get()->getMultWidth();
        _table->rf627smart_calib_table->m_MultH = table.get()->getMultHeight();
        _table->rf627smart_calib_table->m_TimeStamp = table.get()->getTimeStamp();

        _table->rf627smart_calib_table->m_DataSize = table.get()->getData().size();
        _table->rf627smart_calib_table->m_Data = (unsigned char*)calloc(_table->rf627smart_calib_table->m_DataSize, sizeof (uint8_t));
        memcpy(_table->rf627smart_calib_table->m_Data, table.get()->getData().data(), _table->rf627smart_calib_table->m_DataSize * sizeof (uint8_t));

        result = set_calibration_table_to_scanner(
                    (scanner_base_t*)scanner_base, _table, 3000, kSERVICE);

        if (_table->rf627smart_calib_table->m_DataSize > 0)
            free(_table->rf627smart_calib_table->m_Data);
        free (_table->rf627smart_calib_table);
        free(_table);

        return result;
    }

    return false;
}

bool rf627smart::create_approximation_table()
{
    if (_is_connected)
    {
        return create_approximation_table_for_scanner((scanner_base_t*)scanner_base);
    }
    return false;
}

bool rf627smart::read_approximation_table()
{
    if (_is_connected)
    {
        return read_approximation_table_from_scanner(
                    (scanner_base_t*)scanner_base, 3000);
    }
    return false;
}

bool rf627smart::write_approximation_table()
{
    if (_is_connected)
    {
        return write_approximation_table_to_scanner(
                    (scanner_base_t*)scanner_base, 1000);;
    }

    return false;
}

bool rf627smart::save_approximation_table()
{
    if (_is_connected)
    {
        return save_approximation_table_to_scanner(
                    (scanner_base_t*)scanner_base, 1000 * 120);
    }
    return false;
}

std::shared_ptr<ApproxTable> rf627smart::get_approximation_table()
{
    if (_is_connected)
    {
        // Set authorization key to the RF627 device by Service Protocol.
        rf627_approx_table_t* result = get_approximation_table_from_scanner(
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        if (result != nullptr)
        {
            switch (result->version) {
            case 6:
            {
                std::shared_ptr<ApproxTable> table = std::make_shared<ApproxTable_v6>(result);
                return table;
            }
            default:
                return nullptr;
            }
        }else
        {
            return nullptr;
        }
    }

    return nullptr;
}

bool rf627smart::set_approximation_table(std::shared_ptr<ApproxTable> table)
{
    if (_is_connected && table != nullptr)
    {
        bool result = false;

        if (table->getVersion() == "6"){
            rf627_approx_table_t* _table = (rf627_approx_table_t*)calloc(1, sizeof (rf627_approx_table_t));
            _table->version = 6;

            table->convertToBase(_table);

            result = set_approximation_table_to_scanner(
                        (scanner_base_t*)scanner_base, _table, 3000);

            table->clearBase(_table);
            free(_table);

        }

        return result;
    }

    return false;
}

bool rf627smart::reboot_device(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result = false;
            result = send_reboot_device_request_to_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::reboot_sensor(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result = false;
            result = send_reboot_sensor_request_to_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::send_to_periphery(std::string iface_name, std::vector<uint8_t> in)
{
    if (_is_connected)
    {
        bool result = false;

        char* out_data = nullptr;
        uint32_t out_data_size = 0;
        result = send_data_to_scanner_periphery(
                    (scanner_base_t*)scanner_base, iface_name.c_str(), 0,
                    (char*)in.data(), (uint32_t)in.size(), &out_data, &out_data_size);

        if (out_data_size > 0)
        {
            free(out_data);
        }

        return result;
    }

    return false;
}

bool rf627smart::send_to_periphery(
        std::string iface_name, std::vector<uint8_t> in,
        std::vector<uint8_t> &out, uint32_t timeout)
{
    if (_is_connected)
    {
        bool result = false;

        char* out_data = nullptr;
        uint32_t out_data_size = 0;
        result = send_data_to_scanner_periphery(
                    (scanner_base_t*)scanner_base, iface_name.c_str(), timeout,
                    (char*)in.data(), (uint32_t)in.size(), &out_data, &out_data_size);

        if (out_data_size > 0)
        {
            out.clear();
            for(uint32_t i = 0; i < out_data_size; i++)
                out.push_back(out_data[i]);

            free(out_data);
        }

        return result;
    }

    return false;
}

bool rf627smart::receive_from_periphery(
        std::string iface_name, uint16_t count,
        std::vector<uint8_t> &out, uint32_t timeout)
{
    if (_is_connected)
    {
        bool result = false;

        char* out_data = nullptr;
        uint32_t out_data_size = 0;
        result = receive_data_from_scanner_periphery(
                    (scanner_base_t*)scanner_base, iface_name.c_str(), timeout,
                    count, &out_data, &out_data_size);

        out.clear();
        if (out_data_size > 0)
        {
            out.clear();
            for(uint32_t i = 0; i < out_data_size; i++)
                out.push_back(out_data[i]);

            free(out_data);
        }

        return result;
    }

    return false;
}

bool rf627smart::send_custom_command(
        std::string cmd_name, std::vector<unsigned char> &out,
        std::string data_type, std::vector<unsigned char> in)
{
    if (_is_connected)
    {
        bool result = false;

        char* out_data = nullptr;
        uint32_t out_data_size = 0;
        result = send_custom_command_to_scanner(
                    (scanner_base_t*)scanner_base, cmd_name.c_str(), data_type.c_str(),
                    (char*)in.data(), (uint32_t)in.size(), &out_data, &out_data_size);

        if (out_data_size > 0)
        {
            out.resize(out_data_size);
            for(uint32_t i = 0; i < out_data_size; i++)
                out[i] = (out_data[i]);

            free(out_data);
        }

        return result;
    }
    return false;
}

bool rf627smart::add_protocol_settings(
        std::string cmd_name,
        bool crc_enabled, bool confirm_enabled, bool one_answ,
        uint32_t waiting_time, uint32_t resends_count)
{
    return add_protocol_settings_for_cmd((scanner_base_t*)scanner_base,
                (const char *)cmd_name.c_str(), crc_enabled, confirm_enabled, one_answ,
                                         waiting_time, resends_count);
}

bool rf627smart::remove_protocol_settings(std::string cmd_name)
{
    return remove_protocol_settings_for_cmd(
                (scanner_base_t*)scanner_base, (const char *)cmd_name.c_str());
}

bool rf627smart::get_firmware(std::vector<uint8_t> &firmware, uint32_t timeout)
{
    if (_is_connected)
    {
        bool result = false;

        char* out_data = nullptr;
        uint32_t out_data_size = 0;
        result = receive_firmware_from_scanner(
                    (scanner_base_t*)scanner_base, timeout, &out_data, &out_data_size);

        if (out_data_size > 0)
        {
            firmware.clear();
            firmware.reserve(out_data_size);
            for(uint32_t i = 0; i < out_data_size; i++)
                firmware.push_back(out_data[i]);

            free(out_data);
        }

        return result;
    }

    return false;
}


bool rf627smart::read_calibration_table(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result;
            result = read_calibration_table_from_scanner(
                        (scanner_base_t*)scanner_base, 3000, kSERVICE);
            return true;
            break;
        }
        default:
            break;
        }
    }
    return false;
}

bool rf627smart::write_calibration_table(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result = false;
            result = write_calibration_table_to_scanner(
                        (scanner_base_t*)scanner_base, 1000, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }

    return false;
}

bool rf627smart::save_calibration_table(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    if (_is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Set authorization key to the RF627 device by Service Protocol.
            bool result = false;
            result = save_calibration_table_to_scanner(
                        (scanner_base_t*)scanner_base, 1000 * 120, kSERVICE);
            return result;
            break;
        }
        default:
            break;
        }
    }
    return false;
}







void sdk_cleanup()
{
    if (is_initialized)
    {
        is_initialized = false;
        SDK::CORES::RF62X::cleanup();
    }else
    {
        throw std::runtime_error("first you should initialize SDK - sdk_init()");
    }
}

template class ValueEnum<uint32_t>;
template class ValueEnum<uint64_t>;
template class ValueEnum<int32_t>;
template class ValueEnum<int64_t>;
template class ValueEnum<float>;
template class ValueEnum<double>;

template class ValueEnum<std::vector<uint32_t>>;
template class ValueEnum<std::vector<uint64_t>>;
template class ValueEnum<std::vector<int32_t>>;
template class ValueEnum<std::vector<int64_t>>;
template class ValueEnum<std::vector<float>>;
template class ValueEnum<std::vector<double>>;

template class ValueEnum<std::string>;

}
}
}


