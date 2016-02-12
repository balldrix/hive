#include "Sprite.h"
#include "Constants.h"

Sprite::Sprite() : 
m_pGraphics(NULL),
m_pTextureManager(NULL),
m_ID(""),
m_fileName(""),
m_numCols(1),
m_currentFrame(0),
m_initialised(false),
m_showHitBox(false),
m_colourFilter(colourNS::WHITE),
m_transKey(colourNS::MAGENTA)
{
	// initialise the spriteData struct
	m_spriteData = { 0, 0, Vector2D(0.0f, 0.0f),
		0.0f, 0.0f, RECT(), NULL, false, false };
}

Sprite::~Sprite()
{
}

bool
Sprite::Init(Graphics* graphics, TextureManager* textureManager, const char* ID, const char* fileName)
{
	m_pGraphics = graphics;
	m_pTextureManager = textureManager;

	m_ID = ID;
	m_fileName = fileName;

	if (fileName == NULL)
	{
		m_pTextureManager = NULL;
		return false;
	}

	m_spriteData.width = m_pTextureManager->GetWidth();
	m_spriteData.height = m_pTextureManager->GetHeight();
	m_spriteData.position = Vector2D(0.0f,0.0f);
	m_spriteData.scale = 1.0f;
	m_spriteData.angle = 0.0f;
	m_spriteData.rect.left = 0;
	m_spriteData.rect.right = m_spriteData.width;
	m_spriteData.rect.top = 0;
	m_spriteData.rect.bottom = m_spriteData.height;
	m_spriteData.flipHorizontal= false;
	m_spriteData.flipVertical = false;
	m_spriteData.texture = m_pTextureManager->GetTexture();

	m_numCols = m_spriteData.width / TILE_SIZE;
	

	m_initialised = true;

	return true;
}

void
Sprite::Update(float deltaTime)
{
}
	
void
Sprite::RenderSprite()
{
	if (m_pGraphics != NULL && m_pTextureManager != NULL )
	{
		m_pGraphics->RenderSprite(m_spriteData, m_colourFilter);
	}
}

void
Sprite::RenderSprite(Vector2D position)
{
	m_spriteData.position = position;

	RenderSprite();
}


void
Sprite::RenderSprite(Vector2D position, RECT rect)
{
	m_spriteData.position = position;
	SetRect(rect);

	RenderSprite();
}

void
Sprite::RenderHitBox(Graphics* graphics, AABB box)
{
	// draw primitives using graphics pointer

	// set vertices to collision box corners

	//vertex 0
	m_vertex[0].x = box.GetMin().x;
	m_vertex[0].y = box.GetMin().y;
	m_vertex[0].z = 0.0f;
	m_vertex[0].rhw = 1.0f;
	m_vertex[0].colour = colourNS::LIME;

	//vertex 1
	m_vertex[1].x = box.GetMax().x;
	m_vertex[1].y = box.GetMin().y;
	m_vertex[1].z = 0.0f;
	m_vertex[1].rhw = 1.0f;
	m_vertex[1].colour = colourNS::LIME;

	//vertex 2
	m_vertex[2].x = box.GetMax().x;
	m_vertex[2].y = box.GetMax().y;
	m_vertex[2].z = 0.0f;
	m_vertex[2].rhw = 1.0f;
	m_vertex[2].colour = colourNS::LIME;

	//vertex 3
	m_vertex[3].x = box.GetMin().x;
	m_vertex[3].y = box.GetMax().y;
	m_vertex[3].z = 0.0f;
	m_vertex[3].rhw = 1.0f;
	m_vertex[3].colour = colourNS::LIME;

	//vertex 4
	m_vertex[4].x = box.GetMin().x;
	m_vertex[4].y = box.GetMin().y;
	m_vertex[4].z = 0.0f;
	m_vertex[4].rhw = 1.0f;
	m_vertex[4].colour = colourNS::LIME;

	graphics->CreateVertexBuffer(m_vertex, sizeof m_vertex, m_vertexBuffer);

	graphics->RenderQuad(m_vertexBuffer);
}

void
Sprite::SetID(const char* ID)
{
	m_ID = ID;
}

void
Sprite::SetTransKey(int r, int g, int b)
{
	m_transKey = D3DCOLOR_XRGB(r,g,b);
}

void
Sprite::SetWidth(int w)
{
	m_spriteData.width = w;
}

void
Sprite::SetHeight(int h)
{
	m_spriteData.height = h;
}

void
Sprite::SetRect()
{
	m_spriteData.rect.left = (m_currentFrame % m_numCols) * m_spriteData.width;
	m_spriteData.rect.right = m_spriteData.rect.left + m_spriteData.width;
	m_spriteData.rect.top = m_currentFrame / m_numCols * m_spriteData.height;
	m_spriteData.rect.bottom = m_spriteData.rect.top + m_spriteData.height;
}

void
Sprite::SetRect(RECT rect)
{
	m_spriteData.rect = rect;
}

void				
Sprite::SetRect(int left, int right, int top, int bottom)
{
	m_spriteData.rect.left = left;
	m_spriteData.rect.right = right;
	m_spriteData.rect.top = top;
	m_spriteData.rect.bottom = bottom;
}

void
Sprite::SetVerticalFlip(bool vFlip)
{
	m_spriteData.flipVertical = vFlip;
}

void
Sprite::SetHorizontalFlip(bool vFlip)
{
	m_spriteData.flipHorizontal = vFlip;
}

void 
Sprite::SetCurrentFrame(unsigned int frame)
{
	m_currentFrame = frame;
}

void
Sprite::SetShowHitBox(bool showHitBox)
{
	m_showHitBox = showHitBox;
}

void						
Sprite::SetFacingDirection(FACING_DIRECTION direction)
{
	m_facingDirection = direction;
}

void
Sprite::FlipSprite()
{
	if(m_facingDirection == RIGHT)
	{
		m_spriteData.flipHorizontal = false;
	}
	else
	{
		m_spriteData.flipHorizontal = true;
	}
}

void
Sprite::Reset()
{
	m_collisionBox = AABB();
	m_currentFrame = 0;
	SetFacingDirection(RIGHT);
}