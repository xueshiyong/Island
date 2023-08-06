#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct Pos{
    int x;
    int y;
};

void DFS(Pos pos, vector<vector<int>> &island){
    if (pos.x >= 0 and pos.x < island.size() and pos.y >= 0 and pos.y < island[0].size() and island[pos.x][pos.y] == 1){
        Pos left_pos = {pos.x - 1, pos.y};
        Pos right_pos = {pos.x + 1, pos.y};
        Pos up_pos = {pos.x, pos.y - 1};
        Pos down_pos = {pos.x, pos.y + 1};
        island[pos.x][pos.y] = 2;

        DFS(left_pos, island);
        DFS(right_pos, island);
        DFS(up_pos, island);
        DFS(down_pos, island);
    }
    else{
        return;
    }

}

int BFS(Pos pos, vector<vector<int>> &island){
    queue<Pos> que;
    que.push(pos);
    int island_area = 0;

    while (!que.empty()){
        Pos current_pos = que.front();
        que.pop();

        int xx = current_pos.x;
        int yy = current_pos.y;

        if (xx - 1 >= 0 and island[xx - 1][yy] == 1){
            island[xx - 1][yy] = 2;
            Pos next_pos = {xx - 1, yy};
            que.push(next_pos);
            island_area++;
        }

        if (xx + 1 < island.size() and island[xx + 1][yy] == 1){
            island[xx + 1][yy] = 2;
            Pos next_pos = {xx + 1, yy};
            que.push(next_pos);
            island_area++;

        }

        if (yy - 1 >= 0 and island[xx][yy - 1] == 1){
            island[xx][yy - 1] = 2;
            Pos next_pos = {xx, yy - 1};
            que.push(next_pos);
            island_area++;
        }

        if (yy + 1 < island[0].size() and island[xx][yy + 1] == 1){
            island[xx][yy + 1] = 2;
            Pos next_pos = {xx, yy + 1};
            que.push(next_pos);
            island_area++;
        }
    }
    return island_area;
}
void Island_num(vector<vector<int>> island){
    int num = 0;
    int island_area = INT32_MIN;

    for (int i = 0; i < island.size(); i++){
        for (int j = 0; j < island[0].size(); j++){
            if (island[i][j] == 1){
                num++;
                Pos pos = {i, j};
                int current_island_area = BFS(pos, island);
                island_area = max(island_area, current_island_area);
            }
        }
    }

    cout << "num: " << num << endl;
    cout << "max island area: " << island_area << endl;
}

int rotten_oranges(vector<vector<int>> &orange){
    queue<Pos> que;
    int m = orange.size();
    int n = orange[0].size();

    vector<vector<int>> distance(m, vector<int>(m, -1));
    int cnt = 0;
    int res = 0;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (orange[i][j] == 2){
                Pos pos = {i, j};
                que.push(pos);

                distance[i][j] = 0;
            }
            else if(orange[i][j] == 1){
                cnt++;
            }
        }
    }

    while (!que.empty()){
        Pos current_pos = que.front();
        que.pop();

        int xx = current_pos.x;
        int yy = current_pos.y;

        if (xx - 1 >= 0 and orange[xx - 1][yy] == 1){
            cnt--;
            orange[xx - 1][yy] = 2;

            distance[xx - 1][yy] = distance[xx][yy] + 1;
            res = max(res, distance[xx - 1][yy]);

            Pos next_pos = {xx - 1, yy};
            que.push(next_pos);
        }

        if (xx + 1 < m and orange[xx + 1][yy] == 1){
            cnt--;
            orange[xx + 1][yy] = 2;

            distance[xx + 1][yy] = distance[xx][yy] + 1;
            res = max(res, distance[xx + 1][yy]);

            Pos next_pos = {xx + 1, yy};
            que.push(next_pos);
        }

        if (yy - 1 >= 0 and orange[xx][yy - 1] == 1){
            cnt--;
            orange[xx][yy - 1] = 2;

            distance[xx][yy - 1] = distance[xx][yy] + 1;
            res = max(res, distance[xx][yy - 1]);

            Pos next_pos = {xx, yy - 1};
            que.push(next_pos);
        }

        if (yy + 1 < n and orange[xx][yy + 1] == 1){
            cnt--;
            orange[xx][yy + 1] = 2;

            distance[xx][yy + 1] = distance[xx][yy] + 1;
            res = max(res, distance[xx][yy + 1]);

            Pos next_pos = {xx, yy + 1};
            que.push(next_pos);
        }

    }

    if (cnt >= 1){
        return -1;
    }
    cout << "time: " << res << endl;
    return res;
}

struct M_Pos{
    int x;
    int y;
    int step;
};

void min_maze_path(vector<vector<int>> &Maze, Pos start, Pos end){
    queue<M_Pos> que;
    int start_x = start.x;
    int start_y = start.y;

    int end_x = end.x;
    int end_y = end.y;

    int m = Maze.size();
    int n = Maze[0].size();

    vector<vector<int>> used(m, vector<int> (n, 0));
    int step = 0;

    M_Pos m_pos = {start_x, start_y, step};
    que.push(m_pos);

    used[start_x][start_y] = 1;

    vector<int> X_pos = {-1, 1, 0, 0};
    vector<int> Y_pos = {0, 0, -1, 1};

    while (!que.empty()){
        M_Pos current_pos = que.front();
        que.pop();

        int xx = current_pos.x;
        int yy = current_pos.y;
        int sp = current_pos.step;

        if (xx == end_x and yy == end_y){
            cout << "steps: " << sp << endl;
            break;
        }

        for (int i = 0; i < 4; i++){
            int next_xx = xx + X_pos[i];
            int next_yy = yy + Y_pos[i];

            if (next_xx >= 0 and next_xx < m and next_yy >= 0 and next_yy < n and used[next_xx][next_yy] == 0
            and Maze[next_xx][next_yy] == 0){
                M_Pos next_pos = {next_xx, next_yy, sp + 1};
                que.push(next_pos);
                used[next_xx][next_yy] = 1;
            }
            else{
                continue;
            }
        }

    }
}

int main(){
    vector<vector<int>> Maze = {
            {0, 0, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 1}
    };

    Pos start = {0, 0};
    Pos end = {1, 2};
    min_maze_path(Maze, start, end);
}