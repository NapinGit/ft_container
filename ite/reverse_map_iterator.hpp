#ifndef REVERSE_MAP_ITERATOR_HPP
#define REVERSE_MAP_ITERATOR_HPP
#include "../utils/node.hpp"
#include "../utils/iterator_traits.hpp"
# include <iterator>
namespace ft
{
template <class It>
class reverse_map_iterator
{


		public:
			typedef typename ft::iterator_traits<It>::iterator_category 	iterator_category;
			typedef typename ft::iterator_traits<It>::difference_type	 	difference_type;
			typedef typename ft::iterator_traits<It>::value_type		value_type;
			typedef typename ft::iterator_traits<It>::pointer		 		pointer;
			typedef value_type			 									&reference;
            typedef typename It::node                       node;
            typedef typename It::key_type                key_type;
            typedef typename It::mapped_type             mapped_type;
            typedef typename It::key_compare            key_compare;
        private:
            It m_current;

        public:

    	reverse_map_iterator():m_current()
		{}

        reverse_map_iterator(node *ptr):m_current(ptr)
		{}

		explicit reverse_map_iterator(const ft::map_iterator<key_type, mapped_type, key_compare> & r):m_current(r.getNode())
		{}

		explicit reverse_map_iterator(const ft::const_map_iterator< ft::map_iterator<key_type, mapped_type, key_compare> >& r):m_current(r.getNode())
		{}


		reverse_map_iterator(const reverse_map_iterator<It>& r):m_current(r.base())
		{}

        reverse_map_iterator & operator=( const reverse_map_iterator& r)
		{
			m_current = r.base();   
            return *this;
		}

        It	base( void ) const
        { 
            return m_current; 
        }

        reference operator*() const
		{
			It temp(m_current);
			--temp;
			reference r = *temp;
			return r;
		}

		value_type*	 operator->()
		{
			It temp(m_current);
			--temp;
			return &(operator*());
		}

		value_type* operator->() const
		{
			It temp(m_current);
			--temp;
			return &(operator*());
		}

        reverse_map_iterator& operator++()
		{
			--m_current;
			return *this;
		}

		reverse_map_iterator operator++(int)
		{
			reverse_map_iterator temp((*this));
			--m_current;
			return temp;
		}

		reverse_map_iterator& operator--()
		{
			++m_current;
			return *this;
		}

		reverse_map_iterator operator--(int)
		{
			reverse_map_iterator temp((*this));
			++m_current;
			return temp;
		}

        friend bool operator==(const reverse_map_iterator& l, const reverse_map_iterator& r)
		{
			return l.m_current == r.m_current;
		}
		
		friend bool operator!=(const reverse_map_iterator& l, const reverse_map_iterator& r)
		{
			return l.m_current != r.m_current;
		}
};
}

#endif