#include "pch.h"
#include "Item.h"
#include "GameManager.h"
#include "Ani.h"

#include "Player.h"

//생성자에서 데이터 넣어서 생성
Item::Item(int x, int y) : Object(x, y), m_pAni(new Ani())
{
	//랜덤한 수 구하기
	int nNum = (rand() % (int)eItem::Max);
	m_eType = (eItem)nNum;
	
	m_pAni->Resize((int)eItem::Max);
	m_pAni->Add((int)eItem::PowerUp, 
		{
		   {{"     "},
			{"|   |"},
			{"| P |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"| P |"},
			{"|   |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|   |"},
			{"|   |"},
			{"| P |"},
			{"     "}},
		}
	);

	m_pAni->Add((int)eItem::SpeedUp,
		{
		   {{"     "},
			{"|   |"},
			{"| S |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"| S |"},
			{"|   |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|   |"},
			{"|   |"},
			{"| S |"},
			{"     "}},
		}
	);

	m_pAni->Add((int)eItem::BombCount,
		{
		   {{"     "},
			{"|   |"},
			{"|B-C|"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|B-C|"},
			{"|   |"},
			{"|   |"},
			{"     "}},

		   {{"     "},
			{"|   |"},
			{"|   |"},
			{"|B-C|"},
			{"     "}},
		}
	);

	m_pAni->SetState((int)m_eType);
	m_pNowAni = m_pAni->Get();
}
Item::~Item() 
{ 
	SAFE_DELETE(m_pAni);
}

eObjectType Item::GetObjectType() const
{
	return eObjectType::Item;
}

//아이템 인터렉션 하면? 게임매니져로 가서 오브젝트 지우고 아이템 추가? 추가인듯
bool Item::Interaction(class Player* a_refHero)
{
	//플레이어랑 겹치면 랜덤한 아이템과 상호작용
	if( IsCross(a_refHero) == true )
	{
		GameMng()->ObtainItem(m_eType);
		return true;
	}

	return false;
}

bool Item::CanMove() const
{
	return true;
}

//업데이트 그린거 지워주는듯
void Item::_PreUpdate(float a_fDelta)
{
	RenderClear();
}
//업데이트 Ani클래스의 업데이트와 겟을 불러오는듯
bool Item::_Update(float a_fDelta)
{
	m_pAni->Update(a_fDelta);
	m_pNowAni = m_pAni->Get();

	return false;
}