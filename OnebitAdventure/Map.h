#ifndef MAP_H
#define MAP_H

// ------------------------------------------------------------------------------

#include "Types.h"
#include "Image.h"
#include <vector>

// ------------------------------------------------------------------------------

enum Biome // Tipo do chunk (cada chunk é um bioma diferente)
{
	FIELD, FOREST, RUIN
};

// ------------------------------------------------------------------------------

class Map
{
private:
	// Propriedades do mapa
	static const int propsLength = 15;					// Número de props
	Image* images[propsLength];							// Vetor de imagens de props
	int chunkSize;										// Tamanho do chunk
	int lastPos;										// Posição do último prop desenhado

public:

	Map(uint seed);
	~Map();

	void Generate();						// Gera um chunk
};

// ------------------------------------------------------------------------------

#endif // MAP_H
