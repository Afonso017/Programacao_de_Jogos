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

    // Raio de dist�ncia na qual come�a a desacelera��o
    slowDownRadius = width * 0.3f;  // Desacelera a 30% da largura do personagem

    targetX = prevX = x;
    targetY = prevY = y;
}

Entity::~Entity()
{
}

void Entity::Movement()
{
    // Calcular a dist�ncia at� o destino (magnitude)
    distance = sqrt((targetX - x) * (targetX - x) + (targetY - y) * (targetY - y));

    // Se a dist�ncia for muito pequena, considere que a entidade chegou ao destino
    if (distance < 0.05f) {
        MoveTo(targetX, targetY);
        return;
    }

    // Calcula a dire��o (vetor unit�rio)
    deltaX = (targetX - x) / distance;
    deltaY = (targetY - y) / distance;

    float currentSpeed = speed;  // Velocidade ajustada

    // Calcula a velocidade com base na dist�ncia euclidiana
    if (distance < slowDownRadius) currentSpeed *= (distance / slowDownRadius);

    // Ajusta a movimenta��o com base no delta e na for�a de retorno
    newX = (deltaX != 0) ? (deltaX / fabs(deltaX)) * currentSpeed * gameTime : 0;
    newY = (deltaY != 0) ? (deltaY / fabs(deltaY)) * currentSpeed * gameTime : 0;

    // Calcula a velocidade com base na dist�ncia e dire��o
    vx = deltaX * speed * gameTime;
    vy = deltaY * speed * gameTime;

    // Atualizar a posi��o com base na velocidade
    Translate(newX, newY);
}

// O movimento da c�mera consiste em aplicar uma for�a que puxa para baixo todas as entidades,
// dando a ilus�o de que o player est� subindo
void Entity::CameraMovement()
{
    // Verifica se o player passou do limiar
    if (Level1::player->Y() >= limiar) return;

    // Calcula a dist�ncia entre o player e o limiar
    limiarDist = fabs(Level1::player->Y() - limiar);

    // Se o jogador passou do limiar, come�a a aplicar a for�a de gravidade
    if (limiarDist > 0) {
        // A for�a de puxar aumenta proporcionalmente � dist�ncia do limiar
        pullStrength = limiarDist;

        // Aplica essa for�a para todas as entidades (inclusive o pr�prio jogador)
        targetY += pullStrength * gameTime;
        prevY += pullStrength * gameTime;
        Translate(0, pullStrength * gameTime);
    }
    else {
        // Se o jogador n�o est� acima do limiar, a for�a � zero
        pullStrength = 0.0f;
    }
}
