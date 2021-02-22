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

#endif //HIPPO_FIXO_H
