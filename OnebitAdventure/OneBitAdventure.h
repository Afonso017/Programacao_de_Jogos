#pragma once
#ifndef ONEBITADVENTURE_H
#define ONEBITADVENTURE_H

// ------------------------------------------------------------------------------

enum OneBitObjects
{
    PLAYER,
    ENEMY,
    SPECIAL,
};

// ------------------------------------------------------------------------------

enum steeringState 
{ 
    STILL, 
    WALKUP, 
    WALKDOWN, 
    WALKLEFT, 
    WALKRIGHT,
    DAMAGE
};

// ------------------------------------------------------------------------------

#endif // ONEBITADVENTURE_H