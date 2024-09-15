// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Types.h"                      // Tipos específicos da engine
#include "Entity.h"                     // Interface base para objetos
#include "OneBitAdventure.h"            // Cabecalho principal do jogo
#include "Animation.h"                  // Animações de sprites
#include "Font.h"                       // Fonte para exibir texto na tela
#include "TileSet.h"                    // Folha de sprite
#include "Level1.h"
#include <string>                       // Biblioteca para manipulação de strings

// ------------------------------------------------------------------------------
// Classe Enemy : Representa um inimigo no jogo

class Enemy : public Entity
{
protected:
    // --------------------------------------------------------------------------------------------
    // Estados e Flags do Inimigo

    MovementType enemyState;            // Estado atual da animação do inimigo

    // --------------------------------------------------------------------------------------------
    // Atributos de Sprites e Animação

    TileSet* walking = nullptr;         // Folha de sprites do inimigo
    Animation* anim = nullptr;          // Animação do inimigo
    Sprite* lifeSprite;                 // Animação para representar a vida do inimigo
    Sprite* hudLife;                    // Sprite para representar a vida do inimigo

    // --------------------------------------------------------------------------------------------
    // Objetos Auxiliares

    float playerDistance;               // distância do inimigo para o jogador
    float proximityThreshold;           // Distância para iniciar a perseguição ao jogador
    Font* press12;					    // fonte para exibir texto na tela

    // --------------------------------------------------------------------------------------------
    // Atributos Básicos do Inimigo

    int level;                          // Nível do inimigo
    string name; 				        // nome do inimigo apenas para identificar

    // --------------------------------------------------------------------------------------------
    // Métodos Protegidos 

    void InitializeBBox();              // Inicializa a caixa de colisão (BBox)
    void MoveRandomly();                // Move o inimigo aleatoriamente
	void HandleMovement();			    // Controla a movimentação do inimigo
    float PlayerDistance();             // Calcula a distância até o jogador

public:
    // --------------------------------------------------------------------------------------------
    // Construtor e Destrutor

    Enemy();   // Construtor
    virtual ~Enemy() = 0;               // Destrutor virtual puro

    // --------------------------------------------------------------------------------------------
    // Métodos Virtuais Puras

    virtual void OnCollision(Object* obj) = 0;  // Resolução de colisão com outros objetos

    // --------------------------------------------------------------------------------------------
    // Métodos de Movimentação e Animação

    void UpdateAnimation();                             // Atualiza a animação do inimigo
    void MoveTowardsPlayer();                           // Movimenta o inimigo em direção ao jogador
    void DisplayEnemyHealth();                          // Exibe a vida do inimigo na tela

    // --------------------------------------------------------------------------------------------
    // Métodos de Recuperação e Modificação de Atributos

    bool IsHit() const;              // Verifica se o inimigo foi atingido

    // --------------------------------------------------------------------------------------------
    // Métodos Principais

    void Update();                   // Atualiza o estado e a movimentação do inimigo
    void Draw();                     // Desenha o inimigo na tela
	void DrawHealthBar();            // Desenha a barra de vida do inimigo 
	void DrawHealthText();           // Desenha o texto de vida do inimigo
	void DrawLevel();                // Desenha o nível do inimigo
	void DrawName();                 // Desenha o nome do inimigo    
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Enemy::Draw() {
    anim->Draw(x, y, z);  // Desenha a animação do inimigo na posição (x, y, z)
}

inline bool Enemy::IsHit() const
{
    return isHit;     // Retorna se o inimigo foi atingido
}

inline float Enemy::PlayerDistance()
{
    float deltaX = Level1::player->X() - x;
    float deltaY = Level1::player->Y() - y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

// ---------------------------------------------------------------------------------

#endif // ENEMY_H
