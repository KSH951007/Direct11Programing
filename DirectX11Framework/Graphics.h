#pragma once

class Graphics
{
public:
	Graphics();
	~Graphics();


public:
	void Init(uint32 width, uint32 height, HWND hwnd, bool isFullScreen);
	void RenderBegin();
	void RenderEnd();
private:
	void CreateDeviceAndSwapchain(uint32 width, uint32 height, HWND hwnd, bool isFullScreen = true);
	void InitalizeViewport(uint32 width, uint32 height);
	void InitalizeBackBuffer();
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);
private:
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11InputLayout> inputLayout = nullptr;
 	float clearColor[4] = { 0.f,0.f,1.f,1.f };

	//Geometry
	vector<Vertex> vertices;
	ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	//vs
	ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	ComPtr<ID3DBlob> vsBlob = nullptr;

	//ps
	ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	ComPtr<ID3DBlob> psBlob = nullptr;
};

