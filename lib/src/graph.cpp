#include "graph.hpp"

#include <algorithm>

Graph::Graph(std::vector<std::vector<int>> data) {
  data_ = data;
  std::vector<Color> colors(data_.size(), Color::white);
  colors_ = colors;
  std::vector<int> parents(data_.size(), -1);
  parents_ = parents;
}

Graph::Graph(int V) {
  std::vector<std::vector<int>> data(V);
  data_ = data;
  std::vector<Color> colors(data_.size(), Color::white);
  colors_ = colors;
  std::vector<int> parents(data_.size(), -1);
  parents_ = parents;
}

void Graph::AddEdge(int u, int v) { data_[u].push_back(v); }

bool Graph::IsThereAWay(std::pair<int, int> pair) {
  if (pair.first == pair.second) return true;
  bool ans = false;
  InnerDFS(pair.first, pair.second);  // просчитываем пути
  if (parents_[pair.second] != -1)
    ans = true;  // если в целом до нее дошли и определили родителя, значит путь
                 // есть
  CleanColorsParents();
  return ans;
}

void Graph::InnerDFS(int u, int end) {
  if (u == end) return;  // дошли до того, что искали
  for (auto v : data_[u]) {
    if (parents_[v] == -1) {
      parents_[v] = u;
      InnerDFS(v, end);
    }
  }
}

void Graph::InnerDFS(int u, std::vector<int>& order) {
  colors_[u] = Color::grey;
  for (auto v : data_[u]) {
    if (colors_[v] == Color::grey) {
      throw CycleExistError();
    }
    if (colors_[v] == Color::white) {
      try {
        InnerDFS(v, order);
      } catch (const CycleExistError& e) {
        throw;
      }
    }
  }
  colors_[u] = Color::black;
  order.push_back(u);
}

void Graph::CleanColorsParents() {  // потому что каждый раз пересчитываем от
                                    // другой вершины, надо чистить
  std::vector<Color> colors(data_.size(), Color::white);
  colors_ = colors;
  std::vector<int> parents(data_.size(), -1);
  parents_ = parents;
}

std::vector<int> Graph::TopologySort() {
  std::vector<int> order;
  try {
    for (int i = 0; i < data_.size(); ++i) {
      if (colors_[i] == Color::white) {
        InnerDFS(i, order);
      }
    }
    CleanColorsParents();
    std::reverse(order.begin(), order.end());
    return order;
  } catch (const CycleExistError& e) {
    CleanColorsParents();
    throw;
  }
}