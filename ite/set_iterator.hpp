#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP
#include "../utils/node_set.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/trait.hpp"
# include "const_set_iterator.hpp"
# include <iterator>
namespace ft
{
template < typename Key, typename Compare>
class set_iterator
{
    public:

	typedef std::ptrdiff_t					difference_type;
	typedef Compare 						key_compare;
	typedef ft::set_node<Key, key_compare>           node;
	typedef	Key			                        key_type;
    typedef std::bidirectional_iterator_tag     iterator_category;
	typedef	const Key                                value_type;
    typedef	node*							pointer;
	typedef	value_type&							reference;
	


    private:

    pointer   _node;

	pointer ptr_next(pointer _current)
	{
		if (_current->right)
		{
			_current = _current->right;
			while (_current->left) 
				_current = _current->left;
		}
		else 
		{
			while (_current->parent && _current == _current->parent->right)
				_current = _current->parent;
			_current = _current->parent;
		}
		if (_current == NULL)
			return _node->get_end();
		return (_current);
	}

	pointer ptr_prev(pointer _current)
	{
		if (_current && _current == _node->get_end())
			return _node->get_end()->parent;
		if (_current->left)
		{
			_current = _current->left;
			while (_current->right)
				_current = _current->right;
		}
		else
		{ 
			while (_current->parent && _current == _current->parent->left)
				_current = _current->parent;
			_current = _current->parent;
		}

		return (_current);
	}	

    public:

    explicit set_iterator(node  *newPtr): _node(newPtr)
	{
        return;
    }

	set_iterator() : _node(NULL)
    {
        return;
    }

    set_iterator( const set_iterator<Key, key_compare> &other ):
		_node(other.getNode())
	{
		return;
	}

	set_iterator( const ft::const_set_iterator<set_iterator<Key, key_compare> > &other ):
		_node(other.getNode())
	{
		return;
	}

    ~set_iterator( void )
    { 
        return; 
    }

    set_iterator &operator=( const set_iterator<Key, key_compare> &other )
	{
		this->_node = other._node;
		return *this;
	}

	    set_iterator &operator=( const set_iterator<Key, key_compare> &other ) const
	{
		this->_node = other._node;
		return *this;
	}

    node	*getNode( void ) const
    { 
        return _node; 
    }

    reference operator*() const
	{
        return this->_node->getKey();
	}

    value_type*				operator->( void ) const 
    { 
		return &this->_node->getKey();
        //return &this->_node; 
    }

	bool operator!=(const set_iterator& other) 
	{
		key_type	lhs =  _node->getKey();
		key_type	rhs = other.getNode()->getKey();
		if ( lhs == rhs)
			return false;
		return true;
	}

	bool operator!=(const set_iterator& other) const
	{
		key_type	lhs =  _node->getKey();
		key_type	rhs = other.getNode()->getKey();
		if ( lhs == rhs )
			return false;
		return true;
	}

	bool operator!=(const ft::const_set_iterator<set_iterator>& other) 
	{
		return (_node != other.getNode());
	}

	bool operator!=(const ft::const_set_iterator<set_iterator>& other) const
	{
		return (_node != other.getNode());
	}



	set_iterator operator++(int)
	{
        set_iterator tmp(*this);
		this->operator++();
		return (tmp);

	}

	set_iterator &operator++()
	{
        _node = ptr_next(_node);
		return (*this);
	}

    set_iterator &operator--(void)
	{
		_node = ptr_prev(_node);
		return (*this);
	}

	set_iterator operator--(int)
	{
		set_iterator tmp(*this);
		this->operator--();
		return (tmp);

	}

	friend bool	operator==( const set_iterator& lhs, const set_iterator& rhs )
	{
		return (lhs.getNode() == rhs.getNode());

	}

};

}


#endif