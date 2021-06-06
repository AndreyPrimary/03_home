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
    // IpHolder holder_string((std::string)"string");
    
    // std::list<int> int_list = {12,23,34,45,56};
    // IpHolder holder_list(int_list);

    // std::vector<int> int_vector = {98,87,76,65,54};
    // IpHolder holder_list(int_vector);

}

int main (int, char **)
{
    
    std::cout << "Design Version: " << version() << std::endl;

    testCommon();

    return 0;
}
