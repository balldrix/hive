#pragma once

#include "AnimationData.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

using namespace DirectX::SimpleMath;

namespace
{
	struct ObjectData
	{
		unsigned int id = {};
		std::string type = {};
		std::string name = {};
		float height = {};
		float width = {};
		float x = {};
		float y = {};
	};

	struct TilemapLayer
	{
		std::vector<unsigned int> data;
		std::vector<ObjectData> objectData;
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
		std::vector<TilemapLayer> layers;
		unsigned int height = {};
		unsigned int width = {};
		unsigned int tileheight = {};
		unsigned int tilewidth = {};
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

			TilemapLayer tilemapLayer;
			tilemapLayer.name = layer.value("name", "");
			tilemapLayer.id = layer.value("id", 0);

			if(layer.contains("data"))
			{
				for(auto& dataValue : layer["data"])
				{
					tilemapLayer.data.push_back(dataValue.get<unsigned int>());
				}

				tilemapLayer.height = layer.value("height", 0);
				tilemapLayer.width = layer["width"];
				tilemapLayer.parallaxMod = layer.value("parallaxx", 1.0f);
				tilemapLayer.depth = 0.0f;
				tilemapLayer.scrollOffset = Vector2::Zero;
				tilemapLayer.scrollSpeedX = 0;
				tilemapLayer.scrollSpeedY= 0;
			}

			if(layer.contains("properties"))
			{
				json customProperties = layer["properties"];
				for(auto& property : customProperties)
				{
					if(property.contains("name") && property["name"] == "depth" && property.contains("value"))
					{
						tilemapLayer.depth = property["value"];
						continue;
					}

					if(property.contains("name") && property["name"] == "scrollSpeedX" && property.contains("value"))
					{
						tilemapLayer.scrollSpeedX = property["value"];
						continue;
					}

					if(property.contains("name") && property["name"] == "scrollSpeedY" && property.contains("value"))
					{
						tilemapLayer.scrollSpeedY = property["value"];
						continue;
					}
				}
			}

			if(layer.contains("objects"))
			{
				for(auto& objects : layer["objects"])
				{
					static unsigned int id = 0;
					ObjectData objectData;
					objectData.id = objects.value("id", id++);
					objectData.name = objects.value("name", "");
					objectData.type = objects.value("type", "");
					objectData.height = objects.value("height", 0.0f);
					objectData.width = objects.value("width", 0.0f);
					objectData.x = objects.value("x", 0.0f);
					objectData.y = objects.value("y", 0.0f);

					tilemapLayer.objectData.push_back(objectData);
				}
			}

			t.layers.push_back(tilemapLayer);
		}
	}

	void from_json(const json& j, TilemapData& t)
	{
		if(j.contains("layers"))
		{
			ParseLayers(t, j["layers"]);
		}

		t.height = j.at("height").get<unsigned int>();
		t.width = j.at("width").get<unsigned int>();
		t.tileheight = j.at("tileheight").get<unsigned int>();
		t.tilewidth = j.at("tilewidth").get<unsigned int>();
	}
}
