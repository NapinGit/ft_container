#include "../../set.hpp"
#include <list>

#define T1 int

#define _pair ft::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << *iterator;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_SET>
void	printSize(T_SET const &st, bool print_content = 1)
{
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "max_size: " << st.max_size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = st.begin(), ite = st.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int		main(void)
{
	std::list<T1> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ft::set<T1> st(lst.begin(), lst.end());
	ft::set<T1>::iterator it = st.begin(), ite = st.end();

	ft::set<T1> st_range(it, --(--ite));
	for (int i = 0; i < 5; ++i)
		st.insert(i * 5);

	it = st.begin(); ite = --(--st.end());
	ft::set<T1> st_copy(st);
	for (int i = 0; i < 7; ++i)
		st.insert(i * 7);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(st);
	printSize(st_range);
	printSize(st_copy);

	st = st_copy;
	st_copy = st_range;
	st_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(st);
	printSize(st_range);
	printSize(st_copy);
	return (0);
}
