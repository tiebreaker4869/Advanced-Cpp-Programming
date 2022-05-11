#include <iostream>
#include <vector>
enum Type {
    X, O, UNDEFINED
};

enum State {
    X_WIN, O_WIN, DOGFALL, UNFINISHED
};

class Chess {
    private:
        Type type;
    public:
        Chess():type(UNDEFINED){};
        Type get_type(){return type;}
        void set_type(Type player){type = player;}
};

class Board {
    private:
        int size;
        std::vector<std::vector<Chess>> board;
        bool check_row(Type player, int threshold);
        bool check_col(Type player, int threshold);
        bool check_diag(Type player, int threshold);
        bool check_undiag(Type player, int threshold);
    public:
        Board(int _size):size(_size){
            board.resize(_size);
            for(int i = 0; i < _size; i ++){
                board[i].resize(_size);
            }

            for(int i = 0; i < size; i ++)
                for(int j = 0; j < size; j ++)
                    board[i][j].set_type(UNDEFINED);
        }
        

        State check(int threshold);

        void put(int x, int y, Type player);
};

class Game {
    private:
        Board board;
        Type currentPlayer;
    public:
        Game(int board_size):board(board_size),currentPlayer(O){

        }
        void take_turn(int x, int y);

        void switch_turn();

        State check(int threshold);
};



State Board::check(int threshold){
    if(check_row(X, threshold) || check_col(X, threshold) || check_diag(X, threshold) || check_undiag(X, threshold)){
        return X_WIN;
    }

    if(check_row(O, threshold) || check_col(O, threshold) || check_diag(O, threshold) || check_undiag(O, threshold)){
        return O_WIN;
    }

    for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++){
            if(board[i][j].get_type() == UNDEFINED)return UNFINISHED;
        }

    return DOGFALL;
}

void Board::put(int x, int y, Type player){
    board[x][y].set_type(player);
}

void Game::take_turn(int x, int y){
    board.put(x, y, currentPlayer);
}

void Game::switch_turn(){
    currentPlayer = currentPlayer == X ? O : X;
}

State Game::check(int threshold){
    return board.check(threshold);
}

bool Board::check_row(Type player, int threshold){
        for(int i = 0; i < size; i ++){
            for(int j = i; j <= size - threshold; j ++){
                bool success = true;
                for(int k = 0; k < threshold; k ++){
                    if(board[i][j + k].get_type() != player){
                        success = false;
                        break;
                    }
                }
                if(success)return true;
            }
        }
        
    return false;
}

bool Board::check_col(Type player, int threshold){
    for(int i = 0; i < size; i ++)
        for(int j = i; j <= size - threshold; j ++){
            bool success = true;
            for(int k = 0; k < threshold; k ++){
                if(board[j+k][i].get_type() != player){
                    success = false;
                    break;
                }
            }
            if(success)return true;
        }
    
    return false;
}

bool Board::check_diag(Type player, int threshold){
    for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++){
            bool success = true;
            for(int k = 0; k < threshold; k ++){
                int x_ = i + k, y_ = j + k;
                if(x_ >= size || y_ >= size || board[x_][y_].get_type() != player){
                    success = false;
                    break;
                }
            }
            if(success)return true;
        }
    return false;
}

bool Board::check_undiag(Type player, int threshold){
    for(int i = 0; i < size; i ++)
        for(int j = 0; j < size; j ++){
            bool success = true;
            for(int k = 0; k < threshold; k ++){
                int x_ = i + k, y_ = j - k;
                if(x_ >= size || y_ < 0 || board[x_][y_].get_type() != player){
                    success = false;
                    break;
                }
            }
            if(success)return true;
        }

    return false;
}

int main(){
    int _size, win_threshold;
    std::cin >> _size >> win_threshold;
    Game game(_size);
    
    while(game.check(win_threshold) == UNFINISHED){
        int x, y;
        std::cin >> x >> y;
        game.take_turn(x, y);
        game.switch_turn();
    }

    if(game.check(win_threshold) == X_WIN)std::cout << "X Success ";
    else if(game.check(win_threshold) == O_WIN)std::cout << "O Success ";
    else std::cout << "Dogfall " << std::endl;

    return 0;
}