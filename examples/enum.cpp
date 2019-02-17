#include <CLI/CLI.hpp>
#include <sstream>

enum class Level : int { High, Medium, Low };

int main(int argc, char **argv) {
    CLI::App app;

    Level level;
    std::vector<std::pair<std::string, Level>> map{
        {"high", Level::High}, {"medium", Level::Medium}, {"low", Level::Low}};
    app.add_set("-l,--level", level, {Level::High, Level::Medium, Level::Low}, "Level settings")
        ->type_name("enum/Level in {High=0, Medium=1, Low=2}")
        ->transform(CLI::Transformer(map, CLI::ignore_case));

    CLI11_PARSE(app, argc, argv);

    return 0;
}
