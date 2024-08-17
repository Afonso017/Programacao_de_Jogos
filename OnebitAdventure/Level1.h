// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

// 4 tipos de objeto que terá na cena, o jogador, inimigos, objetos do tipo que pode interagir como baús e obstáculos
enum Types { PLAYER, ENEMY, ITEM, OBSTACLE };

class Level1 : public Game
{
private:
	Scene * scene;				// gerenciador de cena
	Player* player = nullptr;	// jogador

public:
	void Init();                // inicialização
	void Update();              // atualização
	void Draw();                // desenho
	void Finalize();            // finalização
};

// -----------------------------------------------------------------------------
