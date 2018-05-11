#include <InterProcess/InterProcess.h>

InterProcess::InterProcess(string segmentName, const unsigned int size)
    : segmentName_(segmentName.c_str()),
      size_(size),
      isPersistence_(false)
{

}

InterProcess::~InterProcess()
{
    std::cout << "Decontruct InterProcess\n" << endl;

    if(isPersistence_)
        removeSegment();
}

void InterProcess::createSegment()
{
    if(isPersistence_ == false)
    {
        boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only,
                                                           segmentName_,
                                                           size_);
        isPersistence_ = true;
    }
}

void InterProcess::openSegment()
{
    if(isPersistence_)
    {
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only,
                                                           segmentName_);
    }
    else
        cout << "Segment not exist\n";
}

size_t InterProcess::getSize()
{
    if(isPersistence_)
    {
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only,
                                                           segmentName_);
        return segment.get_size();
    }
    return 0;
}

size_t InterProcess::getFreeMemory()
{
    if(isPersistence_)
    {
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only,
                                                           segmentName_);
        return segment.get_free_memory();
    }
    return 0;
}

void InterProcess::removeSegment()
{
    if(isPersistence_)
    {
        shared_memory_object::remove(segmentName_);
        isPersistence_ = false;
    }
}

bool InterProcess::isPersistence()
{
    return isPersistence_;
}

