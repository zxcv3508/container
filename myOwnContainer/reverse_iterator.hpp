#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		protected:
			Iterator current;
			
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			reverse_iterator() {}
			
			explicit reverse_iterator (iterator_type it) : current(it.base()) {}
			
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}
			
			iterator_type base() const
			{
				return (this->current);
			}
			
			reference operator*() const
			{
				iterator_type tmp = this->current;
				--tmp;
				return (*tmp);
			}
			
			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}
			
			reverse_iterator& operator++()
			{
				--this->current;
				return (*this);
			}
			
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
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
			
			reverse_iterator& operator--()
			{
				++this->current;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}
			
			reverse_iterator& operator-=(difference_type n)
			{
				this->current += n;
				return (*this);
			}
			
			pointer operator->() const //dereference iterator
			{
				return ( &(operator*()) );
			}
			
			reference operator[](difference_type n) const
			{
				return (this->current[-n - 1]);
			}
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return ( rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}
#endif