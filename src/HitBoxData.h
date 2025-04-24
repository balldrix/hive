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

		if(it != frameData.end())
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

		if(it != tagData.end())
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

		if(it != hitBoxData.end())
			return *it;
		else

			return HitBoxData();
	}
};

namespace nlohmann
{
	static inline void from_json(const json& j, HitBoxData& h)
	{
		h.name = j.at("hitBoxName");

		for(auto& it : j.at("tagData"))
		{
			TagData tagdata;
			tagdata.name = it.at("animationName");

			for(auto& it : it.at("frames"))
			{
				FrameData frameData{};
				auto& bounds = it.at("bounds");

				frameData.frameIndex = it.at("frameIndex");
				frameData.bounds.height = bounds.at("height");
				frameData.bounds.width = bounds.at("width");
				frameData.bounds.x = bounds.at("x");
				frameData.bounds.y = bounds.at("y");

				tagdata.frameData.push_back(frameData);
			}

			h.tagData.push_back(tagdata);
		}
	}
}