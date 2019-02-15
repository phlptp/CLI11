#include "app_helper.hpp"

static_assert(CLI::is_shared_ptr<std::shared_ptr<int>>::value == true, "is_shared_ptr should work on shared pointers");
static_assert(CLI::is_shared_ptr<int *>::value == false, "is_shared_ptr should work on pointers");
static_assert(CLI::is_shared_ptr<int>::value == false, "is_shared_ptr should work on non-pointers");

static_assert(CLI::is_copyable_ptr<std::shared_ptr<int>>::value == true,
              "is_copyable_ptr should work on shared pointers");
static_assert(CLI::is_copyable_ptr<int *>::value == true, "is_copyable_ptr should work on pointers");
static_assert(CLI::is_copyable_ptr<int>::value == false, "is_copyable_ptr should work on non-pointers");

TEST_F(TApp, SimpleSets) {
    std::string value;
    auto opt = app.add_option("-s,--set", value)->check(CLI::IsMember(std::set<std::string>({"one", "two", "three"})));
    args = {"-s", "one"};
    run();
    EXPECT_EQ(1u, app.count("-s"));
    EXPECT_EQ(1u, app.count("--set"));
    EXPECT_EQ(1u, opt->count());
    EXPECT_EQ(value, "one");
}

TEST_F(TApp, SimpleSetsPtrs) {
    auto set = std::shared_ptr<std::set<std::string>>(new std::set<std::string>{"one", "two", "three"});
    std::string value;
    auto opt = app.add_option("-s,--set", value)->check(CLI::IsMember(set));
    args = {"-s", "one"};
    run();
    EXPECT_EQ(1u, app.count("-s"));
    EXPECT_EQ(1u, app.count("--set"));
    EXPECT_EQ(1u, opt->count());
    EXPECT_EQ(value, "one");

    set->insert("four");

    args = {"-s", "four"};
    run();
    EXPECT_EQ(1u, app.count("-s"));
    EXPECT_EQ(1u, app.count("--set"));
    EXPECT_EQ(1u, opt->count());
    EXPECT_EQ(value, "four");
}
