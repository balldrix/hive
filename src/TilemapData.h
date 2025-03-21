#pragma once

#include "AnimationData.h"

#include <string>
#include <vector>

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
	};

	struct TilemapData
	{
		unsigned int height = {};
		std::vector<TilemapLayer> layers;
		unsigned int tileheight = {};
		unsigned int tilewidth = {};
		unsigned int width = {};
	};

	void from_json(const json& j, TilemapData& t)
	{
		t.height = j.at("height").get<unsigned int>();
		json groups = j["layers"];

		for(auto groupIt = groups.begin(); groupIt != groups.end(); ++groupIt)
		{
			json layers = groupIt.value()["layers"];

			for(auto layerIt = layers.begin(); layerIt != layers.end(); ++layerIt)
			{
				json layer = layerIt.value();
				json data = layer["data"];

				TilemapLayer tilemapLayer;

				for(auto dataIt = data.begin(); dataIt != data.end(); ++dataIt)
				{
					tilemapLayer.data.push_back(dataIt.value());
				}

				tilemapLayer.height = layer["height"];
				tilemapLayer.id = layer["id"];
				tilemapLayer.name = layer["name"];
				tilemapLayer.width = layer["width"];
				tilemapLayer.parallaxMod = 1;

				if(layer.contains("parallaxx"))
				{
					tilemapLayer.parallaxMod = layer["parallaxx"];
				}

				tilemapLayer.depth = 0.0f;

				if(layer.contains("properties"))
				{
					json customProperties = layer["properties"];

					for(auto propertyIt = customProperties.begin(); propertyIt != customProperties.end(); ++propertyIt)
					{
						if(propertyIt.value().contains("name") && propertyIt.value()["name"] == "depth" &&
						   propertyIt.value().contains("value"))
						{
							tilemapLayer.depth = propertyIt.value()["value"];
							break;
						}
					}
				}

				t.layers.push_back(tilemapLayer);
			}
		}

		t.tileheight = j.at("tileheight").get<unsigned int>();
		t.tilewidth = j.at("tilewidth").get<unsigned int>();
		t.width = j.at("width").get<unsigned int>();
	}
}