cmake_minimum_required(VERSION 3.29)
project(Hive)

set(CMAKE_CXX_STANDARD 20)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${CMAKE_VS_PLATFORM_NAME}\${VS_CONFIGURATION_TYPE})

add_definitions(-DUNICODE -D_UNICODE)

find_package(directxtk CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/AABB.cpp src/Animator.cpp src/AudioEngine.cpp src/BarController.cpp src/Camera.cpp src/CharacterPortrait.cpp 
								src/Collider.cpp src/ControlSystem.cpp src/EncounterHandler.cpp src/EncounterSceneState.cpp src/Enemy.cpp src/EnemyAttackRunState.cpp 
								src/EnemyAttackState.cpp src/EnemyDataContainer.cpp src/EnemyDeadState.cpp src/EnemyHurtState.cpp src/EnemyIdleState.cpp src/EnemyKnockbackState.cpp
								src/EnemyRunningState.cpp src/EnemyVictoryState.cpp src/EnemyWalkingState.cpp src/Error.cpp src/Game.cpp src/GameObject.cpp src/GameOverSceneState.cpp 
								src/GameOverScreen.cpp src/GameOverScreenController.cpp src/GameState.cpp src/GameStateManager.cpp src/GameplayGameState.cpp src/Graphics.cpp src/HitBoxManager.cpp
								src/ImpactFx.cpp src/InGameHudManager.cpp src/Input.cpp src/KingMook.cpp src/KingMookChargeState.cpp src/KingMookEnemyGlobalState.cpp src/LevelRenderer.cpp src/Main.cpp
								src/MookEnemyGlobalState.cpp src/MookRunningEnemyGlobalState.cpp src/NPCFactory.cpp src/NPCManager.cpp src/ParticleSystem.cpp src/PixelTexture.cpp src/Player.cpp
								src/PlayerAttackState.cpp src/PlayerBlockState.cpp src/PlayerDeadState.cpp src/PlayerGlobalState.cpp src/PlayerHurtState.cpp src/PlayerIdleState.cpp src/PlayerKnockbackState.cpp
								src/PlayerRunningState.cpp src/PlayerSprintingState.cpp src/Randomiser.cpp src/RunningEnemy.cpp src/RunningEnemyDeadState.cpp src/Sound.cpp src/SoundManager.cpp src/SoundSource.cpp
								src/Sprite.cpp src/SpriteSheet.cpp src/Texture.cpp src/TilemapHandler.cpp src/Timer.cpp src/TravelPrompt.cpp src/TravellingHandler.cpp src/TravellingSceneState.cpp src/Window.cpp
								src/AABB.h src/Animation.h src/Animator.h src/AudioConstants.h src/AudioEngine.h src/BarController.h src/Camera.h src/CharacterPortrait.h src/Collider.h src/ControlSystem.h src/DamageData.h
								src/EncounterHandler.h src/EncounterSceneState.h src/Enemy.h src/EnemyAttackRunState.h src/EnemyAttackState.h src/EnemyData.h src/EnemyDataContainer.h src/EnemyDeadState.h src/EnemyHurtState.h
								src/EnemyIdleState.h src/EnemyKnockbackState.h src/EnemyOwnedStates.h src/EnemyRunningState.h src/EnemyVictoryState.h src/EnemyWalkingState.h src/Error.h src/Game.h src/GameObject.h src/GameOverSceneState.h
								src/GameOverScreen.h src/GameOverScreenController.h src/GameState.h src/GameStateManager.h src/GameplayConstants.h src/GameplayGameState.h src/GameplayOwnedSceneStates.h src/GlobalConstants.h src/Graphics.h
								src/HitBoxData.h src/HitBoxManager.h src/ImpactFX.h src/InGameHudConstants.h src/InGameHudManager.h src/Input.h src/KingMook.h src/KingMookChargeState.h src/KingMookEnemyGlobalState.h src/LevelRenderer.h
								src/MookEnemyGlobalState.h src/MookRunningEnemyGlobalState.h src/NPCFactory.h src/NPCManager.h src/ParticleSystem.h src/PixelTexture.h src/Player.h src/PlayerAttackState.h src/PlayerBlockState.h src/PlayerConstants.h
								src/PlayerData.h src/PlayerDeadState.h src/PlayerGlobalState.h src/PlayerHurtState.h src/PlayerIdleState.h src/PlayerKnockbackState.h src/PlayerOwnedStates.h src/PlayerRunningState.h src/PlayerSprintingState.h
								src/Randomiser.h src/Resources.h src/RunningEnemy.h src/RunningEnemyDeadState.h src/Sound.h src/SoundManager.h src/SoundSource.h src/Sprite.h src/SpriteFrameData.h src/SpriteSheet.h src/State.h src/StateMachine.h
								src/Texture.h src/TilemapData.h src/TilemapHandler.h src/Timer.h src/TravelPrompt.h src/TravellingHandler.h src/TravellingSceneState.h src/UnitVectors.h src/Window.h src/pch.h src/Logger.cpp src/Logger.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft::DirectXTK)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL)
target_link_libraries(${PROJECT_NAME} PRIVATE SndFile::sndfile)
target_link_libraries(main PRIVATE spdlog::spdlog_header_only)