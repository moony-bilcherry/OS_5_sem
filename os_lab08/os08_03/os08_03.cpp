#include <Windows.h>
#include <iostream>
#include <ctime>
#define SECOND 10000000

HANDLE hTimer3s = NULL;
long long time3s = -3 * SECOND;

HANDLE hTimer15s = NULL;
long long time15s = -15 * SECOND;

int i = 0;

DWORD WINAPI ChildThread() {
	while (true) {
		WaitForSingleObject(hTimer3s, INFINITE);
		std::cout << clock() << ": timer1" << "\n";
		std::cout << "iterations count: " << i << "\n\n";
	}
}

int main() {
	hTimer3s = CreateWaitableTimer(NULL, FALSE, NULL);
	std::cout << clock() << ": start" << "\n\n";
	if (!SetWaitableTimer(hTimer3s, (LARGE_INTEGER*)&time3s, 3000, NULL, NULL, FALSE)) throw "SetwaitableTimer (3s) error";

	DWORD ChildId = 0;
	HANDLE hchild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, NULL, &ChildId);

	hTimer15s = CreateWaitableTimer(NULL, FALSE, NULL);
	if (!SetWaitableTimer(hTimer15s, (LARGE_INTEGER*)&time15s, 0, NULL, NULL, FALSE)) throw "SetwaitableTimer (15s) error";

	while (true) {
		if (WaitForSingleObject(hTimer15s, 0) == WAIT_OBJECT_0) {
			std::cout << clock() << ": timer2" << "\n";
			std::cout << "breaking loop" << "\n\n";
			TerminateThread(hchild, 0);
			break;
		}
		i++;
	}

	std::cout << "iterations count: " << i << "\n\n";

	system("pause");
	return 0;
}