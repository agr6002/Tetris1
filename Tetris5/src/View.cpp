#include "View.hpp"

View::View(Model model)
    :model(model)
{}

void View::Initialize()
{
    
}

void View::Run()
{
    SDL_SetRenderDrawColor(model.renderer, 0, 0, 0, 255);
    SDL_RenderClear(model.renderer);
    for (int row = 0; row < model.numBoardRows; ++row)
    {
        for (int col = 0; col < model.numBoardCols; ++col)
        {
        Block *block = model.blocks[row][col];
        if (block)
        {
            block->Draw(model.renderer);
        }
        }
    }
    model.piece->Draw(model.renderer);
    SDL_RenderPresent(model.renderer);
}