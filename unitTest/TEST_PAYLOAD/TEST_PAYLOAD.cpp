#include <unitTest/TEST_PAYLOAD/TEST_PAYLOAD.h>

TEST_PAYLOAD::TEST_PAYLOAD()
{
    PayLoadControl plControl;
    plControl.protocol = PAYLOAD_CONTROL_PROTOCOL_TCP;
    plControl.interface = PAYLOAD_CONTROL_INTERFACE_GPIO;
    plControl.command = ControlCommand(ControlCommand::READ);

    payLoad_.control = plControl;
}

PayLoad TEST_PAYLOAD::getPayLoad()
{
    return payLoad_;
}
