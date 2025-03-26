#pragma once

#include "AnimationData.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

using namespace DirectX::SimpleMath;

namespace
{
	struct TilemapLayer
	{
		std::vector<unsigned int> data;
		unsigned int height = {};
		unsigned int id = {};
		std::string name = {};
		unsigned int width = {};
		float parallaxMod = {};
		float depth = {};
		float scrollSpeedX = {};
		float scrollSpeedY = {};
		Vector2 scrollOffset;
	};

	struct TilemapData
	{
		unsigned int height = {};
		std::vector<TilemapLayer> layers;
		unsigned int tileheight = {};
		unsigned int tilewidth = {};
		unsigned int width = {};
	};

	void ParseLayers(TilemapData& t, const json& layers)
	{
		for(auto layerIt = layers.begin(); layerIt != layers.end(); ++layerIt)
		{
			json layer = layerIt.value();

			// If it has "layers", it's a group; process it recursively
			if(layer.contains("layers"))
			{
				ParseLayers(t, layer["layers"]);
				continue;
			}

			// Ensure the layer contains "data" before processing
			if(!layer.contains("data")) continue;

			TilemapLayer tilemapLayer;
			for(auto& dataValue : layer["data"])
			{
				tilemapLayer.data.push_back(dataValue.get<unsigned int>());
			}

			tilemapLayer.height = layer["height"];
			tilemapLayer.id = layer["id"];
			tilemapLayer.name = layer["name"];
			tilemapLayer.width = layer["width"];
			tilemapLayer.parallaxMod = layer.value("parallaxx", 1.0f);
			tilemapLayer.depth = 0.0f;
			tilemapLayer.scrollSpeedX = 0.0f;
			tilemapLayer.scrollSpeedY = -12.0f;
			tilemapLayer.scrollOffset = Vector2::Zero;

			if(layer.contains("properties"))
			{
				json customProperties = layer["properties"];
				for(auto& property : customProperties)
				{
					if(property.contains("name") && property["name"] == "depth" && property.contains("value"))
					{
						tilemapLayer.depth = property["value"];
						break;
					}
				}
			}

			t.layers.push_back(tilemapLayer);
		}
	}

	void from_json(const json& j, TilemapData& t)
	{
		t.height = j.at("height").get<unsigned int>();
		t.tileheight = j.at("tileheight").get<unsigned int>();
		t.tilewidth = j.at("tilewidth").get<unsigned int>();
		t.width = j.at("width").get<unsigned int>();

		if(j.contains("layers"))
		{
			ParseLayers(t, j["layers"]);
		}
	}
}
