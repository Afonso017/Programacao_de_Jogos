// Level1.h

#ifndef LEVEL1_H
#define LEVEL1_H

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Hud.h"
#include "Enemy.h"
#include "Scene.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	bool viewBox = false;				// controle de visualiza��o de caixas de colis�o
	int progress = 0;					// Vari�vel para contar o progresso do player!

public:
	static Character * player;		// instancia do jogador (classe guerreiro)
	static Enemy * enemy;			// inst�ncia do inimigo (classe fantasma)
	static Hud * hud;				// classe que gerencia o hud do jogo
	static Scene * scene;			// gerenciador de cena

	void Init();					// inicializa��o
	void Update();					// atualiza��o
	void Draw();					// desenho
	void Finalize();				// finaliza��o
};

// -----------------------------------------------------------------------------

#endif // LEVEL1_H
