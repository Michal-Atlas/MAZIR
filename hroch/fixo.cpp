#include "fixo.h"

std::pair<int, int> fixo::pop() {
    auto first = data;
    data = data->next;
    return first->value;
}

void queue::push(std::pair<int, int> value) {
    if (!data) { // Push to empty
        data = std::make_shared<node>(node{value});
        return;
    }
    if (last == nullptr) { // Initialize on first run
        last = this->data;
        while (last->next) {
            last = last->next;
        }
    }
    last->next = std::make_shared<node>(node{value});
    last = last->next;

}

void stack::push(std::pair<int, int> value) {
    auto n = std::make_shared<node>(node{value});
    auto first = this->data;
    this->data = n;
    this->data->next = first;
}
