#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <memory>
#include "Iterator.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator : public ft::Iterator<ft::random_access_iterator_tag, T> 
	{
		public:
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::reference         reference;
			typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::pointer           pointer;
		
		private:
			pointer _ptr;
			
		public:
		//Is default-constructible, copy-constructible, copy-assignable and destructible
		random_access_iterator() : _ptr(NULL) {}
		random_access_iterator(pointer _ptr) : _ptr(_ptr) {}
		random_access_iterator(const random_access_iterator<T> &ref) : _ptr(ref.base()) {}
		virtual ~random_access_iterator() {}
		random_access_iterator& operator=(const random_access_iterator<T> &ref)
		{
			if (this != &ref)
				this->_ptr = ref._ptr;
			return (*this);
		}
		
		pointer const &base() const
		{
			return (this->_ptr);
		}
		
		//Can be dereferenced as an rvalue (if in a dereferenceable state).	
		//*a
		//a->m
		reference operator*() const
		{
			return (*this->_ptr);
		}
		pointer operator->() const
		{
			return  (this->_ptr);
		}
		//For mutable iterators (non-constant iterators):
		// Can be dereferenced as an lvalue (if in a dereferenceable state).
		//????
		
		//Can be incremented (if in a dereferenceable state).
		// The result is either also dereferenceable or a past-the-end iterator.
		// Two iterators that compare equal, keep comparing equal after being both increased.
		random_access_iterator &operator++()
		{
			++this->_ptr;
			return (*this);
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			++this->_ptr;
			return (tmp);
		}

		// //Can be decremented (if a dereferenceable iterator value precedes it).
		random_access_iterator &operator--()
		{
			--this->_ptr;
			return (*this);
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			--this->_ptr;
			return (tmp);
		}
		
		//Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
		random_access_iterator operator+(difference_type n) const
		{
			return (random_access_iterator(this->_ptr + n));
		}

		random_access_iterator operator-(difference_type n) const
		{
			return (random_access_iterator(this->_ptr - n));
		}
		
		random_access_iterator &operator+=(difference_type n)
		{
			this->_ptr += n;
			return (*this);
		}
		
		//Supports compound assignment operations += and -=	
		random_access_iterator &operator-=(difference_type n)
		{
			this->_ptr -= n;
			return (*this);
		}
		
		reference operator[](difference_type n) const
		{
			return (*(this->_ptr + n));
		}
		
	};
		//Can be compared for equivalence using the equality/inequality operators
		// (meaningful when both iterator values iterate over the same underlying sequence).
		template<typename _IteratorL, typename _IteratorR>
		inline bool operator==(const random_access_iterator<_IteratorL>& __lhs, const random_access_iterator<_IteratorR>& __rhs)
		{
			std::cout <<"1"<<std::endl;
			return __lhs.base() == __rhs.base();
		}

		template<typename _Iterator>
		inline bool operator==(const random_access_iterator<_Iterator>& __lhs, const random_access_iterator<_Iterator>& __rhs)
		{
			std::cout <<"2"<<std::endl;
			return __lhs.base() == __rhs.base();
		}

		template <class Iter1, class Iter2>
		bool operator!=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
		{
			return ( lhs.base() != rhs.base() );
		}
		
		template <class Iter>
		bool operator!=(const random_access_iterator<Iter>& lhs, const random_access_iterator<Iter>& rhs)
		{
			return ( lhs.base() != rhs.base() );
		}
		
		//Can be compared with inequality relational operators (<, >, <= and >=).	
	template <class Iter1, class Iter2>
	bool operator<(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}


	template <class Iter1, class Iter2>
	bool operator<=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}
	
	template <class Iter>
	bool operator<(const random_access_iterator<Iter>& lhs, const random_access_iterator<Iter>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter>
	bool operator>(const random_access_iterator<Iter>& lhs, const random_access_iterator<Iter>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter>
	bool operator>=(const random_access_iterator<Iter>& lhs, const random_access_iterator<Iter>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iter>
	bool operator<=(const random_access_iterator<Iter>& lhs, const random_access_iterator<Iter>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}
	
	template <class Iterator>
	ft::random_access_iterator<Iterator> operator+(typename ft::random_access_iterator<Iterator>::difference_type n, ft::random_access_iterator<Iterator> &it)
	{
		return (it + n);
	}

	template <class Iterator>
	typename ft::random_access_iterator<Iterator>::difference_type operator-(const ft::random_access_iterator<Iterator> &lhs, const ft::random_access_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
	
	template <class Iterator, class Iterator_c>
	typename ft::random_access_iterator<Iterator>::difference_type operator+(const ft::random_access_iterator<Iterator> &lhs, const ft::random_access_iterator<Iterator_c> &rhs)
	{
		return (lhs.base() + rhs.base());
	}
	
	template <class Iterator, class Iterator_c>
	typename ft::random_access_iterator<Iterator>::difference_type operator-(const ft::random_access_iterator<Iterator> &lhs, const ft::random_access_iterator<Iterator_c> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
	
};

#endif
