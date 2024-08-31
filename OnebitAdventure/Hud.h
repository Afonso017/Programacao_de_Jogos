// Hud.h

#ifndef HUD_H
#define HUD_H

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Scene.h"
#include "Sprite.h"
#include "Font.h"
#include "Animation.h"
#include "Prop.h"

// ---------------------------------------------------------------------------------

enum Life
{
    FULL, THREE_QUARTERS, HALF, QUARTER
};

// ---------------------------------------------------------------------------------

class Hud : public Object
{
private:
    Sprite * backg = nullptr;                   // sprite do background
    Sprite * hud = nullptr;                     // hud para mostrar estado do jogador
	TileSet* tileSet = nullptr;                 // tileset para mostrar estado do jogador
    Font * consolas = nullptr;			        // Fonte para exibir texto na tela!

	float width;                                // Largura do background principal
	float height;	                            // Altura do background principal
	float tw;		                            // Largura de um tile
	float th;		                            // Altura de um tile
    float rightSide;                            // Lado direito do background principal
    float tileBottom;                           // Posi��o y da primeira linha do background (de baixo para cima)
    float offset;                               // Offset proporcional de pixels de um lado do background
    float leftSide;                             // Lado esquerdo do background principal 

    // Animation para representar a vida do jogador
    Animation * life = nullptr;

public:
    Hud(float tileWidth, float tileHeight, float offset);     // construtor
    ~Hud();                                                   // destrutor

    void Update();                              // atualiza��o do objeto
    void Draw();                                // desenho do objeto

    bool nextLevel; 					        // Flag para indicar que o jogador passou de n�vel
	int Width();								// Retorna a largura do background principal
	int Height();								// Retorna a altura do background principal
    float Line(float x) const;                  // Retorna a posi��o y de uma linha no background
    float Col(float y) const;                   // Retorna a posi��o x de uma coluna no background
    bool Collision(Object*, Object*, int);      // Verifica colis�o entre dois objetos
	bool Collision(int, int, int, int, int);    // Verifica colis�o entre dois pontos
}; 

// ---------------------------------------------------------------------------------

// M�todos Get para largura e altura do background principal
inline int Hud::Width()
{
    return backg->Width();
}

inline int Hud::Height()
{
    return backg->Height();
}

inline float Hud::Line(float y) const
{
    return window->Height() - y * th;
}


inline float Hud::Col(float x) const
{
    return leftSide + offset + tw / 2.0f + x * tw;
}

inline bool Hud::Collision(Object* obj1, Object* obj2, int tolerance = 1)
{
    // Verifica se dois objetos est�o se colidindo com uma toler�ncia de 1 inteiro
    return abs(obj1->X() - obj2->X()) <= tolerance && abs(obj1->Y() - obj2->Y()) <= tolerance;
}

inline bool Hud::Collision(int x1, int y1, int x2, int y2, int tolerance = 1)
{
    // Verifica se dois objetos est�o se colidindo com uma toler�ncia de 1 inteiro
    return abs(x1 - x2) <= tolerance && abs(y1 - y2) <= tolerance;
}

// ---------------------------------------------------------------------------------

#endif // HUD_H
