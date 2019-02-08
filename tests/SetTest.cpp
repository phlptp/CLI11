#include "app_helper.hpp"

TEST_F(TApp, SimpleSets) {
    std::string value;
    auto opt = app.add_cli_set("-s,--set", value, {"one", "two", "three"});
    args = {"-s", "one"};
    run();
    EXPECT_EQ(1u, app.count("-s"));
    EXPECT_EQ(1u, app.count("--set"));
    EXPECT_EQ(1u, opt->count());
    EXPECT_EQ(value, "one");
}
