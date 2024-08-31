#include "Hud.h"
#include "Level1.h"
#include "Prop.h"
#include <fstream>
using namespace std;

// ---------------------------------------------------------------------------------

Hud::Hud(float tileWidth, float tileHeight, float offset) : tw(tileWidth), th(tileHeight), offset(offset)
{
    // Background tem 1/3 da largura da janela e 4x a altura da janela
    width = window->Width() / 3.0f + (2 * offset);
    height = window->Height();

    // Carrega mapa vazio e o posiciona na janela no sentido baixo-cima
    backg = new Sprite("Resources/Hud/mapa.png", width, height);
    MoveTo(window->CenterX(), window->CenterY());

    // Lado esquerdo e direito do background principal
    leftSide = window->CenterX() - backg->Width() / 2.0f;
    rightSide = window->CenterX() + backg->Width() / 2.0f;

	// Posição y da primeira linha do background (de baixo para cima)
    tileBottom = window->Height() - tw / 2.0f; 

    nextLevel = false;

    consolas = new Font("Resources/press12.png");
    consolas->Spacing("Resources/press12.dat");

    // Inicializa o hud
    hud = new Sprite("Resources/Hud/hud2.png", width, 144.0f);
	Image* img = new Image("Resources/Hud/hud3.png", width, 576.0f);
    tileSet = new TileSet(img, width, 144.0f, 4, 1);
    life = new Animation(tileSet, 0.0f, false);

    uint seq1[1] = { 0 };
	uint seq2[1] = { 1 };
	uint seq3[1] = { 2 };
	uint seq4[1] = { 3 };

    life->Add(Life::FULL, seq1, 1);
    life->Add(Life::THREE_QUARTERS, seq2, 1);
    life->Add(Life::HALF, seq3, 1);
    life->Add(Life::QUARTER, seq4, 1);
}

// ---------------------------------------------------------------------------------

Hud::~Hud()
{
	delete backg;
	delete hud;
	delete consolas;
	delete life;
	delete tileSet;
}

// ---------------------------------------------------------------------------------

void Hud::Update()
{
    // Mantém background dentro da janela
    if (y - backg->Height() / 2.0f > 0)
        MoveTo(x, window->Height() - 1.0f);
    else if (y + backg->Height() / 2.0f < window->Height())
        MoveTo(x, -backg->Height() / 2.0f);

    // Pega a vida do player e atualiza hud da vida
    int ratio = 100 * Level1::player->GetVida() / Level1::player->MaxLife();
    if (ratio >= 99)
        life->Select(Life::FULL);
    else if (ratio >= 75)
        life->Select(Life::THREE_QUARTERS);
    else if (ratio >= 50)
        life->Select(Life::HALF);
    else
        life->Select(Life::QUARTER);
}

// ---------------------------------------------------------------------------------

void Hud::Draw()
{
    backg->Draw(x, y, Layer::BACK);
    hud->Draw(window->CenterX(), window->Height() - 72.0f, Layer::FRONT);

    // Desenha vida se o player estiver vivo
    if (Level1::player->GetVida() > 0)
        life->Draw(window->CenterX(), window->Height() - 76.0f, Layer::FRONT);

    // Desenha o texto do indicador de vida
    string lifeTxt = "";
    lifeTxt.append(std::to_string(Level1::player->GetVida()));
    lifeTxt.append("/");
    lifeTxt.append(std::to_string(Level1::player->MaxLife()));

	float positionY = window->Height() * 0.93;  // 93% da altura da janela
	float positionX = window->Width() * 0.33;   // 33% da largura da janela

    consolas->Draw(positionX, positionY, lifeTxt, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.001f, 0.7f, 0.0f);
    //consolas->Draw(leftSide + offset + tw * 0.33f, window->Height() - 72.0f, lifeTxt, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.001f, 0.7f, 0.0f);
}

// ---------------------------------------------------------------------------------
