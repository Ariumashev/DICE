#include <iostream>
#include <vector>

int add(int a, int b) {
    return a + b;
}

void unusedFunction() {
    std::vector<int> v = {1, 2, 3};
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
}

int main() {
    int x = 0;

    if (x == 0) {
        std::cout << "hello" << std::endl;}

    int result = add(1, 2);

    std::cout << "result:" << result << std::endl;

    return 0;
}