// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
	Animation * backg = nullptr;   // plano de fundo
	Player * player = nullptr;	// jogador
	bool ctrlKeyESC = false;	// controle de saída na tela inicial

public:
	static Scene* scene;           // gerenciador de cena

	void Init();                    // inicialização
	void Update();                  // atualização
	void Draw();                    // desenho
	void Finalize();                // finalização
};

// -----------------------------------------------------------------------------
