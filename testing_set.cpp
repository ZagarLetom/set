#include <gtest/gtest.h>

#include "s21_set.h"

TEST(Constructor, def_const) {
  s21::set<int> set1({1, 2, 3, 4, 5});
  s21::set<int> set2 = set1;
  s21::set<int> set3(std::move(set1));
  s21::set<int> set4;
  set4 = std::move(set3);
}
TEST(Methods_SET, insert) {
  s21::set<int> set1({1, 2, 3, 4, 5});
  set1.insert(7);
  set1.insert(7);
  set1.insert(0);
  set1.insert(10);
  set1.insert(9);

  for (auto it = set1.begin(); it != set1.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  auto it = set1.begin();
  EXPECT_EQ(0, *it);
  ++it;
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(4, *it);
  ++it;
  EXPECT_EQ(5, *it);
  ++it;
  EXPECT_EQ(7, *it);
  ++it;
  EXPECT_EQ(9, *it);
  ++it;
  EXPECT_EQ(10, *it);
  ++it;
  EXPECT_EQ(it, set1.end());
}

TEST(Methods_SET, empty_size_max) {
  s21::set<int> set1({1, 2, 3});
  EXPECT_EQ(0, set1.empty());
  EXPECT_EQ(3, set1.size());
  std::cout << "max size is " << set1.max_size() << std::endl;
}

TEST(Methods_SET, erase) {
  s21::set<int> set1({1, 2, 3});
  set1.erase(set1.find(0));
  set1.erase(set1.find(52));
  set1.erase(set1.find(2));
  set1.erase(set1.find(2));

  EXPECT_EQ(2, set1.size());
  auto it = set1.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(3, *it);

  set1.insert(1);
  set1.insert(2);
  set1.insert(3);
  set1.insert(4);
  set1.insert(5);
  set1.erase(set1.find(5));
  set1.erase(set1.find(1));
  set1.erase(set1.find(3));
  set1.erase(set1.find(1));
  set1.erase(set1.find(2));
  set1.erase(set1.find(4));
  set1.insert(5);
}

TEST(Methods_SET, merge) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2({2, 3, 4, 5, 0});
  set1.merge(set2);
  EXPECT_EQ(6, set1.size());
  auto it = set1.begin();
  EXPECT_EQ(0, *it);
  ++it;
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(4, *it);
  ++it;
  EXPECT_EQ(5, *it);
}

TEST(Methods_SET, contains) {
  s21::set<int> set1({1, 2, 3});
  EXPECT_EQ(1, set1.contains(1));
  EXPECT_EQ(1, set1.contains(3));
  EXPECT_EQ(0, set1.contains(0));
  EXPECT_EQ(0, set1.contains(12));
}

TEST(Methods_SET, swap) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2({4, 5, 6, 8});
  set1.swap(set2);
  auto it = set1.begin();
  EXPECT_EQ(4, *it);
}

TEST(Iterators, iter_Methods_SET) {
  s21::set<int> set1({1, 2, 3});
  auto it = set1.begin();
  ++it;
  --it;
  ++it;
  std::cout << *it << std::endl;
  auto it2 = set1.begin();
  EXPECT_EQ(0, it == it2);
  EXPECT_EQ(1, it != it2);
}

TEST(Methods_SET, insert_many) {
  s21::set<int> set1({1, 2, 3});
  set1.insert_many(1, 2, 3, 4, 5, 0);
  for (auto i = set1.begin(); i != set1.end(); ++i) {
    std::cout << *i << " ";
  }
  std::cout << std::endl;
}
