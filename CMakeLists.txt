cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project (TicTacToe VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# 编译示例，文件名仅供参考

set (SOURCES_DIR_GAME
	game/policy.hpp
	game/config.hpp
	game/game.hpp
	game/player.hpp
	game/map.hpp
)

set (SOURCES_DIR_UTILS
	
	utils/console.hpp
	utils/console_abstract.hpp
	utils/console_windows.hpp
	utils/point.hpp
	utils/utils.hpp
)

# 入口文件
set (SOURCES_OTHERS
	main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES_OTHERS} ${SOURCES_DIR_GAME} ${SOURCES_DIR_UTILS}) 
source_group("src" FILES ${SOURCES_OTHERS})
source_group("src\\game" FILES ${SOURCES_DIR_GAME})
source_group("src\\utils" FILES ${SOURCES_DIR_UTILS})
