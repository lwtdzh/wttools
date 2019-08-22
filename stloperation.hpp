/**
 * Some tools used for handling some containers.
 * Author: LiWentan.
 * First Modified Date: 2019/8/19. 
 */

#ifndef __WTTOOL_STLOPERATION_H_
#define __WTTOOL_STLOPERATION_H_

#include <unordered_map>
#include <pthread.h>
#include <ctime>
#ifdef linux
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#endif
#ifdef WIN32
#include <windows.h>
#endif
#include <sys/time.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <fcntl.h>
#include <utility>
#include <map>
#include <string.h>
#include <atomic>
#include <iostream>

namespace wttool {

/**
 * Split string by token.
 * @param str: The string to be split.
 * @param token: Used as separation character.
 */
static vector<string> splitstr(const string& str, const string& token = " ") {
    vector<string> res;
    size_t next_pos = 0;
    while (true) {
        size_t found = str.find(token, next_pos);
        if (found == string::npos) {
            break;
        }
        if (found == next_pos) {
            next_pos += token.size();
            continue;
        }
        res.push_back(string(str, next_pos, found - next_pos));
        next_pos = found + token.size();
    }
    if (next_pos < str.size()) {
        res.push_back(string(str, next_pos, str.size() - next_pos));
    }
    return res;
}

/**
 * String to number.
 */
static int64_t str2num(const string& str) {
    int64_t num;
    sscanf(str.c_str(), "%ld", &num);
    return num;
}

/**
 * Number to string.
 */
static string num2str(int64_t num) {
    char str[21];
    sprintf(str, "%ld", num);
    return str;
}

/**
 * Return current local time.
 * Format: yyyymmddhhmmss.
 */
static string cur_time() {
    time_t cur_sec;
    std::time(&cur_sec);
    tm local_time;
    localtime_r(&cur_sec, &local_time);
    char res[15];
    sprintf(res, "%04d%02d%02d%02d%02d%02d", local_time.tm_year + 1900,
        local_time.tm_mon + 1, local_time.tm_mday, local_time.tm_hour,
        local_time.tm_min, local_time.tm_sec);
    return res;
}

/**
 * Print the map.
 * E.g., [name]:[Ming].
 */
static string print_map(const std::map<string, string>& in) {
    auto it = in.cbegin();
    stringstream ss;
    while (it != in.cend()) {
        ss << "[" << it->first << "]:[" << it->second << "]\n";
        ++it;
    }
    return ss.str();
}

/**
 * Print the unordered_map.
 * E.g., [name]:[Ming].
 */
static string print_map(const std::unordered_map<string, string>& in) {
    auto it = in.cbegin();
    stringstream ss;
    while (it != in.cend()) {
        ss << "[" << it->first << "]:[" << it->second << "]\n";
        ++it;
    }
    return ss.str();
}

/**
 * Trim string, erase all characters shown by trim_char in the string.
 */
static string trimstr(const string& str, const string& trim_char = "\n\r\t ") {
    string res = str;
    for (size_t i = 0; i < trim_char.size(); ++i) {
        char char_i[2];
        memcpy(char_i, &trim_char[i], 1);
        memcpy(char_i + 1, "\0", 1);
        size_t it = res.find(char_i);
        while (it != string::npos) {
            res.erase(it, 1);
            it = res.find(char_i);
        }
    }
    return res;
}

/**
 * Parse the argc and argv.
 * Format must be [key]=[value].
 * E.g., abc.exe para1=val1 para2=val2 ...
 */
static std::map<string, string> parse_arg(int argc, char** argv) {
    std::map<string, string> res;
    if (argc == 1) {
        return res;
    }
    for (int i = 1; i < argc; ++i) {
        std::vector<string> res_i = splitstr(argv[i], "=");
        if (res_i.size() != 2) {
            continue;
        }
        res[trimstr(res_i[0], " -")] = trimstr(res_i[1], " ");
    }
    return res;
}

/**
 * Time elasp count class.
 */
class TimeStatistic {
public:
    TimeStatistic() {
        begin();
    }
    void begin() {
        gettimeofday(&_begin_call, NULL);
    }

    void end() {
        gettimeofday(&_end_call, NULL);
    }

    uint32_t cost_ms() {
        end();
        return (_end_call.tv_sec - _begin_call.tv_sec) * 1000 + 
                (_end_call.tv_usec - _begin_call.tv_usec) / 1000;
    }
    
    uint32_t cost_us() {
        end();
        return (_end_call.tv_sec - _begin_call.tv_sec) * 1e6 + 
                (_end_call.tv_usec - _begin_call.tv_usec);
    }

private:
    struct timeval _begin_call;
    struct timeval _end_call;
};

} // End namespace wttool.

#endif // End __WTTOOL_STLOPERATION_H_.