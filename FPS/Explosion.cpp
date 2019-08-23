#include "pch.h"
#include "Explosion.h"

#include "Ani.h"

Explosion::Explosion(int x, int y) : Object(x,y), m_pAni(new Ani())
{
	m_pAni->Resize(1);
	m_pAni->Add(0,
		{
			{{"* * *"},
			 {"     "},
			 {"* * *"},
			 {"     "},
			 {"* * *"}},
			{{" * * "},
			 {"*   *"},
			 {"  *  "},
			 {"*   *"},
			 {" * * "}}
		}
	);

	m_pAni->SetState(0);
	m_pNowAni = m_pAni->Get();
}


Explosion::~Explosion()
{
	SAFE_DELETE(m_pAni);
}

eObjectType Explosion::GetObjectType() const
{
	return eObjectType::Explosion;
}

bool Explosion::CanMove() const
{
	return true;
}