// ------------------------------------------------------------------------------
// Inclusões

#ifndef SELECT_H
#define SELECT_H

#include "Sprite.h"

// ------------------------------------------------------------------------------

class Select : public Game
{
private:
	Sprite* backg = nullptr;   // plano de fundo

public:
	void Init();                // inicialização
	void Update();              // atualização
	void Draw();                // desenho
	void Finalize();            // finalização
};

// ------------------------------------------------------------------------------

#endif SELECT_H