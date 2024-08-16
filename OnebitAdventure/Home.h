// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
	Sprite * backg = nullptr;   // plano de fundo
	Player * player = nullptr;	// jogador
	bool ctrlKeyESC = false;	// controle de saída na tela inicial

public:
	void Init();                    // inicialização
	void Update();                  // atualização
	void Draw();                    // desenho
	void Finalize();                // finalização
};

// -----------------------------------------------------------------------------