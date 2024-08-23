// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Background.h"
#include "Warrior.h"
#include "Ghost.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	Warrior* warrior;		// instancia do jogador (classe guerreiro)
	Background * backg   = nullptr;	// background principal
	Sprite * backg2  = nullptr;		// background
	boolean  viewBox = false;		// controle de visualiza��o de caixas de colis�o
	Scene* scene;					// gerenciador de cena
	Ghost* ghost;					// instancia do inimigo (classe fantasma)

public:

	int  Width();                   // retorna a largura atual da janela
	int  Height();                  // retorna a altura atual da janela

	void Init();					// inicializa��o
	void Update();					// atualiza��o
	void Draw();					// desenho
	void Finalize();				// finaliza��o
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
