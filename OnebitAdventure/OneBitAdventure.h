// ONEBITADVENTURE_H

#ifndef ONEBITADVENTURE_H
#define ONEBITADVENTURE_H

// ------------------------------------------------------------------------------

enum OneBitObjects // Enumeração dos tipos de objetos
{
    PLAYER,
    ENEMY,
    PROP,
};

// ------------------------------------------------------------------------------

enum DirectingAnimation // Enumeração dos estados de movimentação
{ 
    STILL, 
    WALKUP, 
    WALKDOWN, 
    WALKLEFT, 
    WALKRIGHT,
    DAMAGE
};

// ------------------------------------------------------------------------------

enum MovementType // Enumeração dos estados de animação
{
	ATACK, WALK, BACK, IDLE
};

// ------------------------------------------------------------------------------

#endif // ONEBITADVENTURE_H
