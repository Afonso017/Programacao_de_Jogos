// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

// ------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Background.h"

// ------------------------------------------------------------------------------

enum CharacterState { STILL, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT };

// Os casos WALKUp,WALKDOWN e STILL s�o os �nicos que n�o precisam de um sprite de costas e de frente.
// Logo, são opcionais, coloquei apenas para o caso de precisar.
// Como o personagem em estado STILL � o mesmo que o personagem em estado WALKRIGHT, n�o � necess�rio esse estado, mas... n�.

// ------------------------------------------------------------------------------

class Character : public Object
{
protected:
	// são comuns para todos os personagens e tem o mesmo valor
	CharacterState state;				// estado atual do jogador
	Background* backg;					// background
	float targetX;						// posição x do destino do jogador
	float targetY;						// posição y do destino do jogador
	float interpolationSpeed;			// velocidade de interpolação
	float VelX;							// velocidade horizontal do jogador
	float VelY;							// velocidade vertical do jogador
	uint width;							// largura do Character
	uint height;						// altura do Character

	//--------------------------------------------------------------------------------------------
	// Atributos básicos do jogador

	int vida = 0;						// vida do jogador
	float danoAtaque = 0.0f;			// dano de ataque fisico do jogador (não utiliza mana e todas classes tem)
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem
	
	void InitializeBBox();					// inicializa a BBox
public:
	Character(float width, float height, Background* backg);	// construtor
	~Character();												// destrutor

	//--------------------------------------------------------------------------------------------

	// Métodos virtuais
	virtual void OnCollision(Object* obj) = 0;					// resolução da colisão

	//--------------------------------------------------------------------------------------------

	void Update();											// atualização
	void Draw();											// desenho
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Character::Draw()
{
	anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif // CHARACTER_H