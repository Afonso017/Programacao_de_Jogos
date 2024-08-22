#ifndef _PLATFORMER_BACKGROUND_H_
#define _PLATFORMER_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
    Sprite * backg = nullptr;           // sprite do background
    uint width;
    uint height;

public:
    Background();                       // construtor
    ~Background();                      // destrutor

    int Width();
    int Height();

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

inline int Background::Width()
{
    return backg->Width();
}

inline int Background::Height()
{
    return backg->Height();
}

inline void Background::Draw()
{
    backg->Draw(x, y, Layer::BACK);
}

// ---------------------------------------------------------------------------------

#endif
