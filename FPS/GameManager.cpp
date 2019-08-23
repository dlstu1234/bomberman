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
	ClearObject();
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
			//오브젝트 만드는 함수로 제작
			CreateObject(eType, x, y);
		}
	}
}

//스테이지의 끝
void GameManager::StageEnd()
{
	m_eState = eGameState::End;
}

//오브젝트 지움 암튼 지움
void GameManager::ClearObject()
{
	for (auto& vc : m_vcObj)
	{
		for (auto* pObj : vc)
		{
			SAFE_DELETE(pObj);
		}

		vc.clear();
	}
}

//오브젝트 생성 함수
void GameManager::CreateObject(eObjectType a_eObjType, int x, int y)
{
	auto* pObj = ObjectFactory::Make(a_eObjType, x, y);
	if (a_eObjType == eObjectType::Player)
	{
		m_pPlayer = static_cast<Player*>(pObj);
		m_pPlayer->SetStat(&m_stPlayerData);
	}
	else
	{
		int nDepthIndex = (int)a_eObjType / (int)eObjectType::RenderDepthGap;
		nDepthIndex -= 1;

		m_arrObj[nDepthIndex].push_back(pObj);
	}

	pObj->SetMap(m_pMap);
}

void GameManager::Update(float a_fDeltaTime)
{
	int nSize = m_arrObj.size();

	static std::vector<class Object*> vcDelete;
	vcDelete.clear();

	// 0뎁스의 오브젝트는 업데이트 할 내용이 없음
	for( int i=1; i<nSize; ++i )
	{
		auto& arrObj = m_arrObj[i];

		for (auto* pObj : arrObj)
		{
			Object* p = nullptr;

			if( pObj->Update(a_fDeltaTime) == true )
			{
				p = pObj;
			}

			if( pObj->Interaction(m_pPlayer) == true )
			{
				p = pObj;
			}

			if( p != nullptr )
			{
				vcDelete.push_back(p);
			}
		}
	}

	// 인터렉션 이후 삭제해야할 오브젝트 삭제
	for( auto* pDeleteObj : vcDelete )
	{
		pDeleteObj->RenderClear();
		RemoveObject(pDeleteObj);
	}
	vcDelete.clear();

	m_pPlayer->Update(a_fDeltaTime);
}

//그리기
void GameManager::Render()
{
	//포문돌려서 오브젝트에 맞는거 그리기
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			pObj->Render();
		}
	}
	//맵과 플레이어 그리기
	m_pPlayer->Render();
	m_refMap->Render();
	
	//스테이지 끝나면 스테이지 시작함수로 가기
	if(m_eState == eGameState::End )
	{
		StageStart();
	}
	//뭔가 그려줌 아마 캐릭터의 좌표인덧
	cout << "pos : " << m_pPlayer->rt.x << " /// " << m_pPlayer->rt.y << endl;
	COORD center = m_pPlayer->rt.Center();

	cout << "center : " << center.X << " /// " << center.Y << endl;

	//로그 사이즈가 0보다 클때 스트링 나타냄 그리고 로그 클리어?
	if(m_sLog.size() > 0 )
	{
		cout << m_sLog.c_str() << endl;
		m_sLog.clear();
	}
}

void GameManager::RemoveObject(class Object* a_pObj)
{
	//오브젝트의 타입을 받고
	eObjectType eType = a_pObj->GetObjectType();
	
	int nLevelIndex = (int)eType / (int)eObjectType::RenderDepthGap;
	nLevelIndex -= 1; // 인덱스

	auto& vc = m_arrObj[nLevelIndex];
	
	// 아마도 벡터의 시작에서 끝중에 값이 일치하면 지우는듯 ?
	auto itor = std::find_if(std::begin(vc), std::end(vc), [a_pObj](Object*p) {return p == a_pObj;});
	assert(itor != vc.end());
	vc.erase(itor);

	SAFE_DELETE(a_pObj);
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
//플레이어 죽으면 출력!
void GameManager::Die(class Object* a_refObj)
{
	cout << "Player Die" << endl;
}

//폭탄 체크으
bool GameManager::AddBomb(int a_nPlayerX, int a_nPlayerY)
{
	int nX = a_nPlayerX / TileSize;
	int nY = a_nPlayerY / TileSize;
	constexpr static int nIndex = ((int)eObjectType::Bomb / (int)eObjectType::RenderDepthGap) - 1;

	bool bExsistBomb = false;

	for( auto* pObj : m_arrObj[nIndex] )
	{
		if( pObj->GetObjectType() == eObjectType::Bomb )
		{
			bExsistBomb = pObj->rt.IsIn(a_nPlayerX, a_nPlayerY);

			if( bExsistBomb == true )
			{
				break;
			}
		}
	}

	if( bExsistBomb == true )
	{
		return false;
	}
	
	CreateObject(eObjectType::Bomb , nX, nY);
	return true;
}

//폭발하면 카운트 줄이기?
void GameManager::ResistExplosion(int a_nBombX, int a_nBombY, int a_nPower)
{
	m_pPlayer->m_nPutBombCount -= 1;
}

#include "Bomb.h"
//폭탄의 터지는 시간과 파워?를 가져오는 함수?같음
void GameManager::GetBombData(Bomb* a_refBomb) const
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}