#include "game.h"
#include "unit.h"
 
Game::Game(int numPlayers) : numPlayers(numPlayers), numUnits(0) {
	//ai = AI();
	IwGetResManager()->LoadGroup("resource_groups/game.group");
	sprites = IwGetResManager()->GetGroupNamed("Sprites");
	game = IwGetResManager()->GetGroupNamed("Game");
	initRenderState();
}

Game::~Game(){
    	
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
		(*itr).second->clear();
		delete (*itr).second;
	}
	
	units.clear();
	unitBuffer.clear();
}

void Game::initRenderState() {
	
	//set up the camera position and view transform
	IwGxSetPerspMul(0x9);
	IwGxSetFarZNearZ(0xa, 0x8);
	CIwMat view = CIwMat::g_Identity;
	view.SetTrans(CIwVec3(300, 0, -9));
	IwGxSetViewMatrix(&view);
}

std::list<Unit*>* Game::getUnits(){
	return &units;
}

void Game::addUnit(Unit *u){
	
    u->setId(numUnits++);

	if(units.empty()) {
		units.push_back(u);
	} else {
		unitBuffer.push_back(u);
	}
    
    unitBuffer.sort();
	
	if(unitBucket.find(u->getTextureName()) == unitBucket.end())
		unitBucket[u->getTextureName()] = new std::set<Unit*>();
	
	(unitBucket[u->getTextureName()])->insert(u);
}

void Game::tick(){

	float curr_theta, new_theta;

	for(std::list<Unit*>::iterator itr = units.begin(); itr !=units.end(); ++itr) {
		(*itr)->update();
		curr_theta = (*itr)->getTheta();
        
        //while(curr_theta >= unitBuffer.front()){
        //    units.insert((++itr), unitBuffer.pop_front());
        //} 
	}
    
    units.merge(unitBuffer);
	
    int asklfjaslfkj = units.size();
    int alskfjsakfjal = 1;
    
    ++timesteps;
	render();
}

void Game::render() {
	renderWorld();
	renderSprites();
	
	IwGxSwapBuffers();
}

void Game::renderSprites() {
	
	char* curTexture = "";
	CIwMaterial* mat = new CIwMaterial();
	
	for (UnitBucket::iterator itr = unitBucket.begin(); itr != unitBucket.end(); ++itr) {
		
		if (strcmp((*itr).first, curTexture) != 0) {
			curTexture = (*itr).first;
			mat->SetTexture((CIwTexture*)sprites->GetResNamed(curTexture, IW_GX_RESTYPE_TEXTURE));
			mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
			mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
			IwGxSetMaterial(mat);
		}
		
		std::set<Unit*>* renderUnits = (*itr).second;
		
        int c = 0;
		for (std::set<Unit*>::iterator u_it = renderUnits->begin(); u_it != renderUnits->end(); ++u_it) {
            c++;
			(*u_it)->display();
		}
	}
	delete mat;
}

void Game::renderWorld() {

	CIwMaterial* mat = new CIwMaterial();
	mat->SetTexture((CIwTexture*)game->GetResNamed("paper-world", IW_GX_RESTYPE_TEXTURE));
	mat->SetModulateMode(CIwMaterial::MODULATE_NONE);
	mat->SetAlphaMode(CIwMaterial::ALPHA_DEFAULT);
	IwGxSetMaterial(mat);
    
    static int rot = 0;
    rot++;
	
    renderImageWorldSpace(CIwSVec2(60, 0), rot, .7, 960);
	
	delete mat;
}

CIwFVec2 Game::getWorldRadius() {
	return CIwFVec2(innerRadius, outerRadius);
}
