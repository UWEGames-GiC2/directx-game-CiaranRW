#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "CMOGO.h"

//=================================================================
//Base Player Class (i.e. a GO the player controls)
//=================================================================

class Player : public CMOGO
{

public:
	Player(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Player();

	virtual void Tick(GameData* _GD) override;

	std::vector<std::shared_ptr<CMOGO>> projectiles;


protected:
	float gravity = 800.0;
	float speed = 200.0;
	bool sprint = false;

};

#endif