/**********************************************************************************
// Image (Arquivo de Cabeçalho)
// 
// Criação:     16 Mar 2012
// Atualização: 13 Ago 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para representar imagens
//
**********************************************************************************/

#ifndef _PROGJOGOS_IMAGE_H_
#define _PROGJOGOS_IMAGE_H_

#include "Types.h"
#include "Texture.h"
#include <string>
using std::string;

// -------------------------------------------------------------------------------

class Image
{
private:
    ID3D11ShaderResourceView * textureView;      // view associada a textura
    uint width;                                  // largura da imagem
    uint height;                                 // altura da imagem
    string filename;                             // nome do arquivo

public:
    Image(string filename);                      // constroi imagem a partir de um arquivo
    Image
    (string filename, uint width, uint heigth);  // constroi imagem a partir de um arquivo e redimensiona
    ~Image();                                    // destrutor

    uint Width() const;                          // retorna largura da imagem
    uint Height() const;                         // retorna altura da imagem
    void Resize(uint width, uint height);     // redimensiona a imagem
    ID3D11ShaderResourceView * View() const;     // retorna ponteiro para a view da imagem
};

// Métodos Inline
// -------------------------------------------------------------------------------

inline uint Image::Width() const
{ return width; }

inline uint Image::Height() const
{ return height; }

inline ID3D11ShaderResourceView* Image::View() const
{ return textureView; }

// -------------------------------------------------------------------------------

#endif
