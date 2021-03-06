#include <iostream>
#include "fixo.h"
#include <map>
#include <vector>

#define EXPLODE_PAIRS(p) pair{p.first-1,p.second},{p.first+1,p.second},{p.first,p.second-1},{p.first,p.second+1}
#define MAP_PAIR(p) p.second][p.first
//#define DEBUG

enum tiletype {
    WATER,
    LAND,
    FOOD
};
struct tile {
    tiletype type = WATER;
    bool viewed = false;
};
typedef std::pair<int, int> pair;
typedef std::map<pair, tile> map;

void search_island(pair start, map &map, int &max) {
    queue f;
    f.push(start);
    int island_max = 0;
    map[start].viewed = true;
    while (!f.empty()) {
        auto now = f.pop();

        if (map[now].type == FOOD) { ++island_max; }

        for (auto dir : {EXPLODE_PAIRS(now)}) {
            if (map.contains(dir) && !map[dir].viewed && map[dir].type != WATER) {
                f.push(dir);
                map[dir].viewed = true;
            }
        }
    }
    if (island_max > max) { max = island_max; }
}

void search_water(fixo &buffer, map &map, int &max) {
    auto now = buffer.pop();
    if (map[now].type == WATER) {
        for (auto dir : {EXPLODE_PAIRS(now)}) {
            if (map.contains(dir) && !map[dir].viewed) { // Contains = Not out of bounds
                buffer.push(dir);
                if (map[dir].type == WATER) { map[dir].viewed = true; }
            }
        }
    } else {
        search_island(now, map, max);
    }
}

int main() {
    map map;
    std::pair<int, int> start;
    int width, height;
    { // Import Map
        std::cin >> width >> height;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char c;
                std::cin >> c;
                switch (c) {
                    case 'J':
                        map[{x, y}] = {FOOD};
                        break;
                    case '#':
                        map[{x, y}] = {LAND};
                        break;
                    case 'H':
                        map[{x, y}] = {WATER};
                        start = {x, y};
                        break;
                    case '.':
                        map[{x, y}] = {WATER};
                        break;
                    default:
                        break;

                }
            }
        }

        stack f;
        int max = 0;
        f.push(start);
        while (!f.empty()) {
            search_water(f, map, max);
        }
        std::cout << max << std::endl;
        return 0;
    }
}
