#include <Windows.h>
#include <iostream>
#include <ctime>

int main() {
	DWORD pid = GetCurrentProcessId();
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event");
	he == NULL ? std::cout << "OS07_05A: Open event error\n" : std::cout << "OS07_05A: Open Event\n";
	WaitForSingleObject(he, INFINITE);

	int start = clock();
	for (int i = 0; i < 90; i++) {
		std::cout << i << " OS07_05A CHILD A pid = " << pid << ", time: " << clock() - start << '\n';
		Sleep(100);
	}

	CloseHandle(he);

	system("pause");
	return 0;
}