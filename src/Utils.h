#include <directxtk/SimpleMath.h>

#include <string>
#include <stringapiset.h>
#include <WinNls.h>

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
		if(narrow.empty()) return std::wstring();

		int wideLength = MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), -1, nullptr, 0);
		if(wideLength == 0) return std::wstring();  // Conversion failed

		std::wstring wide(wideLength, 0);
		MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), -1, &wide[0], wideLength);

		// Remove the null terminator added by the function
		if(!wide.empty() && wide.back() == L'\0') {
			wide.pop_back();
		}

		return wide;
	}

	static std::string ToNarrowString(const std::wstring& wide)
	{
		if(wide.empty()) return std::string();

		int narrowLength = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
		if(narrowLength == 0) return std::string();  // Conversion failed

		std::string narrow(narrowLength, 0);
		WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, &narrow[0], narrowLength, nullptr, nullptr);

		// Remove the null terminator added by the function
		if(!narrow.empty() && narrow.back() == '\0') {
			narrow.pop_back();
		}

		return narrow;
	}
};