#ifndef CONST_SET_ITERATOR_HPP
#define CONST_SET_ITERATOR_HPP
#include "../utils/node.hpp"
#include "../utils/iterator_traits.hpp"
# include <iterator>
namespace ft
{
template <class It>
class const_set_iterator
{
    public:

		private:
			typename ft::iterator_traits<It>::pointer 						ptr;
		public:
			typedef typename ft::iterator_traits<It>::iterator_category 	iterator_category;
			typedef typename ft::iterator_traits<It>::difference_type	 	difference_type;
			typedef const typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::pointer		 		pointer;
			typedef value_type			 									&reference;
            typedef typename It::node                       node;
            typedef typename It::key_type                key_type;
			typedef typename It::key_compare                key_compare;

    private:

    pointer   _node;

	pointer ptr_next(pointer ptr)
	{
		pointer next;
		if (!ptr->right)
		{
			next = ptr;
			while (next->parent && next == next->parent->right)
				next = next->parent;
			next = next->parent;
		}
		else
		{
			next = ptr->right;
			while (next->left)
				next = next->left;
		}
		if (next == NULL)
			return _node->get_end();
		return (next);
	};

	pointer ptr_prev(pointer ptr)
	{
		pointer next;

		if (ptr && ptr == _node->get_end())
			return _node->get_end()->parent;

		if (!ptr->left)
		{
			next = ptr;
			while (next->parent && next == next->parent->left)
				next = next->parent;
			next = next->parent;
		}
		else
		{
			next = ptr->left;
			while (next->right)
				next = next->right;
		}
		return (next);
	};    

    public:

    explicit const_set_iterator(node  *newPtr): _node(newPtr)
	{
        return;
    }

	const_set_iterator() : _node(NULL)
    {
        return;
    }

    const_set_iterator(const It &cpy): _node(cpy.getNode())
	{
        return;
    }

    const_set_iterator( const const_set_iterator<It> &other ):
		_node(other.getNode())
	{
		return;
	}

    ~const_set_iterator( void )
    { 
        return; 
    }

    const_set_iterator &operator=( const const_set_iterator<It> &other )
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


	bool operator!=(const const_set_iterator& other) 
	{
            return (_node != other.getNode()); 
	}

	bool operator!=(const const_set_iterator& other) const
	{
         return (_node != other.getNode()); 
	}

	/*friend bool operator==(const const_set_iterator& l, const const_set_iterator& r)
	{
			return (l.getNode() == r.getNode());
	}*/

	/*bool operator==(const ft::set_iterator<value_type, key_compare>& itr) const
	{
		return this->ptr == itr;
	}*/


	const_set_iterator operator++(int)
	{
        const_set_iterator tmp(*this);
		this->operator++();
		return (tmp);

	}

	const_set_iterator &operator++()
	{
        _node = ptr_next(_node);
		return (*this);
	}

    const_set_iterator &operator--(void)
	{
		_node = ptr_prev(_node);
		return (*this);
	}

	const_set_iterator operator--(int)
	{
		const_set_iterator tmp(*this);
		this->operator--();
		return (tmp);
	}

};

}


#endif