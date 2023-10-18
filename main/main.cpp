// Copyright 2022 Marina Usova

#include <iostream>
#include "../lib_example/example.h"

int main() {
  int a = 1, b = 4; 
  float result;
  bool success = false;

  try {
      result = division(a, b);
      success = true;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }
  if (success) { printf("%d / %d = %.2f\n", a, b, result); success = false; }

  a = 1; b = 0;

  try {
      result = division(a, b);
      success = true;
  } catch (std::exception err) {
	  std::cerr << err.what() << std::endl;
  }
  if (success) { printf("%d / %d = %.2f\n", a, b, result); success = false; }

  ExampleClass<int> obj(10);
  obj.setRandValues(-50, 30);
  std::cout << obj << std::endl;

  return 0;
}
