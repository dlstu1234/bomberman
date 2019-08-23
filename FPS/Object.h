#pragma once
//������Ʈ Ŭ����
class Object
{
public:
	Object(int _x, int _y);
	virtual ~Object();
	virtual eObjectType GetObjectType() const = 0;

	//������Ʈ üũ
	bool Update(float a_fDelta);
	//�׸���
	void Render();
	//�� ����
	void SetMap(char** a_refMap);
	//�׸��� �����
	void RenderClear();
	
	virtual void Init();
	virtual void Explosived(class Bomb* a_refBomb);
	virtual void Interaction(class Hero* a_refHero);

	//��ǥ ����?
	inline void SetPos(int _x, int _y) { x = _x; y = _y; rt.x = _x; rt.y = _y; }
	//�浹 ó��
	inline bool IsCross(const Object& a_refObj)
	{
		return rt.IsCross(a_refObj.rt);
	}
	//�浹 ó�� 2
	inline bool IsCross(Object* a_refObj)
	{
		assert((a_refObj != nullptr) && "arg error");
		return IsCross(*a_refObj);
	}

	virtual Rect GetRendertRect() const; // �׸��� ��ǥ
protected:
	
	virtual void _PreUpdate(float a_fDelta); // �����ܰ��� ���� �����
	virtual bool _Update(float a_fDelta);
	
public:
	int x; // ���� Ÿ�Ͽ����� ��ġ
	int y;
	Rect rt; // �浹ó���� ��ǥ

protected:
	//�� ����?
	static RenderTile Empty;
	char**	m_refMap = nullptr;
	RenderTile*	m_pNowAni = nullptr;
};


