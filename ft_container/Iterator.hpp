#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
namespace ft
{
  struct input_iterator_tag {};
  ///  Marking output iterators.
  struct output_iterator_tag {};
  /// Forward iterators support a superset of input iterator operations.
  struct forward_iterator_tag : public input_iterator_tag {};
  /// Bidirectional iterators support a superset of forward iterator operations.
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  /// Random-access iterators support a superset of bidirectional iterator operations.
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};
  
	template<typename _Iterator>
    struct iterator_traits {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type        value_type;
      typedef typename _Iterator::difference_type   difference_type;
      typedef typename _Iterator::pointer           pointer;
      typedef typename _Iterator::reference         reference;
    };

  template<typename _Tp>
    struct iterator_traits<_Tp*> {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef _Tp*                        pointer;
      typedef _Tp&                        reference;
    };

  template<typename _Tp>
    struct iterator_traits<const _Tp*> {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };

  // template<typename _Iterator, typename _Container>
	template <class Category,              // iterator::iterator_category
          class T,                     // iterator::value_type
          class Distance = ptrdiff_t,  // iterator::difference_type
          class Pointer = T*,          // iterator::pointer
          class Reference = T&         // iterator::reference
          >
	class Iterator
	{
	  public:
		  typedef  Category  iterator_category;
      typedef  T         value_type;
      typedef  Distance  difference_type;
      typedef  Reference reference;
      typedef  Pointer   pointer;
    
		// typedef typename iterator_traits<_Iterator>::iterator_category  iterator_category;
    // typedef typename iterator_traits<_Iterator>::value_type         value_type;
    // typedef typename iterator_traits<_Iterator>::difference_type    difference_type;
    // typedef typename iterator_traits<_Iterator>::reference          reference;
    // typedef typename iterator_traits<_Iterator>::pointer            pointer;
	};
	
	
	
	
	
}


#endif