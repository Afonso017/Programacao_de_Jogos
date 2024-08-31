// ------------------------------------------------------------------------------
// Inclusões

#include "Object.h"
#include "Prop.h"
#include <list>

// ------------------------------------------------------------------------------

class Map: public Object {
private:
	// Propriedades do mapa
	list<Prop> props;								// Lista de props 20x11
	float width;									// Largura do mapa
	float height;									// Altura do mapa
	boolean nextChunk;								// Flag para indicar que o jogador passou de chunk

public:
	Map(float tileWidth, float tileHeight);
	~Map();

	void generateChunk();
	void draw();
	void Update();
	// Outros atributos como elementos do mapa
};