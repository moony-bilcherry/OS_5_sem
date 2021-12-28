#include <iostream>
#include <Windows.h>
#include <ctime>

int main() {
	HANDLE hs = CreateSemaphore(NULL, 2, 3, L"Semaphore");

	LPCWSTR pathA = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab07\\Debug\\os07_04A.exe";
	LPCWSTR pathB = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab07\\Debug\\os07_04B.exe";
	DWORD pid = GetCurrentProcessId();

	STARTUPINFO si1; 
	STARTUPINFO si2;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	ZeroMemory(&si1, sizeof(STARTUPINFO));
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si1.cb = sizeof(STARTUPINFO); 
	si2.cb = sizeof(STARTUPINFO);

	if (CreateProcess(pathA, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
		std::cout << "\t!! Process OS07_04A was created\n";
	else
		std::cout << "\t!! Process OS07_04A wasn't created\n";

	if (CreateProcess(pathB, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		std::cout << "\t!! Process OS07_04B was created\n";
	else
		std::cout << "\t!! Process OS07_04B wasn't created\n";

	LONG prevcount = 0;

	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30)
			WaitForSingleObject(hs, INFINITE);
		if (i == 60)
			ReleaseSemaphore(hs, 1, &prevcount);
		std::cout << i << " OS07_04 pid = " << pid << ", time " << clock() - start << '\n';
		Sleep(100);
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(hs);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	system("pause");
	return 0;
}