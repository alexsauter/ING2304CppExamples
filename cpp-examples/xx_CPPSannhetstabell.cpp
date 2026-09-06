#include <iostream>

bool x = false;
bool y = false;


int main()
{
    for (int i=0; i<4; i++) {

    //x og y med output, her for xor
    std::cout<<y << "|" << x<< "|" << (x xor y) << std::endl;

    //Lage neste x og y
    y = x xor y;
    x = !x;
    }
    return 0;
}
