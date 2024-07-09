#pragma once
class Graphics;
class Game
{
public:
	Game();
	~Game();

	//게임로직
public:
	void Init(HWND hwnd);
	void Update();
	void LateUpdate();
	void Render();

private:
	HWND hwnd = nullptr;
	uint32 width = 0;
	uint32 height = 0;
	//DX 초기화
private:
	shared_ptr<Graphics> graphic;

};

