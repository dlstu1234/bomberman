#include "pch.h"
#include "Player.h"

//생성자에서 데이터로 넣어서 생성해주는듯
Player::Player(int x, int y) : Object(x, y)
, m_Data{
		{ 'P', 'P', 'P', 'P', 'P' },
		{ 'P', ' ', ' ', ' ', 'P' },
		{ 'P', ' ', ' ', ' ', 'P' },
		{ 'P', ' ', ' ', ' ', 'P' },
		{ 'P', 'P', 'P', 'P', 'P' } }
{
	m_pNowAni = &m_Data;
}


Player::~Player()
{
}

eObjectType Player::GetObjectType() const
{
	return eObjectType::Player;
}

void Player::Render()
{

}