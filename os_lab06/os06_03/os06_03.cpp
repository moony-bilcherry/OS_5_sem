#include <iostream>
#include <Windows.h>

#define KB (1024)
#define PG (4 * KB)

using namespace std;

// Е - 197(10) = C5(16) 
// Р - 208(10) = D0(16)
// Ч - 215(10) = D7(16)

// страница C5 = 197
// 197 * 4096 = 806912(10) = 0x000C5000 - добавить чтоб перейти на страницу
// смещение 0x00000D0D
// короче к адресу начала arr + 0x000C5000 + 0x00000D0D

void saymem() {
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    std::cout << " -- Физическая память: " << ms.dwTotalPhys / KB << '\n';
    std::cout << " -- Доступно физ памяти: " << ms.dwAvailPhys / KB << '\n';
    std::cout << " -- Объем виртуальной памяти: " << ms.dwTotalVirtual / KB << '\n';
    std::cout << " -- Доступно виртуальной памяти: " << ms.dwAvailVirtual / KB << '\n';
}

int main() {
    setlocale(LOCALE_ALL, "rus");
    // заполнение структуры информацией о системе
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    int pages = 256;
    int countItems = pages * PG / sizeof(int);

    saymem();
    // выделение виртуальной памяти (без базового адреса, размер, выделение (при этом страницы заполняются нулями), типа доступа (чтение и запись))
    LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);
    // возвращает LPVOID - дальний указатель на любой тип

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++) {
        arr[i] = i;
    }
    cout << endl;

    saymem();

    // освобождение выделенной памяти (адрес памяти, размер (при MEM_RELEASE здесь NULL), операция (освобождена))
    VirtualFree(xmemaddr, NULL, MEM_RELEASE) ? std::cout << "VirtualFree free\n" : std::cout << "Virtual false\n";
    saymem();

    system("pause");
}

