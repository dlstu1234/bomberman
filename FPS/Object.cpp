#include "pch.h"
#include "Object.h"

RenderTile Object::Empty = RenderTile{
	{"     "},
	{"     "},
	{"     "},
	{"     "},
	{"     "},
};
//������Ʈ�� ��ǥ? ����
Object::Object(int _x, int _y) : x(_x), y(_y) 
{
	rt.x = (float)(_x * TileSize);
	rt.y = (float)(_y * TileSize);
	rt.w = TileSize; 
	rt.h = TileSize;
}
//�Ҹ��Ҷ� nillptr�� �ʱ�ȭ
Object::~Object() 
{
	m_pNowAni = nullptr;
	m_refMap = nullptr;	
}

void Object::Init() { }
//����
void Object::Explosived(class Bomb* a_refBomb) { }
//���� ����
bool Object::Interaction(class Player* a_refHero) { return false; }
void Object::_PreUpdate(float a_fDelta) {}
bool Object::_Update(float a_fDelta) { return false; }

//�� ����
void Object::SetMap(char** a_refMap)
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}

//������Ʈ ����������Ʈ�� �ҷ����ų� _������Ʈ�� ����
bool Object::Update(float a_fDelta)
{
	_PreUpdate(a_fDelta);
	return _Update(a_fDelta);
}
//�浹�ϸ� ����!
Rect Object::GetRendertRect() const
{
	return rt;
}

//�׸��� �����
void Object::RenderClear()
{
	//�浹�ϸ�!
	Rect rt = GetRendertRect();
	int nX = (int)rt.x;
	int nY = (int)rt.y;
	//�� ��ǥ üũ?
	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			Empty[i], TileSize * sizeof(char));
	}
}

//������Ʈ ����
void Object::Render()
{
	Rect rt = GetRendertRect();
	int nX = (int)rt.x;
	int nY = (int)rt.y;

	//�޸� ī�ǽ����� �׸�
	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			(*m_pNowAni)[i], TileSize * sizeof(char));
	}
}


