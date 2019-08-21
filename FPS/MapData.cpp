#include "pch.h"
#include "MapData.h"

//맥스 스테이지 만큼 맵 배열 생성
MapData MapData::m_arrData[eGame::MaxStage] = { {}, };

//스테이지 정보 불러오기
MapData* MapData::Get(int a_nStage)
{
	return &m_arrData[a_nStage];
}

void MapData::Init()
{
	// 1스테이지
	m_arrData[0].x = 10;
	m_arrData[0].y = 10;
	m_arrData[0].mapOriginData = 
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[0].MakeMap();

	// 2스테이지
	m_arrData[1].x = 10;
	m_arrData[1].y = 10;
	m_arrData[1].mapOriginData =
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[1].MakeMap();

	// 3스테이지
	m_arrData[2].x = 10;
	m_arrData[2].y = 10;
	m_arrData[2].mapOriginData =
		"1111111111"
		"1000000601"
		"1020007001"
		"1000000001"
		"1000300001"
		"1000000001"
		"1000004001"
		"1000000001"
		"1050000001"
		"1111111111";
	m_arrData[2].MakeMap();
}

//맵 배열 지우기
void MapData::Release()
{
	for (auto& mapData : m_arrData)
	{
		mapData.ReleaseData();
	}
}
// 맵 만들기
void MapData::MakeMap()
{
	//맵에 새로 char* 좌표값 y 만들어 저장?
	pMap = new char*[y];
	
	//y까지 돌면서
	for (int i = 0; i < y; ++i)
	{
		//x값을 새로 저장
		pMap[i] = new char[x + 1];

		int gap = i * x;

		// 복사
		memcpy_s(pMap[i], sizeof(char) * (x + 1),
			mapOriginData + gap, sizeof(char)* x);

		pMap[i][x] = 0;
	}
}

// 맵 데이터 지우기
void MapData::ReleaseData()
{
	for (int i = 0; i < y; ++i)
	{
		SAFE_DELETE_ARR(pMap[i])
	}

	SAFE_DELETE_ARR(pMap);
}