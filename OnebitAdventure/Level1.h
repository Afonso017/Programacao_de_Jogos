// Inclusões

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

	void Init();                // inicialização
	void Update();              // atualização
	void Draw();                // desenho
	void Finalize();            // finalização
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
