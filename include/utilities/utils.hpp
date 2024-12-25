
#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 // Set for Windows 10
#endif

#include <iostream>
//#include <cmath>
#include <csignal>
#include <windows.h>
#include <shellscalingapi.h>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


void signalHandler(int signal) {
    cerr << "\033[1;41mSignal (" << signal << ") received. Terminating gracefully.\033[0m" << endl;
    exit(signal);
}


/* void setDPIAware() {
    // Try to set the process to per-monitor DPI awareness (best for Windows 10)
    HRESULT result = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    if (SUCCEEDED(result)) {
        cout << "\033[1;46mDPI awareness set to PROCESS_PER_MONITOR_DPI_AWARE\033[0m" << ".\n";
    } else {
        // If setting per-monitor DPI awareness fails, fallback to system DPI awareness
        cerr << "\033[1;41mFailed to set PROCESS_PER_MONITOR_DPI_AWARE. Falling back to system DPI awareness\033[0m" << ".\n";
        result = SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
        if (SUCCEEDED(result)) {
            cout << "\033[1;46mDPI awareness set to PROCESS_SYSTEM_DPI_AWARE\033[0m" << ".\n";
        } else {
            cerr << "\033[1;41mFailed to set PROCESS_SYSTEM_DPI_AWARE. Attempting older API\033[0m" << ".\n";

            // As a final fallback, use SetProcessDPIAware
            if (SetProcessDPIAware()) {
                cout << "\033[1;46mDPI awareness set with SetProcessDPIAware\033[0m" << ".\n";
            } else {
                cerr << "\033[1;41mFailed to set DPI awareness with SetProcessDPIAware\033[0m" << ".\n";
            }
        }
    }
} */

/* void setDPIAware() {
    // Try to load Shcore.dll for SetProcessDpiAwareness
    HMODULE shcore = LoadLibrary(TEXT("Shcore.dll"));
    if (shcore) {
        // Dynamically locate the SetProcessDpiAwareness function
        auto setProcessDpiAwareness = (HRESULT(*)(PROCESS_DPI_AWARENESS)) 
            GetProcAddress(shcore, "SetProcessDpiAwareness");

        if (setProcessDpiAwareness) {
            // Set per-monitor DPI awareness
            HRESULT result = setProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
            if (SUCCEEDED(result)) {
                cout << "DPI awareness set to PROCESS_PER_MONITOR_DPI_AWARE.\n";
                FreeLibrary(shcore);
                return;
            } else {
                cerr << "Failed to set PROCESS_PER_MONITOR_DPI_AWARE.\n";
            }
        } else {
            cerr << "SetProcessDpiAwareness not available.\n";
        }
        FreeLibrary(shcore);
    } else {
        cerr << "Shcore.dll not available. Falling back to SetProcessDPIAware.\n";
    }

    // Fallback to SetProcessDPIAware (present in User32.dll)
    HMODULE user32 = LoadLibrary(TEXT("User32.dll"));
    if (user32) {
        auto setProcessDPIAware = (BOOL(*)()) GetProcAddress(user32, "SetProcessDPIAware");
        if (setProcessDPIAware) {
            if (setProcessDPIAware()) {
                cout << "DPI awareness set using SetProcessDPIAware.\n";
            } else {
                cerr << "Failed to set DPI awareness using SetProcessDPIAware.\n";
            }
        } else {
            cerr << "SetProcessDPIAware not available.\n";
        }
        FreeLibrary(user32);
    } else {
        cerr << "User32.dll not available.\n";
    }
} */
