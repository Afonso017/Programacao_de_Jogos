// ------------------------------------------------------------------------------
// Inclusões

#include "Character.h"
#include "Level1.h"
#include <cmath>

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Character::InitializeBBox()
{
    BBox(new Rect(
        x - walking->TileWidth() / 4.0f,
        y - walking->TileHeight() / 4.0f,
        x + walking->TileWidth() / 4.0f,
        y + walking->TileHeight() / 4.0f));
}

// ---------------------------------------------------------------------------------

// construtor para inicializar os atributos genéricos do jogador
Character::Character()
	: Entity(), walking(nullptr), anim(nullptr), timer(nullptr), press12(nullptr)
{
    progress = 0;
    coins = 0;

    movementTime = 0.05f;

    timer = new Timer();
    timer->Start();

    press12 = new Font("Resources/press12.png");
    press12->Spacing("Resources/press12.dat");
}

Character::~Character()
{
    delete press12;
    delete timer;
}

void Character::Update()
{
    HandleInput();

    Entity::CameraMovement();
    Entity::Movement();

    AdjustMovement();

    ConstrainToScreen();

    anim->NextFrame();
}

void Character::HandleInput()
{
    if (window->KeyDown('W') || window->KeyDown(VK_UP)) {
        if (!isMoving) {
            if (timer->Elapsed(movementTime)) {
                prevY = y;
                targetY = y - height;
                isMoving = true;
            }
        }
        else {
            nextMove = WALKUP;
        }
    }
    else if (window->KeyDown('S') || window->KeyDown(VK_DOWN)) {
        if (!isMoving) {
            if (timer->Elapsed(movementTime)) {
                prevY = y;
                targetY = y + height;
                isMoving = true;
            }
        }
        else {
            nextMove = WALKDOWN;
        }
    }
    else if (window->KeyDown('A') || window->KeyDown(VK_LEFT)) {
        if (!isMoving) {
            if (timer->Elapsed(movementTime)) {
                prevX = x;
                targetX = x - width;
                anim->Select(WALKLEFT);
                isMoving = true;
            }
        }
        else {
            nextMove = WALKLEFT;
        }
    }
    else if (window->KeyDown('D') || window->KeyDown(VK_RIGHT)) {   
        if (!isMoving) {
            if (timer->Elapsed(movementTime)) {
                prevX = x;
                targetX = x + width;
                anim->Select(WALKRIGHT);
                isMoving = true;
            }
        }
        else {
            nextMove = WALKRIGHT;
        }
    }
}

void Character::NextMove()
{
    switch (nextMove)
    {
    case WALKUP:
        if (!isMoving && timer->Elapsed(movementTime))
        {
            prevY = y;
            targetY = y - height;
            isMoving = true;
        }
        break;
    case WALKDOWN:
        if (!isMoving && timer->Elapsed(movementTime))
        {
            prevY = y;
            targetY = y + height;
            isMoving = true;
        }
        break;
    case WALKLEFT:
        if (!isMoving && timer->Elapsed(movementTime))
        {
            prevX = x;
            targetX = x - width;
            anim->Select(WALKLEFT);
            isMoving = true;
        }
        break;
    case WALKRIGHT:
        if (!isMoving && timer->Elapsed(movementTime))
        {
            prevX = x;
            targetX = x + width;
            anim->Select(WALKRIGHT);
            isMoving = true;
        }
        break;
    default: break;
    }
    nextMove = STILL;
}

void Character::AdjustMovement()
{
    // Verifica se chegou ao destino com base na velocidade
    // ajusta velocidade horizontal
    if ((vx > 0 && x + vx >= targetX) || (vx < 0 && x + vx <= targetX)) {
        MoveTo(targetX, y);
        prevX = targetX;
        vx = 0;
        isMoving = false;
        timer->Reset();
    }

    // ajusta velocidade vertical
    if ((vy > 0 && y + vy >= targetY) || (vy < 0 && y + vy <= targetY)) {
        MoveTo(x, targetY);
        prevY = targetY;
        vy = 0;
        isMoving = false;
        timer->Reset();
    }

    // Executa o próximo movimento, se houver
    if (!isMoving && nextMove != STILL) {
        NextMove();
    }
}

void Character::ConstrainToScreen()
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

void Character::Draw()
{
    anim->Draw(x, y, z);
}
