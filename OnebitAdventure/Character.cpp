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
    : Entity(), walking(nullptr), anim(nullptr), timer(nullptr)
{
    timer = new Timer();
    attackTimer = new Timer();

    press12 = new Font("Resources/press12.png");
    press12->Spacing("Resources/press12.dat");

    xpBar = new Sprite("Resources/xpBar.png", 387.0f, 5.0f);

    progress = 0;
    coins = 0;
    level = 1;
    maxXp = 60 + (6 * (level - 1));
    xp = 56;
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
    delete xpBar;
    delete press12;
    delete attackTimer;
    delete timer;
}

// ---------------------------------------------------------------------------------

void Character::Update()
{
    HandleInput();              // Define a direção de movimento

    CameraMovement();           // Aplica a movimentação da câmera
    Movement();                 // Executa a movimentação

	ConstrainToScreen();        // Limita o personagem à tela

	anim->NextFrame();          // Atualiza a animação

	// Atualiza estado de vida do jogador
    if (life <= 0)
    {
        // Cria o TileSet de morte
        walking = new TileSet("Resources/morte.png", width, height, width, height, 1, 1);
        anim = new Animation(walking, 0.125f, true);		   //
        isDead = true;										   // foi de base
    }
}

// ---------------------------------------------------------------------------------

void Character::HandleInput()
{
    // Ignora a movimentação se estiver morto ou já estiver se movendo
    if (isDead || isMoving)
        return;

    if ((window->KeyDown('W') || window->KeyDown(VK_UP))) {
        Move(WALKUP);
    }
    else if ((window->KeyDown('S') || window->KeyDown(VK_DOWN))) {
        Move(WALKDOWN);
    }
    else if ((window->KeyDown('A') || window->KeyDown(VK_LEFT))) {
        Move(WALKLEFT);
        anim->Select(WALKLEFT);
    }
    else if ((window->KeyDown('D') || window->KeyDown(VK_RIGHT))) {
        Move(WALKRIGHT);
        anim->Select(WALKRIGHT);
    }
}

// ---------------------------------------------------------------------------------

void Character::Draw()
{
    anim->Draw(x, y, z);

    DrawTextGet();
    DrawExperienceBar();
    DrawLevelAndXp();
}

// ---------------------------------------------------------------------------------

void Character::DrawTextGet()
{
    if (!text.empty() && !timer->Elapsed(0.7f)) {
        int i = 40;
        for (auto& it : text) {
            press12->Draw(x, y - i, it.first, it.second, Layer::FRONT, 1.0f);
            i += 40;
        }
    }
    else {
        text.clear();
    }
}

// ---------------------------------------------------------------------------------

void Character::DrawExperienceBar()
{
    // Calcula a porcentagem de xp atual em relação ao máximo
    float percent = (float)xp / maxXp;

    // Calcula a largura da barra de vida atual
    float currentWidth = 387.0f * percent;

    // Percentuais para a posição desejada
    float xPercent = 0.50f;		// 50% da largura da tela
    float yPercent = 0.886f;	// 88.6% da altura da tela

    // Calcula a posição X e Y com base nas dimensões da tela
    float definirX = window->Width() * xPercent;
    float definirY = window->Height() * yPercent;

    // Calcula o offset para centralizar a barra de vida
    float offset = definirX - (387.0f - currentWidth) / 2;

    // Desenha a barra de experiência do jogador
    xpBar->DrawResize(offset, definirY, currentWidth, 5.0f);
}

// ---------------------------------------------------------------------------------

void Character::DrawLevelAndXp()
{
    // Percentuais para a posição desejada
    float xPercent = 0.475f;	// 47.5% da largura da tela
    float yPercent = 0.886f;	// 88.6% da altura da tela

    // Calcula a posição X e Y com base nas dimensões da tela
    float definirX = window->Width() * xPercent;
    float definirY = window->Height() * yPercent;

    press12->Draw(definirX - (9 + level % 10), definirY - 45, "Nv:" + std::to_string(level), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.2f);
    press12->Draw(definirX, definirY - 25, std::to_string(xp) + "/" + std::to_string(maxXp), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f);
}

// ---------------------------------------------------------------------------------
