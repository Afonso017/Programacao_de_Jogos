// ------------------------------------------------------------------------------
// Inclusões

#include <iostream>
#include "Enemy.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Enemy::InitializeBBox() {
    BBox(new Rect(x - walking->TileWidth() / 5.0f,
        y - walking->TileHeight() / 5.0f,
        x + walking->TileWidth() / 5.0f,
        y + walking->TileHeight() / 5.0f));
}

// ------------------------------------------------------------------------------

// Construtor da classe Enemy
Enemy::Enemy(float width, float height, Background* backg, Character* player)
    : width(width), height(height), backg(backg), player(player), walking(nullptr), anim(nullptr) {

	// --------------------------------------------------------------------------------------------
    // Inicializa as variáveis de estado do inimigo

    enemyState = WALKLEFT;        // Estado inicial do inimigo
    type = ENEMY;                 // Tipo do inimigo
    isHit = false;                // Flag para indicar se o inimigo foi atingido

	// --------------------------------------------------------------------------------------------
    // Inicializa as variáveis de movimentação do inimigo

    interpolationSpeed = 18.0f;   // Velocidade de interpolação
    VelX = width;                 // Velocidade horizontal do inimigo (em pixels por frame)
    VelY = height;                // Velocidade vertical do inimigo (em pixels por frame)
    targetX = x;                  // Posição X do destino do inimigo pós-movimento
    targetY = y;                  // Posição Y do destino do inimigo pós-movimento
    newX = x;                     // Nova posição X do inimigo
    newY = y;                     // Nova posição Y do inimigo
    prevX = x;                    // Posição X anterior do inimigo
    prevY = y;                    // Posição Y anterior do inimigo

	// --------------------------------------------------------------------------------------------
    // Inicializa variáveis de sprites e animação
    // (Inicialização específica é feita nas subclasses)

	// --------------------------------------------------------------------------------------------
    // Inicializa variáveis auxiliares

    proximityThreshold = 100.0f; // Distância para começar a perseguir o jogador

	// --------------------------------------------------------------------------------------------
    // Inicializa atributos básicos do inimigo

    level = 1;                    // Nível do inimigo

    // (Vida e dano de ataque são definidos nas subclasses)

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
        HandleMovement(); // Atualiza a movimentação do inimigo
    }

    InterpolateMovement(gameTime);  // Interpola o movimento do inimigo
    UpdateAnimation();              // Atualiza a animação do inimigo
    ConstrainToScreen();           // Garante que o inimigo não ultrapasse os limites da tela
}

// ------------------------------------------------------------------------------

// Move o inimigo aleatoriamente
void Enemy::MoveRandomly() {
    int direction = rand() % 4;          // 4 direções possíveis
    switch (direction) {
    case 0: targetX = X() + VelX; break; // Move para a direita
    case 1: targetX = X() - VelX; break; // Move para a esquerda
    case 2: targetY = Y() + VelY; break; // Move para baixo
    case 3: targetY = Y() - VelY; break; // Move para cima
    default: break;                      // Fica parado
    }
}

// ------------------------------------------------------------------------------

// Lida com a movimentação do inimigo
void Enemy::HandleMovement() {
	isHit = true;   // Indica que o inimigo pode atacar o jogador
	prevX = X();    // Armazena a posição X anterior
	prevY = Y();    // Armazena a posição Y anterior

    float deltaX = player->X() - X();                           // Distância em X para o jogador
    float deltaY = player->Y() - Y();                           // Distância em Y para o jogador
    float distanceSquared = deltaX * deltaX + deltaY * deltaY;  // Distância ao quadrado (para eficiência)

    if (distanceSquared < proximityThreshold * proximityThreshold) {
        // 85% de chance de mover na direção do jogador
        if (rand() % 100 < 85) {
            MoveTowardsPlayer(deltaX, deltaY);
        }
        else {
            // 15% de chance de mover aleatoriamente
            MoveRandomly();
        }
    }
    else {
        // Se o jogador está longe, move aleatoriamente
        MoveRandomly();
    }
}

// ------------------------------------------------------------------------------

// Interpola o movimento do inimigo com base no tempo do jogo
void Enemy::InterpolateMovement(float gameTime) {
    newX = X() + (targetX - X()) * interpolationSpeed * gameTime;
    newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;

    // Ajusta a nova posição se estiver muito perto do alvo
    if (abs(targetX - newX) < 0.5f) newX = targetX;
    if (abs(targetY - newY) < 0.5f) newY = targetY;

    MoveTo(newX, newY); // Move o inimigo para a nova posição
}

// ------------------------------------------------------------------------------

// Atualiza a animação do inimigo
void Enemy::UpdateAnimation() {
    anim->Select(enemyState); // Seleciona o estado atual da animação
    anim->NextFrame();       // Avança para o próximo frame da animação
}

// ------------------------------------------------------------------------------

// Garante que o inimigo não ultrapasse os limites da tela
void Enemy::ConstrainToScreen() {
    float diff = 0.067f * backg->Width(); // Margem para a borda da tela

    // Limita a posição X do inimigo
    if (x + width / 2.0f > window->CenterX() + backg->Width() / 2.0f - diff + 8.0f) {
        Translate(-4, 0);
        targetX = newX = window->CenterX() + backg->Width() / 2.0f - diff - width / 2.0f;
    }
    else if (x - width / 2.0f < window->CenterX() - backg->Width() / 2.0f + diff - 8.0f) {
        Translate(4, 0);
        targetX = newX = window->CenterX() - backg->Width() / 2.0f + diff + width / 2.0f;
    }

    // Limita a posição Y do inimigo
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

// Move o inimigo em direção ao jogador com base nas diferenças de posição
void Enemy::MoveTowardsPlayer(float deltaX, float deltaY) {
	// Se a diferença em X for maior que a diferença em Y (em valor absoluto) 
	// o inimigo se move horizontalmente, caso contrário, se move verticalmente
    if (abs(deltaX) > abs(deltaY)) {    
        // Move horizontalmente
		if (deltaX > 0) {    // Delta X positivo significa que o jogador está à direita
            targetX += VelX; // Move para a direita
        }
		else {               // Delta X negativo significa que o jogador está à esquerda
            targetX -= VelX; // Move para a esquerda
        }
    }
    else {
        // Move verticalmente
		if (deltaY > 0) {    // Delta Y positivo significa que o jogador está abaixo
            targetY += VelY; // Move para baixo
        }
		else {               // Delta Y negativo significa que o jogador está acima
            targetY -= VelY; // Move para cima
        }
    }
}

// ------------------------------------------------------------------------------