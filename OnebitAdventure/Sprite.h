/**********************************************************************************
// Sprite (Arquivo de Cabe�alho)
// 
// Cria��o:     11 Jul 2007
// Atualiza��o: 07 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para representar um sprite
//
**********************************************************************************/

#ifndef _PROGJOGOS_SPRITE_H_
#define _PROGJOGOS_SPRITE_H_

// ---------------------------------------------------------------------------------

#include "Image.h"
#include "Types.h"
#include <DirectXMath.h>
using namespace DirectX;

// ---------------------------------------------------------------------------------

struct SpriteData
{
    float x, y;
    float depth;
    uint  width;
    uint  height;
    ID3D11ShaderResourceView* texture;
    XMFLOAT2 texCoord;
    XMFLOAT2 texSize;
};

// ---------------------------------------------------------------------------------

struct Layer
{
    static const float FRONT;
    static const float UPPER;
    static const float MIDDLE;
    static const float LOWER;
    static const float BACK;
};

// ---------------------------------------------------------------------------------

class Sprite
{
private:
    SpriteData sprite;              // dados do sprite 
    bool localImage;                // imagem local ou externa
    const Image * image;            // ponteiro para uma imagem
    void InitSpriteData();          // ajusta valores iniciais do sprite
    void InitSpriteData(uint width, uint height);          // ajusta valores iniciais do sprite

public:
    Sprite(string filename);        // constroi sprite a partir de um arquivo
    Sprite(const Image * img);      // constroi sprite a partir de imagem existente
    ~Sprite();                      // destrutor do sprite

    int Width();                    // largura do sprite
    int Height();                   // altura do sprite

    // desenha imagem na posi��o (x,y) e profundidade (z)
    void Draw(float x, float y, float z = Layer::MIDDLE);
};

// ---------------------------------------------------------------------------------
// Fun��es Inline

// retorna a largura do sprite
inline int Sprite::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline int Sprite::Height() 
{ return image->Height(); }

// ---------------------------------------------------------------------------------

#endif