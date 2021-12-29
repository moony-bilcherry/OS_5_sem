#include <iostream>
#include <Windows.h>

int main() {
	LPCWSTR pathA = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab07\\Debug\\os07_03A.exe";
	LPCWSTR pathB = L"T:\\Uni\\5_sem\\OS\\OS_5_sem\\os_lab07\\Debug\\os07_03B.exe";
	DWORD pid = GetCurrentProcessId();

	STARTUPINFO si1;
	STARTUPINFO si2;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	ZeroMemory(&si1, sizeof(STARTUPINFO)); si1.cb = sizeof(STARTUPINFO);
	ZeroMemory(&si2, sizeof(STARTUPINFO)); si2.cb = sizeof(STARTUPINFO);

	// чтобы остальные объекты нашли этот мьютекс, ему дается имя
	// false - создавший его поток не является владельцем
	HANDLE hm = CreateMutex(NULL, FALSE, L"Mutex");

	if (CreateProcess(pathA, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
		std::cout << "\t!! Process OS07_03A was created\n";
	else
		std::cout << "\t!! Process OS07_03A wasn't created\n";

	if (CreateProcess(pathB, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		std::cout << "\t!! Process OS07_03B was created\n";
	else
		std::cout << "\t!! Process OS07_03B wasn't created\n";

	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30)
			WaitForSingleObject(hm, INFINITE);
		if (i == 60)
			ReleaseMutex(hm);
		std::cout << i << " OS07_03 MAIN pid = " << pid << ", time: " << clock() - start << '\n';
		Sleep(100);
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(hm);
	CloseHandle(pi1.hProcess); 
	CloseHandle(pi2.hProcess);

	system("pause");
	return 0;
}