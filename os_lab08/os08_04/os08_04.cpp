#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	DWORD pid = GetCurrentProcessId();
	std::cout << "Main process ID: " << pid << '\n';

	long long it = -60 * 10000000;
	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, L"os08_04");
	if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 60000, NULL, NULL, FALSE))
		throw "SetWaitableTimer Error";

	LPCWSTR path = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab08\\Debug\\os08_04x.exe";

	PROCESS_INFORMATION pi1, pi2;
	clock_t start = clock();
	pi1.dwThreadId = 1; pi2.dwThreadId = 2;
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1) ?
			std::cout << "Process os08_04x #1 was created\n" : std::cout << "Process os08_04x #1 wasn't created\n";
	}
	{
		STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
		CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2) ?
			std::cout << "Process os08_04x #2 was created\n" : std::cout << "Process os08_04x #2 wasn't created\n";
	}

	WaitForSingleObject(pi1.hProcess, INFINITE); 
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(htimer);
	std::cout << "Elapsed time = " << clock() - start << " clocks\n";
	system("pause");
	return 0;
}