#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <string>

using namespace std;

#define PAYLOAD_CONTROL_PROTOCOL            0x00

// Define PayLoad control
// 4 byte
typedef enum {
    PAYLOAD_CONTROL_PROTOCOL_TCP = 1,
    PAYLOAD_CONTROL_PROTOCOL_RF = 2,
    PAYLOAD_CONTROL_PROTOCOL_BLUETOOTH = 3
} ControlProtocol;

typedef enum {
    PAYLOAD_CONTROL_INTERFACE_GPIO,
    PAYLOAD_CONTROL_INTERFACE_ADC,
    PAYLOAD_CONTROL_INTERFACE_SPI,
    PAYLOAD_CONTROL_INTERFACE_UART
} ControlInterface;

typedef enum {
    READ,
    WRITE,
    SET,
    CLEAR,
    GET,
    TOGGLE,
    ENABLE,
    DISABLE
} ControlCommand;

typedef enum {

} ControlReserve;

typedef struct {
    ControlProtocol protocol;
    ControlInterface interface;
    ControlCommand command;
    ControlReserve reserve;
} PayLoadControl;

ControlProtocol getPayLoadProtocol(PayLoadControl plControl);
ControlInterface getPayLoadInterface(PayLoadControl plControl);
ControlCommand getPayLoadCommand(PayLoadControl plControl);

// Define PayLoad data
//
// ID:00:1B:44:11:3A:B7
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

typedef struct {
    char vid[5];
//    char pid[5];
} Identifier;

typedef struct {

} BlockInfo;


typedef struct {
    HwAddress address;
    Identifier identifier;
    BlockInfo block;
} PayLoadData;

typedef struct {
    Identifier id;
} DeviceInfo;

//DeviceInfo getDeviceInfo(PayLoadData plData);

// Define PayLoad
typedef struct {
    PayLoadControl control;
    PayLoadData data;
} PayLoad;

PayLoadControl getPayLoadControl(PayLoad payload);
PayLoadData getPayLoadData(PayLoad payload);

#endif // PAYLOAD_H
