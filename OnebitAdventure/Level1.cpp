// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Engine.h"
#include "Select.h"
#include "Warrior.h"
#include "Ghost.h"
#include <fstream>
#include <sstream>
#include "Hud.h"
using namespace std;

// ------------------------------------------------------------------------------

Character * Level1::player  = nullptr;
Hud       * Level1::hud     = nullptr;
Scene     * Level1::scene   = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    // Configura o tamanho dos tiles
    float width = window->Width() / 2.5f;
    float tileWidth = (width - width * 0.12f) / 11.25f;
    float tileHeight = window->Height() / 19.0f;

    scene = new Scene();

    hud = new Hud(tileWidth, tileHeight);
    player = new Warrior(tileWidth, tileHeight);

    // Inicializa a posição do Ghost 1
    float col = hud->Col(5);
    float line = hud->Line(11);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(hud, STATIC);
    scene->Add(player, MOVING);
    scene->Add(enemy, MOVING);

    col = hud->Col(2);
    line = hud->Line(15);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(4);
    line = hud->Line(16);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(5);
    line = hud->Line(9);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(8);
    line = hud->Line(10);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(9);
    line = hud->Line(17);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    col = hud->Col(10);
    line = hud->Line(1);

    enemy = new Ghost(tileWidth, tileHeight, col, line);

    scene->Add(enemy, MOVING);

    // Carrega os Props a partir do arquivo
    LoadPropsFromFile("Resources/Props/mapa1.txt", tileWidth, tileHeight);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{   
    // volta para a tela de inicio
    if (window->KeyPress(VK_ESCAPE))
    {
        Engine::Next<Select>();
        return;
    }

    if (window->KeyPress('B'))
        viewBox = !viewBox;

    scene->Update();
	scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    // desenha cena
    scene->Draw();
    // scene->CollisionDetection();

    if (viewBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
}

// ------------------------------------------------------------------------------

// Método para ler o arquivo e criar os Props
void Level1::LoadPropsFromFile(const std::string& filename, float tileWidth, float tileHeight)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        // Ignora linhas vazias e comentários
        if (line.empty() || line[0] == '/')
            continue;

        std::istringstream iss(line);
        int type;
        float x, y;
        bool interactable, bbox;

        // Lê e processa cada linha
        while (iss >> type >> x >> y >> interactable >> bbox)
        {
            // Converte tipo para o valor correspondente
            OneBitObjects propType;
            switch (type)
            {
            case 0: propType = GRASS; break;
            case 1: propType = WALL; break;
            case 2: propType = COIN; break;
            case 3: propType = DOOR; break;
			case 4: propType = TREE; break;
            case 5: propType = TREE; break;
            case 6: propType = CHEST; break;
            case 7: propType = CAMPFIRE; break;
            case 8: propType = FENCE; break;
			case 9: propType = PILLAR; break;
            case 10: propType = PILLAR; break;
            default: propType = PROP; break;
            }

            // Ajusta a posição conforme o tamanho do tile
            float col = hud->Col(x);
            float line = hud->Line(y);

            // Cria o Prop e adiciona à cena
            Prop* prop = new Prop(propType, type, col, line, tileWidth, tileHeight, interactable, bbox);
            scene->Add(prop, STATIC);
        }
    }

    file.close();
}

// ------------------------------------------------------------------------------