#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(int x, int y);
	virtual ~Item();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	//인터렉션 추가됨 히어로랑?
	virtual void Interaction(class Hero* a_refHero) override;
	
	//아이템 타입 추가됨 기본세팅 none
	eItem m_eType = eItem::None;
};