#include "pch.h"
#include "Player.h"

//�����ڿ��� �����ͷ� �־ �������ִµ�
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