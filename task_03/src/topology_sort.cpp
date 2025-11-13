#include "topology_sort.hpp"

#include <iostream>

void TopologySortFunction() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> data(n);
  Graph graph(data);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    if (u == v) {
      std::cout << "-1\n";
      return;
    }
    graph.AddEdge(u, v);
  }
  try {
    std::vector<int> order = graph.TopologySort();
    PrintVector(order);
  } catch (const Graph::CycleExistError& e) {
    std::cout << "-1\n";
    return;
  }
  return;
}
