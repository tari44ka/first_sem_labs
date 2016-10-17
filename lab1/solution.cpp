/*
Ввести массив чисел и число. Сдвинуть эти числа на указанное число. 
Положительное число  - сдвиг влево
Отрицательное - сдвиг вправо
*/
#include <iostream>
#include "list.h"

int main()
{
	std::cout << "Please, enter count of elements (not more, than MAX_INT)" << std::endl;
	int count;
	std::cin >> count;
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
	return 0;
}


