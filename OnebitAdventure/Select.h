// ------------------------------------------------------------------------------
// Inclusões

#include "Sprite.h"

// ------------------------------------------------------------------------------

class Select : public Game
{
private:
	Sprite* backg = nullptr;   // plano de fundo

public:
	void Init();                // inicialização
	void Update();              // atualização
	void Draw();                // desenho
	void Finalize();            // finalização
};

// ------------------------------------------------------------------------------
