#ifndef __EXECUTABLE_TYPE__H
#define __EXECUTABLE_TYPE__H

#include <iostream>

namespace lifter {

class ExecutableType {
public:
    enum class BinaryType {
        ELF = 0, PE = 1, MACH_O = 2, OTHER = 3, ERROR = 255
    };

    static BinaryType getBinaryType(const std::string& file_path);
};

}   // namesapce lifter


#endif