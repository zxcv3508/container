#ifndef UTILL_HPP
#define UTILL_HPP

#include "iterator.hpp"
namespace ft
{
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n;
		n = 0;
		while (first++ != last)
			n++;
		return (n);
	}
	
	template <bool B, class T = void>
	struct enable_if {};
	
	template <class T>
	struct enable_if<true, T> { typedef T type; };
	
	//is_integral
	template <bool is_integral, typename T>
	struct is_intergral_base {
		typedef T type;
		static const bool value = is_integral;
	};

	//float, double, long double은 false로 처리된다.
	//char16_t, char32_t, long long, unsigned long long -> c++11

	template <typename>
	struct is_integral : public is_intergral_base<false, void> {};
	
	template <>
	struct is_integral<bool> : public is_intergral_base<true, bool> {};
	
	template <>
	struct is_integral<char> : public is_intergral_base<true, char> {};
	
	template <>
	struct is_integral<signed char> : public is_intergral_base<true, signed char> {};
	
	template <>
	struct is_integral<unsigned char> : public is_intergral_base<true, unsigned char> {};
	
	template <>
	struct is_integral<short> : public is_intergral_base<true, short> {};
	
	template <>
	struct is_integral<int> : public is_intergral_base<true, int> {};
	
	template <>
	struct is_integral<long> : public is_intergral_base<true, long> {};
	
	template <>
	struct is_integral<unsigned long> : public is_intergral_base<true, unsigned long> {};
	
	template <>
	struct is_integral<long long> : public is_intergral_base<true, long long> {};
	
	template <>
	struct is_integral<unsigned long long> : public is_intergral_base<true, unsigned long long> {};
	
	template <>
	struct is_integral<wchar_t> : public is_intergral_base<true, wchar_t> {};
	template <>
	struct is_integral<char16_t> : public is_intergral_base<true, char16_t> {};
	template <>
	struct is_integral<char32_t> : public is_intergral_base<true, char32_t> {};
}

#endif