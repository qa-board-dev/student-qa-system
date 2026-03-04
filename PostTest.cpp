//
// Created by 16198 on 2/25/2026.
//

#include "Post.h"
#include <gtest/gtest.h>

TEST(PostTest, StoresAuthorAndContent) {
Post p("Student1", "Hello everyone!");
    EXPECT_EQ(p.getAuthor(),"Student1");
    EXPECT_EQ(p.getContent(),"Hello everyone!");
}
TEST(PostTest, StartsUnapproved) {
    Post p("Student1", "Hello");
    EXPECT_FALSE(p.isApproved());
}
TEST(PostTest, ApproveChangesStatus) {
    Post p("Student1", "Hello");
    p.approve();
    EXPECT_TRUE(p.isApproved());
}
TEST(PostTest, EmptyContentThrowsException) {
    EXPECT_THROW(
    Post("Student1", ""),
    invalid_argument);
}