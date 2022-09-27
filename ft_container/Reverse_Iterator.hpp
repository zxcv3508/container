#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <memory>
#include "Iterator.hpp"
namespace ft
{
template <class Iterator>
	class reverse_iterator
	{
	//  struct iterator_traits {
  //     typedef typename _Iterator::iterator_category iterator_category;
  //     typedef typename _Iterator::value_type        value_type;
  //     typedef typename _Iterator::difference_type   difference_type;
  //     typedef typename _Iterator::pointer           pointer;
  //     typedef typename _Iterator::reference         reference;
  //   };
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
		protected:
			Iterator current;


		public:
			/**
			 * @brief Construct a new reverse iterator object
			 * default constructor
			 * initialization constructor
			 * copy constructor
			 */
			reverse_iterator() : current() {} //default constructor
			explicit reverse_iterator (iterator_type it) : current(it) {} //initialization constructor
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {} //copy

			/**
			 * @brief operator
			 */
			//assigns another iterator adaptor
			template <typename Iter>
			reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it) //assignment
			{
				this->current = rev_it.current;
				return (*this);
			}

			//accesses the underlying adaptor
			iterator_type base() const //return base iterator
			{
				return (this->current);
			}

			//accesses the pointed-to-element
			reference operator*() const //dereference iterator
			{
				iterator_type tmp = this->current;
				--tmp;
				return (*tmp);
			}

			pointer operator->() const //dereference iterator
			{
				return ( &(operator*()) );
			}

			//advances or decrements the iterator
			reverse_iterator& operator++() //decrements the base iterator kept by the object (as if applying operator-- to it).
			{
				--this->current;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator--() //increments the base iterator kept by the object (as if applying operator++ to it).
			{
				++this->current;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			//현재 위치에서 n만큼 차이나는 위치의 iterator 반환
			//해당 기능들을 사용하기 위해서는 base iterator가 random_access_iterator여야한다. -> 해당 기능을 vector에서 사용하므로 vector_iterator를 random_access_iterator를 사용한다.
			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator& operator+=(difference_type n)
			{
				this->current -= n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator& operator-=(difference_type n)
			{
				this->current += n;
				return (*this);
			}

			//accesses an element by index
			//If such an element does not exist, it causes undefined behavior.
			//Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
			//iterator가 현재 가리키는 요소에서 n개 위치에 있는 요소에 엑세스한다.
			reference operator[](difference_type n) const
			{
				return (this->current[-n - 1]);
			}
	};

	/**
	 * @brief non-member function overloads
	 *
	 * reverse_iterator 개체 lhs와 rhs 간에 적절한 비교 작업을 수행합니다.
	 * operator on reverse iterators vs equivalent used on base iterators
	 */
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return ( it.base() + n );
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( rhs.base() - lhs.base() );
	}

	//non-member non-const function overload
	template <class Iter>
	bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter>
	bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter>
	bool operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter>
	bool operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter>
	bool operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template <class Iter>
	bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iterator, class Iterator_c>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator_c> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif