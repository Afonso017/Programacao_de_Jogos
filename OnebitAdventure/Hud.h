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

enum LifeContainer
{
    FULL, THREE_QUARTERS, HALF, QUARTER
};

// ---------------------------------------------------------------------------------

class Hud : public Object
{
private:
    Sprite * mainBackg = nullptr;               // sprite do background principal
    Sprite * playerHud = nullptr;               // hud para mostrar estado do jogador
	TileSet* tileSet = nullptr;                 // tileset para mostrar estado do jogador
	Animation * life = nullptr; 			    // Animação para mostrar estado do jogador
    Font * consolas = nullptr;			        // Fonte para exibir texto na tela!

	float width;                                // Largura do background principal
	float height;	                            // Altura do background principal

public:
    uint tileWidth;							    // Largura de um tile
    uint tileHeight;							// Altura de um tile
    float mainLeftSide;                         // Lado esquerdo do background principal
    float mainRightSide;                        // Lado direito do background principal
    float mainBottomSide;					    // Lado inferior do background principal
    float offset;                               // Offset proporcional de pixels de um lado do background

    Hud();                                      // construtor
    ~Hud();                                     // destrutor

    void Update();                              // atualização do objeto
    void Draw();                                // desenho do objeto

	int Width();								// Retorna a largura do background principal
	int Height();								// Retorna a altura do background principal
    int InverseLine(float y) const;
    float Line(float y) const;
    float Col(float x) const;
    bool Collision(Object* obj1, Object* obj2, int tolerance = 1);
    bool Collision(int x1, int y1, int x2, int y2, int tolerance = 1);
}; 

// ---------------------------------------------------------------------------------

// Métodos Get para largura e altura do background principal
inline int Hud::Width()
{
    return mainBackg->Width();
}

inline int Hud::Height()
{
    return mainBackg->Height();
}

inline int Hud::InverseLine(float y) const
{
    return (window->Height() - y) / tileHeight;
}

inline float Hud::Line(float y) const
{
    return mainBottomSide - y * tileHeight;
}

inline float Hud::Col(float x) const
{
    return mainLeftSide + offset + tileWidth / 2.0f + x * tileWidth;
}

inline bool Hud::Collision(Object* obj1, Object* obj2, int tolerance)
{
    // Verifica se dois objetos estão se colidindo com uma tolerância de 1 inteiro
    return abs(obj1->X() - obj2->X()) <= tolerance && abs(obj1->Y() - obj2->Y()) <= tolerance;
}

inline bool Hud::Collision(int x1, int y1, int x2, int y2, int tolerance)
{
    // Verifica se dois objetos estão se colidindo com uma tolerância de 1 inteiro
    return abs(x1 - x2) <= tolerance && abs(y1 - y2) <= tolerance;
}

// ---------------------------------------------------------------------------------

#endif // HUD_H
