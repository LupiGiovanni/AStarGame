//
// Created by gionimbus on 7/20/25.
//

#ifndef GLOBALMAP_H
#define GLOBALMAP_H


class GlobalMap {
public:
    GlobalMap(int width, int height);
    GlobalMap(int width, int height, const int* values);
    ~GlobalMap();
    int getValue (int x, int y) const;

private:
    int width;
    int height;
    int* values; //Map values can be 1 (reachable terrain) or 9 (unreachable terrain)
};


#endif //GLOBALMAP_H
