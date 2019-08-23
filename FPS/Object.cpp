#include "pch.h"
#include "Object.h"

RenderTile Object::Empty = RenderTile{
	{"     "},
	{"     "},
	{"     "},
	{"     "},
	{"     "},
};
//오브젝트의 좌표? 생성
Object::Object(int _x, int _y) : x(_x), y(_y) 
{
	rt.x = (float)(_x * TileSize);
	rt.y = (float)(_y * TileSize);
	rt.w = TileSize; 
	rt.h = TileSize;
}
//소멸할때 nillptr로 초기화
Object::~Object() 
{
	m_pNowAni = nullptr;
	m_refMap = nullptr;	
}

void Object::Init() { }
//폭발
void Object::Explosived(class Bomb* a_refBomb) { }
//현재 상태
bool Object::Interaction(class Player* a_refHero) { return false; }
void Object::_PreUpdate(float a_fDelta) {}
bool Object::_Update(float a_fDelta) { return false; }

//맵 세팅
void Object::SetMap(char** a_refMap)
{
	assert(a_refMap != nullptr);
	m_refMap = a_refMap;
}

//업데이트 프리업데이트를 불러오거나 _업데이트를 리턴
bool Object::Update(float a_fDelta)
{
	_PreUpdate(a_fDelta);
	return _Update(a_fDelta);
}
//충돌하면 리턴!
Rect Object::GetRendertRect() const
{
	return rt;
}

//그린거 지우기
void Object::RenderClear()
{
	//충돌하면!
	Rect rt = GetRendertRect();
	int nX = (int)rt.x;
	int nY = (int)rt.y;
	//맵 좌표 체크?
	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			Empty[i], TileSize * sizeof(char));
	}
}

//오브젝트 랜더
void Object::Render()
{
	Rect rt = GetRendertRect();
	int nX = (int)rt.x;
	int nY = (int)rt.y;

	//메모리 카피식으로 그림
	for (int i = 0; i < TileSize; ++i)
	{
		char* pDest = m_refMap[nY + i];

		memcpy_s((pDest + nX), TileSize * sizeof(char),
			(*m_pNowAni)[i], TileSize * sizeof(char));
	}
}


