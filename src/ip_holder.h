#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <vector>

/** @file      ip_holder.h
 * @brief      print ip address from different source data
 * @details    This simply example for using SFINAE in template
 * for printing ip address from different data type
 * @author     AndreyPrimary
 * @copyright  MIT License, see repository LICENSE file
 */


// Реализовать функцию печати условного IP-адреса.  
// Условность его заключается в том, что количество элементов 
// не обязательно должно быть равно 4-ём или 8-ми, 
// а также каждый элемент не обязательно должен быть из диапазона 0..255. 
// От идеи IP-адреса остаётся фактически только вывод элементов через `.` (символ точки). 
// Функцию  нужно  реализовать  для  различных  входных  параметров  
// путём  использования механизма SFINAE. 
// Всего  нужно  выполнить  3  обязательных  и  один  опциональный  вариант функции. 

/*
// Проверка что тип имеет итератор
template<typename T, typename = void>
struct is_iterator
{
   static constexpr bool value = false;
};

template<typename T>
struct is_iterator<T, typename std::enable_if<
    !std::is_same<typename std::iterator_traits<T>::value_type, void>::value
    >::type>
{
   static constexpr bool value = true;
};
*/

// 1. Адрес  может  быть  представлен  в  виде  произвольного  целочисленного  типа.  
// Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
// с символом `.`(символ точки) в качестве разделителя. Выводятся все байты числа. 

using BYTE = unsigned char;
using ipList = std::list<BYTE>;

/** @brief   A silly function that wraps print_ip()
 * @details  Адрес  может  быть  представлен  в  виде  произвольного  целочисленного  типа.  
 * Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
 * с символом `.`(символ точки) в качестве разделителя. Выводятся все байты числа. 
 * @param    val  An integer compatible type
 * @return   0 - no error
 */
template <typename T, 
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
int print_ip(T val)
{
    BYTE    ip;
    T       rest = val;

    ipList ip_list;

    for (size_t i = 0; i < sizeof(T); i++) {
    // while (rest != 0) {
        ip = rest % 0x100;
        rest = rest / 0x100;
        ip_list.push_front(ip);
    }

    std::string res;

    for (const auto val : ip_list) {
        if (!res.empty()) {
            res += ".";
        }
        res += std::to_string(val);
    }

    std::cout << "[" << res << "]" << std::endl;

    return 0;
}

// 2.Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого. 

/** @brief   A silly function that wraps print_ip()
 * @details  Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого. 
 * @param    val  An std::string compatible type
 * @return   0 - no error
 */
template <typename T, 
    std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
int print_ip(T val)    
{
    std::cout << "[" << val << "]" << std::endl;

    return 0;
}

// 3.Адрес  может  быть  представлен  в  виде  контейнеров  `std::list`,  `std::vector`. 
// Выводится  полное  содержимое  контейнера  поэлементно  и  разделяется  `.`  (символом точка). 
// Элементы выводятся как есть. 

/** @brief   A silly function that wraps print_ip()
 * @details  Адрес  может  быть  представлен  в  виде  контейнеров  `std::list`,  `std::vector`. 
 * Выводится  полное  содержимое  контейнера  поэлементно  и  разделяется  `.`  (символом точка). 
 * Элементы выводятся как есть. 
 * @param    val  An std::string compatible type
 * @return   0 - no error
 */
template <
        template <class, class...> class Vec,
        class Tvec,
        class... Other,
        std::enable_if_t<
            (std::is_same<Vec<Tvec>, std::vector<Tvec>>::value 
            || std::is_same<Vec<Tvec>, std::list<Tvec>>::value),
            int> = 0>
int print_ip(const Vec<Tvec, Other...> &indata)
{
    std::string res;

    for (const auto val : indata) {
        if (!res.empty()) {
            res += ".";
        }
        res += std::to_string(val);
    }

    std::cout << "[" << res << "]" << std::endl;

    return 0;
}
