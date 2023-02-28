 #ifndef PAIR_HPP
# define PAIR_HPP
namespace ft
{
    template<typename _T1, typename _T2>
    struct pair
    {
        typedef _T1	first_type;
	    typedef _T2	second_type;

        pair(): first(),  second()
        {

        }

        pair(const pair &other): first(other.first),  second(other.second)
        {

        }

        template<typename _U1, typename _U2>
	    pair( const pair<_U1, _U2>& _p ) : first(_p.first), second(_p.second) 
        { 

        }

        pair( const _T1& _a, const _T2& _b ) : first(_a), second(_b) 
        {

        }

        ~pair()
        {

        }

        pair &operator=(const pair &x) 
        {
		    if (this != &x)
            {
                //pair out(x);
                //*this = *out;
                //return out;
                
			    this->first = x.first;
			    this->second = x.second;
		    }
			return *this;
		}

        bool operator>(const pair &x) const
        {
            if (this->first > x.first && this->second > x.second)
                return (true);
            return (false);
        }

        bool operator<(const pair &x) const
        {
            if (this->first < x.first && this->second < x.second)
                return (true);
            return (false);
        }

        void swap(pair *other)
        {
            pair tmp(*this);

            this = &other;
            other =  &tmp;
        }

        first_type first;
        second_type second;

    };
    template<typename _T1, typename _T2>
    pair<_T1, _T2> make_pair(_T1 _x, _T2 _y)
    {
	    return pair<_T1, _T2>(_x, _y);
    }

    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) 
    {
	    return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) 
    {
	    return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator< (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) 
    {
	    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) 
    {
	    return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator> (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)  
    {
	    return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
	return !(lhs < rhs);
}
}

#endif