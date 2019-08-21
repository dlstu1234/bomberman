#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	//그리기 추가됨 데이터랑?
	virtual void Render() override;

	RenderTile	m_Data;
};


