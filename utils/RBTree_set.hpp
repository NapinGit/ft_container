#ifndef RBTREE_SET_HPP
# define RBTREE_SET_HPP

#include <iostream>

# include <fstream>
# include "trait.hpp"
# include "pair.hpp"
# include "node_set.hpp"
# include "../ite/set_iterator.hpp"
# include "../ite/const_set_iterator.hpp"
namespace ft
{
template< typename Key, typename Cmp ,
typename Allocator >
class RBtree_set
{
    public:
    typedef ft::set_node<Key, Cmp>           	    Node;
    typedef Node*	                            node_pointer;
	typedef Key									key_type;
	typedef Key				                    value_type;
    typedef value_type*         				pointer_value_type;
	typedef std::size_t							size_type;
	typedef Allocator							allocator_type;
    typedef Cmp									key_compare;
    typedef ft::set_iterator<key_type , key_compare>	iterator;
    typedef ft::const_set_iterator<iterator>	const_iterator;

    private:
        Node *root;
        Node*    			    _end;
	    Cmp     			    compare;
	    size_type			    _size;
	    allocator_type		    _allocator;
	    std::allocator<Node>	_nodeAlloc;

    protected:



Node* find_key(const key_type& k, Node *node) const
    {
        if (node == NULL || node == this->_end)
        {
            return (this->_end);
        }
        if (compare(k , node->getKey()))
        {
            node = find_key(k ,node->left);
        }
        else if (k == node->getKey())
        {
            return node;
        }
        else
        {
            node = find_key(k ,node->right);
        }
        return node;
    }

    Node* find_key(const key_type& k, Node *node)
    {
        if (node == NULL || node == this->_end)
        {
            return (this->_end);
        }
        if (compare(k , node->getKey()))
        {
            node = find_key(k ,node->left);
        }
        else if (k == node->getKey())
        {
            return node;
        }
        else
        {
            node = find_key(k ,node->right);
        }
        return node;
    }

    Node *newNode(const value_type &val) 
    {

        Node *newNode = _nodeAlloc.allocate(1);

		_allocator.construct(&newNode->value, val);
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->color = RED;
        newNode->_end = this->_end;
        return (newNode);
    }

    void initialize_end()
    {
        value_type	nilValue = Key();

		this->_end = this->newNode(nilValue);
    }

    void rotateLeft(Node *&root, Node *&pt)
    {
        Node *pt_right = pt->right;
 
        pt->right = pt_right->left;
 
        if (pt->right != NULL)
            pt->right->parent = pt;
 
        pt_right->parent = pt->parent;
 
        if (pt->parent == NULL)
            root = pt_right;
 
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
 
        else
            pt->parent->right = pt_right;
 
        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void leftRotate(Node *x)
    {
        Node *nParent = x->right;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->right = nParent->left;
        if (nParent->left != NULL)
            nParent->left->parent = x;
        nParent->left = x;
    }
 
    void rotateRight(Node *&root, Node *&pt)
    {
        Node *pt_left = pt->left;
 
        pt->left = pt_left->right;
 
        if (pt->left != NULL)
            pt->left->parent = pt;
 
        pt_left->parent = pt->parent;
 
        if (pt->parent == NULL)
            root = pt_left;
 
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
 
        else
            pt->parent->right = pt_left;
 
        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void rightRotate(Node *x) 
    {
        Node *nParent = x->left;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->left = nParent->right;
        if (nParent->right != NULL)
            nParent->right->parent = x;
        nParent->right = x;
    }

    void fixViolation(Node *&root, Node *&pt)
    {
        Node *parent_pt = NULL;
        Node *grand_parent_pt = NULL;
 
        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
        {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;
 
            if (parent_pt == grand_parent_pt->left)
            {
                Node *uncle_pt = grand_parent_pt->right;
 
                if (uncle_pt != NULL && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                   if (pt == parent_pt->right)
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            else
            {
                Node *uncle_pt = grand_parent_pt->left;
               if ((uncle_pt != NULL) && (uncle_pt->color == RED))
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    if (pt == parent_pt->left)
                    {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }
    
    void	deleteNode( Node* node )
	{
        if (node == NULL || node == this->_end)
            return;
		    _allocator.destroy(&node->value);
		    _nodeAlloc.deallocate(node, 1);
            node = NULL;
            this->_size--; 
	}
    
    void	clearNodesRecursively( Node *toDelete )
	{
		if (toDelete->left)
			clearNodesRecursively(toDelete->left);
		if (toDelete->right)
			clearNodesRecursively(toDelete->right);
		deleteNode(toDelete);
	}
    


    public:

    // Constructor

    RBtree_set(): root(NULL), _end(NULL),  compare(), _size(0), _allocator(Allocator())
    {
        this->_nodeAlloc = std::allocator<Node>();
        initialize_end();
    }

    RBtree_set( const RBtree_set& other ) :root(NULL), _end(NULL),  compare(), _size(0), _allocator(other._allocator)
	{
		this->_nodeAlloc = std::allocator<Node>();
        initialize_end();
        *this = other;

	}

	virtual ~RBtree_set( void )
    {
       clear_all();
       	_allocator.destroy(&this->_end->value);
		_nodeAlloc.deallocate(this->_end, 1);
	}

    RBtree_set&	operator=( const RBtree_set& other )
    {
        if (this == &other)
			return *this;
        clear_all();
        this->compare = other.compare;
		this->_allocator = other._allocator;
        this->_nodeAlloc = other._nodeAlloc;
        if (other._size > 0)
        {
            this->root = this->clone(other.root);
            get_parent_end(find_key(get_maximum()->getKey(), this->root));
        }
		this->_size = other._size;
        return *this;
    }

        iterator start_find_key(const key_type& k)
    {
        return iterator(find_key(k, this->root));
    }

    const_iterator start_find_key(const key_type& k) const
    {
        return iterator(find_key(k, this->root));
    }

    Node    *clone(Node *root_src)
    {
        Node *result = this->newNode(root_src->value);

		result->color = root_src->color;
		if (!root_src->left)
			result->left = NULL;
		else
		{
			result->left = this->clone(root_src->left);
			result->left->parent = result;
		}
		if (!root_src->right)
			result->right = NULL;
		else
		{
			result->right = this->clone(root_src->right);
			result->right->parent = result;
		}
		return result;
    }




    void    get_parent_end(Node *pt)
    {
        if (this->_end->parent)
        {
            if (pt->getKey() > this->_end->parent->getKey())
            {
                this->_end->parent = pt;
            }
        }
        else
        {
            this->_end->parent = pt;
        }
    }


    Node* BSTInsert(Node* root, Node *pt)
    {
        if (root == NULL)
            return pt;
        if (compare(pt->getKey() , root->getKey()))
        {
            root->left  = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (!compare(pt->getKey() , root->getKey()))
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }

    void    clear_all()
    {
        if (root)
            clearNodesRecursively(root);
        this->root = NULL;
        this->_end->parent = NULL;
        this->_size = 0;
    }

    ft::pair<iterator, bool> insertPair(value_type to_insert)
    {
        Node *retour = find_key(to_insert, this->root);
        if (retour == this->_end)
        {
            Node *ptr = newNode(to_insert);
            get_parent_end(ptr);
            this->root = BSTInsert(this->root, ptr);
            fixViolation(this->root, ptr);
            
            this->_size++;
            retour = find_key(to_insert, this->root);
            return ft::make_pair<iterator, bool>(iterator(retour), true);;
        }
        else
            return ft::make_pair<iterator, bool>(iterator(retour), false);
        
    }


    void insert(const value_type &data)
    {
       
        if (find_key(data, this->root) == this->_end)
        {
            //std::cout << "value data = " << data << std::endl;
            Node *ptr = newNode(data);
            //std::cout << "value node = " << ptr->getKey() << std::endl;
            get_parent_end(ptr);
            this->root = BSTInsert(this->root, ptr);
            fixViolation(this->root, ptr);
            this->_size++;
            //printTree("", true);
        }
        else
            return;
    }

    void printTree(std::string indent, bool last)
    {
        printTree2(this->root, indent, last);
    }

    void printTree2(Node *root, std::string indent, bool last) 
    {
        if (root != NULL) 
        {
            std::cout << indent;
            if (last) 
            {
                std::cout << "R----";
                indent += "   ";
            } 
            else
            {
                std::cout << "L----";
                indent += "|  ";
            }
            std::cout << root->getKey() << std::endl;
            printTree2(root->left, indent, false);
            printTree2(root->right, indent, true);
        }
    }

    Node*	minimum( void )
	{
        if (this->root == NULL)
            return this->_end;
        node_pointer curren = this->root;
        while (curren->left != NULL)
            curren = curren->left;
        return curren;
	}

	Node*	minimum( void ) const
	{
		if (this->root == NULL)
            return this->_end;
        node_pointer curren = this->root;
        while (curren->left != NULL)
            curren = curren->left;
        return curren;
	}

    Node*	get_maximum( void )
    {
        if (this->root == NULL)
            return this->_end;
        node_pointer curren = this->root;
        while (curren->right != NULL)
            curren = curren->right;
        return curren;
    }

    Node*	maximum( void )
    {
        return (this->_end);
    }

    Node*	maximum (void ) const
    {
        return (this->_end);
    }

        size_type size() const
    {
        return this->_size;
    }

    void	swap ( RBtree_set& other )
    {
        Node*					tmp_root = other.root;
		Node*					tmp_end = other._end;
		size_type				tmp_size = other._size;
		Cmp						tmp_comparator = other.compare;
		Allocator				tmp_valueAlloc = other._allocator;

		other.root = this->root;
		other._end = this->_end;
		other._size = this->_size;
		other.compare = this->compare;
		other._allocator = this->_allocator;
		this->root = tmp_root;
		this->_end = tmp_end;
		this->_size = tmp_size;
		this->compare = tmp_comparator;
		this->_allocator = tmp_valueAlloc;
    }
 
  void swapColors(Node *x1, Node *x2) 
  {
    bool temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }
 
  void swapValues(Node *u, Node *v) 
  {
    value_type temp;
    temp = u->value;
    u->value = v->value;
    v->value = temp;
  }
 
  void fixRedRed(Node *x) 
  {
    if (x == root) 
    {
        x->color = BLACK;
        return;
    }
    Node *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();

    if (parent->color != BLACK) 
    {
        if (uncle != NULL && uncle->color == RED) 
        {
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fixRedRed(grandparent);
        } 
        else 
        {
            if (parent->isOnLeft()) 
            {
                if (x->isOnLeft()) 
                {
                    swapColors(parent, grandparent);
                } 
                else 
                {
                    leftRotate(parent);
                    swapColors(x, grandparent);
                }
                rightRotate(grandparent);
            } 
            else 
            {
                if (x->isOnLeft()) 
                {
                    rightRotate(parent);
                    swapColors(x, grandparent);
                }
                else 
                {
                    swapColors(parent, grandparent);
                }
                leftRotate(grandparent);
            }
        }
    }
  }
 
    Node *successor(Node *x) 
    {
        Node *temp = x;
 
        while (temp->left != NULL)
        temp = temp->left;
        return temp;
    }
 
    Node *BSTreplace(Node *x) 
    {
        if (x->left != NULL and x->right != NULL)
        return successor(x->right);
        if (x->left == NULL and x->right == NULL)
        return NULL;
        if (x->left != NULL)
        return x->left;
        else
        return x->right;
    }
 
    bool deleteBoolNode(const key_type &key)
    {
        Node *out = this->find_key(key, this->root);
        if (out == this->_end)
            return 0;
        deleteCurrentNode(out);
        return 1;
    }

    iterator deleteIteNode(Node *v, iterator first) 
    {
        first++;
        value_type get = *first;
        deleteCurrentNode(v);
        if (this->_size > 0)
        {
            Node *max = get_maximum();
            this->_end->parent = max;
        }
        else
             this->_end->parent = NULL;
        Node * cpy = this->find_key(get.first, this->root);
        return iterator(cpy);
    }

    iterator getEnd()
    {
        return iterator(this->_end);
    }

    void deleteCurrentNode_start(Node *v)
    {
        deleteCurrentNode(v);
        if (_size > 0)
        {
            Node *max = get_maximum();
            this->_end->parent = max;
        }
        else
             this->_end->parent = NULL;
    }

    void deleteCurrentNode(Node *v) 
    {
        Node *u = BSTreplace(v);
 
        bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
        Node *parent = v->parent;
 
        if (u == NULL) 
        {
            if (v == root) 
            {
                root = NULL;
            }
            else
            {
                if (uvBlack) 
                {
                    fixDoubleBlack(v);
                } 
                else 
                {
                    if (v->sibling() != NULL)
                        v->sibling()->color = RED;
                }
                if (v->isOnLeft()) 
                {
                    parent->left = NULL;
                } 
                else 
                {
                    parent->right = NULL;
                }
            }
            deleteNode(v);
            return;
        }
        if (v->left == NULL or v->right == NULL) 
        {
            if (v == root) 
            {
                v->value = u->value;
                v->left = v->right = NULL;
                deleteNode(u);
            }
            else 
            {
                if (v->isOnLeft()) 
                {
                    parent->left = u;
                } 
                else 
                {
                    parent->right = u;
                }
                deleteNode(v);
                u->parent = parent;
                if (uvBlack) 
                {
                    fixDoubleBlack(u);
                } 
                else 
                {
                    u->color = BLACK;
                }
            }
            return;
        }
    swapValues(u, v);
    deleteCurrentNode(u);
  }
 
  void fixDoubleBlack(Node *x) 
  {
    if (x == root)
      return;
 
    Node *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) 
    {
      fixDoubleBlack(parent);
    } 
    else 
    {
      if (sibling->color == RED) 
      {
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) 
        {
          rightRotate(parent);
        } 
        else 
        {
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } 
      else 
      {
        if (sibling->hasRedChild()) 
        {
            if (sibling->left != NULL and sibling->left->color == RED) 
            {
                if (sibling->isOnLeft()) 
                {
                    sibling->left->color = sibling->color;
                    sibling->color = parent->color;
                    rightRotate(parent);
                }
                else 
                {
                    sibling->left->color = parent->color;
                    rightRotate(sibling);
                    leftRotate(parent);
                }
            }
            else 
            {
                if (sibling->isOnLeft()) 
                {
                    sibling->right->color = parent->color;
                    leftRotate(sibling);
                    rightRotate(parent);
                } 
                else 
                {
                    sibling->right->color = sibling->color;
                    sibling->color = parent->color;
                    leftRotate(parent);
                }
            }
          parent->color = BLACK;
        }
        else 
        {
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }

    Node *get_root()
    {
        return (this->root);
    }
};
}


#endif