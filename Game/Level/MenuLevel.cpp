#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"

#include <iostream>

MenuLevel::MenuLevel()
{
	// 메뉴 아이템 생성.
	items.emplace_back(
		new MenuItem(
			"Resume Game",
			[]()
			{
				Game::Get().ToggleMenu();
			}
		)
	);
	items.emplace_back(
		new MenuItem(
			"Quit Game",
			[]()
			{
				Game::Get().QuitEngine();
			}
		)
	);
}

MenuLevel::~MenuLevel()
{
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}

	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = static_cast<int>(items.size());

	// 방향키 입력처리 (위/아래/엔터,ESC)
	if (Input::Get().GetKeyDown('W'))
	{
		// 인덱스 돌리기.
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown('S'))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();

		// 인덱스 초기화
		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	super::Draw();

	// 메뉴 제목 출력.
	Util::SetConsolePosition(Vector2::Zero);
	Util::SetConsoleTextColor(Color::White);

	// 텍스트 출력
	std::cout << "Sokoban Game\n\n";

	// 메뉴 아이템 출력
	for (int i =0; i < static_cast<int>(items.size()); ++i)
	{
		// 아이템 색상 확인
		Color textColor = (i == currentIndex)
			? selectedColor : unselectedColor;

		Util::SetConsoleTextColor(textColor);

		std::cout << items[i]->text << "\n";
	}
}
