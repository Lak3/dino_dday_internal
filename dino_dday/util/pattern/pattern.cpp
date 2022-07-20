#include "pattern.h"

#define inrange(x, a, b) (x >= a && x <= b)
#define get_bits(x)		 (inrange((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (inrange(x,'0','9') ? x - '0' : 0))
#define get_bytes(x)	 (get_bits(x[0]) << 4 | get_bits(x[1]))

unsigned long c_pattern::find(const char* const mod, const char* const pattern) {
    const unsigned long dwmod = reinterpret_cast<unsigned long>(GetModuleHandleA(mod));

    if (!dwmod)
        return 0x0;

    const image_nt_headers32* nth = reinterpret_cast<image_nt_headers32*>(dwmod + reinterpret_cast<image_dos_header*>(dwmod)->e_lfanew);

    if (!nth)
        return 0x0;

    return find_internal((dwmod + nth->optional_header.base_of_code), (dwmod + nth->optional_header.size_of_code), pattern);
}

unsigned long c_pattern::find_internal(const unsigned long addr, const unsigned long len, const char* const pattern) {
    const char*   patt        = pattern;
    unsigned long first_match = 0u;

    for (unsigned long cur = addr; cur < len; cur += 1u) {
        if (!patt)
            return first_match;

        const unsigned char cur_byte  = *(unsigned char*)cur;
        const unsigned char byte_patt = *(unsigned char*)patt;

        if ((byte_patt == '\?') || (cur_byte == get_bytes(patt))) {
            if (!first_match)
                first_match = cur;

            if (!patt[2])
                return first_match;

            patt += ((byte_patt == '\?\?') || (byte_patt != '\?')) ? 3u : 2u;
        }
        else {
            patt        = pattern;
            first_match = 0u;
        }
    }

    return 0u;
}