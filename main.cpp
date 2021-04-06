#include <iostream>
#include "add.h"
#include "div2.h"

int main(void) {
  std::cout << "Hello world \n";

  std::cout << "1 + 2 = " << add(1, 2) << "\n";
  std::cout << "10 / 5 = " << div2(10.0, 5.0) << "\n";

  return 0;
}

