#include <iostream>
#include "Serializer.hpp"

int main() {
    Data data;
    data.value = 42;

    std::cout << &data << std::endl;
    std::cout << data.value << std::endl;

    uintptr_t raw = Serializer::serialize(&data);
    std::cout << raw << std::endl;

    Data* deserializedData = Serializer::deserialize(raw);
    std::cout << deserializedData << std::endl;
    std::cout << deserializedData->value << std::endl;
    return 0;
}
