#include "pch.h"
#include "Player.h"
#include <dinput.h>
#include "GameData.h"

Player::Player(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	//any special set up for Player goes here
	m_fudge = Matrix::CreateRotationY(XM_PI);

	m_pos.y = 10.0f;

	SetDrag(0.7);
	SetPhysicsOn(true);

}

Player::~Player()
{
	//tidy up anything I've created

}


void Player::Tick(GameData* _GD)
{
	if (_GD->m_KBS_tracker.pressed.LeftShift)
	{
		sprint = !sprint;
	}
	if (sprint)
	{
		speed = 60.0f;
	}
	if (!sprint)
	{
		speed = 30.0f;
	}

	switch (_GD->m_GS)
	{
	case GS_PLAY_MAIN_CAM:
	{
		//TURN AND FORWARD CONTROL HERE
		Vector3 forwardMove = speed * Vector3::Forward;
		Vector3 sideMove = 20.0f * Vector3::Left;
		Matrix rotMove = Matrix::CreateRotationY(m_yaw);
		forwardMove = Vector3::Transform(forwardMove, rotMove);
		sideMove = Vector3::Transform(sideMove, rotMove);
		if (_GD->m_KBS.W)
		{
			m_acc += forwardMove;
		}
		if (_GD->m_KBS.S)
		{
			m_acc -= forwardMove;
		}
		if (_GD->m_KBS.A)
		{
			m_acc += sideMove;
		}
		if (_GD->m_KBS.D)
		{
			m_acc -= sideMove;
		}
		break;
	}
	case GS_PLAY_TPS_CAM:
	{
		//TURN AND FORWARD CONTROL HERE
		Vector3 forwardMove = speed * Vector3::Forward;
		Vector3 sideMove = 20.0f * Vector3::Left;
		Matrix rotMove = Matrix::CreateRotationY(m_yaw);
		forwardMove = Vector3::Transform(forwardMove, rotMove);
		sideMove = Vector3::Transform(sideMove, rotMove);
		if (_GD->m_KBS.W)
		{
			m_acc += forwardMove;
		}
		if (_GD->m_KBS.S)
		{
			m_acc -= forwardMove;
		}
		if (_GD->m_KBS.A)
		{
			m_acc += sideMove;
		}
		if (_GD->m_KBS.D)
		{
			m_acc -= sideMove;
		}
		break;
	}
	}

	//change orinetation of player
	float rotSpeed = 2.0f * _GD->m_dt;
	if (_GD->m_MS.x)
	{
		m_yaw -= rotSpeed * _GD->m_MS.x;
	}
	//if (_GD->m_MS.y)
	//{
	//	m_pitch -= rotSpeed * _GD->m_MS.y;
	//}

	//move player up and down
	if (_GD->m_KBS_tracker.pressed.Space)
	{
		if (_GD->m_can_jump)
		{
			m_acc.y += jump * _GD->m_dt;
		}
	}

	//WHERE PROJECTILES DONE
	//if (_GD->m_KBS_tracker.pressed.B)
	//if (_GD->m_MS.leftButton)
	//{	
	//	//printf("pressed B \n");
	//	bool foundProjectile = false;
	//	for (size_t i = 0; i < projectiles.size(); i++)
	//	{
	//		if (!projectiles[i]->IsActive())
	//		{
	//			printf("Found usable projectile\n");
	//			Vector3 forwardMove = 40.0f * Vector3::Forward;
	//			Matrix rotMove = Matrix::CreateRotationY(m_yaw) * Matrix::CreateRotationX(m_pitch);
	//			forwardMove = Vector3::Transform(forwardMove, rotMove);
	//			projectiles[i]->SetPos(this->GetPos());
	//			projectiles[i]->SetActive(true);
	//			projectiles[i]->SetYaw(this->GetYaw());
	//			projectiles[i]->SetPitch(this->GetPitch());
	//			projectiles[i]->SetDrag(0.01f);
	//			projectiles[i]->SetPhysicsOn(true);
	//			projectiles[i]->SetAcceleration(forwardMove * 100.0f);
	//			break;
	//		}
	//	}
	//}

	//limit motion of the player
	float length = m_pos.Length();
	float maxLength = 500.0f;
	if (length > maxLength)
	{
		m_pos.Normalize();
		m_pos *= maxLength;
		m_vel *= -0.9; //VERY simple bounce back
	}

	if (_GD->gravity_on)
	{
		m_acc.y -= gravity * _GD->m_dt;
	}

	//apply my base behaviour
	CMOGO::Tick(_GD);
}