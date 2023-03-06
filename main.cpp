#include <iostream>
#include <utility>


class score {
    int player_score;
    std::string player_name;
public:
    score(int player_score_, std::string player) : player_score{player_score_}, player_name{std::move(player)} {}

    score(const score& other)= default;

    score(score&& other) noexcept : player_score{other.player_score}, player_name{std::move(other.player_name)}{}

    score& operator= (score&& other) noexcept {
        player_score = other.player_score;
        player_name = std::move(other.player_name);
        return *this;
    }

    ~score()= default;

    void get_name(int j) {
        std::cout << "Player"<< j << ":";
        std::cin >> player_name;

    }

    void update_Score(int hit_score) {
        player_score = player_score + hit_score;
        std::cout << player_name << " are " << player_score << " puncte!\n";
    }

    [[nodiscard]] int get_score() const{
        return player_score;
    }
    std::string get_player_name(){
        return player_name;
    }

    friend std::ostream& operator<<(std::ostream& os, const score& st) {
        os << "Nume: " << st.player_name << ", scor: " << st.player_score << "\n";
        return os;
    }
};

class board_space {
    int value;
    int x;
    int y;
public:
    board_space(int ival, int x_, int y_) : value{ival}, x{x_}, y{y_} {}

    int get_points() {
        if (x >= 0 && x <= 8 && y >= 0 && y <= 8){
            std::cout << "Ai lovit pozitia " << x << " "<< y << "!\n";
            std::cout << "Ai obtinut " << value << " puncte!\n";
        }
        else {
            std::cout << "Ai dat afara!\n";
            std::cout << "Ai obtinut 0 puncte!\n";
            value = 0;
        }

        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const board_space& st) {
        os << "Puncte: " << st.value << ", positie: " << st.x <<" "<< st.y<< "\n";
        return os;
    }

};

class dart {
    int position_x;
    int position_y;
    std::string dart_type;
public:
    dart(int position_x_, int position_y_, std::string dart_type_) : position_x{position_x_}, position_y{position_y_}, dart_type(std::move(dart_type_)) {}

    void get_position() {
        std::cout << "Introduce-ti pozitia darts-ului:" << std::endl;
        std::cout << "x:";
        std::cin >> position_x;
        if (position_x < 0 || position_x > 8)
        {
            position_x = 9;
        }
        std::cout << "y:";
        std::cin >> position_y;
        if (position_x < 0 || position_x > 8)
        {
            position_x = 9;
        }

    }

    [[nodiscard]] int get_x() const {
        return position_x;
    }

    [[nodiscard]] int get_y() const {
        return position_y;
    }

    friend std::ostream& operator<<(std::ostream& os, const dart& st) {
        os << "Positie: " << st.position_x << " " << st.position_y << "\n";
        return os;
    }

};

void winner(score score1_, score score2_) {
    if (score1_.get_score() == score2_.get_score())
        std::cout << "Tie!";
    else if (score1_.get_score() < score2_.get_score())
        std::cout << score2_.get_player_name() << " wins!";
    else
        std::cout << score1_.get_player_name() << " wins!";
}


int main() {
    int i, j = 1;
    score sc3{0, "Joe"}, sc4{0, "Garry"};
    dart dr1{0,0, "basic"}, dr2{0,0, "basic"};
    board_space a[] = {board_space(5,0,0),board_space(5,0,1), board_space(5,0,2), board_space(5,0,3), board_space(5,0,4), board_space(5,0,5), board_space(5,0,6), board_space(5,0,7), board_space(5,0,8), board_space(5,1,0),board_space(10,1,1), board_space(10,1,2), board_space(10,1,3), board_space(10,1,4), board_space(10,1,5), board_space(10,1,6), board_space(10,1,7), board_space(5,1,8), board_space(5,2,0),board_space(10,2,1), board_space(15,2,2), board_space(15,2,3), board_space(15,2,4), board_space(15,2,5), board_space(15,2,6), board_space(10,2,7), board_space(5,2,8), board_space(5,3,0),board_space(10,3,1), board_space(15,3,2), board_space(25,3,3), board_space(25,3,4), board_space(25,3,5), board_space(15,3,6), board_space(10,3,7), board_space(5,3,8), board_space(5,4,0),board_space(10,4,1), board_space(15,4,2), board_space(25,4,3), board_space(50,4,4), board_space(25,4,5), board_space(15,4,6), board_space(10,4,7), board_space(5,4,8), board_space(5,5,0),board_space(10,5,1), board_space(15,5,2), board_space(25,5,3), board_space(25,5,4), board_space(25,5,5), board_space(15,5,6), board_space(10,5,7), board_space(5,5,8), board_space(5,6,0),board_space(10,6,1), board_space(15,6,2), board_space(15,6,3), board_space(15,6,4), board_space(15,6,5), board_space(15,6,6), board_space(10,6,7), board_space(5,6,8), board_space(5,7,0),board_space(10,7,1), board_space(10,7,2), board_space(10,7,3), board_space(10,7,4), board_space(10,7,5), board_space(10,7,6), board_space(10,7,7), board_space(5,7,8), board_space(5,8,0),board_space(5,8,1), board_space(5,8,2), board_space(5,8,3), board_space(5,8,4), board_space(5,8,5), board_space(5,8,6), board_space(5,8,7), board_space(5,8,8) };
    score sc1 = sc3;
    score sc2 = sc4;
    std::cout<<"Reguli: Jocul se joaca in 2 persoane\n";
    std::cout<<"Sunt 3 runde\n";
    std::cout<<"Tabla de darts este de dimensiunea 9X9\n";
    std::cout<<"Fiecare jucator are 2 darts-uri pe runda. De fiecare data trebuie sa fie introdus un numar intre 0 si 8 odata pentru positia orizontala a darts-ului si apoi pentru pozitia verticala.\n";
    std::cout<<"Jucatorul cu cele mai multe puncte la final castiga!\n\n";
    sc1.get_name(j);
    j++;
    sc2.get_name(j);
    for(i = 0; i< 2; i++)
    {
        dr1.get_position();
        sc1.update_Score(a[dr1.get_x()*9 + dr1.get_y()].get_points());
        dr2.get_position();
        sc1.update_Score(a[dr2.get_x()*9 + dr2.get_y()].get_points());
        std::cout << "Next player!\n";

        dr1.get_position();
        sc2.update_Score(a[dr1.get_x()*9 + dr1.get_y()].get_points());
        dr2.get_position();
        sc2.update_Score(a[dr2.get_x()*9 + dr2.get_y()].get_points());
        std::cout << "Next player!\n";
    }
    dr1.get_position();
    sc1.update_Score(a[dr1.get_x()*9 + dr1.get_y()].get_points());
    dr2.get_position();
    sc1.update_Score(a[dr2.get_x()*9 + dr2.get_y()].get_points());
    std::cout << "Next player!\n";

    dr1.get_position();
    sc2.update_Score(a[dr1.get_x()*9 + dr1.get_y()].get_points());
    dr2.get_position();
    sc2.update_Score(a[dr2.get_x()*9 + dr2.get_y()].get_points());
    std::cout << sc1 << sc2;
    winner(sc1,sc2);
    return 0;
}
