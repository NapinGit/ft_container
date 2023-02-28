#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP
#include "../utils/node.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/trait.hpp"
# include "const_map_iterator.hpp"
# include <iterator>
namespace ft
{
template < typename Key, typename T, typename Compare>
class map_iterator
{
    public:

	typedef std::ptrdiff_t					difference_type;
	typedef Compare 						key_compare;
	typedef ft::node< Key, T, key_compare>           node;
	typedef	Key			                        key_type;
    typedef std::bidirectional_iterator_tag     iterator_category;
	typedef	T					                mapped_type;
	typedef	pair< Key, T>	                    value_type;
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

    explicit map_iterator(node  *newPtr): _node(newPtr)
	{
        return;
    }

	map_iterator() : _node(NULL)
    {
        return;
    }

    map_iterator( const map_iterator<Key, T, key_compare> &other ):
		_node(other.getNode())
	{
		return;
	}

    ~map_iterator( void )
    { 
        return; 
    }

    map_iterator &operator=( const map_iterator<Key, T, key_compare> &other )
	{
		this->_node = other._node;
		return *this;
	}

	    map_iterator &operator=( const map_iterator<Key, T, key_compare> &other ) const
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
        return this->_node->getValue();
	}

    value_type*				operator->( void ) const 
    { 
        return &this->_node->getValue(); 
    }

	bool operator!=(const map_iterator& other) 
	{
		key_type	lhs =  _node->getKey();
		key_type	rhs = other.getNode()->getKey();
		mapped_type lhs2 = _node->getMapped();
		mapped_type rhs2 = other.getNode()->getMapped();
		if ( lhs == rhs && lhs2 == rhs2)
			return false;
		return true;
	}

	bool operator!=(const map_iterator& other) const
	{
		key_type	lhs =  _node->getKey();
		key_type	rhs = other.getNode()->getKey();
		mapped_type lhs2 = _node->getMapped();
		mapped_type rhs2 = other.getNode()->getMapped();
		if ( lhs == rhs && lhs2 == rhs2)
			return false;
		return true;
	}

	bool operator!=(const ft::const_map_iterator<map_iterator>& other) 
	{
		return (_node != other.getNode());
	}

	bool operator!=(const ft::const_map_iterator<map_iterator>& other) const
	{
		return (_node != other.getNode());
	}



	map_iterator operator++(int)
	{
        map_iterator tmp(*this);
		this->operator++();
		return (tmp);

	}

	map_iterator &operator++()
	{
        _node = ptr_next(_node);
		return (*this);
	}

    map_iterator &operator--(void)
	{
		_node = ptr_prev(_node);
		return (*this);
	}

	map_iterator operator--(int)
	{
		map_iterator tmp(*this);
		this->operator--();
		return (tmp);

	}

	friend bool	operator==( const map_iterator& lhs, const map_iterator& rhs )
	{
		return (lhs.getNode() == rhs.getNode());

	}

};

}


#endif