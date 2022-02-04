#include "Genetic.h"

#include <iostream>
#include <algorithm>
#include <random>

Genetic::Genetic(int n, int population_size) {
  numOfQueen_ = n;
  numOfPopulation_ = population_size;
}

std::vector<int> Genetic::solveGA() {
  initializeFirstGeneration();
  for (const auto &iter: population_) {
    if (isGoalGnome(iter)) {
      return iter;
    }
  }
  int count = 0;
  while (true) {
    crossOverAndMutant();
    population_ = makeSelection();
    count++;
    if (solutionIndex_ >= 0) {
      std::cout << "Iteration: " << count << std::endl;
      return solution_;
    }
  }
}

std::vector<int> Genetic::createGnome() {
  std::vector<int> new_gnome;
  new_gnome.reserve(numOfQueen_);
  for (int i = 0; i < numOfQueen_; ++i) {
    new_gnome.push_back(i);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(new_gnome.begin(), new_gnome.end(), std::default_random_engine(seed));

  while (std::find(population_.begin(), population_.end(), new_gnome) != population_.end()) {
    std::shuffle(new_gnome.begin(), new_gnome.end(), std::default_random_engine(seed));
  }

  return new_gnome;
}

void Genetic::initializeFirstGeneration() {
  for (int i = 0; i < numOfPopulation_; ++i) {
    population_.push_back(createGnome());
  }
}

bool Genetic::isGoalGnome(const std::vector<int> &gnome) {
  return fitness(gnome) == 0;
}

int Genetic::fitness(const std::vector<int> &gnome) {
  int conflict = 0;
  for (int i = 0; i < numOfQueen_; ++i) {
    for (int j = i + 1; j < numOfQueen_; ++j) {
      if (gnome[i] == gnome[j] || abs(gnome[i] - gnome[j]) == j - i)
        conflict++;
    }
  }
  return conflict;
}

void Genetic::crossOverAndMutant() {
  for (int i = 1; i < numOfPopulation_; i += 2) {
    auto firstGnome = population_[i - 1];
    auto secondGnome = population_[i];
    crossOverGnomes(firstGnome, secondGnome);
    MutantGnome(firstGnome);
    MutantGnome(secondGnome);
    population_.push_back(firstGnome);
    population_.push_back(secondGnome);
  }
}

void Genetic::crossOverGnomes(std::vector<int> &firstGnome, std::vector<int> &secondGnome) {
  int tmp;
  for (int i = 1; i < numOfQueen_; ++i) {
    if (std::abs(firstGnome[i - 1] - firstGnome[i]) < 2) {
      tmp = firstGnome[i];
      firstGnome[i] = secondGnome[i];
      secondGnome[i] = tmp;
    }

    if (std::abs(secondGnome[i - 1] - secondGnome[i]) < 2) {
      tmp = firstGnome[i];
      firstGnome[i] = secondGnome[i];
      secondGnome[i] = tmp;
    }
  }
}

void Genetic::MutantGnome(std::vector<int> &gnome) {
  int bound = numOfQueen_ / 2;
  int leftSideIndex = randomNum(0, bound);
  int rightSideIndex = randomNum(bound + 1, numOfQueen_ - 1);
  std::vector<int> newGnome;
  for (const auto &iter: gnome) {
    if (std::find(newGnome.begin(), newGnome.end(), iter) == newGnome.end()) {
      newGnome.push_back(iter);
    }
  }

  for (int i = 0; i < numOfQueen_; ++i) {
    if (std::find(newGnome.begin(), newGnome.end(), i) == newGnome.end()) {
      newGnome.push_back(i);
    }
  }

  gnome = newGnome;
  std::swap(gnome[leftSideIndex], gnome[rightSideIndex]);
}

std::vector<std::vector<int>> Genetic::makeSelection() {
  std::vector<int> score;
  std::vector<std::vector<int>> new_population;

  for (const auto &iter: population_) {
    score.push_back(fitness(iter));
  }

  auto miniIterator = std::min_element(score.begin(), score.end());
  if (*miniIterator == 0) {
    solutionIndex_ = std::distance(score.begin(), miniIterator);
    solution_ = population_[solutionIndex_];
    return population_;
  }

  while (new_population.size() < numOfPopulation_) {
    auto mini = std::min_element(score.begin(), score.end());
    auto mini_index = std::distance(score.begin(), mini);
    new_population.push_back(population_[mini_index]);
    score.erase(score.begin() + mini_index);
    population_.erase(population_.begin() + mini_index);
  }
  return new_population;
}

int Genetic::randomNum(int start, int end) {
  int range = (end - start) + 1;
  int random_int = start + (rand() % range);
  return random_int;
}
