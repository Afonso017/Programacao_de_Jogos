/**********************************************************************************
// Image (Código Fonte)
// 
// Criação:     16 Mar 2012
// Atualização: 13 Ago 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para representar imagens
//
**********************************************************************************/

#include "Image.h"
#include "Graphics.h"
#include "Image.h"
#include "Graphics.h"

// -------------------------------------------------------------------------------

Image::Image(string filename) : textureView(nullptr), width(0), height(0)
{
    // cria shader resource view da imagem em disco
    D3D11CreateTextureFromFile(
        Graphics::device,               // dispositivo Direct3D
        Graphics::context,              // contexto do dispositivo
        filename.c_str(),               // nome do arquivo de imagem
        nullptr,                        // retorna textura 
        &textureView,                   // retorna view da textura
        width,                          // retorna largura da imagem
        height);                        // retorna altura da imagem
}

// -------------------------------------------------------------------------------

Image::Image(string filename, uint width, uint height) : textureView(nullptr), width(width), height(height)
{
    // cria shader resource view da imagem em disco
    D3D11CreateTextureFromFile(
        Graphics::device,               // dispositivo Direct3D
        Graphics::context,              // contexto do dispositivo
        filename.c_str(),               // nome do arquivo de imagem
        nullptr,                        // retorna textura 
        &textureView,                   // retorna view da textura
        width,                          // retorna largura da imagem
        height);                        // retorna altura da imagem
}

// -------------------------------------------------------------------------------

Image::~Image()
{
    if (textureView)
    {
        ID3D11Resource* resource = nullptr;
        textureView->GetResource(&resource);

        if (resource)
        {
            resource->Release();
            resource = nullptr;
        }

        textureView->Release();
        textureView = nullptr;
    }
}

// -------------------------------------------------------------------------------
