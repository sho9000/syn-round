#include <iostream>
#include <vector>
#include <cstdint>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "errlog.hpp"
#include "helperfuncs.hpp"
#include "jsondata.hpp"

using namespace rapidjson;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // parsing round_options.json
    FILE* pJsonFile = fopen("round_options.json", "rb");

    if (pJsonFile == NULL) {
        log_err_and_exit("Could not find round_options.json");
    }

    char readBuffer[65536];
    FileReadStream is(pJsonFile, readBuffer, sizeof(readBuffer));

    Document round_options;
    round_options.ParseStream(is);

    fclose(pJsonFile);

    json_data opts;
    validate_doc(round_options, &opts);
    
    // launch synapse x
    system(".\\\"Synapse Launcher.exe\"");
    Sleep(5000);

    // get synapse proc id
    DWORD pid = helper::get_pid(opts.syn_file_name);
    if (pid == 0) {
        log_err_and_exit("Could not find synapse, check round_options.json and try again");
    }

    // load user32.dll and get address of SetWindowCompositionAttribute function
    const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
    if (hModule == NULL) {
        log_err_and_exit("Could not load library user32.dll");
    }

    struct ACCENTPOLICY {
            int nAccentState;
            int nFlags;
            int nColor;
            int nAnimationId;
        };
    struct WINCOMPATTRDATA {
        int nAttribute;
        PVOID pData;
        ULONG ulDataSize;
    };
    typedef BOOL(WINAPI* pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
    const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hModule, "SetWindowCompositionAttribute");
    
    if (SetWindowCompositionAttribute == NULL) {
        log_err_and_exit("SetWindowCompositionAttribute was null");
    }

    ACCENTPOLICY policy = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
    WINCOMPATTRDATA data = { WCA_ACCENT_POLICY, &policy, sizeof(ACCENTPOLICY) };

    /* 
    run a loop to find all windows belonging to synapse
    note: the Sleep() calls will make this loop optimized for the cpu
    */
    std::vector<HWND> hwnds;
    while (true) {
        if (hwnds.size() > 0) {
            hwnds.clear();
        }
        helper::get_proc_windows(pid, hwnds);
        if (hwnds.size() == 0) {
            exit(0);
        }

        // apply options
        for (HWND hwnd : hwnds) {
            if (opts.blur) {
                SetWindowCompositionAttribute(hwnd, &data);
            }
            if (opts.rounding_enabled) {
                DWM_WINDOW_CORNER_PREFERENCE preference = opts.rounding_small ? DWMWCP_ROUNDSMALL : DWMWCP_ROUND;
                DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &preference, sizeof(preference));
            }
            Sleep(1);
        }
        Sleep(10);
    }

    return 0;
}