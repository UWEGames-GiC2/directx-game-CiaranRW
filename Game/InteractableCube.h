#pragma once
#include "CMOGO.h"

class InteractableCube : public CMOGO
{

public:
	InteractableCube(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF);
	~InteractableCube();

	virtual void Tick(GameData* _GD) override;

	std::vector<std::shared_ptr<CMOGO>> projectiles;

protected:
	float ShootTimer = 0.0f;
	bool CanShoot = true;
	
};
