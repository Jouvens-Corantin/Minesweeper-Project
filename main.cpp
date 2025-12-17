#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Project II Back-end.h"
#include <random>

int main() {

    //Opening Config Files to get Aspects
    std::vector<std::string> config_lines;
    std::string line;
    std::ifstream file;
    file.open("files/config.cfg", std::ios::in);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }
    while (file >> line) {
        config_lines.push_back(line);
    }
    file.close();

    //Column and row count
    int colCount = stoi(config_lines[0]);
    int rowCount = stoi(config_lines[1]);
    int mineCount = stoi(config_lines[2]);
    int estimated_mine_count = mineCount;

    //Width and Height for windows
    int col_width1 = colCount * 32;
    int row_height1 = (rowCount * 32) + 100;
    int col_width2 = colCount * 16;
    int row_height2 = (rowCount * 16) + 50;

    //Opening and Reading Font Style
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Error loading fonts" << std::endl;
    }

    //"WELCOME TO MINESWEEPER!" Screen set up
    float text_x_pos_welcome = col_width1/2;
    float text_y_pos_welcome = (row_height1/2) - 150;
    sf::Text welcome_text;
    setText(welcome_text, text_x_pos_welcome, text_y_pos_welcome, font, "WELCOME TO MINESWEEPER!", 24, sf::Color::White);
    welcome_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    //"Enter your Name." set up
    float text_x_pos_name = col_width1/2;
    float text_y_pos_name = (row_height1/2) - 75;
    sf::Text enter_name_text;
    setText(enter_name_text, text_x_pos_name, text_y_pos_name, font, "Enter your name:", 20, sf::Color::White);
    enter_name_text.setStyle(sf::Text::Bold);

    //Setting up Welcome Window
    sf::RenderWindow welcome_window(sf::VideoMode(col_width1, row_height1), "Welcome!");

    //Value to Transition between game states
    std::string game_state = "welcome";
    std::string game_state_2 = "None";

    //Stores Characters of entered name
    std::vector<std::string> characters_for_entered_name = {"|"};

    //Verification condition to prevent key spamming
    bool aKeyWasPressed = false;

    //Loop Stop Condition
    bool playing = true;

    //Gaming State Stop Condition
    bool gaming = true;

    //Setting Up UI Sprites
    sf::Sprite face_happy_sprite;
    sf::Texture face_happy;
    face_happy.loadFromFile("files/images/face_happy.png");
    face_happy_sprite.setTexture(face_happy);
    float happy_face_postionx = ((colCount/2) * 32) - 32;
    float happy_face_postiony = 32 * (rowCount + 0.5);
    face_happy_sprite.setPosition(happy_face_postionx, happy_face_postiony);

    sf::Sprite face_lose_sprite;
    sf::Texture face_lose;
    face_lose.loadFromFile("files/images/face_lose.png");
    face_lose_sprite.setTexture(face_lose);
    face_lose_sprite.setPosition(happy_face_postionx, happy_face_postiony);

    sf::Sprite face_won_sprite;
    sf::Texture face_won;
    face_won.loadFromFile("files/images/face_win.png");
    face_won_sprite.setTexture(face_won);
    face_won_sprite.setPosition(happy_face_postionx, happy_face_postiony);

    sf::Sprite debug_button_sprite;
    sf::Texture debug_button;
    debug_button.loadFromFile("files/images/debug.png");
    debug_button_sprite.setTexture(debug_button);
    float debug_button_postionx = ((colCount * 32) - 304);
    float debug_button_postiony = 32 * (rowCount + 0.5);
    debug_button_sprite.setPosition(debug_button_postionx, debug_button_postiony);

    sf::Sprite pause_sprite;
    sf::Texture pause;
    pause.loadFromFile("files/images/pause.png");
    pause_sprite.setTexture(pause);
    float pause_postionx = ((colCount * 32) - 240);
    float pause_postiony = 32 * (rowCount + 0.5);
    pause_sprite.setPosition(pause_postionx, pause_postiony);

    sf::Sprite play_sprite;
    sf::Texture play;
    play.loadFromFile("files/images/play.png");
    play_sprite.setTexture(play);
    float play_postionx = ((colCount * 32) - 240);
    float play_postiony = 32 * (rowCount + 0.5);
    play_sprite.setPosition(play_postionx, play_postiony);

    sf::Sprite leaderboard_sprite;
    sf::Texture leaderboard_button;
    leaderboard_button.loadFromFile("files/images/leaderboard.png");
    leaderboard_sprite.setTexture(leaderboard_button);
    float leaderboard_postionx = ((colCount * 32) - 176);
    float leaderboard_postiony = 32 * (rowCount + 0.5);
    leaderboard_sprite.setPosition(leaderboard_postionx, leaderboard_postiony);


    //Tile Related Sprites
    sf::Sprite tile_hidden_sprite;
    sf::Texture tile_hidden;
    tile_hidden.loadFromFile("files/images/tile_hidden.png");
    tile_hidden_sprite.setTexture(tile_hidden);

    sf::Sprite tile_revealed_sprite;
    sf::Texture tile_revealed;
    tile_revealed.loadFromFile("files/images/tile_revealed.png");
    tile_revealed_sprite.setTexture(tile_revealed);

    sf::Sprite mine_sprite;
    sf::Texture mine;
    mine.loadFromFile("files/images/mine.png");
    mine_sprite.setTexture(mine);

    sf::Sprite flag_sprite;
    sf::Texture flag;
    flag.loadFromFile("files/images/flag.png");
    flag_sprite.setTexture(flag);

    sf::Sprite num_one_sprite;
    sf::Texture one;
    one.loadFromFile("files/images/number_1.png");
    num_one_sprite.setTexture(one);

    sf::Sprite num_two_sprite;
    sf::Texture two;
    two.loadFromFile("files/images/number_2.png");
    num_two_sprite.setTexture(two);

    sf::Sprite num_three_sprite;
    sf::Texture three;
    three.loadFromFile("files/images/number_3.png");
    num_three_sprite.setTexture(three);

    sf::Sprite num_four_sprite;
    sf::Texture four;
    four.loadFromFile("files/images/number_4.png");
    num_four_sprite.setTexture(four);

    sf::Sprite num_five_sprite;
    sf::Texture five;
    five.loadFromFile("files/images/number_5.png");
    num_five_sprite.setTexture(five);

    sf::Sprite num_six_sprite;
    sf::Texture six;
    six.loadFromFile("files/images/number_6.png");
    num_six_sprite.setTexture(six);

    sf::Sprite num_seven_sprite;
    sf::Texture seven;
    seven.loadFromFile("files/images/number_7.png");
    num_seven_sprite.setTexture(seven);

    sf::Sprite num_eight_sprite;
    sf::Texture eight;
    eight.loadFromFile("files/images/number_8.png");
    num_eight_sprite.setTexture(eight);

    std::vector<sf::Sprite> counter_digits;
    std::vector<sf::Sprite> timer_digits;
    sf::Texture digit;
    digit.loadFromFile("files/images/digits.png");
    sf::Sprite digit_sprite;
    for (int i = 0; i <= 10; i++) {
        sf::IntRect textureRect(21 * i, 0, 21, 32);
        digit_sprite.setTextureRect(textureRect);
        digit_sprite.setTexture(digit);
        counter_digits.push_back(digit_sprite);
        timer_digits.push_back(digit_sprite);
    }


    //Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribx(0, colCount - 1);
    std::uniform_int_distribution<> distriby(0, rowCount - 1);

    //Array storing current top 5
    std::string top_five_times_string[5];
    std::string top_five_names[5];
    std::ifstream leaderboard_file;
    std::string leaderboard_data;
    leaderboard_file.open("files/leaderboard.txt");
    if (!leaderboard_file.is_open()) {
        std::cerr << "Could not open leaderboard file" << std::endl;
    }
    for(int i = 0; i < 5; i++) {
        getline(leaderboard_file, leaderboard_data);
        std::vector<std::string> data;
        std::istringstream stream(leaderboard_data);
        std::string token;
        while (getline(stream, token, ',')) {
            data.push_back(token);
        }
        top_five_times_string[i] = data[0];
        top_five_names[i] = data[1];
    }



    //Main Loop
    while(playing) {

        //Closing Condition for Welcome Screen
        sf::Event first_screen;
        while(welcome_window.pollEvent(first_screen)) {
            if(first_screen.type == sf::Event::Closed) {
                playing = false;
                gaming = false;
                welcome_window.close();
            }
        }

        //Welcome Screen
        if (game_state == "welcome") {

            //variable for text height
            int text_x_pos_enteredname = col_width1/2;
            int text_y_pos_enteredname = (row_height1/2) - 45;

            //Empty string to construct text to display
            std::string entered_name = "";

            //Evaluation of all pressed keys
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::A, "A", "a");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::B, "B", "b");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::C, "C", "c");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::D, "D", "d");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::E, "E", "e");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::F, "F", "f");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::G, "G", "g");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::H, "H", "h");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::I, "I", "i");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::J, "J", "j");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::K, "K", "k");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::L, "L", "l");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::M, "M", "m");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::N, "N", "n");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::O, "O", "o");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::P, "P", "p");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::Q, "Q", "q");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::R, "R", "r");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::S, "S", "s");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::T, "T", "t");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::U, "U", "u");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::V, "V", "v");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::W, "W", "w");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::X, "X", "x");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::Y, "Y", "y");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                handleCharacterInput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::Z, "Z", "z");
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                handleCharacterDeput(aKeyWasPressed, characters_for_entered_name, sf::Keyboard::BackSpace);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && characters_for_entered_name.size() > 1) {
                game_state = "Game";
                welcome_window.close();
            }
            else {
                aKeyWasPressed = false;
            }

            //For loop to construct entered name from vector
            for (int i = 0; i < characters_for_entered_name.size(); i++) {
                entered_name += characters_for_entered_name[i];
            }

            //Generating and Displaying entered name text
            sf::Text entered_name_text;
            setText(entered_name_text, text_x_pos_enteredname, text_y_pos_enteredname, font, entered_name, 18, sf::Color::Yellow);
            welcome_window.clear(sf::Color::Blue);
            welcome_window.draw(welcome_text);
            welcome_window.draw(enter_name_text);
            welcome_window.draw(entered_name_text);
            welcome_window.display();
        }

        //Starting Actual Game
        if (game_state == "Game" && gaming) {
            sf::RenderWindow game_window(sf::VideoMode(col_width1, row_height1), "Game");

            //Vector filled with Tiles to act as board
            std::vector<std::vector<Tile*>> board;
            for (int col = 0; col < colCount; col++) {
                std::vector<Tile*> tiles;
                for (int row = 0; row < rowCount; row++) {
                    Tile* ptr = new Tile(col,row, tile_hidden_sprite, tile_revealed_sprite, mine_sprite, flag_sprite, num_one_sprite, num_two_sprite, num_three_sprite, num_four_sprite, num_five_sprite, num_six_sprite, num_seven_sprite, num_eight_sprite);
                    tiles.push_back(ptr);
                }
                board.push_back(tiles);
            }

            //Setting Up The Play Board and Bombs
            std::vector<Tile*> bombs;
            std::vector<std::vector<int>> pairings;
            for (int i = 0; bombs.size() != mineCount; i++) {
                std::vector<int> pair;
                int x = distribx(gen);
                int y = distriby(gen);
                pair.push_back(x);
                pair.push_back(y);
                if (i == 0) {
                    pairings.push_back(pair);
                }else {
                    int counter = 0;
                    for (int j = 0; j < pairings.size(); j++) {
                        if (pairings[j] == pair) {
                            break;
                        }
                        counter += 1;
                    }
                    if (counter == pairings.size()) {
                        board[x][y] -> AddMine();
                        bombs.push_back(board[x][y]);
                        pairings.push_back(pair);
                    }
                }
            }
            pairings.clear();


            //Adding Neighbors
            for (int col = 0; col < colCount; col++) {
                for (int row = 0; row < rowCount; row++) {
                    board[col][row] -> AddNeighbours(board, colCount, rowCount);
                }
            }

            //Counting Adjacent Bombs
            for (int col = 0; col < colCount; col++) {
                for (int row = 0; row < rowCount; row++) {
                    board[col][row] -> CountAdjacentBombs();
                }
            }

            //Bool to prevent Mouse Spam
            bool Mouse_was_pressed = false;

            //Bool for debug mode
            bool debug = false;

            //Bool for Game Over
            bool game_over = false;

            //Bool for Game Won
            bool game_won = false;

            //Counter to Check Win Condition
            int num_of_revealed_tiles = 0;

            //Clock For Time
            sf::Clock c;

            //Bool for Pause_Status
            bool pause = false;


            //Main Gameplay Loop
            while (gaming) {

                //Closing Condition for Game Screen
                sf::Event second_screen;
                while(game_window.pollEvent(second_screen)) {
                    if(second_screen.type == sf::Event::Closed) {
                        gaming = false;
                        playing = false;
                        appendtoleaderboard(top_five_names, top_five_times_string);
                        game_window.close();
                        return 0;
                    }

                    //All Left-Click Functionalties
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        if (!Mouse_was_pressed) {
                            Mouse_was_pressed = true;
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(game_window);
                            int x = mousePosition.x / 32;
                            int y = mousePosition.y / 32;

                            //Checks if tile is clicked
                            if (( x < colCount) && ( y < rowCount)) {
                                if (board[x][y] -> GetFlagStatus() != true) {
                                    revealothermines(board[x][y]);
                                    if (board[x][y] -> GetMineStatus() == true) {
                                        game_over = true;
                                        debug = false;
                                    }
                                }
                            }

                            //Checks if debug is clicked
                            else if ( mousePosition.x >= debug_button_postionx && mousePosition.x <= debug_button_postionx + 64 && mousePosition.y >= debug_button_postiony && mousePosition.y <= debug_button_postiony + 64) {
                                if (debug == true) {
                                    debug = false;
                                }
                                else if (debug == false) {
                                    debug = true;
                                }
                            }

                            //Checks if Leadeboard Button is Clicked
                            else if (mousePosition.x >= leaderboard_postionx && mousePosition.x <= leaderboard_postionx  + 64 && mousePosition.y >= leaderboard_postiony && mousePosition.y <= leaderboard_postiony + 64) {
                                game_state_2 = "Leaderboard";
                            }
                            else if (mousePosition.x >= pause_postionx && mousePosition.x <= pause_postionx  + 64 && mousePosition.y >= pause_postiony && mousePosition.y <= pause_postiony + 64) {
                                game_window.draw(play_sprite);
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        game_window.draw(board[col][row] -> PauseTile());
                                    }
                                }
                                game_window.display();
                                pause = true;
                                Mouse_was_pressed = false;
                            }

                            //Checks if Reset button is Clicked
                            else if (mousePosition.x >= happy_face_postionx && mousePosition.x <= happy_face_postionx  + 64 && mousePosition.y >= happy_face_postiony && mousePosition.y <= happy_face_postiony + 64) {

                                //Clear board and bombs
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        delete board[col][row];
                                    }
                                }
                                board.clear();
                                bombs.clear();
                                estimated_mine_count = mineCount;
                                c.restart();

                                //Remake the board and Heap
                                for (int col = 0; col < colCount; col++) {
                                    std::vector<Tile*> tiles;
                                    for (int row = 0; row < rowCount; row++) {
                                        Tile* ptr = new Tile(col,row, tile_hidden_sprite, tile_revealed_sprite, mine_sprite, flag_sprite, num_one_sprite, num_two_sprite, num_three_sprite, num_four_sprite, num_five_sprite, num_six_sprite, num_seven_sprite, num_eight_sprite);
                                        tiles.push_back(ptr);
                                    }
                                    board.push_back(tiles);
                                }

                                //Redistribute Mines
                                for (int i = 0; bombs.size() != mineCount; i++) {
                                    std::vector<int> pair;
                                    int x = distribx(gen);
                                    int y = distriby(gen);
                                    pair.push_back(x);
                                    pair.push_back(y);
                                    if (i == 0) {
                                        pairings.push_back(pair);
                                    }else {
                                        int counter = 0;
                                        for (int j = 0; j < pairings.size(); j++) {
                                            if (pairings[j] == pair) {
                                                break;
                                            }
                                            counter += 1;
                                        }
                                        if (counter == pairings.size()) {
                                            board[x][y] -> AddMine();
                                            bombs.push_back(board[x][y]);
                                            pairings.push_back(pair);
                                        }
                                    }
                                }
                                pairings.clear();

                                //Read neighbors
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        board[col][row] -> AddNeighbours(board, colCount, rowCount);
                                    }
                                }

                                //Recount Adjacent Bombs
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        board[col][row] -> CountAdjacentBombs();
                                    }
                                }

                                //Reset Win Condition Counters
                                num_of_revealed_tiles = 0;
                            }
                        }
                        else {
                            continue;
                        }
                    }

                    //All Right-Click Functionaltites
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                        if (!Mouse_was_pressed) {
                            Mouse_was_pressed = true;
                            sf::Vector2i mousePosition = sf::Mouse::getPosition(game_window);
                            int x = mousePosition.x / 32;
                            int y = mousePosition.y / 32;

                            //Flag Functionalties
                            if (( x < colCount) && ( y < rowCount)) {
                                if (board[x][y] -> GetFlagStatus() == true) {
                                    board[x][y] -> RemoveFlag();
                                    estimated_mine_count += 1;
                                }else {
                                    board[x][y] -> AddFlag();
                                    estimated_mine_count -= 1;
                                }
                            }
                            else {
                                continue;
                            }
                        }
                    }
                    else {
                        Mouse_was_pressed = false;
                    }
                }

                //Clear board for white background
                game_window.clear(sf::Color::White);


                //Counter Stuff
                    std::string estimated_mine_count_string = std::to_string(estimated_mine_count);
                    std::vector<char> each_digit;
                    bool negative = false;
                    int length_to_add = 3 - estimated_mine_count_string.size();
                    for (int i = 0; i < estimated_mine_count_string.length(); i++) {
                        each_digit.push_back(estimated_mine_count_string[i]);
                    }
                    if (estimated_mine_count_string[0] == '-') {
                        negative = true;
                    }
                    if (length_to_add == 1 && !negative) {
                        each_digit.insert(each_digit.begin(), '0');
                    }
                    if (length_to_add == 2 && !negative) {
                        each_digit.insert(each_digit.begin(), '0');
                        each_digit.insert(each_digit.begin(), '0');
                    }
                    if (length_to_add < 0 && !negative) {
                        each_digit.insert(each_digit.begin(), '0');
                        each_digit.insert(each_digit.begin(), '-');
                    }
                    if (negative) {
                        while (each_digit.size() < 4) {
                            each_digit.insert(each_digit.begin() + 1, '0');
                        }
                    }
                    for (int i = 0; i < each_digit.size(); i++) {
                        if (each_digit[i] == '-') {
                            if (!negative) {
                                counter_digits[10].setPosition(12, 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[10]);
                            }else {
                                counter_digits[10].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[10]);
                            }

                        }

                        if (each_digit[i] == '0') {
                            if (!negative) {
                                counter_digits[0].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[0]);
                            }else {
                                counter_digits[0].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[0]);
                            }
                        }

                        if (each_digit[i] == '1') {
                            if (!negative) {
                                counter_digits[1].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[1]);
                            }else {
                                counter_digits[1].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[1]);
                            }
                        }

                        if (each_digit[i] == '2') {
                            if (!negative) {
                                counter_digits[2].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[2]);
                            }else {
                                counter_digits[2].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[2]);
                            }
                        }

                        if (each_digit[i] == '3') {
                            if (!negative) {
                                counter_digits[3].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[3]);
                            }else {
                                counter_digits[3].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[3]);
                            }
                        }

                        if (each_digit[i] == '4') {
                            if (!negative) {
                                counter_digits[4].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[4]);
                            }else {
                                counter_digits[4].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[4]);
                            }
                        }

                        if (each_digit[i] == '5') {
                            if (!negative) {
                                counter_digits[5].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[5]);
                            }else {
                                counter_digits[5].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[5]);
                            }
                        }
                        if (each_digit[i] == '6') {
                            if (!negative) {
                                counter_digits[6].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[6]);
                            }else {
                                counter_digits[6].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[6]);
                            }

                        }
                        if (each_digit[i] == '7') {
                            if (!negative) {
                                counter_digits[7].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[7]);
                            }else {
                                counter_digits[7].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[7]);
                            }

                        }
                        if (each_digit[i] == '8') {
                            if (!negative) {
                                counter_digits[8].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[8]);
                            }else {
                                counter_digits[8].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[8]);
                            }
                        }

                        if (each_digit[i] == '9') {
                            if (!negative) {
                                counter_digits[9].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[9]);
                            }else {
                                counter_digits[9].setPosition(12+(21*i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[9]);
                            }
                        }
                    }


                //Timer
                    if (true) {
                        int time = (int)c.getElapsedTime().asSeconds();
                        int minutes = time / 60;
                        int seconds = time % 60;
                        std::string minutes_str = std::to_string(minutes);
                        std::string seconds_str = std::to_string(seconds);
                        std::vector<char> time_values;

                        if (minutes_str.length() == 1) {
                            minutes_str = "0" + minutes_str;
                        }
                        if (seconds_str.length() == 1) {
                            seconds_str = "0" + seconds_str;
                        }
                        for (char digit : minutes_str) {
                            time_values.push_back(digit);
                        }
                        for (char digit : seconds_str) {
                            time_values.push_back(digit);
                        }
                        for (int i = 0; i < time_values.size(); i++) {

                            if (time_values[i] == '0') {
                                if (i <= 1) {
                                    timer_digits[0].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[0]);
                                } else {
                                    timer_digits[0].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[0]);
                                }
                            }
                            if (time_values[i] == '1') {
                                if (i <= 1) {
                                    timer_digits[1].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[1]);
                                } else {
                                    timer_digits[1].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[1]);
                                }
                            }
                            if (time_values[i] == '2') {
                                if (i <= 1) {
                                    timer_digits[2].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[2]);
                                } else {
                                    timer_digits[2].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[2]);
                                }
                            }
                            if (time_values[i] == '3') {
                                if (i <= 1) {
                                    timer_digits[3].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[3]);
                                } else {
                                    timer_digits[3].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[3]);
                                }
                            }
                            if (time_values[i] == '4') {
                                if (i <= 1) {
                                    timer_digits[4].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[4]);
                                } else {
                                    timer_digits[4].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[4]);
                                }
                            }
                            if (time_values[i] == '5') {
                                if (i <= 1) {
                                    timer_digits[5].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[5]);
                                } else {
                                    timer_digits[5].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[5]);
                                }
                            }
                            if (time_values[i] == '6') {
                                if (i <= 1) {
                                    timer_digits[6].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[6]);
                                } else {
                                    timer_digits[6].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[6]);
                                }
                            }
                            if (time_values[i] == '7') {
                                if (i <= 1) {
                                    timer_digits[7].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[7]);
                                } else {
                                    timer_digits[7].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[7]);
                                }
                            }
                            if (time_values[i] == '8') {
                                if (i <= 1) {
                                    timer_digits[8].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[8]);
                                } else {
                                    timer_digits[8].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[8]);
                                }
                            }
                            if (time_values[i] == '9') {
                                if (i <= 1) {
                                    timer_digits[9].setPosition((colCount * 32) - 97 +(21 * i), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[9]);
                                } else {
                                    timer_digits[9].setPosition((colCount * 32) - 54 +(21 * (i - 2)), 32 * (rowCount + 0.5) + 16);
                                    game_window.draw(timer_digits[9]);
                                }
                            }
                        }
                    }


                //Pause Function
                while (pause == true) {
                    std::string state = "None";

                    //Checking For Click or if window is closed
                    while(game_window.pollEvent(second_screen)) {
                        if(second_screen.type == sf::Event::Closed) {
                            gaming = false;
                            playing = false;
                            appendtoleaderboard(top_five_names, top_five_times_string);
                            game_window.close();
                            return 0;
                        }
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            if (!Mouse_was_pressed) {
                                Mouse_was_pressed = true;
                                sf::Vector2i mousePosition3 = sf::Mouse::getPosition(game_window);

                                //Unpause State
                                if (mousePosition3.x >= pause_postionx && mousePosition3.x <= pause_postionx  + 64 && mousePosition3.y >= pause_postiony && mousePosition3.y <= pause_postiony + 64) {
                                    state = "State 1";
                                }

                                //Reset State
                                else if (mousePosition3.x >= happy_face_postionx && mousePosition3.x <= happy_face_postionx  + 64 && mousePosition3.y >= happy_face_postiony && mousePosition3.y <= happy_face_postiony + 64) {
                                    state = "State 2";
                                }

                                //Leaderboard State
                                else if (mousePosition3.x >= leaderboard_postionx && mousePosition3.x <= leaderboard_postionx  + 64 && mousePosition3.y >= leaderboard_postiony && mousePosition3.y <= leaderboard_postiony + 64) {
                                    state = "State 3";
                                }
                            }
                        }else {
                            Mouse_was_pressed = false;
                        }

                        //Play functionalities
                        if (state == "State 1") {
                            pause = false;
                            game_window.draw(pause_sprite);
                            game_window.display();
                        }


                        //Reset Functionalties
                        if (state == "State 2") {

                                //Clear board and bombs
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        delete board[col][row];
                                    }
                                }
                                board.clear();
                                bombs.clear();
                                estimated_mine_count = mineCount;
                                c.restart();

                                //Remake the board and Heap
                                for (int col = 0; col < colCount; col++) {
                                    std::vector<Tile*> tiles;
                                    for (int row = 0; row < rowCount; row++) {
                                        Tile* ptr = new Tile(col,row, tile_hidden_sprite, tile_revealed_sprite, mine_sprite, flag_sprite, num_one_sprite, num_two_sprite, num_three_sprite, num_four_sprite, num_five_sprite, num_six_sprite, num_seven_sprite, num_eight_sprite);
                                        tiles.push_back(ptr);
                                    }
                                    board.push_back(tiles);
                                }

                                //Redistribute Mines
                                for (int i = 0; bombs.size() != mineCount; i++) {
                                    std::vector<int> pair;
                                    int x = distribx(gen);
                                    int y = distriby(gen);
                                    pair.push_back(x);
                                    pair.push_back(y);
                                    if (i == 0) {
                                        pairings.push_back(pair);
                                    }else {
                                        int counter = 0;
                                        for (int j = 0; j < pairings.size(); j++) {
                                            if (pairings[j] == pair) {
                                                break;
                                            }
                                            counter += 1;
                                        }
                                        if (counter == pairings.size()) {
                                            board[x][y] -> AddMine();
                                            bombs.push_back(board[x][y]);
                                            pairings.push_back(pair);
                                        }
                                    }
                                }
                                pairings.clear();

                                //Read neighbors
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        board[col][row] -> AddNeighbours(board, colCount, rowCount);
                                    }
                                }

                                //Recount Adjacent Bombs
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        board[col][row] -> CountAdjacentBombs();
                                    }
                                }

                                //Reset Win Condition Counters
                                num_of_revealed_tiles = 0;
                        }

                        //Leaderboard Functionalties
                        if (state == "State 3") {
                            for (int col = 0; col < colCount; col++) {
                                for (int row = 0; row < rowCount; row++) {
                                    game_window.draw(board[col][row] -> PauseTile());
                                }
                            }
                            if (game_over == true) {
                                game_window.draw(face_lose_sprite);
                            }else if (game_won == true) {
                                game_window.draw(face_won_sprite);
                            }else {
                                game_window.draw(face_happy_sprite);
                            }
                            game_window.draw(debug_button_sprite);
                            game_window.draw(play_sprite);
                            game_window.draw(leaderboard_sprite);
                            game_window.display();
                            sf::RenderWindow leaderboard_window(sf::VideoMode(col_width2, row_height2), "Leaderboard");
                            float text_x_pos_leaderboard = col_width2/2;
                            float text_y_pos_leaderboard = (row_height2/2) - 120;
                            sf::Text leaderboard_text;
                            setText(leaderboard_text, text_x_pos_leaderboard, text_y_pos_leaderboard, font, "LEADERBOARD", 20, sf::Color::White);
                            leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                            float text_x_pos_leaderboard_rankings = col_width2/2;
                            float text_y_pos_leaderboard_rankings = (row_height2/2) + 20;

                            std::string rankings_string = "";
                            int counter = 1;
                            while (counter < 6) {
                                rankings_string += std::to_string(counter) + ".";
                                rankings_string += "\t";
                                rankings_string += top_five_times_string[counter - 1];
                                rankings_string += "\t";
                                rankings_string += top_five_names[counter - 1];
                                rankings_string += "\n";
                                rankings_string += "\n";
                                counter++;
                            }

                            sf::Text leaderboard_rankings_text;
                            setText(leaderboard_rankings_text, text_x_pos_leaderboard_rankings , text_y_pos_leaderboard_rankings, font, rankings_string, 18, sf::Color::White);
                            leaderboard_rankings_text.setStyle(sf::Text::Bold);

                            while (leaderboard_window.isOpen()) {
                                //Closing Condition for Leaderboard Screen
                                sf::Event third_screen;
                                while(leaderboard_window.pollEvent(third_screen)) {
                                    if(third_screen.type == sf::Event::Closed) {
                                        game_state_2 = "None";
                                        leaderboard_window.close();
                                    }
                                }

                                leaderboard_window.clear(sf::Color::Blue);
                                leaderboard_window.draw(leaderboard_rankings_text);
                                leaderboard_window.draw(leaderboard_text);
                                leaderboard_window.display();
                            }
                            std::ofstream leaderboard_append_file;
                            leaderboard_append_file.open("files/leaderboard.txt");
                            if (!leaderboard_append_file.is_open()) {
                                std::cerr << "Unable to open Leaderboard file";
                            }

                            //Writing top 5 to leaderboard.txt
                            appendtoleaderboard(top_five_names, top_five_times_string);
                        }
                        state = "None";
                }
            }

                //Printing out UI elements
                if (game_over == true) {
                    game_window.draw(face_lose_sprite);
                }else if (game_won == true) {
                    game_window.draw(face_won_sprite);
                }else {
                    game_window.draw(face_happy_sprite);
                }
                game_window.draw(debug_button_sprite);
                game_window.draw(pause_sprite);
                game_window.draw(leaderboard_sprite);

                //Important for Win Condition
                num_of_revealed_tiles = 0;

                //Printing out Tiles
                for (int col = 0; col < colCount; col++) {
                    for (int row = 0; row < rowCount; row++) {
                        if (debug == false && game_over == false) {
                            if (board[col][row] -> GetMineStatus() == false && board[col][row] -> GetRevealStatus() == true) {
                                num_of_revealed_tiles += 1;
                            }
                            game_window.draw(board[col][row] -> GetBlockSprite());
                            game_window.draw(board[col][row] -> TileReveal());
                        }else if (debug == true && game_over == false) {
                            if (board[col][row] -> GetMineStatus() == false && board[col][row] -> GetRevealStatus() == true) {
                                num_of_revealed_tiles += 1;
                            }
                            game_window.draw(board[col][row] -> GetBlockSprite());
                            game_window.draw(board[col][row] -> RevealMine(debug));
                        }
                    }
                }

                //Checking If Win Condition is Met
                if (num_of_revealed_tiles == (colCount * rowCount) - mineCount) {
                    game_won = true;
                    debug = false;
                }

                //Displaying Win Board
                if (game_won == true) {
                    game_window.draw(face_won_sprite);
                    game_window.draw(debug_button_sprite);
                    game_window.draw(pause_sprite);
                    game_window.draw(leaderboard_sprite);
                    for (int col = 0; col < colCount; col++) {
                        for (int row = 0; row < rowCount; row++) {
                            game_window.draw(board[col][row] -> GetBlockSprite());
                            game_window.draw(board[col][row] -> TileReveal());
                        }
                    }
                    for (Tile* bomb : bombs) {
                        game_window.draw(bomb -> RevealFlag());
                    }
                }

                    //Leaderboard Functionalities
                    if (game_won == true) {

                        //Getting Player Time
                        std::string player_time = "";
                        if (game_won == true) {
                            int time = (int)c.getElapsedTime().asSeconds();
                            int minutes = time / 60;
                            int seconds = time % 60;
                            std::string minutes_str = std::to_string(minutes);
                            std::string seconds_str = std::to_string(seconds);
                            if (minutes_str.length() == 1) {
                                minutes_str = "0" + minutes_str;
                            }
                            if (seconds_str.length() == 1) {
                                seconds_str = "0" + seconds_str;
                            }
                            player_time += minutes_str + ":" + seconds_str;
                        }

                        //Time Comparison Process
                        int player_first_digit = (int)player_time[0];
                        int player_second_digit = (int)player_time[1];
                        int player_third_digit = (int)player_time[3];
                        int player_fourth_digit = (int)player_time[4];
                        int placement;
                        for (int i = 4; i >= 0; i--) {
                            int first_digit = (int)top_five_times_string[i][0];
                            int second_digit = (int)top_five_times_string[i][1];
                            int third_digit = (int)top_five_times_string[i][3];
                            int fourth_digit = (int)top_five_times_string[i][4];
                            if (player_first_digit < first_digit) {
                                placement = i;
                                continue;
                            }
                            if (player_first_digit == first_digit) {
                                if (player_second_digit < second_digit) {
                                    placement = i;
                                    continue;
                                }
                                if (player_second_digit == second_digit) {
                                    if (player_third_digit < third_digit) {
                                        placement = i;
                                        continue;
                                    }
                                    if (player_third_digit == third_digit) {
                                        if (player_fourth_digit < fourth_digit) {
                                            placement = i;
                                            continue;
                                        }
                                        if (player_fourth_digit == fourth_digit) {
                                            placement = i;
                                            continue;
                                        }
                                    }
                                }
                            }
                        }

                        //Shifting all previous values that are less than the placement time
                        if (placement < 5) {
                            for (int i = 4; i > placement; i--) {
                                top_five_times_string[i] = top_five_times_string[i - 1];
                                top_five_names[i] = top_five_names[i - 1];
                            }
                        }

                        //Appending Player Time to Top 5 List
                        top_five_times_string[placement] = player_time;

                        //Constructing and Appending Player Name to Top 5 List
                        std::string player_name = "";
                        if (characters_for_entered_name.size() > 2) {
                            for (int i = 0; i < characters_for_entered_name.size() - 1; i++) {
                                player_name += characters_for_entered_name[i];
                            }
                        }else if (characters_for_entered_name.size() == 2) {
                            player_name += characters_for_entered_name[0];
                        }
                        top_five_names[placement] = " "+player_name +"*";
                    }

                    //Leaderboard Functionalities
                    if (game_state_2 == "Leaderboard") {
                        for (int col = 0; col < colCount; col++) {
                            for (int row = 0; row < rowCount; row++) {
                                game_window.draw(board[col][row] -> PauseTile());
                            }
                        }
                        game_window.display();
                        sf::RenderWindow leaderboard_window(sf::VideoMode(col_width2, row_height2), "Leaderboard");

                        float text_x_pos_leaderboard = col_width2/2;
                        float text_y_pos_leaderboard = (row_height2/2) - 120;
                        sf::Text leaderboard_text;
                        setText(leaderboard_text, text_x_pos_leaderboard, text_y_pos_leaderboard, font, "LEADERBOARD", 20, sf::Color::White);
                        leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                        float text_x_pos_leaderboard_rankings = col_width2/2;
                        float text_y_pos_leaderboard_rankings = (row_height2/2) + 20;

                        std::string rankings_string = "";
                        int counter = 1;
                        while (counter < 6) {
                            rankings_string += std::to_string(counter) + ".";
                            rankings_string += "\t";
                            rankings_string += top_five_times_string[counter - 1];
                            rankings_string += "\t";
                            rankings_string += top_five_names[counter - 1];
                            rankings_string += "\n";
                            rankings_string += "\n";
                            counter++;
                        }

                        sf::Text leaderboard_rankings_text;
                        setText(leaderboard_rankings_text, text_x_pos_leaderboard_rankings , text_y_pos_leaderboard_rankings, font, rankings_string, 18, sf::Color::White);
                        leaderboard_rankings_text.setStyle(sf::Text::Bold);

                        while (leaderboard_window.isOpen()) {
                            //Closing Condition for Leaderboard Screen
                            sf::Event third_screen;
                            while(leaderboard_window.pollEvent(third_screen)) {
                                if(third_screen.type == sf::Event::Closed) {
                                    game_state_2 = "None";
                                    leaderboard_window.close();
                                }
                            }

                            leaderboard_window.clear(sf::Color::Blue);
                            leaderboard_window.draw(leaderboard_rankings_text);
                            leaderboard_window.draw(leaderboard_text);
                            leaderboard_window.display();
                        }
                        std::ofstream leaderboard_append_file;
                        leaderboard_append_file.open("files/leaderboard.txt");
                        if (!leaderboard_append_file.is_open()) {
                            std::cerr << "Unable to open Leaderboard file";
                        }

                        //Writing top 5 to leaderboard.txt
                        appendtoleaderboard(top_five_names, top_five_times_string);
                    }

                //Game Over Screen and Game Won Screen Functionalities
                        while (game_over == true || game_won == true) {
                            for (int i = 0; i < 3; i++) {
                                counter_digits[0].setPosition(33 + (21 * i), 32 * (rowCount + 0.5) + 16);
                                game_window.draw(counter_digits[0]);
                            }
                            while(game_window.pollEvent(second_screen)) {
                                if(second_screen.type == sf::Event::Closed) {
                                    gaming = false;
                                    playing = false;
                                    appendtoleaderboard(top_five_names, top_five_times_string);
                                    game_window.close();
                                    return 0;
                                }
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                                if (!Mouse_was_pressed) {
                                    Mouse_was_pressed = true;
                                    sf::Vector2i mousePosition3 = sf::Mouse::getPosition(game_window);
                                    if (mousePosition3.x >= happy_face_postionx && mousePosition3.x <= happy_face_postionx  + 64 && mousePosition3.y >= happy_face_postiony && mousePosition3.y <= happy_face_postiony + 64) {
                                        game_over = false;
                                        game_won = false;

                                        //Clear board and bombs and Heap
                                        for (int col = 0; col < colCount; col++) {
                                            for (int row = 0; row < rowCount; row++) {
                                                delete board[col][row];
                                            }
                                        }
                                        board.clear();
                                        bombs.clear();
                                        c.restart();
                                        estimated_mine_count = mineCount;

                                        //Remake the board
                                        for (int col = 0; col < colCount; col++) {
                                            std::vector<Tile*> tiles;
                                            for (int row = 0; row < rowCount; row++) {
                                                Tile* ptr = new Tile(col,row, tile_hidden_sprite, tile_revealed_sprite, mine_sprite, flag_sprite, num_one_sprite, num_two_sprite, num_three_sprite, num_four_sprite, num_five_sprite, num_six_sprite, num_seven_sprite, num_eight_sprite);
                                                tiles.push_back(ptr);
                                            }
                                            board.push_back(tiles);
                                        }

                                        //Redistribute Mines
                                        for (int i = 0; bombs.size() != mineCount; i++) {
                                            std::vector<int> pair;
                                            int x = distribx(gen);
                                            int y = distriby(gen);
                                            pair.push_back(x);
                                            pair.push_back(y);
                                            if (i == 0) {
                                                pairings.push_back(pair);
                                            }else {
                                                int counter = 0;
                                                for (int j = 0; j < pairings.size(); j++) {
                                                    if (pairings[j] == pair) {
                                                        break;
                                                    }
                                                    counter += 1;
                                                }
                                                if (counter == pairings.size()) {
                                                    board[x][y] -> AddMine();
                                                    bombs.push_back(board[x][y]);
                                                    pairings.push_back(pair);
                                                }
                                            }
                                        }
                                        pairings.clear();

                                        //Re-read neighbors
                                        for (int col = 0; col < colCount; col++) {
                                            for (int row = 0; row < rowCount; row++) {
                                                board[col][row] -> AddNeighbours(board, colCount, rowCount);
                                            }
                                        }

                                        //Recount Adjacent Bombs
                                        for (int col = 0; col < colCount; col++) {
                                            for (int row = 0; row < rowCount; row++) {
                                                board[col][row] -> CountAdjacentBombs();
                                            }
                                        }

                                        //Reset Win Condition Counters
                                        num_of_revealed_tiles = 0;

                                    }else if (mousePosition3.x >= leaderboard_postionx && mousePosition3.x <= leaderboard_postionx  + 64 && mousePosition3.y >= leaderboard_postiony && mousePosition3.y <= leaderboard_postiony + 64){
                                        for (int col = 0; col < colCount; col++) {
                                            for (int row = 0; row < rowCount; row++) {
                                                game_window.draw(board[col][row] -> PauseTile());
                                            }
                                        }
                                        game_window.display();
                                        sf::RenderWindow leaderboard_window(sf::VideoMode(col_width2, row_height2), "Leaderboard");
                                        float text_x_pos_leaderboard = col_width2/2;
                                        float text_y_pos_leaderboard = (row_height2/2) - 120;
                                        sf::Text leaderboard_text;
                                        setText(leaderboard_text, text_x_pos_leaderboard, text_y_pos_leaderboard, font, "LEADERBOARD", 20, sf::Color::White);
                                        leaderboard_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                                        float text_x_pos_leaderboard_rankings = col_width2/2;
                                        float text_y_pos_leaderboard_rankings = (row_height2/2) + 20;

                                        std::string rankings_string = "";
                                        int counter = 1;
                                        while (counter < 6) {
                                            rankings_string += std::to_string(counter) + ".";
                                            rankings_string += "\t";
                                            rankings_string += top_five_times_string[counter - 1];
                                            rankings_string += "\t";
                                            rankings_string += top_five_names[counter - 1];
                                            rankings_string += "\n";
                                            rankings_string += "\n";
                                            counter++;
                                        }

                                        sf::Text leaderboard_rankings_text;
                                        setText(leaderboard_rankings_text, text_x_pos_leaderboard_rankings , text_y_pos_leaderboard_rankings, font, rankings_string, 18, sf::Color::White);
                                        leaderboard_rankings_text.setStyle(sf::Text::Bold);

                                        while (leaderboard_window.isOpen()) {
                                            //Closing Condition for Leaderboard Screen
                                            sf::Event third_screen;
                                            while(leaderboard_window.pollEvent(third_screen)) {
                                                if(third_screen.type == sf::Event::Closed) {
                                                    game_state_2 = "None";
                                                    leaderboard_window.close();
                                                }
                                            }

                                            leaderboard_window.clear(sf::Color::Blue);
                                            leaderboard_window.draw(leaderboard_rankings_text);
                                            leaderboard_window.draw(leaderboard_text);
                                            leaderboard_window.display();
                                        }

                                        //Writing top 5 to leaderboard.txt
                                        appendtoleaderboard(top_five_names, top_five_times_string);
                                    }
                                }
                            }else {
                                Mouse_was_pressed = false;
                            }
                            }

                            //Drawing Bombs for Game Over
                            if (game_over == true) {
                                game_window.draw(face_lose_sprite);
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        game_window.draw(board[col][row] -> GetBlockSprite());
                                        game_window.draw(board[col][row] -> TileReveal());

                                    }
                                }
                                for (Tile* bomb : bombs) {
                                    game_window.draw(bomb -> GetBomb());
                                }
                            }

                            //Drawing Flags for Game Won
                            else if (game_won == true) {
                                game_window.draw(face_won_sprite);
                                for (int col = 0; col < colCount; col++) {
                                    for (int row = 0; row < rowCount; row++) {
                                        game_window.draw(board[col][row] -> GetBlockSprite());
                                        game_window.draw(board[col][row] -> TileReveal());
                                    }
                                }
                                for (Tile* bomb : bombs) {
                                    game_window.draw(bomb -> RevealFlag());
                                }
                            }
                            game_window.display();
                        }
                game_window.display();
            }
        }
    }
    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.