#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include "map.hpp"
#include "player.hpp"



namespace game {
    // 定义策略基类
    class policy {
    private:
        std::string name;
    public:
        virtual ~policy() = default;
        virtual std::pair<unsigned int, unsigned int> move(const map& current_map) const = 0;
        virtual std::string show_name() const = 0;
    };

    //手动输入策略
    class key_board_policy : public policy {
    private:
        std::string name = "键盘输入模式";
    public:
        virtual std::pair<unsigned int, unsigned int> move(const map& current_map) const override {
            unsigned int row, col;
            std::cin >> row >> col;
            return std::make_pair(row, col);
        }
        virtual std::string show_name() const override {
            return name;
        }
    };

    //随机输出策略
    class random_policy : public policy {
    private:
        std::string name = "随机输出模式";
    public:
        virtual std::pair<unsigned int, unsigned int> move(const map& current_map) const override {
            std::vector<std::pair<unsigned int, unsigned int>> available_places;
            for (unsigned int row = 0; row < current_map.get_map_size(); row++) {
                for (unsigned int col = 0; col < current_map.get_map_size(); col++) {
                    if (!current_map.has_piece(row, col)) {
                        available_places.push_back(std::make_pair(row, col));
                    }
                }
            }
            // 从可用位置中随机选择一个
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<size_t> dis(0, available_places.size() - 1);
            return available_places[dis(gen)];
        }
        virtual std::string show_name() const override {
            return name;
        }
    };

    //随机选择得分最高点输出
    class choose_highest_point : public policy {
    private:
        std::string name = "随机选择最优点";
        //输入点是否有效且已存在vector中
        void point_valid_and_store(const unsigned int& i, const unsigned int& j, const map& current_map, std::vector<std::pair<unsigned int, unsigned int>>& vec) const {
            if (!current_map.out_map(i, j) && !std::count(vec.begin(), vec.end(), std::make_pair(i, j)) && !current_map.has_piece(i, j)) {
                vec.push_back(std::make_pair(i, j));
            }
        }
        //将各点进行判断并分类保存
        void judge_and_store_in_direction(const unsigned int& i, const unsigned int& j, const int d_x, const int d_y, const char symbol, const map& current_map, std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& vec) const {
            int num1 = current_map.piece_number_in_direction(symbol, i, j, d_x, d_y);
            int num2 = current_map.piece_number_in_direction(symbol, i, j, -d_x, -d_y);
            for (int index = 0; index < vec.size(); index++) {
                if (num1 + num2 == index) {
                    point_valid_and_store(i + d_x * num1 + d_x * 1, j + d_y * num1 + d_y * 1, current_map, vec[index]);
                    point_valid_and_store(i - d_x * num2 - d_x * 1, j - d_y * num2 - d_y * 1, current_map, vec[index]);
                }
            }
        }
        //返回最优点构成的集合
        void judge(const char& symbol, const map& current_map, std::vector<std::pair<unsigned int, unsigned int>>& vec) const {
            std::vector<std::pair<unsigned int, unsigned int>> five_in_a_line;  //能够组成五点的位置
            std::vector<std::pair<unsigned int, unsigned int>> four_in_a_line;  //能够组成四点的位置
            std::vector<std::pair<unsigned int, unsigned int>> three_in_a_line; //能够组成三点的位置
            std::vector<std::pair<unsigned int, unsigned int>> two_in_a_line;   //能够组成两点的位置
            std::vector<std::pair<unsigned int, unsigned int>> one_in_a_line;   //能够组成一点的位置

            std::vector<std::vector<std::pair<unsigned int, unsigned int>>> max_available_places;
            max_available_places.push_back(two_in_a_line);
            max_available_places.push_back(three_in_a_line);
            max_available_places.push_back(four_in_a_line);
            max_available_places.push_back(five_in_a_line);

            for (int i = 0; i < current_map.get_map_size(); i++) {
                for (int j = 0; j < current_map.get_map_size(); j++) {
                    if (symbol == current_map.show_piece(i, j)) {
                        judge_and_store_in_direction(i, j, 1, 0, symbol, current_map, max_available_places);    //横向
                        judge_and_store_in_direction(i, j, 0, 1, symbol, current_map, max_available_places);    //竖向
                        judge_and_store_in_direction(i, j, 1, -1, symbol, current_map, max_available_places);   //斜上
                        judge_and_store_in_direction(i, j, 1, 1, symbol, current_map, max_available_places);    //斜下
                    }
                }
            }

            for (int i = max_available_places.size() - 1; i >= 0; i--) {
                if (!max_available_places[i].empty()) {
                    vec = max_available_places[i];
                    break;
                }
            }
            if (vec.empty()) {
                vec = one_in_a_line;
            }
        }
    public:
        virtual std::pair<unsigned int, unsigned int> move(const map& current_map) const override {
            char AI_chess = '0';        //AI
            char player_piece = '#';    //玩家

            std::vector<std::pair<unsigned int, unsigned int>> available_places;
            std::vector<std::pair<unsigned int, unsigned int>> AI_best_places;
            std::vector<std::pair<unsigned int, unsigned int>> player_best_places;

            judge('0', current_map, AI_best_places);
            judge('#', current_map, player_best_places);

            if (AI_best_places.size() < player_best_places.size()) {
                available_places.insert(available_places.end(), AI_best_places.begin(), AI_best_places.end());
            }
            else {
                available_places.insert(available_places.end(), player_best_places.begin(), player_best_places.end());
            }

            //无最优位置：随机落子
            if (available_places.empty()) {
                for (unsigned int row = 0; row < current_map.get_map_size(); row++) {
                    for (unsigned int col = 0; col < current_map.get_map_size(); col++) {
                        if (!current_map.has_piece(row, col)) {
                            available_places.push_back(std::make_pair(row, col));
                        }
                    }
                }
            }

            // 从可用位置中随机选择一个
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<size_t> dis(0, available_places.size() - 1);
            return available_places[dis(gen)];
        }
        virtual std::string show_name() const override {
            return name;
        }
    };

    enum policy_type
    {
        KEYBOARD, RANDOM, BESTPLACE
    };
    class policy_factory {
    public:
        policy* create_policy(policy_type pt) {
            switch (pt)
            {
            case KEYBOARD:
                return new key_board_policy();
                break;
            case RANDOM:
                return new random_policy();
                break;
            case BESTPLACE:
                return new choose_highest_point();
                break;
            default:
                return nullptr;
                break;
            }
        }
    };
}