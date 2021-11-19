#include <Windows.h>        // для системных вызовов
#include <iostream>

using namespace std;

int main()
{
    // long pointer to constant wide string
    LPCWSTR an1 = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab03\\Debug\\os03_02_1.exe";
    LPCWSTR an2 = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab03\\Debug\\os03_02_2.exe";

    // CreateProcess использует эту структуру для определения оконного терминал, рабочего стола, стандартного дескриптора и внешнего вида окна процесса
    STARTUPINFO si1;
    STARTUPINFO si2;

    // CreateProcess заполняет эту структуру инфой про процесс и его стартовый поток
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;

    // заполнение памяти по адресу нулями
    ZeroMemory(&si1, sizeof(STARTUPINFO));
    ZeroMemory(&si2, sizeof(STARTUPINFO));

    // cb - размер структуры
    si1.cb = sizeof(STARTUPINFO);
    si2.cb = sizeof(STARTUPINFO);

    // (имя модуля, ..., ..., ..., флаг наследования от родительского процесса, способ создания и/или задание приоритета, ..., ..., STARTUPINFO, PROCESS_INFORMATION)
    if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)) {
        cout << "--Process OS03_02_1 created\n";
    }
    else {
        cout << "--Process OS03_02_1 not created\n";
    }

    if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)) {
        cout << "--Process OS03_02_2 created\n";
    }
    else {
        cout << "--Process OS03_02_2 not created\n";
    }

    for (int i = 0; i < 1000; i++) {
        std::cout << "OS03_02 PID " << GetCurrentProcessId() << std::endl;
        Sleep(1000);
    }

    // ожидание завершения дочерних процессов
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    // закрывает дексриптов открытого окна
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);

    return 0;
}