#include <gtest/gtest.h>
#include "bot.h"

// Тестирование алгоритмов в классе AliseBot

TEST(FunctionalityTest, AliseBot_Get_Most_Expensive_Resources_Test) {
    // Проверяем алгоритм нахождения самой дорогого ресурса в комнате

    AliseBot bot("in1_success.txt");

    Dungeon dungeon;
    dungeon.loadDungeon("in3.txt");

    EXPECT_EQ(bot.getMostExpensiveResource(dungeon.getRoom(0).getResources(), dungeon.getCosts()), "gems");
    EXPECT_EQ(bot.getMostExpensiveResource(dungeon.getRoom(1).getResources(), dungeon.getCosts()), "gems");
    EXPECT_EQ(bot.getMostExpensiveResource(dungeon.getRoom(2).getResources(), dungeon.getCosts()), "iron");
    EXPECT_EQ(bot.getMostExpensiveResource(dungeon.getRoom(3).getResources(), dungeon.getCosts()), "gold");
    EXPECT_EQ(bot.getMostExpensiveResource(dungeon.getRoom(4).getResources(), dungeon.getCosts()), "exp");

}

TEST(FunctionalityTest, AliseBot_Get_Shortest_Path_Test) {
    AliseBot bot("in3.txt");

    bot.start();

    auto path_from3_to0 = bot.getShortestPath(3, 0);
    auto path_from4_to1 = bot.getShortestPath(4, 1);
    auto path_from2_to_4 = bot.getShortestPath(2, 4);
    auto path_from3_to_4 = bot.getShortestPath(3, 4);

    std::vector<num> path30 = {3, 1, 0};
    std::vector<num> path41 = {4, 0, 1};
    std::vector<num> path24 = {2, 0, 4};
    std::vector<num> path34 = {3, 1, 0, 4};

    EXPECT_EQ(path_from3_to0, path30);
    EXPECT_EQ(path_from4_to1, path41);
    EXPECT_EQ(path_from2_to_4, path24);
    EXPECT_EQ(path_from3_to_4, path34);

}