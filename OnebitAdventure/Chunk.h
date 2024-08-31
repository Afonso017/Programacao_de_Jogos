// ------------------------------------------------------------------------------
// Inclusões

#include <vector>
#include "Prop.h"

// ------------------------------------------------------------------------------

class Chunk {
private:
    int width;
    int height;
    std::vector<Prop> props;

public:

    Chunk(int width, int height);
    void generateChunk();
    void draw();
    // Outros atributos como elementos do mapa
};

// ------------------------------------------------------------------------------