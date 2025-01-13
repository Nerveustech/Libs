/*
 * MIT License
 *
 * Copyright (c) 2024-2025 Andrea Michael M. Molino
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

///
///Macro section
///

#if defined(WIN64) || defined(_WIN64) || defined(__MINGW64__)
	#define WINDOWS_64
#elif defined(WIN32) || defined(_WIN32) || defined(__MINGW32__)
	#define WINDOWS_32
#endif

#if defined(WINDOWS_64) || defined(WINDOWS_32)
    #define WINDOWS
#endif

#ifdef __linux__
    #define LINUX
#endif

typedef enum {
    Success = 0,
    Error,
    Info,
    Warning,
    Custom
}LogType;

///
///End Macro section
///

#if defined(LINUX)

    #define C_RESET  "\x1B[0m"
    #define C_RED    "\x1B[1;31m"
    #define C_GREEN  "\x1B[1;32m"
    #define C_YELLOW "\x1B[1;33m"
    #define C_BLUE   "\x1B[1;34m"
    #define C_ORANGE "\x1B[1;93m"

    void print(LogType type, const char* format, ...);
    void log_file(LogType type, const char* file,  const char* format, ...);

#elif defined(WINDOWS)
/*
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
*/  
    #define NOMINMAX
    #define WIN32_LEAN_AND_MEAN 
    #include <Windows.h>


    #define C_RESET  7
    #define C_RED    4
    #define C_GREEN  2
    #define C_YELLOW 6
    #define C_BLUE   1
    #define C_ACQUA FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    
    void print(LogType type, CONST WCHAR* format, ...);
    void log_file(LogType type, CONST WCHAR* file, CONST WCHAR* format, ...);
#endif

#ifdef LIB_PRINT_IMPLEMENTATION

#ifdef LINUX
void print(LogType type, const char* format, ...)
{

    va_list args;
    va_start(args, format);

    switch (type)
    {
        case Success:
            fprintf(stdout, "%s[SUCCESS]%s ", C_GREEN, C_RESET);
            vfprintf(stdout, format, args);
            break;
    
        case Error:
            fprintf(stderr, "%s[ERROR]%s ", C_RED, C_RESET);
            vfprintf(stderr, format, args);
            break;
        
        case Info:
            fprintf(stdout, "%s[INFO]%s ", C_YELLOW, C_RESET);
            vfprintf(stdout, format, args);
            break;
        
        case Warning:
            fprintf(stdout, "%s[WARNING]%s ", C_ORANGE, C_RESET);
            vfprintf(stdout, format, args);
            break;
        
        case Custom:
            vfprintf(stdout, format, args);
            break;
        
        default:
            __builtin_unreachable();
    }

    va_end(args);
    return;
}

void log_file(LogType type, const char* file,  const char* format, ...)
{
    FILE* file_to_open = fopen(file, "a");

    if(file_to_open == NULL){
        print(Error, "Could not open: %s for log\n", file);
        return;
    }

    va_list args;
    va_start(args, format);

    switch(type){
        case Success:
            fprintf(file_to_open, "[SUCCESS] ");
            vfprintf(file_to_open, format, args);
            break;
    
        case Error:
            fprintf(file_to_open, "[ERROR] ");
            vfprintf(file_to_open, format, args);
            break;
        
        case Info:
            fprintf(file_to_open, "[INFO] ");
            vfprintf(file_to_open, format, args);
            break;
        
        case Warning:
            fprintf(file_to_open, "[WARNING] ");
            vfprintf(file_to_open, format, args);
            break;
        
        case Custom:
            vfprintf(file_to_open, format, args);
            break;
        
        default:
            __builtin_unreachable();
    }

    va_end(args);
    fclose(file_to_open);
    
    return;
}

#endif

#ifdef WINDOWS
void print(LogType type, CONST WCHAR* format, ...)
{
    va_list args;
    va_start(args, format);

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (type)
    {
        case Success:
            SetConsoleTextAttribute(hConsole, C_GREEN);
            fwprintf(stdout, L"[SUCCESS] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfwprintf(stdout, format, args);
            break;
    
        case Error:
            SetConsoleTextAttribute(hConsole, C_RED);
            fwprintf(stderr, L"[ERROR] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfwprintf(stderr, format, args);
            break;
        
        case Info:
            SetConsoleTextAttribute(hConsole, C_ACQUA);
            fwprintf(stdout, L"[INFO] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfwprintf(stdout, format, args);
            break;
        
        case Warning:
            SetConsoleTextAttribute(hConsole, C_YELLOW);
            fwprintf(stdout, L"[WARNING] ");
            SetConsoleTextAttribute(hConsole, C_RESET);
            vfwprintf(stdout, format, args);
            break;
        
        case Custom:
            vfwprintf(stdout, format, args);
            break;
        
        default:
            __assume(0);
    }

    va_end(args);

    return;

}

void log_file(LogType type, CONST WCHAR* file, CONST WCHAR* format, ...)
{
    FILE* file_to_open = NULL; 
    _wfopen_s(&file_to_open, file, L"a");

    if(file_to_open == NULL){
        print(Error, L"Could not open: %s for log\n", file);
        return;
    }

    va_list args;
    va_start(args, format);

    switch(type){
        case Success:
            fwprintf(file_to_open, L"[SUCCESS] ");
            vfwprintf(file_to_open, format, args);
            break;
    
        case Error:
            fwprintf(file_to_open, L"[ERROR] ");
            vfwprintf(file_to_open, format, args);
            break;
        
        case Info:
            fwprintf(file_to_open, L"[INFO] ");
            vfwprintf(file_to_open, format, args);
            break;
        
        case Warning:
            fwprintf(file_to_open, L"[WARNING] ");
            vfwprintf(file_to_open, format, args);
            break;
        
        case Custom:
            vfwprintf(file_to_open, format, args);
            break;
        
        default:
            __assume(0);
    }

    va_end(args);
    fclose(file_to_open);
    
    return;
}
#endif

#endif /*LIB_PRINT_IMPLEMENTATION*/