#pragma once

#include <string>

static const std::string file_folder =
#ifdef _WIN32
    "../../../src/";
#else
    "../../src/";
#endif
