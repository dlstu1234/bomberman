#include "pch.h"
#include "Ani.h"

Ani::Ani()
{
}

Ani::~Ani()
{
}

//추가됨 뭘 하는걸까?
void Ani::Resize(int a_nAniTypeCount)
{
	m_vcAni.resize(a_nAniTypeCount);
}

//벡터 안에 무언가를 집어넣음
void Ani::Add(int a_nAni, RenderTile* tile)
{
	m_vcAni[a_nAni].push_back(tile);
}

//음... 스텟 설정? ani클래스에 있던 값들 설정해주는듯
void Ani::SetState(int a_nAni, int a_nFrame /*= 0*/)
{
	m_pCurrentAni = &m_vcAni[a_nAni];

	m_nAniType = a_nAni;
	m_nFrame = a_nFrame;
	m_nNowMaxFrame = m_pCurrentAni->size();
}

//가져오는듯 뭘가져오나 프레임?
RenderTile* Ani::Get()
{
	RenderTile* r = (*m_pCurrentAni)[m_nFrame++];
	m_nFrame %= m_nNowMaxFrame;
	return r;
}

