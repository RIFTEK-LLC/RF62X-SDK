#pragma once
#include <vector>
#include <string>
#include <map>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <cstdlib>
#include <tuple>

#include <string>
#include <cstdint>
#include <thread>
#include <chrono>
#include <ctime>

namespace cr
{
namespace utils
{

template <typename T>
using enums = std::vector <std::tuple<T, std::string, std::string>>;

class ValueEnum
{
public:

    template <typename T>
    ValueEnum(std::vector <std::tuple<T, std::string, std::string>> enum_base);
    ~ValueEnum();

    template <typename T>
    T getValue(std::string key);
    std::string getLabel(std::string key);

    template<typename T>
    std::string findLabel(T value);
    template<typename T>
    std::string findKey(T value);

    template<typename T>
    std::vector<T> getValueList();

    std::vector<std::string> getKeyList();
    std::vector<std::string> getLabelList();

    template<typename T>
    std::tuple<T, std::string, std::string> getItem(uint32_t index);
    template<typename T>
    std::vector<std::tuple<T, std::string, std::string>> getItemList();

private:
    std::vector <std::tuple<std::any, std::string, std::string>> _enum_base;
};

class BaseProperty
{
public:

    BaseProperty(std::string name, std::any value, std::string access, std::string units,
          std::any min, std::any max, std::any step, std::shared_ptr<ValueEnum> valueEnum,
          bool (*f)(BaseProperty*, std::any))
        : m_name(name)
        , m_value(value)
        , m_defValue(value)
        , m_access(access)
        , m_units(units)
        , m_min(min)
        , m_max(max)
        , m_step(step)
        , m_valueEnum(valueEnum)
        , m_f(f)
    {
    };
    BaseProperty(std::string name, std::any value, std::string access, std::string units,
                 std::shared_ptr<ValueEnum> valueEnum,
          bool (*f)(BaseProperty*, std::any))
        : m_name(name)
        , m_value(value)
        , m_defValue(value)
        , m_access(access)
        , m_units(units)
        , m_valueEnum(valueEnum)
        , m_f(f)
    {
        m_min.reset();
        m_max.reset();
        m_step.reset();
    };
    BaseProperty(std::string name, std::any value, std::string access, std::string units,
                 std::any min, std::any max, bool (*f)(BaseProperty*, std::any))
        : m_name(name)
        , m_value(value)
        , m_defValue(value)
        , m_access(access)
        , m_units(units)
        , m_min(min)
        , m_max(max)
        , m_f(f)
    {
        m_step.reset();
        m_valueEnum = nullptr;
    };
    BaseProperty(std::string name, std::any value, std::string access, std::string units,
                 std::any min, std::any max, std::any step, bool (*f)(BaseProperty*, std::any))
        : m_name(name)
        , m_value(value)
        , m_defValue(value)
        , m_access(access)
        , m_units(units)
        , m_min(min)
        , m_max(max)
        , m_step(step)
        , m_f(f)
    {
        m_valueEnum = nullptr;
    };
    BaseProperty(std::string name, std::any value, std::string access, std::string units,
          bool (*f)(BaseProperty*, std::any))
        : m_name(name)
        , m_value(value)
        , m_defValue(value)
        , m_access(access)
        , m_units(units)
        , m_f(f)
    {
        m_min.reset();
        m_max.reset();
        m_step.reset();
        m_valueEnum = nullptr;
    };
    ~BaseProperty(){};

    std::string getName(){return m_name;}
    std::string getAccess(){return m_access;}
    std::string getUnits(){return m_units;}

    const std::type_info& getValueType(){return m_value.type();}
    template<typename T>
    T getValue() {return std::any_cast<T>(m_value);}
    bool setValue(std::any value) {
        if (m_f != nullptr) {
            if (m_f(this, value)) {
                m_value = value; return true;
            }else return false;
        }
        m_value = value;
        return true;
    }

    std::any getDefValue(){return m_defValue;}

    std::any getMin(){return m_min;}
    std::any getMax(){return m_max;}
    std::any getStep(){return m_step;}
    std::shared_ptr<ValueEnum> getEnum(){return m_valueEnum;}

private:

    std::string m_name;
    std::any m_value;
    std::any m_defValue;
    std::string m_access;
    std::string m_units;
    std::any m_min;
    std::any m_max;
    std::any m_step;
    std::shared_ptr<ValueEnum> m_valueEnum;

    bool (*m_f)(BaseProperty*, std::any);
};

class BaseCommand
{
public:
    BaseCommand(std::string name, std::function<bool()> fn)
        : m_name(name)
        , m_fn(fn)
    {
    };
    ~BaseCommand(){};

    std::string getName(){return m_name;}
    bool execute(){return m_fn();};

private:
    std::string m_name;
    std::function<bool()> m_fn;
};

class SettingsModel
{
public:
    SettingsModel();
    ~SettingsModel();

    /**
     * @brief Method to get string of current version of library.
     * @return String of current library version (format X.Y.Z).
     */
    static std::string getVersion();

    /**
     * @brief help - Method to get general information about all parameters
     * and supported commands.
     * @details The formalized description of the parameter will contain its
     * name, type, access mode, default value, minimum and maximum values,
     * parameter value step.
     * The formalized description of the command will contain its name and
     * description.
     *
     * @return general information about all parameters and commands.
     */
    std::string help();

    /**
     * @brief Method to set property value.
     * @param name Name of property.
     * @param value Value of property.
     * @return TRUE if property is set or FALSE.
     */
    template<typename T>
    bool setProperty(std::string name, T value) {
        if(m_props.find(name) == m_props.end())
            return false;
        return m_props[name]->setValue(value);
    }
    bool setPropertyByKey(std::string name, std::string value);
    bool setProperty(std::pair<std::string, std::any> prop);


    /**
     * @brief Method to get property value.
     * @param name Name of property.
     * @param value Value of property.
     * @return TRUE if property is get or FALSE.
     */
    template<typename T>
    bool getProperty(std::string name, T& value) {
        if(m_props.find(name) != m_props.end()) {
            try { value = m_props[name]->getValue<T>(); }
            catch(...) {
                return false;
            }
            return true;
        }return false;
    }

    /**
     * @brief executeCommand - Method to execute supported command.
     * @param name Name of command
     * @return TRUE if the command was executed, or FALSE.
     */
    bool executeCommand(std::string name);


    std::map<std::string, std::shared_ptr<BaseProperty>>& getProperties(){return m_props;};
    std::map<std::string, std::shared_ptr<BaseCommand>>& getCommands(){return m_commands;};

protected:

    void addProperty(std::string name, std::any value, std::string units = "", std::string access = "write|read",
                  bool (*f)(BaseProperty*, std::any) = +[](BaseProperty* p, std::any v)
    {
        // check value type
        if (std::type_index(p->getValueType()) != std::type_index(v.type()))
            return false;
        return true;
    }) {
        std::shared_ptr<BaseProperty> _param(new BaseProperty(name, value, access, units, f));
        m_props.insert({name, _param});
    };

    template<typename T>
    void addProperty(std::string name, T value, T min, T max, std::string units = "", std::string access = "write|read",
                  bool (*f)(BaseProperty*, std::any) = +[](BaseProperty* p, std::any v)
    {
        // check value type
        if (std::type_index(p->getValueType()) != std::type_index(v.type()))
            return false;

        // check if value matches limits
        if (std::any_cast<T>(p->getMin()) > std::any_cast<T>(v) ||
                std::any_cast<T>(p->getMax()) < std::any_cast<T>(v))
            return false;

        return true;
    }) {
        std::shared_ptr<BaseProperty> _param(new BaseProperty(name, value, access, units, min, max, f));
        m_props.insert({name, _param});
    };

    template<typename T>
    void addProperty(std::string name, T value, T min, T max, T step, std::string units = "", std::string access = "write|read",
                  bool (*f)(BaseProperty*, std::any) = +[](BaseProperty* p, std::any v)
    {
        // check value type
        if (std::type_index(p->getValueType()) != std::type_index(v.type()))
            return false;

        // check if value matches limits
        if (std::any_cast<T>(p->getMin()) > std::any_cast<T>(v) ||
                std::any_cast<T>(p->getMax()) < std::any_cast<T>(v))
            return false;

        // check if value matches step
        if (std::any_cast<T>(v) % std::any_cast<T>(p->getStep()) != 0)
            return false;

        return true;
    }) {
        std::shared_ptr<BaseProperty> _param(new BaseProperty(name, value, access, units, min, max, step, f));
        m_props.insert({name, _param});
    };

    template<typename T>
    void addProperty(std::string name, T value, std::shared_ptr<ValueEnum> valueEnum, std::string units = "", std::string access = "write|read",
                bool (*f)(BaseProperty*, std::any) = +[](BaseProperty* p, std::any v)
    {
        // check value type
        if (std::type_index(p->getValueType()) != std::type_index(v.type()))
            return false;

        // check if value matches enum
        if (p->getEnum() != nullptr && p->getEnum()->getItemList<T>().size() != 0){
            bool isOk = false;
            for (auto a : p->getEnum()->getValueList<T>())
                if (std::any_cast<T>(a) == std::any_cast<T>(v)) {
                    isOk = true;
                    break;
                }
            if (!isOk) return false;
        }

        return true;
    }){
        std::shared_ptr<BaseProperty> _param(new BaseProperty(name, value, access, units, valueEnum, f));
        m_props.insert({name, _param});
    };

    void addCommand(std::string name, std::function<bool()> fn);

    std::shared_ptr<BaseProperty>& props(std::string name) {
        return m_props[name];
    }
    std::shared_ptr<BaseCommand>& commands(std::string name) {
        return m_commands[name];
    }

private:
    std::map<std::string, std::shared_ptr<BaseProperty>> m_props;
    std::map<std::string, std::shared_ptr<BaseCommand>> m_commands;

};



}
}

//#define CREATE_ENUM(type, name, ...) \
//    std::shared_ptr<cr::utils::ValueEnum> name = std::shared_ptr<ValueEnum>(new ValueEnum(enums<type>({__VA_ARGS__})))

#define CREATE_ENUM(type, ...) \
    std::shared_ptr<cr::utils::ValueEnum>(std::shared_ptr<ValueEnum>(new ValueEnum(enums<type>({__VA_ARGS__}))))

