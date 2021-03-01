#ifndef HIPPO_FIXO_H
#define HIPPO_FIXO_H

#include <memory>

struct node {
    std::pair<int, int> value;
    std::shared_ptr<node> next;
};

struct fixo {
protected:
    std::shared_ptr<node> data;
public:
    std::pair<int, int> pop();

    bool empty() { return data == nullptr; }

    virtual void push(std::pair<int, int> value) = 0;
};

struct stack : public fixo {
    void push(std::pair<int, int> value) override;
};

struct queue : public fixo {
private:
    std::shared_ptr<node> last;
public:
    void push(std::pair<int, int> value) override;
};

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

#endif //HIPPO_FIXO_H
