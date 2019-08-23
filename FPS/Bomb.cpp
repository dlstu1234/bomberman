#include "pch.h"
#include "Bomb.h"
#include "GameManager.h"
#include "Ani.h"

Bomb::Bomb(int x, int y) : Object(x, y), m_pAni(new Ani())
{
	m_pAni->Resize(1);
	m_pAni->Add(0,
		{
		   {{"XXXXX"},
			{"XXXXX"},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"xxxxx"},
			{"xxxxx"},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"XXXXX"},
			{"XXXXX"},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"xxxxx"},
			{"xxxxx"},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{" XXX "},
			{" XXX "},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{" xxx "},
			{" xxx "},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"  X  "},
			{"  X  "},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"  x  "},
			{"  x  "},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"     "},
			{"  x  "},
			{"|   |"},
			{"| B |"},
			{"#####"}},

		   {{"     "},
			{"     "},
			{"|   |"},
			{"| B |"},
			{"#####"}},
		}
	);

	m_pAni->SetState(0);
	m_pNowAni = m_pAni->Get();
}

//소멸할때 삭제
Bomb::~Bomb() 
{ 
	SAFE_DELETE(m_pAni);
}

eObjectType Bomb::GetObjectType() const
{
	return eObjectType::Bomb;
}

//getbombdata에 자신을 넣음 bmob 클래스의 값을?
void Bomb::Init()
{
	GameMng()->GetBombData(OUT this);
}

//폭탄의 업데이트 아마 터지는것?
bool Bomb::_Update(float a_fDelta)
{
	// 애니
	m_pAni->Update(a_fDelta);
	m_pNowAni = m_pAni->Get();

	// 수명
	m_fLifeTime -= a_fDelta;
	if (m_fLifeTime <= 0.0f)
	{
		COORD c = rt.Center();
		GameMng()->ResistExplosion(this, c.X, c.Y, m_nExplosiveRange);

		//로그 띄워줌 폭발의 좌표?
		std::string s = "Explosion Pos : ";
		s += std::to_string(c.X);
		s += " /// ";
		s += std::to_string(c.Y);
		s += "\n";
		GameMng()->m_sLog += s;

		return true;
	}

	return false;
}

//터지고 나서 무언가 하면 트루?
bool Bomb::Explosived()
{
	GameMng()->ResistExplosion(this, rt.x, rt.y, m_nExplosiveRange);

	return true;
}
