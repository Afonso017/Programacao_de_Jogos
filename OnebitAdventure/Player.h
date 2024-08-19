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
	bool moved;							// controle para movimento do jogador
	float speedHorizontal;				// velocidade horizontal do jogador
	float speedVertical;				// velocidade vertical do jogador
	int width;							// largura da tela do jogo
	int height;							// altura da tela do jogo

public:
	Player(int width, int height);                           // construtor
	~Player();                          // destrutor
	
	void OnCollision(Object* obj);      // resolução da colisão
	void Update();                      // atualização
	void Draw();                        // desenho

	boolean Move();
	// mover o player
	void MoveTo(float px, float py, float layer = Layer::FRONT);	// Sobrecarga do método pai (MoveTo de Object)
	bool Moved() const;					// saber se o player se moveu para mover as outras entidades
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{
	anim->Draw(x, y, z);
}

inline bool Player::Moved() const
{
	return moved;
}

// ---------------------------------------------------------------------------------
