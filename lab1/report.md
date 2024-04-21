# 人工智能Lab1实验报告

## PB21000164 来泽远

## Lab1.1

### 启发式函数

![image-20240421190221438](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20240421190221438.png)

使用曼哈顿距离。

一致性证明：

由于问题中只能走上下左右四个方向，所以两点之间的消耗满足：
$$
\begin{align}
& h(n) - h(n') \leq cost(n,a,n') \\
& h(n)  \leq cost(n,a,n') + h(n')
\end{align}
$$
其中$n'$为$n$的后继节点，a为任意行动，即满足一致性条件。

又由一致性强于可采纳性，进而该启发式函数也是可采纳的。

### 算法简述

```c++
int a[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while(!open_list.empty())
    {
        // TODO: A*搜索过程实现
        bool end = false;
        Search_Cell *current = open_list.top();
        open_list.pop();
        close_list.push_back(current);
        int i = current->x;
        int j = current->y;
        int type = Map[i][j].type;
        if (current -> fd == 0 || (current->g > Map[i][j].g && current->fd < Map[i][j].fd))
            continue;
        
        for (int k = 0; k < 4; k++)
        {
            int x = i + a[k][0];
            int y = j + a[k][1];
            if(x >= 0 && x < M && y >= 0 && y < N && Map[x][y].type != 1) {
                Search_Cell *temp = new Search_Cell;
                temp->g = current->g + 1;
                temp->h = Heuristic_Funtion(i, j, end_point.first, end_point.second);
                if (Map[x][y].type == 2)
                    temp->fd = T;
                else
                    temp->fd = current->fd - 1;
                temp->parent = current;
                temp->x = x;
                temp->y = y;
                if (temp->g >= Map[x][y].g && temp->fd <= Map[x][y].fd)
                    continue;
            
                if (temp->g < Map[x][y].g) {
                    Map[x][y].g = temp->g;
                    Map[x][y].fd = temp->fd;
                }
                open_list.push(temp);
            }
            if (x == end_point.first && y == end_point.second){
                printf("find end\n");
                step_nums = current->g + 1;
                Search_Cell *temp = current;
                while(temp->parent != nullptr) {
                    if (temp->x == temp->parent->x + 1)
                        way = "D" + way;
                    else if (temp->x == temp->parent->x - 1)
                        way = "U" + way;
                    else if (temp->y == temp->parent->y + 1)
                        way = "R" + way;
                    else if (temp->y == temp->parent->y - 1)
                        way = "L" + way;
                    temp = temp->parent;          
                }
                end = true;
                break;
            }
           
        }
        if (end)
            break;
    }
```

算法的整体框架为广搜，我们将历史最优记录在$Map[i][j]$中，包含g和剩余食物。当当前剩余食物为零，或者当前状态必定劣于历史最优时（g更大且食物更少），我们跳过本次搜索。如满足，则继续搜索上下左右四个方向，并且实现关于补给站和山脉的逻辑。如果g更优，我们更新$Map[i][j]$中的历史最优。如果搜索到终点则算法停止，且广搜的性质满足第一个搜到的必定是最短的路线。

### 性能分析

![image-20240421192004521](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20240421192004521.png)

![image-20240421192024251](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20240421192024251.png)

前后分别为启发式函数设为曼哈顿距离和设为0的情况。衡量性能的指标为搜索过程中while循环的执行次数，可以看到明显的性能差距。

曼哈顿函数提供了当前位置到终点的最短路估计代价，则更有可能朝着距离终点更近的节点拓展，而非将周围的节点视作等价进行拓展。进而，可以减少搜索空间，使得算法性能提升。

## Lab1.2

### 算法实现

```c++
...
printf("read file end\n");
GameTreeNode root(true, board, std::numeric_limits<int>::min(), total_depth);
printf("GameTreeNode over\n");
printf("start alphaBeta\n");
alphaBeta(&root, -1000000, 1000000, total_depth, true);
...
```

首先基于给定的深度进行游戏状态空间的穷举。

```c++
GameTreeNode(bool color, std::vector<std::vector<char>> initBoard, int evaluationScore, int depth)
            : color(color), evaluationScore(evaluationScore) {
            board.initializeBoard(initBoard);
            std::vector<Move> moves = board.getMoves(color);
            children.clear();
            std::vector<std::vector<char>> cur_board = board.getBoard();

            // 为合法动作创建子节点
            if (depth > 0){
                for (int i = 0; i < (int)moves.size(); i++) {
                    GameTreeNode* child = updateBoard(cur_board, moves[i], color, depth - 1);
                    children.push_back(child);
                }
            }
        }
```

具体则是对于当前棋盘上的所有棋子进行遍历，生成所有棋子的动作方案，再依据当前回合返回所有红色方的方案或者黑色方的方案。然后根据当前状态和棋子移动方案生成若干个子节点，并且对其递归生成。

其次进行剪枝。

```c++
int alphaBeta(GameTreeNode* node, int alpha, int beta, int depth, bool isMaximizer) {
    if (depth == 0) {
        int value = node->getEvaluationScore();
        return value;
    }
    //TODO alpha-beta剪枝过程
    if (isMaximizer) {
        int value = -1000000;
        int i = 0;
        for (GameTreeNode* child : node->children) {
            int temp = alphaBeta(child, alpha, beta, depth - 1, false);
            if(depth == total_depth) {
                printf("%d EvaluationScore: %d\n", i+1, temp);
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
```

alpha-beta剪枝根据当前的回合，红色则挑选最大值，黑色则挑选最小值，并且同时更新区间，即alpha和beta。棋局的value由类中的评估函数给出。在初始层（即红色方的第一步棋），我们记录分数最大的孩子的下标，随后将对应动作输出到文件中。

具体结果如下表。

| test | otuput        |
| ---- | ------------- |
| 1    | R (1,1) (4,1) |
| 2    | R (3,5) (3,0) |
| 3    | P (5,3) (4,3) |
| 4    | R (3,1) (3,4) |
| 5    | C (4,3) (0,3) |
| 6    | R (4,0) (4,8) |
| 7    | B (6,9) (4,7) |
| 8    | R (4,2) (6,2) |
| 9    | N (6,7) (4,6) |
| 10   | C (6,4) (4,4) |

### 评估函数

棋局的分数构成主要分为两部分：基于当前状态的评分以及是由哪一个动作拓展至此的评分（击杀评分）。而前者又分为两部分，棋子的存活评分以及位置评分（对对方的威胁）。

```c++
int getEvaluationScore() {
	evaluationScore = board.evaluateNode();
	return evaluationScore + eat_value;
}
```
该函数计算了基于当前状态的评分，存活评分通过`piece_values`获取，位置评分通过`xxPosition`获取。


```c++
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
                            red_score += piece_values["Ju"];
                            red_score += JuPosition[j][9 - i];
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
            return red_score - black_score;
        }
```

击杀评分是在`updateBoard`函数中，随着棋局的更新同步更新，保存至类成员`eat_value`中。

```c++
	GameTreeNode* updateBoard(std::vector<std::vector<char>> cur_board, Move move, bool color, int depth) {
           	//TODO
            GameTreeNode* test;

            char cur_chess = cur_board[move.init_y][move.init_x];
            char goal_chess = cur_board[move.next_y][move.next_x];
            cur_board[move.init_y][move.init_x] = '.';
            cur_board[move.next_y][move.next_x] = cur_chess;

            test = new GameTreeNode(!color, cur_board, 0, depth);
            test->color = !color;
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
            return test;
        }
```

关于评估函数的具体效果难以量化，主要的优化方式为将输出与人脑认为的较优解进行对比。同时涉及到内存限制，搜索也只能搜4、5层，所以会对不同的棋局表现差异较大。比如前几个测试用例中，一两步就能将死的棋局中表现还不错，后几个较为复杂的测试用例难以评估其效果，不过与人脑的直觉还是相对吻合的。

### alpha-beta剪枝效果

对于test1，在depth = 4的情况下：

![image-20240421200018931](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20240421200018931.png)

alpha-beta剪枝仅遍历了2.5w个节点，而总节点约为209w，为前者的83.6倍

depth = 3：

![image-20240421200312037](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20240421200312037.png)

约为21倍。

depth = 2：

![image-20240421200400376](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20240421200400376.png)

约为1.26倍。

发现随着depth的增加，剪枝效果在变好，这也是合理的。在树越大的情况下，剪枝更容易剪掉数量巨大的一簇节点，比如同样在第二层剪枝，depth = 2的收益远比depth = 4小。

对于其余几个test也有很大的加速效果，以及同样的规律，在此不展开。
