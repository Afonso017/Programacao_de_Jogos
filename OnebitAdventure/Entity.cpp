#include "Entity.h"
#include "Level1.h"
#include <cmath>

Entity::Entity()
    : deltaX(0), deltaY(0), distance(0),
    newX(0), newY(0), limiarDist(0), pullStrength(0),
    life(0), maxLife(0), attack(0), defense(0),
	vx(0), vy(0), targetX(x), targetY(y), prevX(x), prevY(y), damage(0),
	isHit(false), isDead(false), isMoving(false), direction(STILL),
	playerMoved(false)
{
    width = Level1::hud->tileWidth;
    height = Level1::hud->tileHeight;

    limiar = window->CenterY();

	speed = 250.0f;  // Velocidade de movimento

    // Raio de distância na qual começa a desaceleração
    slowDownRadius = width * 0.3f;  // Desacelera a 30% da largura do tile
}

Entity::~Entity()
{
}

void Entity::Move(Direction direction)
{
    this->direction = direction;
    switch (direction)
    {
    case WALKUP:
        prevY = y;
        targetY = y - height;
        break;
    case WALKDOWN:
        prevY = y;
        targetY = y + height;
        break;
    case WALKLEFT:
        prevX = x;
        targetX = x - width;
        break;
    case WALKRIGHT:
        prevX = x;
        targetX = x + width;
        break;
    case STILL:
        targetX = prevX = x;
        targetY = prevY = y;
		break;
    case BACKWARD:
        targetX = prevX;
        targetY = prevY;
        break;
    }
    playerMoved = isHit = true;
}

// O movimento da câmera consiste em aplicar uma força que puxa para baixo todas as entidades,
// dando a ilusão de que o player está subindo
void Entity::CameraMovement()
{
    // Verifica se o player passou do limiar
    if (Level1::player->Y() >= limiar) return;

    // Calcula a distância entre o player e o limiar
    limiarDist = fabs(Level1::player->Y() - limiar);

    // Se o jogador passou do limiar, começa a aplicar a força de gravidade
    if (limiarDist > 0) {
        // A força de puxar aumenta proporcionalmente à distância do limiar
        pullStrength = limiarDist;

        // Aplica essa força para todas as entidades (inclusive o próprio jogador)
        targetY += pullStrength * gameTime;
        prevY += pullStrength * gameTime;
        Translate(0, pullStrength * gameTime);
    }
    else {
        // Se o jogador não está acima do limiar, a força é zero
        pullStrength = 0.0f;
    }
}

void Entity::Movement()
{
    // Calcular a distância até o destino (magnitude)
    distance = sqrt((targetX - x) * (targetX - x) + (targetY - y) * (targetY - y));

    // Se a distância for muito pequena, considere que a entidade chegou ao destino
    if (distance < 0.5f) {
        MoveTo(targetX, targetY);
		prevX = targetX;
        prevY = targetY;
        isMoving = false;
        return;
    }

    isMoving = true;

    // Calcula a direção (vetor unitário)
    deltaX = (targetX - x) / distance;
    deltaY = (targetY - y) / distance;

    float currentSpeed = speed;  // Velocidade ajustada

    // Calcula a velocidade com base na distância euclidiana
    if (distance < slowDownRadius) currentSpeed *= (distance / slowDownRadius);

    // Ajusta a movimentação com base no delta e na força de retorno
    newX = (deltaX != 0) ? (deltaX / fabs(deltaX)) * currentSpeed * gameTime : 0;
    newY = (deltaY != 0) ? (deltaY / fabs(deltaY)) * currentSpeed * gameTime : 0;

    // Calcula a velocidade com base na distância e direção
    vx = deltaX * speed * gameTime;
    vy = deltaY * speed * gameTime;

    // Atualizar a posição com base na velocidade
    Translate(newX, newY);
}

void Entity::ConstrainToScreen()
{
    // Verifica o limite direito
    if (x > Level1::hud->mainRightSide - Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite esquerdo
    if (x < Level1::hud->mainLeftSide + Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite inferior
    if (y > window->Height()) {
        targetY = prevY;
    }
}
