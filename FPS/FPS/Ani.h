#pragma once
//�߰��� Ŭ���� �ִ�? �ִϸ��̼� ���õȰŰ���
class Ani
{
public:
	Ani();
	virtual ~Ani();

	void Resize(int a_nAniTypeCount);
	void Add(int a_nAniType, RenderTile* tile);
	void SetState(int a_nAni, int a_nFrame = 0);
	RenderTile* Get();

	//������ ���Ϳ� �������°� ������ ���ΰ�?
	std::vector<std::vector<RenderTile*>> m_vcAni;
	std::vector<RenderTile*>* m_pCurrentAni = nullptr;

	//�����Ӱ��õȰ�??
	int m_nAniType = 0;
	int m_nNowMaxFrame = 0;
	int m_nFrame = 0;
};

