#ifndef SOLVE_CPP
#define SOLVE_CPP

#include <bits/stdc++.h>

using namespace std;

class Storage {
protected:
    vector<vector<int> > table;
    vector<vector<int> > solution;
    pair<int, int> zero;
    int size;
};

class BFS {
private:
    const int ROWS;
    const int COLS;

    struct State {
        vector<vector<int> > board;
        int zeroRow, zeroCol;
        vector<int> path;

        State(const vector<vector<int> > &b, int zRow, int zCol, const vector<int> &p)
            : board(b), zeroRow(zRow), zeroCol(zCol), path(p) {
        }
    };

    struct VectorHash {
        size_t operator()(const vector<vector<int> > &v) const {
            hash<int> hasher;
            size_t seed = 0;
            for (const auto &inner: v) {
                for (const int &i: inner) {
                    seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }
            }
            return seed;
        }
    };

    struct VectorEqual {
        bool operator()(const vector<vector<int> > &lhs, const vector<vector<int> > &rhs) const {
            return lhs == rhs;
        }
    };

    bool isGoalState(const vector<vector<int> > &board) {
        int num = (COLS - ROWS) * COLS + 1;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != num && !(i == ROWS - 1 && j == COLS - 1 && board[i][j] == 0)) {
                    return false;
                }
                num++;
            }
        }
        return true;
    }


    vector<int> getValidMoves(int row, int col) {
        vector<int> moves;
        if (row > 0) {
            moves.push_back(-COLS);
        }
        if (row < ROWS - 1) {
            moves.push_back(COLS);
        }
        if (col > 0) {
            moves.push_back(-1);
        }
        if (col < COLS - 1) {
            moves.push_back(1);
        }
        return moves;
    }

public:
    BFS(int r, int c) : ROWS(r), COLS(c) {
    }

    vector<int> solvePuzzle(const vector<vector<int> > &board) {
        int zeroRow, zeroCol;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == 0) {
                    zeroRow = i;
                    zeroCol = j;
                    break;
                }
            }
        }

        State initialState(board, zeroRow, zeroCol, {});
        queue<State> statesQueue;
        statesQueue.push(initialState);

        unordered_map<vector<vector<int> >, bool, VectorHash, VectorEqual> visited;
        visited[board] = true;

        while (!statesQueue.empty()) {
            State currentState = statesQueue.front();
            statesQueue.pop();

            if (isGoalState(currentState.board)) {
                return currentState.path;
            }

            vector<int> moves = getValidMoves(currentState.zeroRow, currentState.zeroCol);

            for (int move: moves) {
                int newRow = currentState.zeroRow + move / COLS;
                int newCol = currentState.zeroCol + move % COLS;

                vector<vector<int> > newBoard = currentState.board;
                swap(newBoard[currentState.zeroRow][currentState.zeroCol], newBoard[newRow][newCol]);

                if (!visited[newBoard]) {
                    vector<int> newPath = currentState.path;
                    newPath.push_back(newBoard[currentState.zeroRow][currentState.zeroCol]);

                    State newState(newBoard, newRow, newCol, newPath);
                    statesQueue.push(newState);
                    visited[newBoard] = true;
                }
            }
        }

        return {};
    }
};

class General_function : public Storage {
protected:
    bool is_near_zero(int x, int y) {
        if (zero.first == x and zero.second == y)
            return true;
        int rowDiff = abs(zero.first - x);
        int colDiff = abs(zero.second - y);
        return ((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1));
    }

    void move(int x, int y) {
        swap(table[x][y], table[zero.first][zero.second]);
        zero.first = x;
        zero.second = y;
    }

public:
    void set_size(unsigned int n) {
        size = n;
        table.resize(n);
        int m = 1;
        for (auto &row: table) {
            row.resize(size);
            for (int &i: row) {
                i = (m == size * size) ? 0 : m;
                m++;
            }
        }
        solution = table;

        zero.first = table.size() - 1;
        zero.second = table.size() - 1;
    }

    pair<int, int> find(int value) {
        for (int i = 0; i < table.size(); ++i)
            for (int j = 0; j < table.size(); ++j)
                if (table[i][j] == value)
                    return pair<int, int>{i, j};
        return pair<int, int>{-1, -1};
    }

    bool move(int value) {
        pair<int, int> cords = find(value);
        if (is_near_zero(cords.first, cords.second)) {
            move(cords.first, cords.second);
            return true;
        }
        return false;
    }

    void make_random() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 3);
        for (int i = 0; i < 500; ++i) {
            int x = zero.first;
            int y = zero.second;
            switch (dis(gen)) {
                case 0:
                    if (x > 0)
                        move(x - 1, y);
                    break;
                case 1:
                    if (x < table.size() - 1)
                        move(x + 1, y);
                    break;
                case 2:
                    if (y > 0)
                        move(x, y - 1);
                    break;
                case 3:
                    if (y < table.size() - 1)
                        move(x, y + 1);
                    break;
                default:
                    break;
            }
        }
    }

    vector<vector<int> > get_table() {
        return table;
    }

    bool is_solved() {
        return solution == table;
    }

    void test_print() {
        for (auto row: table) {
            for (auto r: row) {
                cout << r << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
};

class Puzzle_game : public General_function {
private:
    void move_zero_up(vector<int> &path) {
        path.push_back(table[zero.first - 1][zero.second]);
        move(zero.first - 1, zero.second);
    }

    void move_zero_down(vector<int> &path) {
        path.push_back(table[zero.first + 1][zero.second]);
        move(zero.first + 1, zero.second);
    }

    void move_zero_left(vector<int> &path) {
        path.push_back(table[zero.first][zero.second - 1]);
        move(zero.first, zero.second - 1);
    }

    void move_zero_right(vector<int> &path) {
        path.push_back(table[zero.first][zero.second + 1]);
        move(zero.first, zero.second + 1);
    }

    bool is_zero_up(pair<int, int> cord) {
        return cord.second == zero.second and cord.first - 1 == zero.first;
    }

    bool is_zero_down(pair<int, int> cord) {
        return cord.second == zero.second and cord.first + 1 == zero.first;
    }

    bool is_zero_left(pair<int, int> cord) {
        return cord.first == zero.first and cord.second - 1 == zero.second;
    }

    bool is_zero_right(pair<int, int> cord) {
        return cord.first == zero.first and cord.second + 1 == zero.second;
    }

    void move_zero_to(int i, int j, vector<int> &path) {
        if (is_near_zero(i, j))
            return;
        if (zero.first - 1 == i) {
            if (zero.second > j) {
                move_zero_left(path);
            } else if (zero.second < j) {
                move_zero_right(path);
            }
        } else {
            if (zero.first > i) {
                move_zero_up(path);
            } else if (zero.first < i) {
                move_zero_down(path);
            } else if (zero.second > j) {
                move_zero_left(path);
            } else if (zero.second < j) {
                move_zero_right(path);
            }
        }
        move_zero_to(i, j, path);
    }

    void move_zero_to_left(pair<int, int> cord, vector<int> &path) {
        if ((cord.first == table.size() - 1 or cord.second == table.size() - 1) and (cord.first != 0)) {
            if (is_zero_right(cord)) {
                move_zero_up(path);
                move_zero_left(path);
            }
            if (is_zero_up(cord)) {
                move_zero_left(path);
                move_zero_down(path);
            }
            if (is_zero_down(cord)) {
                move_zero_left(path);
                move_zero_up(path);
            }
        } else {
            if (is_zero_up(cord)) {
                move_zero_right(path);
                move_zero_down(path);
            }
            if (is_zero_right(cord)) {
                move_zero_down(path);
                move_zero_left(path);
            }
            if (is_zero_down(cord)) {
                move_zero_left(path);
                move_zero_up(path);
            }
        }
    }

    void move_zero_to_right(pair<int, int> cord, vector<int> &path) {
        if (cord.first == table.size() - 1 or cord.second == table.size() - 1 or cord.second == 0) {
            if (is_zero_left(cord)) {
                move_zero_up(path);
                move_zero_right(path);
            }
            if (is_zero_up(cord)) {
                move_zero_right(path);
                move_zero_down(path);
            }
            if (is_zero_down(cord)) {
                move_zero_right(path);
                move_zero_up(path);
            }
        } else {
            if (is_zero_up(cord)) {
                move_zero_left(path);
                move_zero_down(path);
            }
            if (is_zero_left(cord)) {
                move_zero_down(path);
                move_zero_right(path);
            }
            if (is_zero_down(cord)) {
                move_zero_right(path);
                move_zero_up(path);
            }
        }
    }

    void move_zero_to_up(pair<int, int> cord, vector<int> &path) {
        if (cord.first == table.size() - 1 or cord.second == table.size() - 1) {
            if (is_zero_left(cord)) {
                move_zero_up(path);
                move_zero_right(path);
            }
            if (is_zero_right(cord)) {
                move_zero_up(path);
                move_zero_left(path);
            }
        } else {
            if (is_zero_left(cord)) {
                move_zero_down(path);
                move_zero_right(path);
            }
            if (is_zero_down(cord)) {
                move_zero_right(path);
                move_zero_up(path);
            }
            if (is_zero_right(cord)) {
                move_zero_up(path);
                move_zero_left(path);
            }
        }
    }

    void move_zero_to_up_left(pair<int, int> cord, vector<int> &path) {
        if (is_zero_down(cord)) {
            move_zero_left(path);
            move_zero_up(path);
        }
        if (is_zero_left(cord)) {
            move_zero_up(path);
            move_zero_right(path);
        }
    }

    void move_zero_to_down_left(pair<int, int> cord, vector<int> &path) {
        if (is_zero_up(cord)) {
            move_zero_left(path);
            move_zero_down(path);
        }
        if (is_zero_left(cord)) {
            move_zero_down(path);
            move_zero_right(path);
        }
    }

    void move_zero_wiht_value_to(pair<int, int> dest, pair<int, int> value, vector<int> &path) {
        while (dest.second != value.second) {
            if (dest.second < value.second) {
                move_zero_to_left(value, path);
                move_zero_right(path);
                value.second -= 1;
            } else {
                move_zero_to_right(value, path);
                move_zero_left(path);
                value.second += 1;
            }
        }
        while (dest.first != value.first) {
            if (dest.second != table.size() - 1) {
                move_zero_to_up(value, path);
                move_zero_down(path);
                value.first -= 1;
            } else {
                if (value.first - 1 == dest.first) {
                    if (zero.first == dest.first and zero.second == dest.second) {
                        move_zero_down(path);
                        value.first -= 1;
                    } else {
                        move_zero_to_down_left(value, path);
                        move_zero_up(path);
                        value.first += 1;
                    }
                } else {
                    move_zero_to_up_left(value, path);
                    if (value.first - 2 == dest.first) {
                        move_zero_up(path);
                        move_zero_left(path);
                        move_zero_down(path);
                        move_zero_right(path);
                        move_zero_down(path);

                        value.first -= 1;
                        move_zero_to_up_left(value, path);

                        move_zero_down(path);

                        value.first -= 1;
                    } else {
                        move_zero_down(path);
                        value.first -= 1;
                    }
                }
            }
        }
    }

public:
    vector<int> solve() {
        try {
            vector<vector<int> > copy = table;
            pair<int, int> zero_copy = zero;
            vector<int> path;
            int x = 0, y = 0, value = 1;
            while (!is_solved()) {
                if (table[y][x] != value) {
                    pair<int, int> cords = find(value);
                    move_zero_to(cords.first, cords.second, path);
                    move_zero_wiht_value_to(pair<int, int>{y, x}, cords, path);
                }

                value++;
                x++;
                if (x == table.size()) {
                    x = 0;
                    y++;
                }
                if (table.size() - y == 2)
                    break;
            }

            BFS solve(2, table.size());
            vector<vector<int> > lastTwo;
            lastTwo.push_back(table[table.size() - 2]);
            lastTwo.push_back(table.back());
            vector<int> solveTwo = solve.solvePuzzle(lastTwo);
            path.insert(path.end(), solveTwo.begin(), solveTwo.end());
            table = copy;
            zero = zero_copy;
            return path;
        } catch (...) {
            return {};
        }
    }
};

int main(void) {
    auto test = Puzzle_game();

    unsigned int size = 2;
    cout << "Input size of the puzzle (more than 5 is not recommended): ";
    cin >> size;

    test.set_size(size);
    test.make_random();
    test.test_print();
    for (auto &p: test.solve()) {
        cout << "Swap: " << p << std::endl;
        test.move(p);
        test.test_print();
        cout << string(8*size, '-') << endl;
    }

    return 0;
}
#endif
