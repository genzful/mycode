#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

class Board {
private:
  map<char, char> board;

public:
  Board() {
    board = {{'1', '-'}, {'2', '-'}, {'3', '-'}, {'4', '-'}, {'5', '-'},
             {'6', '-'}, {'7', '-'}, {'8', '-'}, {'9', '-'}};
  }

  void print() {
    string printable;
    for (auto itr = board.begin(); itr != board.end(); ++itr) {
      printable += itr->second;
    }
    system("/usr/bin/clear");
    string message =
        "/usr/bin/python ~/mycode/myproj_on_cpp/tiktaktoe/source_code/printboard.py " + printable;
    system(message.c_str());
  }
  void set(char choose, char val) { board[choose] = val; }

  map<char, char> getboard() { return board; }

  // friend ostream &operator<<(ostream &out, const Board &obj) {
  //   int i = 1;
  //   for (auto itr = obj.board.begin(); itr != obj.board.end(); ++itr) {
  //     if (i == 1) {
  //       out << '|';
  //     }
  //     out << itr->second << '|';
  //     if (i % 3 == 0 && i != 9) {
  //       out << '\n' << '|';
  //     }
  //     i++;
  //   }
  //   out << '\n';
  //   return out;
  // }

};

class Player {
private:
  char sym;
  Board &board;
  int moveCount = 0;
  char pick[9] = {};
  char winning_combinations[8][3] = {
      {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'1', '4', '7'},
      {'2', '5', '8'}, {'3', '6', '9'}, {'1', '5', '9'}, {'3', '5', '7'}};

public:
  string name;
  Player(string name, char sym, Board &boardRef) : board(boardRef) {
    this->name = name;
    this->sym = sym;
  }

  void makemove() {
    try {
      string input;
      cout << name << ", ввод номера клетки: ";
      cin >> input;

      if (input.length() != 1) {
        throw invalid_argument("Введите ОДНУ цифру от 1 до 9!");
      }

      char choice = input[0];

      if (choice < '1' || choice > '9') {
        throw invalid_argument("Введите цифру от 1 до 9!");
      }

      map<char, char> gameboard = board.getboard();

      auto it = gameboard.find(choice);
      if (it == gameboard.end()) {
        throw invalid_argument("Такой клетки нет на доске!");
      }

      if (it->second == '-') {
        board.set(choice, sym);
      } else {
        cout << "Клетка занята!" << endl;
        return;
      }

      this->pick[moveCount] = choice;
      moveCount++;

    } catch (const exception &e) {
      cout << "Ошибка: " << e.what() << endl;
      cin.clear();
      cin.ignore(1000, '\n');
    }
  }

  bool win() {
    for (int i = 0; i < 8; i++) {
      bool combinationComplete = true;

      for (int j = 0; j < 3; j++) {
        bool found = false;
        for (int z = 0; z < moveCount; z++) {
          if (winning_combinations[i][j] == pick[z]) {
            found = true;
            break;
          }
        }
        if (!found) {
          combinationComplete = false;
          break;
        }
      }

      if (combinationComplete) {
        return true;
      }
    }
    return false;
  }
};

class Game {
private:
  Player *players[2];
  bool over;
  int v_move = 0;
  Board &board;

public:
  Game(Board &boardRef, Player &p1, Player &p2) : board(boardRef), over(false) {
    players[0] = &p1;
    players[1] = &p2;
  }

  void move() {
    if (v_move % 2 == 0) {
      players[0]->makemove();
      if (players[0]->win()) {
        this->over = true;
        cout << players[0]->name << " победил!" << endl;
        return;
      }
    } else {
      players[1]->makemove();
      if (players[1]->win()) {
        this->over = true;
        cout << players[1]->name << " победил!" << endl;
        return;
      }
    }

    map<char, char> gameboard = board.getboard();
    bool isDraw = true;
    for (auto itr = gameboard.begin(); itr != gameboard.end(); ++itr) {
      if (itr->second == '-') {
        isDraw = false;
        break;
      }
    }

    if (isDraw) {
      cout << "Ничья!" << endl;
      this->over = true;
    }

    v_move++;
  }

  bool isover() { return this->over; }
};

int main() {
  Board board;
  Player player1("Миша", 'X', board);
  Player player2("Игорь", 'O', board);

  Game game(board, player1, player2);

  while (!game.isover()) {
    board.print();
    game.move();
  }
  board.print();
  return 0;
}
