#include <DeviceManager/Module.h>

//Module::Module()
//{
//    memcpy(&moduleInfo_.name, "NA", 3);
//    moduleInfo_.command = CMD_NA;
//    moduleInfo_.peripheral = MODULE_PERIPHERAL_NA;
//    moduleInfo_.state = MODULE_STATE_NA;
//    moduleInfo_.value = -1;
//}

//Module::Module(ModuleInfo moduleInfo)
//{
//    memset(&moduleInfo_.name, 0, MAX_MODULE_NAME_LENGTH);
//    cout << "moduleInfo_.name: " << moduleInfo.name << endl;
//    cout << "name length: " << sizeof(moduleInfo.name) << endl;

//    memcpy(&moduleInfo_.name, &moduleInfo.name, strlen(moduleInfo.name));
//    moduleInfo_.command = moduleInfo.command;
//    moduleInfo_.peripheral = moduleInfo.peripheral;
//    moduleInfo_.state = moduleInfo.state;
//    moduleInfo_.value = moduleInfo.value;
//}

//void Module::setName(string name)
//{
//    strcpy(moduleInfo_.name, name.c_str());
//}

//void Module::setValue(int value)
//{
//    moduleInfo_.value = value;
//}

//void Module::setCommand(ModuleCommand command)
//{
//    moduleInfo_.command = command;
//}

//void Module::setPripheral(ModulePeripheral peripheal)
//{
//    moduleInfo_.peripheral = peripheal;
//}

//void Module::setState(ModuleState state)
//{
//    moduleInfo_.state = state;
//}

//const char * Module::getName()
//{
//    return moduleInfo_.name;
//}

//int Module::getValue()
//{
//    return moduleInfo_.value;
//}

//ModulePeripheral Module::getPripheral()
//{
//    return moduleInfo_.peripheral;
//}

//ModuleCommand Module::getCommand()
//{
//    return moduleInfo_.command;
//}

//ModuleState Module::getState()
//{
//    return moduleInfo_.state;
//}
