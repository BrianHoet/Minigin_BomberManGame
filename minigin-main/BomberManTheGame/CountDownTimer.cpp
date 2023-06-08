#include "CountDownTimer.h"

#include <iostream>

#include "GameObject.h"

CountDownTimer::CountDownTimer(dae::GameObject* owner,float StartCountDownNumber)
	:m_StartCountDownValue(StartCountDownNumber)
{
	m_IsDoneCountingDown = false;
	m_Counter = m_StartCountDownValue;
	m_pOwner = owner;
}

void CountDownTimer::Update(float deltaTime)
{
	if(!m_IsDoneCountingDown)
	{
		m_Counter -= 1.f * deltaTime;

		if(m_Counter <= 0.f)
		{
			m_IsDoneCountingDown = true;
			m_Counter = m_StartCountDownValue;
		}
	}
}

void CountDownTimer::SetIsDoneCountingDown(bool CountDownState)
{
	m_IsDoneCountingDown = CountDownState;
}

bool CountDownTimer::GetIsDoneCountingDown() const
{
	return m_IsDoneCountingDown;
}