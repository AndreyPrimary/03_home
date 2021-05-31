#pragma once

#include <iostream>
#include <memory>
#include <list>

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
template <typename T>
class IpHolderBase {
public:
    IpHolder(T value)
    {
        ipList ip_list = to_ipList(value);

        std::cout << "[" << to_String(ip_list) << "]" << std::endl;
    }

private:    
    using ip_data = BYTE;
    using ipList = std::list<ip_data>;
    // ipList ip_list;

    ipList to_ipList(const T& value)
    {
        ipList ip_list;

        ip_list.push_back(std::to_string(value));

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

};
*/

/*
// 1. Адрес  может  быть  представлен  в  виде  произвольного  целочисленного  типа.  
// Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
// с символом `.`(символ точки) в качестве разделителя. Выводятся все байты числа. 
template <typename T, 
    // typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    // std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    // typename std::enable_if<std::is_integral<T>::value,T>::type* = nullptr>
    std::enable_if_t<std::is_integral<T>::value, bool> = true>
class IpHolder {
  
public:
    IpHolder(T value)
    {
        ipList ip_list = to_ipList(value);

        std::cout << "[" << to_String(ip_list) << "]" << std::endl;
    }

private:    
    using ip_data = BYTE;
    using ipList = std::list<ip_data>;
    // ipList ip_list;

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

};

// the partial specialization of A is enabled via a template parameter
// template<class T, class Enable = void>
// class A {}; // primary template

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

// 3.Адрес  может  быть  представлен  в  виде  контейнеров  `std::list`,  `std::vector`. 
// Выводится  полное  содержимое  контейнера  поэлементно  и  разделяется  `.`  (символом точка). 
// Элементы выводятся как есть. 

// 4.Опционально адрес может быть представлен в виде `std::tuple` при условии, что все типы одинаковы. 
// Выводится полное содержимое поэлементно и разделяется `.` (одним символом  точка).  
// Элементы  выводятся  как  есть.  
// В  случае,  если  типы  кортежа  не одинаковы, должна быть выдана ошибка при компиляции кода.





//----------------------------------------------------------------

class IpHolder {
// 1. Адрес  может  быть  представлен  в  виде  произвольного  целочисленного  типа.  
// Выводить побайтово в беззнаковом виде, начиная со старшего байта, 
// с символом `.`(символ точки) в качестве разделителя. Выводятся все байты числа. 
  
public:

    template <typename T, 
        std::enable_if_t<std::is_integral<T>::value, bool> = true>
    IpHolder(T value)
    {
        ipList ip_list = to_ipList(value);

        std::cout << "[" << to_String(ip_list) << "]" << std::endl;
    }

    template <typename T, typename U = std::string,
        std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
    IpHolder(T value)
    // void IpHolder(std::string value)
    {
        std::cout << "[" << value << "]" << std::endl;
    }

private:    
    using ip_data = BYTE;
    using ipList = std::list<ip_data>;
    // ipList ip_list;

    template <typename T, 
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

