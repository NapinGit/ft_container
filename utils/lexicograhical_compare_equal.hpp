#ifndef LEXICOGRAPHICAL_COMPARE_EQUAL_HPP
#define LEXICOGRAPHICAL_COMPARE_EQUAL_HPP

namespace ft
{
/*template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
  while (first1!=last1)
  {
    if (first2==last2 || *first2<*first1) return false;
    else if (*first1<*first2) return true;
    ++first1; ++first2;
  }
  return (first2!=last2);
}*/

template <class Ite1, class Ite2>
bool	lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		++first1; ++first2;
	}
	if (first1 == last1)
		return (first2 != last2);
	else if (first2 == last2)
		return (false);
	return (*first1 < *first2);
}

template <class InputIterator1, class InputIterator2>
  bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
  while (first1!=last1) {
    if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
      return false;
    ++first1; ++first2;
  }
  return true;
}

/*template <class Ite1, class Ite2>
bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
{
	while (first1 != last1)
	{
		if (*first1 != *first2)
			return false;
		++first1; ++first2;
	}
	return true;
}*/


	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}
}

#endif