
#include <list>
#include "../../map.hpp"
#include <map>
#include <list>
#include <iterator>
#include "../../ite/map_iterator.hpp"
#include "test_utils.hpp"

#define T1 char
#define T2 int
typedef ft::pair<const T1, T2> T3;



//#include "test_utils.hpp"
#include <map>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  map<char,int> mymap;

  mymap['x']=100;
  mymap['y']=200;
  mymap['z']=300;

  cout << "mymap contains:\n";
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a']=1101;
  mymap['b']=2202;

  cout << "mymap contains:\n";
  for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  return 0;
}