#pragma once
#include <windows.h>

void log_err(const char* msg) {
    CHAR szFileName[MAX_PATH];
    GetModuleFileNameA(NULL, szFileName, MAX_PATH);
    MessageBoxA(NULL, (LPCSTR)msg, szFileName, MB_ICONERROR);
}

void log_err_and_exit(const char* msg) {
    CHAR szFileName[MAX_PATH];
    GetModuleFileNameA(NULL, szFileName, MAX_PATH);
    MessageBoxA(NULL, (LPCSTR)msg, szFileName, MB_ICONERROR);
    exit(-1);
}