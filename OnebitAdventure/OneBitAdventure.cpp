// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Resources.h"
#include "Home.h"

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura a janela do jogo
    engine->window->Mode(WINDOWED);
    //engine->window->Size(720, 1080);        // testando uma resolução diferente
    engine->window->Color(25, 25, 25);
    engine->window->Title("OneBit Adventure");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);


    // inicia o jogo
    int status = engine->Start(new Home());

    delete engine;
    return status;
}

// ------------------------------------------------------------------------------