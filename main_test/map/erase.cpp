#include "../../map.hpp"
#include <map>
#include <list>
#include <iterator>
#include "../../ite/map_iterator.hpp"
#define T1 int
#define T2 std::string
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator iterator;
#define _pair ft::pair

static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

int		main(void)
{
	
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_erase(mp, ++mp.begin());

	ft_erase(mp, mp.begin());

	ft_erase(mp, --mp.end());

	//--ite;
	//std::cout << ite->first << std::endl;

	iterator it= mp.begin();
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
	it++;
	std::cout << it->first << std::endl;
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	iterator ite= mp.end();
	std::cout << ite->first << std::endl;
	ite--;
	std::cout << ite->first << std::endl;
	ite--;
	std::cout << ite->first << std::endl;
	ite--;
	std::cout << ite->first << std::endl;
	ft_erase(mp, --(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
	printSize(mp);
	
	/*std::cout << ite->first << std::endl;
	ite--;
	std::cout << ite->first << std::endl;
	ite--;
	std::cout << ite->first << std::endl;
	ite--;
	std::cout << ite->first << std::endl;*/
	ft_erase(mp, --(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	printSize(mp);
	ft_erase(mp, mp.begin(), mp.end());



	return (0);
}         