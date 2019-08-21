#pragma once
//맵 관련 클래스
class MapData
{
public:
	MapData() = default;
	static MapData* Get(int a_nStage);
	static void Init();

	//새로 생긴 함수 지우기?
	static void Release();

private:
	static MapData m_arrData[eGame::MaxStage];

private:
	//3번째 이름이 바뀜
	void MakeMapBuffer();

	//데이터 지우기?같음 어떤 데이터?
	void ReleaseData();

public:

	// 맵을 그린다? 새로 생김
	void Render();

public:
	int x;
	int y;

	//string에서 const char*로 변경 맵 데이타 생성?
	const char* mapOriginData;
	//뭔가 비어있음
	char** pMap = nullptr;
};

