#pragma once

#include "../math/math.h"

class c_pattern {
public:
	unsigned long find(const char* const mod, const char* const pattern);

private:
	unsigned long find_internal(const unsigned long addr, const unsigned long len, const char* const pattern);

private:
    struct image_data_directory {
        unsigned long virtual_address;
        unsigned long size;
    };

    struct image_file_header {
        unsigned short machine;
        unsigned short number_of_sections;
        unsigned long time_date_stamp;
        unsigned long pointer_to_symbol_table;
        unsigned long number_of_symbols;
        unsigned short size_of_optional_header;
        unsigned short characteristics;
    };

    struct image_dos_header {
        unsigned short e_magic;
        unsigned short e_cblp;
        unsigned short e_cp;
        unsigned short e_crlc;
        unsigned short e_cparhdr;
        unsigned short e_minalloc;
        unsigned short e_maxalloc;
        unsigned short e_ss;
        unsigned short e_sp;
        unsigned short e_csum;
        unsigned short e_ip;
        unsigned short e_cs;
        unsigned short e_lfarlc;
        unsigned short e_onvo;
        unsigned short e_res[4];
        unsigned short e_oemid;
        unsigned short e_oeminfo;
        unsigned short e_res2[10];
        long           e_lfanew;
    };

    struct image_optional_header32 {
        unsigned short magic;
        unsigned char major_linker_version;
        unsigned char minor_linker_version;
        unsigned long size_of_code;
        unsigned long size_of_initialized_data;
        unsigned long size_of_uninitialized_data;
        unsigned long address_of_entry_point;
        unsigned long base_of_code;
        unsigned long base_of_data;
        unsigned long image_base;
        unsigned long section_alignment;
        unsigned long file_alignment;
        unsigned short major_operating_system_version;
        unsigned short minor_operating_system_version;
        unsigned short major_image_version;
        unsigned short minor_image_version;
        unsigned short major_subsystem_version;
        unsigned short minor_subsystem_version;
        unsigned long win32_version_value;
        unsigned long size_of_image;
        unsigned long size_of_headers;
        unsigned long checksum;
        unsigned short subsystem;
        unsigned short dll_characteristics;
        unsigned long size_of_stack_reserve;
        unsigned long size_of_stack_commit;
        unsigned long size_of_heap_reserve;
        unsigned long size_of_heap_commit;
        unsigned long loader_flags;
        unsigned long number_of_rva_and_sizes;
        image_data_directory data_directory[16];
    };

    struct image_nt_headers32 {
        unsigned long signature;
        image_file_header file_header;
        image_optional_header32 optional_header;
    };
};