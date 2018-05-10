#include <iostream>

template <unsigned int n>
struct factorial
{
	static const int value = n * factorial<n - 1>::value ;
};

template <>
struct factorial<0>
{
	static const int value = 1 ;
};

int main()
{
	std::cout << "Factorial 5 is " << factorial<5>::value << std::endl;
}


