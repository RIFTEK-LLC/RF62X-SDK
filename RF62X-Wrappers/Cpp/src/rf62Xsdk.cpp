#include "rf62Xsdk.h"
#include "rf62Xtypes.h"
#include "rf62Xcore.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iterator>
#include <algorithm>

extern "C"{
#include <rf62X_sdk.h>
#include <netwok_platform.h>
#include <utils.h>
}






#ifdef _WIN32
#include <winsock.h>
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
extern const char* GetAdapterMasks(int index);
/* windows sockets tweaks */
extern BOOL WinSockInit();
extern void WinSockDeinit();


std::string SDK::SCANNERS::RF62X::sdk_version()
{
    /*
     * Get rf627 core version
     */
    return SDK::CORES::RF62X::version();
}

bool SDK::SCANNERS::RF62X::sdk_init()
{   
    return SDK::CORES::RF62X::init();
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
        }
        case kRF627_SMART:
        {
            m_Data = _frame->rf627smart_frame->data;
            m_DataSize = _frame->rf627smart_frame->data_size;
            m_PixelSize = _frame->rf627smart_frame->pixel_size;
            m_FrameWidth = _frame->rf627smart_frame->width;
            m_FrameHeight = _frame->rf627smart_frame->height;

            m_RoiActive = _frame->rf627smart_frame->user_roi_active;
            m_RoiEnabled = _frame->rf627smart_frame->user_roi_enabled;
            m_RoiPos = _frame->rf627smart_frame->user_roi_pos;
            m_RoiSize = _frame->rf627smart_frame->user_roi_size;
        }
        }
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
            break;
        }
        case kRF627_SMART:
        {
            if(_frame->rf627smart_frame->data != nullptr)
                free(_frame->rf627smart_frame->data);
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

    return std::make_shared<calib_table>(_table);
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

bool calib_table::setX(std::vector<int16_t> Xd)
{

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
bool calib_table::setZX(std::vector<int16_t> Zd, std::vector<int16_t> Xd)
{
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
    if(type == parameter_value_types[PVT_UINT])
    {
        p = new value_uint32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_UINT64])
    {
        p = new value_uint64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_INT])
    {
        p = new value_int32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_INT64])
    {
        p = new value_int64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_FLOAT])
    {
        p = new value_flt();
        p->type = type;
    }else if(type == parameter_value_types[PVT_DOUBLE])
    {
        p = new value_dbl();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_UINT32])
    {
        p = new array_uint32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_UINT64])
    {
        p = new array_uint64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_INT32])
    {
        p = new array_int32();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_INT64])
    {
        p = new array_int64();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_FLT])
    {
        p = new array_flt();
        p->type = type;
    }else if(type == parameter_value_types[PVT_ARRAY_DBL])
    {
        p = new array_dbl();
        p->type = type;
    }else if(type == parameter_value_types[PVT_STRING])
    {
        p = new value_str();
        p->type = type;
    }
    return p;
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

template<typename T>
ValueEnum<T>::ValueEnum(std::vector<std::tuple<T, std::string, std::string>> enum_base)
{
    _enum_base = enum_base;
}

template <typename T>
ValueEnum<T>::~ValueEnum()
{

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
T ValueEnum<T>::getValue(uint32_t index) const
{
    if (_enum_base.size() < index)
    {
        return std::get<0>(_enum_base[index]);
    }else
    {
        throw "No enum item at the specified index";
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
std::string ValueEnum<T>::getLabel(uint32_t index) const
{
    if (_enum_base.size() < index)
    {
        return std::get<2>(_enum_base[index]);
    }else
    {
        throw "No enum item at the specified index";
    }
}

template <typename T>
std::string ValueEnum<T>::getKey(uint32_t index) const
{
    if (_enum_base.size() < index)
    {
        return std::get<1>(_enum_base[index]);
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
    if (_enum_base.size() < index)
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

        if (result->type == parameter_value_types[PVT_UINT])
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
        else if (result->type == parameter_value_types[PVT_UINT64])
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
        else if (result->type == parameter_value_types[PVT_INT])
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
        else if (result->type == parameter_value_types[PVT_INT64])
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
        else if (result->type == parameter_value_types[PVT_FLOAT])
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
        else if (result->type == parameter_value_types[PVT_DOUBLE])
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
        else if (result->type == parameter_value_types[PVT_ARRAY_UINT32])
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
        else if (result->type == parameter_value_types[PVT_ARRAY_UINT64])
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
        else if (result->type == parameter_value_types[PVT_ARRAY_INT32])
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
        else if (result->type == parameter_value_types[PVT_ARRAY_INT64])
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
        else if (result->type == parameter_value_types[PVT_ARRAY_FLT])
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
        else if (result->type == parameter_value_types[PVT_ARRAY_DBL])
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
        else if (result->type == parameter_value_types[PVT_STRING])
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

        }else if (result->type == parameter_value_types[PVT_UNKN])
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
        if (((param_t*)param_base)->type == parameter_value_types[PVT_UINT])
        {
            delete ((value_uint32*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_UINT64])
        {
            delete ((value_uint64*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_INT])
        {
            delete ((value_int32*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_INT64])
        {
            delete ((value_int64*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_FLOAT])
        {
            delete ((value_flt*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_DOUBLE])
        {
            delete ((value_dbl*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_ARRAY_UINT32])
        {
            delete ((array_uint32*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_ARRAY_UINT64])
        {
            delete ((array_uint64*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_ARRAY_INT32])
        {
            delete ((array_int32*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_ARRAY_INT64])
        {
            delete ((array_int64*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_ARRAY_FLT])
        {
            delete ((array_flt*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_ARRAY_DBL])
        {
            delete ((array_dbl*)param_base);
        }
        else if (((param_t*)param_base)->type == parameter_value_types[PVT_STRING])
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
template<> std::vector <std::tuple<uint32_t, std::string, std::string>> param::getValuesEnum<std::vector <std::tuple<uint32_t, std::string, std::string>>>() const
{
    return ((value_uint32*)param_base)->valuesEnum;
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
template<> std::vector <std::tuple<uint64_t, std::string, std::string>> param::getValuesEnum<std::vector <std::tuple<uint64_t, std::string, std::string>>>() const
{
    return ((value_uint64*)param_base)->valuesEnum;
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
template<> std::vector <std::tuple<int32_t, std::string, std::string>> param::getValuesEnum<std::vector <std::tuple<int32_t, std::string, std::string>>>() const
{
    return ((value_int32*)param_base)->valuesEnum;
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
template<> std::vector <std::tuple<int64_t, std::string, std::string>> param::getValuesEnum<std::vector <std::tuple<int64_t, std::string, std::string>>>() const
{
    return ((value_int64*)param_base)->valuesEnum;
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

std::string version::to_string()
{
    std::string s;
    s = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    return s;
}

uint32_t version::to_uint()
{
    return _value;
}

version::version()
{
    version((uint32_t)0);
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

    size_t pos = 0;
    std::string token;

    token = s.substr(0, pos);
    major =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

    token = s.substr(0, pos);
    minor =  std::stoi(token);
    s.erase(0, pos + delimiter.length());

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
            //_x_emr = ((rf627_smart_hello_info_by_service_protocol*)info)->fact_general_xsmr + ;
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
                        profile_from_scanner->rf627old_profile2D->header.zmr;
                m_Header.xemr =
                        profile_from_scanner->rf627old_profile2D->header.xemr;
                m_Header.discrete_value =
                        profile_from_scanner->rf627old_profile2D->header.discrete_value;

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

                m_Header.zmr =
                        profile_from_scanner->rf627smart_profile2D->header.zmr;
                m_Header.xemr =
                        profile_from_scanner->rf627smart_profile2D->header.xemr;
                m_Header.discrete_value =
                        profile_from_scanner->rf627smart_profile2D->header.discrete_value;

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

                switch (m_Header.data_type) {
                case DTY_PixelsNormal:
                case DTY_PixelsInterpolated:
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
                case DTY_ProfileNormal:
                case DTY_ProfileInterpolated:
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
            break;
        }
        }
    }
}

profile2D::~profile2D()
{
    rf627_profile2D_t* _profile = (rf627_profile2D_t*)m_ProfileBase;
    free_profile2D(_profile);
}

profile2D::header profile2D::getHeader()
{
    return m_Header;
}

const std::vector<uint8_t>& profile2D::getIntensity()
{
    return m_Intensity;
}

const std::vector<uint16_t>& profile2D::getPixels()
{
    return m_Pixels;
}

const std::vector<point2D_t>& profile2D::getPoints()
{
    return m_Points;
}

//
// RF627
// old version (v1.x.x)
//


std::vector<rf627old*> rf627old::search(PROTOCOLS protocol)
{
    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
        /*
         * Cleaning detected network adapter.
         */
        FreeAdapterAddresses();
        /*
         * Retrieving addresses associated with adapters on the local computer.
         */
        EnumAdapterAddresses();

        /*
         * Create value for scanners vector's type
         */
        vector_t* scanners = (vector_t*)calloc(1, sizeof (vector_t));
        /*
         * Initialization vector
         */
        vector_init(&scanners);


        /*
         * Iterate over all available network adapters in the current operating
         * system to send "Hello" requests.
         */
        for (int i=0; i<GetAdaptersCount(); i++)
        {
            // get another IP Addr and set this changes in network adapter settings.
            uint32_t host_ip_addr = ntohl(inet_addr(GetAdapterAddress(i)));
            uint32_t host_mask = ntohl(inet_addr("255.255.255.0"));
            // call the function to change adapter settings inside the library.
            set_platform_adapter_settings(host_mask, host_ip_addr);

            // Search for RF627-old devices over network by Service Protocol.
            search_scanners(scanners, kRF627_OLD, 1000, kSERVICE);
        }

        std::vector<rf627old*> result;

        /*
         * Iterate over all discovered rf627-old in network and push into list.
         */
        for(size_t i = 0; i < vector_count(scanners); i++)
        {
            result.push_back(new rf627old((void*)vector_get(scanners,i)));
            result[i]->current_protocol = PROTOCOLS::SERVICE;
        }
        return result;
        break;
    }
    default:
    {
        static std::vector<rf627old*> result;
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
    is_connected = false;
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
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        if (is_connected == false)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = connect_to_scanner(
                        ((scanner_base_t*)this->scanner_base), kSERVICE);
            is_connected = result;
        }else
        {
            result = is_connected;
        }
        return result;
        break;
    }
    default:
        break;
    }

    return false;

}

bool rf627old::check_connection(PROTOCOLS protocol)
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
        if (is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
//            result = check_connection_to_scanner(
//                        ((scanner_base_t*)this->scanner_base), timeout, kSERVICE);
            result = true;
        }else
        {
            result = false;
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
        if (is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = disconnect_from_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            if (result)
                is_connected = FALSE;
            else
                is_connected = TRUE;
        }else
        {
            result = TRUE;
            is_connected = FALSE;
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

    if (is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Get profile from scanner's data stream by Service Protocol.
            rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                        (scanner_base_t*)scanner_base, zero_points, realtime, kSERVICE);

            if (profile_from_scanner != nullptr)
            {
                std::shared_ptr<profile2D> result = std::make_shared<profile2D>(profile_from_scanner);
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

profile3D_t* rf627old::get_profile3D(float step_size, float k,
                                     COUNT_TYPES count_type,
                                     bool zero_points,
                                     PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

//    switch (p) {
//    case PROTOCOLS::SERVICE:
//    {
//        // Get profile from scanner's data stream by Service Protocol.
//        rf627_profile3D_t* profile_from_scanner = get_profile3D_from_scanner(
//                    (scanner_base_t*)scanner_base, step_size, k, (count_types_t)count_type, zero_points, kSERVICE);

//        profile3D_t* result = new profile3D_t;

//        if(profile_from_scanner->rf627_profile3D != NULL)
//        {
//            result->header.data_type =
//                    profile_from_scanner->rf627_profile3D->header.data_type;
//            result->header.flags =
//                    profile_from_scanner->rf627_profile3D->header.flags;
//            result->header.device_type =
//                    profile_from_scanner->rf627_profile3D->header.device_type;
//            result->header.serial_number =
//                    profile_from_scanner->rf627_profile3D->header.serial_number;
//            result->header.system_time =
//                    profile_from_scanner->rf627_profile3D->header.system_time;

//            result->header.proto_version_major =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_major;
//            result->header.proto_version_minor =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_minor;
//            result->header.hardware_params_offset =
//                    profile_from_scanner->rf627_profile3D->header.hardware_params_offset;
//            result->header.data_offset =
//                    profile_from_scanner->rf627_profile3D->header.data_offset;
//            result->header.packet_count =
//                    profile_from_scanner->rf627_profile3D->header.packet_count;
//            result->header.measure_count =
//                    profile_from_scanner->rf627_profile3D->header.measure_count;

//            result->header.zmr =
//                    profile_from_scanner->rf627_profile3D->header.zmr;
//            result->header.xemr =
//                    profile_from_scanner->rf627_profile3D->header.xemr;
//            result->header.discrete_value =
//                    profile_from_scanner->rf627_profile3D->header.discrete_value;

//            result->header.exposure_time =
//                    profile_from_scanner->rf627_profile3D->header.exposure_time;
//            result->header.laser_value =
//                    profile_from_scanner->rf627_profile3D->header.laser_value;
//            result->header.step_count =
//                    profile_from_scanner->rf627_profile3D->header.step_count;
//            result->header.dir =
//                    profile_from_scanner->rf627_profile3D->header.dir;

//            switch (result->header.data_type) {
//            case DTY_PixelsNormal:
//            case DTY_PixelsInterpolated:
//            {
//                result->pixels.resize(profile_from_scanner->
//                                      rf627_profile3D->pixels_format.pixels_count);

//                for(size_t i = 0; i < result->pixels.size(); i++)
//                {
//                    result->pixels[i] = profile_from_scanner->
//                            rf627_profile3D->pixels_format.pixels[i];
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }

//                break;
//            }
//            case DTY_ProfileNormal:
//            case DTY_ProfileInterpolated:
//            {
//                result->points.resize(profile_from_scanner->
//                                      rf627_profile3D->profile_format.points_count);

//                for(size_t i = 0; i < result->points.size(); i++)
//                {
//                    result->points[i].x = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].x;
//                    result->points[i].y = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].y;
//                    result->points[i].z = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].z;
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }
//                break;
//            }
//            default:
//                break;
//            }
//            free(profile_from_scanner->rf627_profile3D->intensity);
//            free(profile_from_scanner->rf627_profile3D->pixels_format.pixels);
//            free(profile_from_scanner->rf627_profile3D);
//            free(profile_from_scanner);
//            return result;
//        }

//        free(profile_from_scanner->rf627_profile3D);
//        free(profile_from_scanner);
//        delete result;
//    }
//    default:
//        break;
//    }

    return NULL;

}

char *rf627old::get_frame(PROTOCOLS protocol)
{
    return nullptr;
}

bool rf627old::read_params(PROTOCOLS protocol)
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
        result = read_params_from_scanner(
                    (scanner_base_t*)scanner_base, 0, kSERVICE);
        return result;
        break;
    }
    default:
        break;
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
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}


std::shared_ptr<param> rf627old::get_param(PARAM_NAME_KEY param_name)
{
    return get_param(parameter_names[(uint8_t)param_name]);
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
    if (type == parameter_value_types[PVT_UINT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_uint32 = (value_uint32_t*)calloc(1, sizeof (value_uint32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT_PARAM_TYPE].c_str();
    }else if (type == parameter_value_types[PVT_UINT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_uint64 = (value_uint64_t*)calloc(1, sizeof (value_uint64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT64_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_INT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_int32 = (value_int32_t*)calloc(1, sizeof (value_int32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_INT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_int64 = (value_int64_t*)calloc(1, sizeof (value_int64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT64_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_FLOAT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_flt = (value_flt_t*)calloc(1, sizeof (value_flt_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::FLOAT_PARAM_TYPE].c_str();
    }else if(type ==  parameter_value_types[PVT_DOUBLE])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->val_dbl = (value_dbl_t*)calloc(1, sizeof (value_dbl_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::DOUBLE_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_UINT32])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_uint32 = (array_uint32_t*)calloc(1, sizeof (array_uint32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT32_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_UINT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_uint64 = (array_uint64_t*)calloc(1, sizeof (array_uint64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::UINT64_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_INT32])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_int32 = (array_int32_t*)calloc(1, sizeof (array_int32_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT32_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_INT64])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_int64 = (array_int64_t*)calloc(1, sizeof (array_int64_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::INT64_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_FLT])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_flt = (array_flt_t*)calloc(1, sizeof (array_flt_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::FLT_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_ARRAY_DBL])
    {
        p = (parameter_t*)calloc(1, sizeof (parameter_t));
        p->arr_dbl = (array_dbl_t*)calloc(1, sizeof (array_dbl_t));
        p->base.type = (char*)param_value_types[(uint8_t)PARAM_VALUE_TYPE::DBL_ARRAY_PARAM_TYPE].c_str();
    }else if (type ==  parameter_value_types[PVT_STRING])
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

        if (param->getType() == parameter_value_types[PVT_STRING])
        {
            std::string new_value = param->getValue<std::string>();
            delete[] p->val_str->value;
            p->val_str->value = new char[new_value.length() + 1];
            strcpy(p->val_str->value, new_value.c_str());
            p->base.size = new_value.length() + 1;
        }
        else if (param->getType() == parameter_value_types[PVT_INT])
        {
            p->val_int32->value = param->getValue<int32_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_INT64])
        {
            p->val_int64->value = param->getValue<int64_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_UINT])
        {
            p->val_uint32->value = param->getValue<uint32_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_UINT64])
        {
            p->val_uint64->value = param->getValue<uint64_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_FLOAT])
        {
            p->val_flt->value = param->getValue<float>();
        }
        else if (param->getType() ==  parameter_value_types[PVT_DOUBLE])
        {
            p->val_dbl->value = param->getValue<double>();
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_UINT32])
        {
            std::vector<uint32_t> v = param->getValue<std::vector<uint32_t>>();
            p->arr_uint32->value = (rfUint32*)calloc(v.size(), sizeof (rfUint32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint32);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_INT32])
        {
            std::vector<int32_t> v = param->getValue<std::vector<int32_t>>();
            p->arr_int32->value = (rfInt32*)calloc(v.size(), sizeof (rfInt32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt32);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_UINT64])
        {
            std::vector<uint64_t> v = param->getValue<std::vector<uint64_t>>();
            p->arr_uint64->value = (rfUint64*)calloc(v.size(), sizeof (rfUint64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint64);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_INT64])
        {
            std::vector<int64_t> v = param->getValue<std::vector<int64_t>>();
            p->arr_int64->value = (rfInt64*)calloc(v.size(), sizeof (rfInt64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt64);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_FLT])
        {
            std::vector<float> v = param->getValue<std::vector<float>>();
            p->arr_flt->value = (rfFloat*)calloc(v.size(), sizeof (rfFloat));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_flt->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfFloat);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_DBL])
        {
            std::vector<double> v = param->getValue<std::vector<double>>();
            p->arr_dbl->value = (rfDouble*)calloc(v.size(), sizeof (rfDouble));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_dbl->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfDouble);
        }
        set_parameter((scanner_base_t*)this->scanner_base, p);
        free_parameter(p, ((scanner_base_t*)this->scanner_base)->type);
        return true;
    }
    return false;
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

//
// RF627
// smart version (v2.x.x)
//

std::vector<std::shared_ptr<rf627smart>> rf627smart::search(uint32_t timeout, PROTOCOLS protocol)
{
    switch (protocol) {
    case PROTOCOLS::SERVICE:
    {
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

            // Search for RF627-Smart devices over network by Service Protocol.
            if (host_ip_addr != 0)
            {
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
            }
        }

        std::vector<std::shared_ptr<rf627smart>> result;

        //Iterate over all discovered rf627-smart in network and push into list.
        for(size_t i = 0; i < vector_count(scanners); i++)
        {
            result.push_back(std::shared_ptr<rf627smart>(std::make_shared<rf627smart>((void*)vector_get(scanners,i))));
            result[i]->current_protocol = PROTOCOLS::SERVICE;
        }

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
    is_connected = false;
}

rf627smart::~rf627smart()
{
    free_scanner(((scanner_base_t*)this->scanner_base));
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
        bool result = false;
        if (is_connected == false)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = connect_to_scanner(
                        ((scanner_base_t*)this->scanner_base), kSERVICE);
            is_connected = result;
            if (is_connected)
                read_params();
        }else
        {
            result = is_connected;
        }

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
        if (is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = check_connection_to_scanner(
                        ((scanner_base_t*)this->scanner_base), timeout, kSERVICE);
            is_connected = result;
        }else
        {
            result = is_connected;
        }

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
        if (is_connected)
        {
            // Establish connection to the RF627 device by Service Protocol.
            result = disconnect_from_scanner(
                        (scanner_base_t*)scanner_base, kSERVICE);
            if (result)
                is_connected = FALSE;
            else
                is_connected = TRUE;
        }else
        {
            result = TRUE;
            is_connected = FALSE;
        }
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

    if (is_connected)
    {
        switch (p) {
        case PROTOCOLS::SERVICE:
        {
            // Get profile from scanner's data stream by Service Protocol.
            rf627_profile2D_t* profile_from_scanner = get_profile2D_from_scanner(
                        (scanner_base_t*)scanner_base, zero_points, realtime, kSERVICE);

            if (profile_from_scanner->rf627smart_profile2D != nullptr)
            {
                std::shared_ptr<profile2D> result = std::make_shared<profile2D>(profile_from_scanner);
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

profile3D_t* rf627smart::get_profile3D(float step_size, float k,
                                     COUNT_TYPES count_type,
                                     bool zero_points,
                                     PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

//    switch (p) {
//    case PROTOCOLS::SERVICE:
//    {
//        // Get profile from scanner's data stream by Service Protocol.
//        rf627_profile3D_t* profile_from_scanner = get_profile3D_from_scanner(
//                    (scanner_base_t*)scanner_base, step_size, k, (count_types_t)count_type, zero_points, kSERVICE);

//        profile3D_t* result = new profile3D_t;

//        if(profile_from_scanner->rf627_profile3D != NULL)
//        {
//            result->header.data_type =
//                    profile_from_scanner->rf627_profile3D->header.data_type;
//            result->header.flags =
//                    profile_from_scanner->rf627_profile3D->header.flags;
//            result->header.device_type =
//                    profile_from_scanner->rf627_profile3D->header.device_type;
//            result->header.serial_number =
//                    profile_from_scanner->rf627_profile3D->header.serial_number;
//            result->header.system_time =
//                    profile_from_scanner->rf627_profile3D->header.system_time;

//            result->header.proto_version_major =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_major;
//            result->header.proto_version_minor =
//                    profile_from_scanner->rf627_profile3D->header.proto_version_minor;
//            result->header.hardware_params_offset =
//                    profile_from_scanner->rf627_profile3D->header.hardware_params_offset;
//            result->header.data_offset =
//                    profile_from_scanner->rf627_profile3D->header.data_offset;
//            result->header.packet_count =
//                    profile_from_scanner->rf627_profile3D->header.packet_count;
//            result->header.measure_count =
//                    profile_from_scanner->rf627_profile3D->header.measure_count;

//            result->header.zmr =
//                    profile_from_scanner->rf627_profile3D->header.zmr;
//            result->header.xemr =
//                    profile_from_scanner->rf627_profile3D->header.xemr;
//            result->header.discrete_value =
//                    profile_from_scanner->rf627_profile3D->header.discrete_value;

//            result->header.exposure_time =
//                    profile_from_scanner->rf627_profile3D->header.exposure_time;
//            result->header.laser_value =
//                    profile_from_scanner->rf627_profile3D->header.laser_value;
//            result->header.step_count =
//                    profile_from_scanner->rf627_profile3D->header.step_count;
//            result->header.dir =
//                    profile_from_scanner->rf627_profile3D->header.dir;

//            switch (result->header.data_type) {
//            case DTY_PixelsNormal:
//            case DTY_PixelsInterpolated:
//            {
//                result->pixels.resize(profile_from_scanner->
//                                      rf627_profile3D->pixels_format.pixels_count);

//                for(size_t i = 0; i < result->pixels.size(); i++)
//                {
//                    result->pixels[i] = profile_from_scanner->
//                            rf627_profile3D->pixels_format.pixels[i];
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }

//                break;
//            }
//            case DTY_ProfileNormal:
//            case DTY_ProfileInterpolated:
//            {
//                result->points.resize(profile_from_scanner->
//                                      rf627_profile3D->profile_format.points_count);

//                for(size_t i = 0; i < result->points.size(); i++)
//                {
//                    result->points[i].x = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].x;
//                    result->points[i].y = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].y;
//                    result->points[i].z = profile_from_scanner->rf627_profile3D->
//                            profile_format.points[i].z;
//                }

//                if(profile_from_scanner->rf627_profile3D->intensity_count > 0)
//                {
//                    result->intensity.resize(
//                                profile_from_scanner->rf627_profile3D->intensity_count);
//                    for (size_t i = 0; i < result->intensity.size(); i++)
//                        result->intensity[i] =
//                                profile_from_scanner->rf627_profile3D->intensity[i];
//                }
//                break;
//            }
//            default:
//                break;
//            }
//            free(profile_from_scanner->rf627_profile3D->intensity);
//            free(profile_from_scanner->rf627_profile3D->pixels_format.pixels);
//            free(profile_from_scanner->rf627_profile3D);
//            free(profile_from_scanner);
//            return result;
//        }

//        free(profile_from_scanner->rf627_profile3D);
//        free(profile_from_scanner);
//        delete result;
//    }
//    default:
//        break;
//    }

    return NULL;

}

std::shared_ptr<frame> rf627smart::get_frame(PROTOCOLS protocol)
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
        rf627_frame_t* _frame = get_frame_from_scanner(
                    (scanner_base_t*)scanner_base, kSERVICE);
        if (_frame != nullptr)
        {
            if (_frame->rf627smart_frame != nullptr)
            {
                std::shared_ptr<param> width = get_param("fact_sensor_width");
                std::shared_ptr<param> height = get_param("fact_sensor_height");

                if (width != NULL)
                {
                    _frame->rf627smart_frame->width = width->getValue<uint32_t>();
                }
                if (height != NULL)
                {
                    _frame->rf627smart_frame->height = height->getValue<uint32_t>();
                }

                if (_frame->rf627smart_frame->data_size == _frame->rf627smart_frame->width * _frame->rf627smart_frame->height * 1)
                {
                    _frame->rf627smart_frame->pixel_size = 1;
                }

                std::shared_ptr<frame> result = std::make_shared<frame>(_frame);
                return result;
            }
            free(_frame);
        }
        break;
    }
    default:
        break;
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

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        param_mutex.lock();
        result = read_params_from_scanner(
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        param_mutex.unlock();
        return result;
        break;
    }
    default:
        break;
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

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        param_mutex.lock();
        result = write_params_to_scanner(
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        param_mutex.unlock();
        return result;
        break;
    }
    default:
        break;
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

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Establish connection to the RF627 device by Service Protocol.
        bool result = false;
        param_mutex.lock();
        result = write_params_to_scanner(
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        param_mutex.unlock();
        return result;
        break;
    }
    default:
        break;
    }

    return false;
}

std::shared_ptr<param> rf627smart::get_param(PARAM_NAME_KEY param_name)
{
    return get_param(parameter_names[(uint8_t)param_name]);
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

        if (param->getType() == parameter_value_types[PVT_STRING])
        {
            std::string new_value = param->getValue<std::string>();
            delete[] p->val_str->value;
            p->val_str->value = new char[new_value.length() + 1];
            strcpy(p->val_str->value, new_value.c_str());
            p->base.size = new_value.length() + 1;
        }
        else if (param->getType() == parameter_value_types[PVT_INT])
        {
            p->val_int32->value = param->getValue<int32_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_INT64])
        {
            p->val_int64->value = param->getValue<int64_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_UINT])
        {
            p->val_uint32->value = param->getValue<uint32_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_UINT64])
        {
            p->val_uint64->value = param->getValue<uint64_t>();
        }
        else if (param->getType() == parameter_value_types[PVT_FLOAT])
        {
            p->val_flt->value = param->getValue<float>();
        }
        else if (param->getType() ==  parameter_value_types[PVT_DOUBLE])
        {
            p->val_dbl->value = param->getValue<double>();
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_UINT32])
        {
            std::vector<uint32_t> v = param->getValue<std::vector<uint32_t>>();
            p->arr_uint32->value = (rfUint32*)calloc(v.size(), sizeof (rfUint32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint32);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_INT32])
        {
            std::vector<int32_t> v = param->getValue<std::vector<int32_t>>();
            p->arr_int32->value = (rfInt32*)calloc(v.size(), sizeof (rfInt32));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int32->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt32);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_UINT64])
        {
            std::vector<uint64_t> v = param->getValue<std::vector<uint64_t>>();
            p->arr_uint64->value = (rfUint64*)calloc(v.size(), sizeof (rfUint64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_uint64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfUint64);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_INT64])
        {
            std::vector<int64_t> v = param->getValue<std::vector<int64_t>>();
            p->arr_int64->value = (rfInt64*)calloc(v.size(), sizeof (rfInt64));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_int64->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfInt64);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_FLT])
        {
            std::vector<float> v = param->getValue<std::vector<float>>();
            p->arr_flt->value = (rfFloat*)calloc(v.size(), sizeof (rfFloat));
            for (rfSize j = 0; j < v.size(); j++)
                p->arr_flt->value[j] = v[j];
            p->base.size = v.size() * sizeof (rfFloat);
        }
        else if (param->getType() ==  parameter_value_types[PVT_ARRAY_DBL])
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

bool rf627smart::start_dump_recording(uint32_t count_of_profiles)
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

bool rf627smart::stop_dump_recording(uint32_t &count_of_profiles)
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

    return true;
}

std::vector<std::shared_ptr<profile2D>> rf627smart::get_dumps_profiles(
        uint32_t index, uint32_t count, PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    std::vector<std::shared_ptr<profile2D>> result;
    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Get parameter of user_dump_enabled
        std::shared_ptr<param> fact_dump_unitSize = get_param("fact_dump_unitSize");
        if (fact_dump_unitSize !=nullptr && fact_dump_unitSize->getType()=="uint32_t")
        {
            rf627_profile2D_t** dumps =
                    (rf627_profile2D_t**)calloc(count, sizeof (rf627_profile2D_t*));
            uint32_t dump_size = 0;
            uint8_t status = get_dumps_profiles_from_scanner(
                        (scanner_base_t*)scanner_base, index, count, 1000, kSERVICE,
                        dumps, &dump_size, fact_dump_unitSize->getValue<uint32_t>());
            if (status)
            {
                for(uint32_t i = 0; i < dump_size; i++)
                {
                    if (dumps[i]->rf627smart_profile2D != nullptr)
                    {
                        result.push_back(std::make_shared<profile2D>(dumps[i]));
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

        break;
    }
    default:
        break;
    }

    return result;
}

bool rf627smart::get_authorization_token(std::string& token, PROTOCOLS protocol)
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

    return false;
}

bool rf627smart::set_authorization_key(std::string key, PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

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

    return false;
}

std::shared_ptr<calib_table> rf627smart::get_calibration_table()
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
bool rf627smart::set_calibration_table(std::shared_ptr<calib_table> table)
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

bool rf627smart::read_calibration_table(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

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

    return false;
}

bool rf627smart::write_calibration_table(PROTOCOLS protocol)
{
    PROTOCOLS p;
    if (protocol == PROTOCOLS::CURRENT)
        p = this->current_protocol;
    else
        p = protocol;

    switch (p) {
    case PROTOCOLS::SERVICE:
    {
        // Set authorization key to the RF627 device by Service Protocol.
        bool result = false;
        result = write_calibration_table_to_scanner(
                    (scanner_base_t*)scanner_base, 3000, kSERVICE);
        return result;
        break;
    }
    default:
        break;
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

    return false;
}







void sdk_cleanup()
{
#if (defined _WIN32)
    FreeAdapterAddresses();
    WinSockDeinit();
#endif
}


}
}
}

