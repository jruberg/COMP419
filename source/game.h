#ifndef _GAME_H
#define _GAME_H

#include "IwArray.h"

class Game;
class Artist;
class Unit;

#include "player.h"
#include "gridcell.h"
#include "uimanager.h"
#include "IwResManager.h"

class Game {
	
    private:
	
        CIwArray<Player*> players;
        int numPlayers;
        
        CIwArray<Unit*> units;

		Artist* artist;
		UIManager* ui_manager;

		CIwResGroup* resources;
	
		long timesteps;
	                    
    public:
	
        Game(int numPlayers);
		~Game();
        
        void addUnit(Unit *u);
		CIwArray<Unit*>* getUnits();
        
        Artist* getArtist();
	
		void tick();
	
		void render();
		
		long getTimesteps();

};

#endif