#ifndef S21_set_H
#define S21_set_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type data;
    Node* left;
    Node* right;

    explicit Node(const value_type& data)
        : data(data), left(nullptr), right(nullptr) {}
  };

  Node* root;
  size_type nodeCount;

  Node* insertNode(Node* node, const value_type& value, bool& inserted);
  void handleRightNode(Node* node, const key_type& key, bool& removed);
  void removeNode(Node* node, const key_type& key, bool& removed);
  void clearNode(Node* node);

 public:
  class iterator;
  class const_iterator;

  // Member functions

  set();
  explicit set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s) noexcept;
  ~set();
  set& operator=(set&& s) noexcept;

  // Iterators

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Capacity

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  template <typename... Args>
  void insert_many(Args&&... args);

  // Lookup

  iterator find(const key_type& key);
  bool contains(const key_type& key);

  class iterator {
   public:
    Node* current;

   public:
    explicit iterator(Node* node);
    reference operator*() const;
    iterator& operator++();
    iterator& operator--();
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
  };

  class const_iterator {
    const Node* current;

   public:
    explicit const_iterator(const Node* node);
    const_reference operator*() const;
    const_iterator& operator++();
    const_iterator& operator--();
    bool operator!=(const const_iterator& other) const;
  };
};

template <typename Key>
set<Key>::set() : root(nullptr), nodeCount(0) {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) : set() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key>::set(const set& s) : set() {
  for (const auto& item : s) {
    insert(item);
  }
}

template <typename Key>
set<Key>::set(set&& s) noexcept : root(s.root), nodeCount(s.nodeCount) {
  s.root = nullptr;
  s.nodeCount = 0;
}

template <typename Key>
set<Key>::~set() {
  clear();
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) noexcept {
  if (this != &s) {
    clear();
    root = s.root;
    nodeCount = s.nodeCount;
    s.root = nullptr;
    s.nodeCount = 0;
  }
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  iterator it(root);
  return it;
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return iterator(nullptr);
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const {
  const_iterator it(root);
  return it;
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const {
  return const_iterator(nullptr);
}

template <typename Key>
bool set<Key>::empty() const noexcept {
  return nodeCount == 0;
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const noexcept {
  return nodeCount;
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
}

template <typename Key>
void set<Key>::clear() noexcept {
  clearNode(root);
  root = nullptr;
  nodeCount = 0;
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  bool inserted = false;
  root = insertNode(root, value, inserted);
  if (inserted) {
    ++nodeCount;
  }
  return {find(value), inserted};
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (pos != end()) {
    bool removed = false;
    removeNode(root, *pos, removed);
    if (removed) {
      --nodeCount;
    }
  }
}

template <typename Key>
void set<Key>::merge(set& other) {
  for (const auto& item : other) {
    insert(item);
  }
  other.clear();
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const key_type& key) {
  Node* current = root;
  while (current) {
    if (key > current->data) {
      current = current->right;
    } else if (key == current->data) {
      return iterator(current);
    } else {
      return end();
    }
  }
  return end();
}

template <typename Key>
bool set<Key>::contains(const key_type& key) {
  return find(key) != end();
}

template <typename Key>
typename set<Key>::Node* set<Key>::insertNode(Node* node,
                                              const value_type& value,
                                              bool& inserted) {
  if (!node) {
    inserted = true;
    return new Node(value);
  }
  if (value < node->data) {
    if (!node->left) {
      inserted = true;
      node->left = new Node(value);
      node->left->right = node;
      return node->left;
    }
  } else if (value > node->data) {
    if (!node->right) {
      inserted = true;
      node->right = new Node(value);
      node->right->left = node;
    } else if (value < node->right->data) {
      inserted = true;
      Node* temp = node->right;
      node->right = new Node(value);
      node->right->left = node;
      node->right->right = temp;
      node->right->right->left = node->right;
    } else {
      node->right = insertNode(node->right, value, inserted);
    }
  }

  return node;
}

template <typename Key>
void set<Key>::handleRightNode(Node* node, const key_type& key, bool& removed) {
  if (node->right) {
    if (key > node->right->data) {
      removeNode(node->right, key, removed);
    } else {
      if (key == node->right->data) {
        if (node->right->right) {
          Node* temp = node->right;
          node->right = node->right->right;
          temp->right = nullptr;
          delete temp;
        } else {
          Node* temp = node->right;
          node->right = nullptr;
          delete temp;
        }
        removed = true;
      }
    }
  }
}

template <typename Key>
void set<Key>::removeNode(Node* node, const key_type& key, bool& removed) {
  if (node->data == key) {
    if (node->right) {
      root = node->right;
    } else {
      root = nullptr;
    }
    delete node;
    removed = true;
  } else {
    handleRightNode(node, key, removed);
  }
}

template <typename Key>
void set<Key>::clearNode(Node* node) {
  if (node) {
    clearNode(node->right);
    delete node;
  }
}

template <typename Key>
void set<Key>::swap(set& other) {
  std::swap(root, other.root);
  std::swap(nodeCount, other.nodeCount);
}

template <typename Key>
template <typename... Args>
void set<Key>::insert_many(Args&&... args) {
  (insert(std::forward<Args>(args)), ...);
}

template <typename Key>
set<Key>::iterator::iterator(Node* node) : current(node) {}

template <typename Key>
typename set<Key>::reference set<Key>::iterator::operator*() const {
  return current->data;
}

template <typename Key>
typename set<Key>::iterator& set<Key>::iterator::operator++() {
  current = current->right;
  return *this;
}

template <typename Key>
typename set<Key>::iterator& set<Key>::iterator::operator--() {
  current = current->left;
  return *this;
}

template <typename Key>
bool set<Key>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename Key>
bool set<Key>::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

template <typename Key>
set<Key>::const_iterator::const_iterator(const Node* node) : current(node) {}

template <typename Key>
typename set<Key>::const_reference set<Key>::const_iterator::operator*() const {
  return current->data;
}

template <typename Key>
typename set<Key>::const_iterator& set<Key>::const_iterator::operator++() {
  current = current->right;
  return *this;
}

template <typename Key>
bool set<Key>::const_iterator::operator!=(const const_iterator& other) const {
  return current != other.current;
}
}  // namespace s21
#endif  // S21_set_H
