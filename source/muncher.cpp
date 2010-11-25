#include "muncher.h"

Muncher::Muncher(Player* owner, Game* game, CIwFVec2 position)
		 : Unit(100.0f, 50.0f, 10.0f, 25.0f, 10.0f, 5.0f, 10.0f, 0.0f, 0.0f, owner, game, position)
{
	spriteSize = 256;
	numFrames = 12;
	curFrame = 0;
    scale = 0.2f;
}

bool Muncher::update() {
    curFrame = (curFrame + 1) % numFrames;
   
    if(curFrame == 0)
        game->getAI()->updateAI(this);
    
	return true;
}

const char* Muncher::getTextureName() {
	return "muncher_sprite_sheet";
}