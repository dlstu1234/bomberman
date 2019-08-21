#include "pch.h"
#include "Ani.h"

Ani::Ani()
{
}

Ani::~Ani()
{
}

//�߰��� �� �ϴ°ɱ�?
void Ani::Resize(int a_nAniTypeCount)
{
	m_vcAni.resize(a_nAniTypeCount);
}

//���� �ȿ� ���𰡸� �������
void Ani::Add(int a_nAni, RenderTile* tile)
{
	m_vcAni[a_nAni].push_back(tile);
}

//��... ���� ����? aniŬ������ �ִ� ���� �������ִµ�
void Ani::SetState(int a_nAni, int a_nFrame /*= 0*/)
{
	m_pCurrentAni = &m_vcAni[a_nAni];

	m_nAniType = a_nAni;
	m_nFrame = a_nFrame;
	m_nNowMaxFrame = m_pCurrentAni->size();
}

//�������µ� ���������� ������?
RenderTile* Ani::Get()
{
	RenderTile* r = (*m_pCurrentAni)[m_nFrame++];
	m_nFrame %= m_nNowMaxFrame;
	return r;
}

