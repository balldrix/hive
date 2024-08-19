#include "LevelRenderer.h"

#include "Graphics.h"
#include "Camera.h"
#include "Shader.h"
#include "TilemapHandler.h"
#include "TilemapData.h"
#include "Texture.h"
#include "Material.h"
#include "QuadMesh.h"
#include "Tile.h"
#include "TextureCoords.h"
#include "GlobalConstants.h"
#include "InstanceData.h"

using namespace GlobalConstants;

LevelRenderer::LevelRenderer() :
	m_camera(nullptr),
	m_shader(nullptr),
	m_tilemapHandler(nullptr),
	m_texture(nullptr),
	m_material(nullptr),
	m_quadMesh(nullptr),
	m_tile(nullptr),
	m_tileInstances(0),
	m_tileWidth(0),
	m_tileHeight(0),
	m_tileSetSpriteWidth(0),
	m_tileSetSpriteHeight(0),
	m_tileSetWidth(0),
	m_numTiles(0)
{
}

LevelRenderer::~LevelRenderer()
{
	DeleteAll();
}

void LevelRenderer::Init(Graphics* graphics, Camera* camera, Shader* shader)
{
	m_camera = camera;
	m_shader = shader;

	m_tilemapHandler = new TilemapHandler();
	m_tilemapHandler->LoadTilemap("GameData\\Tilemaps\\tm_bunker.json");

	m_texture = new Texture();
	m_texture->LoadTexture(graphics, "GameData\\Tilesets\\ts_bunker.png");

	m_material = new Material();
	m_material->Init(m_texture, m_shader);

	m_quadMesh = new QuadMesh();
	m_quadMesh->Init(graphics);
	m_quadMesh->CreateInstanceBuffer(graphics, NumTilesPerScreen * m_tilemapHandler->GetTilemapData().layers.size());

	m_tile = new Tile();
	m_tile->Init(graphics, m_quadMesh, m_material);

	m_tileWidth = m_tilemapHandler->GetTilemapData().tilewidth;
	m_tileHeight = m_tilemapHandler->GetTilemapData().tileheight;
	
	ID3D11Texture2D* tex2D;
	D3D11_TEXTURE2D_DESC desc;
	tex2D = (ID3D11Texture2D*)m_texture->GetResource();
	tex2D->GetDesc(&desc);
	tex2D->Release();
	
	m_tileSetSpriteWidth = desc.Width;
	m_tileSetSpriteHeight = desc.Height;
	m_tileSetWidth = m_tileSetSpriteWidth / m_tileWidth;

	m_tile->SetSize(Vector2((float)m_tileWidth, (float)m_tileWidth));
	m_tile->Update();
}

void LevelRenderer::Render(Graphics* graphics)
{
	auto numLayers = m_tilemapHandler->GetTilemapData().layers.size();
	auto layers = m_tilemapHandler->GetTilemapData().layers;

	for(auto i = layers.begin(); i != layers.end(); ++i)
	{
		m_tileInstances.clear();

		UpdateInstanceData(graphics, *i);

		InstanceType* instances = m_tileInstances.data();

		D3D11_MAPPED_SUBRESOURCE mr;
		InstanceType* pMatrices = nullptr;

		DX::ThrowIfFailed(graphics->GetDeviceContext()->Map(m_quadMesh->GetInstanceBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mr));

		InstanceType* instanceData = reinterpret_cast<InstanceType*>(mr.pData);

		for (UINT i = 0; i < m_tileInstances.size(); i++)
		{
			instanceData[i] = instances[i];
		}

		graphics->GetDeviceContext()->Unmap(m_quadMesh->GetInstanceBuffer(), 0);

		m_tile->RenderInstanced(graphics, (unsigned int)m_tileInstances.size());
	}
}

void LevelRenderer::UpdateInstanceData(Graphics* graphics, const TilemapLayer& layer)
{
	auto layerData = layer;
	auto tileMapWidth = m_tilemapHandler->GetTilemapData().width;
	auto tileMapHeight = m_tilemapHandler->GetTilemapData().height;
	int instanceCount = 0;

	for(size_t x = 0; x < tileMapWidth; x++)
	{
		for(size_t y = 0; y < tileMapHeight; y++)
		{
			auto index = y * tileMapWidth + x;
			auto tileId = layerData.data[index];
			InstanceType* instance = GetInstanceData(graphics, tileId, (unsigned int)x,  tileMapHeight - (unsigned int)y, layerData.id);

			if(instance == nullptr)
				continue;

			m_tileInstances.push_back(*instance);
		}
	}
}

InstanceType* LevelRenderer::GetInstanceData(Graphics* graphics, 
	unsigned int tileId, 
	const unsigned int& posX, 
	const unsigned int& posY,
	const unsigned int& posZ)
{
	if (tileId == 0)
		return nullptr;
	else
		tileId--;

	RECT rect{};
	rect.left = (tileId % m_tileSetWidth) * m_tileWidth;
	rect.right = rect.left + m_tileWidth;
	rect.top = (tileId / m_tileSetWidth) * m_tileHeight;
	rect.bottom = rect.top + m_tileHeight;

	TextureCoords texCoords{};
	texCoords.left = rect.left / (float)m_tileSetSpriteWidth,
	texCoords.right = rect.right / (float)m_tileSetSpriteWidth,
	texCoords.top = rect.top / (float)m_tileSetSpriteHeight;
	texCoords.bottom = rect.bottom / (float)m_tileSetSpriteHeight;

	Vector2 position = { (float)(posX * m_tileWidth), (float)(posY * m_tileHeight) - m_tileHeight * 1.75f };
	position.x -= m_camera->GetPosition().x;

	auto width = m_camera->GetWidth();
	auto cameraLeft = m_camera->GetPosition().x;
	auto cameraRight = m_camera->GetPosition().x + width;

	if ((position.x + m_tileWidth) < cameraLeft || (position.x - m_tileWidth) > cameraRight)
		return nullptr;

	InstanceType instance;

	Matrix translationalMatrix = XMMatrixTranslation(position.x / m_tileWidth, position.y / m_tileHeight, posZ);
	Matrix rotationalMatrix = XMMatrixIdentity();
	Matrix scaleMatrix = XMMatrixIdentity();
	Matrix tempMatrix = rotationalMatrix * scaleMatrix * translationalMatrix;

	instance.position = tempMatrix;
	instance.texOffset = XMFLOAT2(texCoords.left, texCoords.top);
	instance.texScale = XMFLOAT2(1.0f / m_tileSetWidth, 1.0f / m_tileSetWidth);
	
	return &instance;
}

void LevelRenderer::DeleteAll()
{
	delete m_tile;
	m_tile = nullptr;
	
	delete m_texture;
	m_texture = nullptr;
	
	delete m_tilemapHandler;
	m_tilemapHandler = nullptr;
}
