// TikTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <cstdint>
enum Position {
    topleft,
    topMiddle,
    topRight,
    middleLeft,
    middleMiddle,
    middleRight,
    bottomLeft,
    bottomMiddle,
    bottomRight
};
Position toPosition(std::string_view c) {
    static const std::unordered_map<std::string_view, Position> positionMap{
        {"tl", topleft}, {"tm", topMiddle}, {"tr", topRight},
        {"ml", middleLeft}, {"mm", middleMiddle}, {"mr", middleRight},
        {"bl", bottomLeft}, {"bm", bottomMiddle}, {"br", bottomRight}
    };

    auto it = positionMap.find(c);
    if (it != positionMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid position string");
}

class DrawBoard {
public:
    DrawBoard() = default;
    void printBoard() {
        for (const auto& e : m_board) {
            for (const auto& el : e) {
                std::cout << el;
            }
            std::cout << '\n';
        }
    }
    bool checkWin(char player) {
        
        // Check the row
        if (m_board[lastPosition.first][0] == player && m_board[lastPosition.first][3] == player && m_board[lastPosition.first][5] == player) {
            return true;
        }

        // Check the column
        if (m_board[0][lastPosition.second] == player && m_board[2][lastPosition.second] == player && m_board[4][lastPosition.second] == player) {
            return true;
        }

        // Check the diagonals
        if ( m_board[0][0] == player && m_board[2][3] == player && m_board[4][5] == player) {
            return true;
        }
        if (m_board[0][5] == player && m_board[2][3] == player && m_board[4][0] == player) {
            return true;
        }

        return false;
    }
    bool checkPositionValidity(Position p) {
        auto pos = m_positionMap[p];
        int row = pos.first;
        int col = pos.second;


        // Check if the position is valid (i.e., not already occupied)
        return m_board[row][col] == ' ';
    }
    void placePosition(Position p, char c) {
        auto pos = m_positionMap[p];
        int row = pos.first;
        int col = pos.second;
        m_board[row][col] = c;
        lastPosition = std::make_pair(row, col);
    }
private:
    std::vector<std::vector<char>> m_board{
   {' ',' ', '|', ' ' , '|', ' '},
   {'-','-', '-', '-', '-', '-','-'},
   {' ',' ', '|', ' ' , '|', ' '},
   {'-','-', '-', '-', '-', '-','-'},
   {' ',' ', '|', ' ' , '|', ' '}
    };
    std::map<Position, std::pair<int, int>> m_positionMap{
    {topleft, {0, 0}},
    {topMiddle, {0, 3}},
    {topRight, {0, 5}},
    {middleLeft, {2, 0}},
    {middleMiddle, {2, 3}},
    {middleRight, {2, 5}},
    {bottomLeft, {4, 0}},
    {bottomMiddle, {4, 3}},
    {bottomRight, {4, 5}}
    };
    std::pair<int, int> lastPosition{};
};
class Player {
public:
    Player() : m_player{'o'} {}

    void checkAndChangePlayer() {
        if (m_player == 'o') m_player = 'x';
        else if (m_player == 'x') m_player = 'o';
    }
    char getPlayer()const { return m_player; }
private:
    char m_player{};
};
static inline std::string_view lookupTable[9] = { "tl","tm","tr","ml","mm","mr","bl","bm","br" };
bool validateInput(std::string_view input) {
    for (const auto& e : lookupTable) {
        if (input == e) {
            return true;
        }
    }
    return false;
}
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void  getInput(char playerCharacter, DrawBoard& board) {
    std::string input{};
    while (true) {
        std::cout << "Where do you want to go? " << playerCharacter << ": ";
        std::cin >> input;
        ignoreLine();
        if (validateInput(input)) {
            Position position{ toPosition(input) };
            if (board.checkPositionValidity(position)) {
                board.placePosition(position, playerCharacter);
                break;
            }
            else if (!board.checkPositionValidity(position)) {
                std::cout << "Position already filled.\n";
            }
        }
    }
}
int main()
{
    DrawBoard board{};
    board.printBoard();
    std::cout << "Moves are: tr = top right, tl = top left, tm = top middle, mr ml mm, bm br bl as follows\n";
    Player player{};
    while (true) {
        char playerCharacter{ player.getPlayer() };
        getInput(playerCharacter, board);
        board.printBoard();
        if (board.checkWin(playerCharacter)) {
            std::cout << playerCharacter << " wins!";
            break;
        }
        player.checkAndChangePlayer();


    }
}

