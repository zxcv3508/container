#ifndef NULLPTR_HPP
#define NULLPTR_HPP

#include <memory>
#include <iostream>
namespace ft
{
	static class nullptr_t {
		
		public:
			template <class T>
			operator T*() const {
			std::cout <<"123"<<std::endl;
				return 0;
			}

			template <class C, class T>
			operator T C::*() const {
			std::cout <<"1234"<<std::endl;
				return 0;
			}

		private:
			void operator&() const;

	} ft_nullptr = {};
}
#endif