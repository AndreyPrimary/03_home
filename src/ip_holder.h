#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <vector>

// Реализовать функцию печати условного IP-адреса.  
// Условность его заключается в том, что количество элементов 
// не обязательно должно быть равно 4-ём или 8-ми, 
// а также каждый элемент не обязательно должен быть из диапазона 0..255. 
// От идеи IP-адреса остаётся фактически только вывод элементов через `.` (символ точки). 
// Функцию  нужно  реализовать  для  различных  входных  параметров  
// путём  использования механизма SFINAE. 
// Всего  нужно  выполнить  3  обязательных  и  один  опциональный  вариант функции. 

using BYTE = unsigned char;

/*
// Проверка что тип int
template<typename T, typename = void>
struct is_integer
{
   static constexpr bool value = false;
};

template<typename T>
struct is_integer<T, typename std::enable_if<
    std::is_integral<T>::value
    && std::is_same<typename std::iterator_traits<T>::value_type, void>::value
    >::type >
{
   static constexpr bool value = true;
};
*/
/*
// Проверка что тип std::string
template<typename T, typename = void>
struct is_string
{
   static constexpr bool value = false;
};

template<typename T>
struct is_string<T, typename std::enable_if<std::is_same<T, std::string>::value>::type >
{
   static constexpr bool value = true;
};
*/
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
    // && !std::is_same<T, std::string>::value
    >::type>
{
   static constexpr bool value = true;
};
*/

// template< typename T >
// using IsSigned = std::enable_if_t< std::is_signed_v< T > >;

// template<typename T, typename Allocator>
// using is_iterator = std::enable_if<
//     !std::is_same<typename std::iterator_traits<T,Allocator>::value_type, void>::value
//     >;

template<typename T, typename Allocator>
using is_iterator = std::enable_if_t<
    !std::is_same<typename std::vector<T,Allocator>::value_type, void>::value
    || !std::is_same<typename std::list<T,Allocator>::value_type, void>::value
    >;

// std::is_integral<T>::value

// struct is_std_vector<std::vector<T,A>> : std::true_type {};

// 1. Адрес  может  быть  представлен  в  виде  произвольного  целочисленного  типа.  
// Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
// с символом `.`(символ точки) в качестве разделителя. Выводятся все байты числа. 

// 2.Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого. 

// 3.Адрес  может  быть  представлен  в  виде  контейнеров  `std::list`,  `std::vector`. 
// Выводится  полное  содержимое  контейнера  поэлементно  и  разделяется  `.`  (символом точка). 
// Элементы выводятся как есть. 

// 4.Опционально адрес может быть представлен в виде `std::tuple` при условии, что все типы одинаковы. 
// Выводится полное содержимое поэлементно и разделяется `.` (одним символом  точка).  
// Элементы  выводятся  как  есть.  
// В  случае,  если  типы  кортежа  не одинаковы, должна быть выдана ошибка при компиляции кода.




//----------------------------------------------------------------

class IpHolder {
  
public:

// 1. Адрес  может  быть  представлен  в  виде  произвольного  целочисленного  типа.  
// Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
// с символом `.`(символ точки) в качестве разделителя. Выводятся все байты числа. 
    template <typename T, //typename U = int,
        // typename = is_integer < T > >
        std::enable_if_t<std::is_integral<T>::value, bool> = true>
    IpHolder(T value)
    {
        ipList ip_list = to_ipList(value);

        std::cout << "[" << to_String(ip_list) << "]" << std::endl;
    }

// 2.Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого. 
    template <typename T, //typename U = std::string,
        // typename = is_string < T > >
        std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
    IpHolder(T value)
    {
        std::cout << "[" << value << "]" << std::endl;
    }

// 3.Адрес  может  быть  представлен  в  виде  контейнеров  `std::list`,  `std::vector`. 
// Выводится  полное  содержимое  контейнера  поэлементно  и  разделяется  `.`  (символом точка). 
// Элементы выводятся как есть. 
    // template <typename T, typename U = std::list<T>,
        // std::enable_if_t<std::is_same<T, decltype(std::list<T>)>::value
        //     /*|| std::is_same<T, std::vector<T>>::value*/, bool> = true>
    // template <typename T, typename std::enable_if<is_iterator<T>::value, bool> = true>

    // template <typename T, typename U = std::list<T>,
    //     typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type>

    // struct is_iterator<T, typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type>

    // template <typename T, typename U = std::list<T>,
    //     typename std::enable_if<std::is_member_object_pointer <T>> >

    // template <typename T, //typename U = std::list<T>,
    //     typename = is_iterator< T > >

    template <typename T, typename U = std::allocator<T>,
        // typename = is_iterator< T,  U>  >
        is_iterator< T,  U> = true >
        // is_iterator< T,  U> >
    IpHolder(T value)
    {
        std::cout << "[" << to_String(value) << "]" << std::endl;
    }

private:    
    using ip_data = BYTE;
    using ipList = std::list<ip_data>;
    // ipList ip_list;

    template <typename T, //typename U = int,
        // typename = is_integer < T > >
        std::enable_if_t<std::is_integral<T>::value, bool> = true>
    ipList to_ipList(const T& value)
    {
        ip_data ip;
        T       rest = value;

        ipList ip_list;

        while (rest != 0) {
            ip = rest % 0x100;
            rest = rest / 0x100;
            ip_list.push_back(ip);
        }

        return ip_list;
    }

    std::string to_String(const ipList &ip_list)
    {
        std::string res;

        for (const auto val : ip_list) {
            if (!res.empty()) {
                res += ".";
            }
            res += std::to_string(val);
        }

        return res;
    }

    // template <typename T, typename U = std::list<T>,
        // std::enable_if_t<std::is_same<T, std::list<int>>::value
        //     || std::is_same<T, std::vector<T>>::value, bool> = true>

    // template <typename T, typename std::enable_if<is_iterator<T>::value, bool> = true>

    // template <typename T, typename U = std::list<T>,
    //     typename std::enable_if<!std::is_same<typename std::iterator_traits<T>::value_type, void>::value>::type>

    // template <typename T, //typename U = std::allocator<T>,
    //     typename = is_iterator< T >  >

    template <typename T, typename U = std::allocator<T>,
        // typename = is_iterator< T,  U>  >
        is_iterator< T,  U> = true >
        // is_iterator< T,  U> >
    std::string to_String(const T& value)
    {
        std::string res;

        for (const auto val : value) {
            if (!res.empty()) {
                res += ".";
            }
            res += std::to_string(val);
        }

        return res;
    }

};

// the partial specialization of A is enabled via a template parameter
// template<class T, class Enable = void>
// class A {}; // primary template
/*
// 2.Адрес может быть представлен в виде строки. Выводится как есть, вне зависимости от содержимого. 
template <typename T, typename U = std::string,
    // typename std::enable_if_t<std::is_class<T>::value>* = nullptr>
    // typename std::enable_if_t<!std::is_integral<T>::value, bool> = true>
    // class Enable = void>
    // typename std::enable_if<std::is_class<T>::value,T>::type* = nullptr>
    // std::enable_if_t<std::is_class<T>::value>* = nullptr>
    // std::enable_if_t<!std::is_integral<T>::value, bool> = true>
    std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>

class IpHolder {
 
public:
    IpHolder(T value)
    // void IpHolder(std::string value)
    {
        std::cout << "[" << value << "]" << std::endl;
    }
};
*/
//---------------------------------------

#include <string>
#include <type_traits>

struct SomeStruct {

	template<typename TT, 
		typename Fake = 
			typename std::enable_if<
				!std::is_same<typename std::remove_reference<TT>::type, 
					SomeStruct>::value, void>::type
	>
	SomeStruct(TT&& value) : m_value{std::forward<TT>(value)} {

	}

	SomeStruct(const SomeStruct& other) : m_value{other.m_value} {

	}

    const std::string& getValue() const {
		return m_value;
	}

private:
	std::string m_value;
	std::string m_value2;
};


/*
int main() {

	SomeStruct first("Hello, World!");
	SomeStruct second = first;

	return 0;
}
*/

