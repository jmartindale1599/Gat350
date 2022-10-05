#include "Time.h"

namespace neu {

	void Time::Tick() {

		clock_duration duration = clock::now() - m_startTimePoint;

		time = duration.count() / (float)clock::duration::period::den;

		duration = clock::now() - m_frameTimePoint;

		deltaTime = duration.count() / (float)clock::duration::period::den;

		m_frameTimePoint = clock::now();

	}

}
