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
#include <stdarg.h>

#ifdef __linux__

    #define LOG_SUCCESS  0
    #define LOG_ERROR    1
    #define LOG_INFO     2
    #define LOG_WARNING  3

    #define C_RESET  "\x1B[0m"
    #define C_RED    "\x1B[1;31m"
    #define C_GREEN  "\x1B[1;32m"
    #define C_YELLOW "\x1B[1;33m"
    #define C_BLUE   "\x1B[1;34m"
#elif __WIN32
    #include <windows.h>
    #define WIN32_LEAN_AND_MEAN
    #define NOGDICAPMASKS
    #define NOVIRTUALKEYCODES
    #define NOWINMESSAGES
    #define NOWINSTYLES
    #define NOSYSMETRICS
    #define NOMENUS
    #define NOICONS
    #define NOKEYSTATES
    #define NOSYSCOMMANDS
    #define NORASTEROPS
    #define NOSHOWWINDOW
    #define OEMRESOURCE
    #define NOATOM
    #define NOCLIPBOARD
    #define NOCTLMGR
    #define NODRAWTEXT
    #define NOGDI
    #define NOKERNEL
    #define NOUSER
    #define NONLS
    #define NOMB
    #define NOMEMMGR
    #define NOMETAFILE
    #define NOMINMAX
    #define NOMSG
    #define NOOPENFILE
    #define NOSCROLL
    #define NOSERVICE
    #define NOSOUND
    #define NOTEXTMETRIC
    #define NOWH
    #define NOWINOFFSETS
    #define NOCOMM
    #define NOHELP
    #define NOPROFILER
    #define NODEFERWINDOWPOS
    #define NOMCX
    
    #define LOG_SUCCESS  0
    #define LOG_ERROR    1
    #define LOG_INFO     2
    #define LOG_WARNING  3

    #define C_RESET  7
    #define C_RED    4
    #define C_GREEN  2
    #define C_YELLOW 6
    #define C_BLUE   1
#endif


void print_log(int color, const char* format, ...);

#ifdef LIB_PRINT_IMPLEMENTATION

void print_log(int color, const char* format, ...){
#ifdef __linux__
    va_list args;
    va_start(args, format);

    switch (color)
    {
        case LOG_SUCCESS:
            fprintf(stdout, "%s[SUCCESS]%s ", C_GREEN, C_RESET);
            vfprintf(stdout, format, args);
            break;
    
        case LOG_ERROR:
            fprintf(stdout, "%s[ERROR]%s ", C_RED, C_RESET);
            vfprintf(stdout, format, args);
            va_end(args);
        
        case LOG_INFO:
            fprintf(stdout, "%s[INFO]%s ", C_BLUE, C_RESET);
            vfprintf(stdout, format, args);
            break;
        
        case LOG_WARNING:
            fprintf(stdout, "%s[WARNING]%s ", C_YELLOW, C_RESET);
            vfprintf(stdout, format, args);
            break;
        
        default:
            vfprintf(stdout, format, args);
            break;
    }

    va_end(args);
    return;
#elif __WIN32
    va_list args;
    va_start(args, format);


    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (color)
    {
        case LOG_SUCCESS:
            SetConsoleTextAttribute(hConsole, C_GREEN);
            fprintf(stdout, "[SUCCESS] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfprintf(stdout, format, args);
            break;
    
        case LOG_ERROR:
            SetConsoleTextAttribute(hConsole, C_RED);
            fprintf(stdout, "[ERROR] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfprintf(stdout, format, args);
            va_end(args);
        
        case LOG_INFO:
            SetConsoleTextAttribute(hConsole, C_BLUE);
            fprintf(stdout, "[INFO] ");
            vfprintf(stdout, format, args);
            break;
        
        case LOG_WARNING:
            SetConsoleTextAttribute(hConsole, C_YELLOW);
            fprintf(stdout, "[WARNING] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfprintf(stdout, format, args);
            break;
        
        default:
            vfprintf(stdout, format, args);
            break;
    }

    va_end(args);

    return;
#endif
}

#endif