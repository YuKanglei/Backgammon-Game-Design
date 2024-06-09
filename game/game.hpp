#pragma once
#include <iostream>
#include "config.hpp"
#include "map.hpp"
#include "player.hpp"

namespace game {
	class game {
	private:
		config con;
		map m;
		player player1, player2;
	public:
		game();
		void game_start();

		bool game_config_valid() const;
		void game_show_config();

		void initialization();
		void map_initialization();
		void player_initialization();

		void player_drop_piece(const player& PLAYER);

		//外部访问函数
		config get_config() const;
		void set_config(const config& c);
		map& get_map();	//可修改map
		player get_player1() const;
		player get_player2() const;
	};

	inline void game::game_start()
	{
		std::cout << "----------------游戏规则----------------" << std::endl;
		std::cout << "五子棋是一种两人对弈的策略游戏" << std::endl;
		std::cout << "双方轮流在棋盘交叉点上放置棋子" << std::endl;
		std::cout << "先将五个棋子在横竖或斜方向连成一线的获胜" << std::endl;
		std::cout << "----------------游戏设置----------------" << std::endl;
		std::cout << "请按序输入游戏参数：" << std::endl;
		std::cout << "1、棋盘大小（7-11）" << std::endl;
		std::cout << "2、对手类型（1：人类；2：AI）" << std::endl;
		std::cout << "3、先手类型（1：先手；2：后手）" << std::endl;
	}

	inline game::game() {
		con = config();
		m = map();
		player1 = player();
		player2 = player();
	}

	inline void game::initialization()
	{
		map_initialization();
		player_initialization();
	}

	inline void game::map_initialization()
	{
		m.set_map_size(con.get_map_size());
	}

	inline bool game::game_config_valid() const
	{
		if (con.config_true()) {
			return true;
		}
		else {
			return false;
		}
	}

	inline void game::game_show_config()
	{
		std::cout<<con;
	}

	inline void game::player_initialization()
	{
		player1.set_player_number(1);
		player2.set_player_number(2);
		if (con.get_preemptive_type() == 1) {
			player1.set_strategy("key_board");
			player1.set_chess_symbol('#');
			if (con.get_opponent_type() == 1) {
				player2.set_strategy("key_board");
				player2.set_chess_symbol('0');
			}
			else {
				player2.set_strategy("best_palces");
				player2.set_chess_symbol('0');
			}
		}
		else {
			player2.set_strategy("key_board");
			player2.set_chess_symbol('#');
			if (con.get_opponent_type() == 1) {
				player1.set_strategy("key_board");
				player1.set_chess_symbol('0');
			}
			else {
				player1.set_strategy("best_palces");
				player1.set_chess_symbol('0');
			}
		}
	}

	inline void game::player_drop_piece(const player& PLAYER)
	{
		char symbol = PLAYER.get_chess_symbol();
		std::pair<unsigned int, unsigned int> position = PLAYER.get_position(m);
		m.place_piece(position.first, position.second, symbol);
	}

	inline config game::get_config() const
	{
		return con;
	}

	inline void game::set_config(const config& c)
	{
		con = c;
		initialization();
	}

	inline map& game::get_map()
	{
		return m;
	}

	inline player game::get_player1() const
	{
		return player1;
	}

	inline player game::get_player2() const
	{
		return player2;
	}
}