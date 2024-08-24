// ------------------------------------------------------------------------------
// Inclusões

#pragma once
#ifndef HOME_H
#define HOME_H

#include "Game.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
	Animation * backg = nullptr;   // plano de fundo

public:
	void Init();                    // inicialização
	void Update();                  // atualização
	void Draw();                    // desenho
	void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif HOME_H