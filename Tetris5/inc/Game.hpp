#pragma once
#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Block.hpp"
#include "Config.hpp"
#include "Color.hpp"
#include "Piece.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

class Game
{
public:
  Game();
  ~Game();

private:
  bool Initialize();
  void LoadData();
  void Run();
  void UnloadData();

  Model model = Model();
  View view = View(model);
  Controller controller = Controller(view);
  bool isPlaying = true;

};
