#include "Model.hpp"


Model::Model()
{} 

Model::~Model()
{
    std::cout << "Model::~Model()" << std::endl;
    Mix_FreeMusic(music);
    music = NULL;
    for (auto sound_effect: sound_effects)
    {
        Mix_FreeMusic(sound_effect);
        sound_effect = NULL;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}

void Model::CheckLine()
{
  std::cout << "check line" << std::endl;
  for (auto block : piece->blocks)
  {
    bool isLine = true;
    for (int i = 1; i < numBoardCols - 1; i++)
    {
      if (!blocks[block->pos.row][i]) 
      {
        std::cout << block->pos.row << " " << i << std::endl;
        isLine = false;
      }
      else
      {
        std::cout << block->pos.row << " : " << i << std::endl;
      }
    }
    if (isLine == true)
    {
      std::cout << "clear line" << std::endl;
      ClearLine(block->pos.row);
    }
  }
}

bool Model::CheckPieceDrop(int dx, int dy)
{
  for (auto block : piece->blocks)
  {
    if (blocks[block->pos.row + dy][block->pos.col + dx])
    {
      return false;
    }
  }
  return true;
}

void Model::ClearLine(int r)
{
  Mix_PlayMusic(sound_effects[1], -1);
  for (int col = 1; col < numBoardCols - 1; col++)
  {
    blocks[r][col] = nullptr;
  }
  for (int row = r + 1; row > 0; row--)
  {
    for (int col = 1; col < numBoardCols - 1; col++) 
    {
      if (blocks[row][col])
      {
        std::cout << "Block" << std::endl;
        blocks[row][col]->pos.row -= 1;
        blocks[row][col] = blocks[row - 1][col];
      }
    }
  }
}

void Model::CreateNewPiece()
{
    int num = (std::rand()% 6);
    piece = new Piece(Vec2{1, numBoardCols / 2}, blockSize, num);
}

void Model::CopyPiece()
{
  for (auto block : piece->blocks)
  {
    blocks[block->pos.row][block->pos.col] = block;
  }
}

bool Model::Initialize()
{
    int blockWidth = Config::windowMaxWidth / (numBoardCols + numDisplayCols);
    int blockHeight = Config::windowMaxHeight / std::max(numBoardRows, numDisplayRows);
    blockSize = std::min(blockWidth, blockHeight);
    windowWidth = blockSize * (numBoardCols + numDisplayCols);
    windowHeight = blockSize * std::max(numBoardRows, numDisplayRows);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        Config::title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        0);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize: %s\n", Mix_GetError());
        return false;
    }

    music = Mix_LoadMUS(MUSIC_FILE);
    if (music == NULL)
    {
        printf("Failed to load music: %s\n", Mix_GetError());
        return false;
    }
    for (int i = 0; i < numOfSoundEffects; i++)
    {
        sound_effects[i] = Mix_LoadMUS(SOUND_EFFECTS_FILE[i]);
        if (sound_effects[i] == NULL)
        {
        printf("Failed to load music: %s\n", Mix_GetError());
        return false;
        }
    }
    Mix_PlayMusic(music, -1);
    Mix_PauseMusic();
    // TODO: Random::Init();

    LoadData();

    timePrior = SDL_GetTicks();

    return true;
}

void Model::LoadData()
{
    std::cout << "Game::LoadData()" << std::endl;
    for (int row = 0; row < numBoardRows; ++row)
    {
        for (int col = 0; col < numBoardCols; ++col)
        {
        if (row == 0 || row == numBoardRows - 1 || col == 0 || col == numBoardCols - 1)
        {
            blocks[row][col] = new Block{wallColor, blockSize, Vec2{row, col}};
        }
        else
        {
            blocks[row][col] = nullptr;
        }
        }
    }
    CreateNewPiece();
}

void Model::Run()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), timePrior + 16));
    Uint32 timeChange = SDL_GetTicks() - timePrior;
    if (timeChange > 50)
    {
        timeChange = 50;
    }
    timeDelayed += timeChange;
    Uint32 fallDelay = (isDropping ? fallDelayFast : fallDelayRegular);
    if (timeDelayed >= fallDelay)
    {
        if(Mix_PlayingMusic())
        {
            Mix_HaltMusic();
        }
        if (CheckPieceDrop(0,1))
        {
        piece->Drop();
        } else
        {
        //Mix_PlayMusic(sound_effects[0], -1);
        CopyPiece();
        CheckLine();
        CreateNewPiece();
        }
        timeDelayed -= fallDelay;
    }
    timePrior = SDL_GetTicks();
}