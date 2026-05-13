#ifndef DUNGEON_H
#define DUNGEON_H

#include "room.h"
#include "person.h"
#include <vector>
#include <set>

/*
Структура, который хранит в себе информацию о каждой комнате

Схема подземелья раскрывается по следующей логике:
1. Комнаты, в которые заходил персонаж, считаются посещёнными. В посещённых комнатах персонажу известны ресурсы, а также проходы в смежные комнаты.
2. Комнаты, смежные с посещёнными, считаются видимыми. В видимой комнате неизвестны ресурсы, но видны проходы в смежные с ней комнаты.
3. В комнатах, смежных с видимыми, известен только номер.
*/
struct RoomInfo {
    num id_;
    std::vector<num> adjacent_rooms_;
    Resources resources_;

    // Обычная комната
    explicit RoomInfo(num id) noexcept : id_(id) {}

    // Видимая комната
    RoomInfo(num id, const std::vector<num>& adj) noexcept : id_(id), adjacent_rooms_(adj) {}

    // Посещенная комната
    RoomInfo(num id, const std::vector<num> adj, const Resources& res) noexcept
    : id_(id), adjacent_rooms_(adj), resources_(res) {}
};

// Главный класс игры, представляющий из себя игровой мир
// Хранит в себе информацию о пещерах и игровом персонаже, который по этим пещерам перемещается

// Связи между пещерами представлены в виде двунаправленного графа,
// в узлах которого находится объект класса Room, хранящий информацию о конкретной пещере

// Сам граф представлен в пямяти следующим образом:
// При считывании комнат подземелья, сохраняем их в отдельный список rooms_list_
// Их смежности между друг другом сохраняем в список смежности adjacency_list_,
// который представляет собой список пар индексов вершин (комнат), которые хранятся в rooms_list_

class Dungeon {
private:
    std::vector<Room> rooms_list_;
    std::vector<std::pair<num, num>> adjacency_list_;
    std::set<num> visits_;
    Person person_;
    Resources resources_ = Resources(DEFAULT_IRON_COST, DEFAULT_GOLD_COST, DEFAULT_GEMS_COST, DEFAULT_EXP_COST);

public:
    Dungeon() noexcept;
    // Чтение мира из файла
    void loadDungeon(std::string path);

    const Room& getRoom(num room_index) const;
    std::vector<num> getAdjacencyList(num room_index) const noexcept; // получаем список соседних комнат, в которые персонаж может попасть
    RoomInfo getRoomInfo(num room_index) const noexcept;

    // Метод для получения информации о стоимости конкретного ресурса
    num getCost(const std::string& resource_name) noexcept;
};

#endif