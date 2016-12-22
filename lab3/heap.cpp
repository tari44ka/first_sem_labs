#include "heap.h"
#include <iostream>

Heap::Heap()
{
    lastIndex = -1;
}

bool Heap::isEmpty()
{
    return (lastIndex == -1);
}

bool Heap::setDirection(bool increase)
{
    increaseDirection = increase;
}

void Heap::push(int value)
{
    //проверяем, что такого элемента нет
    //todo: проверить, может можно сделать быстре???
    for (int i = 0; i <= lastIndex; ++i)
    {
        if (data[i] == value)
            return;
    }
    //добавляем элемент в конец массива для кучи
    lastIndex ++;
    if (data.size() == lastIndex)
        data.push_back(value);
    else
        data[lastIndex] = value;

    //вызываем функцию починки пирамиды, в которой возможно нарушен один элемент
    repairHeap(lastIndex);

}

void Heap::repairHeap(int index)
{
    if (index == 0)
        return;
    int parent = getParent(index);
    if (increaseDirection)
    {
        if (data[parent] > data[index])
            return;
    }
    else
    {
        if (data[parent] < data[index])
            return;
    }
    std::swap(data[parent], data[index]);
    repairHeap(parent);
    //todo: избавиться от рекурсии
}

int Heap::getParent(int index)
{
    return (index + 1)/ 2 - 1;
}

int Heap::getTop()
{
    if (lastIndex < 0)
    {
        std::cout << "ERROR: you try to get top from empty heap";
        return 0;
    }
    return data[0];
}

void Heap::pop()
{
    if (lastIndex < 0)
    {
        std::cout << "ERROR: you try to remove top from empty heap";
        return ;
    }
    std::swap(data[0], data[lastIndex]);
    lastIndex --;
    max_heapify(0);
}

void Heap::max_heapify(int index)
{
    int left = leftIndex(index);
    int right = rightIndex(index);
    int mustBeHeap = index;
    if (left <= lastIndex)
    {
        if (increaseDirection)
        {
            if (data[left] > data[index])
            {
               mustBeHeap = left;
            }
        }
        else
        {
            if (data[left] < data[index])
            {
                mustBeHeap = left;
            }
        }
    }
    if (right <= lastIndex)
    {
        if (increaseDirection)
        {
            if (data[right] > data[mustBeHeap])
            {
               mustBeHeap = right;
            }
        }
        else
        {
            if (data[right] < data[mustBeHeap])
            {
                mustBeHeap = right;
            }
        }
    }
    if (mustBeHeap != index)
    {
        std::swap(data[mustBeHeap], data[index]);
        max_heapify(mustBeHeap);
    }
    //todo: избавиться от рекурсии
}


int Heap::leftIndex(int index)
{
    return 2*(index + 1) - 1;
}

int Heap::rightIndex(int index)
{
    return 2*(index + 1);
}


void Heap::print()
{
    for (int i = 0; i <= lastIndex; ++i)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void Heap::clear()
{
    lastIndex = -1;
}
