#pragma once
#include <array>
#include <iostream>
#define MAX_MAP_SIZE 15

namespace game {

	class map {
	private:
		unsigned int map_size;
		std::array<std::array<char, MAX_MAP_SIZE>, MAX_MAP_SIZE > m;
	public:
		//棋盘初始化
		map() {
			for (unsigned int i = 0; i < MAX_MAP_SIZE; i++) {
				for (unsigned int j = 0; j < MAX_MAP_SIZE; j++) {
					m[i][j] = '.';
				}
			}
		}
		void set_map_size(unsigned int size);
		unsigned int get_map_size() const;
		// 在指定位置放置棋子
		void place_piece(unsigned int row, unsigned int col, char piece);
		//输入位置，输出棋子
		char show_piece(unsigned int row, unsigned int col) const;
		//输入位置，判断是否有棋子
		bool has_piece(unsigned int row, unsigned int col) const;
		//输入行列，判断是否超出棋盘范围
		bool out_map(unsigned int row, unsigned int col) const;
		//判断棋盘是否下满
		bool map_full() const;
		//返回某个方向上除自身外还有几个子
		unsigned int piece_number_in_direction(const char& symbol, unsigned int current_x, unsigned int current_y, int dir_x, int dir_y) const;
		//判断是否有五子
		bool five_pieces_in_a_line(const char& symbol) const;
	};


	inline void map::set_map_size(unsigned int size)
	{
		map_size = size;
	}

	inline unsigned int map::get_map_size() const
	{
		return map_size;
	}

	inline void game::map::place_piece(unsigned int row, unsigned int col, char piece)
	{
		m[row][col] = piece;
	}

	inline char map::show_piece(unsigned int row, unsigned int col) const
	{
		return m[row][col];
	}

	inline bool map::has_piece(unsigned int row, unsigned int col) const
	{
		if (m[row][col] != '.') {
			return true;
		}
		else {
			return false;
		}
	}

	inline bool map::out_map(unsigned int row, unsigned int col) const
	{
		if (row >= map_size || col >= map_size) {
			return true;
		}
		else {
			return false;
		}
	}

	inline bool map::map_full() const
	{
		for (unsigned int i = 0; i < map_size; i++) {
			for (unsigned int j = 0; j < map_size; j++) {
				if (!has_piece(i, j)) {
					return false;
				}
			}
		}
		return true;
	}


	inline unsigned int map::piece_number_in_direction(const char& symbol, unsigned int current_x, unsigned int current_y, int dir_x, int dir_y) const
	{
		for (int i = 1; i <= 5; i++) {
			if (out_map(current_x + i * dir_x, current_y + i * dir_y) || symbol != show_piece(current_x + i * dir_x, current_y + i * dir_y)) {
				return i - 1;
			}
		}
	}
	inline bool map::five_pieces_in_a_line(const char& symbol) const
	{
		for (unsigned int i = 0; i < map_size; i++) {
			for (unsigned int j = 0; j < map_size; j++) {
				if (symbol == show_piece(i, j)) {
					//横向判断
					int right = piece_number_in_direction(symbol, i, j, 1, 0);
					int left = piece_number_in_direction(symbol, i, j, -1, 0);
					if (right + left + 1 >= 5) {
						return true;
					}
					//纵向判断
					int down = piece_number_in_direction(symbol, i, j, 0, 1);
					int up = piece_number_in_direction(symbol, i, j, 0, -1);
					if (up + down + 1 >= 5) {
						return true;
					}
					//斜上判断
					int right_up = piece_number_in_direction(symbol, i, j, 1, -1);
					int left_down = piece_number_in_direction(symbol, i, j, -1, 1);
					if (right_up + left_down + 1 >= 5) {
						return true;
					}
					//斜下判断
					int right_down = piece_number_in_direction(symbol, i, j, 1, 1);
					int left_up = piece_number_in_direction(symbol, i, j, -1, -1);
					if (right_down + left_up + 1 >= 5) {
						return true;
					}
				}
			}
		}
		return false;
	}
}