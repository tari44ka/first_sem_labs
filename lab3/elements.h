#ifndef ELEMENTS
#define ELEMENTS
#include <iostream>

//Класс, описывающий вызов лифта
class Call
{
    private:

    public:
    int floor_from;
    int time;
    int floor_to;
        friend std::istream & operator >>(std::istream & is, Call & call);
        friend std::ostream & operator <<(std::ostream & os, Call const & call);
};


#endif // ELEMENTS

