#ifndef MAP_HPP
# define MAP_HPP

# include "utils/RBTree.hpp"
#include <stdint.h>
# include <limits>
#include "utils/trait.hpp"
#include "ite/map_iterator.hpp"
#include "ite/const_map_iterator.hpp"
#include "ite/reverse_map_iterator.hpp"
#include "ite/const_reverse_map_iterator.hpp"
#include "utils/node.hpp"
#include "utils/lexicograhical_compare_equal.hpp"
namespace ft
{

template< class Key, class T, class Cmp = std::less<Key>,
	class Allocator = std::allocator<ft::pair< Key, T> > >
class map
{
    public:

	typedef Key									key_type;
	typedef Cmp									key_compare;
	typedef ft::node< Key, T, key_compare>           	node;
	typedef T									mapped_type;
	typedef pair< Key, T>						value_type;
	typedef std::size_t							size_type;
	typedef std::ptrdiff_t						difference_type;
	typedef Allocator							allocator_type;
	typedef ft::RBtree<Key, T, key_compare, Allocator>		tree_type;

	typedef typename Allocator::reference			reference;
	typedef typename Allocator::const_reference		const_reference;
	typedef typename Allocator::pointer				pointer;
	typedef typename Allocator::const_pointer		const_pointer;

	typedef ft::map_iterator<key_type , mapped_type, key_compare>	iterator;
	typedef ft::const_map_iterator<iterator>	const_iterator;
	typedef ft::reverse_map_iterator<iterator>	reverse_iterator;
	typedef ft::const_reverse_map_iterator<iterator>	const_reverse_iterator;


	class value_compare
	{

	public:

		typedef bool		result_type;
		typedef value_type	first_argument_type;
		typedef value_type	second_argument_type;


		Cmp	comp;

		value_compare( Cmp c = Cmp() ): comp(c) { return ; }


		bool operator()( const value_type& lhs, const value_type& rhs ) const
		{
			return comp(lhs.first, rhs.first);
		}

	};

    private:

	tree_type		_RBTree;
	key_compare		compare;
	allocator_type	_allocator;

	value_type const &min(value_type const &a, value_type const &b) const
	{
		return (a < b ? a : b);
	}

	iterator unconst_begin()const
	{
		return iterator(this->_RBTree.minimum());
	}

	iterator unconst_end() const
	{
		return iterator(this->_RBTree.maximum());
	}
	protected:
	
	void print_tree()
	{
		this->_RBTree.printTree("", true);
	}
	public:
	explicit map(const key_compare &cmp = key_compare(), const Allocator &alloc = allocator_type()) : _RBTree(), compare(cmp), _allocator(Allocator(alloc))
	{

	}


	template< typename InputIt >
	map( InputIt first, InputIt last, const key_compare &cmp = key_compare(), const Allocator &alloc = allocator_type() ): compare(cmp), _allocator(alloc)
	{
		this->insert(first, last);
	}
	
	map(const map& other)
	{
		this->_RBTree = other._RBTree;
		this->compare = other.compare;
		this->_allocator = other._allocator;
	}

	~map()
	{

	}

	map	&operator=( const map& other )
	{
		if (this == &other)
			return *this;
		this->_RBTree = other._RBTree;
		this->compare = other.compare;
		this->_allocator = other._allocator;
		return *this;
	}

	/*

		Iterators:

	*/

	iterator begin()
	{
		return iterator(this->_RBTree.minimum());
	}

	const_iterator begin() const
	{
		return const_iterator(this->_RBTree.minimum());
	}

    iterator end()
	{
		return iterator(this->_RBTree.maximum());
	}

	const_iterator end() const
	{
		return const_iterator(this->_RBTree.maximum());
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(this->_RBTree.maximum());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(this->_RBTree.maximum());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(this->_RBTree.minimum());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(this->_RBTree.minimum());
	}


	/*

		Capacity:

	*/

	bool empty() const
	{
		 return _RBTree.size() == 0; 
	}

	size_type size() const
	{
		return	_RBTree.size();
	}

    size_type max_size() const
	{
		
		/*size_type out = 461168601842738790;
		return out;*/
		//return (std::numeric_limits<size_type>::max() / sizeof(ft::pair<Key, T>));
		if (sizeof(ft::pair<Key, T>) == 12)
                    return size_t(PTRDIFF_MAX) / ( sizeof(ft::pair<Key, T>) + 36);
                return size_t(PTRDIFF_MAX) / ( sizeof(ft::pair<Key, T>) + 32);

	}

	/*

		Element access:

	*/

	mapped_type& operator[] (const key_type& k)
	{
		this->insert(ft::make_pair(k, mapped_type()));
		return (this->find(k)->second);
	}

	/*

		Modifiers:

	*/


	ft::pair<iterator,bool> insert (const value_type& val)
	{
		return this->_RBTree.insertPair(val);
	}

	iterator insert (iterator position, const value_type& val)
	{

		(void)position;
		return (_RBTree.insertPair(val).first);


	}
	
	template <class InputIterator>
 	void insert (InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			this->_RBTree.insert(*first);
			first++;
		}
	}

	void erase (iterator position)
	{
		this->_RBTree.deleteCurrentNode_start(position.getNode());
	}
	
	size_type erase (const key_type& k)
	{
		return (this->_RBTree.deleteBoolNode(k));
	}

	void erase (iterator first, iterator last)
	{
		key_type f;
		value_type l;

		if (last.getNode() == last.getNode()->_end)
		{
			while (first.getNode()->getValue() != _RBTree.minimum()->getValue())
			{
				f = first.getNode()->parent->getKey();
				erase(first);
				first = find(f);
			}
			erase(first);
			first = _RBTree.getEnd();
			return ;
		}
		l = last.getNode()->getValue();
		while (first.getNode()->getValue() != l)
		{
			
			if (first.getNode()->parent || first.getNode() == _RBTree.get_root())
				f = first.getNode()->get_successor()->getKey();
			else
				f = _RBTree.get_maximum()->getKey();
			erase(first);
			first = find(f);
		}
		return ;
	}

	void swap (map& x)
	{
		allocator_type				tmp_valueAlloc = x._allocator;
		key_compare					tmp_comparator = x.compare;

		x._allocator = this->_allocator;
		x.compare = this->compare;
		this->_allocator = tmp_valueAlloc;
		this->compare = tmp_comparator;
		this->_RBTree.swap(x._RBTree);
	}

	void clear()
	{
		this->_RBTree.clear_all();
	}

	/*

		Observers:

	*/

	key_compare key_comp() const
	{ 
		return this->compare; 
	}

	value_compare	value_comp() const
	{
		return value_compare(key_comp());
	}


	/*

		Operations:

	*/

	iterator find (const key_type& k)
	{
		return this->_RBTree.start_find_key(k);

	}

	const_iterator find (const key_type& k) const
	{
		return const_iterator(this->_RBTree.start_find_key(k));
	}

	size_type count (const key_type& k) const
	{

		if (this->find(k).getNode() != this->end().getNode())
			return 1;
		return 0;
	}

	
	iterator lower_bound (const key_type & k)
	{
		iterator it = this->begin();
		while (this->compare(it->first, k) && it != this->end())
			it++;
		return (it);
	}

	const_iterator lower_bound (const key_type & k) const
	{
		const_iterator it = this->begin();
		while (this->compare(it->first, k) && it != this->end())
			it++;
		return (it);
	}

	iterator upper_bound (const key_type & k)
	{
		iterator it = this->begin();
		while (this->compare(k, it->first) == false && it != this->end())
			it++;
		return (it);
	}

	const_iterator upper_bound (const key_type & k) const
	{
		const_iterator it = this->begin();
		while (this->compare(k, it->first) == false && it != this->end())
			it++;
		return (it);
	}

	
	ft::pair<iterator,iterator> equal_range (const key_type & k)
	{
		return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
	}

	ft::pair<const_iterator,const_iterator> equal_range (const key_type & k) const
	{
		return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
	}

	/*

		Allocator:

	*/
	
	allocator_type get_allocator() const
	{
		return this->allocator; 
	}

		friend bool	operator==( const map &lhs, const map &rhs )
	{
		iterator	lhs_it = lhs.unconst_begin();
		iterator	lhs_ite = lhs.unconst_end();
		iterator	rhs_it = rhs.unconst_begin();
		iterator	rhs_ite = rhs.unconst_end();

		while (lhs_it != lhs_ite && rhs_it != rhs_ite)
		{
			if (lhs_it->second != rhs_it->second)
				return false;
			lhs_it++;
			rhs_it++;
		}
		if (lhs_it != lhs_ite || rhs_it != rhs_ite)
			return false;
		return true;
	}

	friend bool	operator!=(const map &lhs, const map &rhs) 
	{
		return !(lhs == rhs);
	}


	friend bool	operator<( const map &lhs, const map &rhs )
	{
		iterator	lhs_it = lhs.unconst_begin();
		iterator	lhs_ite = lhs.unconst_end();
		iterator	rhs_it = rhs.unconst_begin();
		iterator	rhs_ite = rhs.unconst_end();

		while (lhs_it != lhs_ite && rhs_it != rhs_ite)
		{
			if (lhs_it->second != rhs_it->second)
				return lhs_it->second < rhs_it->second;
			lhs_it++;
			rhs_it++;
		}
		if (rhs_it == rhs_ite)
			return false;
		return true;
	}


	friend bool	operator<=(const map &lhs, const map &rhs) 
	{
		return !(rhs < lhs);
	}


	friend bool	operator> (const map &lhs, const map &rhs) 
	{
		return (rhs < lhs);
	}


	friend bool	operator>=(const map &lhs, const map &rhs) 
	{
		return !(lhs < rhs);
	}

	friend void swap (map& x, map& y)                         
    { 
        x.swap(y); 
    }




};

}

#endif