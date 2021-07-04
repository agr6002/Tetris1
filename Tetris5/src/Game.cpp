#include <algorithm>
#include <iostream>
#include "Game.hpp"
#include "Vec2.hpp"
#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"

//remember to destroy blocks & pieces

using std::cout;
using std::endl;
using std::max;
using std::min;

Game::Game()
{
  cout << "Game::Game()" << endl;
  if (Initialize())
  {
    Run();
  }
}

Game::~Game()
{
  model.~Model();
}

bool Game::Initialize()
{
  // model = new Model();
  // view = new View(model);
  // controller = new Controller(model, view);
  cout << "Game::Initialize()" << endl;

  return model.Initialize();
}



void Game::Run()
{
  cout << "Game::Run()" << endl;
  while (model.isRunning)
  {
    controller.Run();
    model.Run();
    view.Run();
  }
}

void Game::UnloadData()
{
  cout << "Game::UnloadData()" << endl;
  // TODO
}