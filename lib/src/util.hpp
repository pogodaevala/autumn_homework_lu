#include <iostream>
#include <vector>

template <typename T>
void PrintVector(const std::vector<T>& input_data) {
  for (auto elem : input_data) {
    std::cout << elem << " ";
  }
}

template <typename T>
void PrintVector(const std::vector<std::vector<T>>& input_data) {
  for (auto vec : input_data) {
    PrintVector(vec);
    std::cout << "\n";
  }
}

