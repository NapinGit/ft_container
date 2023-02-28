#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"
namespace ft
{
template<typename T, typename Container = ft::vector<T> >
class	stack
{
    public:
    typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

    protected:

	Container	c;

    public:	
    explicit stack<T, Container>( const Container &container = Container() ):
		c(container)
	{
		return;
	}
 	stack<T, Container>( const stack<T>& other ) 
    { 
        *this = other; 
    }
	~stack<T, Container>( void ) 
    { 

    }

    stack		&operator=( const stack<T> &other )
	{
		if (this != &other)
			this->c = other.c;
		return *this;
	}

    bool empty() const
    {
        return (c.empty());
    }


    size_type size() const
    {
        return c.size();
    }

    value_type& top()
    {
        return c.back();
    }
    
    const value_type& top() const
    {
        return c.back();
    }

    void push (const value_type& val)
    {
        c.push_back(val);
    }
    
    void pop()
    {
        c.pop_back();
    }

    /*
    
        Relational operator

    */


    friend bool	operator>=( const stack& lhs, const stack& rhs )
	{
		return lhs.c >= rhs.c;
	}

    friend bool operator==(const stack& x, const stack& y)
    {  
       return x.c == y.c;
    }

    friend bool operator!=(const stack& x, const stack& y)
    {  
        return x.c != y.c;      
    }

    friend bool operator< (const stack& x, const stack& y)
    {  
        return x.c < y.c;   
    }

    friend bool operator<=(const stack& x, const stack& y)
    {  
        return x.c <= y.c;  
    }

    friend bool operator> (const stack& x, const stack& y)
    {  
        return x.c > y.c;
    }

};

}

#endif