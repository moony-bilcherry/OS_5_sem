#include <iostream>
#include <Windows.h>
#include <ctime>

int main() {
	DWORD pid = GetCurrentProcessId();
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Semaphore");
	hs == NULL ? std::cout << "OS07_04B: Open Semaphore Error\n" : std::cout << "OS07_04B: Open Semaphore\n";

	int start = clock();
	LONG prevcount = 0;

	for (int i = 0; i < 90; i++) {
		if (i == 30)
			WaitForSingleObject(hs, INFINITE);
		if (i == 60)
			ReleaseSemaphore(hs, 1, &prevcount);
		std::cout << i << " OS07_04B CHILD B pid = " << pid << ", time: " << clock() - start << '\n';
		Sleep(100);
	}

	CloseHandle(hs);

	system("pause");
	return 0;
}