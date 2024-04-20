#include<vector>
#include<iostream>
#include<queue>
#include<map>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

struct Map_Cell
{
    int type;
    int g;
    int fd;
    // TODO: 定义地图信息
    // bool visited = false;
    // 2:补给点 补给T次

};

struct Search_Cell
{
    int h;
    int g;
    int x;
    int y;
    int fd;
    Search_Cell *parent;
    // TODO: 定义搜索状态

};

// 自定义比较函数对象，按照 Search_Cell 结构体的 g + h 属性进行比较
struct CompareF {
    bool operator()(const Search_Cell *a, const Search_Cell *b) const {
        return (a->g + a->h) > (b->g + b->h); // 较小的 g + h 值优先级更高
    }
};

// TODO: 定义启发式函数
int Heuristic_Funtion(int i, int j, int end_i, int end_j)
{
    return abs(i - end_i) + abs(j - end_j);
}

void Astar_search(const string input_file, int &step_nums, string &way)
{
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    getline(file, line); // 读取第一行
    stringstream ss(line);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    int M = stoi(words[0]);
    int N = stoi(words[1]);
    int T = stoi(words[2]);
    printf("M = %d, N = %d, T = %d\n", M, N, T);

    pair<int, int> start_point; // 起点
    pair<int, int> end_point;   // 终点
    Map_Cell **Map = new Map_Cell *[M];
    // 加载地图
    for(int i = 0; i < M; i++)
    {
        Map[i] = new Map_Cell[N];
        getline(file, line);
        stringstream ss(line);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        for(int j = 0; j < N; j++)
        {
            // printf("i = %d, j = %d\n", i, j);
            Map[i][j].type = stoi(words[j]);
            Map[i][j].g = 9999; //初值
            Map[i][j].fd = 0;
            if(Map[i][j].type == 3)
            {
                start_point = {i, j};
            }
            else if(Map[i][j].type == 4)
            {
                end_point = {i, j};
            }
        }
    }
    // 以上为预处理部分
    // ------------------------------------------------------------------

    int i = start_point.first;
    int j = start_point.second;

    Search_Cell *search_cell = new Search_Cell;
    search_cell->g = 0;
    search_cell->h = 0; // Heuristic_Funtion();
    search_cell->fd = T;
    search_cell->parent = nullptr;
    search_cell->x = i;
    search_cell->y = j;

    priority_queue<Search_Cell *, vector<Search_Cell *>, CompareF> open_list;
    vector<Search_Cell *> close_list;
    Map[i][j].g = 0;
    Map[i][j].fd = T;
    open_list.push(search_cell);

    int cnt = 0;

    
    int a[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    printf("start A* search\n");
    while(!open_list.empty())
    {
        // TODO: A*搜索过程实现 广搜
        bool end = false;
        Search_Cell *current = open_list.top();
        open_list.pop();
        close_list.push_back(current);
        int i = current->x;
        int j = current->y;
        int type = Map[i][j].type;
        // printf("i = %d, j = %d, type = %d, food_left = %d, g = %d\n", i, j, type, current->fd, current->g);
        if (current -> fd == 0 || (current->g > Map[i][j].g && current->fd < Map[i][j].fd))
            continue;
        
        for (int k = 0; k < 4; k++)
        {
            int x = i + a[k][0];
            int y = j + a[k][1];
            if(x >= 0 && x < M && y >= 0 && y < N && Map[x][y].type != 1) {
                // if ((i == 5 || i == 6) && j == 2) printf("try x = %d, y = %d\n", x, y);
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
                // // 判断是否在close_list
                // bool in_close = false;
                // for (int i = 0; i < close_list.size(); i++) {
                //     if (close_list[i]->x == x && close_list[i]->y == y) {
                //         in_close = true;
                //         break;
                //     }
                // }
                // if (in_close)
                //     continue;
                if (temp->g >= Map[x][y].g && temp->fd <= Map[x][y].fd)
                    continue;
            
                
                if (temp->g < Map[x][y].g) {
                    Map[x][y].g = temp->g;
                    Map[x][y].fd = temp->fd;
                }
                open_list.push(temp);
                // if ((i == 5 || i == 6) && j == 2) printf("push x = %d, y = %d, g = %d\n", x, y, temp->g);
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

    // ------------------------------------------------------------------
    // TODO: 填充step_nums与way
    // step_nums = -1;
    // way = "";
    

    // ------------------------------------------------------------------
    // 释放动态内存
    for(int i = 0; i < M; i++)
    {
        delete[] Map[i];
    }
    delete[] Map;
    while(!open_list.empty())
    {
        auto temp = open_list.top();
        delete[] temp;
        open_list.pop();
    }
    for(int i = 0; i < close_list.size(); i++)
    {
        delete[] close_list[i];
    }

    return;
}

void output(const string output_file, int &step_nums, string &way)
{
    ofstream file(output_file);
    if(file.is_open())
    {
        file << step_nums << endl;
        if(step_nums >= 0)
        {
            file << way << endl;
        }

        file.close();
    }
    else
    {
        cerr << "Can not open file: " << output_file << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    // printf("aaaa");
    string input_base = "../input/input_";
    string output_base = "../output/output_";
    for(int i = 0; i < 11; i++)
    {
        // if (i != 4) continue;
        printf("test i = %d\n", i);
        int step_nums = -1;
        string way = "";
        Astar_search(input_base + to_string(i) + ".txt", step_nums, way);
        output(output_base + to_string(i) + ".txt", step_nums, way);
    }
    return 0;
}