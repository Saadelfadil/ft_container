#include <iostream>
#include "vector_try.hpp"

template <typename T>
void Printvector(const ft::Vector<T>& vector)
{
    std::cout << std::endl << "--- Start Elements of vector ---" <<  std::endl;
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[i] << std::endl;
    std::cout << "--- End of Elements of vector ---" <<  std::endl;
}

int main()
{
    ft::Vector<int> vector;
    

    vector.PushBack(1);
    vector.PushBack(3);
    vector.PushBack(5);
    vector.PushBack(7);

    ft::Vector<int>::iterator it = vector.begin();
    for(size_t i = 0; i < 3;i++)
    { std::cout << *it<< std::endl;it++;}
    // ft::VectorIterator<int> it = vector.end();
    // vector.Clear();
    // vector.PushBack("Saad");
    // vector.PushBack("El fadil");
    // vector.PushBack("Agadir");
    // vector.insert("1337");
    // vector.popBack();
    // // vector.deallocate_memory();
    // std::cout << "Size of the vector : " << vector.Size() <<  std::endl;
    // Printvector(vector);
}


