#include <iostream>
#include "Genetic.h"
#include <chrono>

int main() {
  int n;
  std::cout << "Input number of queens: ";
  std::cin >> n;
  Genetic genetic(n, 100);

  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  auto solution = genetic.solveGA();
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

  std::cout << "Solving time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
  if (solution.empty()) {
    std::cout << "\nError\n";
  } else {
    std::cout << "\nSolution: \n";
  }
  for (const auto &iter: solution) {
    std::cout << iter << " ";
  }
  std::cout << "\n";
  return 0;
}
