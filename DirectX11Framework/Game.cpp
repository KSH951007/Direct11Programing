#include "pch.h"
#include "Game.h"
Game::Game()
{
}

Game::~Game()
{
}


void Game::Init(HWND hwnd)
{
	this->hwnd = hwnd;
	this->width = GWinSizeX;
	this->height = GWinSizeY;

}

void Game::Update()
{
}

void Game::LateUpdate()
{
}

void Game::Render()
{
}

void Game::CreateDeviceAndSwapChain()
{
	D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_UNKNOWN,)
}


