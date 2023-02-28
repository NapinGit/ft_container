#ifndef CONST_VECTOR_ITERATOR_HPP
# define CONST_VECTOR_ITERATOR_HPP
#include "../utils/iterator_traits.hpp"

namespace ft
{

	//
	//const_vector_iterator class
	//
	template <class It>
	struct const_vector_iterator
	{
		private:
			typename ft::iterator_traits<It>::pointer 						ptr;
		public:
			typedef typename ft::iterator_traits<It>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<It>::difference_type	 	difference_type;
			typedef const typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::pointer		 		pointer;
			typedef value_type			 									&reference;
			
			explicit const_vector_iterator(pointer newPtr): ptr(newPtr)
			{}

			const_vector_iterator(): ptr(NULL)
			{}

			const_vector_iterator(const It &cpy): ptr(cpy.base())
			{}

			bool operator!=(const const_vector_iterator& itr) 
			{
				if (this->ptr == itr.ptr)
					return (false);
				return (true);
			}

			bool operator!=(const const_vector_iterator& itr) const
			{
				if (this->ptr == itr.base())
					return (false);
				return (true);
			}

			pointer 	base() const
			{
				return ptr;
			}

			reference operator*() const
			{
				return *this->ptr;
			}

			reference operator[](int n) const
			{
				return (this->ptr[n]);
			}

			const_vector_iterator operator=(const const_vector_iterator &rhs)
			{
				if (this != &rhs)
					this->ptr = rhs.ptr;
				return (*this);
			}

			const_vector_iterator operator=(const const_vector_iterator &rhs) const
			{
				if (this != &rhs)
					this->ptr = rhs.ptr;
				return (*this);
			}

			const_vector_iterator operator++(int)
			{
				const_vector_iterator tmp = *this;

				++(*this);
				return tmp;
			}

			const_vector_iterator &operator++()
			{
				this->ptr++;
				return (*this);
			}

			const_vector_iterator operator--(int)
			{
				const_vector_iterator tmp = *this;

				--(*this);
				return tmp;
			}

			const_vector_iterator &operator--()
			{
				this->ptr--;
				return (*this);
			}

			const_vector_iterator &operator+=(difference_type __n)
	    	{
				ptr += __n;
				return *this;
    		}

		   	const_vector_iterator& operator-=(difference_type n)
		   	{ 
			   ptr -= n;
			   return *this;
			}

			const_vector_iterator operator+(difference_type n) const
			{
				return (const_vector_iterator<It>(ptr + n));
			}

			const_vector_iterator operator+(difference_type n)
			{
				return (const_vector_iterator<It>(ptr + n));
			}

			const_vector_iterator operator-(difference_type i)
			{
				const_vector_iterator it(ptr - i);
				return (it);
			}

			const_vector_iterator operator-(difference_type i) const
			{
				return (this->ptr - i);
			}

		   	const value_type *operator->()  const 
			{
				return &(operator*());
			}

			friend bool operator==(const const_vector_iterator& x, const const_vector_iterator& y)
   			{
				return x.base() == y.base();
			}

			friend difference_type operator-(const const_vector_iterator& x, const const_vector_iterator& y)
			{
				return x.base() - y.base();
			}

			friend const_vector_iterator operator+(difference_type n, const const_vector_iterator& x)
			{
				return (const_vector_iterator<It>(x.base() + n));
			}

			friend bool operator<(const const_vector_iterator& x, const const_vector_iterator& y)
			{
				return x.base() < y.base();
			}

			friend bool operator<=(const const_vector_iterator& x, const const_vector_iterator& y)
			{
				return x.base() <= y.base();
			}

			friend bool operator> (const const_vector_iterator& x, const const_vector_iterator& y)
			{
				return x.base() > y.base();
			}

			friend bool operator>=(const const_vector_iterator& x, const const_vector_iterator& y)
			{
				return x.base() >= y.base();
			}
	};// class const iterator
}// namespace ft

#endif