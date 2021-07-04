#pragma "once"
#include "SDL.h"
#include "Block.hpp"
#include "Model.hpp"

class View 
{
public:
    View(Model model);
    void Initialize();
    void Run();

    Model model;
};