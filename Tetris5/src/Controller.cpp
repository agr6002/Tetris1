#include "Controller.hpp"

Controller::Controller(View view)
    :view(view), model(view.model)
{}

void Controller::Initialize()
{
    
}

void Controller::Run()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        model.isRunning = false;
        break;
        }
    }

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        model.isRunning = false;
    }
    model.isDropping = (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]);
    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
    {
        if (model.CheckPieceDrop(-1, 0))
        {
        model.piece->Move(-1);
        }
    }
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
    {
        if (model.CheckPieceDrop(1, 0))
        {
        model.piece->Move(1);
        }
    }
    if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
    {
        model.piece->Rotate(1);
        if (!model.CheckPieceDrop(0, 0))
        {
        model.piece->Rotate(-1);
        }
    }
    // if (keyState[SDL_SCANCODE_N] && !Mix_PlayingMusic())
    // {
    //    Mix_PlayMusic(music, -1);
    // }
    // if (keyState[SDL_SCANCODE_M] && Mix_PlayingMusic())
    // {
    //   Mix_HaltMusic();
    // }
    if (keyState[SDL_SCANCODE_P] && !Mix_PausedMusic())
    {
        Mix_PauseMusic();
    }
    if (keyState[SDL_SCANCODE_U] && Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
}
