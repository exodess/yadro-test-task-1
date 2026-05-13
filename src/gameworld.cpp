#include "gameworld.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void Dungeon::loadWorld(std::string path) {
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

    // Последняя строка - информация об игроке: количество еды и название целевого ресурса

    std::getline(settings_file, line);
    ss = std::stringstream(line);

    num count_foods = 0;
    if (ss >> member_line) {
        std::from_chars(member_line.data(), member_line.data() + member_line.size(), count_foods);
    }

    ss >> member_line;
    person_ = Person(member_line, count_foods);


    settings_file.close();
}
