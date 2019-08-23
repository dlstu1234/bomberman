#pragma once
#include "Object.h"

class Player : public Object
{
public:
	Player(int x, int y);
	virtual ~Player();

	// Object을(를) 통해 상속됨
	virtual eObjectType GetObjectType() const override;
	virtual Rect GetRendertRect() const override;
	
	//상태 저장?
	void SetStat(struct CharacterData* a_pStat);

private:
	//움직임
	void Move(float a_fDeltaTime);
	//폭탄 체크
	void BombCheck();

protected:
	virtual bool _Update(float a_fDelta);

	RenderTile	m_Data;
	struct CharacterData* m_refStat;

public:
	int m_nPutBombCount = 0;
};


