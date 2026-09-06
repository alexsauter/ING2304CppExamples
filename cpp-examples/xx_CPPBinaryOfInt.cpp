#include <iostream>
#include <bitset>

int a = 0B10110;

int main()
{
    std::cout << sizeof(a) << " byte containing the bits " << std::bitset<32>(a) << '\n';

    return 0;
}
