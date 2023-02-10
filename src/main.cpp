#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "read_bib.h"

int main(void)
{


    // std::cout << bibparser::bib_file[1] << std::endl;

    enum Color { red = 1, green = 2, blue = 3 };
Color r = red;
 
switch(r)
{
    case red  : std::cout << "red\n";   break;
    case green: std::cout << "green\n"; break;
    case blue : std::cout << "blue\n";  break;
}
    
    return 0;
}



