// Level1.h

#ifndef LEVEL1_H
#define LEVEL1_H

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Character.h"
#include "Hud.h"
#include "Map.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	bool viewBox = false;			// controle de visualiza��o de caixas de colis�o

public:
	static Scene * scene;			// gerenciador de cena
	static Hud * hud;				// gerenciador do hud do jogo
	static Map * map;				// gerenciador do mapa do jogo
	static Character * player;		// instancia do jogador (classe guerreiro)

	void Init();					// inicializa��o
	void Update();					// atualiza��o
	void Draw();					// desenho
	void Finalize();				// finaliza��o
};

// -----------------------------------------------------------------------------

#endif // LEVEL1_H
