#pragma once

#include "../hook/hook.h"

class c_hash_fnv {
public:
    static __forceinline constexpr unsigned long hash(const char* const str) {
        unsigned long ret = 0x811C9DC5u;
        int len = 0;

        while (str[len++] != '\0');

        for (int n = 0; n < len; n++)
            ret = ((ret ^ str[n]) * 0x1000193);

        return ret;
    }
};

#define hash_fnv(s) c_hash_fnv::hash(s)