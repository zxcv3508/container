#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <memory>
#include <iostream>

namespace ft
{
	//enable_if
	template<bool B, class T = void>
	struct enable_if {};
		
	template<class T>
	struct enable_if<true, T> { typedef T type; };
	
	//is_integral
template <bool is_integral, typename T>
	struct integral_traits {
		typedef T type;
		static const bool value = is_integral;
	};

	//float, double, long double은 false로 처리된다.
	//char16_t, char32_t, long long, unsigned long long -> c++11
	template <typename>
	struct is_integral_type : public integral_traits<false, bool> {};

	// template 특수화
	// bool 타입에 대해 특수화
	template <>
	struct is_integral_type<bool> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<char> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<signed char> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<wchar_t> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<short int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<long int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<long long int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned char> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned short> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned long int> : public integral_traits<true, bool> {};

	template <>
	struct is_integral_type<unsigned long long int> : public integral_traits<true, bool> {};

	/**
	 * T가 integral type인지 식별하는 class.
	 * is_integral_type< T > 를 상속받아 T에 따라 type을 다르게 갖는다.
	 */
	template <typename T>
	struct is_integral : public is_integral_type<T> {};

	
	//iterator_traits
	
}
#endif
