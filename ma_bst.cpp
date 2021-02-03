#include <iostream>
#include <memory>

template<typename K, typename T>
struct bs_node {
private:
    std::pair<K, T> value;
public:
    std::shared_ptr<bs_node<K, T>> left, right;

    K &get_key() { return value.first; }

    T &get_value() { return value.second; }

    explicit bs_node(std::pair<K, T> _pair) {
        value = _pair;
    }

    T &operator[](K idx) {
        bs_node<T, K> *cursor = this;
        while (idx != cursor->get_key()) {
            if (idx < cursor->get_key()) {
                if (!left) { return value.second; }
                cursor = left.get();
            }
            if (idx > cursor->get_key()) {
                if (!right) { return value.second; }
                cursor = right.get();
            }
        }
        return get_value();
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
                left = std::make_shared<bs_node<K, T>>(_pair);
            }
        }
        if (_pair.first > get_key()) {
            if (right) {
                right->insert(_pair);
            } else {
                right = std::make_shared<bs_node<K, T>>(_pair);
            }
        }
    }
};

int main() {
    bs_node<int, int> root{std::pair<int, int>(0, 42)};
    root.insert({5, 5});
    std::cout << (root[5]) << (root[0]) << (root.key_exists(5) ? "1" : "0") << std::endl;
}
