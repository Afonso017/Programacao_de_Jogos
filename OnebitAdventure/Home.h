// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
	Sprite* backg = nullptr;  // plano de fundo
	bool ctrlKeyESC = false; // controle de saída na tela inicial

public:
	void Init();                    // inicialização
	void Update();                  // atualização
	void Draw();                    // desenho
	void Finalize();                // finalização
};

// -----------------------------------------------------------------------------