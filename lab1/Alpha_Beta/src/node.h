#include <vector>
#include <map>
#include <limits>
#include <iostream>
#include <string>

namespace ChineseChess
{
    //棋力评估，这里的棋盘方向和输入棋盘方向不同，在使用时需要仔细
    //生成合法动作代码部分已经使用，经过测试是正确的，大家可以参考
    std::vector<std::vector<int>> JiangPosition = {
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {5, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            };

    std::vector<std::vector<int>> ShiPosition = {
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            };
        
    std::vector<std::vector<int>> XiangPosition = {
                                                {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
                                            };

    std::vector<std::vector<int>> MaPosition = {
                                                {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
                                                {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
                                                {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
                                                {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
                                                {2, -10, 4, 10, 15, 16, 12, 11, 6, 2},
                                                {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
                                                {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
                                                {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
                                                {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
                                            };

    std::vector<std::vector<int>> PaoPosition = {
                                                {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
                                                {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
                                                {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
                                                {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
                                                {3, 2, 5, 0, 4, 4, 4, -4, -7, -6},
                                                {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
                                                {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
                                                {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
                                                {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
                                            };

    std::vector<std::vector<int>> JuPosition = {
                                                {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
                                                {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
                                                {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
                                                {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
                                                {0, 0, 12, 14, 15, 15, 16, 16, 33, 14},
                                                {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
                                                {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
                                                {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
                                                {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
                                            };

    std::vector<std::vector<int>> BingPosition = {
                                                {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
                                                {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
                                                {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
                                                {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
                                                {0, 0, 0, 6, 7, 40, 42, 55, 70, 4},
                                                {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
                                                {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
                                                {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
                                                {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
                                            };

    //棋子价值评估
    std::map<std::string, int> piece_values = {
                                            {"Jiang", 10000},
                                            {"Shi", 10},
                                            {"Xiang", 3},
                                            {"Ma", 300},
                                            {"Ju", 500},
                                            {"Pao", 300},
                                            {"Bing", 90}
                                        };

    //行期可能性评估，这里更多是对下一步动作的评估
    std::map<std::string, int> next_move_values = {
                                            {"Jiang", 20000},
                                            {"Ma", 200},
                                            {"Ju", 600},
                                            {"Pao", 200},
                                            {"Xiang", 30},
                                            {"Shi", 0},
                                            {"Bing", 0}
                                        };
    
    //动作结构体，每个动作设置score，可以方便剪枝
    struct Move {
        int init_x;
        int init_y;
        int next_x;
        int next_y;
        int score;
    };

    // 定义棋盘上的棋子结构体
    struct ChessPiece {
        char name; // 棋子名称
        int init_x, init_y; // 棋子的坐标
        bool color;   //棋子阵营 true为红色、false为黑色
    };

    // 定义棋盘类
    class ChessBoard {
    public:
        int sizeX, sizeY;   //棋盘大小，固定
        std::vector<ChessPiece> pieces;   //棋盘上所有棋子
        std::vector<std::vector<char>> board;    //当前棋盘、二维数组表示
        std::vector<Move> red_moves;    //红方棋子的合法动作
        std::vector<Move> black_moves;   //黑方棋子的合法动作
    public:
        // 初始化棋盘，提取棋盘上棋子，并生成所有合法动作
        void initializeBoard(const std::vector<std::vector<char>>& init_board) {
            board = init_board;
            sizeX = board.size();
            sizeY = board[0].size();

            for (int i = 0; i < sizeX; ++i) {
                for (int j = 0; j < sizeY; ++j) {
                    char pieceChar = board[i][j];
                    // printf("pieceChar: %c i:%d j:%d \n", pieceChar, i, j);
                    if (pieceChar == '.') continue;

                    ChessPiece piece;
                    piece.init_x = j;
                    piece.init_y = i;
                    piece.color = (pieceChar >= 'A' && pieceChar <= 'Z');
                    piece.name = pieceChar;
                    pieces.push_back(piece);

                    int origin_moves, moves;
                    switch (pieceChar) {
                        case 'R':
                            origin_moves = red_moves.size();
                            generateJuMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Ju moves: %d\n", moves - origin_moves);
                            break;
                        case 'C':
                            origin_moves = red_moves.size();
                            generatePaoMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Pao moves: %d\n", moves - origin_moves);
                            break;
                        case 'N':
                            origin_moves = red_moves.size();
                            generateMaMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Ma moves: %d\n", moves - origin_moves);
                            break;
                        case 'B':
                            origin_moves = red_moves.size();
                            generateXiangMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Xiang moves: %d\n", moves - origin_moves);
                            break;
                        case 'A':
                            origin_moves = red_moves.size();
                            generateShiMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Shi moves: %d\n", moves - origin_moves);
                            break;
                        case 'K':
                            origin_moves = red_moves.size();
                            generateJiangMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Jiang moves: %d\n", moves - origin_moves);
                            break;
                        case 'P':
                            origin_moves = red_moves.size();
                            generateBingMoves(j, i, piece.color);
                            moves = red_moves.size();
                            // printf("Bing moves: %d\n", moves - origin_moves);
                            break;
                        case 'r':
                            generateJuMoves(j, i, piece.color);
                            break;
                        case 'c':
                            generatePaoMoves(j, i, piece.color);
                            break;
                        case 'n':
                            generateMaMoves(j, i, piece.color);
                            break;
                        case 'b':
                            generateXiangMoves(j, i, piece.color);
                            break;
                        case 'a':
                            generateShiMoves(j, i, piece.color);
                            break;
                        case 'k':
                            generateJiangMoves(j, i, piece.color);
                            break;
                        case 'p':
                            generateBingMoves(j, i, piece.color);
                            break;
                        default:
                            break;
                    }
                } 
            }
        }
        bool check_out(int x, int y){
            if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) return true;
            return false;
        }
        
        //生成车的合法动作
        void generateJuMoves(int x, int y, bool color) {
            //前后左右分别进行搜索，遇到棋子停止，不同阵营可以吃掉
            std::vector<Move> JuMoves;
            for(int i = x + 1; i < sizeY; i++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if (board[y][i] != '.') {
                    bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int i = x - 1; i >= 0; i--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if (board[y][i] != '.') {
                    bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int j = y + 1; j < sizeX; j++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                if (board[j][x] != '.') {
                    bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int j = y - 1; j >= 0; j--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                if (board[j][x] != '.') {
                    bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move); 
            }
            for (int i = 0; i < (int)JuMoves.size(); i++) {
                if(color) {
                    JuMoves[i].score = JuPosition[JuMoves[i].next_x][9 - JuMoves[i].next_y] - JuPosition[x][9 -y];
                    red_moves.push_back(JuMoves[i]);
                }
                else {
                    JuMoves[i].score = JuPosition[JuMoves[i].next_x][JuMoves[i].next_y] - JuPosition[x][y];
                    black_moves.push_back(JuMoves[i]);
                }
            }
        }

        //生成马的合法动作
        void generateMaMoves(int x, int y, bool color) {
            //便利所有可能动作，筛选
            std::vector<Move> MaMoves;
            int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
            int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
            int bx[] = {1, 0, 0, -1, -1, 0, 0, 1};
            int by[] = {0, 1, 1, 0, 0, -1, -1, 0};
            //简化，不考虑拌马脚
            //TOD 可以实现拌马脚过程
            for(int i = 0; i < 8; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (check_out(ny, nx)) continue;
                int bmjx = x + bx[i];   // 马脚坐标
                int bmjy = y + by[i];
                if (!check_out(bmjy, bmjx) && board[bmjy][bmjx] != '.') continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    //注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        MaMoves.push_back(cur_move);
                    }
                    continue;
                }
                MaMoves.push_back(cur_move);
            }
            for (int i = 0; i < (int)MaMoves.size(); i++) {
                if(color) {
                    MaMoves[i].score = MaPosition[MaMoves[i].next_x][9 - MaMoves[i].next_y] - MaPosition[x][9 - y];
                    red_moves.push_back(MaMoves[i]);
                }
                else {
                    MaMoves[i].score = MaPosition[MaMoves[i].next_x][MaMoves[i].next_y] - MaPosition[x][y];
                    black_moves.push_back(MaMoves[i]);
                }
            }
        }

        //生成炮的合法动作
        void generatePaoMoves(int x, int y, bool color) {
            //和车生成动作相似，需要考虑炮翻山吃子的情况
            std::vector<Move> PaoMoves;
            //TOD
            bool fanyue = false;
            for(int i = x + 1; i < sizeY; i++) {
                Move cur_move;
                if (!fanyue) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = i;
                    cur_move.next_y = y;
                    cur_move.score = 0;
                    if (board[y][i] != '.') {
                        fanyue = true;
                        continue;
                    }
                    PaoMoves.push_back(cur_move);
                }
                else {
                    if (board[y][i] == '.') {
                        continue;
                    }
                    else {
                        bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                        if (cur_color != color) {
                            cur_move.init_x = x;
                            cur_move.init_y = y;
                            cur_move.next_x = i;
                            cur_move.next_y = y;
                            cur_move.score = 0;
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
            }
            fanyue = false;

            for(int i = x - 1; i >= 0; i--) {
                Move cur_move;
                if (!fanyue) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = i;
                    cur_move.next_y = y;
                    cur_move.score = 0;
                    if (board[y][i] != '.') {
                        fanyue = true;
                        continue;
                    }
                    PaoMoves.push_back(cur_move);
                }
                else {
                    if (board[y][i] == '.') {
                        continue;
                    }
                    else {
                        bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                        if (cur_color != color) {
                            cur_move.init_x = x;
                            cur_move.init_y = y;
                            cur_move.next_x = i;
                            cur_move.next_y = y;
                            cur_move.score = 0;
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
            }
            fanyue = false;

            for(int j = y + 1; j < sizeX; j++) {
                Move cur_move;
                if (!fanyue) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = x;
                    cur_move.next_y = j;
                    cur_move.score = 0;
                    if (board[j][x] != '.') {
                        fanyue = true;
                        continue;
                    }
                    PaoMoves.push_back(cur_move);
                }
                else {
                    if (board[j][x] == '.') {
                        continue;
                    }
                    else {
                        bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                        if (cur_color != color) {
                            cur_move.init_x = x;
                            cur_move.init_y = y;
                            cur_move.next_x = x;
                            cur_move.next_y = j;
                            cur_move.score = 0;
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
            }
            fanyue = false;

            for(int j = y - 1; j >= 0; j--) {
                Move cur_move;
                if (!fanyue) {
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = x;
                    cur_move.next_y = j;
                    cur_move.score = 0;
                    if (board[j][x] != '.') {
                        fanyue = true;
                        continue;
                    }
                    PaoMoves.push_back(cur_move);
                }
                else {
                    if (board[j][x] == '.') {
                        continue;
                    }
                    else {
                        bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                        if (cur_color != color) {
                            cur_move.init_x = x;
                            cur_move.init_y = y;
                            cur_move.next_x = x;
                            cur_move.next_y = j;
                            cur_move.score = 0;
                            PaoMoves.push_back(cur_move);
                        }
                        break;
                    }
                }
            }
            fanyue = false;

            for (int i = 0; i < (int)PaoMoves.size(); i++) {
                if(color) {
                    PaoMoves[i].score = PaoPosition[PaoMoves[i].next_x][9 - PaoMoves[i].next_y] - PaoPosition[x][9 -y];
                    red_moves.push_back(PaoMoves[i]);
                }
                else {
                    PaoMoves[i].score = PaoPosition[PaoMoves[i].next_x][PaoMoves[i].next_y] - PaoPosition[x][y];
                    black_moves.push_back(PaoMoves[i]);
                }
            }
        }

        //生成相的合法动作
        void generateXiangMoves(int x, int y, bool color) {
            std::vector<Move> XiangMoves;
            //TOD
            // printf("            xiang pos %d %d\n", x, y);
            int dx[] = {2, 2, -2, -2};
            int dy[] = {2, -2, 2, -2};
            int bx[] = {1, 1, -1, -1};
            int by[] = {1, -1, 1, -1};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                // 象不能过河
                if (color == true && ny <= 4) continue;
                if (color == false && ny >= 5) continue;
                if (check_out(ny, nx)) continue;
                int bxjx = x + bx[i];
                int bxjy = y + by[i];
                if (!check_out(bxjy, bxjx) && board[bxjy][bxjx] != '.') continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        XiangMoves.push_back(cur_move);
                    }
                    continue;
                }
                XiangMoves.push_back(cur_move);
            }

            for (int i = 0; i < (int)XiangMoves.size(); i++) {
                if(color) {
                    XiangMoves[i].score = XiangPosition[XiangMoves[i].next_x][9 - XiangMoves[i].next_y] - XiangPosition[x][9 -y];
                    red_moves.push_back(XiangMoves[i]);
                }
                else {
                    XiangMoves[i].score = XiangPosition[XiangMoves[i].next_x][XiangMoves[i].next_y] - XiangPosition[x][y];
                    black_moves.push_back(XiangMoves[i]);
                }
            }
        }

        //生成士的合法动作
        void generateShiMoves(int x, int y, bool color) {
            std::vector<Move> ShiMoves;
            //TOD
            int dx[] = {1, 1, -1, -1};
            int dy[] = {1, -1, 1, -1};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (color == true && (nx < 3 || nx >= 6 || ny < 7 || ny >= 10)) continue;
                if (color == false && (nx < 3 || nx >= 6 || ny < 0 || ny >= 3)) continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        ShiMoves.push_back(cur_move);
                    }
                    continue;
                }
                ShiMoves.push_back(cur_move);
            }


            for (int i = 0; i < (int)ShiMoves.size(); i++) {
                if(color) {
                    ShiMoves[i].score = ShiPosition[ShiMoves[i].next_x][9 - ShiMoves[i].next_y] - ShiPosition[x][9 -y];
                    red_moves.push_back(ShiMoves[i]);
                }
                else {
                    ShiMoves[i].score = ShiPosition[ShiMoves[i].next_x][ShiMoves[i].next_y] - ShiPosition[x][y];
                    black_moves.push_back(ShiMoves[i]);
                }
            }
        }

        //生成将的合法动作
        void generateJiangMoves(int x, int y, bool color) {
            std::vector<Move> JiangMoves;
            //TOD
            int dx[] = {1, 0, -1, 0};
            int dy[] = {0, 1, 0, -1};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (color == true && (nx < 3 || nx >= 6 || ny < 7 || ny >= 10)) continue;
                if (color == false && (nx < 3 || nx >= 6 || ny < 0 || ny >= 3)) continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        JiangMoves.push_back(cur_move);
                    }
                    continue;
                }
                JiangMoves.push_back(cur_move);
            }

            for (int i = 0; i < (int)JiangMoves.size(); i++) {
                if(color) {
                    JiangMoves[i].score = JiangPosition[JiangMoves[i].next_x][9 - JiangMoves[i].next_y] - JiangPosition[x][9 -y];
                    red_moves.push_back(JiangMoves[i]);
                }
                else {
                    JiangMoves[i].score = JiangPosition[JiangMoves[i].next_x][JiangMoves[i].next_y] - JiangPosition[x][y];
                    black_moves.push_back(JiangMoves[i]);
                }
            }
        }

        //生成兵的合法动作
        void generateBingMoves(int x, int y, bool color) {
            //需要分条件考虑，小兵在过楚河汉界之前只能前进，之后可以左右前
            if (x == 4 && y == 8 && color == false) {
                if (board[9][4] == 'K')
                    // printf("????  %d %d %c \n",x,y,board[9][4]);
                    1;
            }
            std::vector<Move> BingMoves;
            Move cur_move;
            //TOD
            // printf("            bing x: %d, y: %d\n", x, y);
            if (color == true){
                if (y >= 5){ // 没过河
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = x;
                    cur_move.next_y = y - 1;
                    cur_move.score = 0;
                    if (board[y - 1][x] == '.' || board[y - 1][x] >= 'a' && board[y - 1][x] <= 'z')
                        BingMoves.push_back(cur_move);
                }
                else {
                    if (y - 1 >= 0){
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = x;
                        cur_move.next_y = y - 1;
                        cur_move.score = 0;
                        if (board[y - 1][x] == '.' || board[y - 1][x] >= 'a' && board[y - 1][x] <= 'z')
                            BingMoves.push_back(cur_move);
                    }
                    if (x - 1 >= 0) {
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = x - 1;
                        cur_move.next_y = y;
                        cur_move.score = 0;
                        if (board[y][x - 1] == '.' || board[y][x - 1] >= 'a' && board[y][x - 1] <= 'z')
                            BingMoves.push_back(cur_move);
                    }
                    if (x + 1 < sizeY) {
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = x + 1;
                        cur_move.next_y = y;
                        cur_move.score = 0;
                        if (board[y][x + 1] == '.' || board[y][x + 1] >= 'a' && board[y][x + 1] <= 'z')
                            BingMoves.push_back(cur_move);
                    }
                }
            }
            else {
                if (y <= 4){ // 没过河
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = x;
                    cur_move.next_y = y + 1;
                    cur_move.score = 0;
                    if (board[y + 1][x] == '.' || board[y + 1][x] >= 'A' && board[y + 1][x] <= 'Z')
                        BingMoves.push_back(cur_move);
                }
                else {
                    if(y + 1 < sizeX){
                        if (board[x][y + 1] == 'K')
                            printf("123123 %d %d %d\n", x,y,board[x][y + 1]);
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = x;
                        cur_move.next_y = y + 1;
                        cur_move.score = 0;
                        if (board[y + 1][x] == '.' || board[y + 1][x] >= 'A' && board[y + 1][x] <= 'Z')
                            BingMoves.push_back(cur_move);
                    }
                    if (x - 1 >= 0) {
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = x - 1;
                        cur_move.next_y = y;
                        cur_move.score = 0;
                        if (board[y][x - 1] == '.' || board[y][x - 1] >= 'A' && board[y][x - 1] <= 'Z')
                            BingMoves.push_back(cur_move);
                    }
                    if (x + 1 < sizeY) {
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = x + 1;
                        cur_move.next_y = y;
                        cur_move.score = 0;
                        if (board[y][x + 1] == '.' || board[y][x + 1] >= 'A' && board[y][x + 1] <= 'Z')
                            BingMoves.push_back(cur_move);
                    }
                }
            }


            for (int i = 0; i < (int)BingMoves.size(); i++) {
                if(color) {
                    BingMoves[i].score = BingPosition[BingMoves[i].next_x][9 - BingMoves[i].next_y] - BingPosition[x][9 -y];
                    red_moves.push_back(BingMoves[i]);
                }
                else {
                    BingMoves[i].score = BingPosition[BingMoves[i].next_x][BingMoves[i].next_y] - BingPosition[x][y];
                    black_moves.push_back(BingMoves[i]);
                }
            }
        }
    
        //终止判断
        bool judgeTermination() {
            //TOD
            // 判断黑色king是否存活
            bool black_king = false;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 9; j++) {
                    if (board[i][j] == 'k') {
                        black_king = true;
                        break;
                    }
                }
            }
            return black_king;
        }

        //棋盘分数评估，根据当前棋盘进行棋子价值和棋力评估，max玩家减去min玩家分数
        int evaluateNode() {
            //TOD
            int red_score = 0;
            int black_score = 0;
            for (int i = 0; i < 10 ; i++) {
                for (int j = 0; j < 9; j++) {
                    if (board[i][j] == '.') continue;
                    char pieceChar = board[i][j];
                    switch (pieceChar) {
                        case 'R':
                            // printf("                R i: %d, j: %d\n", i, j);
                            red_score += piece_values["Ju"];
                            red_score += JuPosition[j][9 - i];
                            // printf("Ju: %d\n", JuPosition[j][9 - i]);
                            break;
                        case 'C':
                            red_score += piece_values["Pao"];
                            red_score += PaoPosition[j][9 - i];
                            break;
                        case 'N':
                            red_score += piece_values["Ma"];
                            red_score += MaPosition[j][9 - i];
                            break;
                        case 'B':
                            red_score += piece_values["Xiang"];
                            red_score += XiangPosition[j][9 - i];
                            break;      
                        case 'A':
                            red_score += piece_values["Shi"];
                            red_score += ShiPosition[j][9 - i];
                            break;
                        case 'K':
                            red_score += piece_values["Jiang"];
                            red_score += JiangPosition[j][9 - i];
                            break;
                        case 'P':
                            red_score += piece_values["Bing"];
                            red_score += BingPosition[j][9 - i];
                            break;
                        case 'r':
                            black_score += piece_values["Ju"];
                            black_score += JuPosition[j][i];
                            break;
                        case 'c':
                            black_score += piece_values["Pao"];
                            black_score += PaoPosition[j][i];
                            break;
                        case 'n':
                            black_score += piece_values["Ma"];
                            black_score += MaPosition[j][i];
                            break;
                        case 'b':
                            black_score += piece_values["Xiang"];
                            black_score += XiangPosition[j][i];
                            break;
                        case 'a':
                            black_score += piece_values["Shi"];
                            black_score += ShiPosition[j][i];
                            break;
                        case 'k':
                            black_score += piece_values["Jiang"];
                            black_score += JiangPosition[j][i];
                            break;
                        case 'p':
                            black_score += piece_values["Bing"];
                            black_score += BingPosition[j][i];
                            break;
                        default:
                            break;
                    }
                }
            }
            // printf("Red: %d, Black: %d\n", red_score, black_score);
            return red_score - black_score;
        }

        //测试接口
        std::vector<Move> getMoves(bool color) {
            if(color) return red_moves;
            return black_moves;
        }
    
        std::vector<ChessPiece> getChessPiece() {
            return pieces;
        }
    
        std::vector<std::vector<char>> getBoard() {
            return board;
        }
    };

    // 定义博弈树节点类
    class GameTreeNode {
    public:
        bool color; // 当前玩家类型，true为红色方、false为黑色方
        ChessBoard board; // 当前棋盘状态
        std::vector<GameTreeNode*> children; // 子节点列表
        int evaluationScore; // 棋盘评估分数
        int eat_value; // 吃子分数
        bool win;
        bool lose;

    public:
        // 构造函数
        GameTreeNode(bool color, std::vector<std::vector<char>> initBoard, int evaluationScore)
            : color(color), evaluationScore(evaluationScore) {
            // printf("aaaaa\n");
            board.initializeBoard(initBoard);
            // printf("bbbbb\n");
            std::vector<Move> moves = board.getMoves(color);
            // printf("cccccc\n");
            children.clear();
            // printf("ddddddd\n");
            // std::vector<std::vector<char>> cur_board = board.getBoard();
            win = false;
            lose = false;

            // 为合法动作创建子节点
            // printf("GameTreeNode  depth: %d\n", depth);
            // if (depth > 0){
            //     for (int i = 0; i < (int)moves.size(); i++) {
            //         GameTreeNode* child = updateBoard(cur_board, moves[i], color, depth - 1);
            //         children.push_back(child);
            //     }
            // }
        }

        //根据当前棋盘和动作构建新棋盘（子节点）
        GameTreeNode* updateBoard(std::vector<std::vector<char>> cur_board, Move move, bool color) {
            //TOD
            // printf("updateBoard\n");
            GameTreeNode* test;

            char cur_chess = cur_board[move.init_y][move.init_x];
            char goal_chess = cur_board[move.next_y][move.next_x];
            cur_board[move.init_y][move.init_x] = '.';
            cur_board[move.next_y][move.next_x] = cur_chess;

            test = new GameTreeNode(color, cur_board, 0);
            if (goal_chess == 'k') {
                test->win = true;
            }
            if (goal_chess == 'K') {
                test->lose = true;
            }
            test->color = color;
            switch (goal_chess)
            {
            case 'R':
                test->eat_value = -next_move_values["Ju"];
                break;
            case 'C':
                test->eat_value = -next_move_values["Pao"];
                break;
            case 'N':
                test->eat_value = -next_move_values["Ma"];
                break;
            case 'B':
                test->eat_value = -next_move_values["Xiang"];
                break;
            case 'A':
                test->eat_value = -next_move_values["Shi"];
                break;
            case 'K':
                test->eat_value = -next_move_values["Jiang"];
                break;
            case 'P':
                test->eat_value = -next_move_values["Bing"];
                break;
            case 'r':
                test->eat_value = next_move_values["Ju"];
                break;
            case 'c':
                test->eat_value = next_move_values["Pao"];
                break;
            case 'n':
                test->eat_value = next_move_values["Ma"];
                break;
            case 'b':
                test->eat_value = next_move_values["Xiang"];
                break;
            case 'a':
                test->eat_value = next_move_values["Shi"];
                break;
            case 'k':
                test->eat_value = next_move_values["Jiang"];
                break;
            case 'p':
                test->eat_value = next_move_values["Bing"];
                break;
            default:
                test->eat_value = 0;
                break;
            }
            // test->board.initializeBoard(cur_board);
            // test->evaluationScore = test->getEvaluationScore();
            
            return test;
        }

        //返回节点评估分数
        int getEvaluationScore() {
            // return 0;
            evaluationScore = board.evaluateNode();
            return evaluationScore + eat_value;
        }

        //返回棋盘类
        ChessBoard getBoardClass() {
            return board;
        }
        
        ~GameTreeNode() {
            for (GameTreeNode* child : children) {
                if(child != nullptr)delete child;
            }
        }

    };
    
}
