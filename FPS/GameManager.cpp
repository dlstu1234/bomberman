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
	MapData::Release(); // �� ������ Ŭ������ ������ �Լ��� ����
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
	assert(m_refMap != nullptr && m_refMap->pMap != nullptr); // ����ó�� �� �ٲ�

	int nWidth = m_refMap->x;
	int nHeight = m_refMap->y;
	const std::string& sRef = m_refMap->mapOriginData;
	m_pMap = m_refMap->pMap;

	// �� ����
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

//������Ʈ ���� ��ư ����
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
	//���������� ������Ʈ �׸���?
	for (auto obj : m_vcObj)
	{
		obj->Render();
	}
	//�÷��̾� �׸���
	m_pPlayer->Render();

	//�� �׷��ְ�
	SetCursor(0, 0);
	m_refMap->Render();
}

void GameManager::RemoveObject(class Object* a_pObj)
{
	// �Ƹ��� ������ ���ۿ��� ���߿� ���� ��ġ�ϸ� ����µ� ?
	auto itor = std::find_if(std::begin(m_vcObj), std::end(m_vcObj), [a_pObj](Object*p) {return p == a_pObj; });
	assert(itor != m_vcObj.end());
	m_vcObj.erase(itor);
}
//�����
void GameManager::DropItem(Object* a_pObj)
{

}

//������ ������? ������ ���� ȿ�� ���
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
//��ź�� ������ �ð��� �Ŀ�?�� �������� �Լ�?����
void GameManager::GetBombData(Bomb* a_refBomb) const
{
	a_refBomb->m_fLifeTime = m_stPlayerData.fBombTime;
	a_refBomb->m_nExplosiveRange = m_stPlayerData.nBombPower;
}