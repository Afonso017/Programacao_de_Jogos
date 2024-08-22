// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Background.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	Scene  * scene;					// gerenciador de cena
	Player * player  = nullptr;		// jogador
	Background * backg   = nullptr;	// background principal
	Sprite * backg2  = nullptr;		// background
	boolean  viewBox = false;		// controle de visualização de caixas de colisão

public:
	int  Width();                   // retorna a largura atual da janela
	int  Height();                  // retorna a altura atual da janela

	void Init();					// inicialização
	void Update();					// atualização
	void Draw();					// desenho
	void Finalize();				// finalização
};

// -----------------------------------------------------------------------------

// retorna a largura atual da janela
inline int Level1::Width()
{
	return backg->Width();
}

// retorna a altura atual da janela
inline int Level1::Height()
{
	return backg->Height();
}

// -----------------------------------------------------------------------------
