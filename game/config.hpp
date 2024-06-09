#pragma once
#include <iostream>

namespace game {
	class config {
	private:
		unsigned int map_size, opponent_type, preemptive_type;
	public:
		// Default
		config() : map_size(10), opponent_type(1), preemptive_type(1) {}

		unsigned int get_map_size() const;
		void set_map_size(unsigned int size);

		unsigned int get_opponent_type() const;
		void set_opponent_type(unsigned int type);

		unsigned int get_preemptive_type() const;
		void set_preemptive_type(unsigned int type);

		bool config_true() const;

		friend std::istream& operator>>(std::istream& in, config& cfg);
		friend std::ostream& operator<<(std::ostream& out, const config& cfg);
	};

	inline unsigned int config::get_map_size() const {
		return map_size;
	}
	inline void config::set_map_size(unsigned int size) {
		map_size = size;
	}

	inline unsigned int config::get_opponent_type() const {
		return opponent_type;
	}
	inline void config::set_opponent_type(unsigned int type) {
		opponent_type = type;
	}

	inline unsigned int config::get_preemptive_type() const {
		return preemptive_type;
	}
	inline void config::set_preemptive_type(unsigned int type) {
		preemptive_type = type;
	}

	inline bool config::config_true() const
	{
		if (map_size < 7 || map_size >11) {
			return false;
		}
		else if (opponent_type < 1 || opponent_type>2) {
			return false;
		}
		else if (preemptive_type < 1 || preemptive_type >2) {
			return false;
		}
		else {
			return true;
		}
	}

	//运算符重载
	std::istream& operator>>(std::istream& in, config& cfg)
	{
		in >> cfg.map_size >> cfg.opponent_type >> cfg.preemptive_type;
		return in;
	}
	std::ostream& operator<<(std::ostream& out, const config& cfg)
	{
		out << "----------------游戏设置----------------" << std::endl;
		out << "  棋盘大小   ： " << cfg.map_size << " x " << cfg.map_size << std::endl;
		out << "  对手为     ： " << cfg.opponent_type << "（1：人类，2：AI）" << std::endl;
		out << "  先手类型为 ： " << cfg.preemptive_type << "（1：先手，2：后手）" << std::endl;
		return out;
	}
}