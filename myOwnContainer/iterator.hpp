#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	// itertator tag
	// iterator_traits에서 쓸 itertator tag의 계층 구조 정의
	struct input_iterator_tag {};
	/// Marking output iterators.
	struct output_iterator_tag {};
	/// Forward iterators support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag {};
	/// Bidirectional iterators support a superset of forward iterator operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	/// Random-access iterators support a superset of bidirectional iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	
	// iterator_traits class
	// 전달된 이터레이터 의 속성과 범위를 결정
	template <class Iterator>
	class iterator_traits
	{
		public:
		typedef typename Iterator::difference_type      difference_type;
		typedef typename Iterator::value_type           value_type;
		typedef typename Iterator::pointer              pointer;
		typedef typename Iterator::reference            reference;
		typedef typename Iterator::iterator_category    iterator_category;	
	};
	
	template <typename T>
	class iterator_traits<T*>
	{
		public:
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};
	
	template<typename T>
	class iterator_traits<const T*>
	{
		public:
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// iterator class
	template <class Category, class T,
		class Distance = ptrdiff_t, class Pointer = T*,
			class Reference = T&>
	class iterator
	{
		private:
			/* data */
			
		public:
			typedef  Category  iterator_category;
			typedef  T	     value_type;
			typedef  Distance  difference_type;
			typedef  Reference reference;
			typedef  Pointer   pointer;
	};
	

}

#endif