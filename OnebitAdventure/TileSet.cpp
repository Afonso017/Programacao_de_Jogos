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

TileSet::TileSet(string filename, uint imgWidth, uint imgHeight, uint tileWidth, uint tileHeight, uint numCols, uint numTiles) :
    image(new Image(filename, imgWidth, imgHeight)), 
    width(tileWidth), 
    height(tileHeight), 
    columns(numCols),    
    size(numTiles)
{
    localImage = true;
}

// -------------------------------------------------------------------------------

TileSet::TileSet(Image* img, uint tileWidth, uint tileHeight, uint numCols, uint numTiles) :
    image(img),
    width(tileWidth),
    height(tileHeight),
    columns(numCols),
    size(numTiles)
{
    localImage = false;
}

// -------------------------------------------------------------------------------

TileSet::TileSet(string filename, uint numLines, uint numCols) :
    image(new Image(filename)),
    columns(numCols),
    size(numLines* numCols)
{
    width = image->Width() / numCols;
    height = image->Height() / numLines;
    localImage = true;
}

// -------------------------------------------------------------------------------

TileSet::TileSet(Image* image, uint numLines, uint numCols) :
    image(image),
    columns(numCols),
    size(numLines* numCols),
    localImage(localImage)
{
    width = image->Width() / numCols;
    height = image->Height() / numLines;
    localImage = false;
}

// -------------------------------------------------------------------------------

TileSet::~TileSet()
{
    // libera mem�ria ocupada pela imagem
    if (localImage)
         delete image;
}

// -------------------------------------------------------------------------------
