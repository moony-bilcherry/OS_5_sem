#include <Windows.h>
#include <iostream>

int main()
{
    for (int i = 0; i < 125; i++) {
        std::cout << "OS03_02_2 PID " << GetCurrentProcessId() << std::endl;
        Sleep(1000);
    }

    return 0;
}