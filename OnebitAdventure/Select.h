// ------------------------------------------------------------------------------
// Inclus�es

#include "Sprite.h"

// ------------------------------------------------------------------------------

class Select : public Game
{
private:
	Sprite* backg = nullptr;   // plano de fundo

public:
	void Init();                // inicializa��o
	void Update();              // atualiza��o
	void Draw();                // desenho
	void Finalize();            // finaliza��o
};

// ------------------------------------------------------------------------------
