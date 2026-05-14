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
    std::string temp;
    num N = 0;

    settings_file.open(path);

    // Проверяем, существует ли файл и может ли программа его открыть
    if (!settings_file.is_open()) {
        throw std::runtime_error("Could not open settings file");
    }

    // ===============================================================================================
    // В первой строке должно быть одно число N - количество комнат в подземелье (не считая начальную)
    // ===============================================================================================
    std::getline(settings_file, line);
    ss = std::stringstream(line);

    ss >> member_line;
    std::from_chars(member_line.data(), member_line.data() + member_line.size(), N);

    // Считываем N+1 строк с информацией о каждой комнате
    // Формат строки: <номер_вершины> <список_смежных_вершин> <iron> <gold> <gems> <exp>
    for (auto i = 0; i <= N; i++) {
        Resources resources;
        num vertex_id = 0;
        std::vector<num> vertex_list {};

        std::getline(settings_file, line);
        ss = std::stringstream(line);

        // ===============================
        // Первый параметр - номер вершины
        // ===============================
        if (ss >> member_line) {
            std::from_chars(member_line.data(), member_line.data() + member_line.size(), vertex_id);
        }

        // =======================================
        // Второй параметр - список смежных вершин
        // =======================================
        ss >> member_line;

        // Проверяем, чтобы не было лишних символов
        for(auto ch : member_line) {
            if(!std::isdigit(ch) && ch != ',') {
                throw std::runtime_error(line);
            }
        }
        
        while (!member_line.empty()) {
            num ind;

            std::getline(std::stringstream(member_line), temp, ',');
            std::from_chars(temp.data(), temp.data() + temp.size(), ind);
            member_line = (member_line.find(',') != std::string::npos) ? member_line.substr(member_line.find(',') + 1) : "";
            vertex_list.push_back(ind);
        }

        // =================================================================
        // Остальные четыре параметра - количество каждого ресурса в комнате
        // =================================================================
        std::vector<num> resources_cost;
        resources_cost.reserve(4);
        for (auto j = 0; j < 4; j++) {
            num count = 0;
            ss >> member_line;
            std::from_chars(member_line.data(), member_line.data() + member_line.size(), count);
            resources_cost[j] = count;
        }

        resources["iron"] = resources_cost[0];
        resources["gold"] = resources_cost[1];
        resources["gems"] = resources_cost[2];
        resources["exp"] = resources_cost[3];

        // Создаем комнату и сохраняем ее в списке комнат Dungeon
        auto current_room = Room(vertex_id, resources);
        rooms_list_.push_back(current_room);

        // Добавляем новую пару смежностей в виде <номер_вершины> : { список смежных вершин }
        adjacency_list_.push_back({vertex_id, vertex_list});
    }

    // ==================================================
    // Считываем количество еды у персонажа и создаем его
    // ==================================================
    std::getline(settings_file, line);
    ss = std::stringstream(line);

    num count_foods = 0;
    if (ss >> member_line) {
        std::from_chars(member_line.data(), member_line.data() + member_line.size(), count_foods);
    }
    person_ = Person(count_foods);

    // ==============================================================
    // В конце - целевой ресурс, т.е его стоимость увеличена в 2 раза
    // ==============================================================
    ss >> member_line;
    prices_[member_line] *= 2;

    getRoom(0).visite(); // В начальный момент персонаж находится в комнате 0

    settings_file.close();
}

Room &Dungeon::getRoom(num room_index) {
    if (room_index >= rooms_list_.size()) {
        throw std::out_of_range("Room number out of range");
    }

    return rooms_list_[room_index];
}

const Room &Dungeon::getRoom(num room_index) const {
    if (room_index >= rooms_list_.size()) {
        throw std::out_of_range("Room number out of range");
    }

    return rooms_list_[room_index];
}

std::vector<num> Dungeon::getAdjacencyList(num room_index) const noexcept {

    // Сохраняем все смежные с данной комнатой вершины
    for (auto adj : adjacency_list_) {
        if (adj.first == room_index) {
            return adj.second;
        }
    }

    return {};
}

RoomInfo Dungeon::getRoomInfo(num room_index) const noexcept {
    // Получаем список индексов комнат, которые являются смежными с номером room_index
    auto adj_rooms = getAdjacencyList(room_index);

    // Проверяем, посещалась ли эта комната
    if (getRoom(room_index).isVisited()) {
        auto res = rooms_list_[room_index].getResources();

        return RoomInfo(room_index, adj_rooms, res);
    }

    // Если комната не посещалась, то возможно она является видимой,
    // т.е смежной с одной из посещенных комнат
    for (auto index : adj_rooms) {
        if (getRoom(index).isVisited()) {
            return RoomInfo(room_index, adj_rooms);
        }
    }

    return RoomInfo(room_index);
}

const Resources& Dungeon::getCosts() const noexcept {
    return prices_;
}

Resources &Dungeon::getCosts() noexcept {
    return prices_;
}


Person& Dungeon::getPerson() noexcept {
    return person_;
}

num Dungeon::getCountRooms() const noexcept {
    return rooms_list_.size();
}

num Dungeon::getCountPaths() const noexcept {
    // В списке смежностей хранятся пары в двух направлениях
    return adjacency_list_.size();
}

