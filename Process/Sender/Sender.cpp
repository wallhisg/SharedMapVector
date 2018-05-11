#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>

#include <InterProcess/SharedMemoryMap.h>
#include <InterProcess/SharedMemoryVector.h>
#include <DeviceManager/Box.h>

int main ()
{
    using namespace boost::interprocess;

    std::cout << "TEST SHARED MAP" << std::endl;
    // Shared memory with INT
    typedef std::pair<const int, Box> ValueType;

    ModuleInfo mdInfo1;
    mdInfo1.value = 1;
    ModuleInfo mdInfo2;
    mdInfo2.value = 2;

    Box box1;
    memcpy(&box1.info.address.value, "123456", 7);
    box1.modules[0] = mdInfo1;

    Box box2;
    memcpy(&box2.info.address.value, "abcdef", 7);
    box2.modules[0] = mdInfo2;

    ValueType value(1,box1);
    ValueType value1(2,box2);

    SharedMemoryMap<int, Box> sharedMemoryMap1("MyBox", 65536);

    sharedMemoryMap1.createSharedMemoryMap();
    sharedMemoryMap1.insert(value);
    sharedMemoryMap1.insert(value1);

    size_t freeMem = sharedMemoryMap1.getFreeMemory();
    std::cout << "freeMem: " << freeMem << std::endl;

    std::cout << "TEST SHARED VECTOR" << std::endl;

    Event event;
    SharedMemoryVector<Event> sharedMemoryVector("MyVector", 65536);
    sharedMemoryVector.createSharedMemoryVector();

//    event.value = 0;
//    sharedMemoryVector.push_back(event);
//    event.value = 1;
//    sharedMemoryVector.push_back(event);
//    event.value = 2;
//    sharedMemoryVector.push_back(event);
//    event.value = 5;
//    sharedMemoryVector.push_back(event);

    for(int i = 1; i < 20; ++i) //Insert data in the vector
    {
        event.value = i;
        std::cout << "nvalue = " << event.value << std::endl;
        sharedMemoryVector.push_back(event);
    }

    return 0;
}
