#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <sstream>

#define DEBUG

struct ms_node {
    std::vector<ms_node *> neighbours;
    bool marked = false, observed = false;

    void mark_refs() {
        for (auto *node : neighbours) {
            if (!node->marked) {
                node->marked = true;
                node->mark_refs();
            }
        }
    }
};

int main() {
    std::vector<ms_node> nodes;
    { // Initialize NodeList
        int node_num;
        std::cin >> node_num;
        nodes.resize(node_num);
    }
    { // Mark Observers
        int observer_count;
        std::cin >> observer_count;
        for (int i = 0; i < observer_count; ++i) {
            int x;
            std::cin >> x;
            nodes[x].observed = true;
        }
    }
    { // Create connections
        int x, y;
        while (std::cin >> x >> y) {
            nodes[x].neighbours.emplace_back(&nodes[y]);
        }
    }

    for (auto &node : nodes) {
        if (node.observed) {
            node.marked = true;
            node.mark_refs();
        }
    } // Mark observers and connected nodes

    std::vector<int> garbage; // Find unmarked Nodes
    for (int i = 0; i < nodes.size(); ++i) if (!nodes[i].marked) { garbage.emplace_back(i); }

    for (int i : garbage) { std::cout << i << "\n"; }
    std::cout << std::endl;

    /*std::ostringstream os;

    if (!garbage.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(garbage.begin(), garbage.end()-1,
                  std::ostream_iterator<int>(os, "\n"));

        // Now add the last element with no delimiter
        os << garbage.back();
    }*/

    /*std::cout << os.str() << std::endl;
    for (int i = 0; i < nodes.size(); ++i) {
        std::cout << "{ " << i << ", O:" << nodes[i].observed << ", M:" << nodes[i].marked << " }" << std::endl;
    }*/
}