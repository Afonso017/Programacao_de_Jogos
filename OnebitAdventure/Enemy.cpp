// ------------------------------------------------------------------------------
// Inclus�es

#include <iostream>
#include "Enemy.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colis�o
void Enemy::InitializeBBox() {
    BBox(new Rect(x - walking->TileWidth() / 5.0f,
        y - walking->TileHeight() / 5.0f,
        x + walking->TileWidth() / 5.0f,
        y + walking->TileHeight() / 5.0f));
}

// ------------------------------------------------------------------------------

// Construtor da classe Enemy
Enemy::Enemy(float width, float height)
    : width(width), height(height), walking(nullptr), anim(nullptr) {

	// --------------------------------------------------------------------------------------------
    // Inicializa as vari�veis de estado do inimigo

    enemyState = WALKLEFT;        // Estado inicial do inimigo
    type = ENEMY;                 // Tipo do inimigo
    isHit = false;                // Flag para indicar se o inimigo foi atingido

	// --------------------------------------------------------------------------------------------
    // Inicializa as vari�veis de movimenta��o do inimigo

    interpolationSpeed = 25.0f;   // Velocidade de interpola��o (Fazendo testes com os inimigos sendo mais r�pidos que o player)
    VelX = width;                 // Velocidade horizontal do inimigo (em pixels por frame)
    VelY = height;                // Velocidade vertical do inimigo (em pixels por frame)
    targetX = x;                  // Posi��o X do destino do inimigo p�s-movimento
    targetY = y;                  // Posi��o Y do destino do inimigo p�s-movimento
    prevX = x;                    // Posi��o X anterior do inimigo
    prevY = y;                    // Posi��o Y anterior do inimigo
    newX = x;                     // Nova posi��o X do inimigo
    newY = y;                     // Nova posi��o Y do inimigo

	// --------------------------------------------------------------------------------------------
    // Inicializa vari�veis de sprites e anima��o
    // (Inicializa��o espec�fica � feita nas subclasses)

	// --------------------------------------------------------------------------------------------
    // Inicializa vari�veis auxiliares

    proximityThreshold = 150.0f; // Dist�ncia para come�ar a perseguir o jogador

	// --------------------------------------------------------------------------------------------
    // Inicializa atributos b�sicos do inimigo

    level = 1;                    // N�vel do inimigo

    // (Vida e dano de ataque s�o definidos nas subclasses)

	// --------------------------------------------------------------------------------------------
}

// Destrutor da classe Enemy
Enemy::~Enemy() 
{
}

// ------------------------------------------------------------------------------

// Atualiza o estado do inimigo
void Enemy::Update() {
    if (player->IsMoving()) {
        HandleMovement(); // Atualiza a movimenta��o do inimigo
    }

    InterpolateMovement(gameTime);      // Interpola o movimento do inimigo
    UpdateAnimation();                  // Atualiza a anima��o do inimigo
    ConstrainToScreen();                // Garante que o inimigo n�o ultrapasse os limites da tela
}

// ------------------------------------------------------------------------------

// Move o inimigo aleatoriamente
void Enemy::MoveRandomly() {
    int direction = rand() % 7;         // 4 dire��es poss�veis

    switch (direction) {
    case 0: 
        targetX = X() + VelX;           // Move para a direita
		enemyState = WALKRIGHT;
        break; 
    case 1: 
        targetX = X() - VelX;           // Move para a esquerda
		enemyState = WALKLEFT;
        break; 
    case 2: 
        targetY = Y() + VelY; 
		enemyState = WALKDOWN;          // Move para baixo
        break; 
    case 3: 
        targetY = Y() - VelY; 
		enemyState = WALKUP;            // Move para cima
        break;
    default: 
        break;                          // Fica parado
    }
}

// ------------------------------------------------------------------------------

// Lida com a movimenta��o do inimigo
void Enemy::HandleMovement() {
	isHit = true;   // Indica que o inimigo pode atacar o jogador
	prevX = X();    // Armazena a posi��o X anterior
	prevY = Y();    // Armazena a posi��o Y anterior

    float deltaX = player->X() - X();                           // Dist�ncia em X para o jogador
    float deltaY = player->Y() - Y();                           // Dist�ncia em Y para o jogador
    float distanceSquared = deltaX * deltaX + deltaY * deltaY;  // Dist�ncia ao quadrado (para efici�ncia)

    if (distanceSquared < proximityThreshold * proximityThreshold) {
        // 85% de chance de mover na dire��o do jogador
        if (rand() % 100 < 85) {
            MoveTowardsPlayer(deltaX, deltaY);
        }
        else {
            // 15% de chance de mover aleatoriamente
            MoveRandomly();
        }
    }
    else {
        // Se o jogador est� longe, move aleatoriamente
        MoveRandomly();
    }
}

// ------------------------------------------------------------------------------

// Interpola o movimento do inimigo com base no tempo do jogo
void Enemy::InterpolateMovement(float gameTime) {
    newX = X() + (targetX - X()) * interpolationSpeed * gameTime;
    newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;

    // Ajusta a nova posi��o se estiver muito perto do alvo
    if (abs(targetX - newX) < 0.99f) newX = targetX;
    if (abs(targetY - newY) < 0.99f) newY = targetY;

    MoveTo(newX, newY); // Move o inimigo para a nova posi��o
}

// ------------------------------------------------------------------------------

// Atualiza a anima��o do inimigo
void Enemy::UpdateAnimation() {
    anim->Select(enemyState); // Seleciona o estado atual da anima��o
    anim->NextFrame();        // Avan�a para o pr�ximo frame da anima��o
}

// ------------------------------------------------------------------------------

// Garante que o inimigo n�o ultrapasse os limites da tela
void Enemy::ConstrainToScreen() {
    float diff = 0.067f * Level1::hud->Width(); // Margem para a borda da tela

    // Limita a posi��o X do inimigo
    if (x + width / 2.0f > window->CenterX() + Level1::hud->Width() / 2.0f - diff + 8.0f) {
        Translate(-4, 0);
        targetX = newX = window->CenterX() + Level1::hud->Width() / 2.0f - diff - width / 2.0f;
    }
    else if (x - width / 2.0f < window->CenterX() - Level1::hud->Width() / 2.0f + diff - 8.0f) {
        Translate(4, 0);
        targetX = newX = window->CenterX() - Level1::hud->Width() / 2.0f + diff + width / 2.0f;
    }

    // Limita a posi��o Y do inimigo
    if (y + walking->TileHeight() / 2.0f > window->Height()) {
        Translate(0, -4);
        targetY = newY = window->Height() - walking->TileHeight() / 2.0f;
    }
    else if (y - walking->TileHeight() / 2.0f < 0) {
        Translate(0, 4);
        targetY = newY = walking->TileHeight() / 2.0f;
    }
}

// ------------------------------------------------------------------------------

// Move o inimigo em dire��o ao jogador com base nas diferen�as de posi��o
void Enemy::MoveTowardsPlayer(float deltaX, float deltaY) {
	// Se a diferen�a em X for maior que a diferen�a em Y (em valor absoluto) 
	// o inimigo se move horizontalmente, caso contr�rio, se move verticalmente
    if (abs(deltaX) > abs(deltaY)) {    
        // Move horizontalmente
		if (deltaX > 0) {    // Delta X positivo significa que o jogador est� � direita
            targetX += VelX; // Move para a direita
			enemyState = WALKRIGHT; // Atualiza o estado do inimigo
        }
		else {               // Delta X negativo significa que o jogador est� � esquerda
            targetX -= VelX; // Move para a esquerda
			enemyState = WALKLEFT; // Atualiza o estado do inimigo
        }
    }
    else {
        // Move verticalmente
		if (deltaY > 0) {    // Delta Y positivo significa que o jogador est� abaixo
            targetY += VelY; // Move para baixo
			enemyState = WALKDOWN; // Atualiza o estado do inimigo
        }
		else {               // Delta Y negativo significa que o jogador est� acima
            targetY -= VelY; // Move para cima
			enemyState = WALKUP; // Atualiza o estado do inimigo
        }
    }
}

// ------------------------------------------------------------------------------