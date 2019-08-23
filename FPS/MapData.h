#pragma once
//맵 관련 클래스
class MapData
{
public:
	MapData() = default;
	static MapData* Get(int a_nStage);
	static void Init();
	static void Release();
	//오브젝트 타입의 데이터 입력? 불러오는듯
	static eObjectType DataToObjectType(char c);

private:
	static MapData m_arrData[eGame::MaxStage];

private:
	//맵 버퍼 만들기
	void MakeMapBuffer();

	//데이터 지우기?같음 어떤 데이터?
	void ReleaseData();

public:

	// 맵을 그린다? 새로 생김
	void Render();

public:
	int x;
	int y;

	//맵 데이타 생성?
	const char* mapOriginData;
	//맵 상태가 비어있음
	char** pMap = nullptr;
};

