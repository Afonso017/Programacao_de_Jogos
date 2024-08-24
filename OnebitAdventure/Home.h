// ------------------------------------------------------------------------------
// Inclus�es

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
	void Init();                    // inicializa��o
	void Update();                  // atualiza��o
	void Draw();                    // desenho
	void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif HOME_H