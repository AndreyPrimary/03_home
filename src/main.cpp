#include "lib.h"

#define LOG_ALLOC
#define LOG_LIST

#include <iostream>
// #include <fstream>
// #include <sstream>
// #include <map>
// #include <vector>
// #include <iterator>
// #include <algorithm>

#include "ip_holder.h"


void testCommon()
{
    IpHolder holder_int(2345678);
    IpHolder holder_string((std::string)"string");

  	// SomeStruct first("Hello, World!");
	// SomeStruct second = first;
}

int main (int, char **)
{
    
    std::cout << "Design Version: " << version() << std::endl;

    testCommon();

    return 0;
}
