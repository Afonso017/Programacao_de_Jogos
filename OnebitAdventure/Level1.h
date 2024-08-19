// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	Scene * scene;				// gerenciador de cena
	Player* player = nullptr;	// jogador
	Sprite* backg = nullptr;    // background
	Sprite* backg2 = nullptr;   // background

public:
	int  Width();                                           // retorna a largura atual da janela
	int  Height();                                          // retorna a altura atual da janela

	void Init();                // inicializa��o
	void Update();              // atualiza��o
	void Draw();                // desenho
	void Finalize();            // finaliza��o
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
