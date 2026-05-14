#include "bot.h"
#include <queue>
#include <algorithm>

AliseBot::AliseBot(const std::string& input_file) noexcept
: BaseBot(input_file) {}

void AliseBot::start() {
    auto person = dungeon_.getPerson();
    auto initial_count_foods = person.getCurrentCountFoods();

    while (person.isAlive()) {
        // Фаза исследования
        if (person.getCurrentCountFoods() > initial_count_foods / 2) {
            // Переходим в комнату с наименьшим номером
            auto avialable_rooms = dungeon_.getAdjacencyList(person.getCurrentRoomNumber());

            // Номера комнат хранятся в отсортированном виде,
            // поэтому необходимо найти лишь первый свободный индекс
            for (auto num : avialable_rooms) {
                if (!dungeon_.getRoom(num).isVisited() && num) {
                    person.enter(dungeon_.getRoom(num));
                    break;
                }
            }

            // Забираем самый ценный ресурс в комнате (в первый раз еда не тратится)
            auto res = dungeon_.getRoom(person.getCurrentRoomNumber()).getResources();
            auto result = getMostExpensiveResource(res, dungeon_.getCosts());

            if (!result.empty()) {
                person.collect(dungeon_.getRoom(person.getCurrentRoomNumber()), result);
            }

        }
        // Фаза возвращения
        else {
            // Выбираем кратчайший маршрут до начальной вершины.
            // Нужно учитывать, что путь составляется на основе того, про какие комнаты в подземелье он знает,
            // т.е изначально схема подземелья ему неизвестна и поясняется в результате прохождения по комнатам
            auto path = getShortestPath(person.getCurrentRoomNumber(), 0);

            // Вычисляем глубину текущей вершины в графе, если она меньше чем оставшееся количество еды,
            // то значит можно потратить еду на
            if ((path.size() - 1) < person.getCurrentCountFoods()) {
                auto res = dungeon_.getRoom(person.getCurrentRoomNumber()).getResources();
                auto result = getMostExpensiveResource(res, dungeon_.getCosts());

                if (!result.empty()) {
                    person.collect(dungeon_.getRoom(person.getCurrentRoomNumber()), result);
                }

                continue;
            }

            // Переходим на одну вершину ближе к начальной точке
            person.enter(dungeon_.getRoom(path[1]));
        }
    }

    person.result(dungeon_.getCosts());
}

// Ищем самый дорогой ресурс из всех и возвращаем его название
// При этом его количество не должно быть равно 0
std::string AliseBot::getMostExpensiveResource(Resources volumes, Resources costs) noexcept {
    std::vector<std::string> avialable_resources {"iron", "gold", "gems", "exp"};
    std::string result = avialable_resources[0];

    // Сравниваем два игровых ресурса, тот, чья ценность выше,
    // сравнивается с остальными в списке, пока не найдем с наибольшей ценой или хотя бы не пустой
    for (auto i = 1; i < 4; ++i) {
        auto applicant = avialable_resources[i];
        if (volumes[applicant] * costs[applicant] > volumes[result] * costs[result] &&
            volumes[applicant] > 0) {
            result = applicant;
        }
    }

    return result;
}

std::vector<num> AliseBot::getShortestPath(num start_num, num end_num) noexcept {
    // Нахождение кратчайшего маршрута в графе между двумя вершинами
    // Для этого воспользуемся алгоритмом поиска в ширину, так как все ребра в графе равновесны.
    // Таким образом остается лишь найти наименьшее количество вершин от начальной до конечной комнаты

    num n = dungeon_.getCountRooms(); // количество вершин в графе

    std::vector<num> d(n, UINT8_MAX); // Храним кратчайшие пути
    std::vector<num> p(n, UINT8_MAX);
    std::queue<num> q;

    d[start_num] = 0;
    q.push(start_num);

    while (!q.empty()) {
        num v = q.front();
        q.pop();

        if (v == end_num) break;

        for (num adj : dungeon_.getAdjacencyList(v)) {
            // Назад персонаж должен идти по пройденным комнатам
            if (d[adj] == UINT8_MAX && (dungeon_.getRoom(adj).isVisited() || adj == end_num)) {
                d[adj] = d[v] + 1;
                p[adj] = v;
                q.push(adj);
            }
        }
    }

    std::vector<num> result_path;
    for (auto v = end_num; v != UINT8_MAX; v = p[v]) {
        result_path.push_back(v);
    }
    std::reverse(result_path.begin(), result_path.end());

    return result_path;
}
