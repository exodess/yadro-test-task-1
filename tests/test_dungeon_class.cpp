#include <gtest/gtest.h>
#include "dungeon.h"

TEST(TestTask1, Dungeon_Load_World_Test) {
    std::string test_file = "in1_success.txt";

    Dungeon dungeon;
    ASSERT_ANY_THROW(dungeon.loadDungeon(test_file));
}