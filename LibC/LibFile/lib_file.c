/* Libs - LibC/LibFile
 * Copyright (C) 2024  Andrea Michael Maria Molino
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "lib_file.h"

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