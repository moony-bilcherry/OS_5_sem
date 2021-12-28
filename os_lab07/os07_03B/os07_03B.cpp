#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	DWORD pid = GetCurrentProcessId();
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	hm == NULL ? std::cout << "OS07_3B: Open Mutex Error\n" : std::cout << "OS07_03B: Open mutex\n";

	int start = clock();
	for (int i = 0; i < 90; i++) {
		if (i == 30)
			WaitForSingleObject(hm, INFINITE);
		if (i == 60)
			ReleaseMutex(hm);
		std::cout << i << " OS07_03B CHILD2 pid = " << pid << ", time " << clock() - start << '\n';
		Sleep(100);
	}

	CloseHandle(hm);
	system("pause");
}