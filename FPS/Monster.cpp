#include "pch.h"
#include "Monster.h"

#include "Player.h"
#include "GameManager.h"

//생성자에서 몬스터 생성해주는듯?
Monster::Monster(int x, int y) : Object(x, y)
, m_Data{
		{ '1', '1', '1', '1', '1' },
		{ '1', 'M', 'M', 'M', '1' },
		{ '1', 'M', 'M', 'M', '1' },
		{ '1', 'M', 'M', 'M', '1' },
		{ '1', '1', '1', '1', '1' }
}
{
	m_pNowAni = &m_Data;
}

Monster::~Monster()
{
}

eObjectType Monster::GetObjectType() const
{
	return eObjectType::Monster;
}

bool Monster::CanMove() const
{
	return true;
}

//플레이어와의 상호작용
bool Monster::Interaction(Player* a_refHero)
{
	if( IsCross(a_refHero) == true )
	{
		GameMng()->Die(this);
	}

	return false;
}

bool Monster::Explosived()
{
	--m_nLife;
	if (m_nLife <= 0)
	{
		GameMng()->AddScore(MonsterScore);
		return true;
	}

	return false;
}