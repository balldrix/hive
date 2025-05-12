#include <directxtk/SimpleMath.h>

#include <codecvt>
#include <locale>
#include <string>

using namespace DirectX::SimpleMath;

namespace Utils
{
	static Vector2 Truncate(const Vector2 v, float maxLength)
	{
		auto length = v.Length();

		if(length <= maxLength) return v;

		return v * (maxLength / length);
	}

	static std::wstring ToWideString(const std::string& narrow)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(narrow);
	}

	static std::string ToNarrowString(const std::wstring& wide)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wide);
	}
};