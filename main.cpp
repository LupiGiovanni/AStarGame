#include <iostream>
#include "GlobalMap.h"
#include "GameCharacter.h"
#include "SearchState.h"

bool displayPath (const GlobalMap& map, int width, int height, const std::vector<SearchState>& path) {
    if (path.empty())
        return false;

    SearchState start = path.front();
    SearchState goal = path.back();

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

}