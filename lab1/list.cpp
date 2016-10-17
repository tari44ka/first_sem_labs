#include "list.h"
#include <iostream>


List::List()
{
	head = NULL;
	tail = NULL;
}

List::~List()
{
	Element *ptr = head;
	while (ptr != tail)
	{
		ptr = ptr->next;
		delete ptr->prev;
	}
	if (ptr != NULL)
		delete ptr;
	head = NULL;
	tail = NULL;
}

void List::addInTail(int value)
{
	Element *ptr = new Element;
	ptr->value = value;
	
	if (head == NULL)
	{
		ptr->next = ptr;
		ptr->prev = ptr;

		head = ptr;
		tail = ptr;
	}
	else
	{	
		ptr->prev = tail;
		ptr->next = head;
	
		head->prev = ptr;
		tail->next = ptr;
	
		tail = ptr;
	}
}

void List::moveHead(int position)
{
	if (position > 0)
		moveForward(position);
	else
		moveBack(position);
}

void List::moveForward(int position)
{
	while (position)
	{
		head = head->next;
		position--;
	}
	tail = head->prev;
}

void List::moveBack(int position)
{
	while (position)
	{
		head = head->prev;
		position++;
	}
	tail = head->prev;
}

void List::print()
{
	Element *ptr = head;
	while (ptr != tail)
	{
		std::cout << ptr->value << " ";
		ptr = ptr->next;
	}
	if (ptr != NULL)
	{
		std::cout << ptr->value;
	}
	std::cout << std::endl;
}

