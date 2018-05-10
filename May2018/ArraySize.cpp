#include <iostream>

template<typename T, std::size_t N>
constexpr std::size_t ArraySize(T (&)[N]) noexcept
{
    return N;
}

int main()
{
    int myIntArray[] = {1, 2, 3, 4, 5};
    std::cout << "myIntArray size: " << ArraySize(myIntArray) << std::endl;

    float myFloatArray[] = {1.1f, 2.2f, 3.3f};
    std::cout << "myFloatArray size: " << ArraySize(myFloatArray) << std::endl;
}

