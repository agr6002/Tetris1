#pragma "once"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Block.hpp"
#include "Config.hpp"
#include "Color.hpp"
#include "Piece.hpp"
#include "Vec2.hpp"

class Model 
{
public:
    Model();
    ~Model();
    bool Initialize();
    void Run();

    bool CheckPieceDrop(int dx, int dy);
    void CopyPiece();
    void ClearLine(int r);
    void CheckLine();
    void CreateNewPiece();

    void LoadData();

    Uint32 fallDelayFast = Config::fallDelayFast;
    Uint32 fallDelayRegular = Config::fallDelayRegular;
    bool isDropping = false;
    Uint32 timeDelayed = 0;
    Uint32 timePrior = 0;
    int blockSize = 0;

    SDL_Renderer *renderer = nullptr;
    int numBoardCols = Config::numBoardCols;
    int numBoardRows = Config::numBoardRows;
    Block *blocks[Config::numBoardRows][Config::numBoardCols];
    Piece *piece = nullptr;
    int numDisplayCols = Config::numDisplayCols;
    int numDisplayRows = Config::numDisplayRows;
    SDL_Window *window = nullptr;
    int windowHeight = 0;
    int windowWidth = 0;
    Color &wallColor = Color::gray;

    int numOfSoundEffects = 2;
    char const *MUSIC_FILE = "media/music-1.ogg";
    char const *SOUND_EFFECTS_FILE[2] = {"media/selection.wav", "media/line.wav"};
    Mix_Music *music = NULL;
    Mix_Music *sound_effects[2] = {NULL, NULL};
    bool isRunning = true;
};