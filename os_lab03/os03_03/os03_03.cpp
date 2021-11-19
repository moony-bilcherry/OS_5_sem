#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    DWORD pid = GetCurrentProcessId();

    // снимок процессов в данный момент (TH32CS_SNAPALL = все процессы + их потоки, кучи и модули)
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    // структура для экземпляра процесса из снимка
    PROCESSENTRY32 peProccessEntry;
    peProccessEntry.dwSize = sizeof(PROCESSENTRY32);

    wcout << L"Current PID " << pid << endl << L"----------------" << endl;
    try {
        // берет информацию о первом процессе из снимка
        if (!Process32First(snap, &peProccessEntry)) {
            throw L"Process32First";
        }
        do {
            wcout << L"Name: " << peProccessEntry.szExeFile
                << L"\nPID: " << peProccessEntry.th32ProcessID
                << L"\nParent PID: " << peProccessEntry.th32ParentProcessID;
            if (peProccessEntry.th32ProcessID == pid) {
                wcout << " --> current process";
            }

            wcout << endl << L"---------------------" << endl;

        } while (Process32Next(snap, &peProccessEntry));
    }
    catch (char* msg) {
        wcout << L"ERROR: " << msg << endl;
    }
}