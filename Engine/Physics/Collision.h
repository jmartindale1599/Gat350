#pragma once

namespace neu {

	class Actor;

	class ICollision {

	public:

		virtual void onCollisionEnter(Actor* other) = 0;
		
		virtual void onCollisionExit(Actor* other) = 0;

	};

}
