// ------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Timer.h"

// ------------------------------------------------------------------------------

enum PlayerState { STILL, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT };

// Os casos WALKUp,WALKDOWN e STILL s�o os �nicos que n�o precisam de um sprite de costas e de frente.
// Logo, s�o opcionais, coloquei apenas para o caso de precisar.
// Como o personagem em estado STILL � o mesmo que o personagem em estado WALKRIGHT, n�o � necess�rio esse estado, mas... n�.

// ------------------------------------------------------------------------------

class Player : public Object
{
private:
	TileSet * walking;                  // folha de sprites do personagem
	Animation * anim;                   // anima��o do personagem
	PlayerState state = WALKLEFT;       // estado atual do jogador
	Timer * timer = nullptr;			// timer para limitar o movimento do jogador
	boolean isMoving = false;			// controle para movimento do jogador
	float VelX;							// velocidade horizontal do jogador
	float VelY;							// velocidade vertical do jogador
	int width;							// largura da tela do jogo
	int height;							// altura da tela do jogo
	int targetX;						// posi��o x do destino do jogador
	int targetY;						// posi��o y do destino do jogador

public:
	Player(int width, int height);      // construtor
	~Player();                          // destrutor
	
	void OnCollision(Object* obj);      // resolu��o da colis�o
	void Update();                      // atualiza��o
	void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{
	anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
