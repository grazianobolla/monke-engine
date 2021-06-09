#include "file.h"
#include "log.h"

#include <fstream>
#include <sstream>

bool mk::get_file(const char *path, std::string &dest)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream src_stream;
        src_stream << file.rdbuf();
        file.close();

        dest = src_stream.str();
        return true;
    }
    catch (std::ifstream::failure e)
    {
        log_info("couldnt retrieve file " << path);
        return false;
    }

    return false;
}