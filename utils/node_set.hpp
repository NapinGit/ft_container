#ifndef NODE_SET_HPP
# define NODE_SET_HPP

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
    template<typename Key, typename Compare >
    class set_node
    {
        
        public :
	    typedef Key			                    value_type;
        typedef value_type*	            		pointer_value_type;
	    typedef std::size_t						size_type;
        
        set_node( void ): parent(NULL), right(NULL), left(NULL), _end(NULL), color(RED)
        {
		    value = Key();
	    }

        set_node( value_type &value ): parent(NULL), right(NULL), left(NULL), _end(NULL), value(value),  color(RED)
        { 
            return;
        }

        set_node( const set_node &other ): parent(other.parent), right(other.right), left(other.left), _end(other._end), value(other.value), color(other.color)
        { 
            return;
        }

        ~set_node( void )
	    {
		    return;
	    }

        set_node&	operator=( const set_node& other )
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


        const value_type&	getKey( void ) const 
        { 
            return value;
        }

        const value_type&	getValue( void ) const 
        { 
            return value;
        }

        value_type&	getKey( void )
        { 
            return value;
        }

        value_type&	getValue( void )
        { 
            return value;
        }

	

        bool			isGodFather( void) const
	    {
		    return this->parent == this;
	    }


        set_node*   get_minimum( void )
        {
		    set_node*	minimum = this;

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

        void swap(set_node *other)
        {
            set_node* tmp;

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

        set_node* get_successor()
        {
		    if (this->right != NULL)
			    return minValue(this->right);
		    set_node* n = this;
		    set_node* p = this->parent;
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

        set_node* minValue(set_node* set_node)
	    {
		    class set_node* tmp = set_node;

    		while (tmp != NULL && tmp->left != NULL)
	    	{
		    	tmp = tmp->left;
		    }
		    return tmp;
	    }

        set_node*   get_maximum( void )
        {
		    set_node*	maximum = this;

		    while (maximum->right)
		    {
			    maximum = maximum->right;
		    }
		    return maximum;
	    }


        set_node*   get_end( void )
        {

		    return _end;
	    }

        set_node *uncle() 
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
 
        set_node *sibling() 
        {
            if (parent == NULL)
                return NULL;
            if (isOnLeft())
                return parent->right;
            return parent->left;
        }
 
        void moveDown(set_node *nParent) 
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

        bool            operator==(const set_node &rhs) const 
        { 
            return (*this == rhs);
        }

        bool            operator!=(const set_node &rhs) const
        { 
             return (*this != rhs);
        }

        public:
	    set_node*		parent;
	    set_node*		right;
	    set_node*		left;
        set_node*       _end;
	    bool		color;
        value_type	value;
    };
}
#endif