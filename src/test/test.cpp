#include <gtest/gtest.h>

#include "include/lib.h"

TEST(templateTest, TemplateTest1) {
    auto vec = get_vector(10);
    EXPECT_EQ(10, vec.size());
}
