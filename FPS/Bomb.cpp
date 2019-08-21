#include "pch.h"
#include "Bomb.h"
#include "GameManager.h"

Bomb::Bomb(int x, int y) : Object(x, y)
, m_Data{
		{ '1', '1', '1', '1', '1' },
		{ '1', 'B', 'B', 'B', '1' },
		{ '1', 'B', 'B', 'B', '1' },
		{ '1', 'B', 'B', 'B', '1' },
		{ '1', '1', '1', '1', '1' },
}
{
	m_pNowAni = &m_Data;
}
Bomb::~Bomb() { }

eObjectType Bomb::GetObjectType() const
{
	return eObjectType::Bomb;
}

//getbombdata에 자신을 넣음 bmob 클래스의 값을?
void Bomb::Init()
{
	GameMng()->GetBombData(this);
}

//폭탄의 업데이트 아마 터지는것?
void Bomb::Update(float a_fDelta)
{
	m_fLifeTime -= a_fDelta;

	if (m_fLifeTime <= 0.0f)
	{
		// Bomb!
	}
}
//터지고 나서의 효과?추가될거같음
void Bomb::Explosived(Bomb* a_refBomb)
{
	if (a_refBomb == this) { return; }

	// Bomb!
}

void Bomb::Render()
{

}