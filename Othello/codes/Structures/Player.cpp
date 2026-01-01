#include <string>
#include <windows.h>

struct Player
{
    std::string name;
    char color;

    Player(std::string name, char color)
    {
        this -> name = name;
        this -> color = color;
    }

    std::string retrievePlayer()
    {
        return name + "|" + std::string(1, color);
    }

    void loadPlayer(std::string player)
    {
        int speratorIndex = player.find("|");

        std::string name = player.substr(0, speratorIndex);
        std::string color = player.substr(speratorIndex + 1, player.size());

        this -> name = name;
        this -> color = static_cast<char>(color[0]);
    }
};