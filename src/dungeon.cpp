#include "dungeon.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <charconv>

Dungeon::Dungeon() noexcept : person_(Person()) {}

void Dungeon::loadDungeon(std::string path) {
    std::ifstream settings_file;
    std::string line;
    std::stringstream ss;
    std::string member_line;
    num N = 0;

    settings_file.open(path);

    // Проверяем, существует ли файл и может ли программа его открыть
    if (!settings_file.is_open()) {
        throw std::runtime_error("Could not open settings file");
    }

    // В первой строке должно быть одно число N - количество комнат в подземелье (не считая начальную)
    std::getline(settings_file, line);
    ss = std::stringstream(line);

    ss >> member_line;
    if (member_line != line) {
        std::cout << line;
        return;
    }

    std::from_chars(member_line.data(), member_line.data() + member_line.size(), N);

    // Считываем N+1 строк с информацией о каждой комнате
    // Формат строки: <номер_вершины> <список_смежных_вершин> <iron> <gold> <gems> <exp>
    for (auto i = 0; i <= N; i++) {
        Resources resources;
        num vertex_id;
        num vertex_list;

        std::getline(settings_file, line);
        ss = std::stringstream(line);

        // Первый параметр - номер вершины
        if (ss >> member_line) {
            std::from_chars(member_line.data(), member_line.data() + member_line.size(), vertex_id);
        }

        // Второй параметр - список смежных вершин
        if (ss >> member_line) {
            std::from_chars(member_line.data(), member_line.data() + member_line.size(), vertex_list);
        }

        std::vector<num> resources_cost;
        resources_cost.reserve(4);
        for (auto j = 0; j < 4; j++) {
            ss >> member_line;
            std::from_chars(member_line.data(), member_line.data() + member_line.size(), resources_cost[j]);
        }

        resources.iron() = resources_cost[0];
        resources.gold() = resources_cost[1];
        resources.gems() = resources_cost[2];
        resources.exp() = resources_cost[3];

        // Создаем комнату и сохраняем ее в списке комнат Dungeon
        auto current_room = Room(vertex_id, resources);
        rooms_list_.push_back(current_room);

        // Добавляем новую пару смежностей
        adjacency_list_.push_back({vertex_id, vertex_list});
    }

    // Считываем количество еды у персонажа и создаем его
    std::getline(settings_file, line);
    ss = std::stringstream(line);

    num count_foods = 0;
    if (ss >> member_line) {
        std::from_chars(member_line.data(), member_line.data() + member_line.size(), count_foods);
    }
    person_ = Person(count_foods);

    // В конце - целевой ресурс, т.е его стоимость увеличена в 2 раза
    ss >> member_line;
    if (member_line == "iron") resources_.iron() *= 2;
    else if (member_line == "gold") resources_.gold() *= 2;
    else if (member_line == "gems") resources_.gems() *= 2;
    else if (member_line == "exp") resources_.exp() *= 2;
    else {
        throw std::logic_error(line);
    }

    settings_file.close();
}

const Room &Dungeon::getRoom(num room_index) const {
    if (room_index >= rooms_list_.size()) {
        throw std::out_of_range("Room number out of range: " + room_index);
    }

    return rooms_list_[room_index];
}

std::vector<num> Dungeon::getAdjacencyList(num room_index) const noexcept {
    std::vector<num> adj_rooms {};

    // Сохраняем все смежные с данной комнатой вершины
    for (auto adj : adjacency_list_) {
        if (adj.first == room_index) {
            adj_rooms.push_back(adj.second);
        }
    }

    return adj_rooms;
}

RoomInfo Dungeon::getRoomInfo(num room_index) const noexcept {
    // Получаем список индексов комнат, которые являются смежными с номером room_index
    auto adj_rooms = getAdjacencyList(room_index);

    // Проверяем, посещалась ли эта комната
    if (visits_.contains(room_index)) {
        auto res = rooms_list_[room_index].getResources();

        return RoomInfo(room_index, adj_rooms, res);
    }

    // Если комната не посещалась, то возможно она является видимой,
    // т.е смежной с одной из посещенных комнат
    for (auto index : adj_rooms) {
        if (visits_.contains(index)) {
            return RoomInfo(room_index, adj_rooms);
        }
    }

    return RoomInfo(room_index);
}

num Dungeon::getCost(const std::string &resource_name) noexcept {
    if (resource_name == "iron") {
        return resources_.iron();
    }
    else if (resource_name == "gold") {
        return resources_.gold();
    }
    else if (resource_name == "gems") {
        return resources_.gems();
    }
    else if (resource_name == "exp") {
        return resources_.exp();
    }

    else {
        throw std::logic_error("Cannot found resource name: " + resource_name);
    }
}
