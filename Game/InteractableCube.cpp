#include "pch.h"
#include "InteractableCube.h"
#include <dinput.h>
#include "GameData.h"

InteractableCube::InteractableCube(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	m_fudge = Matrix::CreateRotationY(XM_PI);

	//m_pos.x = 10.0f;
	m_pos.y = 1.0f;
	//m_pos.z = 10.0f;
	//SetScale(Vector3::One * 0.05f);
	SetDrag(0.7);
	SetPhysicsOn(true);
}

InteractableCube::~InteractableCube()
{

}

void InteractableCube::Tick(GameData* _GD)
{
	float rotSpeed = 2.0f * _GD->m_dt;
	if (_GD->m_MS.x)
	{
		m_yaw -= rotSpeed * _GD->m_MS.x;
	}
	if (_GD->m_MS.y)
	{
		m_pitch -= rotSpeed * _GD->m_MS.y;
	}

	if (_GD->m_MS_tracker.leftButton)
	{
		//printf("pressed B \n");
		bool foundProjectile = false;
		for (size_t i = 0; i < projectiles.size(); i++)
		{
			
			if (!projectiles[i]->IsActive())
			{
				//printf("Found usable projectile\n");
				Vector3 forwardMove = 40.0f * Vector3::Forward;
				Matrix rotMove = Matrix::CreateRotationY(m_yaw) * Matrix::CreateRotationX(m_pitch);
				forwardMove = Vector3::Transform(forwardMove, rotMove);
				projectiles[i]->SetPos(this->GetPos());
				projectiles[i]->SetActive(true);
				projectiles[i]->SetYaw(this->GetYaw());
				projectiles[i]->SetPitch(this->GetPitch());
				projectiles[i]->SetDrag(0.01f);
				projectiles[i]->SetPhysicsOn(true);
				projectiles[i]->SetAcceleration(forwardMove * 100.0f);
				break;
			}
		}
	}




	CMOGO::Tick(_GD);
}