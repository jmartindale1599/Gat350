
#include "3X3.h"

namespace neu {

	//1 0 0
	//0 1 0
	//0 0 1 

	const Matrix3x3 Matrix3x3::identity{

		Vector3{1,0,0},

		Vector3{0,1,0},

		Vector3{0,0,1}

	};

	const Matrix3x3 Matrix3x3::zero{

		Vector3{0,0,0},

		Vector3{0,0,0},

		Vector3{0,0,0}

	};

}
