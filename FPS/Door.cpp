#include "pch.h"
#include "Door.h"
#include "GameManager.h"

Door::Door(int x, int y) : Object(x, y)
, m_Close{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
}
, m_Open{
			{ ' ', 'D', 'D', 'D', ' ' },
			{ 'D', ' ', ' ', ' ', 'D' },
			{ 'D', ' ', ' ', ' ', 'D' },
			{ 'D', ' ', ' ', ' ', 'D' },
			{ ' ', 'D', 'D', 'D', ' ' },
} {
	m_pNowAni = &m_Close;
}

Door::~Door()
{
}

eObjectType Door::GetObjectType() const
{
	return eObjectType::Door;
}

//문이 닫힘
void Door::Init()
{
	m_eState = eDoorState::Close;
}

//문과 인터렉션 닫혀있으면 리턴해주고 아니면 스테이지 시작으로 이동?
bool Door::Interaction(class Player* a_refHero)
{
	if (m_eState == eDoorState::Close) { return false; }

	if( IsCross(a_refHero) == true )
	{
		GameMng()->StageEnd();
	}

	return false;
}
