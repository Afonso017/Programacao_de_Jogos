// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

// 4 tipos de objeto que ter� na cena, o jogador, inimigos, objetos do tipo que pode interagir como ba�s e obst�culos
enum Types { PLAYER, ENEMY, ITEM, OBSTACLE };

class Level1 : public Game
{
private:
	Scene * scene;				// gerenciador de cena
	Player* player = nullptr;	// jogador

public:
	void Init();                // inicializa��o
	void Update();              // atualiza��o
	void Draw();                // desenho
	void Finalize();            // finaliza��o
};

// -----------------------------------------------------------------------------
