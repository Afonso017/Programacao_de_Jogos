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
	BBox(new Rect(
		x - walking->TileWidth() / 4.0f,
		y - walking->TileHeight() / 4.0f,
		x + walking->TileWidth() / 4.0f,
		y + walking->TileHeight() / 4.0f));
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

	interpolationSpeed = 25.0f; // Velocidade de interpolação do movimento do jogador, aumentar esse número para acelerar
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

	timer = new Timer();													// Timer para controlar o tempo de exibição do texto
	press12 = new Font("Resources/press12.png");							// Fonte para exibir texto na tela
	press12->Spacing("Resources/press12.dat");								// Espaçamento da fonte
	attackTimer = new Timer();												// Timer para controlar o tempo de exibição do texto
	speedMovement = new Timer();											// Timer para controlar a velocidade de movimento do jogador
	xpBar = new Sprite(new Image("Resources/xpBar.png", 387.0f, 5.0f));		// Sprite para representar a experiência do jogador

	// --------------------------------------------------------------------------------------------
	// Inicializar atributos básicos de todo jogador

	level = 1;																// Nível do jogador
	maxXp = 60 + (6 * (level - 1));											// Experiência máxima do jogador
	xp = 56;																// Experiência do jogador

	// Apenas o level é inicializado aqui, pois cada classe tem sua própria vida e dano de ataque

	// --------------------------------------------------------------------------------------------
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
	delete press12;
	delete timer;
	delete attackTimer;
	delete speedMovement;
	delete xpBar;
}

// ---------------------------------------------------------------------------------

void Character::Update()
{
	HandleInput();							// Detecta a entrada do jogador para movimentá-lo na direção correta

	if (movementType == BACK)
		BackMovement();						// Realiza a animação de recuo do jogador

	InterpolateMovement(gameTime);			// Interpolação do movimento do jogador para suavizar a movimentação
	UpdateAnimation(); 						// Atualiza a animação do jogador para o próximo frame
	ConstrainToScreen();					// Garante que o jogador não ultrapasse os limites da tela

	if (xp >= maxXp) {
		level++;							// Aumenta o nível do jogador
		xp = 0;								// Reseta a experiência do jogador
		maxXp = 60 + (6 * (level - 1));		// Aumenta a experiência máxima do jogador

		maxLife = 52 + (10 * (level - 1));
		vida = maxLife;
	}


	if (vida <= 0) {

		Image* img = new Image("Resources/morte.png", 64, 64); // Carrega a imagem do Warrior
		walking = new TileSet(img, 64, 64, 1, 1);              // Cria o TileSet do Warrior
		anim = new Animation(walking, 0.125f, true);		   //
		isDead = true;										   // foi de base

		press12->Draw(window->CenterX() - 50.0f, window->CenterY(), "Game Over", Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.2f);
	}
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
	isMoving = false;						  // Indica que o jogador não está se movendo	

	if (!isDead && newX == targetX && newY == targetY && attackTimer->Elapsed(0.2f)) {
		if (speedMovement->Elapsed(0.03f)) {  // Verifica se o timer permite um novo movimento

			movementType = WALK;			  // Define o tipo de movimento do jogador para andar

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
	if (targetX > window->CenterX() + Level1::hud->Width() / 2.0f - diff) {
		newX = targetX = prevX;
		movementType = IDLE;
	}
	// Verifica o limite esquerdo
	if (targetX < window->CenterX() - Level1::hud->Width() / 2.0f + diff) {
		newX = targetX = prevX;
		movementType = IDLE;
	}
	// Verifica o limite inferior
	if (targetY > window->Height()) {
		newY = targetY = prevY;
		movementType = IDLE;
	}
	// Verifica o limite superior
	if (targetY < 0) {
		newY = targetY = prevY;
		movementType = IDLE;
	}

	MoveTo(newX, newY); // Atualiza a posição do jogador
}

// ---------------------------------------------------------------------------------

void Character::Draw() {
	anim->Draw(x, y, z);

	DrawTextGet();
	DrawExperienceBar();
	DrawLevelAndXp();
}
// ---------------------------------------------------------------------------------

void Character::DrawTextGet() {
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

void Character::DrawExperienceBar() {
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

void Character::DrawLevelAndXp() {
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