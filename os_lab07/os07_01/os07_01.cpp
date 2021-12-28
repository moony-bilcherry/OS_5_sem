#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

DWORD WINAPI ChildThrOne();
DWORD WINAPI ChildThrTwo();

void EnterCriticalSectionAsm();
void LeaveCriticalSectionAsm();

int check = 0;

int main() {
	DWORD OneId = NULL, TwoId = NULL;

	HANDLE hOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThrOne, NULL, 0, &OneId);
	HANDLE hTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThrTwo, NULL, 0, &TwoId);

	WaitForSingleObject(hOne, INFINITY);	
	WaitForSingleObject(hTwo, INFINITY);

	CloseHandle(hOne); 
	CloseHandle(hTwo);

	system("pause");
	return 0;
}

DWORD WINAPI ChildThrOne() {
	int start = clock();

	EnterCriticalSectionAsm();
	cout << "\n\tThread 1 entered critical section\n";

	for (int i = 0; i < 10; i++) {
		cout << "* Thread 1:" << i << ", time: " << clock() - start << endl;
	}

	cout << "\tThread 1 leaves critical section\n";
	LeaveCriticalSectionAsm();

	return 0;
}

DWORD WINAPI ChildThrTwo() {
	int start = clock();

	EnterCriticalSectionAsm();
	cout << "\n\tThread 2 entered critical section\n";

	for (int i = 0; i < 10; i++) {
		cout << "* Thread 2:" << i << ", time: " << clock() - start << endl;
	}

	cout << "\tThread 2 leaves critical section\n";
	LeaveCriticalSectionAsm();

	return 0;
}

void EnterCriticalSectionAsm() {
	// lock устанавливает сигнал LOCK и запрещает доступ к системной шине другим процессорам на время выполнения данной команды
	// BTS сохраняет значение бита из check со смещением 0 во флаге CF, а затем устанавливает этот бит в 1
	_asm {
	CriticalSection:
		lock bts check, 0;
		jc CriticalSection
	}
}

void LeaveCriticalSectionAsm() {
	// BTR сохраняет значение бита из check со смещением 0 во флаге CF, а затем обнуляет этот бит
	_asm lock btr check, 0
}