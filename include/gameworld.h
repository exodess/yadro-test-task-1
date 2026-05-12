#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "dungeon.h"

// Главный класс игры, представляющий из себя игровой мир
// Хранит в себе информацию о пещерах и игровом персонаже, который по этим пещерам перемещается

// Связи между пещерами представлены в виде двунаправленного графа,
// в узлах которого находится объект класса Dungeon, хранящий информацию о конкретной пещере


class GameWorld {
private:
    std::vector<Dungeon> dungeons_network_;
    Person person_;

public:
    // Чтение мира из файла
    void LoadWorld(std::string path) noexcept;
};

#endif