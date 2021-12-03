#include <Windows.h>
#include <iostream>

DWORD WINAPI OS04_03_T1() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 50; ++i) {
        Sleep(1000);
        std::cout << i << ". T1 PID = " << pid << ", TID = " << tid << std::endl;
    }
    return 0;
}

DWORD WINAPI OS04_03_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 125; ++i) {
        Sleep(1000);
        std::cout << i << ". T2 PID = " << pid << ", TID = " << tid << std::endl;
    }
    return 0;
}

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    DWORD childId_T1, childId_T2 = NULL;

    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_03_T1, NULL, 0, &childId_T1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_03_T2, NULL, 0, &childId_T2);

    for (int i = 0; i < 100; ++i) {
        Sleep(1000);
        std::cout << i << ". Parent Thread PID = " << pid << ", TID = " << tid << std::endl;

        if (i == 20) {
            SuspendThread(hChild1);
            std::cout << "\n\t\t!!! Thread Child1 suspended!!!\n";
        }
        if (i == 40) {
            SuspendThread(hChild2);
            std::cout << "\n\t\t!!!Thread Child2 suspended !!!\n";
        }
        if (i == 60) {
            ResumeThread(hChild1);
            std::cout << "\n\t\t!!! Thread Child1 resumed!!!\n";
        }
    }
    ResumeThread(hChild2);
    std::cout << "\n\t\t!!! Thread Child2 resumed !!!\n";

    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);

    CloseHandle(hChild1);
    CloseHandle(hChild2);

    return 0;
}

