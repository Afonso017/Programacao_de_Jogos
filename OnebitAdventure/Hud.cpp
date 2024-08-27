#include "Hud.h"
#include "Level1.h"
#include "Prop.h"
#include <fstream>
using namespace std;

// ---------------------------------------------------------------------------------

Hud::Hud(float tileWidth, float tileHeight) : tw(tileWidth), th(tileHeight)
{
    // Background tem 1/3 da largura da janela e 4x a altura da janela
    width = window->Width() / 2.5f;
    height = window->Height() * 4.0f;

    // Carrega mapa vazio e o posiciona na janela no sentido baixo-cima
    backg = new Sprite(new Image("Resources/Hud/mapa.png", width, height));
    MoveTo(window->CenterX(), 0.75f * backg->Height());

    leftSide = window->CenterX() - backg->Width() / 2.0f;
    rightSide = window->CenterX() + backg->Width() / 2.0f;
    tileBottom = window->Height() - tw / 2.0f;
    offset = 0.067f * width;
    nextLevel = false;

    // Prepara para carregar as informações do mapa
    int type;
    bool interactable, bbox;
    float x, y;
    imagesSize = 8;
    images = new string * [imagesSize] {
        new string("Resources/Props/grass.png"),
        new string("Resources/Props/wall.png"),
        new string("Resources/Props/coin.png"),
        new string("Resources/Props/door.png"),
        new string("Resources/Props/tree.png"),
        new string("Resources/Props/chest.png"),
        new string("Resources/Props/campfire.png"),
		new string("Resources/Props/fence.png"),
    };

    // Faz a leitura do arquivo descritor do mapa e adiciona props na cena
    ifstream fin;
    fin.open("Resources/Hud/mapa1.txt");
    fin >> type;
    while (!fin.eof())
    {
        if (fin.good())
        {
            fin >> x; fin >> y; fin >> interactable; fin >> bbox;

            string img = *images[type];

            // Verificar tipo do Prop ou se é um Inimigo
            switch (type)
            {
            case 2:
                type = COIN;
                break;
            case 3:
                type = DOOR;
                break;
            case 5:
                type = CHEST;
                break;
            default:
                type = PROP;
                break;
            }

            // Adiciona Prop/Inimigo na cena
            Level1::scene->Add(new Prop(type, img, Col(y), Line(x), tw, th, interactable, bbox), STATIC);
        }
        else
        {
            // Ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }
        fin >> type;
    }
    fin.close();

    consolas = new Font("Resources/press12.png");
    consolas->Spacing("Resources/press12.dat");

    // Inicializa o hud
    hud = new Sprite(new Image("Resources/Hud/hud2.png", width, 144.0f));
    life = new Animation(new TileSet(new Image("Resources/Hud/hud3.png", width, 576.0f), 4, 1), 0.0f, false);
    life->Add(Life::FULL, new uint{ 0 }, 1);
    life->Add(Life::THREE_QUARTERS, new uint{ 1 }, 1);
    life->Add(Life::HALF, new uint{ 2 }, 1);
    life->Add(Life::QUARTER, new uint{ 3 }, 1);
}

// ---------------------------------------------------------------------------------

Hud::~Hud()
{
	delete backg;
	delete hud;
	delete consolas;
	delete life;
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
        life->Draw(window->CenterX(), window->Height() - 72.0f, Layer::FRONT);

    // Desenha o texto do indicador de vida
    string lifeTxt = "";
    lifeTxt.append(std::to_string(Level1::player->GetVida()));
    lifeTxt.append("/");
    lifeTxt.append(std::to_string(Level1::player->MaxLife()));

    consolas->Draw(leftSide + offset + tw * 0.33f, window->Height() - 72.0f, lifeTxt, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.001f, 0.7f, 0.0f);
}

// ---------------------------------------------------------------------------------
