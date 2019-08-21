#pragma once

//캐릭터가 가지고 있을 값
struct CharacterData
{
	float fMoveSpeed;
	float fBombTime;
	int nBombPower;
	int nBombCount;

	CharacterData();
};

//게임 내부 구현 클래스
class GameManager
{
#pragma region SINGLE_TON
private:
	static inline GameManager* m_pInstance = nullptr;
	GameManager();
	~GameManager();

	GameManager operator=(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager(const GameManager&) = delete;

public:

	static void CreateInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new GameManager();
			m_pInstance->Init();
		}
	}

	static GameManager* GetInstance()
	{
		return m_pInstance;
	}

	static void ReleaseInstance()
	{
		m_pInstance->Release();
		SAFE_DELETE(m_pInstance);
	}

#pragma endregion

public:
	enum
	{
		MaxLife = 3,
		RoundTime = 90,

		MoveSpeed = 10,
		BombTime = 2,
		BombBasePower = 2,
		BombBaseCount = 1,
	};

	void Init();

	//추가됨- 뭔가를 지움
	void Release();

	void GameInit();
	void StageStart();

	void Update(float a_fDeltaTime);
	void Render();

	//추가된 함수. 클리어? 요것도 뭔가를 지울듯 
	void ClearObject();

	//상호작용 추가됨- 무슨 상호작용?
	// 일단 오브젝트 지움
	void RemoveObject(class Object* a_pObj);
	//아이템도 떨궈
	void DropItem(class Object* a_pObj);
	//폭탄의 데이터를 가져오는듯
	void GetBombData(class Bomb* a_refBomb) const;
	//아이템 얻으면? 먹으면 하는듯
	void ObtainItem(eItem a_eItem);

private:

	//오브젝트
	std::vector<class Object*> m_vcObj;
	class Player* m_pPlayer = nullptr;

	//스테이지 정보
	int m_nNowStage = 0;
	float m_fGameTime = 0; // 스테이지 별 남은 시간
	class MapData* m_refMap = nullptr;
	char** m_pMap = nullptr;

	int m_nNowLife = 0;		// 플레이어 라이프
	int m_nScore = 0;		//점수

	// 추가됨- 폭발 왜?
	std::queue<class Bomb*> m_qBomb;

	//추가됨- 현재 플레이어 데이터
	CharacterData m_stPlayerData;
};

#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())