#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec) {
	char file[20];
	wcstombs(file, FileName, 20);
	std::cout << "\tprintWatchRowFileTxt\n";
	std::cout << "File path: " << file << "\n";
	
	PLARGE_INTEGER fileSize = new LARGE_INTEGER();
	char* path = new char[MAX_PATH + 1];
	char* cFileName = new char[wcslen(FileName) * sizeof(char) + 1];

	// получение пути к папке из пути к файлу
	wcstombs(cFileName, FileName, strlen(cFileName));
	int i = 0;
	int lenName = 0;
	while (true) {
		path[lenName++] = cFileName[i++];
		if (FileName[i] == '\0') {
			while (path[--lenName] != '\\') path[lenName] = '\0';
			path[lenName] = '\0';
			break;
		}
	}
	std::cout << "Folder path: " << path << "\n";

	wchar_t wtext[20];
	mbstowcs(wtext, path, strlen(path) + 1);		// + null
	LPWSTR ptr = wtext;

	try {
		// путь, слушаем только саму папку, изменение размера файла
		HANDLE hNotif = FindFirstChangeNotification(ptr, FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);

		if (hNotif == INVALID_HANDLE_VALUE) {
			CloseHandle(hNotif);
			throw "INVALID_HANDLE_VALUE in FindFirstChangeNotification";
		}

		bool bWait = true;
		DWORD dwWaitStatus;
		clock_t t1;
		clock_t t2;
		t1 = clock();
		std::cout << "Watch started timestamp: " << t1 << " clocks\n";
		while (bWait)
		{
			dwWaitStatus = WaitForSingleObject(hNotif, 0);

			if (dwWaitStatus == WAIT_OBJECT_0) {
				std::cout << "Row quantity has changed\n";
				// получение информации о следующем событии
				if (FindNextChangeNotification(hNotif) == FALSE) {
					CloseHandle(hNotif);
					throw "FindNextChangeNotification is FALSE";
				}
				int position = 0;
				int rowCount = 1;
				HANDLE of = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (of == INVALID_HANDLE_VALUE) {
					CloseHandle(of);
					throw "create or open file failed";
				}

				if (GetFileSizeEx(of, fileSize))
				{
					char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
					ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));
					DWORD n = NULL;
					if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
					{
						while (buf[position++] != '\0')
							if (buf[position] == '\n') 
								rowCount++;
					}
				}
				std::cout << "\tCurrent amount = " << rowCount << "\n";
				CloseHandle(of);
			}
			t2 = clock();
			int clockDifference = t2 - t1;
			double timeDifference = (double)clockDifference / CLOCKS_PER_SEC;
			if (timeDifference > mlsec / 1000) {
				std::cout << "Watching is ended\n";
				std::cout << "Time passed: " << timeDifference << " seconds\n";
				break;
			}
		}
	}
	catch (const char* em) { 
		std::cout << "!! Error: " << em << " \n";
		std::cout << "---------------------------------------------------------\n";
		return false;
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	LPWSTR  file = (LPWSTR)(L"..\\os09_01.txt");

	printWatchRowFileTxt(file, 200000);

	system("pause");
	return 0;
}