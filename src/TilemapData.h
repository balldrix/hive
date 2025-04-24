#pragma once

#include <directxtk/SimpleMath.h>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;
using namespace DirectX::SimpleMath;

struct MapObjectData
{
	unsigned int id = {};
	std::string type = {};
	std::string name = {};
	float height = {};
	float width = {};
	float x = {};
	float y = {};
	std::unordered_map<std::string, std::string> customProperties;
};

struct TilemapLayer
{
	std::vector<unsigned int> data;
	std::vector<MapObjectData> objectData;
	unsigned int height = {};
	unsigned int id = {};
	std::string name = {};
	unsigned int width = {};
	float parallaxMod = {};
	float depth = {};
	float opacity = {};
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

inline void ParseLayers(TilemapData& t, const json& layers)
{
	for(auto layerIt = layers.begin(); layerIt != layers.end(); ++layerIt)
	{
		json layer = layerIt.value();

		// If it has "layers", it's a group; process it recursively
		if(layer.contains("layers"))
		{
			ParseLayers(t, layer.at("layers"));
			continue;
		}

		TilemapLayer tilemapLayer;
		tilemapLayer.name = layer.at("name");
		tilemapLayer.id = layer.at("id");

		if(layer.contains("data"))
		{
			for(const auto& dataValue : layer.at("data"))
			{
				tilemapLayer.data.push_back(dataValue.get<unsigned int>());
			}

			tilemapLayer.height = layer.at("height");
			tilemapLayer.width = layer.at("width");
			tilemapLayer.parallaxMod = layer.value("parallaxx", 0.0f);
			tilemapLayer.depth = 0.0f;
			tilemapLayer.opacity = layer.at("opacity");
			tilemapLayer.scrollOffset = Vector2::Zero;
			tilemapLayer.scrollSpeedX = 0;
			tilemapLayer.scrollSpeedY = 0;
		}

		if(layer.contains("properties"))
		{
			json customProperties = layer.at("properties");
			for(const auto& property : customProperties)
			{
				if(property.contains("name") && property.at("name") == "depth" && property.contains("value"))
				{
					tilemapLayer.depth = property.at("value");
					continue;
				}

				if(property.contains("name") && property.at("name") == "scrollSpeedX" && property.contains("value"))
				{
					tilemapLayer.scrollSpeedX = property.at("value");
					continue;
				}

				if(property.contains("name") && property.at("name") == "scrollSpeedY" && property.contains("value"))
				{
					tilemapLayer.scrollSpeedY = property.at("value");
					continue;
				}
			}
		}

		if(layer.contains("objects"))
		{
			for(const auto& objects : layer.at("objects"))
			{
				static unsigned int id = 0;
				MapObjectData objectData;
				objectData.id = objects.at("id");
				objectData.name = objects.at("name");
				objectData.type = objects.at("type");
				objectData.height = objects.at("height");
				objectData.width = objects.at("width");
				objectData.x = objects.at("x");
				objectData.y = objects.at("y");

				if(objects.contains("properties"))
				{
					for(const auto& property : objects.at("properties"))
					{
						std::string key = property.at("name");
						std::string value;

						if(property.contains("value"))
						{
							if(property.at("value").is_string())
								value = property.at("value");
							else
								value = property.at("value").dump();
						}

						objectData.customProperties[key] = value;
					}
				}

				tilemapLayer.objectData.push_back(objectData);
			}
		}

		t.layers.push_back(tilemapLayer);
	}
}

namespace nlohmann
{
	static inline void from_json(const json& j, TilemapData& t)
	{
		if(j.contains("layers"))
		{
			ParseLayers(t, j.at("layers"));
		}

		t.height = j.at("height");
		t.width = j.at("width");
		t.tileheight = j.at("tileheight");
		t.tilewidth = j.at("tilewidth");
	}
}