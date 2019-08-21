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
	m_arrData[0].MakeMapBuffer();

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
	m_arrData[1].MakeMapBuffer();

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
	m_arrData[2].MakeMapBuffer();
}

//맵 지우기
void MapData::Release()
{
	for (auto& mapData : m_arrData)
	{
		mapData.ReleaseData();
	}
}

// 3번째 맵 만들기 변경됨
void MapData::MakeMapBuffer()
{
	int nX = x * TileSize;
	int nY = y * TileSize;

	pMap = new char*[nY];
	//memcyp 쓰던걸 빼버림
	for (int i = 0; i < nY; ++i)
	{
		pMap[i] = new char[nX + 1];
		pMap[i][nX] = 0;
	}
}

//3번째에 바뀐 맵 데이터 지우기
void MapData::ReleaseData()
{
	int nY = y * TileSize;

	for (int i = 0; i < nY; ++i)
	{
		SAFE_DELETE_ARR(pMap[i])
	}

	SAFE_DELETE_ARR(pMap);
}

//3번째에 바뀜 그리는게 조금 달라짐 nY를 받는?
void MapData::Render()
{
	int nY = y * TileSize;

	for (int i = 0; i < nY; ++i)
	{
		cout << pMap[i] << endl;
	}
}