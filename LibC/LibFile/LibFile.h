/*
 * MIT License
 *
 * Copyright (c) 2024 Andrea Michael M. Molino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

long get_filesize(FILE* file);
long get_filesize_from_file(const char* file);
bool is_file_open(FILE* file_to_open);

char* read_buffer_file(const char* file, size_t nelem);
char* read_entire_file(const char* file);

bool write_entire_file(const char* file, void* data, size_t size);
bool write_zero_file(const char* file, size_t size);

bool is_file_elf(const char* file);
bool is_file_png(const char* file);
bool is_file_pdf(const char* file);
bool is_file_jpg(const char* file);

#ifdef CHECK_FILE_TYPE_IMPLEMENTATION

bool is_file_elf(const char* file){
    const uint8_t elf_magic_number[4] = { 0x7F, 0x45, 0x4C, 0x46};
    
    char* buffer_elf_file = read_buffer_file(file, 4);

    if(buffer_elf_file == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    if(memcmp(buffer_elf_file, elf_magic_number, 4) == 0){
        free(buffer_elf_file);
        return true;
    }

    free(buffer_elf_file);
    return false;
}

bool is_file_png(const char* file){
    const uint8_t png_magic_number[8]         = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    const uint8_t png_magic_number_variant[8] = {0x50, 0x89, 0x47, 0x4E, 0x0A, 0x0D, 0x0A, 0x1A};

    char* buffer_png_file = read_buffer_file(file, 8);
    
    if(buffer_png_file == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    if(memcmp(buffer_png_file, png_magic_number, 8) == 0){
        free(buffer_png_file);
        return true;
    }

    if(memcmp(buffer_png_file, png_magic_number_variant, 8) == 0){
        free(buffer_png_file);
        return true;
    }

    free(buffer_png_file);
    return false;
}

bool is_file_pdf(const char* file){
    const uint8_t pdf_magic_number[5] = {0x25, 0x50, 0x44, 0x46, 0x2D};

    char* buffer_pdf_file = read_buffer_file(file, 5);

    if(buffer_pdf_file == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    if(memcmp(buffer_pdf_file, pdf_magic_number, 5) == 0){
        free(buffer_pdf_file);
        return true;
    }

    free(buffer_pdf_file);
    return false;
}

bool is_file_jpg(const char* file){
    const uint8_t jpg_magic_number[12] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00, 0x01};
    
    char* buffer_jpg_file = read_buffer_file(file, 12);

    if(buffer_jpg_file == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    if(memcmp(buffer_jpg_file, jpg_magic_number, 12) == 0){
        free(buffer_jpg_file);
        return true;
    }
    free(buffer_jpg_file);
    
    const uint8_t jpg_magic_number_variant[4]   = {0xFF, 0xD8, 0xFF, 0xEE};
    char* buffer_jpg_file_2 = read_buffer_file(file, 4);
    
    if(buffer_jpg_file_2 == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    if(memcmp(buffer_jpg_file_2, jpg_magic_number_variant, 4) == 0){
        free(buffer_jpg_file_2);
        return true;
    }
    free(buffer_jpg_file_2);


    const uint8_t jpg_magic_number_variant2[4]  = {0xFF, 0xD8, 0xFF, 0xE0};
    char* buffer_jpg_file_3 = read_buffer_file(file, 4);

    if(buffer_jpg_file_3 == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    if(memcmp(buffer_jpg_file_3, jpg_magic_number_variant2, 4) == 0){
        free(buffer_jpg_file_3);
        return true;
    }
    free(buffer_jpg_file_3);


    const uint8_t jpg_magic_number_variant3[12] = {0xFF, 0xD8, 0xFF, 0xE1, 0x3F, 0x3F, 0x45, 0x78, 0x69, 0x66, 0x00, 0x00};//0x3F == ? skippable
    char* buffer_jpg_file_4 = read_buffer_file(file, 12);

    if(buffer_jpg_file_4 == NULL){
        fprintf(stderr, "[ERROR] Buffer is NULL\n");
        fprintf(stderr, "[ERROR] Could not identify file\n");
        return false;
    }

    for(int i = 0; i < 12; i++){
        if(buffer_jpg_file_4[i] == 0x3F){
            i++;
        }
        if(memcmp(&buffer_jpg_file_4[i], &jpg_magic_number_variant3[i], 1) != 0){
            return false;
        }
    }
    free(buffer_jpg_file_4);
    return true;

}
#endif