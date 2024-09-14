// ------------------------------------------------------------------------------
// Inclus�es

#include "Enemy.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colis�o
void Enemy::InitializeBBox()
{
    // Inicializa a BBox
    BBox(new Rect(
        x - walking->TileWidth() / 4.0f,
        y - walking->TileHeight() / 4.0f,
        x + walking->TileWidth() / 4.0f,
        y + walking->TileHeight() / 4.0f)
    );
}

// ------------------------------------------------------------------------------

// Construtor da classe Enemy
Enemy::Enemy()
    : Entity(), walking(nullptr), anim(nullptr) {

    // --------------------------------------------------------------------------------------------
    // Inicializa as vari�veis de estado do inimigo

    direction = STILL;            // Dire��o inicial do inimigo
    enemyState = WALK;            // Estado inicial do inimigo
    type = ENEMY;                 // Tipo do inimigo
    isHit = false;                // Flag para indicar se o inimigo foi atingido

    // --------------------------------------------------------------------------------------------
    // Inicializa vari�veis de sprites e anima��o

    lifeSprite = new Sprite(new Image("Resources/sangue.png", 86.0f, 6.0f));
    hudLife = new Sprite(new Image("Resources/vida.png", 104.0f, 17.0f));

    // --------------------------------------------------------------------------------------------
    // Inicializa vari�veis auxiliares

    press12 = new Font("Resources/press12.png"); // Fonte para exibir texto na tela
    press12->Spacing("Resources/press12.dat");	 // Espa�amento da fonte

    // --------------------------------------------------------------------------------------------
    // Inicializa atributos b�sicos do inimigo

    level = 1;                    // N�vel do inimigo

    // (Vida e dano de ataque s�o definidos nas subclasses)

    // --------------------------------------------------------------------------------------------
}

// Destrutor da classe Enemy
Enemy::~Enemy()
{
    delete lifeSprite;
    delete hudLife;
    delete press12;
}

// ------------------------------------------------------------------------------

// Atualiza o estado do inimigo
void Enemy::Update()
{
    deltaX = Level1::player->X() - X();                     // Dist�ncia em X para o jogador
    deltaY = Level1::player->Y() - Y();                     // Dist�ncia em Y para o jogador
    distance = deltaX * deltaX + deltaY * deltaY;           // Dist�ncia ao quadrado (para efici�ncia)

    if (Level1::player->IsMoving() && Level1::player->GetMovementType() != IDLE) {

        HandleMovement();                                   // Atualiza a movimenta��o do inimigo
    }

    if (distance < proximityThreshold) {
        // Se o inimigo est� a um bloco de dist�ncia do jogador, � exibido a vida do inimigo
        DisplayEnemyHealth();
    }

	// Se a vida do inimigo for menor ou igual a zero ele vai de base, � deletado e o jogador ganha experi�ncia
    if (life <= 0) {
        // Morreu
        // Deleta o objeto
        Level1::scene->Delete(this, MOVING);
        Level1::player->SetXp(20 * (level));
    }

    InterpolateMovement();                                  // Interpola o movimento do inimigo
    UpdateAnimation();                                      // Atualiza a anima��o do inimigo
    ConstrainToScreen();                                    // Garante que o inimigo n�o ultrapasse os limites da tela
}

void Enemy::ConstrainToScreen()
{
    // Verifica o limite direito
    if (x > Level1::hud->mainRightSide - Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite esquerdo
    if (x < Level1::hud->mainLeftSide + Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite inferior
    if (y > window->Height()) {
        targetY = prevY;
    }
}

// ------------------------------------------------------------------------------

// Move o inimigo aleatoriamente
void Enemy::MoveRandomly() {
    int direction = rand() % 6;         // 4 dire��es poss�veis

    switch (direction) {
    case 0:
        //targetX = X() + VelX;
        direction = WALKRIGHT;          // Move para a direita
        break;
    case 1:
        //targetX = X() - VelX;
        direction = WALKLEFT;           // Move para a esquerda 
        break;
    case 2:
        //targetY = Y() + VelY;
        direction = WALKDOWN;           // Move para baixo
        break;
    case 3:
        //targetY = Y() - VelY;
        direction = WALKUP;             // Move para cima
        break;
    default:
        //prevX = X();                    // Atualiza a posi��o X anterior
        //prevY = Y();                    // Atualiza a posi��o Y anterior
        direction = STILL;              // Fica parado
        break;
    }
}

// ------------------------------------------------------------------------------

// Lida com a movimenta��o do inimigo
void Enemy::HandleMovement() {
    if (newX == targetX && newY == targetY) {   // Se o inimigo j� chegou ao destino anterior, ent�o, ele pode se mover novamente

        isHit = true;   // Indica que o inimigo pode atacar o jogador
        prevX = X();    // Armazena a posi��o X anterior
        prevY = Y();    // Armazena a posi��o Y anterior

        if (distance < proximityThreshold) {
            // 85% de chance de mover na dire��o do jogador
            if (rand() % 100 < 90) {
                MoveTowardsPlayer(deltaX, deltaY);
            }
            else {
                // 15% de chance de mover aleatoriamente
                MoveRandomly();
            }
        }
        else {
            // Se o jogador est� longe, move aleatoriamente
            MoveRandomly();
        }

    }
}

// ------------------------------------------------------------------------------

// Interpola o movimento do inimigo com base no tempo do jogo
void Enemy::InterpolateMovement() {

    newX = X() + (targetX - X()) * speed * gameTime;
    newY = Y() + (targetY - Y()) * speed * gameTime;

    // Ajusta a nova posi��o se estiver muito perto do alvo
    if (abs(targetX - newX) < 0.5f) newX = targetX;
    if (abs(targetY - newY) < 0.5f) newY = targetY;

    MoveTo(newX, newY); // Move o inimigo para a nova posi��o
}

// ------------------------------------------------------------------------------

// Atualiza a anima��o do inimigo
void Enemy::UpdateAnimation()
{
    anim->Select(enemyState); // Seleciona o estado atual da anima��o
    anim->NextFrame();        // Avan�a para o pr�ximo frame da anima��o
}

// ------------------------------------------------------------------------------

// Move o inimigo em dire��o ao jogador com base nas diferen�as de posi��o
void Enemy::MoveTowardsPlayer(float deltaX, float deltaY) {
    // Se a diferen�a em X for maior que a diferen�a em Y (em valor absoluto) 
    // o inimigo se move horizontalmente, caso contr�rio, se move verticalmente
    if (abs(deltaX) > abs(deltaY)) {
        //  Move horizontalmente
        if (deltaX > 0) {    // Delta X positivo significa que o jogador est� � direita
            //targetX += VelX; // Move para a direita
            direction = WALKRIGHT; // Atualiza o estado do inimigo
        }
        else {               // Delta X negativo significa que o jogador est� � esquerda
            //targetX -= VelX; // Move para a esquerda
            direction = WALKLEFT; // Atualiza o estado do inimigo
        }
    }
    else {
        // Move verticalmente
        if (deltaY > 0) {    // Delta Y positivo significa que o jogador est� abaixo
            //targetY += VelY; // Move para baixo
            direction = WALKDOWN; // Atualiza o estado do inimigo
        }
        else {               // Delta Y negativo significa que o jogador est� acima
            //targetY -= VelY; // Move para cima
            direction = WALKUP; // Atualiza o estado do inimigo
        }
    }
}

// ------------------------------------------------------------------------------

void Enemy::DisplayEnemyHealth() {
    DrawHealthBar();
    DrawHealthText();
    DrawLevel();
    DrawName();
}

// ------------------------------------------------------------------------------

void Enemy::DrawHealthBar() {
    float barWidth = 86.0f;
    float barHeight = 6.0f;
    float percent = (float)life / maxLife;
    float currentWidth = barWidth * percent;
    float offset = x - (barWidth - currentWidth) / 2;

    hudLife->Draw(x, y - (45.0f + hudLife->Height()));
    lifeSprite->DrawResize(offset, y - (46.0f + hudLife->Height()), currentWidth, barHeight);
}

// ------------------------------------------------------------------------------

void Enemy::DrawHealthText() {
    std::string vidaTexto = std::to_string(life) + "/" + std::to_string(maxLife);
    press12->Draw(x - 13.0f, y - 40.0f, vidaTexto, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 0.8f);
}

// ------------------------------------------------------------------------------

void Enemy::DrawLevel() {
    press12->Draw((x + 15) - width / 2.0f, y - 80.0f, "Nv:" + std::to_string(level), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 0.8f);
}

// ------------------------------------------------------------------------------

void Enemy::DrawName() {
    press12->Draw(x - width / 2.0f, y - 100.0f, name, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f);
}

// ------------------------------------------------------------------------------