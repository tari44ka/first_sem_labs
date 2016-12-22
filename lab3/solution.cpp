#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "heap.h"
#include "elements.h"



bool compByTime(Call c1, Call c2)
{
        return (c1.time < c2.time);
}

//todo: почему библиотечка не цепляется?
int abs(int a)
{
    return (a>= 0)? a : -1 * a;
}

/*
    Читать из файла вызовы.
    Сяитается, что в файле записаны вызовы в следующем формате:
    время - номер этажа, с которого вызывают - номер этажа, на который поедут.
*/
void readFromFile(char* fileName, std::vector<Call> &calls)
	throw (int)
{
	std::ifstream fin (fileName);
	if (!fin.is_open())
	{
		std::cout << "error in open file";
		throw 1;
	}
	calls.clear();
	while (!fin.eof())
	{
                Call call;
                fin >> call;
		calls.push_back(call);
	}
	//todo: понять природу данного костыля и удалить его
        // почему-то последняя запись из файла считывается два раза.
	calls.pop_back();
}

void print(std::vector<Call> &calls)
{
        std::cout << calls.size() << std::endl;
        for (std::vector<Call>::iterator it = calls.begin(); it != calls.end();it++)
            std::cout << *it << std::endl;
}


/*
Данная функция ищет самую интересную цель. Эта цель должна быть самой ранней, а среди
самых ранних - максимально далекой
*/
int findNext(std::vector<Call> &calls, int curFloor)
{
    int index = 0;
    int maxDistance = abs(curFloor - calls[0].floor_from);
    int time = calls[0].time;
    int i = 1;
    while ((i < calls.size()) && (calls[i].time == time))
    {
        int curDistance = abs(curFloor - calls[i].floor_from);
        if (curDistance > maxDistance)
        {
            maxDistance = curDistance;
            index = i;
        }
        i++;
    }
    return index;
}

/*Функция проверяет, нет ли до и включая текущего момента вывозов лифта с данного этажа в нужном направлении*/
void haveCallHere(std::vector<Call> &calls, int curTime, int curFloor,
                  std::vector<int> &indexes)
{
    indexes.clear();
    int i = 0;
    while ((i < calls.size()) && (calls[i].time < curTime))
    {
        if (calls[i].floor_from == curFloor)
            indexes.push_back(i);
        i++;
    }
}

bool callInDirection(int curFloor, int floorTo, bool increase)
{
    return increase? (floorTo > curFloor) : (floorTo < curFloor);
}
void findElevatorPlace(std::vector <Call> &calls)
{
        std::sort (calls.begin(), calls.end(), compByTime);

        int curTime = 1;
        int curFloor = 1;
        bool increase = true;

        int currentTarget = 0;
        Heap targetHeap;

        /*У лифта два состояния:
            1) Есть цель: тогда идем в этом направлении собирая по пути всех тех,
               кто под эту цель подходит (едет в том же направлении)
            2) Нет цели: тогда берем самый ранний по времени вызов, и едем к нему.
               если "ранних" вызовов несколько, берем тот, что дальше*/
        while (!targetHeap.isEmpty() || !calls.empty())
        {
            std::cout << curTime << " - " << curFloor << std::endl;

            // 1.проверить, нет ли с текущего этажа вызова лифта, который случился раньше, чем
            // текущий момент
            std::vector<int> indexes;
            haveCallHere(calls, curTime, curFloor, indexes);
            // Если вызовы есть, то в лифт зайдут только те люди, которые едут в нужном направлении.
            // Если направления нет, то те, которые с первым.
            bool haveStop = false;
            if (!indexes.empty())
            {
                if (currentTarget == 0)
                {
                    increase = calls[indexes[0]].floor_to > curFloor;
                    targetHeap.setDirection(!increase);
                }

                std::vector <int> toDelete;
                for (int i = 0; i < indexes.size(); ++i)
                {
                    int floorTo = calls[indexes[i]].floor_to;
                    if (callInDirection( curFloor, floorTo,  increase))
                    {
                            std::cout << "somebody in (and want on " << calls[indexes[i]].floor_to << " floor)" << std::endl;
                            haveStop = true;
                            int floorTo = calls[indexes[i]].floor_to;
                            if (floorTo > currentTarget)
                                currentTarget = floorTo;
                            targetHeap.push(floorTo);
                            toDelete.push_back(indexes[i]);
                    }

                }
                for (int i = 0; i < toDelete.size(); ++i)
                {
                    for (int j = toDelete[i] +1; j < calls.size(); ++j)
                    {
                        calls[j -1] = calls[j];
                    }
                    calls.pop_back();
                }
            }
            // Если есть кому выйти:

            if (!targetHeap.isEmpty() && (curFloor == targetHeap.getTop()))
            {
                std::cout << "somebody goes out" << std::endl;
                targetHeap.pop();
                if (currentTarget == curFloor)
                    currentTarget = 0;
            }
            // 2. если лифту некуда ехать, найти самый далекий вызов, и отправиться к нему.
            if ((currentTarget == 0)  && !calls.empty())
            {
                if (calls[0].time < curTime)
                {
                    int index = findNext(calls, curFloor);
                    currentTarget = calls[index].floor_from;
                    increase = calls[index].floor_from > curFloor;
                    targetHeap.setDirection(!increase);
                    std::cout << "new target is  " << calls[index].floor_from  << std::endl;
                }
            }
            curTime ++;
            if (!haveStop && (currentTarget != 0))
            {
                if (increase)
                    curFloor ++;
                else
                    curFloor--;
            }

        }
}

int main()
{
        std::vector<Call> calls;
	//todo: на эту передачу ругается warning. Найти проблему и решить
	readFromFile("input.txt", calls);

        std::cout<< "input calls are: " << std::endl;
        print(calls);
        std::cout << " ---------- " << std::endl;
	

        std::cout << "Elevator path is: " << std::endl;
        findElevatorPlace(calls);

  /*  Heap heap;
    heap.setDirection(false);
    int command;
    do
    {
        std::cout << "enter coomand ";
        std::cin >> command;
        switch(command)
        {
            case 1:
                {
                int value;
                std::cin >> value;
                heap.push(value);
                break;
            }
        case 2:
            {
                std::cout << heap.getTop();
                break;
        }
        case 3:
            {
                heap.pop();
        }
        }
        heap.print();
    }while (command != 0);*/
    return 0;
}
