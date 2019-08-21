#pragma once
//�� ���� Ŭ����
class MapData
{
public:
	MapData() = default;
	static MapData* Get(int a_nStage);
	static void Init();

	//���� ���� �Լ� �����?
	static void Release();

private:
	static MapData m_arrData[eGame::MaxStage];

private:
	//3��° �̸��� �ٲ�
	void MakeMapBuffer();

	//������ �����?���� � ������?
	void ReleaseData();

public:

	// ���� �׸���? ���� ����
	void Render();

public:
	int x;
	int y;

	//string���� const char*�� ���� �� ����Ÿ ����?
	const char* mapOriginData;
	//���� �������
	char** pMap = nullptr;
};

