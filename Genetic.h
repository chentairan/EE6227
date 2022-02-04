#ifndef GENETIC_H_
#define GENETIC_H_

#include <vector>

class Genetic {
 public:
  Genetic(int n, int population_size);
  std::vector<int> solveGA();

 private:
  std::vector<int> createGnome();
  void initializeFirstGeneration();
  bool isGoalGnome(const std::vector<int> &gnome);
  int fitness(const std::vector<int> &gnome);
  void crossOverAndMutant();
  void crossOverGnomes(std::vector<int> &firstGnome, std::vector<int> &secondGnome);
  void MutantGnome(std::vector<int> &gnome);
  std::vector<std::vector<int>> makeSelection();
  int randomNum(int start, int end);

 private:
  std::vector<std::vector<int>> population_;
  int numOfQueen_;
  int numOfPopulation_;
  std::vector<int> solution_;
  int solutionIndex_ = -1;
};

#endif // GENETIC_H_
