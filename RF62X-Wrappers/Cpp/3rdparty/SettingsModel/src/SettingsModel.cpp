#include "SettingsModel.h"
#include "SettingsModelVersion.h"

#include <string>
#include <iostream>
#include <sstream>


using namespace cr::utils;



template<>
ValueEnum::ValueEnum(
        std::vector<std::tuple<int, std::string, std::string> > enum_base)
{
    for (auto a : enum_base)
        _enum_base.push_back(
                    std::tuple<std::any, std::string, std::string>(
                        std::any(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
}



template<>
ValueEnum::ValueEnum(
        std::vector<std::tuple<unsigned int, std::string, std::string> > enum_base)
{
    for (auto a : enum_base)
        _enum_base.push_back(
                    std::tuple<std::any, std::string, std::string>(
                        std::any(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
}



template<>
ValueEnum::ValueEnum(
        std::vector<std::tuple<double, std::string, std::string> > enum_base)
{
    for (auto a : enum_base)
        _enum_base.push_back(
                    std::tuple<std::any, std::string, std::string>(
                        std::any(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
}



template<>
ValueEnum::ValueEnum(
        std::vector<std::tuple<std::string, std::string, std::string> > enum_base)
{
    for (auto a : enum_base)
        _enum_base.push_back(
                    std::tuple<std::any, std::string, std::string>(
                        std::any(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
}



ValueEnum::~ValueEnum()
{

}



std::string ValueEnum::getLabel(std::string key)
{
    auto it = std::find_if(
                _enum_base.begin(), _enum_base.end(),
                [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw "No enum item for the specified key";
    }
}



std::vector<std::string> ValueEnum::getKeyList()
{
    std::vector<std::string> result;
    for (auto &item : _enum_base)
        result.push_back(std::get<1>(item));
    return result;
}



std::vector<std::string> ValueEnum::getLabelList()
{
    std::vector<std::string> result;
    for (auto &item : _enum_base)
        result.push_back(std::get<2>(item));
    return result;
}



template<>
int ValueEnum::getValue(std::string key)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::any_cast<int>(std::get<0>(*it));
    }else
    {
        throw std::invalid_argument("No enum item for the specified key");
    }
}



template<>
unsigned int ValueEnum::getValue(std::string key)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::any_cast<unsigned int>(std::get<0>(*it));
    }else
    {
        throw std::invalid_argument("No enum item for the specified key");
    }
}


template<>
float ValueEnum::getValue(std::string key)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::any_cast<float>(std::get<0>(*it));
    }else
    {
        throw std::invalid_argument("No enum item for the specified key");
    }
}


template<>
double ValueEnum::getValue(std::string key)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::any_cast<double>(std::get<0>(*it));
    }else
    {
        throw std::invalid_argument("No enum item for the specified key");
    }
}

template<>
bool ValueEnum::getValue(std::string key)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::any_cast<bool>(std::get<0>(*it));
    }else
    {
        throw std::invalid_argument("No enum item for the specified key");
    }
}



template<>
std::string ValueEnum::getValue(std::string key)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [key](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::get<1>(e) == key;
    });

    if (it != _enum_base.end())
    {
        return std::any_cast<std::string>(std::get<0>(*it));
    }else
    {
        throw std::invalid_argument("No enum item for the specified key");
    }
}



template<>
std::string ValueEnum::findLabel(int value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<int>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findLabel(unsigned int value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<unsigned int>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findLabel(double value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<double>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findLabel(std::string value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<std::string>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<2>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findKey(int value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<int>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<1>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findKey(unsigned int value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<unsigned int>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<1>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findKey(double value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<double>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<1>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::string ValueEnum::findKey(std::string value)
{
    auto it = std::find_if(_enum_base.begin(), _enum_base.end(),
                           [value](const std::tuple<std::any, std::string, std::string>& e)
    {
        return std::any_cast<std::string>(std::get<0>(e)) == value;
    });

    if (it != _enum_base.end())
    {
        return std::get<1>(*it);
    }else
    {
        throw std::invalid_argument("No enum item at the specified value");
    }
}



template<>
std::vector<int> ValueEnum::getValueList()
{
    std::vector<int> result;
    for (auto &item : _enum_base)
        result.push_back(std::any_cast<int>(std::get<0>(item)));
    return result;
}



template<>
std::vector<unsigned int> ValueEnum::getValueList()
{
    std::vector<unsigned int> result;
    for (auto &item : _enum_base)
        result.push_back(std::any_cast<unsigned int>(std::get<0>(item)));
    return result;
}



template<>
std::vector<double> ValueEnum::getValueList()
{
    std::vector<double> result;
    for (auto &item : _enum_base)
        result.push_back(std::any_cast<double>(std::get<0>(item)));
    return result;
}


template<>
std::vector<std::string> ValueEnum::getValueList()
{
    std::vector<std::string> result;
    for (auto &item : _enum_base)
        result.push_back(std::any_cast<std::string>(std::get<0>(item)));
    return result;
}



template<>
std::tuple<int, std::string, std::string> ValueEnum::getItem(uint32_t index)
{
    if (index < _enum_base.size())
    {
        std::tuple<int, std::string, std::string> _res(
                    std::any_cast<int>(std::get<0>(_enum_base[index])),
                        std::get<1>(_enum_base[index]),
                        std::get<2>(_enum_base[index]));
        return _res;
    }else
    {
        throw std::range_error("No enum item at the specified index");
    }
}



template<>
std::tuple<unsigned int, std::string, std::string> ValueEnum::getItem(uint32_t index)
{
    if (index < _enum_base.size())
    {
        std::tuple<unsigned int, std::string, std::string> _res(
                    std::any_cast<unsigned int>(std::get<0>(_enum_base[index])),
                        std::get<1>(_enum_base[index]),
                        std::get<2>(_enum_base[index]));
        return _res;
    }else
    {
        throw std::range_error("No enum item at the specified index");
    }
}



template<>
std::tuple<double, std::string, std::string> ValueEnum::getItem(uint32_t index)
{
    if (index < _enum_base.size())
    {
        std::tuple<double, std::string, std::string> _res(
                    std::any_cast<double>(std::get<0>(_enum_base[index])),
                        std::get<1>(_enum_base[index]),
                        std::get<2>(_enum_base[index]));
        return _res;
    }else
    {
        throw std::range_error("No enum item at the specified index");
    }
}



template<>
std::tuple<std::string, std::string, std::string> ValueEnum::getItem(uint32_t index)
{
    if (index < _enum_base.size())
    {
        std::tuple<std::string, std::string, std::string> _res(
                    std::any_cast<std::string>(std::get<0>(_enum_base[index])),
                        std::get<1>(_enum_base[index]),
                        std::get<2>(_enum_base[index]));
        return _res;
    }else
    {
        throw std::range_error("No enum item at the specified index");
    }
}



template<>
std::vector<std::tuple<int, std::string, std::string>> ValueEnum::getItemList()
{
    std::vector<std::tuple<int, std::string, std::string>> _res;
    for (auto& a : _enum_base)
    {
        _res.push_back(std::tuple<int, std::string, std::string>(
                           std::any_cast<int>(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
    }
    return _res;
}



template<>
std::vector<std::tuple<unsigned int, std::string, std::string>> ValueEnum::getItemList()
{
    std::vector<std::tuple<unsigned int, std::string, std::string>> _res;
    for (auto& a : _enum_base)
    {
        _res.push_back(std::tuple<unsigned int, std::string, std::string>(
                           std::any_cast<unsigned int>(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
    }
    return _res;
}


template<>
std::vector<std::tuple<float, std::string, std::string>> ValueEnum::getItemList()
{
    std::vector<std::tuple<float, std::string, std::string>> _res;
    for (auto& a : _enum_base)
    {
        _res.push_back(std::tuple<float, std::string, std::string>(
                           std::any_cast<float>(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
    }
    return _res;
}

template<>
std::vector<std::tuple<double, std::string, std::string>> ValueEnum::getItemList()
{
    std::vector<std::tuple<double, std::string, std::string>> _res;
    for (auto& a : _enum_base)
    {
        _res.push_back(std::tuple<double, std::string, std::string>(
                           std::any_cast<double>(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
    }
    return _res;
}

template<>
std::vector<std::tuple<bool, std::string, std::string>> ValueEnum::getItemList()
{
    std::vector<std::tuple<bool, std::string, std::string>> _res;
    for (auto& a : _enum_base)
    {
        _res.push_back(std::tuple<bool, std::string, std::string>(
                           std::any_cast<bool>(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
    }
    return _res;
}



template<>
std::vector<std::tuple<std::string, std::string, std::string>> ValueEnum::getItemList()
{
    std::vector<std::tuple<std::string, std::string, std::string>> _res;
    for (auto& a : _enum_base)
    {
        _res.push_back(std::tuple<std::string, std::string, std::string>(
                           std::any_cast<std::string>(std::get<0>(a)), std::get<1>(a), std::get<2>(a)));
    }
    return _res;
}

std::string SettingsModel::getVersion()
{
    return SETTINGS_MODEL_VERSION;
}

std::string SettingsModel::help()
{
    std::stringstream buffer;

    buffer << std::endl << "Properties Info: " << std::endl;
    buffer << "==================================================" << std::endl;

    if (m_props.size() > 0)
    for (auto& prop : m_props)
    {
        buffer << "* Key\t\t:\t" << prop.first << std::endl;
        buffer << "* Type\t\t:\t" << prop.second->getValueType().name() << std::endl;
        if (std::type_index(prop.second->getValueType()) == std::type_index(typeid(int)))
        {
            buffer << "* Value\t\t:\t" << prop.second->getValue<int>() << std::endl;

            if(prop.second->getMin().has_value() && prop.second->getMax().has_value())
                buffer << "* Range\t\t:\t["
                       << std::any_cast<int>(prop.second->getMin()) << " - "
                       << std::any_cast<int>(prop.second->getMax()) << "]" << std::endl;

            if (!prop.second->getUnits().empty())
            buffer << "* Units\t\t:\t" << prop.second->getUnits() << std::endl;
            buffer << "* Access\t:\t" << prop.second->getAccess() << std::endl;

            if(prop.second->getEnum() != nullptr)
            {
                buffer << "* Enums";
                for(auto& a : prop.second->getEnum()->getItemList<int>())
                {
                    buffer << "\t\t:\tkey: " << std::get<1>(a) << "; value: " << std::get<0>(a)<< std::endl;
                }
            }
        }else
        if (std::type_index(prop.second->getValueType()) == std::type_index(typeid(unsigned int)))
        {
            buffer << "* Value\t\t:\t" << prop.second->getValue<unsigned int>() << std::endl;

            if(prop.second->getMin().has_value() && prop.second->getMax().has_value())
                buffer << "* Range\t\t:\t["
                       << std::any_cast<unsigned int>(prop.second->getMin()) << " - "
                       << std::any_cast<unsigned int>(prop.second->getMax()) << "]" << std::endl;

            if (!prop.second->getUnits().empty())
            buffer << "* Units\t\t:\t" << prop.second->getUnits() << std::endl;
            buffer << "* Access\t:\t" << prop.second->getAccess() << std::endl;

            if(prop.second->getEnum() != nullptr)
            {
                buffer << "* Enums";
                for(auto& a : prop.second->getEnum()->getItemList<unsigned int>())
                {
                    buffer << "\t\t:\tkey: " << std::get<1>(a) << "; value: " << std::get<0>(a)<< std::endl;
                }
            }
        }else
        if (std::type_index(prop.second->getValueType()) == std::type_index(typeid(double)))
        {
            buffer << "* Value\t\t:\t" << prop.second->getValue<double>() << std::endl;

            if(prop.second->getMin().has_value() && prop.second->getMax().has_value())
                buffer << "* Range\t\t:\t["
                       << std::any_cast<double>(prop.second->getMin()) << " - "
                       << std::any_cast<double>(prop.second->getMax()) << "]" << std::endl;

            if (!prop.second->getUnits().empty())
            buffer << "* Units\t\t:\t" << prop.second->getUnits() << std::endl;
            buffer << "* Access\t:\t" << prop.second->getAccess() << std::endl;

            if(prop.second->getEnum() != nullptr)
            {
                buffer << "* Enums";
                for(auto& a : prop.second->getEnum()->getItemList<double>())
                {
                    buffer << "\t\t:\tkey: " << std::get<1>(a) << "; value: " << std::get<0>(a)<< std::endl;
                }
            }
        }else
        if (std::type_index(prop.second->getValueType()) == std::type_index(typeid(float)))
        {
            buffer << "* Value\t\t:\t" << prop.second->getValue<float>() << std::endl;

            if(prop.second->getMin().has_value() && prop.second->getMax().has_value())
                buffer << "* Range\t\t:\t["
                       << std::any_cast<float>(prop.second->getMin()) << " - "
                       << std::any_cast<float>(prop.second->getMax()) << "]" << std::endl;

            if (!prop.second->getUnits().empty())
            buffer << "* Units\t\t:\t" << prop.second->getUnits() << std::endl;
            buffer << "* Access\t:\t" << prop.second->getAccess() << std::endl;

            if(prop.second->getEnum() != nullptr)
            {
                buffer << "* Enums";
                for(auto& a : prop.second->getEnum()->getItemList<float>())
                {
                    buffer << "\t\t:\tkey: " << std::get<1>(a) << "; value: " << std::get<0>(a)<< std::endl;
                }
            }
        }else
        if (std::type_index(prop.second->getValueType()) == std::type_index(typeid(bool)))
        {
            buffer << "* Value\t\t:\t" << std::boolalpha << prop.second->getValue<bool>() << std::endl;

            if (!prop.second->getUnits().empty())
            buffer << "* Units\t\t:\t" << prop.second->getUnits() << std::endl;
            buffer << "* Access\t:\t" << prop.second->getAccess() << std::endl;

            if(prop.second->getEnum() != nullptr)
            {
                buffer << "* Enums";
                for(auto& a : prop.second->getEnum()->getItemList<bool>())
                {
                    buffer << "\t\t:\tkey: " << std::get<1>(a) << "; value: " << std::get<0>(a)<< std::endl;
                }
            }
        }else
        if (std::type_index(prop.second->getValueType()) == std::type_index(typeid(std::string)))
        {
            buffer << "* Value\t\t:\t" << prop.second->getValue<std::string>() << std::endl;

            if (!prop.second->getUnits().empty())
            buffer << "* Units\t\t:\t" << prop.second->getUnits() << std::endl;
            buffer << "* Access\t:\t" << prop.second->getAccess() << std::endl;

            if(prop.second->getEnum() != nullptr)
            {
                buffer << "* Enums";
                for(auto& a : prop.second->getEnum()->getItemList<std::string>())
                {
                    buffer << "\t\t:\tkey: " << std::get<1>(a) << "; value: " << std::get<0>(a)<< std::endl;
                }
            }
        }

        buffer << "--------------------------------------------------" << std::endl;
    }else
    {
        buffer << "not supported" << std::endl;
    }

    buffer << std::endl << "Commands Info: " << std::endl;
    buffer << "==================================================" << std::endl;
    if (m_commands.size() > 0)
    {
        for (auto& commands : m_commands)
        {
            buffer << "* Key\t\t:\t" << commands.first << std::endl;
            buffer << "* Description\t:\t" << "" << std::endl;

            buffer << "--------------------------------------------------" << std::endl;
        }
    }else
    {
        buffer << "not supported" << std::endl;
    }
    return buffer.str();
}

bool SettingsModel::setPropertyByKey(std::string name, std::string value)
{
    if(m_props.find(name) == m_props.end())
        return false;

    try {
        if (std::type_index(m_props[name]->getValueType()) == std::type_index(typeid(int)))
            return m_props[name]->setValue(m_props[name]->getEnum()->getValue<int>(value));
        if (std::type_index(m_props[name]->getValueType()) == std::type_index(typeid(unsigned int)))
            return m_props[name]->setValue(m_props[name]->getEnum()->getValue<unsigned int>(value));
        if (std::type_index(m_props[name]->getValueType()) == std::type_index(typeid(float)))
            return m_props[name]->setValue(m_props[name]->getEnum()->getValue<float>(value));
        if (std::type_index(m_props[name]->getValueType()) == std::type_index(typeid(double)))
            return m_props[name]->setValue(m_props[name]->getEnum()->getValue<double>(value));
        if (std::type_index(m_props[name]->getValueType()) == std::type_index(typeid(bool)))
            return m_props[name]->setValue(m_props[name]->getEnum()->getValue<bool>(value));
        if (std::type_index(m_props[name]->getValueType()) == std::type_index(typeid(std::string)))
            return m_props[name]->setValue(m_props[name]->getEnum()->getValue<std::string>(value));
    }  catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return false;
}

bool SettingsModel::setProperty(std::pair<std::string, std::any> prop)
{
    if(m_props.find(prop.first) == m_props.end())
        return false;
    return m_props[prop.first]->setValue(prop.second);
}

bool SettingsModel::executeCommand(std::string name)
{
    if(m_commands.find(name) == m_commands.end())
        return false;

    return m_commands[name]->execute();
}

void SettingsModel::addCommand(std::string name, std::function<bool ()> fn)
{
    std::shared_ptr<BaseCommand> _cmd(new BaseCommand(name, fn));
    m_commands.insert({name, _cmd});
}
