#include <iostream>
#include <string>
#include <time.h>


class Timer
{
public:
    Timer(std::string name) : _name(name)
    {
        _start_time = clock();
    }

    ~Timer()
    {
        _end_time = clock();
        std::cout << "Timer " << _name << ": " << (_end_time - _start_time) / (double)CLOCKS_PER_SEC << " seconds" << std::endl;
    }
private:
    clock_t _start_time;
    clock_t _end_time;
    std::string _name;
};
