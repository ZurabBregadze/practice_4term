#include <iostream>
#include <vector>

struct Board {
    int n;
    std::vector<int> queens; // queens[i] - строка, где стоит ферзь в столбце i

    Board(int n) : n(n), queens(n, 0) {}
};

// Проверка безопасности позиции
bool isSafe(const Board& board, int row, int col) {
    for (int i = 0; i < col; ++i) {
        int q_row = board.queens[i];

        // Проверка на одну строку
        if (q_row == row)
            return false;

        // Проверка главной диагонали ↖ (разница row - col одинаковая)
        if (q_row - i == row - col)
            return false;

        // Проверка побочной диагонали ↙ (разница row + col одинаковая)
        if (q_row + i == row + col)
            return false;
    }
    return true;
}

// Рекурсивный поиск решений
void search(Board& board, int col, std::vector<Board>& solutions) {
    if (col == board.n) {
        solutions.push_back(board);
        return;
    }

    for (int row = 0; row < board.n; ++row) {
        if (isSafe(board, row, col)) {
            board.queens[col] = row;  // Ставим ферзя
            search(board, col + 1, solutions);
            board.queens[col] = -1;  // Убираем ферзя (бэктрекинг)
        }
    }
}

// Вывод vector
template<typename N>
std::ostream& operator<<(std::ostream& out,const std::vector<N>& vec)
{
    for (const auto x : vec)
    {
        out << x << std::endl;
    }
    return out;
}

// Вывод доски
std::ostream& operator<<(std::ostream& out, const Board& board)
{
    for (int i = 0; i < board.n; ++i) {
        for (int j = 0; j < board.n; ++j) {
            if (board.queens[j] == i) {
                out << "1";
            } else {
                out << "0";
            }
            if (j != board.n - 1) {
                out << " ";  //
            }
        }
        out << std::endl;
    }

    return out;
}

int main() {
    int n;
    std::cin >> n;

    Board board(n);
    std::vector<Board> solutions;
    

    search(board, 0, solutions);
    std::cout << "Найдено решений: "<< solutions.size() << std::endl;
    std::cout << solutions << std::endl; // рисовка досок
    return 0;
}
