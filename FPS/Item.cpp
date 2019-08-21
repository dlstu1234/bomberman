#include "pch.h"
#include "Item.h"
#include "GameManager.h"

//��⵵ �����ڿ��� ������ �־ ����
Item::Item(int x, int y) : Object(x, y),
m_Item {
	{
		{ 'X', '-', '-', '-', 'X' },
		{ '|', 'X', ' ', 'X', '|' },
		{ '|', ' ', 'X', ' ', '|' },
		{ '|', 'X', ' ', 'X', '|' },
		{ 'X', '-', '-', '-', 'X' },
	},

	{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
	},

	{
			{ 'X', '-', '-', '-', 'X' },
			{ '|', 'X', ' ', 'X', '|' },
			{ '|', ' ', 'X', ' ', '|' },
			{ '|', 'X', ' ', 'X', '|' },
			{ 'X', '-', '-', '-', 'X' },
	},
}
{
	m_pNowAni = &m_Item[0];
}
Item::~Item() { }

eObjectType Item::GetObjectType() const
{
	return eObjectType::Item;
}

//������ ���ͷ��� �ϸ�? ���ӸŴ����� ���� ������Ʈ ����� ������ �߰�? �߰��ε�
void Item::Interaction(class Hero* a_refHero)
{
	GameMng()->RemoveObject(this);
	GameMng()->ObtainItem(m_eType);
}

void Item::Render()
{

}