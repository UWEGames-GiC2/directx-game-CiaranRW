#include "pch.h"
#include "Enemy.h"
#include <dinput.h>
#include "GameData.h"

Enemy::Enemy(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_fudge = Matrix::CreateRotationY(XM_PI);

	//m_pos.x = 10.0f;
	m_pos.y = 1.0f;
	//m_pos.z = 10.0f;
	SetDrag(0.7);
	SetPhysicsOn(true);
}

Enemy::~Enemy()
{
	//tidy up anything I've created

}



void Enemy::Tick(GameData* _GD)
{
	







	CMOGO::Tick(_GD);
}