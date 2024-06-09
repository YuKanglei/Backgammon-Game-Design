#pragma once
#include <iostream>
#include <string>
#include "policy.hpp"

namespace game {
	class player {
	private:
		char chess_symbol;
		policy_factory* p_fac = new policy_factory();
		policy* strategy;
		unsigned int score;
		unsigned int player_number;	//玩家编号
	public:
		//默认初始化
		player() :chess_symbol('#'), strategy(), score(0), player_number(1) {}

		void set_chess_symbol(char symbol);
		void set_strategy(std::string stra);
		void add_score();
		void set_player_number(unsigned int number);

		std::pair<unsigned int, unsigned int> get_position(const map& current_map) const;
		char get_chess_symbol() const;
		std::string get_strategy_name() const;
		unsigned int get_score() const;
		unsigned int get_player_number() const;

		bool win(const map& current_map) const;
	};


	inline void player::set_chess_symbol(char symbol)
	{
		if (chess_symbol != symbol) {
			chess_symbol = symbol;
		}
	}

	inline void player::set_strategy(std::string stra)
	{
		if (stra == "key_board") {
			strategy = p_fac->create_policy(KEYBOARD);
		}
		else if (stra == "random") {
			strategy = p_fac->create_policy(RANDOM);
		}
		else if (stra == "best_palces") {
			strategy = p_fac->create_policy(BESTPLACE);
		}
	}

	inline void player::add_score()
	{
		score++;
	}

	inline void player::set_player_number(unsigned int number)
	{
		player_number = number;
	}

	inline std::pair<unsigned int, unsigned int> player::get_position(const map& current_map) const
	{
		return strategy->move(current_map);
	}

	inline char player::get_chess_symbol() const
	{
		return chess_symbol;
	}

	inline std::string player::get_strategy_name() const
	{
		return strategy->show_name();
	}

	inline unsigned int player::get_score() const
	{
		return score;
	}

	inline unsigned int player::get_player_number() const
	{
		return player_number;
	}

	inline bool player::win(const map& current_map) const
	{
		return current_map.five_pieces_in_a_line(chess_symbol);
	}
}