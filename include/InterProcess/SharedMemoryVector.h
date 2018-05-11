#ifndef SHAREDMEMORYVECTOR_H
#define SHAREDMEMORYVECTOR_H


#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <vector>
#include <functional>
#include <algorithm>

#include <DeviceManager/Box.h>
#include <unitTest/Debug.h>

using namespace boost::interprocess;

#define MAX_NO_OF_VECTOR    10

typedef struct Event
{
//    char str[10];
    int value;

    bool operator<(const Event& a) const
    {
        return value < a.value;
    }
} Event;

template <typename TypeOne>
class SharedMemoryVector
{
public:
    typedef allocator<TypeOne, managed_shared_memory::segment_manager> ShmemAllocator;
    typedef vector<TypeOne, ShmemAllocator> SharedVector;
    typedef boost::interprocess::interprocess_upgradable_mutex upgradable_mutex_type;

    typedef std::vector<TypeOne> Vector;

    SharedMemoryVector(std::string sharedMemoryName, size_t size)
    {
        sharedMemoryName_ = sharedMemoryName + "Vector";
        sharedMemoryNameObject_ = sharedMemoryName + "VectorObject";
        size_ = size;
    }

    // Enable when run time
#if (DEBUG_INTERPROCESS)
    ~SharedMemoryVector()
    {
        if(isPersistence_)
        {
            shared_memory_object::remove(sharedMemoryName_.c_str());
        }
    }
#endif

    bool compareByLength(const Event &lhs, const Event &rhs)
    {
        return lhs.value < rhs.value;
    }
    void createSharedMemoryVector()
    {
        shared_memory_object::remove(sharedMemoryName_.c_str());

        managed_shared_memory segment(create_only ,sharedMemoryName_.c_str(), size_);

        ShmemAllocator alloc_inst(segment.get_segment_manager());

        SharedVector_ = segment.construct<SharedVector>(sharedMemoryNameObject_.c_str())(alloc_inst);

        isPersistence_ = true;
    }

    void push_back(TypeOne t)
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedVector *, std::size_t> find_res = segment.find<SharedVector>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find `theSharedData'.\n";
            return;
        }

        SharedVector &vector = *find_res.first;

        vector.push_back(t);
    }

    bool getVector(Vector &vector)
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedVector *, std::size_t> find_res = segment.find<SharedVector>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find `theSharedData'.\n";
            return false;
        }

        SharedVector &vector_ = *find_res.first;

//        typename SharedVector::iterator it();

        for(typename SharedVector::iterator it = vector_.begin(); it != vector_.end(); it++)
        {
            vector.push_back(*it);
        }
        std::sort(vector.begin(), vector.end());
        std::cout << "size = " << vector.size() << std::endl;
        return true;
    }

    size_t getFreeMemory()
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedVector *, std::size_t> find_res = segment.find<SharedVector>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find `theSharedData'.\n";
            isPersistence_ = false;
            return 0;
        }
        else
        {
            isPersistence_ = true;
            return segment.get_free_memory();
        }

    }

    size_t getSize()
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedVector *, std::size_t> find_res = segment.find<SharedVector>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find "  << sharedMemoryNameObject_.c_str() << std::endl;
            isPersistence_ = false;
            return 0;
        }
        else
        {
            isPersistence_ = true;
            return segment.get_size();
        }

    }

    bool isPersistence()
    {
        return isPersistence_;
    }

private:
    SharedVector *SharedVector_;
//    std::vector<TypeOne> vector;
    std::string sharedMemoryName_;
    std::string sharedMemoryNameObject_;
    size_t size_;

    mutable upgradable_mutex_type mutex;
    bool isPersistence_ = false;
};



#endif // SHAREDMEMORYVECTOR_H
