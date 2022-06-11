#pragma once
#include <vector>
#include <dwmapi.h>
#include <windows.h>
#include <TlHelp32.h>
#include <shellapi.h>
#include <shlobj.h>
#include <olectl.h>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "shell32.lib")

#define ACCENT_ENABLE_BLURBEHIND 3
#define WCA_ACCENT_POLICY 19

namespace helper {
    const wchar_t *to_wstr(const char *c) {
        const size_t cSize = strlen(c)+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs (wc, c, cSize);

        return wc;
    }

    DWORD get_pid(const char* procName) {
        DWORD procId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32W procEntry{};
            procEntry.dwSize = sizeof(procEntry);
            if (Process32FirstW(hSnap, &procEntry)) {
                do {
                    if (!_wcsicmp(procEntry.szExeFile, to_wstr(procName))) {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32NextW(hSnap, &procEntry));
            }
        }
        CloseHandle(hSnap);
        return procId;
    }

    void get_proc_windows(DWORD pid, std::vector<HWND>& hwnds) {
        uint64_t n = 0;
        HWND cur_hwnd = NULL;
        do {
            n++;
            cur_hwnd = FindWindowEx(NULL, cur_hwnd, NULL, NULL);
            DWORD cur_pid = NULL;
            GetWindowThreadProcessId(cur_hwnd, &cur_pid);
            if (cur_pid == pid) {
                hwnds.push_back(cur_hwnd);
            }
            if ((n % 15) == 0) { // sleep every 15 iterations (for performance reasons)
                Sleep(1);
                n = 0;
            }
        } while (cur_hwnd != NULL);
    }

    HRESULT save_icon(HICON hIcon, const wchar_t* path) {
        PICTDESC desc = { sizeof(PICTDESC) };
        desc.picType = PICTYPE_ICON;
        desc.icon.hicon = hIcon;
        IPicture* pPicture = 0;
        HRESULT hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (void**)&pPicture);
        if (FAILED(hr)) return hr;

        IStream* pStream = 0;
        CreateStreamOnHGlobal(0, TRUE, &pStream);
        LONG cbSize = 0;
        hr = pPicture->SaveAsFile(pStream, TRUE, &cbSize);

        if (!FAILED(hr)) {
            HGLOBAL hBuf = 0;
            GetHGlobalFromStream(pStream, &hBuf);
            void* buffer = GlobalLock(hBuf);
            HANDLE hFile = CreateFileW((LPCWSTR)path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
            if (!hFile) hr = HRESULT_FROM_WIN32(GetLastError());
            else {
                DWORD written = 0;
                WriteFile(hFile, buffer, cbSize, &written, 0);
                CloseHandle(hFile);
            }
            GlobalUnlock(buffer);
        }

        pStream->Release();
        pPicture->Release();
        return hr;
    }
}