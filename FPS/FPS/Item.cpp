#include "pch.h"
#include "Item.h"
#include "GameManager.h"

Item::Item(int x, int y) : Object(x, y) { }
Item::~Item() { }

eObjectType Item::GetObjectType() const
{
	return eObjectType::Item;
}

//아이템 인터렉션 하면? 게임매니져로 가서 오브젝트 지우고 아이템 추가? 추가인듯
void Item::Interaction(class Hero* a_refHero)
{
	GameMng()->RemoveObject(this);
	GameMng()->ObtainItem(m_eType);
}
