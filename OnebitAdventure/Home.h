// ------------------------------------------------------------------------------
// Inclus�es

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
	bool ctrlKeyESC = false;	// controle de sa�da na tela inicial

public:
	static Scene* scene;           // gerenciador de cena

	void Init();                    // inicializa��o
	void Update();                  // atualiza��o
	void Draw();                    // desenho
	void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------
