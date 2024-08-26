// ------------------------------------------------------------------------------
// Inclus�es

#include "Character.h"
#include <iostream>
#include "Enemy.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colis�o
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

// construtor para inicializar os atributos gen�ricos do jogador
Character::Character(float width, float height)
	: width(width), height(height), walking(nullptr), anim(nullptr) {

	// --------------------------------------------------------------------------------------------
	// Inicializar vari�veis de estado do jogador

	characterState = WALKLEFT;	// Estado inicial do jogador
	direction = WALKLEFT;		// Dire��o inicial do jogador
	type = PLAYER;				// Tipo do jogador
	movementType = IDLE;		// Tipo de anima��o do jogador
	isHit = false;				// Flag para indicar se o personagem j� foi atingido
	isDead = false;				// Flag para indicar se o personagem est� morto
	isMoving = false;			// Flag para indicar se o personagem est� se movendo

	// --------------------------------------------------------------------------------------------
	// Inicializar vari�veis de movimenta��o do jogador

	interpolationSpeed = 22.0f; // Velocidade de interpola��o do movimento do jogador, aumentar esse n�mero para acelerar
	VelX = width;				// Velocidade horizontal (Quanto ele percorre horizontalmente)
	VelY = height;				// Velocidade vertical	 (Quanto ele percorre verticalmente)
	targetX = x;				// Posi��o x do destino do jogador p�s movimento
	targetY = y;				// Posi��o y do destino do jogador p�s movimento
	newX = x;					// Nova posi��o x do jogador
	newY = y;					// Nova posi��o y do jogador
	prevX = x;					// Posi��o x anterior do jogador
	prevY = y;					// Posi��o y anterior do jogador

	// --------------------------------------------------------------------------------------------
	// Inicializar vari�veis de sprites e anima��o do jogador

	// Nenhuma � inicializada aqui, pois cada personagem tem suas pr�prias folhas de sprites e anima��es

	// --------------------------------------------------------------------------------------------
	// Inicializar vari�veis auxiliares para constru��es de l�gicas

	timer = new Timer();							// Timer para controlar o tempo de exibi��o do texto
	consolas = new Font("Resources/Pexilify.png");	// Fonte para exibir texto na tela
	consolas->Spacing("Resources/Pexilify.dat");	// Espa�amento da fonte
	attackTimer = new Timer();						// Timer para controlar o tempo de exibi��o do texto
	speedMovement = new Timer();					// Timer para controlar a velocidade de movimento do jogador

	// --------------------------------------------------------------------------------------------
	// Inicializar atributos b�sicos de todo jogador

	level = 1;					// N�vel do jogador

	// Apenas o level � inicializado aqui, pois cada classe tem sua pr�pria vida e dano de ataque

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
	HandleInput();					// Detecta a entrada do jogador para moviment�-lo na dire��o correta

	if (movementType == BACK)
		BackMovement();				// Realiza a anima��o de recuo do jogador

	InterpolateMovement(gameTime);  // Interpola��o do movimento do jogador para suavizar a movimenta��o
	UpdateAnimation(); 				// Atualiza a anima��o do jogador para o pr�ximo frame
	ConstrainToScreen();			// Garante que o jogador n�o ultrapasse os limites da tela
}

// ---------------------------------------------------------------------------------

void Character::PerformAttack() {
	// L�gica que movimenta o jogador para a dire��o do ataque apenas para colidir com o inimigo
}

// ---------------------------------------------------------------------------------

void Character::BackMovement() {
	// L�gica que movimenta o jogador para a dire��o oposta ao ataque pois houve colis�o
	targetX = prevX;		// Volta para a posi��o x anterior do jogador
	targetY = prevY;		// Volta para a posi��o y anterior do jogador

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

			ConstrainToScreen(); // Garante que o jogador n�o ultrapasse os limites da tela
		}
	}
}

// ---------------------------------------------------------------------------------

void Character::SetMovementDirection(DirectingAnimation newDirection, DirectingAnimation newAnimation, float deltaX, float deltaY) {
	prevX = X();					// Salva a posi��o x anterior do jogador
	prevY = Y();					// Salva a posi��o y anterior do jogador
	direction = newDirection; 		// Atualiza a dire��o do jogador
	characterState = newAnimation;  // Atualiza a anima��o do jogador
	targetX = X() + deltaX;			// Define a posi��o x do destino do jogador p�s movimento
	targetY = Y() + deltaY;			// Define a posi��o y do destino do jogador p�s movimento
	isMoving = true;				// Indica que o jogador est� se movendo
	isHit = true;					// Indica que o jogador pode atacar o inimigo e ser atingido (Se houver colis�o)

	speedMovement->Start();         // Inicia o timer ap�s o movimento
}

// ---------------------------------------------------------------------------------

void Character::InterpolateMovement(float gameTime) {
	newX = X() + (targetX - X()) * interpolationSpeed * gameTime;	// Interpola a posi��o x do jogador
	newY = Y() + (targetY - Y()) * interpolationSpeed * gameTime;	// Interpola a posi��o y do jogador

	if (abs(targetX - newX) < 0.5f) newX = targetX;					// Corrige a posi��o x do jogador em pequenos passos
	if (abs(targetY - newY) < 0.5f) newY = targetY;					// Corrige a posi��o y do jogador em pequenos passos

	MoveTo(newX, newY);												// Move o jogador para a nova posi��o

	float diff = 0.067f * Level1::hud->Width();
}

// ---------------------------------------------------------------------------------

void Character::UpdateAnimation() {
	anim->Select(characterState);	// Atualiza a anima��o do jogador
	anim->NextFrame();				// Atualiza o frame da anima��o
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

	MoveTo(newX, newY); // Atualiza a posi��o do jogador
}

// ---------------------------------------------------------------------------------