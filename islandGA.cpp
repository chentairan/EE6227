#include <iostream>
#include "Genetic.h"
#include <chrono>
#include <vector>

int main() {
  int n, island, interval;
  std::cout << "Input number of queens: ";
  std::cin >> n;
  std::cout << "Input number of island: ";
  std::cin >> island;
  std::cout << "Input number of interval generation in which migration occurs: ";
  std::cin >> interval;

  std::vector<Genetic *> solvers;
  std::vector<bool> solver_status = std::vector<bool>(island, false);
  for (int i = 0; i < island; ++i) {
    solvers.push_back(new Genetic(n, 100, 25));
  }
  std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
  int numOfGeneration = 0;
  std::vector<std::vector<int>> solutions;
  while (true) {
    numOfGeneration++;
    std::vector<std::vector<int>> migration;
    if (solutions.size() == island) {
      break;
    }
    for (int i = 0; i < island; ++i) {
      if (not solver_status[i]) {
        solver_status[i] = solvers[i]->oneStep();
        if (solver_status[i]) {
          std::cout << "island " << i << " solved" << std::endl;
          solutions.push_back(solvers[i]->getSolution());
        }
        if (numOfGeneration % interval == 0 && island - solutions.size() > 1) {
          if (not migration.empty()) {
            solvers[i]->setNewGnome(migration);
          }
          migration = solvers[i]->randomGetGnome();
        }
      }
    }
  }
  std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

  std::cout << "Solving time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
  if (solutions.empty()) {
    std::cout << "\nError\n";
  } else {
    std::cout << "\nSolutions: \n";
  }
  for (int i = 0; i < solutions.size(); ++i) {
    std::cout << "island " << i << ": ";
    for (const auto &iter: solutions[i]) {
      std::cout << iter << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  return 0;
}
