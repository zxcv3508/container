#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include <iostream>

namespace ft
{
	template<typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference         reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer           pointer;
		private:
			pointer _ptr;
		public:
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

			///////////////////////////////////
			
			
			pointer const &base() const
			{
				return (this->_ptr);
			}
			
			reference operator*()
			{
				return (*this->_ptr);
			}
			pointer operator->() const
			{
				return  (this->_ptr);
			}
			const reference operator*() const
			{
				return (*this->_ptr);
			}
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
	
	
}

#endif