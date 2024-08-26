/**********************************************************************************
// TileSet (C�digo Fonte)
// 
// Cria��o:     17 Abr 2012
// Atualiza��o: 23 Ago 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Representa uma folha de sprites
//
**********************************************************************************/

#include "TileSet.h"
#include "Image.h"

// -------------------------------------------------------------------------------

TileSet::TileSet(string filename, uint tileWidth, uint tileHeight, uint numCols, uint numTiles) : 
    image(new Image(filename)), 
    width(tileWidth), 
    height(tileHeight), 
    columns(numCols),    
    size(numTiles)
{
    
}

// -------------------------------------------------------------------------------

TileSet::TileSet(Image* img, uint tileWidth, uint tileHeight, uint numCols, uint numTiles) :
    image(img),
    width(tileWidth),
    height(tileHeight),
    columns(numCols),
    size(numTiles)
{

}

// -------------------------------------------------------------------------------

TileSet::TileSet(string filename, uint numLines, uint numCols) :
    image(new Image(filename)),
    columns(numCols),
    size(numLines* numCols)
{
    width = image->Width() / numCols;
    height = image->Height() / numLines;
}

// -------------------------------------------------------------------------------

TileSet::TileSet(Image* image, uint numLines, uint numCols) :
    image(image),
    columns(numCols),
    size(numLines* numCols)
{
    width = image->Width() / numCols;
    height = image->Height() / numLines;
}

// -------------------------------------------------------------------------------

TileSet::~TileSet()
{
    // libera mem�ria ocupada pela imagem
    if (image)
    {
         delete image;
    }
}

// -------------------------------------------------------------------------------