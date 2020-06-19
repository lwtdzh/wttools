/**
 * Comparison functions.
 * If return < 0, lhs < rhs.
 * If return == 0, lhs == rhs.
 * If return > 0, lhs > rhs. 
 * Author: LiWentan.
 * First Modified Date: 2019/8/19. 
 */

#ifndef __WTTOOL_COMPARE_H_
#define __WTTOOL_COMPARE_H_

#include <iostream>

namespace wttool {

using namespace std;

/**
 * Default comparison functions.
 */
template <typename T>
static int cmp(const T& lhs, const T& rhs) {
    size_t t_size = sizeof(T);
    if (t_size >= sizeof(int)) {
        int& lhs_num = *(int*)lhs;
        int& rhs_num = *(int*)rhs;
        if (lhs_num < rhs_num) {
            return -1;
        }
        if (lhs_num == rhs_num) {
            return 0;
        }
        return 1;
    }
    char& lhs_chr = *(char*)lhs;
    char& rhs_chr = *(char*)rhs;
    if (lhs_chr < rhs_chr) {
        return -1;
    }
    if (lhs_chr == rhs_chr) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for int64.
 */
template <>
int cmp(const int64_t& lhs, const int64_t& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for int32.
 */
template <>
int cmp(const int32_t& lhs, const int32_t& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for int16.
 */
template <>
int cmp(const int16_t& lhs, const int16_t& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for int8.
 */
template <>
int cmp(const char& lhs, const char& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}    

/**
 * Comparison function for uint64.
 */
template <>
int cmp(const uint64_t& lhs, const uint64_t& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for uint32.
 */
template <>
int cmp(const uint32_t& lhs, const uint32_t& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for uint16.
 */
template <>
int cmp(const uint16_t& lhs, const uint16_t& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}

/**
 * Comparison function for uint8.
 */
template <>
int cmp(const unsigned char& lhs, const unsigned char& rhs) {
    if (lhs < rhs) {
        return -1;
    } else if (lhs == rhs) {
        return 0;
    }
    return 1;
}    

/**
 * Comparison function for string.
 */
template <>
int cmp(const string& lhs, const string& rhs) {
    size_t length = (lhs.size() > rhs.size()) ? rhs.size() : lhs.size();
    for (size_t i = 0; i < length; ++i) {
        if (lhs[i] == rhs[i]) {
            continue;
        }
        return lhs[i] - rhs[i];
    }
    if (lhs.size() == rhs.size()) {
        return 0;
    }
    if (length == lhs.size()) {
        return -1;
    } else {
        return 1;
    }
}

} // End namespace wttool.

#endif // End ifdef __WTTOOL_COMPARE_H_.
