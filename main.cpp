#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <utility>


int get_points(int bound) {
    switch (bound) {
        case 1:
            std::cout << "Circle1 is pressed!\n";
            return 5;
        case 2:
            std::cout << "Circle2 is pressed!\n";
            return 10;
        case 3:
            std::cout << "Circle3 is pressed!\n";
            return 15;
        case 4:
            std::cout << "Circle4 is pressed!\n";
            return 25;
        case 5:
            std::cout << "Circle5 is pressed!\n";
            return 50;
        default:
            std::cout << "Afara!\n";
            return 0;
    }
}

int bound_setter(sf::Vector2f mouse_vector){
    int bound_set = 0;
    //Functia de calculare a distantei de la coordonatele centrului (x:395;y:430)
    double distance = sqrt(pow(mouse_vector.x - 395,2)+ pow(mouse_vector.y - 430,2));
    if (distance >= -400 && distance <= 400) {
        bound_set = 1;
    }
    if (distance >= -300 && distance <= 300)  {
        bound_set = 2;
    }
    if (distance >= -200 && distance <= 200)  {
        bound_set = 3;
    }
    if (distance >= -100 && distance <= 100)  {
        bound_set = 4;
    }
    if (distance >= -50 && distance <= 50)  {
        bound_set = 5;
    }
    return bound_set;
}

class player {
    int player_score;
    std::string player_name;
public:
    player(int player_score_, std::string player) : player_score{player_score_}, player_name{std::move(player)} {}

    player(const player& other)= default;

    player(player&& other) noexcept : player_score{other.player_score}, player_name{std::move(other.player_name)}{}

    player& operator= (player&& other) noexcept {
        player_score = other.player_score;
        player_name = std::move(other.player_name);
        return *this;
    }

    ~player()= default;

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

    friend std::ostream& operator<<(std::ostream& os, const player& st) {
        os << "Nume: " << st.player_name << ", scor: " << st.player_score << "\n";
        return os;
    }
};

class dart {
    int position_x;
    int position_y;
    std::string dart_type;
public:
    dart(int position_x_, int position_y_, std::string dart_type_) : position_x{position_x_}, position_y{position_y_}, dart_type(std::move(dart_type_)) {}


    friend std::ostream& operator<<(std::ostream& os, const dart& st) {
        os << "Positie: " << st.position_x << " " << st.position_y << "\n";
        return os;
    }

};

class circle {
    sf::CircleShape& circle_name;
    float radius;
    float x_position;
    float y_position;
    sf::Color circle_color;

public:
    circle(sf::CircleShape& circle_name_, float r, float x, float y, sf::Color col): circle_name{circle_name_}, radius{r}, x_position{x}, y_position{y}, circle_color{col}{

    }

    void set_circle(){
        circle_name.setRadius(radius);
        circle_name.setPosition(x_position, y_position);
        circle_name.setFillColor(circle_color);

    }

    void draw_circle(sf::RenderWindow& window_){
        window_.draw(circle_name);
    }

};

class game{
    sf::RenderWindow window;
    player sc1{0, "Joe"}, sc2{0, "Garry"};
    sf::CircleShape circle1, circle2, circle3, circle4, circle5;
    dart dr1{0, 0, "basic"}, dr2{0, 0, "basic"};
    circle c1{circle1, 400.f, 10.f, 45.f, sf::Color(0, 0, 0)}, c2{circle2, 300.f, 110.f, 145.f, sf::Color(255, 255, 255)}, c3{circle3, 200.f, 210.f, 245.f, sf::Color(0, 0, 0)}, c4{ circle4,100.f, 310.f, 345.f, sf::Color(255, 255, 255)}, c5{ circle5,50.f, 360.f, 395.f,sf::Color(250, 50, 50)};
    sf::Texture crosshair;
    sf::Text player_1;
    sf::Text player_2;
    sf::Text score1;
    sf::Text score2;
    sf::Text text;
    sf::Sprite mouse_sprite;
    sf::Font font;

public:
    game(){

        window.create(sf::VideoMode(1200, 900), "Darts Game", sf::Style::Titlebar | sf::Style::Close);
        window.setMouseCursorVisible(false);

        crosshair.loadFromFile("crosshair_small_2.png");
        mouse_sprite.setTexture(crosshair);

        if (!font.loadFromFile("Roboto-Black.ttf"))
        {
            // error...
        }

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("Score:");

        // set the character size
        text.setCharacterSize(44); // in pixels

        // set the color
        text.setFillColor(sf::Color::Black);

        text.setPosition(900.f,70.f);

        player_1.setFont(font);
        player_1.setString("Player1:");
        player_1.setCharacterSize(44); // in pixels
        player_1.setFillColor(sf::Color::Black);
        player_1.setPosition(900.f,170.f);

        player_2.setFont(font);
        player_2.setString("Player2:");
        player_2.setCharacterSize(44); // in pixels
        player_2.setFillColor(sf::Color::Black);
        player_2.setPosition(900.f,240.f);

        c1.set_circle();
        c2.set_circle();
        c3.set_circle();
        c4.set_circle();
        c5.set_circle();


        score1.setFont(font);
        score2.setFont(font);
        score1.setString(std::to_string(sc1.get_score()));
        score2.setString(std::to_string(sc2.get_score()));

        score1.setCharacterSize(44); // in pixels
        score1.setFillColor(sf::Color::Black);
        score1.setPosition(1090.f,170.f);
        score2.setCharacterSize(44); // in pixels
        score2.setFillColor(sf::Color::Black);
        score2.setPosition(1090.f,240.f);

    }

    static void winner(player score1_, player score2_, sf::RenderWindow& win_window, const sf::Font& font) {

        sf::Text player_2_win;
        player_2_win.setFont(font);
        player_2_win.setString("Player2 WON!");
        player_2_win.setCharacterSize(44); // in pixels
        player_2_win.setFillColor(sf::Color::White);
        player_2_win.setPosition(300.f,340.f);

        sf::Text player_1_win;
        player_1_win.setFont(font);
        player_1_win.setString("Player1 WON!");
        player_1_win.setCharacterSize(44); // in pixels
        player_1_win.setFillColor(sf::Color::White);
        player_1_win.setPosition(300.f,340.f);

        sf::Text Tie;
        Tie.setFont(font);
        Tie.setString("Tie");
        Tie.setCharacterSize(44); // in pixels
        Tie.setFillColor(sf::Color::White);
        Tie.setPosition(300.f,340.f);
        win_window.clear(sf::Color::Black);
        if (score1_.get_score() == score2_.get_score())
        {
            std::cout << "Tie!";
            win_window.draw(Tie);

        }
        else if (score1_.get_score() < score2_.get_score())
        {
            std::cout << score2_.get_player_name() << " wins!";
            win_window.draw(player_2_win);

        }
        else
        {
            std::cout << score1_.get_player_name() << " wins!";
            win_window.draw(player_1_win);
        }
        win_window.display();
    }

    void run(){
        int i = 0;
        int j = 0;
        int t = 0;
        bool mouse_pressed = false;
        int end = 0;
        while (window.isOpen()){
            sf::Event event{};
            sf::View fixed = window.getView();
            window.setFramerateLimit(60);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(end == 0){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse_pressed && j == 0) {
                        mouse_pressed = true;
                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        // transform the mouse position from window coordinates to world coordinates
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        sc1.update_Score(get_points(bound_setter(mouse)));
                        score1.setString(std::to_string(sc1.get_score()));
                        i++;
                        j++;
                        std::cout<<i<<" "<<j<<"\n";

                        std::cout << localPosition.x << "\n";
                        std::cout << localPosition.y << "\n";
                        std::cout << "______________\n";

                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse_pressed && j == 1 && t == 0) {
                        mouse_pressed = true;
                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        // transform the mouse position from window coordinates to world coordinates
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        sc1.update_Score(get_points(bound_setter(mouse)));
                        score1.setString(std::to_string(sc1.get_score()));
                        i++;
                        j++;
                        t++;
                        std::cout<<i<<" "<<j<<" "<<t<<"\n";

                        std::cout << localPosition.x << "\n";
                        std::cout << localPosition.y << "\n";
                        std::cout << "______________\n";

                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse_pressed && j == 1 && t == 1) {
                        mouse_pressed = true;
                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        // transform the mouse position from window coordinates to world coordinates
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        sc2.update_Score(get_points(bound_setter(mouse)));
                        score2.setString(std::to_string(sc2.get_score()));
                        i++;
                        j--;
                        t--;
                        std::cout<<i<<" "<<j<<" "<<t<<"\n";

                        std::cout << localPosition.x << "\n";
                        std::cout << localPosition.y << "\n";
                        std::cout << "______________\n";

                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse_pressed && j == 2) {
                        mouse_pressed = true;
                        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                        // transform the mouse position from window coordinates to world coordinates
                        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                        sc2.update_Score(get_points(bound_setter(mouse)));
                        score2.setString(std::to_string(sc2.get_score()));
                        i++;
                        j--;
                        std::cout<<i<<" "<<j<<"\n";


                        std::cout << localPosition.x << "\n";
                        std::cout << localPosition.y << "\n";
                        std::cout << "______________\n";

                    }

                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        mouse_pressed = false;
                }
                if  (i==12)
                    end = 1;

                //draw loop
                switch (end) {
                    case 0:
                        window.clear(sf::Color::White);
                        window.setView(fixed);
                        window.draw(text);
                        window.draw(score1);
                        window.draw(score2);
                        window.draw(player_1);
                        window.draw(player_2);
                        c1.draw_circle(window);
                        c2.draw_circle(window);
                        c3.draw_circle(window);
                        c4.draw_circle(window);
                        c5.draw_circle(window);
                        mouse_sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                        window.draw(mouse_sprite);
                        window.display();
                        break;
                    case 1:
                        winner(sc1,sc2,window,font);
                        break;

                }
            }
        }
    }
};

int main() {

   game darts;
   darts.run();

    return 0;
}