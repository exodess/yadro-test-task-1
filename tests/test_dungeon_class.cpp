#include <gtest/gtest.h>

#include "bot.h"
#include "dungeon.h"

TEST(FunctionalityTest, Dungeon_LoadDungeon_Test_With_Throw) {
    std::string test_file = "...";

    Dungeon dungeon;
    ASSERT_ANY_THROW(dungeon.loadDungeon(test_file));
}

TEST(FunctionalityTest, Dungeon_LoadDungeon_Test_1) {
    std::string test_file = "in1_success.txt";

    Dungeon dungeon;
    dungeon.loadDungeon(test_file);

    auto costs = dungeon.getCosts();
    auto person = dungeon.getPerson();

    EXPECT_EQ(costs["iron"], DEFAULT_IRON_COST);
    EXPECT_EQ(costs["gold"], DEFAULT_GOLD_COST);
    EXPECT_EQ(costs["gems"], DEFAULT_GEMS_COST * 2);
    EXPECT_EQ(costs["exp"], DEFAULT_EXP_COST);

    EXPECT_EQ(dungeon.getCountPaths(), 6);
    EXPECT_EQ(dungeon.getCountRooms(), 6);

    EXPECT_EQ(person.getCurrentRoomNumber(), 0);
    EXPECT_EQ(person.getCurrentCountFoods(), 6);
    EXPECT_EQ(person.isAlive(), true);
}