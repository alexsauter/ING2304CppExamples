#include <iostream>

//bool mybit = true; //Deklarasjon med verdi - tillatt

bool mybit; //Deklarasjon uten verdi - tillatt

//mybit = true; //Operasjon utenfor funksjon - ikke tillatt!!

int main()
{
    mybit = true; //Boolsk verdi "true" er gyldig
    //mybit = 1; //Tallverdi "1" er tolket som "true" for boolsk variabel - tillatt
    //mybit = 5; //Tallverdi "5" er også ulik 0 og derfor tolket som "true" - mulig
    if (mybit) {
        std::cout<<"Hello World";
    }

    return 0;
}

