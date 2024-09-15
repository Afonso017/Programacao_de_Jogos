// Character.h

#ifndef CHARACTER_H
#define CHARACTER_H

// ------------------------------------------------------------------------------

#include "Types.h"
#include "Entity.h"
#include "Animation.h"
#include "Font.h"
#include <string>
#include <unordered_map>

// ------------------------------------------------------------------------------
// Classe Character : É a classe base para todos os personagens (classes) do jogo

class Character : public Entity
{
protected:
	// TileSet e animação
	TileSet* walking = nullptr;         // folha de sprites do personagem
	Animation* anim = nullptr;          // animação do personagem

	// Objetos auxiliares para construções de lógicas
	Timer* timer;						// timer para controlar o tempo de exibição do texto
	Timer* attackTimer;					// timer para controlar o tempo de ataque do jogador
	Font* press12;						// fonte para exibir texto na tela
	Sprite* xpBar;						// sprite para representar a experiência do jogador
	std::unordered_map<string, Color> text;  // unordered_map para armazenar o texto a ser exibido na tela

	// Atributos básicos de todo jogador
	int progress;						// quantos tiles andou
	int coins;							// moedas capturadas
	int level;							// nível do jogador
	int xp;								// experiência do jogador
	int maxXp;							// experiência máxima do jogador
	float criticalChance;				// chance de dano crítico

	// --------------------------------------------------------------------------------------------
	// Métodos protegidos 

	void InitializeBBox();									// inicializa a BBox

public:
	Character();											// construtor
	virtual ~Character();									// destrutor

	// Métodos de movimentação e animação
	void HandleInput();										// movimentação do jogador

	// Métodos de recuperação e modificação de atributos
	void SetXp(int xp);										// define a experiência do jogador
	bool IsHit() const;										// verifica se o jogador foi atingido

	// Métodos auxiliares
	void Update();											// atualização
	void Draw();											// desenho
	void DrawTextGet();										// desenha o texto na tela
	void DrawExperienceBar();								// desenha a barra de experiência do jogador
	void DrawLevelAndXp();									// desenha o level e a experiência do jogador
};

// --------------------------------------------------------------------------------------------------
// Métodos Inline

inline bool Character::IsHit() const
{
	return isHit;
}

inline void Character::SetXp(int xp)
{
	this->xp += xp;
}

// -----------------------------------------------------------------------------

#endif // CHARACTER_H
