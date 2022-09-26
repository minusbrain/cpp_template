#include <base/improve_containers.h>

#include <iostream>
#include <vector>

#include "lib.h"

int main() {
    std::vector<int> vec = get_vector(10);
    std::cout << vec << '\n';
    return 0;
}