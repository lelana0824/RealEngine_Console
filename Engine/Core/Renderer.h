#pragma once

#include "Util/Util.h"
#include <iostream>

namespace Wanted
{

	// dll 내부에서만 사용
	class Renderer
	{
	public:
		static void Draw(const char image)
		{
			std::cout << image;
		}

		// 위치 설정 및 그리기 한번에 처리하는 함수.
		static void Draw(const Vector2& position, const char image)
		{
			Util::SetConsolePosition(position);
			Draw(image);
		}

		// 위치,색상 설정 및 그리기.
		static void Draw(const Vector2& position, 
			Color color,
			const char image)
		{
			Util::SetConsoleTextColor(color);
			Draw(position, image);

			// 원래 색상으로 다시 설정 (흰색으로).
			Util::SetConsoleTextColor(Color::White);
		}
	};
}