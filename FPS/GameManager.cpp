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

//스테이지 시작
void GameManager::StageStart()
{
	++m_nNowStage;
	m_fGameTime = RoundTime;
	m_eState = eGameState::Run;

	ClearObject();

	m_refMap = MapData::Get(m_nNowStage);
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr);

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
			eObjectType eType = MapData::DataToObjectType(sRef[nIndex]);

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
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			SAFE_DELETE(pObj);
		}

		vc.clear();
	}
}

//오브젝트 생성 함수 오브젝트 포인터로 바뀜
Object* GameManager::CreateObject(eObjectType a_eObjType, int x, int y)
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
	//만들어진 오브젝트를 리턴
	return pObj;
}

void GameManager::Update(float a_fDeltaTime)
{
	m_vcDelete.clear();
	int nSize = m_arrObj.size();

	// 0뎁스의 오브젝트는 업데이트 할 내용이 없음
	for( int i = 1; i < nSize; ++i )
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
				m_vcDelete.push_back(p);
			}
		}
	}

	// 없앰
	/*for( auto* pDeleteObj : vcDelete )
	{
		pDeleteObj->RenderClear();
		RemoveObject(pDeleteObj);
	}
	vcDelete.clear();*/

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
	//테스트용 로그
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

void GameManager::PostRender()
{
	//삭제할 오브젝트 삭제
	for (auto* pDeleteObj : m_vcDelete)
	{
		pDeleteObj->RenderClear();
		RemoveObject(pDeleteObj);
	}
	m_vcDelete.clear();

	// 폭탄 추가
	for (auto& ex : m_vcExplision)
	{
		int nBombX = ex.x;
		int nBombY = ex.y;
		int nPow = ex.pow;

		CreateObject(eObjectType::Explosion, nBombX, nBombY);

		CreateExplosionRecursive(eDir::Left, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Top, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Right, nBombX, nBombY, nPow);
		CreateExplosionRecursive(eDir::Bottom, nBombX, nBombY, nPow);
	}

	m_vcExplision.clear();
}

void GameManager::CreateExplosionRecursive(eDir a_eDir, int nBombX, int nBombY, int a_nRemainPower)
{
	switch (a_eDir)
	{
	case eDir::Left: { nBombX -= 1; } break;
	case eDir::Top: { nBombY -= 1; } break;
	case eDir::Right: { nBombX += 1; } break;
	case eDir::Bottom: { nBombY += 1; } break;
	}

	CreateObject(eObjectType::Explosion, nBombX, nBombY);

	--a_nRemainPower;
	if (a_nRemainPower == 0) { return; }

	CreateExplosionRecursive(a_eDir, nBombX, nBombY, a_nRemainPower);
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
	auto itor = std::find_if(std::begin(vc), std::end(vc), [a_pObj](Object*p) {return p == a_pObj; });
	if (itor != vc.end())
	{
		vc.erase(itor);
		SAFE_DELETE(a_pObj);
	}
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
		m_stPlayerData.fMoveSpeed += 30;
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
Object* GameManager::AddBomb(int a_nPlayerX, int a_nPlayerY)
{
	if (FindObject_withPosition(eObjectType::Bomb, a_nPlayerX, a_nPlayerY) == false)
	{
		int nX = a_nPlayerX / TileSize;
		int nY = a_nPlayerY / TileSize;

		return CreateObject(eObjectType::Bomb, nX, nY);
	}

	return nullptr;
}

bool GameManager::FindObject_withPosition(eObjectType a_eObj, int x, int y)
{
	int nX = x / TileSize;
	int nY = y / TileSize;
	int nIndex = ((int)a_eObj / (int)eObjectType::RenderDepthGap) - 1;

	for (auto* pObj : m_arrObj[nIndex])
	{
		if (pObj->GetObjectType() == a_eObj)
		{
			if (pObj->rt.IsIn(x, y) == true)
			{
				return true;
			}
		}
	}

	return false;
}

void GameManager::ResistExplosion(Object* a_refBomb, int x, int y, int pow)
{
	m_pPlayer->ResetBomb(a_refBomb);
	m_vcExplision.emplace_back(x / TileSize, y / TileSize, pow);
}

bool GameManager::MoveCheck(Object* a_pMoveIgnoreObject /*= nullptr*/)
{
	for (auto& vc : m_arrObj)
	{
		for (auto* pObj : vc)
		{
			if (a_pMoveIgnoreObject == pObj) { continue; }

			if (pObj->CanMove() == true) { continue; }

			if (pObj->IsCross(m_pPlayer) == true)
			{
				return false;
			}
		}
	}

	return true;
}

void GameManager::CheckExplosion(Object* a_refExplosion)
{
	int nIndex = (int)eObjectType::RenderDepth3 - 1; // 폭발 타겟들만 있는 뎁스
	const auto& vc = m_arrObj[nIndex];

	for (auto* pObj : vc)
	{
		if (pObj == a_refExplosion) { continue; }

		if (a_refExplosion->IsCross(pObj) == true)
		{
			if (pObj->Explosived() == true)
			{
				m_vcDelete.push_back(pObj);
			}
		}
	}

}

void GameManager::AddScore(int a_nScore)
{
	m_nScore += m_nScore;
}

#include "Bomb.h"
//폭탄의 터지는 시간과 파워?를 가져오는 함수?같음
void GameManager::GetBombData(OUT Bomb* a_refBomb) const
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}