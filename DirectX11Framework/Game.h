#pragma once

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
	void CreateDeviceAndSwapChain();
private:
	HWND hwnd;
	uint32 width = 0;
	uint32 height = 0;
	//DX �ʱ�ȭ
private:
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain> swapChain = nullptr;

};

