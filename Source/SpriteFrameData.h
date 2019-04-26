// SpriteFrameData.h
// Christopher Ball 2019
// hold sprite frame data from json file

#ifndef _SPRITEFRAMEDATA_H_
#define _SPRITEFRAMEDATA_H_

#include "pch.h"

// sprite sourceRect data
namespace
{
	struct SpriteFrameData
	{
		RECT	sourceRect;
		bool	rotated;
		Vector2	size;
		Vector2	origin;
	};

	void from_json(const json& j, SpriteFrameData& s)
	{
		json rect = j["frame"];
		s.sourceRect.left = rect["x"];
		s.sourceRect.top = rect["y"];
		s.sourceRect.right = s.sourceRect.left + rect["w"];
		s.sourceRect.bottom = s.sourceRect.top + rect["h"];

		// rotation
		s.rotated = j["rotated"];

		// size
		json size = j["sourceSize"];
		s.size.x = size["w"];
		s.size.y = size["h"];

		json origin = j["origin"];
		s.origin.x = origin["x"];
		s.origin.y = origin["y"];
	}
}

#endif // !_SPRITEFRAMEDATA_H_

