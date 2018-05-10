#include <iostream>

template<unsigned p, unsigned d>
struct DoIsPrime
{
    static const bool value = (p % d != 0) && DoIsPrime<p, d - 1>::value;
};

template<unsigned p>
struct DoIsPrime<p, 2>
{
    static const bool value = (p % 2 != 0);
};

template<unsigned p>
struct IsPrime
{
    static const bool value = DoIsPrime<p, p / 2>::value;
};

int main()
{
    if(IsPrime<13>::value)
    {
        std::cout << "Is prime." << std::endl;
    }
    else
    {
        std::cout << "Is not prime." << std::endl;
    }
}
