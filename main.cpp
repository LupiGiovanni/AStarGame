#include <iostream>
#include <memory>
#include "GlobalMap.h"
#include "GameCharacter.h"
#include "SearchState.h"

bool displayPath (const GlobalMap& map, int width, int height, const std::vector<SearchState>& path) {
    if (path.empty())
        return false;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            bool isPath = false;

            for (auto it = path.begin(); it != path.end(); ++it) {
                if (it->getX() == x && it->getY() == y) {
                    if (it == path.begin()) {
                        std::cout << "S  ";
                    } else if (it == path.end() - 1) {
                        std::cout << "G  ";
                    } else {
                        std::cout << "+  ";
                    }
                    isPath = true;
                    break;
                }
            }

            if (!isPath) {
                if (map.getValue(x ,y) == 9)
                    std::cout << "#  ";
                else if (map.getValue(x, y) < 9)
                    std::cout << ".  ";
            }

        }
        std::cout << std::endl;
    }
    return true;
}

int main() {
    int map_width = 20;
    int map_height = 20;
    int map_values[] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,
        1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,
        1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,
        1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,
        1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,
        1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,
        1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,
        1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,
        1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,
        1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,
        1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,
        1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,
        1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,
        1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,
        1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,
        1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,
        1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,
        1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };

    GlobalMap& map = GlobalMap::getInstance();
    map.initialize(20, 20, map_values);
    GameCharacter character (0, 0);
    SearchState goal (19, 19);

    std::vector<SearchState> path;
    path = character.reachGoal(goal);
    displayPath(map, map_width, map_height, path);
    for (auto state : path)
        state.printStateInfo();
    return 0;
}