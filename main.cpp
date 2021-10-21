#include <iostream>
#include "vector.hpp"

template <typename T>
void Printvector(const Vector<T>& vector)
{
    std::cout << std::endl << "--- Start Elements of vector ---" <<  std::endl;
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[i] << std::endl;
    std::cout << "--- End of Elements of vector ---" <<  std::endl;
}

int main()
{
    Vector<std::string> vector;

    vector.PushBack("Saad");
    vector.PushBack("El fadil");
    vector.PushBack("Agadir");
    vector.Clear();
    vector.PushBack("Saad");
    vector.PushBack("El fadil");
    vector.PushBack("Agadir");
    vector.insert("1337");
    vector.popBack();
    std::cout << "Size of the vector : " << vector.Size() <<  std::endl;
    Printvector(vector);
    
}


