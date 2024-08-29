// Enemy.h
#pragma once
#ifndef ENEMY_H
#define ENEMY_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Types.h"                      // Tipos específicos da engine
#include "Object.h"                     // Interface base para objetos
#include "Animation.h"                  // Animações de sprites
#include "OneBitAdventure.h"            // Cabeçalhos específicos do jogo
#include "Character.h"                  // Classe base para todos os personagens
#include "Font.h"                       // Fonte para exibir texto na tela

// ------------------------------------------------------------------------------
// Classe Enemy : Representa um inimigo no jogo

class Enemy : public Object
{
protected:
    // --------------------------------------------------------------------------------------------
    // Estados e Flags do Inimigo

    MovementType enemyState;            // Estado atual da animação do inimigo
    bool isHit;                         // Flag que indica se o inimigo já atacou
    DirectingAnimation direction;       // Direção da animação do inimigo

    // --------------------------------------------------------------------------------------------
    // Atributos de Movimentação

    float interpolationSpeed;           // Velocidade de interpolação do movimento
    float VelX;                         // Velocidade horizontal do inimigo
    float VelY;                         // Velocidade vertical do inimigo
    float targetX;                      // Posição X do destino após o movimento
    float targetY;                      // Posição Y do destino após o movimento
    float prevX;                        // Posição X anterior do inimigo
    float prevY;                        // Posição Y anterior do inimigo
    float newX;                         // Nova posição X do inimigo
    float newY;                         // Nova posição Y do inimigo
	boolean playerInRange;              // Flag que indica se o jogador está dentro do alcance do inimigo

    // --------------------------------------------------------------------------------------------
    // Atributos de Sprites e Animação

    TileSet* walking = nullptr;         // Folha de sprites do inimigo
    Animation* anim = nullptr;          // Animação do inimigo
    uint width;                         // Largura do inimigo
    uint height;                        // Altura do inimigo
    Sprite* life;                       // Animação para representar a vida do inimigo
    Sprite* hudLife;                    // Sprite para representar a vida do inimigo

    // --------------------------------------------------------------------------------------------
    // Objetos Auxiliares

    float distance;                     // Distância entre o inimigo e o jogador
    float deltaX;                       // Distância em X para o jogador
    float deltaY;                       // Distância em Y para o jogador
    float proximityThreshold;           // Distância para iniciar a perseguição ao jogador
    Font* press12;					    // fonte para exibir texto na tela

    // --------------------------------------------------------------------------------------------
    // Atributos Básicos do Inimigo

    int danoAtaque = 0;                 // Dano de ataque físico do inimigo
    int vida = 0;                       // Vida do inimigo
    int vidaMax = 0;                    // Vida máxima do inimigo
    int level;                          // Nível do inimigo
    string name; 				        // nome do inimigo apenas para identificar

    // --------------------------------------------------------------------------------------------
    // Métodos Protegidos 

    void InitializeBBox();              // Inicializa a caixa de colisão (BBox)
    void MoveRandomly();                // Move o inimigo aleatoriamente

public:
    // --------------------------------------------------------------------------------------------
    // Construtor e Destrutor

    Enemy(float width, float height);   // Construtor
    virtual ~Enemy() = 0;               // Destrutor virtual puro

    // --------------------------------------------------------------------------------------------
    // Métodos Virtuais Puras

    virtual void OnCollision(Object* obj) = 0;  // Resolução de colisão com outros objetos

    // --------------------------------------------------------------------------------------------
    // Sobrescrita de Métodos Virtuais de Object

    float X() const override;           // Obtém a coordenada X do inimigo
    float Y() const override;           // Obtém a coordenada Y do inimigo
    float Z() const override;           // Obtém a coordenada Z do inimigo

    // --------------------------------------------------------------------------------------------
    // Métodos de Movimentação e Animação

    void HandleMovement();                              // Lógica de movimentação do inimigo
    void InterpolateMovement(float gameTime);           // Interpola o movimento do inimigo
    void UpdateAnimation();                             // Atualiza a animação do inimigo
    void ConstrainToScreen();                           // Garante que o inimigo permaneça dentro da tela
    void MoveTowardsPlayer(float deltaX, float deltaY); // Movimenta o inimigo em direção ao jogador
    void DisplayEnemyHealth();                          // Exibe a vida do inimigo na tela

    // --------------------------------------------------------------------------------------------
    // Métodos de Recuperação e Modificação de Atributos

    int GetDamage() const;           // Retorna o dano de ataque do inimigo
    void SetVida(int damage);        // Modifica a vida do inimigo
    int GetVida() const;             // Retorna a vida do inimigo
    float GetTargetX() const;        // Retorna a posição X do destino do inimigo
    float GetTargetY() const;        // Retorna a posição Y do destino do inimigo
    float GetPrevX() const;          // Retorna a posição X anterior do inimigo
    float GetPrevY() const;          // Retorna a posição Y anterior do inimigo
    float GetVelX() const;           // Retorna a velocidade horizontal do inimigo
    float GetVelY() const;           // Retorna a velocidade vertical do inimigo
    float GetDistance() const;       // Retorna a distância entre o inimigo e o jogador
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

// ---------------------------------------------------------------------------------

inline int Enemy::GetDamage() const
{
    return danoAtaque;    // Retorna o dano de ataque do inimigo
}

// ---------------------------------------------------------------------------------

inline void Enemy::SetVida(int damage)
{
    vida -= damage;      // Reduz a vida do inimigo com base no dano recebido
}

// ---------------------------------------------------------------------------------

inline int Enemy::GetVida() const
{
    return vida;         // Retorna a vida atual do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetTargetX() const
{
    return targetX;     // Retorna a posição X do destino do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetTargetY() const
{
    return targetY;     // Retorna a posição Y do destino do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetPrevX() const
{
    return prevX;      // Retorna a posição X anterior do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetPrevY() const
{
    return prevY;      // Retorna a posição Y anterior do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetVelX() const
{
    return VelX;       // Retorna a velocidade horizontal do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetVelY() const
{
    return VelY;       // Retorna a velocidade vertical do inimigo
}

// ---------------------------------------------------------------------------------

inline float Enemy::GetDistance() const
{
    return distance;   // Retorna a distância entre o inimigo e o jogador
}

// ---------------------------------------------------------------------------------

inline bool Enemy::IsHit() const
{
    return isHit;     // Retorna se o inimigo foi atingido
}

// ---------------------------------------------------------------------------------
// Métodos Inline Sobrescritos de Object

inline float Enemy::X() const
{
    return x;         // Retorna a coordenada X do inimigo (ou pode modificar se a lógica de posição for diferente)
}

inline float Enemy::Y() const
{
    return y;         // Retorna a coordenada Y do inimigo (ou pode modificar se a lógica de posição for diferente)
}

inline float Enemy::Z() const
{
    return z;         // Retorna a coordenada Z do inimigo (ou pode modificar se a lógica de posição for diferente)
}

#endif // ENEMY_H