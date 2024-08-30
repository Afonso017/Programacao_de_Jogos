// ONEBITADVENTURE_H

#ifndef ONEBITADVENTURE_H
#define ONEBITADVENTURE_H

// ------------------------------------------------------------------------------

enum OneBitObjects // Enumera��o dos tipos de objetos
{
    PLAYER,
    ENEMY,
    PROP,
    DOOR,
    CHEST,
    COIN,
	GRASS,
    WALL,
    TREE,
    PILLAR,
    FENCE,
	CAMPFIRE
};

// ------------------------------------------------------------------------------

enum DirectingAnimation // Enumera��o dos estados de movimenta��o
{ 
    STILL, 
    WALKUP, 
    WALKDOWN, 
    WALKLEFT, 
    WALKRIGHT,
    DAMAGE
};

// ------------------------------------------------------------------------------

enum MovementType // Enumera��o dos estados de anima��o
{
	ATACK, WALK, BACK, IDLE
};

// ------------------------------------------------------------------------------

#endif // ONEBITADVENTURE_H
