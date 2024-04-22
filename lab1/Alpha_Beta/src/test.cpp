#include <fstream>
#include <cmath>
#include "node.h"
#include <iostream>

using namespace ChineseChess;

//博弈树搜索，depth为搜索深度
int cnt = 1;
int total_depth = 5;
int ans_id = 0;
bool win = false;
bool lose = false;
int alphaBeta(GameTreeNode* node, int alpha, int beta, int depth, bool isMaximizer) {
    // printf("%d alpah: %d, beta: %d, depth: %d\n", cnt++, alpha, beta, depth);
    if (depth == 0) {
        int value = node->getEvaluationScore();
        // printf("EvaluationScore: %d\n", value);
        return value;
    }
    //TOD alpha-beta剪枝过程
    if (node -> children.size() == 0){
        std::vector<Move> moves = node->board.getMoves(isMaximizer);
        // printf("moves size: %d\n", moves.size());
        for (int i = 0; i < (int)moves.size(); i++) {
            GameTreeNode* child = node->updateBoard(node->board.board, moves[i], isMaximizer);
            if (child -> win){
                win = true;
                return 1000000;
            }
            if (child -> lose){
                lose = true;
                return -1000000;
            }
            node->children.push_back(child);
        }
    }
    if (isMaximizer) {
        int value = -1000000;
        int i = 0;
        for (GameTreeNode* child : node->children) {
            int temp = alphaBeta(child, alpha, beta, depth - 1, false);
            if(depth == total_depth) {
                printf("%d EvaluationScore: %d\n", i, temp);
                if(temp > value)
                    ans_id = i;
            }
            value = std::max(value, temp);
            alpha = std::max(alpha, value);
            i++;
            if (alpha >= beta)
                break;
        }
        return value;
    }
    else {
        int value = 1000000;
        for (GameTreeNode* child : node->children) {
            value = std::min(value, alphaBeta(child, alpha, beta, depth - 1, true));
            beta = std::min(beta, value);
            if (alpha >= beta)
                break;
        }
        return value;
    }
    return 0;
}

void test(GameTreeNode *node) {
    for (GameTreeNode* child : node->children) {
        if (child) test(child);
    }
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
    // printf("read file end\n");
    GameTreeNode root(true, board, std::numeric_limits<int>::min());
    // printf("GameTreeNode over\n");
    // printf("num children: %lld\n", root.children.size());
    // test(&root);
    // return ;
    //TOD
    // printf("start alphaBeta\n");
    alphaBeta(&root, -1000000, 1000000, total_depth, true);
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

    printf("\nred_moves: %ld\n", red_moves.size());
    for (int i = 0; i < red_moves.size(); i++) {
        int initx = red_moves[i].init_x;
        int inity = red_moves[i].init_y;
        int nextx = red_moves[i].next_x;
        int nexty = red_moves[i].next_y;
        char chess = cur_board[inity][initx];
        std::cout << chess << " (" << initx << "," << inity << ") (" << nextx << "," << nexty << ")" << std::endl;
    }
    printf("\n\n");
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
    char chess = cur_board[inity][initx];
    printf("total_depth: %d\n", total_depth);
    printf("win: %d\n", win);
    printf("lose: %d\n", lose);
    printf("test: %d\n",i);
    output_file << chess << " (" << initx << "," << 9 - inity << ") (" << nextx << "," << 9 - nexty << ")";
    std::cout << chess << " (" << initx << "," << 9 - inity << ") (" << nextx << "," << 9 - nexty << ")\n" << std::endl;


    return ;
}
int main(){
    // run(3); 
    // for (int i = 1; i <= 10; i++) {
    //     printf("run %d\n", i);
    //     if (i == 9)total_depth = 7;
    //     else if (i == 7)total_depth = 7;
    //     else total_depth = 5;
    //     run(i);
    //     win = false;
    // }

    for (int i = 1; i <= 10; i++) {
        printf("run %d\n", i);
        run(i);
        win = false;
        lose = false;
    }
    return 0;
}