#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>
#include <iostream>

#include <InterProcess/SharedMemoryMap.h>
#include <InterProcess/SharedMemoryVector.h>
#include <DeviceManager/Box.h>

int main ()
{
    using namespace boost::interprocess;

    try
    {

        std::cout << "TEST SHARED MAP" << std::endl;
        SharedMemoryMap<int, Box> sharedMemoryMap("MyBox", 65536);

        typedef std::map<int, Box> BoxMap;
        BoxMap map_;
        if(sharedMemoryMap.getMap(map_))
        {
            for(BoxMap::const_iterator i = map_.begin(); i != map_.end(); ++i)
            {
                std::cout << i->second.info.address.value << std::endl;
            }
            size_t freeMem = sharedMemoryMap.getFreeMemory();
            std::cout << "freeMem: " << freeMem << std::endl;
            size_t sizeMem = sharedMemoryMap.getSize();
            std::cout << "sizeMem: " << sizeMem << std::endl;
        }

        std::cout << "TEST SHARED VECTOR" << std::endl;

//        Event event;
//        memcpy(&event.str, "abcd\n", 6);
        SharedMemoryVector<Event> sharedMemoryVector("MyVector", 65536);

        typedef std::vector<Event> Vector;
        Vector vector;
        if(sharedMemoryVector.getVector(vector))
        {
            Vector::iterator it = vector.begin();
            while(it++ != vector.end())
            {
//                std::cout << "nstr = " << (*it).str << std::endl;
                std::cout << "nvalue = " << (*it).value << std::endl;
            }
            size_t freeMem = sharedMemoryVector.getFreeMemory();
            std::cout << "freeMem: " << freeMem << std::endl;
            size_t sizeMem = sharedMemoryVector.getSize();
            std::cout << "sizeMem: " << sizeMem << std::endl;

        }
//        shared_memory_object::remove("MyVector");
    }
    catch(std::exception &e)
    {
        std::cout<<" error  " << e.what() <<std::endl;
        shared_memory_object::remove("MyBox");
        shared_memory_object::remove("MyVectorVectorObject");
    }

    return 0;

}
