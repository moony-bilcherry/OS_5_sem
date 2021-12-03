#include <Windows.h>
#include <iostream>

int main()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 1000; i++) {
        Sleep(500);
        std::cout << "PID = " << pid << ", TID = " << tid << "\n";
    }

    return 0;
}

