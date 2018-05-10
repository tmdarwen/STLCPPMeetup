#include <iostream>
bool DoPrimeCheck(int number, int divisor)
{
    if(divisor == 2)
    {
        return number % 2;
    }
    return DoPrimeCheck(number, divisor / 2);
}

bool IsPrime(int number)
{
    return DoPrimeCheck(number, number / 2);
}

int main()
{
    if(IsPrime(13))
    {
        std::cout << "Is prime." << std::endl;
    }
    else
    {
        std::cout << "Is not prime." << std::endl;
    }
}
