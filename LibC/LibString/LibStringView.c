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

#include "LibStringView.h"
#include <stdio.h>

String_View sv_append(const char* string){
    String_View string_to_append = {0};
    
    if(string == NULL) {
        string_to_append.string = "";
        string_to_append.size = 1;
        return string_to_append;
    }
    
    string_to_append.string = string;
    string_to_append.size = strlen(string);

    return string_to_append;
}

char* sv_to_cstr(String_View sv){
    char* sv_buffer = (char*)calloc(sv.size + 1, sizeof(char));
    if(sv_buffer == NULL) return NULL;

    strcpy(sv_buffer, sv.string);
    sv_buffer[sv.size] = '\0';
    
    return sv_buffer;
}

bool sv_cmp(String_View sv, String_View sv2){

    //Avoid wasting time on compare
    if(sv.size != sv2.size){
        return false;
    }

    for(size_t i = 0; i < sv.size; i++){
        if(sv.string[i] != sv2.string[i])
            return false;
    }
    
    return true;
}

String_View sv_trim_left(String_View sv){
    size_t space_counter = 0;

    for(size_t i = 0; i < sv.size; i++){

        if(isspace(sv.string[i]) != 0)
            space_counter++;
        
        if(isspace(sv.string[i]) == 0)
            break;
        
    }

    return sv_append(&sv.string[space_counter]);
}