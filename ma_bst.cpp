#include <iostream>
#include <memory>

template<typename K, typename T>
struct bs_map_node {
private:
    std::pair<K, T> value;
public:
    std::shared_ptr<bs_map_node<K, T>> left, right;

    K &get_key() { return value.first; }

    T &get_value() { return value.second; }

    explicit bs_map_node(std::pair<K, T> _pair) {
        value = _pair;
    }
    // Returns a value from provided key, if the key does not exist, it is created and instantiated to 0, then returned as normal
    T &operator[](K idx) {
        bs_map_node<T, K> *cursor = this;
        while (idx != cursor->get_key()) {
            if (idx < cursor->get_key()) {
                if (!cursor->left) {
                    cursor->left = std::make_shared<bs_map_node<K, T>>(bs_map_node<K, T>({idx, 0}));
                    return cursor->left->get_value();
                }
                cursor = cursor->left.get();
            } else if (idx > cursor->get_key()) {
                if (!cursor->right) {
                    cursor->right = std::make_shared<bs_map_node<K, T>>(bs_map_node<K, T>({idx, 0}));
                    return cursor->right->get_value();
                }
                cursor = cursor->right.get();
            }
        }
        return cursor->get_value();
    }

    bool key_exists(K key) {
        if (key == get_key()) return true;
        if (key < get_key()) {
            if (left) {
                return left->key_exists(key);
            } else return false;
        }
        if (key > get_key()) {
            if (right) {
                return right->key_exists(key);
            } else return false;
        }
    }

    void insert(std::pair<K, T> _pair) {
        if (_pair.first == get_key()) { return; }
        if (_pair.first < get_key()) {
            if (left) {
                left->insert(_pair);
            } else {
                left = std::make_shared<bs_map_node<K, T>>(_pair);
            }
        }
        if (_pair.first > get_key()) {
            if (right) {
                right->insert(_pair);
            } else {
                right = std::make_shared<bs_map_node<K, T>>(_pair);
            }
        }
    }

    void insert(std::shared_ptr<bs_map_node<K, T>> _node) {
        if (_node->get_key() == get_key()) { return; }
        if (_node->get_key() < get_key()) {
            if (left) {
                left->insert(_node);
            } else {
                left = _node;
            }
        }
        if (_node->get_key() > get_key()) {
            if (right) {
                right->insert(_node);
            } else {
                right = _node;
            }
        }
    }

    /// Removes a Node by Key and preserves its children.
    void remove(T target) {
        auto cursor = this;
        while (cursor->left || cursor->right) {
            if (cursor->left && cursor->left->get_key() == target) {
                auto left_carry = cursor->left->left;
                auto right_carry = cursor->left->right;
                cursor->left = nullptr;
                if (left_carry) { insert(left_carry); }
                if (right_carry) { insert(right_carry); }
                return;
            }
            if (cursor->right && cursor->right->get_key() == target) {
                auto left_carry = cursor->right->left;
                auto right_carry = cursor->right->right;
                cursor->right = nullptr;
                if (left_carry) { insert(left_carry); }
                if (right_carry) { insert(right_carry); }
                return;
            }

            if (cursor->get_key() < target && cursor->left) {
                cursor = cursor->left.get();
            } else if (cursor->get_key() > target && cursor->right) {
                cursor = cursor->right.get();
            } else { return; }
        }
    }
};

std::string print_int_node(bs_map_node<int, int> &_node) {
    return
            (_node.left ? print_int_node(*_node.left) + "\n" : "") +
            std::to_string(_node.get_key()) + " " + std::to_string(_node.get_value()) +
            (_node.right ? "\n" + print_int_node(*_node.right) : "");
}

int main() {
    bs_map_node<int, int> root{std::pair<int, int>(5, 1)};
    root[20] = 3;
    root[8] = 13;
    root[4156] = 43;
    root.remove(8);
    root.remove(20);
    /*int in;
    std::cin >> in;
    bs_map_node<int, int> root{std::pair<int, int>(in, 1)};

    while (std::cin >> in) {
            root[in]++;
    }
    std::cout << print_int_node(root) << std::endl;*/
}
