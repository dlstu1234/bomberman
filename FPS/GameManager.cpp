#include "pch.h"
#include "GameManager.h"

#include "MapData.h"
#include "Object.h"
#include "Player.h"
#include "ObjectFactory.h"

CharacterData::CharacterData()
{
	fMoveSpeed = GameManager::MoveSpeed;
	fBombTime = GameManager::BombTime;
	nBombPower = GameManager::BombBasePower;
	nBombCount = GameManager::BombBaseCount;
}

GameManager::GameManager() { }
GameManager::~GameManager()
{
	for (auto* pObj : m_vcObj)
	{
		SAFE_DELETE(pObj);
	}

	SAFE_DELETE(m_pPlayer);
}

void GameManager::Init()
{
	MapData::Init();
}

void GameManager::Release()
{
	MapData::Release(); // 맵 데이터 클래스의 릴리즈 함수로 ㄲㄲ
}

void GameManager::GameInit()
{
	m_nNowLife = 3;
	m_nScore = 0;
	m_nNowStage = 0;
}

void GameManager::StageStart()
{
	++m_nNowStage;
	m_fGameTime = RoundTime;

	ClearObject();

	MapData::Get(m_nNowStage);
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr); // 예외처리 좀 바뀜

	int nWidth = m_refMap->x;
	int nHeight = m_refMap->y;
	const std::string& sRef = m_refMap->mapOriginData;
	m_pMap = m_refMap->pMap;

	// 맵 제작
	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			int nIndex = y * nWidth + x;
			eObjectType eType = (eObjectType)(sRef[nIndex] - '0');

			if (eType == eObjectType::None) { continue; }

			if (eType == eObjectType::Player && m_pPlayer != nullptr)
			{
				m_pPlayer->SetPos(x, y);
				m_pPlayer->SetMap(m_pMap);
				continue;
			}

			auto* pObj = ObjectFactory::Make(eType, x, y);
			if (eType == eObjectType::Player)
			{
				m_pPlayer = static_cast<Player*>(pObj);
			}
			else
			{
				m_vcObj.push_back(pObj);
			}

			pObj->SetMap(m_pMap);
		}
	}
}

//오브젝트 지움 암튼 지움
void GameManager::ClearObject()
{
	for (auto obj : m_vcObj)
	{
		SAFE_DELETE(obj);
	}

	m_vcObj.clear();
}

void GameManager::Update(float a_fDeltaTime)
{
	for (auto obj : m_vcObj)
	{
		obj->Update(a_fDeltaTime);
	}

	m_pPlayer->Update(a_fDeltaTime);
}

void GameManager::Render()
{
	//포문돌려서 오브젝트 그리기?
	for (auto obj : m_vcObj)
	{
		obj->Render();
	}
	//플레이어 그리기
	m_pPlayer->Render();

	//맵 그려주고
	SetCursor(0, 0);
	m_refMap->Render();
}

void GameManager::RemoveObject(class Object* a_pObj)
{
	// 아마도 벡터의 시작에서 끝중에 값이 일치하면 지우는듯 ?
	auto itor = std::find_if(std::begin(m_vcObj), std::end(m_vcObj), [a_pObj](Object*p) {return p == a_pObj; });
	assert(itor != m_vcObj.end());
	m_vcObj.erase(itor);
}
//비엇슴
void GameManager::DropItem(Object* a_pObj)
{

}

//아이템 먹으면? 종류에 따라 효과 상승
void GameManager::ObtainItem(eItem a_eItem)
{
	switch (a_eItem)
	{
	case eItem::PowerUp:
		m_stPlayerData.nBombPower += 1;
		break;
	case eItem::BombCount:
		m_stPlayerData.nBombCount += 1;
		break;
	case eItem::SpeedUp:
		m_stPlayerData.fMoveSpeed += 1;
		break;
	default:
		assert(false && "arg error");
		break;
	}

}

#include "Bomb.h"
//폭탄의 터지는 시간과 파워?를 가져오는 함수?같음
void GameManager::GetBombData(Bomb* a_refBomb) const
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}