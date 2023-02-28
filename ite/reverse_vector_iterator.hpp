#ifndef REVERSE_VECTOR_ITERATOR_HPP
# define REVERSE_VECTOR_ITERATOR_HPP

# include "../utils/iterator_traits.hpp"
//# include "const_reverse_vector_iterator.hpp"

namespace ft
{

	template<class It>
	class reverse_vector_iterator
	{
		public:
		typedef It 														iterator_type;
		typedef typename ft::iterator_traits<It>::pointer             	pointer;
		typedef typename ft::iterator_traits<It>::reference           	reference;
		typedef typename ft::iterator_traits<It>::difference_type     	difference_type;
		typedef typename ft::iterator_traits<It>::iterator_category   	iterator_category;
		typedef typename ft::iterator_traits<It>::value_type          	value_type;
		
		private:
		It m_current;

		public:

		reverse_vector_iterator(): m_current()
		{}

		explicit reverse_vector_iterator(const ft::vector_iterator<value_type>& r): m_current(r.base())
		{}

		explicit reverse_vector_iterator(const ft::const_vector_iterator< ft::vector_iterator<value_type> >& r): m_current(r.base())
		{}

		reverse_vector_iterator(const reverse_vector_iterator<It>& r): m_current(r.base())
		{}

		reverse_vector_iterator & operator=( const reverse_vector_iterator& r)
		{
			m_current = r.base();   return *this;
		}

		It base() const
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

		pointer operator->()
		{
			It temp(m_current);
			--temp;
			return &(operator*());
		}

		pointer operator->() const
		{
			It temp(m_current);
			--temp;
			return &(operator*());
		}

		reference operator[](difference_type off) const
		{
			return this->m_current[-off - 1];
		}

		reverse_vector_iterator& operator++()
		{
			--m_current;
			return *this;
		}

		reverse_vector_iterator operator++(int)
		{
			reverse_vector_iterator temp((*this));
			--m_current;
			return temp;
		}

		reverse_vector_iterator& operator--()
		{
			++m_current;
			return *this;
		}

		reverse_vector_iterator operator--(int)
		{
			reverse_vector_iterator temp((*this));
			++m_current;
			return temp;
		}

		friend bool operator==(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return l.m_current == r.m_current;
		}
		
		friend bool operator!=(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return l.m_current != r.m_current;
		}

		friend bool operator<(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return l.m_current > r.m_current;
		}

		friend bool operator<=(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return l.m_current >= r.m_current;
		}

		friend bool operator>(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return l.m_current < r.m_current;
		}

		friend bool operator>=(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return l.m_current <= r.m_current;
		}

		reverse_vector_iterator& operator+=(difference_type off)
		{
			m_current -= off; return *this;
		}

		reverse_vector_iterator& operator-=(difference_type off)
		{
			m_current += off; return *this;
		}

		friend reverse_vector_iterator operator+(reverse_vector_iterator l, difference_type off)
		{
			return (l += off);
		}

		friend reverse_vector_iterator operator+(difference_type off, reverse_vector_iterator r)
		{
			return (r += off); 
		}

		friend reverse_vector_iterator operator-(reverse_vector_iterator l, difference_type off)
		{
			return (l-= off);
		}

		friend difference_type operator-(const reverse_vector_iterator& l, const reverse_vector_iterator& r)
		{
			return r.m_current - l.m_current;
		}

	};
}// namespace ft

#endif