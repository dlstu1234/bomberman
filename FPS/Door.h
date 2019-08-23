#pragma once
#include "Object.h"

class Door : public Object
{
public:
	//���� ������ ������ Ȯ���ϴ� Ÿ��?
	enum class eDoorState
	{
		Close,
		Open,
	};

	Door(int x, int y);
	virtual ~Door();

	// Object��(��) ���� ��ӵ�
	virtual eObjectType GetObjectType() const override;
	virtual bool CanMove() const override;

	virtual void Init() override;
	virtual bool Interaction(class Player* a_refHero) override;
	
	// ���� ���� ����?
	eDoorState m_eState = eDoorState::Close;

	//�����ſ� ����Ÿ�� �׸���?
	RenderTile	m_Close;
	RenderTile	m_Open;
};
