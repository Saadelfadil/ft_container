#include <iostream>
#include "vector.hpp"

template <typename T>
void Printvector(const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[i] << std::endl;
    std::cout << "------------------" << std::endl;
}

int main()
{
    Vector<std::string> vector;

    vector.PushBack("Saad");
    vector.PushBack("El fadil");
    vector.PushBack("Agadir");

    Printvector(vector);
}