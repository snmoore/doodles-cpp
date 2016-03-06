// Trivial examples using pairs

#include <iostream> // For std::cout etc

std::pair<int,char> pair1() {
    std::pair<int,char> result { 1, 'a' };
    return result;
}

std::pair<int,char> pair2() {
    return std::pair<int,char>{ 2, 'b' };
}

std::pair<int,char> pair3() {
    std::pair<int,char> result;
    result.first = 3;
    result.second = 'c';
    return result;
}

std::pair<int,char> pair4() {
    return std::make_pair(4, 'd');
}

int main() {
    std::cout << "Pair 1: " << pair1().first << " " << pair1().second << std::endl;
    std::cout << "Pair 2: " << pair2().first << " " << pair2().second << std::endl;
    std::cout << "Pair 3: " << pair3().first << " " << pair3().second << std::endl;
    std::cout << "Pair 4: " << pair4().first << " " << pair4().second << std::endl;
}
