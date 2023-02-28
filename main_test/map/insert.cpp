#include "../../map.hpp"
#include <map>
#include <iterator>
#include "../../ite/map_iterator.hpp"
#define T1 int
#define T2 std::string
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator iterator;
#define _pair ft::pair

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


template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	iterator tmp;

	//std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

void	ft_insert(ft::map<T1, T2> &mp, ft::pair<T1, T2> p)
{
	//iterator tmp;
    _pair<iterator, bool> tmp;
    tmp = mp.insert(p);
    //ft::pair<ft::map<int, std::string>::iterator, bool> yol = mp.insert(p);
    //std::cout << "RETURN = first = "  << yol.first->first << " second =  " <<yol.second << std::endl;
    //std::cout << "insert return: " << printPair(tmp.first);
    

	//std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	//tmp = mp.insert(p);
	//std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

int main()
{
    ft::map<int ,std::string> mp;
    ft_insert(mp, T3(42, "lol"));
    std::cout << "bondour" << std::endl;
	ft_insert(mp, T3(42, "mdr"));

	ft_insert(mp, T3(50, "mdr"));
	ft_insert(mp, T3(35, "funny"));

	ft_insert(mp, T3(45, "bunny"));
	ft_insert(mp, T3(21, "fizz"));
	/*ft_insert(mp, T3(7, "buzz"));
	ft_insert(mp, T3(6, "buzz"));
	ft_insert(mp, T3(5, "buzz"));
	ft_insert(mp, T3(4, "buzz"));
	ft_insert(mp, T3(3, "buzz"));
	ft_insert(mp, T3(2, "buzz"));
	ft_insert(mp, T3(1, "buzz"));
	ft_insert(mp, T3(8, "buzz"));
	ft_insert(mp, T3(9, "buzz"));
	ft_insert(mp, T3(10, "buzz"));
	ft_insert(mp, T3(11, "buzz"));*/
	//ft_insert(mp, T3(11, "buzz"));
    mp.print_tree();

	ft::map<int ,std::string> mp2;
	mp2 = mp;
	mp2.clear();
	iterator it = mp2.begin();
	iterator ite = mp2.end();
	std::cout << "ITE  est egal a = " << std::endl;
	
	std::cout << it->first << std::endl;
	it++;
	mp2.erase(it);
	//mp2.print_tree();


	/*while (it != ite)
	{
		//std::cout << it->first << std::endl;
		it++;
	}*/

	/*ft_insert(mp, mp.begin(), T3(55, "fuzzy"));*/

	/*ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
	ft_insert(mp2, mp2.end(), T3(1500, "World"));*/
    return 0;
}                     