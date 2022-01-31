// erasing from map
#include <iostream>
#include <map>
#include "./map.hpp"

void helper()
{
    ft::Map<char,int> mymap;
  ft::Map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  // mymap['c']=30;
  // mymap['d']=40;
  // mymap['e']=50;
  // mymap['f']=60;

    // mymap.hamiiid();
  // it=mymap.find('b');
  // mymap.erase (it);                   // erasing by iterator

  // mymap.erase ('c');                  // erasing by key

  // it=mymap.find ('e');
  mymap.erase ( mymap.begin(), mymap.end() );    // erasing by range

//   show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}


int main ()
{
    helper();
    system("leaks a.out");
  return 0;
}