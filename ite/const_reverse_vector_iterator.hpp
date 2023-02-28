#ifndef CONST_REVERSE_VECTOR_ITERATOR_HPP
# define CONST_REVERSE_VECTOR_ITERATOR_HPP

# include "../utils/iterator_traits.hpp"
# include "reverse_vector_iterator.hpp"



namespace ft
{
	

	template<class It>
	class const_reverse_vector_iterator
	{
		public:
		typedef It 														iterator_type;
		typedef typename ft::iterator_traits<It>::pointer             	pointer;
		typedef typename ft::iterator_traits<It>::difference_type     	difference_type;
		typedef typename ft::iterator_traits<It>::iterator_category   	iterator_category;
		typedef typename ft::iterator_traits<It>::value_type    	value_type;
		typedef const value_type	 									&reference;

		const_reverse_vector_iterator(): m_current(NULL)
		{}

		const_reverse_vector_iterator(const ft::vector_iterator<value_type>& r): m_current(r.base())
		{}

		const_reverse_vector_iterator(const ft::const_vector_iterator< ft::vector_iterator<value_type> >& r): m_current(r.base())
		{}

		const_reverse_vector_iterator(const const_reverse_vector_iterator<It>& r): m_current(r.base())
		{}

		const_reverse_vector_iterator(const ft::reverse_vector_iterator< ft::vector_iterator<value_type> >& r): m_current(r.base())
		{}

		const_reverse_vector_iterator & operator=( const const_reverse_vector_iterator& r)
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

		const value_type *operator->() const
		{
			It temp(m_current);
			--temp;
			return &(operator*());
		}

		reference operator[](difference_type off) const
		{
			return this->m_current[-off - 1];
		}

		const_reverse_vector_iterator& operator++()
		{
			--m_current;
			return *this;
		}

		const_reverse_vector_iterator operator++(int)
		{
			const_reverse_vector_iterator temp((*this));
			--m_current;
			return temp;
		}

		const_reverse_vector_iterator& operator--()
		{
			++m_current;
			return *this;
		}

		const_reverse_vector_iterator operator--(int)
		{
			const_reverse_vector_iterator temp((*this));
			++m_current;
			return temp;
		}

		friend bool operator==(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return l.m_current == r.m_current;
		}
		
		friend bool operator!=(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return l.m_current != r.m_current;
		}

		friend bool operator<(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return l.m_current > r.m_current;
		}

		friend bool operator<=(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return l.m_current >= r.m_current;
		}

		friend bool operator>(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return l.m_current < r.m_current;
		}

		friend bool operator>=(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return l.m_current <= r.m_current;
		}

		const_reverse_vector_iterator& operator+=(difference_type off)
		{
			m_current -= off; return *this;
		}

		const_reverse_vector_iterator& operator-=(difference_type off)
		{
			m_current += off; return *this;
		}

		friend const_reverse_vector_iterator operator+(const_reverse_vector_iterator l, difference_type off)
		{
			return (l += off);
		}

		friend const_reverse_vector_iterator operator+(difference_type off, const_reverse_vector_iterator r)
		{
			return (r += off); 
		}

		friend const_reverse_vector_iterator operator-(const_reverse_vector_iterator l, difference_type off)
		{
			return (l-= off);
		}

		friend difference_type operator-(const const_reverse_vector_iterator& l, const const_reverse_vector_iterator& r)
		{
			return r.m_current - l.m_current;
		}

		private:
		It m_current;
	};
}

#endif