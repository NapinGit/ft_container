#include "test_utils.hpp"
#include "../../set.hpp"
#include <set>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

template <class T>
void	print(set<T>& lst)
{
	for (typename set<T>::iterator it = lst.begin(); it != lst.end(); it++)
		cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  set<int> myset;

  myset.insert (100);
  myset.insert (200);
  myset.insert (300);

  cout << "myset contains:";
  for (set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  myset.clear();
  myset.insert (1101);
  myset.insert (2202);

  cout << "myset contains:";
  for (set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  return 0;
}