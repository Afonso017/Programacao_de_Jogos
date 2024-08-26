// Inclus�es

#pragma once
#ifndef LEVEL1_H
#define LEVEL1_H

#include "Game.h"
#include "Scene.h"
#include "Background.h"
#include "Warrior.h"
#include "Ghost.h"
#include "Font.h"

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	Warrior* warrior;				// instancia do jogador (classe guerreiro)
	Background* backg = nullptr;	// background principal
	Sprite* backg2 = nullptr;		// background
	boolean  viewBox = false;		// controle de visualiza��o de caixas de colis�o
	Font* consolas;					// Fonte para exibir texto na tela!

	int progress = 0;				// Vari�vel para contar o progresso do player!
	
	Ghost* ghost;					// instancia do inimigo (classe fantasma)
public:
	static Scene* scene;			// gerenciador de cena

	int  Width();                   // retorna a largura atual da janela
	int  Height();                  // retorna a altura atual da janela

	void Init();					// inicializa��o
	void Update();					// atualiza��o
	void Draw();					// desenho
	void Finalize();				// finaliza��o
};

// -----------------------------------------------------------------------------

// retorna a largura atual da janela
inline int Level1::Width()
{
	return backg->Width();
}

// retorna a altura atual da janela
inline int Level1::Height()
{
	return backg->Height();
}

// -----------------------------------------------------------------------------

#endif LEVEL1_H