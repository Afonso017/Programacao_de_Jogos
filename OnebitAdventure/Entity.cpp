#include "Entity.h"
#include "Level1.h"
#include <cmath>

Entity::Entity()
    : deltaX(0), deltaY(0), distance(0),
    newX(0), newY(0), limiarDist(0), pullStrength(0),
    life(0), maxLife(0), attack(0), defense(0),
	vx(0), vy(0), targetX(0), targetY(0), prevX(0), prevY(0), damage(0)
{
    width = Level1::hud->tileWidth;
    height = Level1::hud->tileHeight;

    limiar = window->CenterY();

    speed = 225.0f;
    isMoving = false;

    // Raio de distância na qual começa a desaceleração
    slowDownRadius = width * 0.3f;  // Desacelera a 30% da largura do personagem

    targetX = prevX = x;
    targetY = prevY = y;
}

Entity::~Entity()
{
}

void Entity::Movement()
{
    // Calcular a distância até o destino (magnitude)
    distance = sqrt((targetX - x) * (targetX - x) + (targetY - y) * (targetY - y));

    // Se a distância for muito pequena, considere que a entidade chegou ao destino
    if (distance < 0.05f) {
        MoveTo(targetX, targetY);
        return;
    }

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
