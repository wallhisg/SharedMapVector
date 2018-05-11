#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <vector>
#include <functional>
#include <DeviceManager/Box.h>
#include <unitTest/Debug.h>

using namespace boost::interprocess;

#define MAX_NO_OF_CHAR_ARRAY    32

struct CharArray
{
   CharArray(char in[5]) { memcpy(data, in, 5); }
   char& operator[](unsigned int idx) { return data[idx]; }
   bool operator<(unsigned int idx) { return data[idx]; }
   char data[5];
};

#define SHARED_MEMORY_NAME_BOX  "SHM_BOXES"

template <typename TypeOne, typename TypeTwo>
class SharedMemoryMap
{
public:
    typedef TypeOne KeyType;
    typedef TypeTwo MappedType;
    typedef std::pair<const TypeOne, TypeTwo> ValueType;
    typedef allocator<ValueType, managed_shared_memory::segment_manager> ShmemAllocator;
    typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> SharedMap;
    typedef boost::interprocess::interprocess_upgradable_mutex upgradable_mutex_type;

    typedef std::map<TypeOne, TypeTwo> Map;

    SharedMemoryMap(std::string sharedMemoryName, size_t size)
    {
        sharedMemoryName_ = sharedMemoryName;
        sharedMemoryNameObject_ = sharedMemoryName + "Object";
        size_ = size;
    }

#if(DEBUG_INTERPROCESS)
    // Enable when run time
    ~SharedMemoryMap()
    {
        if(isPersistence_)
        {
            shared_memory_object::remove(sharedMemoryName_.c_str());
        }
    }
#endif
    void createSharedMemoryMap()
    {
        shared_memory_object::remove(sharedMemoryName_.c_str());

        managed_shared_memory segment(create_only ,sharedMemoryName_.c_str(), size_);

        ShmemAllocator alloc_inst(segment.get_segment_manager());

        sharedMap_ = segment.construct<SharedMap>(sharedMemoryNameObject_.c_str())(std::less<TypeOne>(),
                                                                                   alloc_inst);

        isPersistence_ = true;
    }

    void insert(ValueType valueType)
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedMap *, std::size_t> find_res = segment.find<SharedMap>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find `theSharedData'.\n";
            return;
        }

        SharedMap &map = *find_res.first;

        map.insert(valueType);
    }

    bool getItem(TypeTwo &result, TypeOne k) const
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedMap *, std::size_t> find_res = segment.find<SharedMap>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find `theSharedData'.\n";
            return false;
        }

        SharedMap &map = *find_res.first;
        typename SharedMap::const_iterator pos = map.find(k);
        if(pos != map.end())
        {
            result = pos->second;
            return true;
        }

        return false;
    }

    bool getMap(Map &map)
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedMap *, std::size_t> find_res = segment.find<SharedMap>(sharedMemoryNameObject_.c_str());

        if (!find_res.first)
        {
            std::cerr << "Failed to find `theSharedData'.\n";
            return false;
        }

        SharedMap &sharedMap = *find_res.first;
        map.insert(sharedMap.begin(), sharedMap.end());

        return true;
    }

    size_t getFreeMemory()
    {
        boost::interprocess::scoped_lock<upgradable_mutex_type> lock(mutex);
        managed_shared_memory segment(open_only, sharedMemoryName_.c_str());
        std::pair<SharedMap *, std::size_t> find_res = segment.find<SharedMap>(sharedMemoryNameObject_.c_str());

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
        std::pair<SharedMap *, std::size_t> find_res = segment.find<SharedMap>(sharedMemoryNameObject_.c_str());

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
    SharedMap *sharedMap_;
    Map map_;
    std::string sharedMemoryName_;
    std::string sharedMemoryNameObject_;
    size_t size_;

    mutable upgradable_mutex_type mutex;
    bool isPersistence_ = false;
};



#endif // SHAREDMEMORY_H
