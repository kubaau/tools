#pragma once

#include <chrono>

#include "IoTypedefs.hpp"
#include "Lock.hpp"
#include "Observer.hpp"

class FileChangeNotifier : Observable<FilePath>
{
    using SleepDuration = std::chrono::high_resolution_clock::duration;

public:
    FileChangeNotifier(const FilePath& path, const SleepDuration& sleep)
        : thr{[this] { loop(); }}, path{path}, sleep{sleep}
    {
    }

    ~FileChangeNotifier()
    {
        LOCK(path_mtx);
        path.clear();
        thr.detach();
    }

private:
    void loop()
    {
        using namespace std;
        while (true)
        {
            {
                LOCK;
                if (sleep < SleepDuration::zero())
                    return;
                this_thread::sleep_for(sleep);
            }
        }
    }

    std::thread thr;

    FilePath path;
    mutable std::mutex path_mtx;

    mutable std::mutex mtx;
    SleepDuration sleep;
    std::filesystem::file_time_type last_write;
};

using FileChangeObserver = IObserver<FilePath>;
