#include <iostream>
#include "Vector.hpp"

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
    ft::Vector<int> vector;

    vector.push_back(1);
    vector.push_back(3);
    vector.push_back(5);
    vector.push_back(7);

    ft::Vector<int>::iterator it = vector.begin();
    for(ft::Vector<int>::iterator it = vector.begin(); it < vector.end();it++)
    {
        std::cout << *it<< std::endl;
    }
    // vector.pop_back();
    // vector.insert(1);
    // vector.clear();
    // ft::VectorIterator<int> it = vector.end();
    // vector.PushBack("Saad");
    // vector.PushBack("El fadil");
    // vector.PushBack("Agadir");
    // // vector.deallocate_memory();
    Printvector(vector);
}


