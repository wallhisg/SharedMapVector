#ifndef BOX_H
#define BOX_H


#include <vector>
#include <DeviceManager/Module.h>
//using namespace std;

#define MAX_BOX_NAME_LENGTH         32
#define MAX_NO_OF_MODULE_IN_BOX     8
typedef enum {
    BOX_PROTOCOL_TCP = 1,
    BOX_PROTOCOL_RF = 2,
    BOX_PROTOCOL_BLUETOOTH = 3
} BoxProtocol;

typedef struct
{
    char type[2];
    char address[18];
} MacAddress;

typedef struct
{
    char type[2];
    char address[18];
} RfAddress;

typedef struct
{
    char type[2];
    char address[18];
} BluetoothAddress;


typedef union {
    MacAddress mac;
    RfAddress rf;
    BluetoothAddress bluetooth;
    char value[20];
} HwAddress;

// Mo ta du lieu Box
typedef struct {
    BoxProtocol protocol;
    HwAddress address;
    char name[MAX_BOX_NAME_LENGTH];
} BoxInfo;

// Mo ta cac module co trong Box
//typedef struct {
//    uint8_t noOfModule;
//    Module module;
//} BoxModules;

// typedef struct {
//     vector<Module> modules;
//     BoxData info;
// } Box;

typedef struct {
    BoxInfo info;
    ModuleInfo modules[MAX_NO_OF_MODULE_IN_BOX];
} Box;

//class Box
//{
//public:
//    Box();


//private:
//    char name[MAX_BOX_NAME_LENGTH];
//    BoxProtocol protocol;
//    HwAddress address;
////    vector<Module> module;
//};

#endif // BOX_H
