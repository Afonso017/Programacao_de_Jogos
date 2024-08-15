// ------------------------------------------------------------------------------
// Inclus�es

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
    engine->window->Size(400, 686);
    engine->window->Color(25, 25, 25);
    engine->window->Title("OneBit Adventure");
    engine->window->Icon(IDI_ICON);

    // configura dispositivo gr�fico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Home());

    delete engine;
    return status;
}

// ------------------------------------------------------------------------------