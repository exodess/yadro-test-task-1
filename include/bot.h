#ifndef BOT_H
#define BOT_H
#include "dungeon.h"

// В данном файле описана структура класса Бота, который будет управлять игровым персонажем
// Весь алгоритм по нахождению оптимальной стратегии находится здесь

// Для того, чтобы код был как можно более легко встраиваемым, был введен абстрактный класс для бота,
// который бы описывал минимальный функционал, которым должен обладать любой бот для этой игры
// Поэтому, если нужно реализовать новый алгоритм работы, нужно лишь изменить логику класса-наследника BaseBot

class BaseBot {
protected:
    Dungeon dungeon_;
    std::string input_file_;
public:
    explicit BaseBot(const std::string& input_file) noexcept : input_file_(input_file) {}

    virtual void start() = 0;
    virtual ~BaseBot() = default;
};

class AliseBot : public ::BaseBot {
public:
    explicit AliseBot(const std::string& input_file) noexcept;

    std::string getMostExpensiveResource(Resources volumes, Resources costs) noexcept;
    std::vector<num> getShortestPath(num from, num to) noexcept;

    // Реализация разных фаз работы бота
    void setResearchPhase(Person&);
    void setReturnPhase(Person&);

    // Здесь располагается логика управления персонажем
    void start() override;
};

#endif
