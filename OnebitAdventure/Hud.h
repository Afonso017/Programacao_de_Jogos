// Hud.h

#ifndef HUD_H
#define HUD_H

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Scene.h"
#include "Sprite.h"
#include "Font.h"
#include "Animation.h"

// ---------------------------------------------------------------------------------

enum Life
{
    FULL, THREE_QUARTERS, HALF, QUARTER
};

// ---------------------------------------------------------------------------------

class Hud : public Object
{
private:
    Sprite * backg = nullptr;           // sprite do background
    Sprite * hud = nullptr;             // hud para mostrar estado do jogador
    Font * consolas = nullptr;			// Fonte para exibir texto na tela!
    Image ** images = nullptr;          // Vetor de ponteiros para imagens que serão usadas no mapa

    int imagesSize;
    float width;
    float height;
    float tw;
    float th;
    bool viewBox = false;

    // Animation para representar a vida do jogador
    Animation * life = nullptr;

public:
    Hud(float tileWidth, float tileHeight);    // construtor
    ~Hud();                                    // destrutor

    static Scene * scene;

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto

    int Width();
    int Height();
}; 

// ---------------------------------------------------------------------------------

// Métodos Get para largura e altura do background principal
inline int Hud::Width()
{
    return backg->Width();
}

inline int Hud::Height()
{
    return backg->Height();
}

// ---------------------------------------------------------------------------------

#endif // HUD_H
