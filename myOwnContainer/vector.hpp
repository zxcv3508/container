/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyopark <hyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 20:23:11 by hyopark           #+#    #+#             */
/*   Updated: 2022/09/15 17:47:28 by hyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "random_access_iterator.hpp"
#include "utill.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

	template <typename T, typename _Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T												value_type;
			typedef _Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::random_access_iterator<T>			iterator;
			typedef typename ft::random_access_iterator<const T>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::size_type				size_type;
			
		private:
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_end_of_capacity;
			
		public:
			explicit vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
			{
			}
			
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
			{
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				while (n--)
				{
					this->_alloc.construct(this->_end++, val);
				}
			}
			
			// 호출 시점에서 무었을 호출할지 명확하지않음 -> is intagral, enable_if
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type* = NULL)
			: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
			{
				difference_type n = ft::distance(first, last);
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				while (n--)
					this->_alloc.construct(this->_end++, *first++);
			}
			
			vector (const vector& x)
			: _alloc(x._alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
			{
				difference_type n = x._end - x._start;
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				pointer tmp = x._start;
				while (n--)
					_alloc.construct(_end++, *tmp++);
				this->_end_of_capacity = this->_end;
			}
			
			// ~vector()
			// {
				
			// }
			
			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					this->clear();
					this->assign(x.begin(), x.end());
				}
				return (*this);
			}
			
			iterator begin()
			{
				return (iterator(this->_start));
			}
			
			const_iterator begin() const
			{
				return (const_iterator(this->_start));
			}
			
			iterator end()
			{
				return (iterator(this->_end));
			}
			
			const_iterator end() const
			{
				return (const_iterator(this->_end));
			}
			
			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->_end));
			}
			
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_end));
			}
			
			reverse_iterator rend()
			{
				return (reverse_iterator(this->_start));
			}
			
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_end));
			}
			
			const_iterator cbegin() const
			{
				return ( const_iterator(this->_start));
			}
			
			const_reverse_iterator crend() const
			{
				return (const_reverse_iterator(this->_end));
			}


			size_type size() const
			{
				return (this->_end - this->_start);
			}
			
			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}
			
			void resize (size_type n, value_type val = value_type())
			{
				if (n < size())
					erase(this->_start + n, this->_end);
				else if (n > size())
					insert(this->_end, n - size(), val);
			}
			
			size_type capacity() const
			{
				return (this->_end_of_capacity - this->_start);
			}
			
			bool empty() const
			{
				return (this->size() == 0);
			}
			
			void reserve (size_type n)
			{
				pointer prev_start;
				pointer prev_end;
				pointer prev_end_of_capacity;
				
				if (n > this->_alloc.max_size())
					throw (std::length_error("over the alloc max size"));
				if (this->capacity() < n)
				{
					prev_start = this->_start;
					prev_end = this->_end;
					prev_end_of_capacity = this->_end_of_capacity;
					
					this->_start = this-> _alloc.allocate(n);
					this->_end = this->_start;
					this->_end_of_capacity = this->_start + n;
					
					pointer tmp_start = prev_start;
					while (tmp_start != prev_end)
					{
						this->_alloc.construct(this->_end, *tmp_start);
						this->_alloc.destroy(tmp_start);
						++_end;
						++tmp_start;
					}
				this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
				}
			}
			
			void shrink_to_fit();

			reference operator[] (size_type n)
			{
				return (*(this->_start + n));
			}
			
			const_reference operator[] (size_type n) const
			{
				return (*(this->_start + n));
			}
			
			reference at (size_type n)
			{
				if (n >= this->size())
					throw (std::out_of_range("Out_of_range Error: ft::vector::at "));
				return ((*this)[n]);
			}
			
			const_reference at (size_type n) const
			{
				if (n >= this->size())
					throw (std::out_of_range("Out_of_range Error: ft::vector::at "));
				return ((*this)[n]);
			}
			
			reference front()
			{
				return (*(this->_start));
			}
			
			const_reference front() const
			{
				return (*(this->_start));
			}
			
			reference back()
			{
				return (*(this->_end - 1));
			}
			
			const_reference back() const
			{
				return (*(this->_end - 1));
			}
			
			value_type* data();
			const value_type* data() const;

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type * = NULL)
			{
				size_type n;
				
				n = ft::distance(first, last);
				this->clear();
				if (n <= this->capacity())
				{
					while (n--)
					{
						this->_alloc.construct(this->_end++, *first++);
					}
				}
				else
				{
					pointer prev_start = this->_start;
					pointer prev_end_of_capacity = this->_end_of_capacity;

					this->_start = this->_alloc.allocate(n);
					this->_end = this->_start;
					this->_end_of_capacity = this->_start + n;
					const_pointer tmp = &(*first);
					while(tmp != &(*last))
						this->_alloc.construct(this->_end++, *tmp++);
					this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
				}
			}
			
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				if (n <= this->capacity())
				{
					while (n--)
						this->_alloc.construct(this->_end++, val);
				}
				else
				{
					pointer prev_start = this->_start;
					pointer prev_end_of_capacity = this->_end_of_capacity;

					this->_start = this->_alloc.allocate(n);
					this->_end = this->_start;
					this->_end_of_capacity = this->_start + n;
					while (n--)
						this->_alloc.construct(this->_end++, val);
					this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
				}
			}
			
			void push_back (const value_type& val)
			{
				if (this->_end == this->_end_of_capacity)
				{
					if (this->size() == 0)
						this->reserve(1);
					else
						this->reserve(this->capacity() * 2);
				}
				this->_alloc.construct(this->_end++, val);
			}
			
			void pop_back()
			{
				this->_alloc.destroy(--(this->_end));
			}
			
			size_type ft_new_size(size_type n)
			{	
				size_type curr_size = this->capacity();
				
				// n = n+this->size();
				// if (curr_size < 0)
				// 	return -1;
				// if (curr_size < 1)
				// 	curr_size = 1;
				// while (curr_size < n)
				// {
				// 	curr_size *= 2;
				// }
				
			}
			
			iterator insert (iterator position, const value_type& val)
			{
				size_type	n = &*position - _start;
				size_type	r_n = _end - &*position;
				
				if (this->size() == 0)
					this->reserve(1);
				else if (this->_end == this->_end_of_capacity)
					this->reserve(2 * this->capacity());
				
				for (size_type i = 0 ; i < r_n; i++)
				{
					this->_alloc.construct(this->_end - i, *(_end - i - 1));
					this->_alloc.destroy(this->_end - i - 1);
				}
				this->_alloc.construct(_start + n, val);
				this->_end++;
				return (iterator(this->_start + n));
			}
			
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (position > this->end() || position < this->begin())
					return;
				size_type tmp_start;
				size_type tmp_end;
				size_type space;
				
				tmp_start = &*position - _start;
				tmp_end = _end - &*position;
				space = this->_end_of_capacity - this->_end;
				if (this->max_size() < this->size() + n)
					throw std::length_error("ft::vector::insert: max_size() < this->size() + n");
				if (this->capacity() >= this->size() + n)
					this->reserve((this->size() + n) * 2);
				else
					this->reserve((this->size() + n) * 1);
					
				for (int i = 0 ; i < tmp_end; i++)
				{
					this->_alloc.construct(this->_end - i + n - 1,  *(_end - i - 1));
					this->_alloc.destroy(this->_end - i - 1);
				}
				for (int i = 0 ; i < n ; i++)
				{
					this->_alloc.construct(_start + tmp_start + i , val);
				}
				this->_end += n;
			}
			
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral< InputIterator >::value >::type*  = NULL)
			{
				if (position > this->end() || position < this->begin())
					return;
				size_type tmp_start;
				size_type tmp_end;
				size_type n;
				
				tmp_start = &*position - _start;
				tmp_end = _end - &*position;
				n = ft::distance(first,last);
				if (this->max_size() < this->size() + n)
					throw std::length_error("ft::vector::insert: max_size() < this->size() + n");
				if (this->capacity() >= this->size() + n)
					this->reserve((this->size() + n) * 2);
				else
					this->reserve((this->size() + n) * 1);
					
				for (int i = 0 ; i < tmp_end; i++)
				{
					this->_alloc.construct(this->_end - i + n - 1,  *(_end - i - 1));
					this->_alloc.destroy(this->_end - i - 1);
				}
				for (int i = 0 ; i < n ; i++)
				{
					this->_alloc.construct(this->_start + tmp_start + i , *first++);
				}
				this->_end += n;
			}
			
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (vector& x);
			void clear()
			{
				while (this->_start != this->_end)
					this->_alloc.destroy(--this->_end);
			}

			allocator_type get_allocator() const;
			};
			
			template <class T, class Alloc>
			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
			template <class T, class Alloc>
			void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}
#endif