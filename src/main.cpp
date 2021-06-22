#include "lib.h"

#define LOG_ALLOC
#define LOG_LIST

#include <iostream>
#include <string>
// #include <fstream>
// #include <sstream>
// #include <map>
// #include <vector>
// #include <iterator>
// #include <algorithm>

#include "ip_holder.h"


void testCommon()
{
    // IpHolder holder_int(2345678);
    // IpHolder holder_string((std::string)"string");
    
    // std::list<int> int_list = {12,23,34,45,56};
    // IpHolder holder_list(int_list);

    // std::vector<int> int_vector = {98,87,76,65,54};
    // IpHolder holder_list(int_vector);

    int int_val = 2345678;
    print_ip(int_val);

    std::string string_val = "7610294";
    print_ip(string_val);

    std::list<int> int_list = {12,23,34,45,56};
    print_ip(int_list);

    std::vector<int> int_vector = {98,87,76,65,54};
    print_ip(int_vector);
}

void test()
{
    print_ip( char{-1} ); // 255
    print_ip( short{0} ); // 0.0
    print_ip( int{2130706433} ); // 127.0.0.1
    print_ip( long{8875824491850138409} );         // 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100,   200,   300,   400}   );   // 100.200.300.400
    print_ip( std::list<short>{400,   300,   200,   100}   );   // 400.300.200.100
}

int main (int, char **)
{
    
    std::cout << "Design Version: " << version() << std::endl;

    // testCommon();
    test();

    return 0;
}
