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

#include "LibFile.h"

long get_filesize(FILE* file){
    is_file_open(file);

    if(fseek(file, 0, SEEK_END) < 0) return -1;

    long filesize = ftell(file); 
    if(filesize < 0) return -1;


    if(fseek(file, 0, SEEK_SET) < 0) return -1;

    return filesize; 
}

long get_filesize_from_file(const char* file){
    FILE* file_to_open = fopen(file, "r");
    is_file_open(file_to_open);

    if(fseek(file_to_open, 0, SEEK_END) < 0) return -1;

    long filesize = ftell(file_to_open); 
    if(filesize < 0) return -1;


    if(fseek(file_to_open, 0, SEEK_SET) < 0) return -1;

    fclose(file_to_open);
    return filesize;
}

void is_file_open(FILE* file_to_open){
    if(file_to_open == NULL){
        fprintf(stderr, "[ERROR] Could not open: %s\n", strerror(errno));
        return;
    }
}

char* read_buffer_file(const char* file, size_t nelem){
    FILE* fp = fopen(file, "rb");
    is_file_open(fp);

    char* internal_buffer = (char*)calloc(nelem + 1, sizeof(char));
    if(internal_buffer == NULL){
        fprintf(stderr, "[ERROR] Could not allocate memory\n");
        return NULL;
    }

    if(!fread(internal_buffer, nelem, 1, fp)){
        fprintf(stderr, "[ERROR] Could not read file:%s\n", file);
        return NULL;
    }

    fclose(fp);

    return internal_buffer;
}

char* read_entire_file(const char* file){
    FILE* fp = fopen(file, "rb");
    is_file_open(fp);

    size_t filesize = get_filesize(fp);

    char* internal_buffer = (char*)calloc(filesize + 1, sizeof(char));
    if(internal_buffer == NULL){
        fprintf(stderr, "[ERROR] Could not allocate memory\n");
        return NULL;
    }

    if(!fread(internal_buffer, filesize, 1, fp)){
        fprintf(stderr, "[ERROR] Could not read file:%s\n", file);
        return NULL;
    }

    fclose(fp);

    return internal_buffer;
}

//Section CHECK_FILE_TYPE

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
