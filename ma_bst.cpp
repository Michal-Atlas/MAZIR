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
};

std::string print_int_node(bs_map_node<int, int> &_node) {
    return
            (_node.left ? print_int_node(*_node.left) + "\n" : "") +
            std::to_string(_node.get_key()) + " " + std::to_string(_node.get_value()) +
            (_node.right ? "\n" + print_int_node(*_node.right) : "");
}

int main() {
    int in;
    std::cin >> in;
    bs_map_node<int, int> root{std::pair<int, int>(in, 1)};

    while (std::cin >> in) {
        if (root.key_exists(in)) {
            root[in]++;
        } else {
            root.insert({in, 1});
        }
    }
    std::cout << print_int_node(root) << std::endl;
}
