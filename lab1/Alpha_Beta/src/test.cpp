#include <fstream>
#include <cmath>
#include "node.h"
#include <iostream>

using namespace ChineseChess;

//博弈树搜索，depth为搜索深度
int cnt = 1;
int total_depth = 2;
int ans_id = 0;
int alphaBeta(GameTreeNode node, int alpha, int beta, int depth, bool isMaximizer) {
    printf("%d alpah: %d, beta: %d, depth: %d\n", cnt++, alpha, beta, depth);
    if (depth == 0) {
        int value = node.getEvaluationScore();
        // printf("EvaluationScore: %d\n", value);
        return value;
    }
    //TOD alpha-beta剪枝过程
    if (isMaximizer) {
        int value = -10000;
        for (int i = 0; i < (int)node.children.size(); i++) {
            GameTreeNode* child = node.children[i];
            int temp = alphaBeta(*child, alpha, beta, depth - 1, false);
            if(temp > value) {
                ans_id = i;
            }
            value = std::max(value, temp);
            alpha = std::max(alpha, value);
            if (alpha >= beta)
                break;
        }
        return value;
    }
    else {
        int value = 10000;
        for (int i = 0; i < (int)node.children.size(); i++) {
            GameTreeNode* child = node.children[i];
            value = std::min(value, alphaBeta(*child, alpha, beta, depth - 1, true));
            beta = std::min(beta, value);
            if (alpha >= beta)
                break;
        }
        return value;
    }
    return 0;
}

void run(int i) {
    std::ifstream file("../input/" + std::to_string(i) + ".txt");
    std::vector<std::vector<char>> board;

    std::string line;
    int n = 0;
    while (std::getline(file, line)) {
        // printf("ccc\n");
        std::vector<char> row;

        for (char ch : line) {
            row.push_back(ch);
        }

        board.push_back(row);
        n = n + 1;
        if (n >= 10) break;
    }

    file.close();
    
    GameTreeNode root(true, board, std::numeric_limits<int>::min(), total_depth);
    // printf("num children: %lld\n", root.children.size());
    
    //TOD
    // printf("alphaBeta\n");
    alphaBeta(root, -10000, 10000, total_depth, true);
    // printf("alphaBeta end\n");

    //代码测试
    ChessBoard _board = root.getBoardClass();
    std::vector<std::vector<char>> cur_board = _board.getBoard();

    // for (int i = 0; i < cur_board.size(); i++) {
    //     for (int j = 0; j < cur_board[0].size(); j++) {
    //         std::cout << cur_board[i][j];
    //     }
    //     std::cout << std::endl;
    // }
    std::vector<Move> red_moves = _board.getMoves(true);
    std::vector<Move> black_moves = _board.getMoves(false);

    // printf("red_moves: %d\n", red_moves.size());
    // for (int i = 0; i < red_moves.size(); i++) {
    //     std::cout << "init: " << red_moves[i].init_x <<  " " << red_moves[i].init_y << std::endl;
    //     std::cout << "next: " << red_moves[i].next_x <<  " " << red_moves[i].next_y << std::endl;
    //     std::cout << "score " << red_moves[i].score << std::endl;
    // }
    // printf("black_moves: %d\n", black_moves.size());
    // for (int i = 0; i < black_moves.size(); i++) {
    //     std::cout << "init: " << black_moves[i].init_x <<  " " << black_moves[i].init_y << std::endl;
    //     std::cout << "next: " << black_moves[i].next_x <<  " " << black_moves[i].next_y << std::endl;
    //     std::cout << "score " << black_moves[i].score << std::endl;
    // }
    
    printf("ans_id: %d\n", ans_id);
    std::ofstream output_file("../output/output_" + std::to_string(i) + ".txt");
    int initx = red_moves[ans_id].init_x;
    int inity = red_moves[ans_id].init_y;
    int nextx = red_moves[ans_id].next_x;
    int nexty = red_moves[ans_id].next_y;
    char chess = cur_board[initx][inity];
    output_file << chess << " (" << initx << "," << inity << ") (" << nextx << "," << nexty << ")";
    std::cout << chess << " (" << initx << "," << inity << ") (" << nextx << "," << nexty << ")" << std::endl;

    return ;
}
int main(){
    run(1);
    // for (int i = 1; i <= 10; i++) {
    //     run(i);
    // }
    return 0;
}