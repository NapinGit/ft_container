#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>

# include <stdexcept>
#include "trait.hpp"
#include "pair.hpp"
# define RED 0
# define BLACK 1

# define LEFT 0
# define RIGHT 1
namespace ft
{
    template<typename Key, typename T, typename Compare >
    class node
    {
        
        public :
        typedef Key						        key_type;
	    typedef T								mapped_type;
	    typedef ft::pair<Key, T>			value_type;
        typedef value_type*	            		pointer_value_type;
	    typedef std::size_t						size_type;
        
        node( void ): parent(NULL), right(NULL), left(NULL), _end(NULL), color(RED)
        {
		    value->first = Key();
		    value->second = T();
	    }

        node( value_type &value ): parent(NULL), right(NULL), left(NULL), _end(NULL), value(value),  color(RED)
        { 
            return;
        }

        node( const node &other ): parent(other.parent), right(other.right), left(other.left), _end(other._end), value(other.value), color(other.color)
        { 
            return;
        }

        ~node( void )
	    {
		    return;
	    }

        node&	operator=( const node& other )
        {
    
            this->parent = other.parent;
            this->right = other.right;
            this->left = other.left;
            this->color = other.color;
            this->value = other.value;
            return *this;
        }

        /*


            ACCESS TO PAIR OR PAIR VALUE < KEY , T >


        */

        value_type&		getValue( void ) 
        { 
            return value; 
        }

        const value_type&		getValue( void ) const 
        { 
            return value;
        }

        const key_type&	getKey( void ) const 
        { 
            return value.first;
        }
	
        mapped_type&	getMapped( void ) 
        {
            return value.second;
        }

        bool			isGodFather( void) const
	    {
		    return this->parent == this;
	    }

	    const mapped_type&	getMapped( void ) const 
        { 
            return value.second; 
        }

        node*   get_minimum( void )
        {
		    node*	minimum = this;

		    while (minimum->left)
		    {
			    minimum = minimum->left;
		    }
		    return minimum;
	    }

        value_type*				operator->( void ) const 
        { 
            return &this->getValue(); 
        }

        void swap(node *other)
        {
            node* tmp;

            tmp = this;
            this->parent = other->parent;
            this->right = other->right;
            this->left = other->left;
            this->color = other->color;
            this->value = other->value;

            other->parent = tmp->parent;
            other->right = tmp->right;
            other->left = tmp->left;
            other->color = tmp->color;
            other->value = tmp->value;
        }

        node* get_successor()
        {
		    if (this->right != NULL)
			    return minValue(this->right);
		    node* n = this;
		    node* p = this->parent;
            if (p == NULL)
                return _end;
		    while (p != NULL && n == p->right)
		    {
			    n = p;
			    p = p->parent;
		    }
            if (p == NULL)
                return _end;
		    return p;
        }

        node* minValue(node* node)
	    {
		    class node* tmp = node;

    		while (tmp != NULL && tmp->left != NULL)
	    	{
		    	tmp = tmp->left;
		    }
		    return tmp;
	    }

        node*   get_maximum( void )
        {
		    node*	maximum = this;

		    while (maximum->right)
		    {
			    maximum = maximum->right;
		    }
		    return maximum;
	    }


        node*   get_end( void )
        {

		    return _end;
	    }

        node *uncle() 
        {
            if (parent == NULL or parent->parent == NULL)
                return NULL;
            if (parent->isOnLeft())
                return parent->parent->right;
            else
                return parent->parent->left;
        }
 
        bool isOnLeft() 
        { 
            return this == parent->left; 
        }
 
        node *sibling() 
        {
            if (parent == NULL)
                return NULL;
            if (isOnLeft())
                return parent->right;
            return parent->left;
        }
 
        void moveDown(node *nParent) 
        {
            if (parent != NULL) 
            {
                if (isOnLeft()) 
                {
                    parent->left = nParent;
                } 
                else 
                {
                    parent->right = nParent;
                }
            }
            nParent->parent = parent;
            parent = nParent;
        }

        bool hasRedChild() 
        {
            return (left != NULL and left->color == RED) or (right != NULL and right->color == RED);
        }

        bool            operator==(const node &rhs) const 
        { 
            return (*this == rhs);
        }

        bool            operator!=(const node &rhs) const
        { 
             return (*this != rhs);
        }

        public:
	    node*		parent;
	    node*		right;
	    node*		left;
        node*       _end;
	    bool		color;
        value_type	value;
    };
}
#endif