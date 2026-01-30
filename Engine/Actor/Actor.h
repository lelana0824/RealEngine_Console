#pragma once
#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace Wanted {
	
	class Level;

	class WANTED_API Actor : public RTTI
	{
		// RTTI 코드 추가
		RTTI_DECLARATIONS(Actor, RTTI)
	public:
		Actor(const char image = ' ', 
			const Vector2& position = Vector2::Zero,
			Color color = Color::White
		);
		virtual ~Actor();

		// 게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 위치 변경 및 읽기 함수
		void SetPosition(const Vector2& newPosition);
		inline Vector2 GetPosition() const {
			return position;
		}


		// 오너십 추가읽기 함수
		inline void SetOwner(Level* newOwner) { owner = newOwner; }
		inline Level* GetOwner() const { return owner; }

		// Getter;
		inline bool HasBeganPlay() const { 
			return hasBeganPlay; 
		}
		inline bool IsActive() const 
		{ 
			return isActive && !destroyRequested; 
		}
		inline bool IsDestroyRequested() const {
			return destroyRequested;
		}
	protected:
		// 이미 BeginPlay 이벤트를 받았는지 여부
		bool hasBeganPlay = false;

		// 활성화 상태 여부
		bool isActive = true;

		// 현재 프레임에 삭제 요청 받았는지 여부
		bool destroyRequested = false;

		char image = ' ';

		Color color = Color::White;

		// 오너십 Ownership.
		Level* owner = nullptr;

	private:
		Vector2 position;
	};

}

