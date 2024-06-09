#include "utils/utils.hpp"
#include "game/game.hpp"
#define BOARD_X 6   //每节横向棋盘大小
#define BOARD_Y 3   //每节纵向棋盘大小
#define BASE_X 8    //横向偏移量
#define BASE_Y 4    //纵向偏移量

//显示棋盘
void show_current_map(game::game& g, const utils::console& c) 
{
    unsigned int map_size = g.get_config().get_map_size();

    //绘制横和纵向坐标轴
    for (unsigned int i = 0; i < map_size; i++) {
        if (i < 10) {
            char number = '0' + i;
            c.get_instance()->write(number, utils::point<unsigned int>(i * BOARD_X + BASE_X, 1));
            c.get_instance()->write(number, utils::point<unsigned int>(2, i * BOARD_Y + BASE_Y));
        }
        else {
            char number = '0' + i % 10;
            c.get_instance()->write('1', utils::point<unsigned int>(i * BOARD_X + BASE_X, 1));
            c.get_instance()->write('1', utils::point<unsigned int>(1, i * BOARD_Y + BASE_Y));
            c.get_instance()->write(number, utils::point<unsigned int>(i * BOARD_X + BASE_X + 1, 1));
            c.get_instance()->write(number, utils::point<unsigned int>(2, i * BOARD_Y + BASE_Y));
        }
    }

    for (unsigned int i = 0; i < map_size; i++) {
        for (unsigned int j = 0; j < map_size; j++) {
            //棋子绘制
            if (g.get_map().show_piece(i, j) != '.') {
                c.get_instance()->write(g.get_map().show_piece(i, j), utils::point<unsigned int>(i * BOARD_X + BASE_X, j * BOARD_Y + BASE_Y));
            }
            //上方和左侧边框绘制
            for (int index = -2; index <= 2; index++) {
                c.get_instance()->write('_', utils::point<unsigned int>(i * BOARD_X + BASE_X + index, j * BOARD_Y + BASE_Y - 2));
                if (index > -2 && index < 2) {
                    c.get_instance()->write('|', utils::point<unsigned int>(i * BOARD_X + BASE_X - 3, j * BOARD_Y + BASE_Y + index));
                }
            }
        }
    }
    //下方和右侧边框绘制
    for (unsigned int i = 0; i < map_size; i++) {
        for (int index = -2; index <= 2; index++) {
            c.get_instance()->write('_', utils::point<unsigned int>(i * BOARD_X + BASE_X + index, map_size * BOARD_Y + BASE_Y - 2));
        }
        for (int index = -1; index <= 1; index++) {
            c.get_instance()->write('|', utils::point<unsigned int>(map_size * BOARD_X + BASE_X - 3, i * BOARD_Y + BASE_Y + index));
        }
    }
}

//显示用户信息
void show_player_info(game::game& g, const utils::console& c) {
    std::string head_info = "                 使用棋子";
    std::string player = "PLAYER";
    std::string AI = "AI";
    char host_symbol = '#';
    char opponent_symbol = '0';

    unsigned int map_size = g.get_map().get_map_size();
    unsigned int head_X = map_size * BOARD_X + BASE_X + 6;
    unsigned int head_Y = BOARD_Y + BASE_Y;

    //输出表头
    for (unsigned int i = 0; i < head_info.size(); i++) {
        c.get_instance()->write(head_info[i], utils::point<unsigned int>(head_X + i, head_Y));
    }
    //输出玩家信息
    for (unsigned int index = 1; index <= 2; index++) {
        for (unsigned int i = 0; i < player.size(); i++) {
            c.get_instance()->write(player[i], utils::point<unsigned int>(head_X + i + 3, head_Y + index));
            if (i == player.size() - 1) {
                c.get_instance()->write('0' + index, utils::point<unsigned int>(head_X + player.size() + 3, head_Y + index));
                if (index == 1) {
                    c.get_instance()->write(g.get_player1().get_chess_symbol(), utils::point<unsigned int>(head_X + player.size() + 16, head_Y + index));
                    if (g.get_player1().get_strategy_name() != "键盘输入模式") {
                        for (unsigned int j = 0; j < AI.size(); j++)
                            c.get_instance()->write(AI[j], utils::point<unsigned int>(head_X + player.size() + 3 + j, head_Y + index));
                    }
                }
                else {
                    c.get_instance()->write(g.get_player2().get_chess_symbol(), utils::point<unsigned int>(head_X + player.size() + 16, head_Y + index));
                    if (g.get_player2().get_strategy_name() != "键盘输入模式") {
                        for (unsigned int j = 0; j < AI.size(); j++)
                            c.get_instance()->write(AI[j], utils::point<unsigned int>(head_X + player.size() + 3 + j, head_Y + index));
                    }
                }
            }
        }
    }
}

//显示棋盘与用户信息
void show_all(game::game& g, const utils::console& c) {
    show_current_map(g, c);
    show_player_info(g, c);
}

//显示胜利信息
void show_win(const game::game& g, const utils::console& c, const game::player& p) {
    std::string player = "PLAYER";
    std::string win = "WIN!";

    unsigned int map_size = g.get_config().get_map_size();
    unsigned int start_y = map_size * BOARD_Y + BASE_Y + 3;
    unsigned int start_x = (map_size / 2) * BOARD_X + BASE_X - 4;

    c.get_instance()->set_color(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    for (int i = 0; i < (player.size() + win.size() + 1); i++) {
        if (i < player.size()) {
            c.get_instance()->write(player[i], utils::point<unsigned int>(start_x + i, start_y));
        }
        else if (i == player.size()) {
            c.get_instance()->write('0' + p.get_player_number(), utils::point<unsigned int>(start_x + i, start_y));
        }
        else {
            c.get_instance()->write(win[i - player.size() - 1], utils::point<unsigned int>(start_x + i, start_y));
        }
    }
    c.get_instance()->set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//用户落子
void player_drop(const game::player& p, game::map& m, const utils::console& c) {
    std::string player = "player";
    std::string tip = "请输入落子坐标(X，Y):";
    std::string error = "当前输入无效，请重新输入:";
    //输出提示信息
    for (int i = 0; i < (player.size() + tip.size() + 1); i++) {
        if (i < player.size()) {
            c.get_instance()->write(player[i], utils::point<unsigned int>(i, m.get_map_size() * BOARD_Y + BASE_Y + 1));
        }
        else if (i == player.size()) {
            c.get_instance()->write('0' + p.get_player_number(), utils::point<unsigned int>(i, m.get_map_size() * BOARD_Y + BASE_Y + 1));
        }
        else {
            c.get_instance()->write(tip[i-player.size()-1], utils::point<unsigned int>(i, m.get_map_size() * BOARD_Y + BASE_Y + 1));
        }
    }
    while (1) {
        std::pair<unsigned int, unsigned int> position = p.get_position(m);
        //判定错误并输出错误信息
        if (m.out_map(position.first, position.second) || m.has_piece(position.first, position.second)) {
            //清空此行
            for (int i = 0; i < (player.size() + tip.size() + 9); i++) {
                c.get_instance()->write(' ', utils::point<unsigned int>(i, m.get_map_size() * BOARD_Y + BASE_Y + 1));
            }
            c.get_instance()->set_color(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            for (int i = 0; i < error.size(); i++) {
                c.get_instance()->write(error[i], utils::point<unsigned int>(i, m.get_map_size() * BOARD_Y + BASE_Y + 1));
            }
            c.get_instance()->set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
            m.place_piece(position.first, position.second, p.get_chess_symbol());
            break;
        }
    }
}

//游戏开始
void game_start(game::game& g, const utils::console& c) {
    game::config config;
    g.game_start();
    std::cin >> config;
    g.set_config(config);
    while (1) {
        if (!g.game_config_valid()) {
            c.get_instance()->clear();
            g.game_start();
            //打印警告信息
            c.get_instance()->set_color(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "当前输入无效，请重新输入:" << std::endl;
            c.get_instance()->set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            std::cin >> config;
            g.set_config(config);
        }
        else {
            break;
        }
    }
}

//游戏循环
void game_loop(game::game& g, const utils::console& c) {
    c.get_instance()->clear();
    show_all(g, c);
    while (!g.get_map().map_full()) {
        player_drop(g.get_player1(), g.get_map(), c);
        c.get_instance()->clear();
        show_all(g, c);
        if (g.get_player1().win(g.get_map())) {
            show_win(g, c, g.get_player1());
            break;
        }
        player_drop(g.get_player2(), g.get_map(), c);
        c.get_instance()->clear();
        show_all(g, c);
        if (g.get_player2().win(g.get_map())) {
            show_win(g, c, g.get_player2());
            break;
        }
    }
}

//游戏结束
void game_end(const game::game& g, const utils::console& c) {
    unsigned int map_size = g.get_config().get_map_size();
    unsigned int start_y = map_size * BOARD_Y + BASE_Y + 4;
    unsigned int start_x = (map_size / 2) * BOARD_X + BASE_X - 4;

    std::string end_info = "游戏结束";

    for (int i = 0; i < end_info.size(); i++) {
        c.get_instance()->write(end_info[i], utils::point<unsigned int>(start_x + i, start_y));
    }
}

int main() {
    utils::console console;
    game::game game;

    console.initialize();

    //游戏开始
    game_start(game, console);
    //游戏进行
    game_loop(game, console);
    //游戏结束
    game_end(game, console);

    return 0;
}