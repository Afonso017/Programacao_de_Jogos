// ---------------------------------------------------------------------------------
// Inclusões

#include "Warrior.h"
#include "OneBitAdventure.h"

// ---------------------------------------------------------------------------------

void Warrior::init()
{
	Image* img = new Image("Resources/WizardSprite.png", this->width * 4, this->height * 2); // carrega sprite sheet do player
	walking = new TileSet(img, this->width, this->height, 4, 8);		// 2x4 sprites
	anim = new Animation(walking, 0.125f, true);						// 0.125f é o tempo de troca de frames

	uint SeqRight[4] = { 0,1,2,3 }; // sequência de sprites para andar para a direita
	uint SeqLeft[4] = { 4,5,6,7 };  // sequência de sprites para andar para a esquerda
	anim->Add(WALKRIGHT, SeqRight, 4); // adiciona a sequência de sprites para andar para a direita
	anim->Add(WALKLEFT, SeqLeft, 4);   // adiciona a sequência de sprites para andar para a esquerda


}

// ---------------------------------------------------------------------------------

void Warrior::OnCollision(Object* obj)
{
	// Se colidir com um inimigo, perde vida
	
}

// ---------------------------------------------------------------------------------