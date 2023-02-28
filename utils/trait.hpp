#ifndef TRAIT_HPP
# define TRAIT_HPP

namespace ft
{
    	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 	first_argument_type;
		typedef Arg2 	second_argument_type;
		typedef Result 	result_type;
	};

    template <class T>
	struct less: ft::binary_function<T, T, bool>
	{
		bool operator() (const T& x, const T& y) const
		{
			return (x < y);
		}
	};

	template <class T>
	struct more: ft::binary_function<T, T, bool>
	{
		bool	operator() (const T& first, const T& second) const 
		{
			return (first > second);
		}
	};

    template <bool B>
    struct enable_if {};

    template <>
    struct enable_if<true> { typedef int type; };

        template <typename T>
    struct is_integral { static const bool value = false; };

    template <>
    struct is_integral<bool> { static const bool value = true; };
        
    template <>
    struct is_integral<char> { static const bool value = true; };

    template <>
    struct is_integral<short> { static const bool value = true; };

    template <>
    struct is_integral<int> { static const bool value = true; };

    template <>
    struct is_integral<long> { static const bool value = true; };

    template <>
    struct is_integral<long long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned char> { static const bool value = true; };

    template <>
    struct is_integral<unsigned short> { static const bool value = true; };

    template <>
    struct is_integral<unsigned int> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };

}
#endif