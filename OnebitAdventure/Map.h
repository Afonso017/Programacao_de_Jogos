#pragma once
#ifndef MAP_H
#define MAP_H

// ------------------------------------------------------------------------------
// Inclus�es

#include "Object.h"
#include "Prop.h"
#include <queue>
#include <vector>
using std::vector;
using std::deque;

// ------------------------------------------------------------------------------

class Map: public Object {
private:
	// Propriedades do mapa
	deque<vector<Prop>> linesMap;									// Lista de props (Ah ideia � ter (20 vetores com no m�ximo 11 props)
	float width;													// Largura do mapa
	float height;													// Altura do mapa
	boolean nextChunk;												// Flag para indicar que o jogador passou de chunk

public:
	Map(float tileWidth, float tileHeight);
	~Map();

	void Draw();
	void Update();
	// Outros atributos como elementos do mapa
};

// ------------------------------------------------------------------------------

void Map::Draw() {
	// La�o que percorre a lista de LinesMap desenhando cada prop de cada vetor
	for (auto& vec : linesMap) {
		for (auto& prop : vec) {
			prop.Draw();  // Chama o m�todo Draw de cada Prop
		}
	}
}

// ------------------------------------------------------------------------------

#endif // MAP_H