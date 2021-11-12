#include <Windows.h>
#include <iostream>

int main()
{
    for (int i = 0; i < 50; i++) {
        std::cout << "OS03_02_1 PID " << GetCurrentProcessId() << std::endl;
        Sleep(1000);
    }

    return 0;
}