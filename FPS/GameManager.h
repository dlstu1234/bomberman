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
		MaxLife = 3,		// 플레이어 라이프 수
		RoundTime = 90,		// 90초

		MoveSpeed = 10,		// 이동 속도
		BombTime = 2,		// 2초
		BombBasePower = 2,	// 2칸
		BombBaseCount = 1,	// 최초 폭탄 설치 갯수
	};
	//게임의 상태
	enum class eGameState
	{
		None,

		Run,
		End,
	};

	void Init();
	void Release();

	//게임 시작 끝
	void GameInit();
	void StageStart();
	void StageEnd();

	void Update(float a_fDeltaTime);
	void Render();

	//오브젝트 지우기
	void ClearObject();
	//오브젝트 생성
	void CreateObject(eObjectType a_eObjType, int x, int y);

	// 상호작용
	//지움
	void RemoveObject(class Object* a_pObj);
	//아이템 드랍
	void DropItem(class Object* a_pObj);
	//폭탄 데이터
	void GetBombData(class Bomb* a_refBomb) const;
	//아이템과의 상호작용
	void ObtainItem(eItem a_eItem);
	//죽음
	void Die(class Object* a_refObj);
	//폭탄 생성?
	bool AddBomb(int a_nPlayerX, int a_nPlayerY);
	//터지고나면 ?
	void ResistExplosion(int a_nBombX, int a_nBombY, int a_nPower);

private:

	// 오브젝트
	std::array<std::vector<class Object*>, (int)eObjectType::RenderDepthCount> m_arrObj;
	class Player* m_pPlayer = nullptr;

	// 스테이지 정보
	int m_nNowStage = 0;
	float m_fGameTime = 0;	// 스테이지별 남은 시간
	class MapData* m_refMap = nullptr;
	char** m_pMap = nullptr;

	// 데이터
	int m_nNowLife = 0;		// 플레이어 라이프
	int m_nScore = 0;		// 점수

	// 폭발
	std::queue<class Bomb*> m_qBomb;

	// 현재 플레이어 데이터
	CharacterData m_stPlayerData;

	// 게임 상태
	eGameState	m_eState = eGameState::None;

	// 로그
	std::string m_sLog = "";
};

#define InitGameMng()		{GameManager::CreateInstance(); }
#define GameMng()			(GameManager::GetInstance())
#define ReleaseGameMng()	(GameManager::ReleaseInstance())