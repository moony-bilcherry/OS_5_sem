#include <iostream>
#include <Windows.h>

#define KB (1024)
void sh(HANDLE pheap);

int main() {
	// создается пользовательская куча (опции (доступ не синхронизирован и куча заполняется нулями), начальный размер (4 мб), конечный размер (ограничен размером виртуальной памяти))
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4096, 0);
	sh(heap);

	// выделяем место в созданной куче на 300к интов
	int* x1 = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
	std::cout << "\nAddress: " << x1 << "\n\n";

	sh(heap);

	// занятая ранее память освобождается
	HeapFree(heap, HEAP_NO_SERIALIZE, x1);
	sh(heap);
	HeapDestroy(heap);
	system("pause");
	return 0;
}

void sh(HANDLE pheap) {
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	// перемещение по куче от узла к узлу
	while (HeapWalk(pheap, &phe)) {
		// R - начало непрерывной области
		// U и B - нераспределенная и распределенная область соотв.
		std::cout << "-- address = " << std::hex << phe.lpData <<
			", size = " << std::dec << phe.cbData <<
			((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") <<					
			((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") <<
			((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") << '\n';
	}
	std::cout << "----\n";
}