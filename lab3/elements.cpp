#include "elements.h"

 std::istream & operator >>(std::istream & is, Call & call)
{
    is >> call.time;
    is >> call.floor_from;
    is >> call.floor_to;

}

 std::ostream & operator <<(std::ostream & os, Call const & call)
{
    os << call.time << " ";
    os << call.floor_from << " ";
    os << call.floor_to << std::endl;
}
