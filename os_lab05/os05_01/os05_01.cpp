#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

void getProcessPriority(HANDLE hp); //приоритетный класс процесса 
void getThreadPriority(HANDLE ht);
void getAffinityMask(HANDLE hp, HANDLE ht);

int main()
{
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	cout << "os05_01\n\n";
	cout << "PID: " << pid << "\nTID: " << tid << endl;
	getProcessPriority(processHandle);
	getThreadPriority(threadHandle);
	getAffinityMask(processHandle, threadHandle);

	system("pause");
}

void getProcessPriority(HANDLE hp) {
	DWORD prty = GetPriorityClass(hp);

	switch (prty) {
		case IDLE_PRIORITY_CLASS: 
			cout << "ProcessPriority: IDLE_PRIORITY_CLASS\n"; 
			break;
		case BELOW_NORMAL_PRIORITY_CLASS: 
			cout << "ProcessPriority: BELOW_NORMAL_PRIORITY_CLASS\n"; 
			break;
		case NORMAL_PRIORITY_CLASS: 
			cout << "ProcessPriority: NORMAL_PRIORITY_CLASS\n"; 
			break;
		case ABOVE_NORMAL_PRIORITY_CLASS: 
			cout << "ProcessPriority: ABOVE_NORMAL_PRIORITY_CLASS\n"; 
			break;
		case HIGH_PRIORITY_CLASS: 
			cout << "ProcessPriority: HIGH_PRIORITY_CLASS\n"; 
			break;
		case REALTIME_PRIORITY_CLASS: 
			cout << "ProcessPriority: REALTIME_PRIORITY_CLASS\n"; 
			break;
		default: cout << "ERROR: PROCESS PRIORITY NOT RECOGNIZED\n\n"; break;
	}
}

void getThreadPriority(HANDLE ht) {
	DWORD prty = GetPriorityClass(ht);

	cout << "ThreadPriority: " << GetThreadPriority(ht) << " ";

	switch (prty) {
		case THREAD_PRIORITY_LOWEST: 
			cout << "THREAD_PRIORITY_LOWEST\n"; 
			break;
		case THREAD_PRIORITY_BELOW_NORMAL: 
			cout << "THREAD_PRIORITY_BELOW_NORMAL\n"; 
			break;
		case THREAD_PRIORITY_NORMAL: 
			cout << "THREAD_PRIORITY_NORMAL\n"; 
			break;
		case THREAD_PRIORITY_ABOVE_NORMAL: 
			cout << "THREAD_PRIORITY_ABOVE_NORMAL\n"; 
			break;
		case THREAD_PRIORITY_HIGHEST: 
			cout << "THREAD_PRIORITY_HIGHEST\n"; 
			break;
		case THREAD_PRIORITY_IDLE: 
			cout << "THREAD_PRIORITY_IDLE\n"; 
			break;
		default: cout << "ERROR: THREAD PRIORITY NOT RECOGNIZED\n\n"; break;
	}
}

void getAffinityMask(HANDLE hp, HANDLE ht) {
	DWORD pa = NULL, sa = NULL, icpu = -1;
	char buf[13];

	if (!GetProcessAffinityMask(hp, &pa, &sa)) throw "GetProcessAffinityMask";

	// преобразует pa в строку buf в 2-й СС
	_itoa_s(pa, buf, 2);
	cout << "Process affinity Mask: " << buf << endl;
	_itoa_s(sa, buf, 2);
	cout << "System affinity Mask: " << buf << endl;

	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	cout << "Amount of available processors: " << sys_info.dwNumberOfProcessors << endl << endl;
	icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	cout << "Thread IdealProcessor: " << dec << icpu << endl;
	
	
}