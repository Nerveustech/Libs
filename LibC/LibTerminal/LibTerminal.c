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

#include "LibTerminal.h"

int clear_terminal(void){
#ifdef __linux__
    printf("\033[H\033[2J");
    printf("\033[H\033[3J");
    return 0;

#elif __WIN32

    PCWSTR clear_window = L"\x1b[H\x1b[2J";
    PCWSTR clear_scroll_back = L"\x1b[H\x1b[3J";

    if(__internal_windows_terminal_helper(clear_window) != 0){
        return 1;
    }
    if(__internal_windows_terminal_helper(clear_scroll_back) != 0){
        return 1;
    }
    
    return 0;

#endif
}

#ifdef __WIN32
int __internal_windows_terminal_helper(PCWSTR escape_code){
//https://learn.microsoft.com/en-us/windows/console/clearing-the-screen taken as an example

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mode = 0;
    if(!GetConsoleMode(hConsole, &mode)){
        return 1;
    }

    const DWORD default_mode = mode;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(hConsole, mode)){
        return 1;
    }

    if(!WriteConsoleW(hConsole, escape_code, (DWORD)wcslen(escape_code), NULL, NULL)){
        SetConsoleMode(hConsole, default_mode);
        return 1;
    }

    SetConsoleMode(hConsole, default_mode);
    return 0;
}
#endif