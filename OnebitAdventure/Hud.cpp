#include "Hud.h"

// ---------------------------------------------------------------------------------

Hud::Hud()
{
	// Dimensões comuns aos 3 huds
    width = window->Width() / 3.0f;     // Largura da área central
	height = window->Height();          // Altura da área central

    // Descontando as bordas laterais de 5% da largura total
    offset = width * 0.05f;                          // Exemplo de 5% de borda em cada lado

    // Área útil de movimento, sem contar as bordas
    tileWidth = (width - (2.0f * offset)) / 11.0f;         // Largura e passada horizontal de um tile
    tileHeight = height / 19.0f;  				                // Altura e passada vertical de um tile

    // Imagem do background esquerdo

    // -------------------------------------------------------------------------
    // Inicializa hud principal
    // 
    // Imagem do background principal
    mainBackg = new Sprite("Resources/Hud/mapa.png", width, height);

    // Lado esquerdo e direito do background principal
    mainLeftSide = window->CenterX() - mainBackg->Width() / 2.0f;
    mainRightSide = window->CenterX() + mainBackg->Width() / 2.0f;
    mainBottomSide = window->Height() - tileHeight / 2.0f;       // Posição da primeira linha do background

	// Hud do player com vida, mana, xp, etc
    playerHud = new Sprite("Resources/Hud/hud2.png", width, 2.8f * tileHeight);
	Image* img = new Image("Resources/Hud/hud3.png", width, 4.0f * 2.8f * tileHeight);
    tileSet = new TileSet(img, width, 2.8f * tileHeight, 4, 1);
    life = new Animation(tileSet, 0.0f, false);

    uint seq1[1] = { 0 };
	uint seq2[1] = { 1 };
	uint seq3[1] = { 2 };
	uint seq4[1] = { 3 };

    life->Add(FULL, seq1, 1);
    life->Add(THREE_QUARTERS, seq2, 1);
    life->Add(HALF, seq3, 1);
    life->Add(QUARTER, seq4, 1);

    // --------------------------------------------------------------------------

    // Imagem do background direito
    

	// Fonte para exibir texto na tela
    consolas = new Font("Resources/press12.png");
    consolas->Spacing("Resources/press12.dat");
}

// ---------------------------------------------------------------------------------

Hud::~Hud()
{
    delete mainBackg;
    delete playerHud;
    delete tileSet;
    delete life;
    delete consolas;
}

// ---------------------------------------------------------------------------------

void Hud::Update()
{
    // Pega a vida do player e atualiza hud da vida
    int ratio = 100 * 1/*Level1::player->GetVida() / Level1::player->MaxLife()*/;
    if (ratio >= 99)
        life->Select(FULL);
    else if (ratio >= 75)
        life->Select(THREE_QUARTERS);
    else if (ratio >= 50)
        life->Select(HALF);
    else
        life->Select(QUARTER);
}

// ---------------------------------------------------------------------------------

void Hud::Draw()
{
    mainBackg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    playerHud->Draw(window->CenterX(), window->Height() - playerHud->Height() / 2.0f, Layer::FRONT);

    // Desenha vida se o player estiver vivo
    if (72/*Level1::player->GetVida()*/ > 0)
        life->Draw(window->CenterX(), window->Height() - playerHud->Height() / 2.0f, Layer::FRONT);

    // Desenha o texto do indicador de vida
    string lifeTxt = "";
    lifeTxt.append(std::to_string(72/*Level1::player->GetVida()*/));
    lifeTxt.append("/");
    lifeTxt.append(std::to_string(72/*Level1::player->MaxLife()*/));

	float positionX = mainLeftSide + offset + 0.25f * tileWidth;
    float positionY = mainBottomSide - 0.8f * tileHeight;

    consolas->Draw(positionX, positionY, lifeTxt, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.001f, 0.7f, 0.0f);
}

// ---------------------------------------------------------------------------------
