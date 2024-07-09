#include "pch.h"
#include "Game.h"
#include "Graphics.h"

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
	graphic = make_shared<Graphics>();
	graphic->Init(width,height,hwnd,true);
	
}

void Game::Update()
{
}

void Game::LateUpdate()
{
}

void Game::Render()
{
	graphic->RenderBegin();

	graphic->RenderEnd();
}




