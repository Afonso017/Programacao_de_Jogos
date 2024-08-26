// ------------------------------------------------------------------------------
// Inclusões

#include "Character.h"
#include <iostream>
#include "Enemy.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Character::InitializeBBox()
{
	// Inicializa a BBox
	BBox(new Rect(
		x - walking->TileWidth() / 2.4f, 
		y - walking->TileHeight() / 2.3f,
		x + walking->TileWidth() / 2.4f, 
		y + walking->TileHeight() / 2.3f)
	);
}

// ---------------------------------------------------------------------------------

// construtor para inicializar os atributos genéricos do jogador
Character::Character(float width, float height)
	: width(width), height(height), walking(nullptr), anim(nullptr) {

	// --------------------------------------------------------------------------------------------
	// Inicializar variáveis de estado do jogador

	characterState = WALKLEFT;	// Estado inicial do jogador
	direction = WALKLEFT;		// Direção inicial do jogador
	type = PLAYER;				// Tipo do jogador
	movementType = IDLE;		// Tipo de animação do jogador
	isHit = false;				// Flag para indicar se o personagem já foi atingido
	isDead = false;				// Flag para indicar se o personagem está morto
	isMoving = false;			// Flag para indicar se o personagem está se movendo

	// --------------------------------------------------------------------------------------------
	// Inicializar variáveis de movimentação do jogador

	interpolationSpeed = 22.0f; // Velocidade de interpolação do movimento do jogador, aumentar esse número para acelerar
	VelX = width;				// Velocidade horizontal (Quanto ele percorre horizontalmente)
	VelY = height;				// Velocidade vertical	 (Quanto ele percorre verticalmente)
	targetX = x;				// Posição x do destino do jogador pós movimento
	targetY = y;				// Posição y do destino do jogador pós movimento
	newX = x;					// Nova posição x do jogador
	newY = y;					// Nova posição y do jogador
	prevX = x;					// Posição x anterior do jogador
	prevY = y;					// Posição y anterior do jogador

	// --------------------------------------------------------------------------------------------
	// Inicializar variáveis de sprites e animação do jogador

	// Nenhuma é inicializada aqui, pois cada personagem tem suas próprias folhas de sprites e animações

	// --------------------------------------------------------------------------------------------
	// Inicializar variáveis auxiliares para construções de lógicas

	timer = new Timer();							// Timer para controlar o tempo de exibição do texto
	consolas = new Font("Resources/Pexilify.png");	// Fonte para exibir texto na tela
	consolas->Spacing("Resources/Pexilify.dat");	// Espaçamento da fonte
	attackTimer = new Timer();						// Timer para controlar o tempo de exibição do texto
	speedMovement = new Timer();					// Timer para controlar a velocidade de movimento do jogador

	// --------------------------------------------------------------------------------------------
	// Inicializar atributos básicos de todo jogador

	level = 1;					// Nível do jogador

	// Apenas o level é inicializado aqui, pois cada classe tem sua própria vida e dano de ataque

	// --------------------------------------------------------------------------------------------
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
	delete consolas;
	delete timer;
	delete attackTimer;
}

// ---------------------------------------------------------------------------------

void Character::Update()
{
	HandleInput();					// Detecta a entrada do jogador para movimentá-lo na direção correta

	if (movementType == BACK)
		BackMovement();				// Realiza a animação de recuo do jogador

	InterpolateMovement(gameTime);  // Interpolação do movimento do jogador para suavizar a movimentação
	UpdateAnimation(); 				// Atualiza a animação do jogador para o próximo frame
	ConstrainToScreen();			// Garante que o jogador não ultrapasse os limites da tela
}

// ---------------------------------------------------------------------------------

void Character::PerformAttack() {
	// Lógica que movimenta o jogador para a direção do ataque apenas para colidir com o inimigo
}

// ---------------------------------------------------------------------------------

void Character::BackMovement() {
	// Lógica que movimenta o jogador para a direção oposta ao ataque pois houve colisão
	targetX = prevX;		// Volta para a posição x anterior do jogador
	targetY = prevY;		// Volta para a posição y anterior do jogador

	SetMovementType(WALK);	// Define o tipo de movimento do jogador para andar
}

// ---------------------------------------------------------------------------------

void Character::HandleInput() {
	if (!isDead && newX == targetX && newY == targetY && attackTimer->Elapsed(0.2f)) {
		if (speedMovement->Elapsed(0.01f)) {  // Verifica se o timer permite um novo movimento

			movementType = WALK;			 // Define o tipo de movimento do jogador para andar

			if (window->KeyDown(VK_UP) && Y() == targetY) {
				SetMovementDirection(WALKUP, characterState, 0.0f, -VelY);
			}
			else if (window->KeyDown(VK_DOWN) && Y() == targetY) {
				SetMovementDirection(WALKDOWN, characterState, 0.0f, VelY);
			}
			else if (window->KeyDown(VK_LEFT) && X() == targetX) {
				SetMovementDirection(WALKLEFT, WALKLEFT, -VelX, 0.0f);
			}
			else if (window->KeyDown(VK_RIGHT) && X() == targetX) {
				SetMovementDirection(WALKRIGHT, WALKRIGHT, VelX, 0.0f);
			}

			ConstrainToScreen(); // Garante que o jogador não ultrapasse os limites da tela
		}
	}
}

// ---------------------------------------------------------------------------------

void Character::SetMovementDirection(DirectingAnimation newDirection, DirectingAnimation newAnimation, float deltaX, float deltaY) {
	prevX = X();					// Salva a posição x anterior do jogador
	prevY = Y();					// Salva a posição y anterior do jogador
	direction = newDirection; 		// Atualiza a direção do jogador
	characterState = newAnimation;  // Atualiza a animação do jogador
	targetX = X() + deltaX;			// Define a posição x do destino do jogador pós movimento
	targetY = Y() + deltaY;			// Define a posição y do destino do jogador pós movimento
	isMoving = true;				// Indica que o jogador está se movendo
	isHit = true;					// Indica que o jogador pode atacar o inimigo e ser atingido (Se houver colisão)

	speedMovement->Start();         // Inicia o timer após o movimento
}

// ---------------------------------------------------------------------------------

void Character::InterpolateMovement(float gameTime) {
	newX = X() + (targetX - X()) * interpolationSpeed * gameTime;	// Interpola a posição x do jogador
	newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;	// Interpola a posição y do jogador

	if (abs(targetX - newX) < 0.5f) newX = targetX;					// Corrige a posição x do jogador em pequenos passos
	if (abs(targetY - newY) < 0.5f) newY = targetY;					// Corrige a posição y do jogador em pequenos passos

	MoveTo(newX, newY);												// Move o jogador para a nova posição

	float diff = 0.067f * Level1::hud->Width();
}

// ---------------------------------------------------------------------------------

void Character::UpdateAnimation() {
	anim->Select(characterState);	// Atualiza a animação do jogador
	anim->NextFrame();				// Atualiza o frame da animação
}

// ---------------------------------------------------------------------------------

void Character::ConstrainToScreen() {
	float diff = 0.067f * Level1::hud->Width();

	// Verifica o limite direito
	if (targetX + width / 2.0f > window->CenterX() + Level1::hud->Width() / 2.0f - diff) {
		newX = targetX = prevX;
		movementType = IDLE;
	}
	// Verifica o limite esquerdo
	if (targetX - width / 2.0f < window->CenterX() - Level1::hud->Width() / 2.0f + diff) {
		newX = targetX = prevX;
		movementType = IDLE;
	}
	// Verifica o limite inferior
	if (targetY + walking->TileHeight() / 2.0f > window->Height()) {
		newY = targetY = prevY;
		movementType = IDLE;
	}
	// Verifica o limite superior
	if (targetY - walking->TileHeight() / 2.0f < 0) {
		newY = targetY = prevY;
		movementType = IDLE;
	}

	MoveTo(newX, newY); // Atualiza a posição do jogador
}

// ---------------------------------------------------------------------------------