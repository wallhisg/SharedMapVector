#ifndef IPC_H
#define IPC_H

#include <iostream>
#include <cassert>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <InterProcess/SharedMemoryMap.h>
#include <InterProcess/SharedMemoryVector.h>

#include <PayLoad/PayLoad.h>

using namespace std;
using namespace boost::interprocess;

class InterProcess
{
public:
    InterProcess(string segmentName, const unsigned int size);
    ~InterProcess();
    void createSegment();
    void openSegment();
    size_t getSize();
    size_t getFreeMemory();
    void removeSegment();
    bool isPersistence();
private:
    const char *segmentName_;
    unsigned int size_;
    boost::interprocess::managed_shared_memory segment_;
    bool isPersistence_ = false;

};
#endif // IPC_H
