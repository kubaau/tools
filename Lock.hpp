#pragma once

#include <mutex>
#include "Combine.hpp"

#define LOCK_MTX(mtx) std::lock_guard<std::mutex> LINE_COMBINE(lock){mtx};
#define LOCK_REMTX(mtx) std::lock_guard<std::recursive_mutex> LINE_COMBINE(lock){mtx};
#define LOCK LOCK_MTX(mtx)
#define UNIQUE_LOCK_MTX(name, mtx) std::unique_lock<std::mutex> name{mtx};
#define UNIQUE_LOCK(name) UNIQUE_LOCK_MTX(name, mtx)
