
#ifndef VECTOR_HPP
#define VECTOR_HPP
# include <cstring>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cstdio>


# include "ite/vector_iterator.hpp"
# include "ite/const_vector_iterator.hpp"
# include "ite/reverse_vector_iterator.hpp"
# include "ite/const_reverse_vector_iterator.hpp"

# include "utils/trait.hpp"
# include "utils/lexicograhical_compare_equal.hpp"
#include <algorithm>

namespace ft
{
template< typename T, typename Allocator = std::allocator<T> >
class vector
{
    public:
    	typedef T												value_type;
	    typedef Allocator										allocator_type;
	    typedef std::size_t										size_type;
	    typedef std::ptrdiff_t									difference_type;
	    typedef typename Allocator::reference					reference;
	    typedef typename Allocator::const_reference				const_reference;
	    typedef typename Allocator::pointer						pointer;
	    typedef typename Allocator::const_pointer				const_pointer;
	    typedef ft::vector_iterator<T>							iterator;
	    typedef ft::const_vector_iterator<iterator>			    const_iterator;
	    typedef ft::reverse_vector_iterator<iterator>           reverse_iterator;
	    typedef ft::const_reverse_vector_iterator<iterator>	    const_reverse_iterator;

    public:

        /*

                Constructor/Destructor/Operator:

        */


        explicit vector( const Allocator &alloc = Allocator() ):
		 _size(0), _capacity(0), data(NULL), allocator(alloc)
	    {
		    return;
	    }
	    
        explicit vector( size_type count, const /*value_type*/T& value = T(),
			const Allocator& alloc = Allocator() ):
		 _size(0), _capacity(0),data(NULL), allocator(alloc)
	    {
		    resize(count, value);
	    }


        template< typename InputIt >
	    vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ):
		 _size(0), _capacity(0), data(NULL), allocator(alloc)
	    {
		    assign(first, last);
	    }

	    vector( const vector& other ):
		 _size(0), _capacity(0), data(NULL), allocator(other.allocator)
	    {
		    *this = other;
	    }

        ~vector()
        {
           this->clear();
           if (this->data)
                allocator.deallocate(this->data, this->_capacity);
        }

        vector&		operator=( const vector& other )
	    {
		    this->allocator = other.allocator;
		    this->assign(other.begin(), other.end());
		    return *this;
        }

        /*

                Iterator:

        */

       	iterator		begin( void )
        { 
            return iterator(this->data); 
        }
	    const_iterator	begin( void ) const
	    {
		    return const_iterator(this->data);
	    }

        iterator		end( void )
        { 
            return iterator(&this->data[this->_size]); 
        }

	    const_iterator	end( void ) const
	    {
		    return const_iterator(&this->data[this->_size]);
	    }



        reverse_iterator		rbegin( void )
        { 
            return reverse_iterator(this->end());
        }

        const_reverse_iterator		rbegin( void ) const
        { 
            return const_reverse_iterator(this->end()); 
        }

        reverse_iterator rend( void )
        {
            return reverse_iterator(this->begin());
        }

        const_reverse_iterator		rend( void ) const
        { 
            return const_reverse_iterator(this->begin()); 
        }

        /*

                Capacity:

        */

        size_type    size()    const
        {
            return (this->_size);
        }

        size_type      max_size()  const
        {
            return  (allocator.max_size());
        }

        void    reserve(size_type  size)
        {
            if (size > allocator.max_size())
		    {
		        throw std::length_error("vector::reserve");
		    }
		    if (size > _capacity)
		    {
			    T *		new_data = allocator.allocate(size);

			    for (size_type i = 0 ; i < _size && i < size ; i++)
			    {
				    allocator.construct(new_data + i, data[i]);
				    allocator.destroy(data + i);
			    }
			    allocator.deallocate(data, _capacity);
    			_capacity = size;
	    		data = new_data;
		    }
        }

        

        void resize (size_type new_size, const value_type& val = value_type())
	    {
		    if (new_size > _size)
		    {
			    if (new_size > _capacity)
			    {
				    if (new_size > _size * 2)
					    this->reserve(new_size);
			    	else if (_size > 0)
				    	this->reserve(_size * 2);
				    else
					    this->reserve(1);
			    }

			    for (size_type i = _size ; i < new_size ; i++)
				allocator.construct(data + i, val);
	    	}
		    else
		    {
			    for (size_type i = new_size ; i < _size ; i++)
			    	allocator.destroy(data + i);
		    }

	    	_size = new_size;
	    }

        size_type    capacity()    const
        {
            return (this->_capacity);
        }

        bool empty() const
        {
            if (this->_size == 0)
                return true;
            else
                return false;
        }

        /*

            Element access:

        */

        T   &operator[](const int idx) const
        {
            return(this->data[idx]);
        }
        
        reference   at(const size_type index)
        {
            if (index >= this->_size)
                throw std::out_of_range("index given is out of range.");
            return this->data[index];
        }

        const reference   at(const size_type index) const
        {
            if (index >= this->_size)
                throw std::out_of_range("index given is out of range.");
            return this->data[index];
        }

        reference		front( void ) 
        { 
            return this->data[0]; 
        }

        const_reference	front( void ) const 
        { 
            return this->data[0]; 
        }

        reference		back( void ) 
        { 
            return this->data[this->_size - 1]; 
        }

        const_reference	back( void ) const 
        { 
            return this->data[this->_size - 1]; 
        }


        /*

                Modifiers:

        */

        
        template<class InIt>
        void assign(InIt first, InIt last,
                        typename ft::enable_if <!ft::is_integral<InIt>::value >::type* = 0)
        {
            this->clear();
            
            while (first != last)
            {
                this->push_back(*first);
                first++;
            }
        }

        void	assign( size_type new_size, const T& value )
        {
            this->clear();
            this->resize(new_size, value);
        }

        void	push_back( const T& value )
	    {
		   if (this->_size >= this->_capacity)
           {
               if (this->_capacity == 0)
                    this->reserve(1);
                else
                this->reserve(this->_capacity * 2);
           }
            allocator.construct(&this->data[this->_size], value);
            this->_size++;
	    }

        void pop_back()
        {
            allocator.destroy(&(this->data[this->_size - 1]));
            this->_size--;
        }

        iterator insert (iterator position, const T& val)
        {
            size_type index = position - this->begin();

            this->insert(position, 1, val);
            return(iterator(&this->data[index]));
        }

        void insert (iterator position, size_type n, const value_type & val)
	    {
		    size_type		off = position - this->begin();

	    	if (_size + n > _capacity)
	    	{
		    	if (_size + n > _size * 2)
			    	this->reserve(_size + n);
			    else if (_size > 0)
				    this->reserve(_size * 2);
			    else
				    this->reserve(1);
		    }
		    for (size_type i = 0 ; i < n ; i++)
			    allocator.construct(data + _size + i, val);
		    for (int i = _size - 1 ; i >= 0 && i >= (int)off ; i--)
			    data[i + n] = data[i];
		    for (size_type i = off ; i < off + n ; i++)
			    data[i] = val;
		    _size = _size + n;
	    }

        	template <class InputIterator>
	    void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
	    {
		    size_type		off = position - this->begin();
		    size_type		n = 0;

		    for (InputIterator cpy = first ; cpy != last && n <= this->max_size() ; cpy++)
			    n++;
		    if (_size + n > _capacity)
		    {
			    if (_size + n > _size * 2)
				    this->reserve(_size + n);
			    else if (_size > 0)
				    this->reserve(_size * 2);
			    else
				    this->reserve(1);
		    }
		    for (size_type i = 0 ; i < n ; i++)
			    allocator.construct(data + _size + i, *first);
		    for (int i = _size - 1 ; i >= 0 && i >= (int)off ; i--)
			    data[i + n] = data[i];
		    for (size_type i = off ; i < off + n ; i++)
			    data[i] = *first++;
		    _size = _size + n;
	    }

        iterator erase (iterator position)
	    {
	    	for (size_type i = position - this->begin() ; i < _size - 1 ; i++)
		    	data[i] = data[i + 1];

		    _size--;
	    	allocator.destroy(data + _size);

		    return (position);
	    }


	    iterator erase (iterator first, iterator last)
	    {
		    size_type		n = last - first;

		    while (n-- > 0)
			    this->erase(first);
		    return (first);
	    }
        
        void	swap( vector& other )
	    {
	    	value_type		*tmp_data = this->data;
		    size_type		tmp_size = this->_size;
		    size_type		tmp_capacity = this->_capacity;
		    allocator_type	tmp_allocator = this->allocator;

	    	this->data = other.data;
    		this->_size = other._size;
    		this->_capacity = other._capacity;
	    	this->allocator = other.allocator;
		    other.data			= tmp_data;
    		other._size			= tmp_size;
	    	other._capacity		= tmp_capacity;
		    other.allocator	= tmp_allocator;
	    }

        void    clear()
        {
            while (this->_size)
                this->pop_back();
            this->_size = 0;

        }

        /*

                Allocator:
 
        */

        allocator_type			&get_allocator()
        { 
            return this->allocator; 
        }

	    const allocator_type	&get_allocator() const 
        { 
            return this->allocator; 
        }

        friend void swap (vector& x, vector& y)                         
        { 
            x.swap(y); 
        }

        friend bool	operator==(const vector &lhs, const vector &rhs)
	    {
		    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	    }
	    friend bool	operator!=(const vector &lhs, const vector &rhs)
	    {
		    return !(lhs == rhs);
	    }
	    friend bool	operator<(const vector &lhs, const vector &rhs)
	    {
		    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	    }
	    friend bool	operator>(const vector &lhs, const vector &rhs)
	    {
		    return rhs < lhs;
	    }
	    friend bool	operator<=(const vector &lhs, const vector &rhs)
	    {
		    return !(lhs > rhs);
	    }
	    friend bool	operator>=(const vector &lhs, const vector &rhs)
	    {
		    return !(lhs < rhs);
	    }


        private:
        size_type  _size;
        size_type  _capacity;
        value_type		*data;
        allocator_type	allocator;
};

};

#endif