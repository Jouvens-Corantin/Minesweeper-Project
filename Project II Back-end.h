#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef PROJECT_II_BACK_END_H
#define PROJECT_II_BACK_END_H

//Sets text
void setText(sf::Text &text, float x, float y, sf::Font &font, std::string words, int size, sf::Color color){
    text.setFont(font);
    text.setString(words);
    text.setCharacterSize(size);
    text.setFillColor(color);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width/2.0f,textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
};

//Adds Characters to entered name
void handleCharacterInput(bool& keyWasPressed, std::vector<std::string>& characters, sf::Keyboard::Key key, const std::string& upperChar, const std::string& lowerChar){
    if (sf::Keyboard::isKeyPressed(key)) {
        if (!keyWasPressed) {
            keyWasPressed = true;
            if (characters.size() < 11) {
                if (characters.size() == 1) {
                    characters.insert(characters.begin(),upperChar);
                }else {
                    characters.insert(characters.begin() + characters.size() - 1,lowerChar);
                }
            }
        }
    }else {
        keyWasPressed = false;
    }
};

//Removes characters from entered name
void handleCharacterDeput(bool& keyWasPressed, std::vector<std::string>& characters, sf::Keyboard::Key key) {
    if (sf::Keyboard::isKeyPressed(key)) {
        if (key == sf::Keyboard::BackSpace) {
            if (!keyWasPressed) {
                keyWasPressed = true;
                if (characters.size() == 1) {
                    characters[0] = "|";
                } else {
                    characters.erase(characters.end() - 2);
                }
            }
        }
    }
    else {
        keyWasPressed = false;
    }
};


//Class for each tile on the board
class Tile {

    //All of our sprites
    private:
    int _column_position;
    int _row_position;
    sf::Sprite tile_hidden;
    sf::Sprite tile_revealed;
    sf::Sprite minesprite;
    sf::Sprite flag;
    sf::Sprite num_1;
    sf::Sprite num_2;
    sf::Sprite num_3;
    sf::Sprite num_4;
    sf::Sprite num_5;
    sf::Sprite num_6;
    sf::Sprite num_7;
    sf::Sprite num_8;
    bool revealed = false;
    bool mine = false;
    bool present_flag = false;
    std::vector<Tile*> neighbors;
    int adjacent_bombs = 0;


    public:
    //Construction with all of the needed sprites
    Tile(int column_position, int row_position, sf::Sprite& tile_hidden_sprite, sf::Sprite& tile_revealed_sprite, sf::Sprite& mine_sprite, sf::Sprite& flag_sprite, sf::Sprite& num_1_sprite, sf::Sprite& num_2_sprite, sf::Sprite& num_3_sprite, sf::Sprite& num_4_sprite, sf::Sprite& num_5_sprite, sf::Sprite& num_6_sprite, sf::Sprite& num_7_sprite, sf::Sprite& num_8_sprite) {
        _column_position = column_position;
        _row_position = row_position;
        tile_hidden = tile_hidden_sprite;
        tile_revealed = tile_revealed_sprite;
        minesprite = mine_sprite;
        flag = flag_sprite;
        num_1 = num_1_sprite;
        num_2 = num_2_sprite;
        num_3 = num_3_sprite;
        num_4 = num_4_sprite;
        num_5 = num_5_sprite;
        num_6 = num_6_sprite;
        num_7 = num_7_sprite;
        num_8 = num_8_sprite;
        float tile_hidden_postionx = _column_position * 32.0f;
        float tile_hidden_postiony = _row_position * 32.0f;
        tile_hidden.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        tile_revealed.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        minesprite.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        flag.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_1.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_2.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_3.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_4.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_5.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_6.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_7.setPosition(tile_hidden_postionx, tile_hidden_postiony);
        num_8.setPosition(tile_hidden_postionx, tile_hidden_postiony);
    }

    //Gets tile Sprite
    sf::Sprite GetBlockSprite() {
        if (revealed == false) {
            return tile_hidden;
        } else{
            return tile_revealed;
        }
    }

    //Shows necessary sprite for tile
    sf::Sprite TileReveal(){
        if (present_flag == true && mine == true && revealed == false) {
            return flag;
        }
        else if (present_flag == true && revealed == false) {
            return flag;
        }else if (revealed == true && mine == true) {
            return minesprite;
        }else if (revealed == true && mine == false) {
            if (adjacent_bombs == 0) {
                return tile_revealed;
            }
            if (adjacent_bombs == 1) {
                return num_1;
            }
            if (adjacent_bombs == 2) {
                return num_2;
            }
            if (adjacent_bombs == 3) {
                return num_3;
            }
            if (adjacent_bombs == 4) {
                return num_4;
            }
            if (adjacent_bombs == 5) {
                return num_5;
            }
            if (adjacent_bombs == 6) {
                return num_6;
            }
            if (adjacent_bombs == 7) {
                return num_7;
            }
            if (adjacent_bombs == 8) {
                return num_8;
            }
        }
        return tile_hidden;
    }

    //Gets adjacent tiles
    void AddNeighbours(std::vector<std::vector<Tile*>>& board, int colnum, int rownum) {
        if (mine == false) {
            if (_column_position + 1 < colnum) {
                neighbors.push_back(board[_column_position + 1][_row_position]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_column_position - 1 >= 0) {
                neighbors.push_back(board[_column_position - 1][_row_position]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_column_position - 1 >= 0 && _row_position - 1  >= 0) {
                neighbors.push_back(board[_column_position - 1][_row_position - 1]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_column_position + 1 < colnum && _row_position + 1  < rownum) {
                neighbors.push_back(board[_column_position + 1][_row_position + 1]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_row_position - 1  >= 0) {
                neighbors.push_back(board[_column_position][_row_position - 1]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_column_position + 1 < colnum && _row_position - 1  >= 0) {
                neighbors.push_back(board[_column_position + 1][_row_position - 1]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_column_position - 1 >= 0 && _row_position + 1  < rownum) {
                neighbors.push_back(board[_column_position - 1][_row_position + 1]);
            }else {
                neighbors.push_back(nullptr);
            }

            if (_row_position + 1 < rownum) {
                neighbors.push_back(board[_column_position][_row_position + 1]);
            }else {
                neighbors.push_back(nullptr);
            }
        }

    }

    //Count how many bombs are adjacent
    void CountAdjacentBombs() {
        for (Tile* tile : neighbors) {
            if (tile != nullptr) {
                if (tile -> GetMineStatus() == true){
                    adjacent_bombs += 1;
                }
            }
        }
    }

    //Reveals tile
    void reveal() {
        if (present_flag == false){
            revealed = true;
        }
    }

    //Reveals only mines used in Lose Screen
    sf::Sprite RevealMine(bool debug) {
        if (present_flag == true && revealed == false && debug == true) {
            return flag;
        }else if (revealed == false && mine == true) {
            return minesprite;
        }
        else if (revealed == false && mine == true) {
            return minesprite;
        }else if (revealed == true && mine == true) {
            return minesprite;
        }else if (revealed == true && mine == false) {
            if (adjacent_bombs == 0) {
                return tile_revealed;
            }
            if (adjacent_bombs == 1) {
                return num_1;
            }
            if (adjacent_bombs == 2) {
                return num_2;
            }
            if (adjacent_bombs == 3) {
                return num_3;
            }
            if (adjacent_bombs == 4) {
                return num_4;
            }
            if (adjacent_bombs == 5) {
                return num_5;
            }
            if (adjacent_bombs == 6) {
                return num_6;
            }
            if (adjacent_bombs == 7) {
                return num_7;
            }
            if (adjacent_bombs == 8) {
                return num_8;
            }
        }
        return tile_hidden;
    }

    //Reveals only Flags used In Win Screen
    sf::Sprite RevealFlag() {
        if (mine == true && revealed == false) {
            return flag;
        }
        else if (present_flag == true && revealed == false) {
            return flag;
        }else if (revealed == true && mine == false) {
            if (adjacent_bombs == 0) {
                return tile_revealed;
            }
            if (adjacent_bombs == 1) {
                return num_1;
            }
            if (adjacent_bombs == 2) {
                return num_2;
            }
            if (adjacent_bombs == 3) {
                return num_3;
            }
            if (adjacent_bombs == 4) {
                return num_4;
            }
            if (adjacent_bombs == 5) {
                return num_5;
            }
            if (adjacent_bombs == 6) {
                return num_6;
            }
            if (adjacent_bombs == 7) {
                return num_7;
            }
            if (adjacent_bombs == 8) {
                return num_8;
            }
        }
        return tile_hidden;
    }


    //Getters, Setters, and additional Methods
    sf::Sprite GetFlag() {
        return flag;
    }

    sf::Sprite GetBomb() {
        return  minesprite;
    }

    void AddMine() {
        mine = true;
    }

    void AddFlag() {
        present_flag= true;
    }

    bool GetFlagStatus() {
        return present_flag;
    }

    void RemoveFlag() {
        present_flag = false;
    }

    bool GetMineStatus() {
        return mine;
    }

    bool GetRevealStatus() {
        return revealed;
    }

    int GetNumOfAdjacentBombs() {
        return adjacent_bombs;
    }

    std::vector<Tile*> GetNeighbors(){
        return neighbors;
    }

    //Shows Blank Tile for Pause Screen
    sf::Sprite PauseTile() {
        return tile_revealed;
    }

};


//Recursive Function to reveal multiple tiles off one click
void revealothermines(Tile* main_tile) {
    if (main_tile == nullptr) {
        return;
    }
    main_tile -> reveal();
    if (main_tile -> GetNumOfAdjacentBombs() == 0) {
        for (Tile* tile : main_tile -> GetNeighbors()) {
            if (tile != nullptr && tile -> GetRevealStatus() == false && tile -> GetMineStatus() == false && tile -> GetFlagStatus() == false) {
                revealothermines(tile);
            }
        }
    }
}

void appendtoleaderboard(std::string (&top_five_names1)[5], std::string (&top_five_times_string1)[5]) {
    std::ofstream leaderboard_append_file;
    leaderboard_append_file.open("files/leaderboard.txt");
    if (!leaderboard_append_file.is_open()) {
        std::cerr << "Unable to open Leaderboard file";
    }
    else {
        for (int i = 0; i < 5; i++) {
            if (top_five_names1[i].find("*") != std::string::npos) {
                std::string official_name = "";
                for (int j = 0; j < top_five_names1[i].length() -1; j++) {
                    official_name += top_five_names1[i][j];
                }
                leaderboard_append_file << top_five_times_string1[i] << "," << official_name << "\n";
            }else {
                leaderboard_append_file << top_five_times_string1[i] << "," << top_five_names1[i] << "\n";
            }
        }
    }
    leaderboard_append_file.close();
}


#endif //PROJECT_II_BACK_END_H
