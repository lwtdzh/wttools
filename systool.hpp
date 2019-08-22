/**
 * Some system tools.
 * Author: LiWentan.
 * First Modified Date: 2019/8/19. 
 */
 
#ifndef __WTTOOL_SYSTOOL_H_
#define __WTTOOL_SYSTOOL_H_

#include <iostream>

#define MEMCPY_MAX_LENGTH 10240000
#define toscreen std::cout<<__FILE__<<", "<<__LINE__<<": "
// typedef int16_t short;
// typedef int32_t int
// typedef int64_t long long
// typedef uint16_t unsigned short
// typedef uint32_t unsigned int
// typedef uint64_t unsigned long long

namespace wttool {
    
static void wtmemcpy(void* des, void* src, size_t length) {
    static char buffer[MEMCPY_MAX_LENGTH];
    if (length > MEMCPY_MAX_LENGTH) {
        toscreen << "Wtmemcpy is out the capacity.\n";
        return;
    }
    memcpy(buffer, src, length);
    memcpy(des, buffer, length);
    return;
}
    
} // End namespace wttool.

#endif // End ifdef __WTTOOL_SYSTOOL_H_.
