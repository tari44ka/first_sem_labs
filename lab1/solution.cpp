/*
Ввести массив чисел и число. Сдвинуть эти числа на указанное число. 
Положительное число  - сдвиг влево
Отрицательное - сдвиг вправо
*/
#include <iostream>
#include "list.h"
#include <stdlib.h>

void firstTask()
{
	int count;
	do
	{
		std::cout << "Please, enter count of elements (not more, than MAX_INT)" << std::endl;
		std::cin >> count;
	}
	while (count <= 0);
	List *list = new List();
	std::cout << "Please, enter each element (all are integer)" << std::endl;
	for (int i = 0; i < count; ++i)
	{
		int value;
		std::cin >> value;
		list->addInTail(value);
	}
	std::cout << "Please, enter shift-value (integer)" << std::endl;
	int shift;
	std::cin >> shift;

	list->moveHead(shift);
	std::cout << "Shifted list is" << std::endl;
	list->print();
	delete list;
}

int simpleCompare(const void* a, const void* b)
{
	if (*(int*)a < *(int*)b) return -1;
	if (*(int*)a == *(int*)b) return 0;
	if (*(int*)a > *(int*)b) return 1;
}

int getUnpairValue(int* array, int count)
{
	qsort(array, count, sizeof(int), simpleCompare);

	int constCount = 1;
	for (int i = 1; i < count; ++i)
	{
		if (array[i] == array[i-1])
			constCount++;
		else
		{
			if (constCount % 2 == 1)
			{
				return array[i-1];
			}
			constCount = 1;
		}
	}
	return array[count - 1];
}

void secondTask()
{
	int count;
	do
	{
		std::cout << "Please, enter count of elements (not more, than MAX_INT). It must be odd" << std::endl;
		std::cin >> count;
	}
	while ((count <= 0) || (count % 2 == 0));
	int *array = new int[count];
	std::cout << "Please, enter each element (all are integer)" << std::endl;
	for (int i = 0; i < count; ++i)
	{
		std::cin >> array[i];
	}
	int unpairValue = getUnpairValue(array, count);
	std::cout << "Unpair value is " << unpairValue << std::endl;
}

int main()
{
	int type;
	do
	{
		std::cout << "Please, enter task number (1 or 2)" << std::endl;
		std::cin >> type;
	}
	while ((type != 1) && (type != 2));
	
	switch (type)
	{
		case 1:
			firstTask();
			break;
		case 2:
			secondTask();
			break;
	};
	return 0;
}


