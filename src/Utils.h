#pragma once

#include "EventManager.h"

#include <DirectXMath.h>
#include <directxtk/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stringapiset.h>
#include <vector>
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

	static std::optional<Vector2> TryParseVector2(const std::string& s)
	{
		std::stringstream ss(s);
		std::string token;
		std::vector<float> values;

		while(std::getline(ss, token, ',')) 
		{
			try 
			{
				values.push_back(std::stof(token));
			}
			catch(...) 
			{
				return std::nullopt;
			}
		}

		if(values.size() == 2) 
		{
			return Vector2{ values[0], values[1] };
		}
		return std::nullopt;
	}

	static std::optional<SpawnNPCArgument> TryParseNPCSpawn(const std::string& s)
	{
		try {
			nlohmann::json j = nlohmann::json::parse(s);
			if(!j.contains("id") || !j.contains("definitionId") || !j.contains("position"))
				return std::nullopt;

			SpawnNPCArgument arg;
			arg.id = j.at("id").get<std::string>();
			arg.definitionId = j.at("definitionId").get<std::string>();

			const auto& pos = j.at("position");
			arg.position = DirectX::XMFLOAT2{ pos.at("x"), pos.at("y") };
			return arg;
		}
		catch(...) {
			return std::nullopt;
		}

		return std::nullopt;
	}

	static EventArgument ParseEventArgument(const std::string& s)
	{
		if(auto spawnNPC = TryParseNPCSpawn(s))
		{
			return *spawnNPC;
		}

		if(auto vec = TryParseVector2(s)) 
		{
			return DirectX::XMFLOAT2{ vec->x, vec->y };
		}

		try 
		{
			return std::stof(s);
		}
		catch(const std::invalid_argument&) 
		{
			return s;
		}
	}
};