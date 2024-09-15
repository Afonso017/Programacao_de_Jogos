// ------------------------------------------------------------------------------
// Inclusões

#include "Map.h"
#include "Level1.h"
#include "Ghost.h"
#include "Prop.h"
#include "Types.h"
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <vector>
#include <random>
#include <string>

using std::vector;
typedef vector<vector<uint>> intMatrix;
typedef vector<vector<float>> floatMatrix;
typedef vector<vector<string>> stringMatrix;
typedef vector<floatMatrix> chunkMatrix;
typedef std::uniform_int_distribution<int> intDistribution;
typedef std::uniform_real_distribution<double> doubleDistribution;

// Constantes
const int tamanho = 11;   // Tamanho do mapa
const int nChunks = 20;	  // Número de chunks no mapa
std::random_device rd;    // Inicializa o gerador de números aleatórios
std::mt19937 rng(rd());   // Inicializa o Mersenne Twister com uma semente aleatória

// Vetor de pesos de props para cada bioma, todos tem chance de gerar moedas, caixas, baús e portas
const float weights[3][16] = {
    { 0.017f, 0.0f, 0.017f, 0.017f, 0.0f, 0.017f, 0.017f, 0.067f, 0.067f, 0.0f, 0.0f, 0.017f, 0.008f, 0.008f, 0.0f, 0.75f },  // FIELD
    { 0.018f, 0.0f, 0.018f, 0.018f, 0.0f, 0.018f, 0.018f, 0.018f, 0.018f, 0.0f, 0.0f, 0.018f, 0.018f, 0.018f, 0.018f, 0.75f },  // FOREST
    { 0.016f, 0.0f, 0.016f, 0.016f, 0.016f, 0.0f, 0.0f, 0.0f, 0.0f, 0.040f, 0.040f, 0.040f, 0.0f, 0.0f, 0.065f, 0.75f }   // RUIN
};

// Estrutura para armazenar um prop com seu intervalo na roleta
struct PropInterval {
    uint type;         // Tipo do prop
    float start;       // Início do intervalo
    float end;         // Fim do intervalo

	PropInterval(uint type, float start, float end) : type(type), start(start), end(end) {}
};

// Define a roleta do bioma FIELD
std::vector<PropInterval> fieldRoulette = {
    PropInterval(0, 0.000f, 0.017f),
    PropInterval(2, 0.017f, 0.034f),
    PropInterval(3, 0.034f, 0.051f),
    PropInterval(5, 0.051f, 0.068f),
    PropInterval(6, 0.068f, 0.085f),
    PropInterval(7, 0.085f, 0.152f),
    PropInterval(8, 0.152f, 0.219f),
    PropInterval(11, 0.219f, 0.236f),
    PropInterval(12, 0.236f, 0.244f),
    PropInterval(13, 0.244f, 0.452f)
};

//// Define a roleta do bioma FOREST
//std::vector<PropInterval> fieldRoulette = {
//    PropInterval(0, 0.000f, 0.017f),
//    PropInterval(2, 0.017f, 0.034f),
//    PropInterval(3, 0.034f, 0.051f),
//    PropInterval(5, 0.051f, 0.068f),
//    PropInterval(6, 0.068f, 0.085f),
//    PropInterval(7, 0.085f, 0.152f),
//    PropInterval(8, 0.152f, 0.219f),
//    PropInterval(11, 0.219f, 0.236f),
//    PropInterval(12, 0.236f, 0.244f),
//    PropInterval(13, 0.244f, 0.252f),
//    PropInterval(15, 0.252f, 1.000f)
//};
//
//// Define a roleta do bioma RUIN
//std::vector<PropInterval> fieldRoulette = {
//    PropInterval(0, 0.000f, 0.017f),
//    PropInterval(2, 0.017f, 0.034f),
//    PropInterval(3, 0.034f, 0.051f),
//    PropInterval(5, 0.051f, 0.068f),
//    PropInterval(6, 0.068f, 0.085f),
//    PropInterval(7, 0.085f, 0.152f),
//    PropInterval(8, 0.152f, 0.219f),
//    PropInterval(11, 0.219f, 0.236f),
//    PropInterval(12, 0.236f, 0.244f),
//    PropInterval(13, 0.244f, 0.252f),
//    PropInterval(15, 0.252f, 1.000f)
//};

// Função que cria a roleta de um bioma e seleciona um prop
static const uint spinRoulette(const std::vector<PropInterval>& roulette)
{
    doubleDistribution dist(0.0, 1.0);
	float r = dist(rng);  // Gera um número aleatório entre 0 e 1

    for (const auto& prop : roulette) {
        if (r >= prop.start && r < prop.end) {
            return prop.type;  // Retorna o prop selecionado
        }
    }

	return 15;  // Retorna espaço vazio
}

static void generateMap()
{
    intDistribution dist(0, 2);

    for (int c = 0; c < nChunks; ++c) {
        int randRoulette = dist(rng);       // Escolhe um bioma aleatório

		/*if (randRoulette == 0) {
			propType = spinRoulette(fieldRoulette);
		}
		else if (randRoulette == 1) {
			propType = spinRoulette(fieldRoulette);
		}
		else if (randRoulette == 2) {
			propType = spinRoulette(fieldRoulette);
		}*/
    }
}

// ------------------------------------------------------------------------------

Map::Map(uint seed)
{
	// Inicializa as propriedades do mapa
	lastPos = Level1::hud->Line(0);
    rng.seed(seed);

    // Inicializa vetor de imagens de props
    images[0] = new Image("Resources/Props/box.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[1] = new Image("Resources/Props/campfireanim.png", Level1::hud->tileWidth * 2, Level1::hud->tileHeight);
    images[2] = new Image("Resources/Props/chest.png", Level1::hud->tileWidth * 2, Level1::hud->tileHeight);
    images[3] = new Image("Resources/Props/coin.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[4] = new Image("Resources/Props/door.png", Level1::hud->tileWidth * 2, Level1::hud->tileHeight);
    images[5] = new Image("Resources/Props/fence.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[6] = new Image("Resources/Props/fenceRotten.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[7] = new Image("Resources/Props/grass.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[8] = new Image("Resources/Props/grass2.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[9] = new Image("Resources/Props/pilar.png", Level1::hud->tileWidth, Level1::hud->tileHeight * 3);
    images[10] = new Image("Resources/Props/pilar2.png", Level1::hud->tileWidth, Level1::hud->tileHeight * 3);
    images[11] = new Image("Resources/Props/rock.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[12] = new Image("Resources/Props/tree.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[13] = new Image("Resources/Props/tree2.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[14] = new Image("Resources/Props/wall.png", Level1::hud->tileWidth, Level1::hud->tileHeight);

    // Gera os chunks do mapa
    for (int i = 0; i < nChunks; ++i) {
        Generate();
    }
    
	// Inicialização dos inimigos
	//Level1::scene->Add(new Ghost(8, 4), MOVING);
	/*Level1::scene->Add(new Ghost(tileWidth, tileHeight, Level1::hud->Col(5), hud->Line(9)), MOVING);
	Level1::scene->Add(new Ghost(tileWidth, tileHeight, Level1::hud->Col(8), hud->Line(10)), MOVING);
	Level1::scene->Add(new Ghost(tileWidth, tileHeight, Level1::hud->Col(5), hud->Line(11)), MOVING);
	Level1::scene->Add(new Ghost(tileWidth, tileHeight, Level1::hud->Col(2), hud->Line(15)), MOVING);
	Level1::scene->Add(new Ghost(tileWidth, tileHeight, Level1::hud->Col(4), hud->Line(16)), MOVING);
	Level1::scene->Add(new Ghost(tileWidth, tileHeight, Level1::hud->Col(9), hud->Line(17)), MOVING);*/
}

// ------------------------------------------------------------------------------

Map::~Map()
{
	for (Image* img : images)
		delete img;
}

// ------------------------------------------------------------------------------

void Map::Generate()
{
    // Gera um chunk, percorrendo cada linha e coluna gerando os props
    for (int y = 0; y < tamanho; ++y) {
        for (int x = 0; x < tamanho; ++x) {

            uint idx = spinRoulette(fieldRoulette);
			if (idx == propsLength) continue;
            
            Image * img = images[idx];
            uint type;
            switch (idx)
            {
            case 0: type = BOX; break;
            case 1: type = CAMPFIRE; break;
            case 2: type = CHEST; break;
            case 3: type = COIN; break;
            case 4: type = DOOR; break;
            case 9: case 10: type = PILLAR; break;
            default: type = PROP;
            }

            float col = Level1::hud->Col(x);                // Coluna do prop
            float line = lastPos;                           // Linha continua da última posição

			bool interactable = type != PROP;               // Tipo prop não é interagível
            bool bbox = idx != 7 && idx != 8 && idx != 11;  // Gramas e pedras não possuem bbox

            // Adiciona o prop gerado na cena
            Level1::scene->Add(new Prop(type, img, col, line, interactable, bbox), STATIC);
        }
        lastPos -= Level1::hud->tileHeight;     // Passa para a próxima linha
    }
}

// ------------------------------------------------------------------------------
