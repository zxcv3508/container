#include <iostream>
// #include <type_traits>
// #include "type_traits.hpp"
#include "Random_access_iterator.hpp"
#include <vector>
#include "vector.hpp"
#include "nullptr.hpp"

// class A {};

// // 정수 타입만 받는 함수
// template <typename T>
// void only_integer(const T& t) {
//   static_assert(std::is_integral<T>::value);
//   std::cout << "T is an integer \n";
// }

// int main() {
//   int n = 3;
//   only_integer(n);

// //   A a;
// //   only_integer(a);
// }
class AAA{
	int a();
};
int ccc(){}
int main ()
{
	ft::vector<int> a ;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	ft::vector<int> b ;
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(5);
	b.push_back(6);
	b.push_back(7);
	int d = 0;
	// for (ft::vector<int>::iterator i = a.begin() ; i != a.end(); i++)
	// {
	// 	std::cout << *i << std::endl;
	// 	d++;
	// 	if (d == 6)
	// 		break;
	// }
	for (ft::vector<int>::reverse_iterator i = b.rbegin() ; i != b.rend(); i++)
	{
		std::cout << *i << std::endl;
		d++;
		if (d == 10)
			break;
	}
	std::cout  << std::endl;
	for (ft::vector<int>::reverse_iterator i = a.rbegin() ; i != a.rend(); i++)
	{
		std::cout << *i << std::endl;
		d++;
		if (d == 6)
			break;
	}
}