#include <iostream>
#include "fixo.h"
#include <map>
#include <vector>
#include <stdlib.h>

enum tiletype {
    WATER,
    LAND,
    FOOD,
    PASSED
};
typedef std::map<std::pair<int, int>, tiletype> map;

void lookaround(fixo &buffer, map &map, std::vector<std::pair<int, int>> &processed, int width, int height) {
    auto now = buffer.pop();
    std::pair<int, int> check = {now.first - 1, now.second};
    if (now.first > 0 &&
        !(map[now] == LAND && !map.contains(check)) &&
        std::find(processed.begin(), processed.end(), check) == processed.end()) {
        buffer.push(check);
        processed.push_back(check);
    }
    check = {now.first, now.second - 1};
    if (now.second > 0 && !(map[now] == LAND && !map.contains(check)) &&
        std::find(processed.begin(), processed.end(), check) == processed.end()) {
        buffer.push(check);
        processed.push_back(check);
    }
    check = {now.first + 1, now.second};
    if (now.first < width && !(map[now] == LAND && !map.contains(check)) &&
        std::find(processed.begin(), processed.end(), check) == processed.end()) {
        buffer.push(check);
        processed.push_back(check);
    }
    check = {now.first, now.second + 1};
    if (now.second < height && !(map[now] == LAND && !map.contains(check)) &&
        std::find(processed.begin(), processed.end(), check) == processed.end()) {
        buffer.push(check);
        processed.push_back(check);
    }
}

void printmap(map &map, std::vector<std::pair<int, int>> &processed, int width, int height) {
    std::map<tiletype, char> tilesym = {{PASSED, '@'},
                                        {LAND,   '#'},
                                        {FOOD,   'F'}};
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << (std::find(processed.begin(), processed.end(), std::pair<int, int>{x, y}) != processed.end()
                          ? '@' : (map.contains({x, y}) ? tilesym[map[{x, y}]] : ' '));
        }
        std::cout << std::endl;
    }
}

int main() {
    map map;
    std::pair<int, int> start;
    std::pair<int, int> now;
    std::vector<std::pair<int, int>> processed;
    int width, height;
    { // Import Map
        std::cin >> width >> height;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char c;
                std::cin >> c;
                switch (c) {
                    case 'J':
                        map[{x, y}] = FOOD;
                        break;
                    case '#':
                        map[{x, y}] = LAND;
                        break;
                    case 'H':
                        start = {x, y};
                        break;
                    default:
                        break;

                }
            }
        }
        now = start;

        stack f;
        f.push(start);
        for (int i = 0; i < 100; ++i) {
            auto n = f.pop();
            std::cout << std::endl << i << "[ " << n.first << ", " << n.second << " ]" << std::endl;
            f.push(n);
            lookaround(f, map, processed, width, height);
            printmap(map, processed, width, height);
        }


        return 0;
    }
}