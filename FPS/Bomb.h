#pragma once
#include "Object.h"
class Bomb : public Object
{
public:
	Bomb(int x, int y);
	virtual ~Bomb();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;

	//업데이트랑 터지는거
	void Init() override;
	void Update(float a_fDelta) override;
	void Explosived(class Bomb* a_refBomb) override;

	//폭탄의 정보
	float	m_fLifeTime = 2.0f;
	int		m_nExplosiveRange = 2;
	RenderTile	m_Data;
};

