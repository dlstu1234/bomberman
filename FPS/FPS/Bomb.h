#pragma once
#include "Object.h"
class Bomb : public Object
{
public:
	Bomb(int x, int y);
	virtual ~Bomb();

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;

	//�߰��� - ������Ʈ�� �����°�
	void Init() override;
	void Update(float a_fDelta) override;
	void Explosived(class Bomb* a_refBomb) override;

	//��ź�� ���� �߰���
	float	m_fLifeTime = 2.0f;
	int		m_nExplosiveRange = 2;
};

