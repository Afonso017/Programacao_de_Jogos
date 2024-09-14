// Level1.h

#ifndef LEVEL1_H
#define LEVEL1_H

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Character.h"
#include "Hud.h"
#include "Map.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	bool viewBox = false;			// controle de visualização de caixas de colisão

public:
	static Scene * scene;			// gerenciador de cena
	static Hud * hud;				// gerenciador do hud do jogo
	static Map * map;				// gerenciador do mapa do jogo
	static Character * player;		// instancia do jogador (classe guerreiro)

	void Init();					// inicialização
	void Update();					// atualização
	void Draw();					// desenho
	void Finalize();				// finalização
};

// -----------------------------------------------------------------------------

#endif // LEVEL1_H
