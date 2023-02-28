#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include "../utils/iterator_traits.hpp"
# include "const_vector_iterator.hpp"

namespace   ft
{

template <typename T>
class vector_iterator
{


    public:
	typedef std::ptrdiff_t					difference_type;
	typedef std::size_t						size_type;
    typedef std::random_access_iterator_tag	iterator_category;
	typedef	T								value_type;
	typedef	T*								pointer;
	typedef	T&								reference;
    
    private:
	pointer	ptr;

    public:

    explicit vector_iterator(pointer newPtr): ptr(newPtr)
	{

    }

	vector_iterator() : ptr(NULL)
    {

    }

	bool operator!=(const vector_iterator& itr) 
	{
		if (this->ptr == itr.base())
			return (false);
		return (true);
	}

	bool operator!=(const vector_iterator& itr) const
	{
		if (this->ptr == itr.base())
			return (false);
		return (true);
	}

	bool operator!=(const ft::const_vector_iterator<vector_iterator>& itr) 
	{
		if (this->ptr == itr.base())
			return (false);
		return (true);
	}

	bool operator!=(const ft::const_vector_iterator<vector_iterator>& itr) const
	{
		if (this->ptr == itr.base())
			return (false);
		return (true);
	}

	friend bool operator==(const vector_iterator& x, const vector_iterator& y)
   	{
		return x.base() == y.base();
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

	vector_iterator operator=(vector_iterator rhs)
	{
		if (this != &rhs)
			this->ptr = rhs.base();
		return (*this);
	}

	vector_iterator operator++(int)
	{
		vector_iterator tmp = *this;

		++(*this);
	    return tmp;
	}

	vector_iterator &operator++()
	{
		this->ptr++;
		return (*this);
	}

	vector_iterator operator--(int)
	{
		vector_iterator tmp = *this;

		--(*this);
		return tmp;
	}

	vector_iterator &operator--()
	{
				this->ptr--;
				return (*this);
	}

	vector_iterator& operator-=(difference_type n)
	{ 
	   ptr -= n;
	   return *this;
	}

	friend bool operator< (const vector_iterator& x, const vector_iterator& y)
	{
		return x.base() < y.base();
	}

	friend bool operator<=(const vector_iterator& x, const vector_iterator& y)
	{
		return x.base() <= y.base();
	}

	friend bool operator> (const vector_iterator& x, const vector_iterator& y)
	{
		return x.base() > y.base();
	}

	friend bool operator>=(const vector_iterator& x, const vector_iterator& y)
	{
		return x.base() >= y.base();
	}

	vector_iterator operator+(difference_type n) const
	{
		return (vector_iterator<value_type>(ptr + n));
	}

	friend vector_iterator operator+(difference_type n, const vector_iterator& x)
	{
		return (vector_iterator<value_type>(x.base() + n));
	}

	vector_iterator operator-(int i) const
	{
		vector_iterator it(ptr - i);
		return (it);
	}

	vector_iterator operator-(int i)
	{
		vector_iterator it(ptr - i);
		return (it);
	}

	vector_iterator operator-(difference_type i) const
	{
		return (this->ptr - i);
	}

	friend difference_type operator-(const vector_iterator& x, const vector_iterator& y)
	{
		return x.base() - y.base();
	}

	vector_iterator &operator+=(difference_type __n)
	{
		ptr += __n;
		return *this;
    }

	pointer 		operator->()
	{
		return &(operator*());
	}

	const pointer 		operator->() const
	{
		return &(operator*());
	}

	};// class vector_iterator
}// namespace ft

#endif
