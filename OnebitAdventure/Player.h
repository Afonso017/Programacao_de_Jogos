// ------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Timer.h"

// ------------------------------------------------------------------------------

enum PlayerState { STILL, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT };

// Os casos WALKUp,WALKDOWN e STILL são os únicos que não precisam de um sprite de costas e de frente.
// Logo, são opcionais, coloquei apenas para o caso de precisar.
// Como o personagem em estado STILL é o mesmo que o personagem em estado WALKRIGHT, não é necessário esse estado, mas... né.

// ------------------------------------------------------------------------------

class Player : public Object
{
private:
	TileSet * walking;                  // folha de sprites do personagem
	Animation * anim;                   // animação do personagem
	PlayerState state = WALKLEFT;       // estado atual do jogador
	Timer * timer = nullptr;			// timer para limitar o movimento do jogador
	boolean isMoving = false;			// controle para movimento do jogador
	float VelX;							// velocidade horizontal do jogador
	float VelY;							// velocidade vertical do jogador
	int width;							// largura da tela do jogo
	int height;							// altura da tela do jogo
	int targetX;						// posição x do destino do jogador
	int targetY;						// posição y do destino do jogador

public:
	Player(int width, int height);      // construtor
	~Player();                          // destrutor
	
	void OnCollision(Object* obj);      // resolução da colisão
	void Update();                      // atualização
	void Draw();                        // desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{
	anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
