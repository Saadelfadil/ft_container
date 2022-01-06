#include "vector.hpp"
#include "iostream"
#include <vector>
int main(){
    int arr[9] = {1,2,3,4,5,6,7,8,9}; 
    std::vector<int> a(arr,arr + 9);
    std::cout << a.size() << " " << a.capacity() << "\n";
}