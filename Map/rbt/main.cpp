#include "map.hpp"
int main()
{
    ft::Map<int ,int>d;
    d.insert(ft::make_pair(12, 454));
    d.insert(ft::make_pair(13, 42));
    d.insert(ft::make_pair(14, 41));
    d.insert(ft::make_pair(15, 457));
    d.insert(ft::make_pair(16, 455));
    ft::Map<int ,int>::iterator it = d.begin();
    for (; it != d.end(); ++it) {
        std::cout << "LAYN3EL TABON MOK --> " << it->second << std::endl;
    }
}