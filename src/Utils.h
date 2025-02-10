#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

namespace Utils 
{
	static Vector2 Truncate(const Vector2 v, float maxLength)
	{
		auto length = v.Length();

		if(length <= maxLength) return v;

		return v * (maxLength / length);
	}
};