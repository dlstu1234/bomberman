#include "pch.h"
#include "Player.h"

//생성자에서 데이터로 넣어서 생성해주는듯
Player::Player(int x, int y) : Object(x, y)
, m_Data{
		{ ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', 'P', ' ', 'P', ' ' },
		{ ' ', 'P', 'P', 'P', ' ' },
		{ ' ', ' ', ' ', ' ', ' ' } }
{
	m_pNowAni = &m_Data;

	rt.x += 1;
	rt.y += 1;
	rt.w = TileSize - 2;
	rt.h = TileSize - 2;
}

//상태 비워주기
Player::~Player()
{
	m_refStat = nullptr;
}

eObjectType Player::GetObjectType() const
{
	return eObjectType::Player;
}
//충돌 처리
Rect Player::GetRendertRect() const
{
	return Rect{ rt.x -1, rt.y - 1, rt.w, rt.h };
}
//상태 세팅
void Player::SetStat(struct CharacterData* a_pStat)
{
	m_refStat = a_pStat;
	m_nPutBombCount = 0;
}

bool Player::_Update(float a_fDelta)
{
	Move(a_fDelta);
	BombCheck();
	
	return false;
}
//플레이어 움직임
void Player::Move(float a_fDeltaTime)
{
	float fAdd = a_fDeltaTime * (m_refStat->fMoveSeepd);

	float fX = 0;
	float fY = 0;

	if (IsKeyDown(eKey::A)) { fX -= fAdd; }
	if (IsKeyDown(eKey::D)) { fX += fAdd; }

	if (IsKeyDown(eKey::S)) { fY += fAdd; }
	if (IsKeyDown(eKey::W)) { fY -= fAdd; }

	rt.x += fX;
	rt.y += fY;
}
//플레이어가 폭탄 설치체크
void Player::BombCheck()
{
	if(m_nPutBombCount >= m_refStat->nBombCount)  { return; }

	if (IsKeyDown(eKey::Space))
	{
		COORD c = rt.Center();
		if( GameMng()->AddBomb(c.X, c.Y) == true )
		{
			++m_nPutBombCount;
		}
	}
}