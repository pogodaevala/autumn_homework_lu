#include <exception>
#include <utility>
#include <vector>

class Graph {
 public:
  // Graph();
  Graph(std::vector<std::vector<int>> data);  // список связности
  Graph(int V);
  //~Graph();
  void AddEdge(int u, int v);
  std::vector<int> TopologySort();
  bool IsThereAWay(std::pair<int, int> pair);
  class CycleExistError : public std::exception {};

 private:
  enum class Color { white = 0, grey = 1, black = 2 };
  std::vector<std::vector<int>> data_;
  std::vector<Color> colors_;
  std::vector<int> parents_;
  void CleanColorsParents();
  void InnerDFS(int u, int end = -1);
  void InnerDFS(int u, std::vector<int>& order);
};