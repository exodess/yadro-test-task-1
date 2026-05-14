#include <gtest/gtest.h>
#include "resources.h"

TEST(FunctionalityTest, Resources_Test) {
    Resources res_default;
    Resources res_users = Resources(1, 2, 5, 19);

    ASSERT_EQ(res_default["iron"], 0);
    ASSERT_EQ(res_default["gold"], 0);
    ASSERT_EQ(res_default["gems"], 0);
    ASSERT_EQ(res_default["exp"], 0);

    ASSERT_EQ(res_users["iron"], 1);
    ASSERT_EQ(res_users["gold"], 2);
    ASSERT_EQ(res_users["gems"], 5);
    ASSERT_EQ(res_users["exp"], 19);

}