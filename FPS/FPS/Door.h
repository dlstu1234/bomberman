#pragma once
#include "Object.h"

class Door : public Object
{
public:
	//문이 열린지 닫힌지 확인하는 타입?
	enum class eDoorState
	{
		Close,
		Open,
	};

	Door(int x, int y);
	virtual ~Door();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	//추가됨
	virtual void Init() override;
	virtual void Interaction(class Hero* a_refHero) override;
	
	// 문의 현재 상태?
	eDoorState m_eState = eDoorState::Close;
};
