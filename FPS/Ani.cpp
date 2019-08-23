#include "pch.h"
#include "Ani.h"

Ani::~Ani()
{
}

//리사이즈 사이즈 확인? 새롭게 사이즈 넣을듯?
void Ani::Resize(int a_nAniTypeCount)
{
	m_vcAni.resize(a_nAniTypeCount);
}

//
void Ani::Add(int a_nAni, const RenderTile& tile)
{
	//예외처리 값보다 사이즈가 작으면 터트림 리사이즈를 불러와주세용
	assert(a_nAni < m_vcAni.size() && "logic error - Call Resize");
	//푸시! 넣어준다 타일을?
	m_vcAni[a_nAni].push_back(tile);
}

//타입에 맞는 타일을 넣어주는? 함수?
void Ani::Add(int a_nAniType, const std::initializer_list<RenderTile>& tiles)
{
	
	for(auto& tile : tiles)
	{
		Add(a_nAniType, tile);
	}
}
//음... 스텟 설정? ani클래스에 있던 값들 설정해주는듯
void Ani::SetState(int a_nAni, int a_nCut /*= 0*/)
{
	m_pCurrentAni = &m_vcAni[a_nAni];

	m_nAniType = a_nAni;
	m_nCut = a_nCut;
	m_nNowMaxCut = (int)m_pCurrentAni->size();
	m_fNowTile = 0.0f;
}

//다음 컷?
void Ani::NextCut()
{
	//컷 늘려줌
	++m_nCut;
	//컷을 맥스컷으로 나눈게 컷이됨??
	m_nCut %= m_nNowMaxCut;
}

//업데이트!
void Ani::Update(float a_fDeltaTime)
{
	m_fNowTile += a_fDeltaTime;
	
	if (m_fNowTile > a_fCutTime)
	{
		NextCut();
		m_fNowTile = 0;
	}
}

//가져오는듯 뭘가져오나?
RenderTile* Ani::Get()
{
	RenderTile* r = &(*m_pCurrentAni)[m_nCut];
	return r;
}

