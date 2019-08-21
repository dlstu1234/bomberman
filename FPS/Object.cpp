#include "pch.h"
#include "Object.h"

Object::Object(int _x, int _y) : x(_x), y(_y) { }

Object::~Object() { }

void Object::Init() { }
void Object::Update(float a_fDelta) { }
//랜더 추가댐
void Object::Render()
{
	int nX = x * TileSize;
	int nY = y * TileSize;

	//타일 사이즈까지 돌면서 맵을 싺돌림
	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			m_pNowAni[i], TileSize * sizeof(char));
	}
}
void Object::Explosived(class Bomb* a_refBomb) { }
void Object::Interaction(class Hero* a_refHero) { }

