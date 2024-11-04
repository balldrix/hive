#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

struct Bounds
{
	unsigned int x;
	unsigned int y;
	unsigned int height;
	unsigned int width;
};

struct FrameData
{
	unsigned int frameIndex;
	Bounds bounds;

	static FrameData GetFrameData(const int frameIndex, std::vector<FrameData>& frameData)
	{
		auto it = std::find_if(frameData.begin(), frameData.end(),
			[&frameIndex](const FrameData& obj) { return obj.frameIndex == frameIndex; });

		if (it != frameData.end())
			return *it;
		else

			return FrameData();
	}
};

struct TagData
{
	std::string name;
	std::vector<FrameData> frameData;

	static TagData GetTagData(const std::string tagName, std::vector<TagData>& tagData)
	{
		auto it = std::find_if(tagData.begin(), tagData.end(),
			[&tagName](const TagData& obj) { return obj.name == tagName; });

		if (it != tagData.end())
			return *it;
		else

			return TagData();
	}
};

struct HitBoxData
{
	std::string name;
	std::vector<TagData> tagData;

	static HitBoxData GetHitboxData(const std::string hitBoxName, std::vector<HitBoxData>& hitBoxData)
	{
		auto it = std::find_if(hitBoxData.begin(), hitBoxData.end(),
			[&hitBoxName](const HitBoxData& obj) { return obj.name == hitBoxName; });

		if (it != hitBoxData.end())
			return *it;
		else

			return HitBoxData();
	}
};

inline void from_json(const json& j, HitBoxData& h)
{
	h.name = j["hitBoxName"];

	for(auto& it : j["tagData"])
	{
		TagData tagdata;
		tagdata.name = it["animationName"];

		for (auto& it : it["frames"])
		{
			FrameData frameData {};
			auto bounds = it["bounds"];
				
			frameData.frameIndex = it["frameIndex"];
			frameData.bounds.height = bounds["height"];
			frameData.bounds.width = bounds["width"];
			frameData.bounds.x = bounds["x"];
			frameData.bounds.y = bounds["y"];

			tagdata.frameData.push_back(frameData);
		}

		h.tagData.push_back(tagdata);
	}
}