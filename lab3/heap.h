#ifndef HEAP
#define HEAP

#include <vector>

class Heap
{
    public:
        bool setDirection(bool increase);
        void push(int value);
        void pop();
        int getTop();
        bool isEmpty();
        void print();
        void clear();
        Heap();
    private:
        std::vector<int> data;
        int lastIndex;
        bool increaseDirection;
        void repairHeap(int lastIndex);
        int getParent(int index);
        void max_heapify(int index);
        int leftIndex(int index);
        int rightIndex(int index);



};
#endif // HEAP

