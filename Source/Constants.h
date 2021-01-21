#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace GlobalConstants
{
	const wchar_t WindowName[]					= L"Hive";				
	const wchar_t WndClassName[]				= L"MyWndClass";			
	const unsigned int WindowWidth				= 960;					
	const unsigned int WindowHeight				= 640;						
	const unsigned int GameWidth				= 120;							
	const unsigned int GameHeight				= 80;							
	const float BackColor[4]					= { 0.3f, 0.3f, 0.3f, 0.0f };	
	const float	Gravity							= 4.0f;
	const float StartingBoundaryMinX			= 1.0f;
	const float StartingBoundaryMinY			= 61.0f;
}

namespace GameplayConstants
{
	const float VerticalHitRange				= 3.0f;
}

namespace PlayerConstants
{
	const float RespawnGroundPositionY			= 70.0f;
	const float RespawnAirPositionY				= -20.0f;
	const float FallingSpeed					= 5.0f;
}

namespace InGameHudConstants
{
	const unsigned int HealthBarPositionX		= 11;
	const unsigned int HealthBarPositionY		= 8;
	const unsigned int EnemyHealthBarPositionY  = 18;
	const unsigned int EnemyPortraitPositionX	= 2;
	const unsigned int EnemyPortraitPositionY	= 14;
	const unsigned int LifeCounterPositionX		= 74;
	const unsigned int LifeCounterPositionY		= 6;
	const unsigned int TravelPromptPositionX	= 88;
	const unsigned int TravelPromptPositionY	= 16;
	const unsigned int KillCountPositionX		= 115;
	const unsigned int KillCountPositionY		= 10;
	const float TravelPromptTime				= 3.0f;
}

#endif _CONSTANTS_H_