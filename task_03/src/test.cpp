#include <gtest/gtest.h>

#include <vector>

#include "graph.hpp"

TEST(GraphTest, EmptyGraph) {
  std::vector<std::vector<int>> data(0);
  Graph graph(data);
  std::vector<int> result = graph.TopologySort();
  ASSERT_TRUE(result.empty());
}

TEST(GraphTest, SingleVertex) {
  std::vector<std::vector<int>> data(1);
  Graph graph(data);
  std::vector<int> result = graph.TopologySort();
  ASSERT_EQ(result, std::vector<int>{0});
}

TEST(GraphTest, TwoVerticesNoEdges) {
  std::vector<std::vector<int>> data(2);
  Graph graph(data);
  std::vector<int> result = graph.TopologySort();
  ASSERT_EQ(result, std::vector<int>({1, 0}));
}

TEST(GraphTest, LinearGraph) {
  std::vector<std::vector<int>> data(3);
  Graph graph(data);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  std::vector<int> result = graph.TopologySort();
  ASSERT_EQ(result, std::vector<int>({0, 1, 2}));
}

TEST(GraphTest, DiamondGraph) {
  std::vector<std::vector<int>> data(4);
  Graph graph(data);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(2, 3);
  std::vector<int> result = graph.TopologySort();
  ASSERT_EQ(result, std::vector<int>({0, 2, 1, 3}));
}

TEST(GraphTest, SelfLoopThrows) {
  std::vector<std::vector<int>> data(2);
  Graph graph(data);
  graph.AddEdge(0, 0);
  ASSERT_THROW(graph.TopologySort(), Graph::CycleExistError);
}

TEST(GraphTest, CycleThrows) {
  std::vector<std::vector<int>> data(3);
  Graph graph(data);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 0);
  ASSERT_THROW(graph.TopologySort(), Graph::CycleExistError);
}

TEST(GraphTest, MultipleComponents) {
  std::vector<std::vector<int>> data(4);
  Graph graph(data);
  graph.AddEdge(0, 1);
  graph.AddEdge(2, 3);
  std::vector<int> result = graph.TopologySort();
  ASSERT_EQ(result, std::vector<int>({2, 3, 0, 1}));
}