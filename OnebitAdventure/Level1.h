// Level1.h

#ifndef LEVEL1_H
#define LEVEL1_H

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Hud.h"
#include "Enemy.h"
#include "Scene.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	bool viewBox = false;				// controle de visualização de caixas de colisão
	int progress = 0;					// Variável para contar o progresso do player!

public:
	static Character * player;		// instancia do jogador (classe guerreiro)
	static Enemy * enemy;			// instância do inimigo (classe fantasma)
	static Hud * hud;				// classe que gerencia o hud do jogo
	static Scene * scene;			// gerenciador de cena

	void Init();					// inicialização
	void Update();					// atualização
	void Draw();					// desenho
	void Finalize();				// finalização
};

// -----------------------------------------------------------------------------

#endif // LEVEL1_H
