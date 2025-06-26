#include "prvector.h"

int main() {
    my_vector<int> v;

    std::cout << "input: ";
    int a, b, c;
    std::cin >> a >> b >> c;
    
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);

    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << std::endl;

    my_vector<int> v2 = v;
    v2.pop_back();

    for (int x : v2) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}