#include <iostream>
#include "Genetic.h"
#include <chrono>
#include <fstream>

int main() {
  std::ofstream outfile;
  outfile.open("result.txt", std::ios::out | std::ios::trunc );
  outfile << "Number of Queens | " << "Calculation time (s) | " << "Result\n";
  for (int i = 4; i <= 50; ++i) {
    Genetic genetic(i, 100);
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    auto solution = genetic.solveGA();
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double time_cost = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();

    outfile << i << "\t" << std::setprecision(6) << time_cost << "\t" << "[";
    for (const auto & iter : solution) {
      outfile << iter << ", ";
    }
    outfile << "]\n";
  }
  outfile.close();
  return 0;
}
