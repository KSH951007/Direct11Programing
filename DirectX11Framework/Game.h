#pragma once
class Graphics;
class Game
{
public:
	Game();
	~Game();

	//���ӷ���
public:
	void Init(HWND hwnd);
	void Update();
	void LateUpdate();
	void Render();

private:
	HWND hwnd = nullptr;
	uint32 width = 0;
	uint32 height = 0;
	//DX �ʱ�ȭ
private:
	shared_ptr<Graphics> graphic;

};

