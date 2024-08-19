// ------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Player.h"

// ------------------------------------------------------------------------------

Player::Player(int widthT, int heightT)
{
	walking = new TileSet("Resources/WizardSprite.png", 70, 70, 4, 8); // 4x8 sprites de 70x70
	anim = new Animation(walking, 0.125f, true); // 0.125f é o tempo de troca de frames

	uint SeqRight[4] = { 0,1,2,3 }; // sequência de sprites para andar para a direita
	uint SeqLeft[4] = { 4,5,6,7 };  // sequência de sprites para andar para a esquerda

	anim->Add(WALKRIGHT, SeqRight, 4); // adiciona a sequência de sprites para andar para a direita
	anim->Add(WALKLEFT, SeqLeft, 4);   // adiciona a sequência de sprites para andar para a esquerda

	state = WALKLEFT; // estado inicial do jogador

	type = PLAYER;    // tipo do jogador

	speedVertical = 60;   // Esses foram os valores ideias que encontrei para o movimento do player
	speedHorizontal = 57; // Esses foram os valores ideias que encontrei para o movimento do player

	width = widthT;   // largura da tela
	height = heightT; // altura da tela

	
	// 700 (tamanho da janela) / 70 (tamanho do player) = 10 (tamanho do quadro)
	// a janela tem 70 quadros de dimensão 10x10

	MoveTo(window->CenterX(), window->CenterY() - 3, Layer::FRONT);

	timer = new Timer();
	timer->Start();

	moved = true;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete walking;
	delete anim;
	delete timer;
}

// ---------------------------------------------------------------------------------

boolean Player::Move()
{
		if (window->KeyDown(VK_UP))
		{
			// anda para cima
			MoveTo(X(), Y() - speedVertical);
			return true;
		}
		if (window->KeyDown(VK_DOWN))
		{
			// anda para baixo
			MoveTo(X(), Y() + speedVertical);
			return true;
		}
		if (window->KeyDown(VK_LEFT))
		{
			// anda para esquerda
			state = WALKLEFT;
			MoveTo(X() - speedHorizontal, Y());
			return true;
		}
		if (window->KeyDown(VK_RIGHT))
		{
			// anda para direita
			state = WALKRIGHT;
			MoveTo(X() + speedHorizontal, Y());
			return true;
		}

		return false;
}

void Player::MoveTo(float px, float py, float layer)
{
	Object::MoveTo(px, py, layer);
	moved = true;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	// atualiza a cena caso player tenha movido e tenha se passado um tempo ms
	if (timer->Elapsed(0.100f)) {
		Move();
		timer->Reset();
	}

	// atualiza animação
	anim->Select(state);
	anim->NextFrame();

	// mantém personagem dentro da tela
	if (x + walking->TileWidth() / 2.0f > (window->CenterX() + (width - 100) / 2.0f))
		MoveTo(window->CenterX() + (width - 157) / 2.0f, y);

	if (x - walking->TileWidth() / 2.0f < (window->CenterX() - (width - 100) / 2.0f))
		MoveTo(window->CenterX() - (width - 160) / 2.0f, y);

	if (y + walking->TileHeight() / 2.0f > window->Height())
		MoveTo(x, window->Height() - walking->TileHeight() / 2.0f);

	if (y - walking->TileHeight() / 2.0f < 0)
		MoveTo(x, walking->TileHeight() / 2.0f);
}

// ---------------------------------------------------------------------------------
