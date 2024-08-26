#include "Hud.h"
#include "Level1.h"
#include "Prop.h"
#include <fstream>
using namespace std;

// ---------------------------------------------------------------------------------

Scene * Hud::scene = nullptr;

// ---------------------------------------------------------------------------------

Hud::Hud(float tileWidth, float tileHeight) : tw(tileWidth), th(tileHeight)
{
    // Background tem 1/3 da largura da janela e 4x a altura da janela
    width = window->Width() / 3.0f;
    height = window->Height() * 4.0f;

    // Carrega mapa vazio e o posiciona na janela no sentido baixo-cima
    backg = new Sprite(new Image("Resources/Hud/mapa.png", width, height));
    MoveTo(window->CenterX(), 0.75f * backg->Height());

    // Prepara para carregar as informações do mapa
    int type;
    bool interactable, bbox;
    float x, y;
    imagesSize = 7;
    images = new Image*[imagesSize] {
        new Image("Resources/Props/tree.png"),
        new Image("Resources/Props/wall.png"),
        new Image("Resources/Props/coin.png"),
        new Image("Resources/Props/door.png"),
        new Image("Resources/Props/grass.png"),
        new Image("Resources/Props/chest.png"),
        new Image("Resources/Props/campfire.png")
    };
    scene = new Scene();

    consolas = new Font("Resources/consolas12.png");
    consolas->Spacing("Resources/consolas12.dat");

    // Faz a leitura do arquivo descritor do mapa e adiciona props na cena
    //ifstream fin;
    //fin.open("Resources/Hud/mapa1.txt");
    //fin >> type;
    //while (!fin.eof())
    //{
    //    if (fin.good())
    //    {
    //        fin >> x; fin >> y; fin >> interactable; fin >> bbox;
    //        
    //        // Verificar se é um Prop ou Inimigo
    //        
    //        // Caso seja um prop, adiciona na cena do Hud
    //        Image * img = images[type];
    //        float line = window->Height() - x * th - th / 2.0f + 3.0f;
    //        float col = backg->Width() + y * tw + tw / 2.0f + 1.0f;

    //        scene->Add(new Prop(img, col, line, tw, th, interactable, bbox), STATIC);
    //    }
    //    else
    //    {
    //        // Ignora comentários
    //        fin.clear();
    //        char temp[80];
    //        fin.getline(temp, 80);
    //    }
    //    fin >> type;
    //}
    //fin.close();

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
    delete life;
    delete consolas;
    delete scene;

    for (int i = 0; i < imagesSize; i++)
        delete images[i];
    delete[] images;
}

// ---------------------------------------------------------------------------------

void Hud::Update()
{
    // Mantém background dentro da janela
    if (y - backg->Height() / 2.0f > 0)
        MoveTo(x, window->Height() - 1.0f);
    else if (y + backg->Height() / 2.0f < window->Height())
        MoveTo(x, -backg->Height() / 2.0f);

    if (window->KeyPress('B'))
        viewBox = !viewBox;

    // Pega a vida do player e atualiza hud da vida
    int ratio = 100 * Level1::player->GetVida() / Level1::player->MaxLife();
    if (ratio >= 75)
        life->Select(Life::FULL);
    else if (ratio >= 50)
        life->Select(Life::THREE_QUARTERS);
    else if (ratio >= 25)
        life->Select(Life::HALF);
    else
        life->Select(Life::QUARTER);

    scene->Update();
    scene->CollisionDetection();
}

// ---------------------------------------------------------------------------------

void Hud::Draw()
{
    backg->Draw(x, y, Layer::BACK);
    hud->Draw(x, window->Height() - 72.0f, Layer::FRONT);

    if (viewBox)
        scene->DrawBBox();
    
    // Desenha vida se o player estiver vivo
    if (Level1::player->GetVida() > 0)
        life->Draw(x, window->Height() - 72.0f, Layer::FRONT);

    // Desenha o texto do indicador de vida
    string lifeTxt = "";
    lifeTxt.append(std::to_string(Level1::player->GetVida()));
    lifeTxt.append("/");
    lifeTxt.append(std::to_string(Level1::player->MaxLife()));

    consolas->Draw(backg->Width() + 48.0f, window->Height() - 72.0f, lifeTxt, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.001f, 1.2f, 0.0f);

    scene->Draw();

    // --------------------------------------------------------------------------------------
    // DEBUG
    // --------------------------------------------------------------------------------------

    string dano = "Prev Ghost: ";
    dano.append(std::to_string(Level1::enemy->GetPrevX()));
    dano.append(", ");
    dano.append(std::to_string(Level1::enemy->GetPrevY()));
    dano.append(" - ");
    dano.append(std::to_string(Level1::enemy->GetTargetX()));
    dano.append(", ");
    dano.append(std::to_string(Level1::enemy->GetTargetY()));
    dano.append(" - ");
    dano.append(std::to_string(Level1::enemy->GetVelX()));
    dano.append(", ");
    dano.append(std::to_string(Level1::enemy->GetVelY()));

    consolas->Draw(700, 150, dano, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.2f, 0.0f);

    dano = "Prev Warrior: ";
    dano.append(std::to_string(Level1::player->GetPrevX()));
    dano.append(", ");
    dano.append(std::to_string(Level1::player->GetPrevY()));
    dano.append(" - ");
    dano.append(std::to_string(Level1::player->GetTargetX()));
    dano.append(", ");
    dano.append(std::to_string(Level1::player->GetTargetY()));
    dano.append(" - ");
    dano.append(std::to_string(Level1::player->GetVelX()));
    dano.append(", ");
    dano.append(std::to_string(Level1::player->GetVelY()));

    consolas->Draw(700, 200, dano, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.2f, 0.0f);
}

// ---------------------------------------------------------------------------------
