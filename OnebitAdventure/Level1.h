// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Background.h"
#include "Warrior.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	Warrior* warrior;		// instancia do jogador (classe guerreiro)
	Background * backg   = nullptr;	// background principal
	Sprite * backg2  = nullptr;		// background
	boolean  viewBox = false;		// controle de visualização de caixas de colisão
	Scene* scene;					// gerenciador de cena

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
