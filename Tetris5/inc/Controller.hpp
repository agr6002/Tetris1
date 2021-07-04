//#pragma "once"
#include "Model.hpp"
#include "View.hpp"

class Controller 
{
public:
    Controller(View view);
    void Initialize();
    void Run();

    Model model;
    View view;
};