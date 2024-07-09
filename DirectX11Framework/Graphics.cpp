#include "pch.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	swapChain->SetFullscreenState(false, nullptr);

}



void Graphics::CreateDeviceAndSwapchain(uint32 width, uint32 height, HWND hwnd, bool isWindowed)
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.OutputWindow = hwnd;
	desc.Windowed = isWindowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;




	HRESULT hResult = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_SINGLETHREADED,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		swapChain.GetAddressOf(),
		device.GetAddressOf(),
		nullptr,
		deviceContext.GetAddressOf()
	);
	CHECK(hResult);
}

void Graphics::Init(uint32 width, uint32 height, HWND hwnd, bool isWindowed)
{
	CreateDeviceAndSwapchain(width, height, hwnd, isWindowed);
	InitalizeBackBuffer();
	InitalizeViewport(width, height);

	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();
}

void Graphics::RenderBegin()
{
	
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);

	uint32 stride = sizeof(Vertex);
	uint32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);

	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

	deviceContext->Draw(vertices.size(), 0);

	deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
}

void Graphics::RenderEnd()
{
	swapChain->Present(0, 0);
}

void Graphics::InitalizeViewport(uint32 width, uint32 height)
{

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	//래스터라이저단계에 뷰포트를 설정
	deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::InitalizeBackBuffer()
{
	ID3D11Texture2D* backBuffer;
	//백버퍼의 주소를 가져온다
	HRESULT check = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	CHECK(check);
	//백버퍼의 주소를 이용하여 렌더 타겟을 생성한다
	check = device->CreateRenderTargetView(backBuffer, nullptr, renderTargetView.GetAddressOf());
	CHECK(check);
	// 참조를 제거한다	
	backBuffer->Release();

	//렌더 타겟을 백 버퍼로 설정한다.
	deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
}

void Graphics::CreateGeometry()
{
	vertices.resize(3);
	vertices[0].position = Vec3(0, 0.5f, 0);
	vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);

	vertices[1].position = Vec3(0.5f, -0.5f, 0);
	vertices[1].color = Color(1.f, 1.f, 0.f, 1.f);

	vertices[2].position = Vec3(-0.5f, -0.5f, 0);
	vertices[2].color = Color(0.f, 1.f, 0.f, 1.f);

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(Vertex) * vertices.size();
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices.data();

	device->CreateBuffer(&vertexDesc, &data, vertexBuffer.GetAddressOf());

}

void Graphics::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},

	};
	const int32 count = sizeof(inputDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	HRESULT result = device->CreateInputLayout(inputDesc, count, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), inputLayout.GetAddressOf());
	CHECK(result);
}

void Graphics::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", vsBlob);

	HRESULT result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
	CHECK(result);
}

void Graphics::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", psBlob);


	HRESULT result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
	CHECK(result);
}

void Graphics::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	HRESULT result = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr
	);
	CHECK(result);
}
