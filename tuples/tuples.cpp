// Trivial examples using tuples

#include <iostream> // For std::cout etc
#include <utility>  // For std::tuple

std::tuple<int,char,std::string> tuple1() {
    std::tuple<int,char,std::string> result { 1, 'a', "Hello" };
    return result;
}

std::tuple<int,char,std::string> tuple2() {
    return std::tuple<int,char,std::string>{ 2, 'b', "World" };
}

std::tuple<int,char,std::string> tuple3() {
    std::tuple<int,char,std::string> result;
    std::get<0>(result) = 3;    // get<n> returns a reference
    std::get<1>(result) = 'c';
    std::get<2>(result) = "Say";
    return result;
}

std::tuple<int,char,std::string> tuple4() {
    return std::make_tuple(4, 'd', "Hi!");
}

int main() {
    std::cout << "Tuple 1: ";
    std::cout << std::get<0>(tuple1()) << " ";
    std::cout << std::get<1>(tuple1()) << " ";
    std::cout << std::get<2>(tuple1()) << std::endl;

    std::cout << "Tuple 2: ";
    std::cout << std::get<0>(tuple2()) << " ";
    std::cout << std::get<1>(tuple2()) << " ";
    std::cout << std::get<2>(tuple2()) << std::endl;

    std::cout << "Tuple 3: ";
    std::cout << std::get<0>(tuple3()) << " ";
    std::cout << std::get<1>(tuple3()) << " ";
    std::cout << std::get<2>(tuple3()) << std::endl;

    std::cout << "Tuple 4: ";
    std::cout << std::get<0>(tuple4()) << " ";
    std::cout << std::get<1>(tuple4()) << " ";
    std::cout << std::get<2>(tuple4()) << std::endl;
}
