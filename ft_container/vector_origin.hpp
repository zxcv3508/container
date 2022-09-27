#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "Reverse_Iterator.hpp"
#include "type_traits.hpp"
#include "utill.hpp"
#include "Iterator.hpp"
#include "Random_access_iterator.hpp"

namespace ft
{
  template<typename T, typename _Alloc = std::allocator<T> >
class vector
{
	public:
		typedef T                                             value_type;
		typedef _Alloc                                        allocator_type;
		typedef typename allocator_type::reference            reference;
		typedef typename allocator_type::const_reference      const_reference;
		typedef typename allocator_type::pointer              pointer;
		typedef typename allocator_type::const_pointer        const_pointer;
		typedef ft::random_access_iterator<T>                 iterator;
		typedef ft::random_access_iterator<const T>           const_iterator;
		typedef ft::reverse_iterator<iterator>                reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>          const_reverse_iterator;
		typedef typename allocator_type::size_type            size_type;
		typedef typename allocator_type::difference_type      difference_type;
		
	private:
		allocator_type	_alloc;
		pointer			_start;
		pointer			_end;
		pointer			_end_of_capacity;
		
	public:
		// (1) empty container constructor (default constructor)
		// Constructs an empty container, with no elements.
		explicit vector(const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL){}
		
		// (2) fill constructor
		// Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
		{
			this->_start = _alloc.allocate(n);
			this->_end = _start;
			this->_end_of_capacity = this->_start + n;
			while (n--)
			{
				// std::cout << "hi : "<<val <<std::endl;
				this->_alloc.construct(this->_end++, val);
			}
		}
		
		// (3) range constructor
		// Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type(),
				typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator >::type* = NULL)
		: _alloc(alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
		{
			difference_type n = last - first;
			this->_start = _alloc.allocate(n);//distence???????
			this->_end = this->_start;
			this->_end_of_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++, *first++);
		}
		// (4) copy constructor
		// Constructs a container with a copy of each of the elements in x, in the same order.
		vector(const vector &ref)
		: _alloc(ref._alloc), _start(NULL), _end(NULL), _end_of_capacity(NULL)
		{
			difference_type n = ref._end - ref._start;
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			pointer tmp = ref._start;
			while (n--)
				_alloc.construct(_end++, *tmp++);
			this->_end_of_capacity = this->_end;
		}
		// The container keeps an internal copy of alloc, which is used to allocate storage throughout its lifetime.
		// The copy constructor (4) creates a container that keeps and uses a copy of x's allocator.
		// The storage for the elements is allocated using this internal allocator.
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_start, this->_end_of_capacity - this->_start);
		}
		
		//Assign content
		
		template< class InputIt >
		void assign( InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::type * = NULL)
		{
			this->clear();
			size_type n = ft::distance(first, last);
			if (n <= this->capacity())
			{
				while (n--)
					this->_alloc.construct(this->_end++, *first++);
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
		
		void assign( size_type count, const value_type& value )
		{
			this->clear();
			if (count <= this->capacity())
			{
				while (count--)
					this->_alloc.construct(this->_end++, value);
			}
			else
			{
				pointer prev_start = this->_start;
				pointer prev_end_of_capacity = this->_end_of_capacity;

				this->_start = this->_alloc.allocate(count);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + count;
				while (count--)
					this->_alloc.construct(this->_end++, value);
				this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
			}
		}
		
		
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				this->clear();
				this->assign(x.begin(), x.end());
			}
			return (*this);
		}
		
		allocator_type get_allocator() const
		{
			return (this->_Alloc);
		}
		
		//Iterators
		// begin		Return iterator to beginning (public member function)
		iterator begin()
		{
			return (iterator(this->_start));
		}
		
		const_iterator begin() const
		{
			return (const_iterator(this->_start));
		}
		
		// end	Return iterator to end (public member function)
		iterator end()
		{
			return (iterator(this->_end));
		}
		
		const_iterator end() const
		{
			return (const_iterator(this->_end));
		}
	
		// rbegin	Return reverse iterator to reverse beginning (public member function)
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->_end));
		}
		
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->_end));
		}
		
		// rend	Return reverse iterator to reverse end (public member function)
		reverse_iterator rend()
		{
			return (reverse_iterator(this->_start));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->_start));
		}
		
		// (C++11)
		// // cbegin	Return const_iterator to beginning (public member function)
		// iterator cbegin() const
		// {
		// 	return (const_iterator(_start));
		// }
		
		// // cend	Return const_iterator to end (public member function)
		// iterator cend() const
		// {
		// 	return (const_iterator(_end));
		// }
		
		// // crbegin	Return const_reverse_iterator to reverse beginning (public member function)
		// iterator crbegin() const
		// {
		// 	return (const_reverse_iterator(_start));
		// }
		
		// // crend	Return const_reverse_iterator to reverse end (publ
		// iterator crend() const
		// {
		// 	return (const_reverse_iterator(_end));
		// }
		
		//Capacity
		// size	Return size (public member function)
		size_type size() const
		{
			return (_end - _start);
		}
		// max_size	Return maximum size (public member function)
		//최대 요소 수
		size_type max_size() const
		{
			return (this->_alloc.max_size());
		}
		
		// capacity	Return size of allocated storage capacity (public member function)
		size_type capacity() const
		{
			return (this->_end_of_capacity - this->_start);
		}
		// empty	Test whether vector is empty (public member function)
		bool empty() const
		{
			return (this->_start == this->_end);
		}
		
		// reserve	Request a change in capacity (public member function)
		// 인자값으로 새로이 할당 // 크면 하고 작으면 아무것도안함
		void reserve(size_type n)
		{
			if (n > max_size() )
				throw(std::length_error("Error: ft::vector::reserve"));
			else if (n > this->capacity())
			{
				pointer prev_start = this->_start;
				pointer prev_end = this->_end;
				pointer prev_end_of_capacity = this->_end_of_capacity;
				
				this->_start = this->_alloc.allocate(n);
				this->_end = this->_start;
				this->_end_of_capacity = this->_start + n;
				pointer tmp = prev_start;
				while (tmp != prev_end)
				{
					this->_alloc.construct(this->_end++, *tmp);
					this->_alloc.destroy(tmp++);
				}
				this->_alloc.deallocate(prev_start, prev_end_of_capacity - prev_start);
			}
		}
		
		// 		Modifiers
		// clear
		
		// clears the contents
		void clear()
		{
			while (this->_start != this->_end)
				this->_alloc.destroy(--this->_end);
		}
		// insert
		
		// inserts elements
		iterator insert( iterator pos, const T& value )
		{
			size_type	n = &*pos - _start;
			size_type	r_n = _end - &*pos;

			if (this->size() == 0)
				this->reserve(1);
			else if (_end == this->_end_of_capacity)
				this->reserve(2 * this->size());
			for (size_type i = 0; i < r_n; i++) {
				_alloc.construct(_end - i, *(_end - i - 1));
				_alloc.destroy(_end - i - 1);
			}
			_alloc.construct(_start + n, value);
			_end++;
			return (iterator(_start + n));
		}
		
		void insert( iterator pos, size_type count, const T& value )
		{
			if (pos > this->end() || pos < this->begin())
					return;
				
				size_type	next_size = this->size() + count;
				size_type	_pos = &*pos - _start;
				size_type	prev_capa = this->capacity();
				size_type	alloced_size = 0;
				pointer		new_start = NULL;
				pointer		prev_capa_end = this->_end_of_capacity;

				if (this->max_size() < next_size)
					throw std::length_error("ft::vector::insert: max_size() < this->size() + n");
				if (this->capacity() < next_size) {
					new_start = _alloc.allocate(next_size);
					this->_end_of_capacity = new_start + next_size;
					alloced_size = next_size;
				} else {
					new_start = _alloc.allocate(this->capacity() * 2);
					this->_end_of_capacity = new_start + this->capacity() * 2;
					alloced_size = this->capacity() * 2;
				}
				try {
					for (size_type i = 0; i < _pos; ++i)
						_alloc.construct(new_start + i, *(_start + i));
					for (size_type i = 0; i < count; ++i)
						_alloc.construct(new_start + _pos + i, value);
					for (size_type i = 0; i < this->size() - _pos; ++i)
						_alloc.construct(new_start + _pos + count + i, *(_start + _pos + i));
				} catch(...) {
					for (size_type i = 0; i < _pos; ++i)
						_alloc.destroy(new_start + i);
					for (size_type i = 0; i < count; ++i)
						_alloc.destroy(new_start + _pos + i);
					for (size_type i = 0; i < this->size() - _pos; ++i)
						_alloc.destroy(new_start + _pos + count + i);
					_alloc.deallocate(new_start, alloced_size);
					this->_end_of_capacity = prev_capa_end;
					throw;
				}

				for (size_type i = 0; i < this->size(); ++i)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, prev_capa);
				_end = new_start + count + this->size();
				_start = new_start;
		}
		
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value >::type* = NULL)
		{
			if (pos > this->end() || pos < this->begin())
					return;
				
				size_type	num = ft::distance(first, last);
				size_type	next_size = this->size() + num;
				size_type	prev_capa = this->capacity();
				size_type	_pos = &*pos - _start;
				size_type	alloced_size = 0;
				pointer		new_start = NULL;
				pointer		prev_capa_ptr = this->_end_of_capacity;

				if (this->max_size() < next_size)
					throw std::length_error("ft::vector::insert: max_size() < this->size() + n");
				if (this->capacity() * 2 < next_size) {
					new_start = _alloc.allocate(next_size);
					this->_end_of_capacity = new_start + next_size;
					alloced_size = next_size;
				} else {
					new_start = _alloc.allocate(this->capacity() * 2);
					this->_end_of_capacity = new_start + this->capacity() * 2;
					alloced_size = this->capacity() * 2;
				}
				try {
					for (size_type i = 0; i < _pos; ++i)
						_alloc.construct(new_start + i, *(_start + i));
					for (size_type i = 0; i < num; ++i)
						_alloc.construct(new_start + _pos + i, *(&*first++));
					for (size_type i = 0; i < this->size() - _pos; ++i)
						_alloc.construct(new_start + _pos + num + i, *(_start + _pos + i));
				} catch(...) {
					for (size_type i = 0; i < _pos; ++i)
						_alloc.destroy(new_start + i);
					for (size_type i = 0; i < num; ++i)
						_alloc.destroy(new_start + _pos + i);
					for (size_type i = 0; i < this->size() - _pos; ++i)
						_alloc.destroy(new_start + _pos + num + i);
					_alloc.deallocate(new_start, alloced_size);
					this->_end_of_capacity = prev_capa_ptr;
					throw;
				}
				for (size_type i = 0; i < this->size(); ++i)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, prev_capa);
				_end = new_start + num + this->size();
				_start = new_start;
		}
		
		// emplace
		
		// (C++11)
		
		// constructs element in-place
		
		// erase
		
		// erases elements
		
		iterator erase(iterator pos)
		{
			this->_alloc.destroy(&(*pos));
			size_type n = this->_end - &(*pos) - 1;
			pointer tmp = &(*pos);

			while (n--)
			{
				this->_alloc.construct(tmp, *(tmp + 1));
				this->_alloc.destroy(tmp++);
			}
			--this->_end;
			return (pos);
		}

		//범위[first, last) 제거
		iterator erase(iterator first, iterator last)
		{
			pointer tmp = &(*first);
			while (tmp != &(*last))
				_alloc.destroy(tmp++);
			size_type n = this->_end - &(*last);
			size_type range = ft::distance(first, last);
			tmp = &(*first);
			while (n--)
			{
				_alloc.construct(tmp, *last++);
				_alloc.destroy(tmp++);
			}
			this->_end -= range;
			return (first);
		}
		// push_back
		
		
		// adds an element to the end
		void push_back( const T& value )
		{
			if (this->_end == this->_end_of_capacity)
			{
				if (this->size() == 0)
					this->reserve(1);
				else
					this->reserve(this->capacity() * 2);
			}
			this->_alloc.construct(this->_end++, value);
		}

		// emplace_back
		
		// (C++11)
		
		// constructs an element in-place at the end
		// pop_back
		
		// removes the last element
		void pop_back()
		{
			this->_alloc.destroy(--this->_end);
		}
		// resize
		
		// changes the number of elements stored
		// n 만큼 저장할수 있게 컨테이너 사이즈 변경()) // 작으면 작은데로 바꿈(초과 값은 삭제) // 예외발생시 아무효과없어야함
		void resize(size_type __new_size, value_type val = value_type())
		{
			if (__new_size > this->max_size())
				throw std::length_error("ft::vector::resize: n > max_size()");
			if (this->size() == __new_size)
				return;
			if (__new_size < this->size()) {
				while (this->size() != __new_size)
					pop_back();
			} else {
				if (this->capacity() * 2 < __new_size)
					reserve(__new_size);
				while (this->size() != __new_size)
					push_back(val);
			}
		}
		// swap
		
		// swaps the contents
		void swap( vector& other )
		{
			if (*this == other) 
				return ;

			allocator_type tmp_alloc = other._alloc;
			pointer tmp_start = other._start;
			pointer tmp_end = other._end;
			pointer tmp_end_of_capacity = other._end_of_capacity;

			other._alloc = this->_alloc;
			other._start = this->_start;
			other._end = this->_end;
			other._end_of_capacity = this->_end_of_capacity;

			this->_alloc = tmp_alloc;
			this->_start = tmp_start;
			this->_end = tmp_end;
			this->_end_of_capacity = tmp_end_of_capacity;
		}
		// (C++11)
		// // shrink_to_fit	Shrink to fit (public member function)
		// size_type shrink_to_fit()
		// {
			
		// }
		
	// Element access
	// at
	reference at(size_type pos)
	{
		// if (pos >= this->size())
		if (!(pos < size()))
			throw(std::out_of_range("Out_of_range Error: ft::vector::at"));
		return ((*this)[pos]);
	}

	//const access element
	const_reference at(size_type pos) const
	{
		// if (pos >= this->size())
		if (!(pos < size()))
			throw(std::out_of_range("Out_of_range Error: ft::vector::at"));
		return ((*this)[pos]);
	}
	
	// access specified element with bounds checking
	// operator[]
	// 익셉션 필요없음
	reference operator[](size_type n)
	{
		return (*(this->_start + n));
	}

	//const access element
	const_reference operator[](size_type n) const
	{
		return (*(this->_start + n));
	}
	// access specified element
	// front
	// 벡터의 첫번째 element를 리턴.
	reference front()
	{
		return (*(this->_start));
	}

	const_reference front() const
	{
		return (*(this->_start));
	}
	// access the first element
	// back
	reference back()
	{
		return (*(this->_end - 1));
	}

	const_reference back() const
	{
		return (*(this->_end - 1));
	}
	
	// access the last element
	// data

	// T* data()
	// const_reference data() const
	// {
	// 	return 
	// }
	
	// direct access to the underlying array
		
		
		
		
};
//  Non-member functions

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector< T, Alloc >::const_iterator it_lhs = lhs.begin();
		typename ft::vector< T, Alloc >::const_iterator it_rhs = rhs.begin();

		while (it_lhs != lhs.end())
		{
			if (it_rhs == rhs.end() || *it_lhs++ != *it_rhs++)
				return (false);
		}
		return (true);
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return (!(lhs == rhs));
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return (!(rhs < lhs));
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return (rhs < lhs);
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return (!(lhs < rhs));
}


template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
{
	lhs.swap(rhs);
}


}
#endif