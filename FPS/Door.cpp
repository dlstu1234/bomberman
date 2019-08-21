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
			{ ' ', '1', '1', '1', ' ' },
			{ '1', ' ', ' ', ' ', '1' },
			{ '1', ' ', ' ', ' ', '1' },
			{ '1', ' ', ' ', ' ', '1' },
			{ ' ', '1', '1', '1', ' ' },
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
void Door::Interaction(class Hero* a_refHero)
{
	if (m_eState == eDoorState::Close) { return; }

	GameMng()->StageStart();
}

void Door::Render()
{

}