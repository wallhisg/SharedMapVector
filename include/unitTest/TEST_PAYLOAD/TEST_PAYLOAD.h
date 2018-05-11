#ifndef TEST_PAYLOAD_H
#define TEST_PAYLOAD_H

#include <PayLoad/PayLoad.h>

class TEST_PAYLOAD
{
public:
    TEST_PAYLOAD();
    PayLoad getPayLoad();
private:
    PayLoad payLoad_;
};

#endif // TEST_PAYLOAD_H
