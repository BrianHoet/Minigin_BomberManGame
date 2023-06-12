#pragma once
#include "BaseComponent.h"

namespace dae
{

	class CountDownTimer : public dae::BaseComponent
	{
	public:
		CountDownTimer(dae::GameObject* owner, float StartCountDownNumber);
		~CountDownTimer() = default;
		CountDownTimer(const CountDownTimer& other) = delete;
		CountDownTimer(CountDownTimer&& other) = delete;
		CountDownTimer& operator=(const CountDownTimer& other) = delete;
		CountDownTimer& operator=(CountDownTimer&& other) = delete;

		void Update(float deltaTime) override;
		void SetIsDoneCountingDown(bool CountDownState);
		bool GetIsDoneCountingDown() const;

	private:
		float m_StartCountDownValue;
		float m_Counter;
		bool m_IsDoneCountingDown;
	};

}