#ifndef MODULE_H
#define MODULE_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>

//using namespace std;

#define MAX_MODULE_NAME_LENGTH      32

typedef enum {
    MODULE_PERIPHERAL_NA,
    MODULE_PERIPHERAL_GPIO,
    MODULE_PERIPHERAL_ADC,
    MODULE_PERIPHERAL_SPI,
    MODULE_PERIPHERAL_UART
} ModulePeripheral;

typedef enum {
    CMD_NA,
    CMD_READ,
    CMD_WRITE,
    CMD_SET,
    CMD_CLEAR,
    CMD_GET,
    CMD_TOGGLE,
    CMD_ENABLE,
    CMD_DISABLE
} ModuleCommand;

typedef enum {
    MODULE_STATE_NA,
    MODULE_STATE_ON,
    MODULE_STATE_OF,
    MODULE_STATE_RUNNING,
    MODULE_STATE_STOP,
    MODULE_STATE_HIBERNATE,
    MODULE_STATE_SUSPEND,
    MODULE_STATE_RESUME
} ModuleState;

typedef struct {
    char name[MAX_MODULE_NAME_LENGTH];
    int value;
    ModuleCommand command;
    ModulePeripheral peripheral;
    ModuleState state;
} ModuleInfo;

//class Module
//{
//public:
//    Module();
//    Module(ModuleInfo moduleInfo);

//    void setName(std::string name);
//    void setValue(int value);
//    void setPripheral(ModulePeripheral peripheal);
//    void setCommand(ModuleCommand command);
//    void setState(ModuleState state);

//    const char *getName();
//    int getValue();
//    ModulePeripheral getPripheral();
//    ModuleCommand getCommand();
//    ModuleState getState();

//private:
//    ModuleInfo moduleInfo_;
//};

#endif // MODULE_H
