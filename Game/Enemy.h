#pragma once
#include "CMOGO.h"

class Enemy : public CMOGO
{

public:
	Enemy(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~Enemy();

	virtual void Tick(GameData* _GD) override;


protected:


};