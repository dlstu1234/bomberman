#pragma once
//오브젝트 클래스
class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	virtual void Init();
	virtual void Update(float a_fDelta);
	//랜더 추가됨
	virtual void Render();
	//터지는거랑 인터렉션 추가됨
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);

	//좌표랑 맵 세팅?
	inline void SetPos(int _x, int _y) { x = _x; y = _y; }
	inline void SetMap(char** a_refMap) { assert(a_refMap != nullptr); m_refMap = a_refMap; }

public:
	int x;
	int y;

protected:
	//맵 관련?
	char** m_refMap = nullptr;
	RenderTile* m_pNowAni = nullptr;
};


