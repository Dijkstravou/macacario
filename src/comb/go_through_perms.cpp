#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};

    // Ordena o vetor em ordem crescente
    std::sort(vec.begin(), vec.end());

    do {
        // Imprime a permutacao atual
        for (int i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(vec.begin(), vec.end()));

    return 0;
}