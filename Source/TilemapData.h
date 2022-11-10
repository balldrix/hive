#include "pch.h"

#pragma once

namespace 
{
	struct TilemapLayer
	{
		std::vector<unsigned int> data;
		unsigned int height = {};
		unsigned int id = {};
		std::string name = {};
		unsigned int width = {};
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
		json layers = j["layers"];		

		for(auto i = layers.begin(); i != layers.end(); ++i)
		{
			json layer = i.value();
			json data = layer["data"];

			TilemapLayer tilemapLayer;

			for(auto j = data.begin(); j != data.end(); ++j)
			{
				tilemapLayer.data.push_back(j.value());
			}

			tilemapLayer.height = layer["height"];
			tilemapLayer.id = layer["id"];
			tilemapLayer.name = layer["name"];
			tilemapLayer.width = layer["width"];

			t.layers.push_back(tilemapLayer);
		}
		
		t.tileheight = j.at("tileheight").get<unsigned int>();
		t.tilewidth = j.at("tilewidth").get<unsigned int>();
		t.width = j.at("width").get<unsigned int>();
	}
}