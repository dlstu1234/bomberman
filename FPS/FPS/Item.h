#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(int x, int y);
	virtual ~Item();

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;

	//���ͷ��� �߰��� ����ζ�?
	virtual void Interaction(class Hero* a_refHero) override;
	
	//������ Ÿ�� �߰��� �⺻���� none
	eItem m_eType = eItem::None;
};