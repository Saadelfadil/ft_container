#include <iostream>
#include "vector.hpp"
#include <vector>
int main ()
{
  {
    ft::Vector<int> myvector;

    // set some initial content:
    for (int i=1;i<10;i++)
      myvector.push_back(i);
    for (int i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
    std::cout << myvector.capacity() << "\n";
    myvector.resize(5);
    myvector.resize(8,100);
    myvector.resize(12);
    myvector.resize(20, 12);

    std::cout << "myvector contains:";
    for (int i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }
  std::cout << "------------\n";
  {
    std::vector<int> myvector;

    // set some initial content:
    for (int i=1;i<10;i++)
      myvector.push_back(i);
    for (int i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
    std::cout << myvector.capacity() << "\n";
    myvector.resize(5);
    myvector.resize(8,100);
    myvector.resize(12);
    myvector.resize(20, 12);

    std::cout << "myvector contains:";
    for (int i=0;i<myvector.size();i++)
      std::cout << ' ' << myvector[i];
    std::cout << '\n';
  }

  return 0;
}