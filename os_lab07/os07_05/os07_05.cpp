#include <iostream>
#include <Windows.h>
#include <ctime>

int main() {
	DWORD pid = GetCurrentProcessId();
	// атрибут защиты, ручной сброс, начальное состояние несигнальное, имя
	HANDLE he = CreateEvent(NULL, TRUE, FALSE, L"Event");
	LPCWSTR pathA = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab07\\Debug\\os07_05A.exe";
	LPCWSTR pathB = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab07\\Debug\\os07_05B.exe";

	STARTUPINFO si1; 
	STARTUPINFO si2;
	PROCESS_INFORMATION pi1; 
	PROCESS_INFORMATION pi2;

	ZeroMemory(&si1, sizeof(STARTUPINFO));
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si1.cb = sizeof(STARTUPINFO); 
	si2.cb = sizeof(STARTUPINFO);

	if (CreateProcess(pathA, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
		std::cout << "\t!! Process OS07_05A was created\n";
	else
		std::cout << "\t!! Process OS07_05A wasn't created\n";

	if (CreateProcess(pathB, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		std::cout << "\t!! Process OS07_05B was created\n";
	else
		std::cout << "\t!! Process OS07_05B wasn't created\n";

	int start = clock();
	LONG prevcount = 0;
	for (int i = 0; i < 90; i++) {
		// устанавливает объект события в сигнальное состояние
		if (i == 15)
			PulseEvent(he);
		std::cout << i << " OS07_05 MAIN pid = " << pid << ", time: " << clock() - start << '\n';
		Sleep(100);
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(he);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	system("pause");
	return 0;
}