#include <iostream>
#include <map>

#include "SettingsModel.h"
using namespace cr::utils;


class TestDevice : public SettingsModel
{
public:
    TestDevice(){
        // add simple property with default value
        addProperty("TestBool", (bool)false);
        // add property with default value and limits (value|min|max)
        addProperty("TestDouble", (double)10.0, (double)0.0, (double)100.0);
        // add property with default value, limits and step (value|min|max|step)
        addProperty("TestInt1", (int)10, (int)0, (int)100, (int)2);
        // add property with default value and enum (value|enum)
        addProperty("TestInt2", (int)0, CREATE_ENUM(int, {0, "zero", "0"},{1, "one", "1"}));

        addCommand("TestCommand", [&](){return this->testMethod();});

    }
    ~TestDevice(){};

    bool testMethod()
    {
        std::cout << "test command was executed!" << std::endl;
        return true;
    }
};


// Entry point.
int main(void)
{
    std::cout<<"=================================================" << std::endl;
    std::cout<<"SettingsModel " << SettingsModel::getVersion()     << std::endl;
    std::cout<<"=================================================" << std::endl;

    bool result;
    bool testBool;
    double testDbl;
    int testInt1;
    int testInt2;
    int unknown;
    TestDevice device;

    std::cout << device.help() << std::endl;



    ///
    /// Examples of API using (safe)
    ///

    // Set property examples
    result = device.setProperty("TestBool", (bool)true);     // return true
    result = device.setProperty("TestBool", 2);              // return false
    result = device.setProperty("TestDouble", (double)50.0); // return true
    result = device.setProperty("TestDouble", (double)101.0);// return false
    result = device.setProperty("TestInt1", (int)10);        // return true
    result = device.setProperty("TestInt1", (int)11);        // return false
    result = device.setProperty("TestInt2", 0);              // return true
    result = device.setPropertyByKey("TestInt2", "one");     // return true
    result = device.setPropertyByKey("TestInt2", "two");     // return false
    result = device.setProperty("Unknown", 42);              // return false

    // Get property examples
    result = device.getProperty("TestBool", testBool);       // testBool = true
    result = device.getProperty("TestDouble", testDbl);      // testDouble= 50.0
    result = device.getProperty("TestInt1", testInt1);       // testInt1 = 10
    result = device.getProperty("TestInt2", testInt2);       // testInt2 = 1
    result = device.getProperty("Unknown", unknown);         // return false

    // Run command example
    result = device.executeCommand("TestCommand");           // return true
    result = device.executeCommand("Unknown");               // return false



    ///
    /// Examples of alternative API using (more convenient but unsafe)
    ///

    // Set property examples
    result = device.props("TestBool")->setValue(true);       // return true
    result = device.props("TestBool")->setValue(2);          // return false
    result = device.props("TestDouble")->setValue(50.0);     // return true
    result = device.props("TestDouble")->setValue(101.0);    // return false
    result = device.props("TestInt1")->setValue(10);         // return true
    result = device.props("TestInt1")->setValue(11);         // return false
    result = device.props("TestInt2")->setValue(1);          // return true
    result = device.props("TestInt2")->setValue(2);          // return false

    // Get property examples
    testBool = device.props("TestBool")->getValue<bool>();   // testBool = true
    testDbl = device.props("TestDouble")->getValue<double>();// testDouble= 50.0
    testInt1 = device.props("TestInt1")->getValue<int>();    // testInt1 = 10
    testInt2 = device.props("TestInt2")->getValue<int>();    // testInt2 = 1

    // Run command example
    result = device.commands("TestCommand")->execute();      // return true

    // Segmentation fault (core dumped) and runtime exception in Set/Get and Execute examples
    //result = device.props("Unknown")->setValue(42);      // Exception!!! Property not exist.
    //unknown = device.props("Unknown")->getValue<int>();  // Exception!!! Property not exist
    //testBool = device.props("TestBool")->getValue<int>();// Exception!!! Wrong type conversion
    //result = device.commands("Unknown")->execute();      // Exception!!! Command not exist



    ///
    /// Examples of using the API through the communication channel
    ///

    return 1;
}
