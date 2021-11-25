#include <iostream>
#include <vector>
#include "vector.hpp"

template <typename T>
void Printvector(const ft::Vector<T>& vector)
{
    std::cout << std::endl << "--- Start Elements of vector ---" <<  std::endl;
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << std::endl;
    std::cout << "--- End of Elements of vector ---" <<  std::endl;
}

int main()
{
    ft::Vector<int>::iterator i;
    ft::Vector<int>::const_iterator c_it(i);

    // c_it == i;

}


