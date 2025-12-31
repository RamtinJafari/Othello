struct Config
{
    bool instanceCreated = false;
    int GAME_HISTORY_LIMIT;
    int BOARD_SIZE;
    string BOARD_COLOR;
    string BOARD_BORDER_COLOR;
    bool SOUND;
    bool SHOW_AVAILABLE_PLACES_FOR_PIECES;
    bool HINT;
    int HINT_LIMIT;

    private:
        Config()
        {
            
        }

    void intializeConfig() 
    {

    }

    Config createCostumConfig() 
    {

    }
};

static Config config;