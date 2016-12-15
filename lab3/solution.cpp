#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Call
{
	int floor_from;
	int time;
	int floor_to;
};

struct Point
{
	int time;
        int floor;
};

bool compByTime(Call c1, Call c2)
{
        return (c1.time > c2.time);
}

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
		std::cout << "a " ;
		//todo: настроить чтение через перегрузку оператора
		Call call;
		fin >> call.time;
		fin >> call.floor_from;
		fin >> call.floor_to;
		calls.push_back(call);
	}
	//todo: понять природу данного костыля и удалить его
	calls.pop_back();
}

void print(std::vector<Call> &calls)
{
	//todo: заменить на итератор
	std::cout << calls.size() << std::endl;
	for (int i = 0; i < calls.size(); ++i)
	{
		//todo: настроить через перегрузку оператора
		std::cout << calls[i].time << " ";
		std::cout << calls[i].floor_from << " ";
		std::cout << calls[i].floor_to << std::endl;
	}
}

void print(std::vector<Point> &points)
{
        //todo: заменить на итератор
        std::cout << calls.size() << std::endl;
        for (int i = 0; i < points.size(); ++i)
        {
                //todo: настроить через перегрузку оператора
                std::cout << points[i].time << " ";
                std::cout << points[i].floor << std::endl;
        }
}

/*
Данная функция ищет самую интересную цель. Эта цель должна быть в указанный момент
времени  curTime и быть максимально далеко от curFloor
Также известно, что все объекты с указанным временем находятся в начале вектора
*/
int findNext(std::vector<Call> &calls, int curTime, int curFloor)
{
    int index = 0;
    int maxDistance = abs(curFloor - calls[0].floor_from);
    int i = 1;
    while ((i < calls.size()) && (calls[i].time <= curTime))
    {
        int curDistance = abs(curFloor - calls[i].floor_from);
        if (curDistance > maxDistance)
        {
            maxDistance = curDistance;
            index = i;
        }
    }
    return index;
}

/*Функция проверяет, нет ли до и включая текущего момента вывозов лифта с данного этажа в нужном направлении*/
void haveCallHere(std::vector<Calls> &calls, int curTime, int curFloor, bool increase,
                  std::vector<Calls> &indexes)
{
    indexes.clear();
    int i = 0;
    while ((i < calls.size()) && (calls[i].time <= curTime))
    {
        if ((calls[i].floor_from == curFloor) &&
            (calls[i].floor_to > curFloor) == increase)
            indexes.push_back(i);
    }
}

void findElevatorPlace(std::vector <Call> &calls,
                       std::vector <Point> &points)
{
        //todo: отсортировать вызовы
        Point start;
        start.time = 0;
        start.floor = 1;
        points.push_back(start);

        int currZhile = 0;
        int curTime = 1;
        int curFloor = 1;
        bool increase = true;


        /*У лифта два состояния:
            1) Есть цель: тогда идем в этом направлении собирая по пути всех тех,
               кто под эту цель подходит (едет в том же направлении)
            2) Нет цели: тогда берем самый ранний по времени вызов, и едем к нему.
               если "ранних" вызовов несколько, берем тот, что дальше*/
        while (currZhile != 0 && !points.empty())
        {
            Point point;
            point.time = curTime;
            point.floor = curFloor;
            points.push_back(point);
            if (currZhile == 0)
            {
                if (points[0].time <= curTime)
                {
                    int index = findNext(calls, curTime, curFloor);
                    currZhile = calls[index].floor_from;
                    incrase = (curZhile > curFloor);
                }
            }
            else
            {
                bool haveStop = false;
                //TODO выше: соорудить кучу из целей пассажиров, упорядоченную по направлению поездки
                if (curFloor == /*Взять из кучи голову*/)
                {
                    /*TODO: Удалить из кучи голову*/
                    haveStop = true;
                }
                std::vector<int> indexes;
                haveCallHere(calls, curTime, curFloor, increase, indexes);
                if (!indexes.empty())
                {
                    haveStop = true;
                    /*Пояснение: Грузим всех, кто стоит на этом этаже и едет в нужную сторону*/
                    for (int i = indexes.size() - 1; i >= 0; --i)
                    {
                        /*TODO: добавить их цель в кучу целей*/
                        calls.remove(indexes[i]);
                    }
                }
                if (!haveStop)
                {
                    curFloor++;
                }
            }
            curTime ++;
        }
}

int main()
{
	std::vector<Call> calls;
	//todo: на эту передачу ругается warning. Найти проблему и решить
	readFromFile("input.txt", calls);
	
        std::vector<Point> points;

        findElevatorPlace(calls, points);
        print(points);
	return 0;
}
