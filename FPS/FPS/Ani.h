#pragma once
//추가된 클래스 애니? 애니메이션 관련된거같음
class Ani
{
public:
	Ani();
	virtual ~Ani();

	void Resize(int a_nAniTypeCount);
	void Add(int a_nAniType, RenderTile* tile);
	void SetState(int a_nAni, int a_nFrame = 0);
	RenderTile* Get();

	//뭔가를 벡터에 넣으려는거 같은데 맵인가?
	std::vector<std::vector<RenderTile*>> m_vcAni;
	std::vector<RenderTile*>* m_pCurrentAni = nullptr;

	//프레임관련된거??
	int m_nAniType = 0;
	int m_nNowMaxFrame = 0;
	int m_nFrame = 0;
};

