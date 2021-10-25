#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <cmath>
#include <math.h>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include <ctime>
#include <sstream>
#include "Game.h"
#include "The_Name.h"
#include "Pause.h"
#include <fstream>
#define ll long long
#define  dou  double
#define en endl
#define bo bool
#define yest bool yes=true;
#define yesf bool yes=false;
#define space " "
#define txt freopen("input.txt", "rt", stdin);freopen("output.txt", "wt", stdout);
#define zezo_atef ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace std;
using namespace sf;
struct Bubble
{
    int color;
    Texture texture;
    Sprite sprite;
    bool found;
    Sprite Animation;
    bool one_by_one;
    bool one_by_one_pop;
    bool visited_anim = false;
};
void rand_color(); //line number : 151
void bubble_isfound(); // line number : 198
void draw_matrix(RenderWindow& game); // line number : 208
bool level_empty(); //line number : 325
void pop_end(RenderWindow& game); //line number : 338
bool valid(int x, int y); // line number : 505
int steps(int x, int y, int gridcolor, int& stepCounter); //line number : 510
void areaSearch(int x, int y, int gridcolor); //line number : 537
void animation(int poppedColor, RenderWindow& game); //line number : 566
void swap_bubbles();//line number : 630
void the_event(RenderWindow& game);//line number : 673
bool shift_done();//line number : 790
void shifting_bubbles(RenderWindow& game);//line number : 822
void Target();//line number : 874
void declare();//line number : 885
void color_correction();//line number : 1060
void grid_color(Bubble(&grid)[10][10], RenderWindow& game);//line number : 1084
void crush_grid(Bubble(&grid)[10][10], RenderWindow& game);//line number : 1294
void virus_color(Bubble(&grid)[10][10], RenderWindow& game);//line number : 1516
int NumberOfZeros();//line number : 1702
int NumberOfDigits(int total_score);//line number : 1713
void score();//line number : 1717
void SettingTheOrigin();//line number : 1736
void check_level(RenderWindow& game);//line number : 1762
bool check_level_end();//line number : 1796
int Bonus();//line number : 1959
int remaining_bubbles();//line number : 1988
bool in_the_top_5(int score);//line number : 2005
void loadFiles();//line number : 2013
int The_high_score();//line number : 2030
void savefiles();//line number : 2041
void draw_table(RenderWindow& window);//line number : 2054
void Score_order(int score, string name);//line number : 2108
void displayScores();//line number : 2141
void main_menu_window();//line number : 2287
void game_window();//line number : 2369
void game_end_window();//line number : 2405
void game_over_window();//line number : 2552
void Enter_name_player();//line number : 2676
void pause_window(RenderWindow& game);//line number : 2792
void About_Us_window();
int cnt9 = 0;
pair<int, string>scr[5];
int Score;
string Name;
int target[16];
int levelnum = 0;
int page_number = -1;
bool mainmenu = true;
bool close = false;
bool shifting = false;
bool sound = true;
int pop_cnt = 0;
int high_score;
bool game_end_bool;
Clock pop_end_clock;
//icon drawings
Texture img1_texture, img2_texture, img3_texture, img4_texture, img5_texture, img6_texture, img7_texture, img8_texture, img9_texture, img10_texture;
Sprite img1_sprite, img2_sprite, img3_sprite, img4_sprite, img5_sprite, img6_sprite, img7_sprite, img8_sprite, img9_sprite, img10_sprite;
Texture sound_texture;
Sprite sound_sprite;
Texture first_help_texture, second_help_texture, third_help_texture;
Sprite first_help_sprite, second_help_sprite, third_help_sprite;
Texture game_name_texture;
Sprite game_name_sprite;
Texture game_back_ground;
Sprite game_back_ground_sprite;
Texture score_mask_texture;
Sprite score_mask_sprite;
Texture pause_texture;
Sprite pause_sprite;
Texture empty_texture;
Text text_target, level_text, highscore_text;
Font font_target, level_font, highscore_font;
RectangleShape line(Vector2f(670, 3));
Texture blue; Texture green; Texture red; Texture purple; Texture yellow;
// help methods shapes & texts
Font font; Text help_1_txt; Text help_2_txt; Text help_3_txt;
// Clock for animation
Clock anim1; Clock icon_anim;
// help methods animation
Texture red_tex[12]; Sprite red_sprite;
Texture purple_tex[12]; Sprite purple_sprite;
Texture yellow_tex[12]; Sprite yellow_sprite;
Texture green_tex[12]; Sprite green_sprite;
Texture blue_tex[12]; Sprite blue_sprite;
Texture textureBonusWindow;
RectangleShape BonusWindow(Vector2f(400, 280));
// Global Variables for help functions
int cnt_help1 = 0; int cnt_help2 = 0; int cnt_help3 = 0; int tmp1, tmp2, tmp3; int f[9] = {};
long long total_score = 0; int number_of_poppedballs = 0; int previous_no_zeroes = 0;
// Global booleans for help functions
bool help_1_activated = false; bool help_2_activated = false; bool help_3_activated = false; bool first_help_activated = false;
bool text1 = false, txt2 = false, txt3 = false; bool flag1_help = 0, flag2_help = 0, flag3_help = 0;
bool pop_start = false;
//texts
Text textNumber_remaining;
Font fontNumber_remaining;
Text textNumber_bonus;
Font fontNumber_bonus;
// Clocks
Clock help1_clock, help2_clock, help3_clock;
// Animation
Sprite anim;
// Score txt
Text score_txt; Font score_font;
// grid drawings
RectangleShape game_frame(Vector2f(550.0f, 460.0f));
RectangleShape square(Vector2f(55.0f, 46.0f));
const int n = 10;
Bubble grid[n][n];
// visited is needed for search, popped is needed for animation
bool visited[n][n], popped[n][n];
// needed to stop click overlap in between delays
bool finishedClick = 1;
// this is the grid initializer
Clock bonus_clock;
int bonus_start = 0;
Music music;
void rand_color()
{
    srand(time(NULL));
    // 1 for red ... 2 for purple ... 3 for yellow ... 4 for green ... 5 for blue
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j].color = rand() % 5 + 1;
            switch (grid[i][j].color)
            {
            case 1:
                grid[i][j].texture.loadFromFile("Textures/Virus/red corona.png");
                grid[i][j].sprite.setTexture(grid[i][j].texture);
                grid[i][j].sprite.setScale(0.10, 0.10);
                grid[i][j].sprite.setOrigin(13.45, 13.45);

                break;
            case 2:
                grid[i][j].texture.loadFromFile("Textures/Virus/purple corona.png");
                grid[i][j].sprite.setTexture(grid[i][j].texture);
                grid[i][j].sprite.setScale(0.10, 0.10);
                grid[i][j].sprite.setOrigin(13.45, 13.45);
                break;
            case 3:
                grid[i][j].texture.loadFromFile("Textures/Virus/yellow corona.png");
                grid[i][j].sprite.setTexture(grid[i][j].texture);
                grid[i][j].sprite.setScale(0.10, 0.10);
                grid[i][j].sprite.setOrigin(13.45, 13.45);
                break;
            case 4:
                grid[i][j].texture.loadFromFile("Textures/Virus/dark green corona.png");
                grid[i][j].sprite.setTexture(grid[i][j].texture);
                grid[i][j].sprite.setScale(0.10, 0.10);
                grid[i][j].sprite.setOrigin(13.45, 13.45);
                break;
            case 5:
                grid[i][j].texture.loadFromFile("Textures/Virus/blue corona.png");
                grid[i][j].sprite.setTexture(grid[i][j].texture);
                grid[i][j].sprite.setScale(0.10, 0.10);
                grid[i][j].sprite.setOrigin(13.45, 13.45);
                break;
            }
        }
    }
}
void bubble_isfound()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j].found = true;
        }
    }
}
void draw_matrix(RenderWindow& game)
{
    // color
    game.clear();
    game.draw(game_back_ground_sprite);
    // grid
    game.draw(game_frame);
    // icons
    game.draw(first_help_sprite);
    game.draw(second_help_sprite);
    game.draw(third_help_sprite);
    game.draw(score_mask_sprite);
    game.draw(text_target);
    game.draw(level_text);
    game.draw(pause_sprite);
    game.draw(line);
    game.draw(highscore_text);
    game.draw(help_1_txt);
    game.draw(help_2_txt);
    game.draw(help_3_txt);
    game.draw(score_txt);
    game.draw(img1_sprite);
    game.draw(img2_sprite);
    game.draw(img3_sprite);
    game.draw(img4_sprite);
    game.draw(img5_sprite);
    game.draw(img6_sprite);
    game.draw(img7_sprite);
    game.draw(img8_sprite);
    game.draw(img9_sprite);
    game.draw(img10_sprite);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            //sets positions of bubbles
            if (popped[i][j])
            {
                grid[i][j].sprite.setScale(1.0f, 1.0f);
                grid[i][j].Animation.setScale(grid[i][j].sprite.getScale());
            }
            else {
                grid[i][j].sprite.setScale(0.16f, 0.15f);
                grid[i][j].sprite.setOrigin(30.0f, 23.0f);
                grid[i][j].Animation.setScale(0.22407, 0.21);
                grid[i][j].Animation.setOrigin(60.27483, 65.73);
            }
            grid[i][j].sprite.setPosition(Vector2f((j * 55) + 85, (i * 46) + 185));
            grid[i][j].Animation.setPosition(Vector2f((j * 55) + 86, (i * 46) + 182));
            square.setPosition((j * 55) + 75, (i * 46) + 180);
            if (i & 2 != 0)
            {
                if (j % 2 == 0)
                {
                    square.setFillColor(Color(152, 248, 240, 150));
                    game.draw(square);
                }
                else
                {
                    square.setFillColor(Color(34, 191, 255, 150));
                    game.draw(square);
                }
            }
            else
            {
                if (j % 2 != 0)
                {
                    square.setFillColor(Color(152, 248, 240, 150));
                    game.draw(square);
                }
                else
                {
                    square.setFillColor(Color(34, 191, 255, 150));
                    game.draw(square);
                }
            }
            if (grid[i][j].found || popped[i][j]) {
                game.draw(grid[i][j].sprite);
                game.draw(grid[i][j].Animation);
            }
        }
    }
    if (shifting && shift_done() && !pop_start)
    {
        if (bonus_start == 0)
        {
            bonus_clock.restart();
            bonus_start = 1;
            textNumber_bonus.setString(to_string(Bonus()));
            textNumber_remaining.setString(to_string(remaining_bubbles()));
            total_score += Bonus();
        }
        if (bonus_clock.getElapsedTime().asSeconds() <= 4)
        {
            if (BonusWindow.getPosition().y >= 300 && bonus_clock.getElapsedTime().asSeconds() <= 3)
            {
                game.draw(BonusWindow);
                game.draw(textNumber_bonus);
                game.draw(textNumber_remaining);
                BonusWindow.move(Vector2f(0, -25));
                textNumber_bonus.setPosition(Vector2f(BonusWindow.getPosition().x + 50, BonusWindow.getPosition().y - 31));
                textNumber_remaining.setPosition(Vector2f(BonusWindow.getPosition().x + 110, BonusWindow.getPosition().y + 35));
            }
            else
            {
                if (BonusWindow.getPosition().y < 900)
                {

                    BonusWindow.move(Vector2f(0, 25));
                    textNumber_bonus.setPosition(Vector2f(BonusWindow.getPosition().x + 50, BonusWindow.getPosition().y - 31));
                    textNumber_remaining.setPosition(Vector2f(BonusWindow.getPosition().x + 110, BonusWindow.getPosition().y + 35));
                    game.draw(BonusWindow);
                    game.draw(textNumber_bonus);
                    game.draw(textNumber_remaining);
                }
            }
        }
        else
        {

            pop_start = true;
        }
    }
    game.display();
}
bool level_empty()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j].found)
                return false;
        }
    }
    return true;
}
void pop_end(RenderWindow& game) {
    int tmpx = 0, tmpy = 0; int tmp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j].one_by_one_pop = false;

        }
    }
    if (check_level_end() && shift_done() && pop_start) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j].color != 0) {
                    grid[i][j].one_by_one_pop = true;
                    tmpx = i; tmpy = j + 1;
                    pop_cnt++;
                }
                if (pop_cnt == 9) {
                    break;
                }
            }
            if (pop_cnt == 9) {
                break;
            }
        }
    }
    tmp = tmpy;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j].one_by_one_pop)
            {
                switch (grid[i][j].color) {
                case 1:
                    f[0] = 0;
                    while (f[0] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(red_tex[f[0]]);
                            f[0]++;
                            grid[i][j].sprite.setTexture(empty_texture);
                            draw_matrix(game);
                            anim1.restart();
                        }
                        if (f[0] == 12)
                        {
                            grid[i][j].found = false;
                            grid[i][j].color = 0;
                        }
                    }
                    f[0] = 0;
                    break;
                case 2:
                    f[1] = 0;
                    while (f[1] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(purple_tex[f[1]]);
                            f[1]++;
                            grid[i][j].sprite.setTexture(empty_texture);
                            draw_matrix(game);
                            anim1.restart();
                        }
                        if (f[1] == 12)
                        {
                            grid[i][j].found = false;
                            grid[i][j].color = 0;
                        }
                    }
                    f[1] = 0;
                    break;
                case 3:
                    f[2] = 0;
                    while (f[2] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(yellow_tex[f[2]]);
                            f[2]++;
                            grid[i][j].sprite.setTexture(empty_texture);
                            draw_matrix(game);
                            anim1.restart();
                        }
                        if (f[2] == 12)
                        {
                            grid[i][j].found = false;
                            grid[i][j].color = 0;
                        }
                    }
                    f[2] = 0;
                    break;
                case 4:
                    f[3] = 0;
                    while (f[3] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(green_tex[f[3]]);
                            f[3]++;
                            grid[i][j].sprite.setTexture(empty_texture);
                            draw_matrix(game);
                            anim1.restart();
                        }
                        if (f[3] == 12)
                        {
                            grid[i][j].found = false;
                            grid[i][j].color = 0;
                        }
                    }
                    f[3] = 0;
                    break;
                case 5:
                    f[4] = 0;
                    while (f[4] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(blue_tex[f[4]]);
                            f[4]++;
                            grid[i][j].sprite.setTexture(empty_texture);
                            draw_matrix(game);
                            anim1.restart();
                        }
                        if (f[4] == 12)
                        {
                            grid[i][j].found = false;
                            grid[i][j].color = 0;
                        }
                    }
                    f[4] = 0;
                    break;
                }
            }
        }
    }
    if (pop_cnt != 0) {
        while (f[5] < 12)
        {
            if (pop_end_clock.getElapsedTime().asSeconds() > 0.03) {
                for (int i = tmpx; i < n; i++) {
                    for (int j = tmpy; j < n; j++)
                    {
                        if (grid[i][j].color == 0) {
                            continue;
                        }
                        switch (grid[i][j].color) {
                        case 0:
                        case 1:
                            grid[i][j].Animation.setTexture(red_tex[f[5]]);
                            break;
                        case 2:
                            grid[i][j].Animation.setTexture(purple_tex[f[5]]);
                            break;
                        case 3:
                            grid[i][j].Animation.setTexture(yellow_tex[f[5]]);
                            break;
                        case 4:
                            grid[i][j].Animation.setTexture(green_tex[f[5]]);
                            break;
                        case 5:
                            grid[i][j].Animation.setTexture(blue_tex[f[5]]);
                            break;
                        }
                        grid[i][j].sprite.setTexture(empty_texture);
                    }

                    tmpy = 0;

                }
                tmpy = tmp;
                f[5]++;
                draw_matrix(game);
                pop_end_clock.restart();
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                grid[i][j].found = false;
                f[5] = 0;
            }
        }
    }
}
//my stuff here
 //checks validity of the index to avoid misreading
bool valid(int x, int y)
{
    return x < n&& x >= 0 && y < n&& y >= 0;
}
// bubble counter useful for special cases ( less than 2 bubbles ) & other code
int steps(int x, int y, int gridcolor, int& stepCounter)
{

    cout << "ClickResult:  " << x << " " << y << "             color: " << gridcolor << endl;
    ++stepCounter;
    int dx[] = { 0,1,0,-1 };
    int dy[] = { 1,0,-1,0 };
    if (valid(x, y))
    {
        for (int i = 0; i < 4; i++) {
            if (valid(x + dx[i], y + dy[i])) {
                if (!visited[x + dx[i]][y + dy[i]])
                {
                    if (gridcolor == grid[x + dx[i]][y + dy[i]].color)
                    {
                        visited[x][y] = true;
                        visited[x + dx[i]][y + dy[i]] = true;
                        steps(x + dx[i], y + dy[i], gridcolor, stepCounter);
                    }
                }

            }
        }
    }
    return stepCounter;
}
// search algorithm searches for area
void areaSearch(int x, int y, int gridcolor)
{
    int dx[] = { 0,1,0,-1 };
    int dy[] = { 1,0,-1,0 };
    if (valid(x, y))
    {
        for (int i = 0; i < 4; i++) {
            if (valid(x + dx[i], y + dy[i])) {
                if (!visited[x + dx[i]][y + dy[i]])
                {
                    if (gridcolor == grid[x + dx[i]][y + dy[i]].color)
                    {
                        visited[x][y] = true;
                        popped[x][y] = true;
                        visited[x + dx[i]][y + dy[i]] = true;
                        popped[x + dx[i]][y + dy[i]] = true;
                        areaSearch(x + dx[i], y + dy[i], gridcolor);
                    }
                    // removed sfml
                    grid[x][y].found = 0;
                    // removed grid numbers
                    grid[x][y].color = 0;
                }

            }
        }
    }
}
// Animation
void animation(int poppedColor, RenderWindow& game)
{
    Clock clock;
    int k = 1;
    bool done = 0, update = 0, synced = 1;
    // draw the popped ones to make them invisible then dra them 11 times for each frame
    while (!done)
    {
        update = 0, synced = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                if (popped[i][j] && synced)
                {
                    string FileDirectory;
                    FileDirectory = "Animation/";
                    switch (poppedColor)
                    {
                    case 1:
                        FileDirectory = FileDirectory + "Red/";
                        break;
                    case 2:
                        FileDirectory = FileDirectory + "Purple/";
                        break;
                    case 3:
                        FileDirectory = FileDirectory + "Yellow/";
                        break;
                    case 4:
                        FileDirectory = FileDirectory + "Green/";
                        break;
                    case 5:
                        FileDirectory = FileDirectory + "Blue/";
                        break;
                    }
                    if (clock.getElapsedTime().asSeconds() > 0.05f)
                    {
                        if (k == 11)
                        {
                            done = 1;
                            break;
                        }
                        FileDirectory = FileDirectory + to_string(k) + ".png";
                        grid[i][j].texture.loadFromFile(FileDirectory);
                        grid[i][j].sprite.setTexture(grid[i][j].texture);
                        grid[i][j].sprite.setOrigin(10.0f, 0.0f);
                        grid[i][j].sprite.setPosition(Vector2f((j * 55) + 85, (i * 46) + 180));
                        update = 1;
                    }
                    else {
                        synced = 0;
                    }
                }
            }
        }
        if (update)
        {
            draw_matrix(game);
            ++k;
            clock.restart();
        }
    }
}
void swap_bubbles()
{

    // swaps grid colors from down to up
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j].color == 0)
            {
                // shifts zeros individually till they reach max height
                for (int x = i; x > 0; x--)
                {
                    swap(grid[x][j].color, grid[x - 1][j].color);
                }
            }
        }
    }

    for (int j = 0; j < n; j++)
    {
        // counts number of zeros in a column
        int ZeroCounter = 0;
        for (int i = 0; i < n; i++)
        {
            if (grid[i][j].color == 0)
            {
                ++ZeroCounter;
            }
        }
        if (ZeroCounter == n)
        {
            for (int x = 0; x < n; x++)
            {
                for (int y = j; y < n - 1; y++)
                {
                    swap(grid[x][y].color, grid[x][y + 1].color);
                }
            }
        }
    }
}
// the events are here
void the_event(RenderWindow& game)
{
    Event evnt;
    while (game.pollEvent(evnt))
    {
        switch (evnt.type)
        {
        case Event::MouseButtonPressed:
            if (evnt.mouseButton.button == Mouse::Left && evnt.mouseButton.x >= 9 && evnt.mouseButton.x <= 38 && evnt.mouseButton.y >= 9 && evnt.mouseButton.y <= 38)
            {
                game.close();
                pause_window(game);
            }
            if (finishedClick && evnt.mouseButton.button == sf::Mouse::Left) {
                finishedClick = 0;
                cout << Mouse::getPosition(game).x << "        " << Mouse::getPosition(game).y << endl;
                // if clicked you will check whether the coordinates are in the range of the square origins or no
                int chosen_x = 20, chosen_y = 20;
                for (int j = 0; j < 10; j++)
                {
                    if (Mouse::getPosition(game).x >= (j * 55) + 85 && Mouse::getPosition(game).x <= ((j + 1) * 55) + 85)
                    {
                        chosen_y = j;
                    }
                }
                for (int i = 0; i < 10; i++)
                {
                    if (Mouse::getPosition(game).y >= (i * 46) + 180 && Mouse::getPosition(game).y <= ((i + 1) * 46) + 180)
                    {
                        chosen_x = i;
                    }
                }
                //needed so game doesnt crash if someone clicks outside of grid
                if (chosen_x == 20 || chosen_y == 20)
                {
                    continue;
                }
                if (grid[chosen_x][chosen_y].color != 0) {
                    int stepCounter = 0, stepsTaken;

                    memset(popped, 0, sizeof popped);
                    stepsTaken = steps(chosen_x, chosen_y, grid[chosen_x][chosen_y].color, stepCounter);
                    int poppedColor = grid[chosen_x][chosen_y].color;
                    memset(visited, 0, sizeof visited);
                    cout << "Steps Taken: " << stepsTaken << endl;
                    if (stepsTaken > 1 && ((first_help_activated == false && cnt_help1 == 0) || (first_help_activated == false && cnt_help1 == 1) || (help1_clock.getElapsedTime().asSeconds() > 0.1 && cnt_help1 == 2)) && ((help_2_activated == false && cnt_help2 == 0) || (help_2_activated == false && cnt_help2 == 1) || (help2_clock.getElapsedTime().asSeconds() > 0.1 && cnt_help2 == 2)) && ((help_3_activated == false && cnt_help3 == 0) || (help_3_activated == false && cnt_help3 == 1) || (help3_clock.getElapsedTime().asSeconds() > 0.1 && cnt_help3 == 2))) {
                        areaSearch(chosen_x, chosen_y, grid[chosen_x][chosen_y].color);
                        animation(poppedColor, game);
                        memset(popped, 0, sizeof popped);
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            cout << grid[i][j].color << " ";
                        }
                        cout << endl;
                    }
                    cout << endl << endl;
                    memset(visited, 0, sizeof visited);
                }
            }

            // (j * 55) + 85, (i * 46) + 180)
            break;
        case Event::Closed:
            game.close();
            levelnum = 0;
            page_number = 3;
            break;
        case Event::KeyPressed:
            if (evnt.key.code == Keyboard::Enter)
            {
                game.close();
                /* if (in_the_top_5(total_score))
                 {
                     game_end_bool2 = true;
                     Enter_name_player();
                     Score_order(total_score, Name);
                     savefiles();
                 }
                 else*/
                game_end_window();
            }
            else if (evnt.key.code == Keyboard::Q)
            {
                cout << level_empty() << en;
            }
            else if (evnt.key.code == Keyboard::Escape)
            {
                game.close();
                /*if (in_the_top_5(total_score))
                {
                    game_over_bool = true;
                    Enter_name_player();
                    Score_order(total_score, Name);
                    savefiles();
                }
                else*/
                game_over_window();
            }
            else if (evnt.key.code == Keyboard::Num9)
            {
                game.close();
                Enter_name_player();
            }
            else if (evnt.key.code == Keyboard::Space)
            {
                game.close();
                pause_window(game);
            }
            break;
        }
    }
}
// SFML SHIFTING
bool shift_done()
{
    //cout << "shift done\n";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            //cout << "( " << i << " , " << j << " )" << grid[i][j].found << space;
            if (!grid[i][j].found)
            {

                if (i == 9)
                {
                    if (j != 9)
                        if (grid[i][j + 1].found)
                            return false;
                }

                else
                {
                    if (j != 9 && i != 0)
                        if (grid[i - 1][j].found)
                            return false;

                }
            }
        }
        //cout << en;
    }

    return true;
}
void shifting_bubbles(RenderWindow& game)
{
    shifting = false;
    //shifting up to down
    for (int i = 0; i < 10; i++)
    {
        for (int j = 9; j >= 0; j--)
        {
            if (grid[j][i].found == true)
                continue;

            int x = j - 1;
            while (x >= 0)
            {
                if (grid[x][i].found == true)
                {
                    grid[j][i].found = true;
                    grid[j][i].texture = grid[x][i].texture;
                    grid[j][i].sprite.setTexture(grid[j][i].texture);
                    grid[x][i].found = false;
                    break;
                }
                x--;
            }

        }
    }
    //shifting right to left

    for (int j = 0; j < 10; j++)
    {
        if (grid[9][j].found == 0)
        {
            for (int i = j; i < 9; i++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if (grid[k][i + 1].found == false)
                        continue;
                    grid[k][i + 1].found = false;
                    grid[k][i].found = true;
                    grid[k][i].texture = grid[k][i + 1].texture;
                    grid[k][i].sprite.setTexture(grid[k][i].texture);
                }
            }
        }

    }
    finishedClick = 1;
    shifting = check_level_end();
    draw_matrix(game);
}
//target
void Target()
{


    int add[15] = { 0,2000,2500,2500,2000,2500,2500,2000,2500,2500,3000,2500,3000,3000,2500 };
    target[0] = 1000;
    for (int i = 1; i < 15; i++)
    {
        target[i] = target[i - 1] + add[i];
    }
}
void declare()
{
    // red animation
    red_tex[0].loadFromFile("Animation/Resized/Red/1.png");
    red_tex[1].loadFromFile("Animation/Resized/Red/2.png");
    red_tex[2].loadFromFile("Animation/Resized/Red/3.png");
    red_tex[3].loadFromFile("Animation/Resized/Red/4.png");
    red_tex[4].loadFromFile("Animation/Resized/Red/5.png");
    red_tex[5].loadFromFile("Animation/Resized/Red/6.png");
    red_tex[6].loadFromFile("Animation/Resized/Red/7.png");
    red_tex[7].loadFromFile("Animation/Resized/Red/8.png");
    red_tex[8].loadFromFile("Animation/Resized/Red/9.png");
    red_tex[9].loadFromFile("Animation/Resized/Red/10.png");
    red_tex[10].loadFromFile("Animation/Resized/Red/11.png");
    red_tex[11].loadFromFile("Animation/Resized/Red/12.png");
    // Purple animation
    purple_tex[0].loadFromFile("Animation/Resized/Purple/1.png");
    purple_tex[1].loadFromFile("Animation/Resized/Purple/2.png");
    purple_tex[2].loadFromFile("Animation/Resized/Purple/3.png");
    purple_tex[3].loadFromFile("Animation/Resized/Purple/4.png");
    purple_tex[4].loadFromFile("Animation/Resized/Purple/5.png");
    purple_tex[5].loadFromFile("Animation/Resized/Purple/6.png");
    purple_tex[6].loadFromFile("Animation/Resized/Purple/7.png");
    purple_tex[7].loadFromFile("Animation/Resized/Purple/8.png");
    purple_tex[8].loadFromFile("Animation/Resized/Purple/9.png");
    purple_tex[9].loadFromFile("Animation/Resized/Purple/10.png");
    purple_tex[10].loadFromFile("Animation/Resized/Purple/11.png");
    purple_tex[11].loadFromFile("Animation/Resized/Purple/12.png");
    // Yellow animation
    yellow_tex[0].loadFromFile("Animation/Resized/Yellow/1.png");
    yellow_tex[1].loadFromFile("Animation/Resized/Yellow/2.png");
    yellow_tex[2].loadFromFile("Animation/Resized/Yellow/3.png");
    yellow_tex[3].loadFromFile("Animation/Resized/Yellow/4.png");
    yellow_tex[4].loadFromFile("Animation/Resized/Yellow/5.png");
    yellow_tex[5].loadFromFile("Animation/Resized/Yellow/6.png");
    yellow_tex[6].loadFromFile("Animation/Resized/Yellow/7.png");
    yellow_tex[7].loadFromFile("Animation/Resized/Yellow/8.png");
    yellow_tex[8].loadFromFile("Animation/Resized/Yellow/9.png");
    yellow_tex[9].loadFromFile("Animation/Resized/Yellow/10.png");
    yellow_tex[10].loadFromFile("Animation/Resized/Yellow/11.png");
    yellow_tex[11].loadFromFile("Animation/Resized/Yellow/12.png");
    // Green animation
    green_tex[0].loadFromFile("Animation/Resized/Green/1.png");
    green_tex[1].loadFromFile("Animation/Resized/Green/2.png");
    green_tex[2].loadFromFile("Animation/Resized/Green/3.png");
    green_tex[3].loadFromFile("Animation/Resized/Green/4.png");
    green_tex[4].loadFromFile("Animation/Resized/Green/5.png");
    green_tex[5].loadFromFile("Animation/Resized/Green/6.png");
    green_tex[6].loadFromFile("Animation/Resized/Green/7.png");
    green_tex[7].loadFromFile("Animation/Resized/Green/8.png");
    green_tex[8].loadFromFile("Animation/Resized/Green/9.png");
    green_tex[9].loadFromFile("Animation/Resized/Green/10.png");
    green_tex[10].loadFromFile("Animation/Resized/Green/11.png");
    green_tex[11].loadFromFile("Animation/Resized/Green/12.png");
    // Blue animation
    blue_tex[0].loadFromFile("Animation/Resized/Blue/1.png");
    blue_tex[1].loadFromFile("Animation/Resized/Blue/2.png");
    blue_tex[2].loadFromFile("Animation/Resized/Blue/3.png");
    blue_tex[3].loadFromFile("Animation/Resized/Blue/4.png");
    blue_tex[4].loadFromFile("Animation/Resized/Blue/5.png");
    blue_tex[5].loadFromFile("Animation/Resized/Blue/6.png");
    blue_tex[6].loadFromFile("Animation/Resized/Blue/7.png");
    blue_tex[7].loadFromFile("Animation/Resized/Blue/8.png");
    blue_tex[8].loadFromFile("Animation/Resized/Blue/9.png");
    blue_tex[9].loadFromFile("Animation/Resized/Blue/10.png");
    blue_tex[10].loadFromFile("Animation/Resized/Blue/11.png");
    blue_tex[11].loadFromFile("Animation/Resized/Blue/12.png");
    // Score txt
    score_font.loadFromFile("Fonts/balloons.ttf");
    score_txt.setCharacterSize(30);
    score_txt.setFont(score_font);
    score_txt.setFillColor(Color::Red);
    score_txt.setPosition(313, 70);
    // help 1 animation
    red_sprite.setOrigin(25, 25);
    red_sprite.setPosition(100, 100);
    //help 1
    first_help_texture.loadFromFile("Textures/help_icons/help 3.png");
    first_help_sprite.setTexture(first_help_texture);
    first_help_sprite.setScale(0.4, 0.4);
    first_help_sprite.setOrigin(20, 20);
    first_help_sprite.setPosition(630, 80);
    //help 2
    second_help_texture.loadFromFile("Textures/help_icons/help 2.png");
    second_help_sprite.setTexture(second_help_texture);
    second_help_sprite.setScale(0.4, 0.4);
    second_help_sprite.setOrigin(20, 20);
    second_help_sprite.setPosition(540, 80);
    //help 3
    third_help_texture.loadFromFile("Textures/help_icons/help 1.png");
    third_help_sprite.setTexture(third_help_texture);
    third_help_sprite.setScale(0.4, 0.4);
    third_help_sprite.setOrigin(19.6, 19.6);
    third_help_sprite.setPosition(450, 80);
    //the name
    game_name_texture.loadFromFile("Corona icons/Corona breaker name.png");
    game_name_sprite.setTexture(game_name_texture);
    game_name_sprite.setPosition(190, 0);
    game_name_sprite.setScale(0.6f, 0.6f);
    //score
    score_mask_texture.loadFromFile("Corona icons/kemama_2.png");
    score_mask_sprite.setTexture(score_mask_texture);
    score_mask_sprite.setPosition(240, 46);
    score_mask_sprite.setScale(0.8f, 0.7f);
    //frame
    game_frame.setPosition(75, 180);
    game_frame.setOutlineColor(Color::Black);
    game_frame.setOutlineThickness(5);
    //line
    line.setPosition(15, 45);
    line.setFillColor(Color::Black);
    //pause
    pause_texture.loadFromFile("Corona icons/pause button.png");
    pause_texture.setSmooth(true);
    pause_sprite.setTexture(pause_texture);
    pause_sprite.setScale(0.22f, 0.22f);
    pause_sprite.setPosition(10, 10);
    //target
    Target();
    font_target.loadFromFile("Fonts/Boldfinger.ttf");
    text_target.setFont(font_target);
    text_target.setString("Target : " + to_string(target[levelnum]));
    text_target.setCharacterSize(20);
    text_target.setFillColor(Color(254, 70, 70));
    text_target.setOutlineColor(Color::Black);
    text_target.setOutlineThickness(4);
    text_target.setPosition(250, 10);
    //level
    level_font.loadFromFile("Fonts/Boldfinger.ttf");
    level_text.setFont(level_font);
    level_text.setString("Level : " + to_string(levelnum + 1));
    level_text.setCharacterSize(20);
    level_text.setFillColor(Color(254, 70, 70));
    level_text.setOutlineColor(Color::Black);
    level_text.setOutlineThickness(4);
    level_text.setPosition(60, 10);
    //highscore
    highscore_font.loadFromFile("Fonts/Boldfinger.ttf");
    highscore_text.setFont(level_font);
    highscore_text.setString("HighScore : " + to_string(The_high_score()));
    highscore_text.setCharacterSize(20);
    highscore_text.setFillColor(Color(254, 70, 70));
    highscore_text.setOutlineColor(Color::Black);
    highscore_text.setOutlineThickness(4);
    highscore_text.setPosition(485, 10);

    //bonus window

    textureBonusWindow.loadFromFile("Bonus_Window.png");
    BonusWindow.setTexture(&textureBonusWindow);
    BonusWindow.setOrigin(Vector2f(BonusWindow.getSize().x / 2, BonusWindow.getSize().y / 2));
    BonusWindow.setPosition(Vector2f(700 / 2, 800 + (BonusWindow.getSize().y / 2)));
    //bouns number
    //******************************************

    fontNumber_bonus.loadFromFile("Fonts/balloons.ttf");
    textNumber_bonus.setFont(fontNumber_bonus);
    textNumber_bonus.setCharacterSize(45);
    textNumber_bonus.setFillColor(Color(253, 225, 0));
    textNumber_bonus.setOutlineColor(Color::White);
    textNumber_bonus.setOutlineThickness(3);
    textNumber_bonus.setPosition(Vector2f(700 / 2, 800 + (BonusWindow.getSize().y / 2)));

    //remaining bublles
    //*******************************************

    fontNumber_remaining.loadFromFile("Fonts/balloons.ttf");
    textNumber_remaining.setFont(fontNumber_bonus);
    textNumber_remaining.setCharacterSize(40);
    textNumber_remaining.setFillColor(Color(250, 240, 0));
    textNumber_remaining.setPosition(Vector2f(700 / 2, 800 + (BonusWindow.getSize().y / 2)));
    //icons
    img1_texture.loadFromFile("Icons/image 1.png");
    img2_texture.loadFromFile("Icons/image 2.png");
    img3_texture.loadFromFile("Icons/image 21.png");
    img4_texture.loadFromFile("Icons/image 28.png");
    img5_texture.loadFromFile("Icons/image 28.png");
    img6_texture.loadFromFile("Icons/image 6.png");
    img7_texture.loadFromFile("Icons/image 7.png");
    img8_texture.loadFromFile("Icons/image 7.png");
    img9_texture.loadFromFile("Icons/image 7.png");
    img10_texture.loadFromFile("Icons/image 7.png");
    img1_sprite.setTexture(img1_texture);
    img2_sprite.setTexture(img2_texture);
    img3_sprite.setTexture(img3_texture);
    img4_sprite.setTexture(img4_texture);
    img5_sprite.setTexture(img5_texture);
    img6_sprite.setTexture(img6_texture);
    img7_sprite.setTexture(img7_texture);
    img8_sprite.setTexture(img7_texture);
    img9_sprite.setTexture(img7_texture);
    img10_sprite.setTexture(img7_texture);
    img3_sprite.setPosition(30, 650);
    img2_sprite.setPosition(30, 70);
    img1_sprite.setPosition(460, 650);
    img4_sprite.setPosition(175, 0);
    img5_sprite.setPosition(415, 0);
    img6_sprite.setPosition(270, 650);
    img7_sprite.setPosition(60, 230);
    img8_sprite.setPosition(60, 490);
    img9_sprite.setPosition(640, 230);
    img10_sprite.setPosition(640, 490);
    img7_sprite.setScale(-1, 1); img8_sprite.setScale(-1, 1);
    //************
    game_back_ground.loadFromFile("Icons/back_ground.jpg");
    game_back_ground_sprite.setTexture(game_back_ground);
    empty_texture.loadFromFile("empty.png");
}
void color_correction() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            switch (grid[i][j].color) {
            case 1:
                grid[i][j].sprite.setTexture(red);
                break;
            case 2:
                grid[i][j].sprite.setTexture(purple);
                break;
            case 3:
                grid[i][j].sprite.setTexture(yellow);
                break;
            case 4:
                grid[i][j].sprite.setTexture(green);
                break;
            case 5:
                grid[i][j].sprite.setTexture(blue);
                break;
            }
        }
    }
}
void grid_color(Bubble(&grid)[10][10], RenderWindow& game) {
    // mouse
    auto mouse_pos = Mouse::getPosition(game);
    auto translated_pos = game.mapPixelToCoords(mouse_pos);
    CircleShape mouse; mouse.setFillColor(Color::White); mouse.setRadius(0.0001); mouse.setOrigin(0.00005, 0.00005); mouse.setPosition(translated_pos);
    // check if the button is clicked
    if (first_help_sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && text1 == false && (cnt_help1 == 0 || cnt_help1 == 1) && help1_clock.getElapsedTime().asSeconds() > 0.3) {
        text1 = true;
        txt2 = false;
        txt3 = false;
        cnt_help1 = 1;
        help1_clock.restart();
    }
    if (text1) {
        first_help_activated = true;
    }
    else
        first_help_activated = false;
    if (text1) {
        font.loadFromFile("Fonts/balloons.ttf");
        help_1_txt.setCharacterSize(40); help_1_txt.setFillColor(Color::White); help_1_txt.setString("3 * 3 Corona virus color change"); help_1_txt.setPosition(130, 130); help_1_txt.setFont(font);
        first_help_sprite.setScale(0.7, 0.7);
        first_help_sprite.setOrigin(34.3, 34.3);
    }
    yellow.loadFromFile("Textures/Virus/yellow corona.png");
    green.loadFromFile("Textures/Virus/dark green corona.png");
    red.loadFromFile("Textures/Virus/red corona.png");
    purple.loadFromFile("Textures/Virus/purple corona.png");
    blue.loadFromFile("Textures/Virus/blue corona.png");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j].visited_anim = false;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && first_help_activated == true && cnt_help1 == 1 && grid[i][j].color != 0) {
                cnt_help1 = 2; // to check if the button is clicked again
                int tmp = rand() % 5 + 1;
                tmp1 = tmp;
                if (i > 0 && j > 0 && i < 9 && j < 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; grid[i - 1][j - 1].color = tmp; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; grid[i - 1][j].color = tmp; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; grid[i - 1][j + 1].color = tmp; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; grid[i][j - 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; grid[i][j + 1].color = tmp; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; grid[i + 1][j - 1].color = tmp; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; grid[i + 1][j].color = tmp; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; grid[i + 1][j + 1].color = tmp; }
                    text1 = false;
                }
                // corners
                else if (i == 0 && j == 0) {
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; grid[i][j + 1].color = tmp; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; grid[i + 1][j].color = tmp; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; grid[i + 1][j + 1].color = tmp; }
                    text1 = false;
                }
                else if (i == 0 && j == 9) {
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; grid[i][j - 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; grid[i + 1][j - 1].color = tmp; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; grid[i + 1][j].color = tmp; }
                    text1 = false;
                }
                else if (i == 9 && j == 0) {
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; grid[i - 1][j].color = tmp; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; grid[i - 1][j + 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; grid[i][j + 1].color = tmp; }
                    text1 = false;
                }
                else if (i == 9 && j == 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; grid[i - 1][j - 1].color = tmp; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; grid[i - 1][j].color = tmp; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; grid[i][j - 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    text1 = false;
                }
                // sides
                else if (i == 0 && j != 0 && j != 9) {
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; grid[i][j - 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; grid[i][j + 1].color = tmp; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; grid[i + 1][j - 1].color = tmp; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; grid[i + 1][j].color = tmp; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; grid[i + 1][j + 1].color = tmp; }
                    text1 = false;
                }
                else if (i == 9 && j != 0 && j != 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; grid[i - 1][j - 1].color = tmp; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; grid[i - 1][j].color = tmp; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; grid[i - 1][j + 1].color = tmp; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; grid[i][j - 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; grid[i][j + 1].color = tmp; }
                    text1 = false;
                }
                else if (j == 0 && i != 0 && i != 9) {
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; grid[i - 1][j].color = tmp; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; grid[i - 1][j + 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; grid[i][j + 1].color = tmp; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; grid[i + 1][j].color = tmp; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; grid[i + 1][j + 1].color = tmp; }
                    text1 = false;
                }
                else if (j == 9 && i != 0 && i != 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; grid[i - 1][j - 1].color = tmp; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; grid[i - 1][j].color = tmp; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; grid[i][j - 1].color = tmp; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; grid[i][j].color = tmp; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; grid[i + 1][j - 1].color = tmp; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; grid[i + 1][j].color = tmp; }
                    text1 = false;
                }
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].visited_anim) {
                switch (grid[i][j].color) {
                case 1:
                    grid[i][j].sprite.setTexture(red);
                    while (f[0] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(red_tex[f[0]]);
                            f[0]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    f[0] = 0;
                    help1_clock.restart();
                    break;
                case 2:
                    grid[i][j].sprite.setTexture(purple);
                    while (f[1] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(purple_tex[f[1]]);
                            f[1]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    f[1] = 0;
                    help1_clock.restart();
                    break;
                case 3:
                    grid[i][j].sprite.setTexture(yellow);
                    while (f[2] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(yellow_tex[f[2]]);
                            f[2]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    f[2] = 0;
                    help1_clock.restart();
                    break;
                case 4:
                    grid[i][j].sprite.setTexture(green);
                    while (f[3] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(green_tex[f[3]]);
                            f[3]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    f[3] = 0;
                    help1_clock.restart();
                    break;
                case 5:
                    grid[i][j].sprite.setTexture(blue);
                    while (f[4] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(blue_tex[f[4]]);
                            f[4]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    f[4] = 0;
                    help1_clock.restart();
                    break;
                }
            }
        }
    }
    if (first_help_sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && first_help_activated == true && help1_clock.getElapsedTime().asSeconds() > 0.3) {
        text1 = false;
        txt2 = false;
        txt3 = false;
        help1_clock.restart();
    }
    if (text1 == false) {
        help_1_txt.setString("");
        first_help_sprite.setScale(0.4, 0.4);
        first_help_sprite.setOrigin(19.6, 19.6);
    }
    else
        help_1_txt.setString("3*3 Corona virus color change");
    color_correction();
    draw_matrix(game);
}
void crush_grid(Bubble(&grid)[10][10], RenderWindow& game) {
    // mouse
    auto mouse_pos = Mouse::getPosition(game);
    auto translated_pos = game.mapPixelToCoords(mouse_pos);
    CircleShape mouse; mouse.setFillColor(Color::White); mouse.setRadius(0.0001); mouse.setOrigin(0.00005, 0.00005); mouse.setPosition(translated_pos);
    // check if the button is clicked
    if (second_help_sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && txt2 == false && (cnt_help2 == 0 || cnt_help2 == 1) && help2_clock.getElapsedTime().asSeconds() > 0.3) {
        text1 = false;
        txt2 = true;
        txt3 = false;
        cnt_help2 = 1;
        help2_clock.restart();
    }
    if (txt2) {
        help_2_activated = true;
    }
    else
        help_2_activated = false;
    if (txt2) {
        font.loadFromFile("Fonts/balloons.ttf");
        help_2_txt.setCharacterSize(40); help_2_txt.setFillColor(Color::White); help_2_txt.setString("Crush 3*3 Corona virus"); help_2_txt.setPosition(180, 130); help_2_txt.setFont(font);
        second_help_sprite.setScale(0.7, 0.7);
        second_help_sprite.setOrigin(35, 35);
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j].visited_anim = false;
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && help_2_activated == true && cnt_help2 == 1 && grid[i][j].color != 0) {
                cnt_help2 = 2; // to check if the button is clicked again
                if (i > 0 && j > 0 && i < 9 && j < 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; }
                    txt2 = false;
                }
                // corners
                else if (i == 0 && j == 0) {
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; }
                    txt2 = false;
                }
                else if (i == 0 && j == 9) {
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; }
                    txt2 = false;
                }
                else if (i == 9 && j == 0) {
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; }
                    txt2 = false;
                }
                else if (i == 9 && j == 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    txt2 = false;
                }
                // sides
                else if (i == 0 && j != 0 && j != 9) {
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; }
                    txt2 = false;
                }
                else if (i == 9 && j != 0 && j != 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; }
                    txt2 = false;
                }
                else if (j == 0 && i != 0 && i != 9) {
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; }
                    if (grid[i - 1][j + 1].color != 0) { grid[i - 1][j + 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i][j + 1].color != 0) { grid[i][j + 1].visited_anim = true; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; }
                    if (grid[i + 1][j + 1].color != 0) { grid[i + 1][j + 1].visited_anim = true; }
                    txt2 = false;
                }
                else if (j == 9 && i != 0 && i != 9) {
                    if (grid[i - 1][j - 1].color != 0) { grid[i - 1][j - 1].visited_anim = true; }
                    if (grid[i - 1][j].color != 0) { grid[i - 1][j].visited_anim = true; }
                    if (grid[i][j - 1].color != 0) { grid[i][j - 1].visited_anim = true; }
                    if (grid[i][j].color != 0) { grid[i][j].visited_anim = true; }
                    if (grid[i + 1][j - 1].color != 0) { grid[i + 1][j - 1].visited_anim = true; }
                    if (grid[i + 1][j].color != 0) { grid[i + 1][j].visited_anim = true; }
                    txt2 = false;
                }
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].visited_anim) {
                switch (grid[i][j].color) {
                case 1:
                    grid[i][j].sprite.setTexture(red);
                    while (f[0] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(red_tex[f[0]]);
                            grid[i][j].sprite.setColor(Color(255, 255, 255, 0)); // makes difference to the grid not the ball so here I make the ball disappear untill it actually removes by grid[i][j].color=0
                            f[0]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    grid[i][j].sprite.setColor(Color(255, 255, 255, 255)); // here I return the opacity again to make the balls that will shift downwards appear with their full opacity as the change of the sfml occur to the grid not to the ball the stored in the specific position in the matrix
                    grid[i][j].color = 0;
                    grid[i][j].found = false;
                    help2_clock.restart();
                    f[0] = 0;
                    break;
                case 2:
                    grid[i][j].sprite.setTexture(purple);
                    while (f[1] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(purple_tex[f[1]]);
                            grid[i][j].sprite.setColor(Color(255, 255, 255, 0));
                            f[1]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    grid[i][j].sprite.setColor(Color(255, 255, 255, 255));
                    grid[i][j].color = 0;
                    grid[i][j].found = false;
                    help2_clock.restart();
                    f[1] = 0;
                    break;
                case 3:
                    grid[i][j].sprite.setTexture(yellow);
                    while (f[2] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(yellow_tex[f[2]]);
                            grid[i][j].sprite.setColor(Color(255, 255, 255, 0));
                            f[2]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    grid[i][j].sprite.setColor(Color(255, 255, 255, 255));
                    grid[i][j].color = 0;
                    grid[i][j].found = false;
                    help2_clock.restart();
                    f[2] = 0;
                    break;
                case 4:
                    grid[i][j].sprite.setTexture(green);
                    while (f[3] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(green_tex[f[3]]);
                            grid[i][j].sprite.setColor(Color(255, 255, 255, 0));
                            f[3]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    grid[i][j].sprite.setColor(Color(255, 255, 255, 255));
                    grid[i][j].color = 0;
                    grid[i][j].found = false;
                    help2_clock.restart();
                    f[3] = 0;
                    break;
                case 5:
                    grid[i][j].sprite.setTexture(blue);
                    while (f[4] < 12) {
                        if (anim1.getElapsedTime().asSeconds() > 0.03) {
                            grid[i][j].Animation.setTexture(blue_tex[f[4]]);
                            grid[i][j].sprite.setColor(Color(255, 255, 255, 0));
                            f[4]++;
                            draw_matrix(game);
                            anim1.restart();
                        }
                    }
                    grid[i][j].sprite.setColor(Color(255, 255, 255, 255));
                    grid[i][j].color = 0;
                    grid[i][j].found = false;
                    help2_clock.restart();
                    f[4] = 0;
                    break;
                }
            }
        }
    }
    if (second_help_sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && help_2_activated == true && help2_clock.getElapsedTime().asSeconds() > 0.3) {
        text1 = false;
        txt2 = false;
        txt3 = false;
        help2_clock.restart();
    }
    if (txt2 == false) {
        help_2_txt.setString("");
        second_help_sprite.setScale(0.4, 0.4);
        second_help_sprite.setOrigin(20, 20);
    }
    else
        help_2_txt.setString("Crush 3*3 Corona virus");
    draw_matrix(game);
}
void virus_color(Bubble(&grid)[10][10], RenderWindow& game) {
    // mouse
    auto mouse_pos = Mouse::getPosition(game);
    auto translated_pos = game.mapPixelToCoords(mouse_pos);
    CircleShape mouse; mouse.setFillColor(Color::White); mouse.setRadius(0.0001); mouse.setOrigin(0.00005, 0.00005); mouse.setPosition(translated_pos);
    // check if the button is clicked
    if (third_help_sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && txt3 == false && (cnt_help3 == 0 || cnt_help3 == 1) && help3_clock.getElapsedTime().asSeconds() > 0.3) {
        text1 = false;
        txt2 = false;
        txt3 = true;
        cnt_help3 = 1;
        help3_clock.restart();
    }
    if (txt3) {
        help_3_activated = true;
    }
    else
        help_3_activated = false;
    if (txt3) {
        font.loadFromFile("Fonts/balloons.ttf");
        help_3_txt.setCharacterSize(40); help_3_txt.setFillColor(Color::White); help_3_txt.setString("Change Corona virus color"); help_3_txt.setPosition(150, 130); help_3_txt.setFont(font);
        third_help_sprite.setScale(0.7, 0.7);
        third_help_sprite.setOrigin(35, 35);
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && help_3_activated == true && cnt_help3 == 1 && grid[i][j].color != 0) {
                int tmp = 0;
                RenderWindow choose_color(VideoMode(600, 100), "Choose Color", Style::Close);
                yellow.loadFromFile("Textures/Virus/yellow corona.png");
                green.loadFromFile("Textures/Virus/dark green corona.png");
                red.loadFromFile("Textures/Virus/red corona.png");
                purple.loadFromFile("Textures/Virus/purple corona.png");
                blue.loadFromFile("Textures/Virus/blue corona.png");
                while (choose_color.isOpen()) {
                    choose_color.setPosition(Vector2i(510, 750));
                    Sprite ball1; Sprite ball2; Sprite ball3; Sprite ball4; Sprite ball5;
                    ball1.setScale(0.16f, 0.15f);
                    ball2.setScale(0.16f, 0.15f);
                    ball3.setScale(0.16f, 0.15f);
                    ball4.setScale(0.16f, 0.15f);
                    ball5.setScale(0.16f, 0.15f);
                    ball1.setTexture(blue); ball2.setTexture(green); ball3.setTexture(red); ball4.setTexture(purple); ball5.setTexture(yellow);
                    ball1.setPosition(100, 20); ball2.setPosition(200, 20); ball3.setPosition(300, 20); ball4.setPosition(400, 20); ball5.setPosition(500, 20);
                    ball1.setOrigin(25, 25); ball2.setOrigin(25, 25); ball3.setOrigin(25, 25); ball4.setOrigin(25, 25); ball5.setOrigin(25, 25);
                    auto mouse_pos2 = Mouse::getPosition(choose_color);
                    auto translated_pos2 = game.mapPixelToCoords(mouse_pos2);
                    CircleShape mouse2; mouse2.setFillColor(Color::Transparent); mouse2.setRadius(0.0001); mouse2.setOrigin(0.00005, 0.00005); mouse2.setPosition(translated_pos2);
                    Event ev;

                    while (choose_color.pollEvent(ev)) {
                        if (ev.type == Event::Closed) {
                            help_3_activated = false;
                            help_1_activated = false;
                            help_2_activated = false;
                            txt3 = false;
                            choose_color.close();
                        }
                    }

                    if (ball1.getGlobalBounds().intersects(mouse2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
                        tmp = 5;
                        cnt_help3 = 2;
                        grid[i][j].color = 5;
                        choose_color.close();
                    }
                    else if (ball2.getGlobalBounds().intersects(mouse2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
                        tmp = 4;
                        grid[i][j].color = 4;
                        cnt_help3 = 2;
                        choose_color.close();
                    }
                    else if (ball3.getGlobalBounds().intersects(mouse2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
                        tmp = 1;
                        grid[i][j].color = 1;
                        cnt_help3 = 2;
                        choose_color.close();
                    }
                    else if (ball4.getGlobalBounds().intersects(mouse2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
                        tmp = 2;
                        grid[i][j].color = 2;
                        cnt_help3 = 2;
                        choose_color.close();
                    }
                    else if (ball5.getGlobalBounds().intersects(mouse2.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
                        tmp = 3;
                        grid[i][j].color = 3;
                        cnt_help3 = 2;
                        choose_color.close();
                    }
                    choose_color.clear();
                    choose_color.draw(ball1);
                    choose_color.draw(ball2);
                    choose_color.draw(ball3);
                    choose_color.draw(ball4);
                    choose_color.draw(ball5);
                    choose_color.display();
                }
                if (cnt_help3 == 2) {
                    grid[i][j].color = tmp;
                    help_3_activated = false;
                    help_1_activated = false;
                    help_2_activated = false;
                    txt3 = false;
                    switch (grid[i][j].color) {
                    case 1:
                        grid[i][j].sprite.setTexture(red);
                        while (f[0] < 12) {
                            if (anim1.getElapsedTime().asSeconds() > 0.03) {
                                grid[i][j].Animation.setTexture(red_tex[f[0]]);
                                f[0]++;
                                draw_matrix(game);
                                anim1.restart();
                            }
                        }
                        help3_clock.restart();
                        f[0] = 0;
                        break;
                    case 2:
                        grid[i][j].sprite.setTexture(purple);
                        while (f[1] < 12) {
                            if (anim1.getElapsedTime().asSeconds() > 0.03) {
                                grid[i][j].Animation.setTexture(purple_tex[f[1]]);
                                f[1]++;
                                draw_matrix(game);
                                anim1.restart();
                            }
                        }
                        help3_clock.restart();
                        f[1] = 0;
                        break;
                    case 3:
                        grid[i][j].sprite.setTexture(yellow);
                        while (f[2] < 12) {
                            if (anim1.getElapsedTime().asSeconds() > 0.03) {
                                grid[i][j].Animation.setTexture(yellow_tex[f[2]]);
                                f[2]++;
                                draw_matrix(game);
                                anim1.restart();
                            }
                        }
                        help3_clock.restart();
                        f[2] = 0;
                        break;
                    case 4:
                        grid[i][j].sprite.setTexture(green);
                        while (f[3] < 12) {
                            if (anim1.getElapsedTime().asSeconds() > 0.03) {
                                grid[i][j].Animation.setTexture(green_tex[f[3]]);
                                f[3]++;
                                draw_matrix(game);
                                anim1.restart();
                            }
                        }
                        help3_clock.restart();
                        f[3] = 0;
                        break;
                    case 5:
                        grid[i][j].sprite.setTexture(blue);
                        while (f[4] < 12) {
                            if (anim1.getElapsedTime().asSeconds() > 0.03) {
                                grid[i][j].Animation.setTexture(blue_tex[f[4]]);
                                f[4]++;
                                draw_matrix(game);
                                anim1.restart();
                            }
                        }
                        help3_clock.restart();
                        f[4] = 0;
                        break;
                    }
                }
            }
        }
    }
    if (third_help_sprite.getGlobalBounds().intersects(mouse.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && help_3_activated == true && help3_clock.getElapsedTime().asSeconds() > 0.3) {
        help_1_activated = false;
        help_2_activated = false;
        help_3_activated = false;
        text1 = false;
        txt2 = false;
        txt3 = false;
        help3_clock.restart();
    }
    if (txt3 == false) {
        help_3_txt.setString("");
        third_help_sprite.setScale(0.4, 0.4);
        third_help_sprite.setOrigin(20, 20);
    }
    else
        help_3_txt.setString("Change Corona virus color");
    color_correction();
    draw_matrix(game);
}
int NumberOfZeros() {
    int number_of_zeroes = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j].color == 0) {
                number_of_zeroes++;
            }
        }
    }
    return number_of_zeroes;
}
int NumberOfDigits(int total_score) {
    int digits = log10(total_score) + 1;
    return digits;
}
void score() {
    stringstream s; int score_of_ball = 0;
    if (NumberOfZeros() != previous_no_zeroes) {
        number_of_poppedballs = NumberOfZeros() - previous_no_zeroes;
        previous_no_zeroes = NumberOfZeros();
    }
    //cout << "function:" << NumberOfZeros() << endl << "previous zeros: " << previous_no_zeroes << endl << "actually popped: " << number_of_poppedballs << endl;
    if (number_of_poppedballs != 0) {
        score_of_ball = 5;
        while ((number_of_poppedballs > 0)) {
            total_score += score_of_ball;
            score_of_ball += 10;
            number_of_poppedballs--;
        }
    }
    s << total_score;
    score_txt.setString(s.str());
    highscore_text.setString("HighScore : " + to_string(The_high_score()));
}
void SettingTheOrigin() {
    if (NumberOfDigits(total_score) == 2) {
        score_txt.setPosition(308, 70);
    }
    else if ((NumberOfDigits(total_score) == 3)) {
        score_txt.setPosition(304, 70);
    }
    else if ((NumberOfDigits(total_score) == 4)) {
        score_txt.setPosition(300, 70);
    }
    else if ((NumberOfDigits(total_score) == 5)) {
        score_txt.setPosition(296, 70);
    }
    else if ((NumberOfDigits(total_score) == 6)) {
        score_txt.setPosition(292, 70);
    }
    else if ((NumberOfDigits(total_score) == 7)) {
        score_txt.setPosition(288, 70);
    }
    else if ((NumberOfDigits(total_score) == 8)) {
        score_txt.setPosition(284, 70);
    }
    else if ((NumberOfDigits(total_score) == 9)) {
        score_txt.setPosition(280, 70);
    }
}
void check_level(RenderWindow& game)
{
    if (target[levelnum] <= total_score)
    {
        levelnum++;
        if (levelnum == 15)
            if (levelnum == 15)
            {
                levelnum = 0;
                game_end_bool = true;
            }
        text_target.setString("Target : " + to_string(target[levelnum]));
        level_text.setString("Level : " + to_string(levelnum + 1));
        bonus_start = 0;
        pop_cnt = 0;
        pop_start = false;
        bubble_isfound();
        rand_color();
    }
    else
    {
        game.close();
        game_over_window();
    }
}
bool check_level_end()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i == 0 && j != 0 && j != 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i][j - 1].found == true && grid[i][j - 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j + 1].found == true && grid[i][j + 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i + 1][j].found == true && grid[i + 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (j == 0 && i != 0 && i != 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i - 1][j].found == true && grid[i - 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j + 1].found == true && grid[i][j + 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i + 1][j].found == true && grid[i + 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (i == 9 && j != 0 && j != 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i][j - 1].found == true && grid[i][j - 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j + 1].found == true && grid[i][j + 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i - 1][j].found == true && grid[i - 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (j == 9 && i != 0 && i != 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i - 1][j].found == true && grid[i - 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j - 1].found == true && grid[i][j - 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i + 1][j].found == true && grid[i + 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (i == 0 && j == 0)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i + 1][j].found == true && grid[i + 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j + 1].found == true && grid[i][j + 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (i == 0 && j == 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i][j - 1].found == true && grid[i][j - 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i + 1][j].found == true && grid[i + 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (j == 9 && i == 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i - 1][j].found == true && grid[i - 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j - 1].found == true && grid[i][j - 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else if (j == 0 && i == 9)
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i - 1][j].found == true && grid[i - 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j + 1].found == true && grid[i][j + 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                }
            }
            else
            {
                if (grid[i][j].found == true && grid[i][j].color != 0)
                {
                    if (grid[i - 1][j].found == true && grid[i - 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j + 1].found == true && grid[i][j + 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i + 1][j].found == true && grid[i + 1][j].color == grid[i][j].color)
                    {
                        return false;
                    }
                    else if (grid[i][j - 1].found == true && grid[i][j - 1].color == grid[i][j].color)
                    {
                        return false;
                    }
                }

            }

        }
    }
    return true;
}
//game end (15 levels done)
int Bonus()
{

    switch (remaining_bubbles())
    {
    case 0:
        return 2000;
    case 1:
        return 1980;
    case 2:
        return 1920;
    case 3:
        return 1820;
    case 4:
        return 1680;
    case 5:
        return 1500;
    case 6:
        return 1280;
    case 7:
        return 1020;
    case 8:
        return 720;
    case 9:
        return 380;
    default:
        return 0;
    }
}
int remaining_bubbles()
{
    int num_bubble = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j].found == true)
            {
                num_bubble++;
            }
        }
    }
    return num_bubble;
}
//bouns window (after the check level end)
bool in_the_top_5(int score)
{
    if (score > scr[4].first)
    {
        return true;
    }
    return false;
}
void loadFiles()
{
    ifstream inScoreFile;
    inScoreFile.open("Top_5 high scores.txt");
    if (inScoreFile.fail()) {
        cout << "Error loading score file!";
        exit(1);
    }
    for (int i = 0; i < 5; i++)
    {
        inScoreFile >> scr[i].second;
        inScoreFile >> scr[i].first;
    }
    inScoreFile.close();
    sort(scr, scr + 5);
    reverse(scr, scr + 5);
}
int The_high_score()
{
    loadFiles();
    high_score = scr[0].first;
    if (total_score > high_score)
    {
        high_score = total_score;
    }
    return high_score;
}
// save score after each game
void savefiles()
{
    ofstream insert;
    // open a file to write score
    insert.open("Top_5 high scores.txt", ios::trunc); //truncate (remove what's in the file and put the following: )
    for (int i = 0; i < 5; i++)
    {
        insert << scr[i].second + "  ";
        insert << scr[i].first;
        insert << "\n";
    }
    insert.close();
}
void draw_table(RenderWindow& window)
{
    RectangleShape square1;
    square1.setOutlineColor(Color::Black);
    square1.setOutlineThickness(3);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i % 2 == 0)
            {
                if (j == 0)
                {
                    square1.setPosition(20, (i * 80) + 245);
                    square1.setSize(Vector2f(80, 80));
                }
                else if (j == 1)
                {
                    square1.setPosition(100, (i * 80) + 245);
                    square1.setSize(Vector2f(400, 80));
                }
                else if (j == 2)
                {
                    square1.setPosition(500, (i * 80) + 245);
                    square1.setSize(Vector2f(180, 80));
                }
                square1.setFillColor(Color(40, 242, 71));
                window.draw(square1);
            }
            else
            {
                if (j == 0)
                {
                    square1.setPosition(20, (i * 80) + 245);
                    square1.setSize(Vector2f(80, 80));
                }
                else if (j == 1)
                {
                    square1.setPosition(100, (i * 80) + 245);
                    square1.setSize(Vector2f(400, 80));
                }
                else if (j == 2)
                {
                    square1.setPosition(500, (i * 80) + 245);
                    square1.setSize(Vector2f(180, 80));
                }

                square1.setFillColor(Color(1, 217, 254));
                window.draw(square1);
            }
        }
    }
}
void Score_order(int score, string name)
{
    int last = 0;
    for (int i = 4; i >= 0; i--)
    {
        if (score > scr[i].first)   // new score: 150 / 100 100 200 break still 300 500
        {
            last = i;  // the index of the highest value in the scores which "score" is higher than
        }
        else
            break;
    }
    for (int i = 4; i > last; i--)
    {
        scr[i].first = scr[i - 1].first;
        scr[i].second = scr[i - 1].second;
    }
    scr[last].first = score;
    scr[last].second = name;
    savefiles();
}
//scoreboard_name
void displayScores()
{
    RenderWindow window(VideoMode(700, 800), "Scoreboard", Default);
    Event ev;
    Font font;
    if (font.loadFromFile("Data/Avara.otf") == false)
    {
        cout << "Error loading Font file!";
        exit(1);
    }
    font.loadFromFile("Data/Avara.otf");
    // player name
    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(4);
    // player score
    Text text1;
    text1.setFont(font);
    text1.setCharacterSize(30);
    text1.setFillColor(Color::White);
    text1.setOutlineColor(Color::Black);
    text1.setOutlineThickness(4);
    //scoreboard
    Texture scoreboard_word;
    scoreboard_word.loadFromFile("Data/scoreboard_name.png");
    Sprite scrboard_;
    scrboard_.setTexture(scoreboard_word);
    scrboard_.setScale(0.5f, 0.5f); // 0.15*width and 0.15*height -> 75,75
    scrboard_.setPosition(150, 10);
    scrboard_.setOrigin(65, 30);
    //No.///Name///Score
    Text no, name_text, score_text, main_menu;
    //no
    no.setFont(font);
    no.setCharacterSize(36);
    no.setFillColor(Color::White);
    no.setOutlineColor(Color::Black);
    no.setOutlineThickness(3);
    no.setString("No.");
    no.setPosition(30, 250);
    //name
    name_text.setFont(font);
    name_text.setCharacterSize(36);
    name_text.setFillColor(Color::White);
    name_text.setOutlineColor(Color::Black);
    name_text.setOutlineThickness(3);
    name_text.setString("Name");
    name_text.setPosition(245, 250);
    //score
    score_text.setFont(font);
    score_text.setCharacterSize(36);
    score_text.setFillColor(Color::White);
    score_text.setOutlineColor(Color::Black);
    score_text.setOutlineThickness(3);
    score_text.setString("Score");
    score_text.setPosition(545, 250);
    //main_menu
    main_menu.setFont(font);
    main_menu.setCharacterSize(36);
    main_menu.setFillColor(Color::White);
    main_menu.setOutlineColor(Color::Black);
    main_menu.setOutlineThickness(3);
    main_menu.setString("Main Menu >>");
    main_menu.setPosition(430, 740);
    Text number;
    number.setFont(font);
    number.setCharacterSize(30);
    number.setFillColor(Color::White);
    number.setOutlineColor(Color::Black);
    number.setOutlineThickness(4);
    Texture back_ground;
    Sprite back_ground_sprite;
    back_ground.loadFromFile("Icons/back_ground5.jpg");
    back_ground_sprite.setTexture(back_ground);
    Texture image1_texture, image2_texture;
    Sprite image1_sprite, image2_sprite;
    image1_texture.loadFromFile("Icons/image 31.png");
    image1_sprite.setTexture(image1_texture);
    image1_sprite.setPosition(250, 95);
    loadFiles();
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                page_number = 3;
                window.close();
            }
            if (ev.type == Event::KeyPressed) {
                if (ev.key.code == Keyboard::N) {
                    cout << "Enter score\n";
                    cin >> Score;
                    if (in_the_top_5(Score))
                    {
                        cout << "Enter the name\n";
                        cin >> Name;
                        Score_order(Score, Name);
                        for (int i = 0; i < 5; i++)
                        {
                            cout << scr[i].second << "   " << scr[i].first << endl;
                        }
                    }
                }
            }
            if (ev.MouseMoved)
            {
                if (ev.mouseMove.x >= 430 && ev.mouseMove.x <= 680 && ev.mouseMove.y >= 740 && ev.mouseMove.y <= 795)
                {
                    main_menu.setFillColor(Color::Blue);
                    break;
                }
                else
                {
                    main_menu.setFillColor(Color::White);
                }
            }
            if (ev.type == Event::MouseButtonPressed)
            {
                if (ev.mouseButton.button == Mouse::Left)
                {
                    if (ev.mouseButton.x >= 430 && ev.mouseButton.x <= 680 && ev.mouseButton.y >= 740 && ev.mouseButton.y <= 795)
                    {
                        cout << "to main menu" << endl;
                        window.close();
                        main_menu_window();
                    }
                }
            }
        }
        window.clear();
        window.draw(back_ground_sprite);
        int y = 340;
        //el gadwal
        draw_table(window);
        window.draw(no);
        window.draw(name_text);
        window.draw(image1_sprite);
        window.draw(score_text);
        for (int i = 0; i < 5; i++)
        {
            text.setString(scr[i].second);
            text.setPosition(110, y);
            text1.setString(to_string(scr[i].first));
            text1.setPosition(510, y);
            number.setString(to_string(i + 1) + " .");
            number.setPosition(40, y);
            window.draw(text);
            window.draw(text1);
            window.draw(number);
            y += 80;
        }
        window.draw(main_menu);
        window.draw(scrboard_);
        window.display();
    }
}
void main_menu_window()
{
    Game game2(700, 800);
    RenderWindow window(VideoMode(700, 800), "Main menu", Default);
    if (sound)
        sound_texture.loadFromFile("Icons/Sound.png");
    else
        sound_texture.loadFromFile("Icons/Muted_Sound.png");
    sound_sprite.setTexture(sound_texture);
    sound_sprite.setPosition(30, 700);
    Texture back_ground;
    Sprite back_ground_sprite;
    back_ground.loadFromFile("Icons/back_ground8.jpg");
    back_ground_sprite.setTexture(back_ground);
    //game.music();
    Event ev;
    while (window.isOpen()) {

        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
                page_number = 3;
                break;
            }
            if (ev.MouseMoved)
            {
                if (ev.mouseMove.x >= 260 && ev.mouseMove.x <= 370 && ev.mouseMove.y >= 264 && ev.mouseMove.y <= 337)
                {
                    page_number = 0;
                    game2.change_color(page_number);
                    game2.return_color(page_number);
                    break;
                }
                else if (ev.mouseMove.x >= 255 && ev.mouseMove.x <= 520 && ev.mouseMove.y >= 365 && ev.mouseMove.y <= 420)
                {
                    page_number = 1;
                    game2.change_color(page_number);
                    game2.return_color(page_number);
                    break;
                }
                else if (ev.mouseMove.x >= 255 && ev.mouseMove.x <= 475 && ev.mouseMove.y >= 455 && ev.mouseMove.y <= 505)
                {
                    page_number = 2;
                    game2.change_color(page_number);
                    game2.return_color(page_number);
                    break;
                }
                else if (ev.mouseMove.x >= 255 && ev.mouseMove.x <= 360 && ev.mouseMove.y >= 550 && ev.mouseMove.y <= 600)
                {
                    page_number = 3;
                    game2.change_color(page_number);
                    game2.return_color(page_number);
                    break;
                }
                else
                {
                    game2.return_all_colors();
                }
            }
            if (ev.type == Event::MouseButtonPressed)
            {
                if (ev.mouseButton.button == Mouse::Left)
                {
                    if (ev.mouseButton.x >= 260 && ev.mouseButton.x <= 370 && ev.mouseButton.y >= 264 && ev.mouseButton.y <= 337)
                    {
                        window.close();
                        //game.music();
                        page_number = 0;
                        bonus_start = 0;
                        pop_cnt = 0;
                        pop_start = false;
                        total_score = 0;
                        levelnum = 0;
                        cnt_help1 = 0;
                        cnt_help2 = 0;
                        cnt_help3 = 0;
                        bubble_isfound();
                        rand_color();
                        break;
                    }
                    if (ev.mouseButton.x >= 255 && ev.mouseButton.x <= 520 && ev.mouseButton.y >= 365 && ev.mouseButton.y <= 420)
                    {
                        window.close();
                        //game.music();
                        page_number = 1;
                        break;
                    }
                    if (ev.mouseButton.x >= 255 && ev.mouseButton.x <= 475 && ev.mouseButton.y >= 455 && ev.mouseButton.y <= 505)
                    {
                        window.close();
                        //game.music();
                        page_number = 2;
                        break;
                    }
                    if (ev.mouseButton.x >= 255 && ev.mouseButton.x <= 360 && ev.mouseButton.y >= 550 && ev.mouseButton.y <= 600)
                    {
                        window.close();
                        //game.music();
                        page_number = 3;
                        break;
                    }
                    if (ev.mouseButton.x >= 30 && ev.mouseButton.x <= 125 && ev.mouseButton.y >= 700 && ev.mouseButton.y <= 793)
                    {
                        if (sound)
                        {
                            sound = false;
                            music.pause();
                        }
                        else
                        {
                            sound = true;
                            music.play();
                        }
                        if (sound)
                        {
                            sound_texture.loadFromFile("Icons/Sound.png");
                        }
                        else
                            sound_texture.loadFromFile("Icons/Muted_Sound.png");
                        sound_sprite.setTexture(sound_texture);
                    }
                }
            }
        }
        window.clear();
        window.draw(back_ground_sprite);
        game2.draw(window);
        window.draw(sound_sprite);
        window.display();
    }
}
void game_window()
{
    RenderWindow game(VideoMode(700, 800), "The Game Window");
    loadFiles();
    declare();
    shifting_bubbles(game);
    while (game.isOpen())
    {
        swap_bubbles();
        shifting_bubbles(game);
        grid_color(grid, game);
        crush_grid(grid, game);
        virus_color(grid, game);
        score();
        SettingTheOrigin();
        the_event(game);
        pop_end(game);
        highscore_text.setString("HighScore : " + to_string(The_high_score()));
        draw_matrix(game);
        if (level_empty())
            check_level(game);
        if (game_end_bool)
        {
            game.close();
            game_end_window();
        }
    }
}
void game_end_window()
{
    if (in_the_top_5(total_score))
    {
        Enter_name_player();
        Score_order(total_score, Name);
        savefiles();
    }
    RenderWindow game_end(VideoMode(700, 800), "Game end");
    Texture game_end_frame;
    game_end_frame.loadFromFile("game end frame.png");
    Sprite game_end_frame_sprite;
    game_end_frame_sprite.setScale(0.7, 0.7);
    game_end_frame_sprite.setTexture(game_end_frame);
    game_end_frame_sprite.setPosition(85, 340);
    Text excellent, game_end_paragraph;
    Text player_score;
    Font font2;
    font2.loadFromFile("Data/Avara.otf");
    player_score.setFont(font2);
    player_score.setString("Your score : " + to_string(total_score));
    player_score.setCharacterSize(28);
    player_score.setFillColor(Color::White);
    player_score.setOutlineColor(Color::Black);
    player_score.setOutlineThickness(3);
    player_score.setPosition(230, 180);
    Text high_score_game_end;
    high_score_game_end.setFont(font2);
    high_score_game_end.setString("High score : " + to_string(The_high_score()));
    high_score_game_end.setCharacterSize(22);
    high_score_game_end.setFillColor(Color::White);
    high_score_game_end.setOutlineColor(Color::Black);
    high_score_game_end.setOutlineThickness(3);
    high_score_game_end.setPosition(250, 230);
    Font excellent_font, game_end_paragraph_font;
    excellent_font.loadFromFile("HauntedNight-Demo.otf");
    game_end_paragraph_font.loadFromFile("SKETCHUP FREE TRIAL.ttf");
    excellent.setString("Excellent");
    excellent.setOutlineColor(Color::Black);
    excellent.setOutlineThickness(3);
    excellent.setFont(excellent_font);
    game_end_paragraph.setFont(game_end_paragraph_font);
    game_end_paragraph.setString("                  Congratulations.\n You completed the 15 levels successfully.\n         We hope you enjoyed the game\n                   Have a nice day!");
    excellent.setCharacterSize(60);
    game_end_paragraph.setCharacterSize(31);
    excellent.setFillColor(Color(254, 77, 57));
    game_end_paragraph.setFillColor(Color::Black);
    excellent.setPosition(215, 270);
    game_end_paragraph.setPosition(95, 375);
    Texture game_end_name;
    game_end_name.loadFromFile("icons/game_end_name.png");
    Sprite game_end_name_sprite;
    game_end_name_sprite.setScale(0.6f, 0.6f);
    game_end_name_sprite.setTexture(game_end_name);
    game_end_name_sprite.setPosition(30, 15);
    Text play, top_menu;
    Font font;
    Texture image1_texture, image2_texture, image3_texture, image4_texture;
    Sprite image1_sprite, image2_sprite, image3_sprite, image4_sprite;
    image1_texture.loadFromFile("Icons/image 3.png");
    image2_texture.loadFromFile("Icons/image 14.png");
    image3_texture.loadFromFile("Icons/image 23.png");
    image4_texture.loadFromFile("Icons/image 29.png");
    image1_sprite.setTexture(image1_texture);
    image2_sprite.setTexture(image2_texture);
    image3_sprite.setTexture(image3_texture);
    image4_sprite.setTexture(image4_texture);
    image3_sprite.setPosition(450, 600);
    image4_sprite.setPosition(30, 590);
    image1_sprite.setPosition(50, 190);
    image2_sprite.setPosition(440, 120);
    if (font.loadFromFile("Data/Avara.otf") == false)
    {
        cout << "Error loading Font file!";
        exit(1);
    }
    font.loadFromFile("Data/Avara.otf");
    Text main_menu;
    main_menu.setFont(font);
    main_menu.setCharacterSize(32);
    main_menu.setFillColor(Color::White);
    main_menu.setOutlineColor(Color::Black);
    main_menu.setOutlineThickness(3);
    main_menu.setString("Main Menu");
    main_menu.setPosition(130, 550);
    Text play_again;
    play_again.setFont(font);
    play_again.setCharacterSize(32);
    play_again.setFillColor(Color::White);
    play_again.setOutlineColor(Color::Black);
    play_again.setOutlineThickness(3);
    play_again.setString("Play Again");
    play_again.setPosition(410, 550);
    Texture back_ground;
    Sprite back_ground_sprite;
    back_ground.loadFromFile("Icons/back_ground7.jpg");
    back_ground_sprite.setTexture(back_ground);
    while (game_end.isOpen())
    {
        Event evnt;
        while (game_end.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                game_end.close();
                page_number = 3;
                break;

            case Event::MouseMoved:

                if (evnt.mouseMove.x >= 130 && evnt.mouseMove.x <= 315 && evnt.mouseMove.y >= 550 && evnt.mouseMove.y <= 600)
                {
                    main_menu.setFillColor(Color::Blue);
                    play_again.setFillColor(Color::White);

                }
                else if (evnt.mouseMove.x >= 410 && evnt.mouseMove.x <= 590 && evnt.mouseMove.y >= 550 && evnt.mouseMove.y <= 600)
                {
                    main_menu.setFillColor(Color::White);
                    play_again.setFillColor(Color::Blue);
                }
                else
                {
                    main_menu.setFillColor(Color::White);
                    play_again.setFillColor(Color::White);
                }
                break;
            case Event::MouseButtonPressed:
                if (evnt.mouseButton.button == Mouse::Left)
                {
                    if (evnt.mouseButton.x >= 150 && evnt.mouseButton.x <= 335 && evnt.mouseButton.y >= 550 && evnt.mouseButton.y <= 600)
                    {
                        game_end_bool = false;
                        game_end.close();
                        main_menu_window();
                    }
                    else if (evnt.mouseButton.x >= 420 && evnt.mouseButton.x <= 600 && evnt.mouseButton.y >= 550 && evnt.mouseButton.y <= 600)
                    {
                        game_end_bool = false;
                        game_end.close();
                        bonus_start = 0;
                        pop_cnt = 0;
                        pop_start = false;
                        levelnum = 0;
                        bubble_isfound();
                        rand_color();
                        cnt_help1 = 0;
                        cnt_help2 = 0;
                        cnt_help3 = 0;
                        total_score = 0;
                        game_window();
                    }
                }
                break;
            }
        }
        game_end.clear();
        game_end.draw(back_ground_sprite);
        game_end.draw(excellent);
        game_end.draw(main_menu);
        game_end.draw(play_again);
        game_end.draw(game_end_frame_sprite);
        game_end.draw(game_end_paragraph);
        game_end.draw(game_end_name_sprite);
        game_end.draw(player_score);
        game_end.draw(high_score_game_end);
        game_end.draw(image1_sprite);
        game_end.draw(image2_sprite);
        game_end.draw(image3_sprite);
        game_end.draw(image4_sprite);
        game_end.display();
    }
}
void game_over_window()
{
    if (in_the_top_5(total_score))
    {
        Enter_name_player();
        Score_order(total_score, Name);
        savefiles();
    }
    RenderWindow game_over(VideoMode(700, 800), "Game over");
    Text player_score;
    Font font2;
    font2.loadFromFile("Data/Avara.otf");
    player_score.setFont(font2);
    player_score.setString("Your score : " + to_string(total_score));
    player_score.setCharacterSize(28);
    player_score.setFillColor(Color::White);
    player_score.setOutlineColor(Color::Black);
    player_score.setOutlineThickness(3);
    player_score.setPosition(230, 230);
    Text high_score_game_over;
    high_score_game_over.setFont(font2);
    high_score_game_over.setString("High score : " + to_string(The_high_score()));
    high_score_game_over.setCharacterSize(22);
    high_score_game_over.setFillColor(Color::White);
    high_score_game_over.setOutlineColor(Color::Black);
    high_score_game_over.setOutlineThickness(3);
    high_score_game_over.setPosition(250, 270);
    Texture game_over_name;
    game_over_name.loadFromFile("icons/game_over_name.png");
    Sprite game_over_name_sprite;
    game_over_name_sprite.setTexture(game_over_name);
    game_over_name_sprite.setPosition(50, 15);
    game_over_name_sprite.setScale(0.8f, 0.8f);
    Text play, top_menu;
    Font font;
    if (font.loadFromFile("Data/Avara.otf") == false)
    {
        cout << "Error loading Font file!";
        exit(1);
    }
    font.loadFromFile("Data/Avara.otf");
    Text main_menu;
    main_menu.setFont(font);
    main_menu.setCharacterSize(50);
    main_menu.setFillColor(Color::White);
    main_menu.setOutlineColor(Color::Black);
    main_menu.setOutlineThickness(7);
    main_menu.setString("Main Menu");
    main_menu.setPosition(200, 510);
    Text play_again;
    play_again.setFont(font);
    play_again.setCharacterSize(50);
    play_again.setFillColor(Color::White);
    play_again.setOutlineColor(Color::Black);
    play_again.setOutlineThickness(7);
    play_again.setString("Play Again");
    play_again.setPosition(200, 370);
    Texture image1_texture, image2_texture, image3_texture, image4_texture;
    Sprite image1_sprite, image2_sprite, image3_sprite, image4_sprite;
    image1_texture.loadFromFile("Icons/image 4.png");
    image2_texture.loadFromFile("Icons/image 5.png");
    image3_texture.loadFromFile("Icons/image 12.png");
    image4_texture.loadFromFile("Icons/image 18.png");
    image1_sprite.setTexture(image1_texture);
    image2_sprite.setTexture(image2_texture);
    image3_sprite.setTexture(image3_texture);
    image4_sprite.setTexture(image4_texture);
    image4_sprite.setPosition(35, 560);
    image1_sprite.setPosition(10, 220);
    image3_sprite.setPosition(450, 200);
    image2_sprite.setPosition(460, 560);
    Texture back_ground;
    Sprite back_ground_sprite;
    back_ground.loadFromFile("Icons/back_ground6.jpg");
    back_ground_sprite.setTexture(back_ground);
    while (game_over.isOpen())
    {
        Event evnt;
        while (game_over.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case Event::Closed:
                game_over.close();
                page_number = 3;
                break;

            case Event::MouseMoved:

                if (evnt.mouseMove.x >= 200 && evnt.mouseMove.x <= 450 && evnt.mouseMove.y >= 370 && evnt.mouseMove.y <= 420)
                {
                    play_again.setFillColor(Color::Blue);
                    main_menu.setFillColor(Color::White);

                }
                else if (evnt.mouseMove.x >= 200 && evnt.mouseMove.x <= 450 && evnt.mouseMove.y >= 510 && evnt.mouseMove.y <= 560)
                {
                    play_again.setFillColor(Color::White);
                    main_menu.setFillColor(Color::Blue);
                }
                else
                {
                    main_menu.setFillColor(Color::White);
                    play_again.setFillColor(Color::White);
                }
                break;
            case Event::MouseButtonPressed:
                if (evnt.mouseButton.button == Mouse::Left)
                {
                    if (evnt.mouseButton.x >= 200 && evnt.mouseButton.x <= 450 && evnt.mouseButton.y >= 510 && evnt.mouseButton.y <= 560)
                    {
                        game_over.close();
                        main_menu_window();
                    }
                    else if (evnt.mouseButton.x >= 200 && evnt.mouseButton.x <= 450 && evnt.mouseButton.y >= 370 && evnt.mouseButton.y <= 420)
                    {
                        page_number = 0;
                        bonus_start = 0;
                        pop_cnt = 0;
                        pop_start = false;
                        total_score = 0;
                        levelnum = 0;
                        bubble_isfound();
                        rand_color();
                        game_over.close();
                        cnt_help1 = 0;
                        cnt_help2 = 0;
                        cnt_help3 = 0;
                        game_window();

                    }
                }
                break;
            }
        }
        game_over.clear();
        game_over.draw(back_ground_sprite);
        game_over.draw(main_menu);
        game_over.draw(play_again);
        game_over.draw(game_over_name_sprite);
        game_over.draw(player_score);
        game_over.draw(high_score_game_over);
        game_over.draw(image1_sprite);
        game_over.draw(image2_sprite);
        game_over.draw(image3_sprite);
        game_over.draw(image4_sprite);
        game_over.display();
    }

}
void Enter_name_player()
{
    The_Name game(700, 800);
    bool write = false;
    RenderWindow window(VideoMode(700, 800), "User Name");
    Event event;
    Font font;
    font.loadFromFile("Data/Avara.otf");
    string playerInput = "";
    Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(35);
    playerText.setFillColor(Color::Black);
    playerText.setPosition(110, 425);
    Text erorr, Next_button;
    erorr.setFont(font);
    erorr.setString("* Warning..! You've exceeded allowed number of characters. *");
    erorr.setCharacterSize(16);
    erorr.setOutlineThickness(1);
    erorr.setFillColor(Color::Red);
    erorr.setPosition(110, 510);
    bool erorr_text = false, erorr_text2 = false;
    //Next
    Next_button.setFont(font);
    Next_button.setString("Next");
    Next_button.setCharacterSize(50);
    Next_button.setFillColor(Color::White);
    Next_button.setOutlineThickness(10);
    Next_button.setPosition(Vector2f(280, 600));
    Text erorr2;
    erorr2.setFont(font);
    erorr2.setString("* Please enter your name *");
    erorr2.setCharacterSize(16);
    erorr2.setOutlineThickness(1);
    erorr2.setFillColor(Color::Red);
    erorr2.setPosition(240, 660);
    Texture back_ground;
    Sprite back_ground_sprite;
    back_ground.loadFromFile("Icons/back_ground9.jpg");
    back_ground_sprite.setTexture(back_ground);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                page_number = 3;
                window.close();
            }
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if ((playerInput.size() == 20 && event.text.unicode != '\b') || event.text.unicode == ' ')
                    {
                        if (event.text.unicode != ' ')
                            erorr_text = true;
                        continue;

                    }
                    else if (event.text.unicode != '\b')
                    {
                        playerInput += static_cast<char>(event.text.unicode);
                        write = true;
                        erorr_text2 = false;
                        erorr_text = false;
                        playerText.setString(playerInput);
                    }
                    else if (playerInput.size() == 0 && write == true) {
                        continue;
                    }
                    else
                    {
                        erorr_text = false;
                        playerInput.erase(playerInput.size() - 1, 1);
                        playerText.setString(playerInput);
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (event.mouseButton.x >= 280 && event.mouseButton.x <= 400 && event.mouseButton.y >= 600 && event.mouseButton.y <= 650 && playerInput.size() > 0)
                {
                    Name = playerInput;
                    erorr_text2 = false;
                    window.close();
                }
                else if (event.mouseButton.x >= 280 && event.mouseButton.x <= 400 && event.mouseButton.y >= 600 && event.mouseButton.y <= 650 && playerInput.size() == 0)
                {
                    erorr_text2 = true;
                }
            }
            if (event.type == Event::MouseMoved)
            {
                if (event.mouseMove.x >= 280 && event.mouseMove.x <= 400 && event.mouseMove.y >= 600 && event.mouseMove.y <= 650)
                {
                    Next_button.setFillColor(Color::Blue);
                }
                else
                {
                    Next_button.setFillColor(Color::White);
                }
            }
        }
        window.clear();
        window.draw(back_ground_sprite);
        game.draw(window);
        if (erorr_text)
        {
            window.draw(erorr);
        }
        if (erorr_text2)
        {
            window.draw(erorr2);
        }
        window.draw(Next_button);
        window.draw(playerText);
        window.display();
    }
}
void pause_window(RenderWindow& game)
{
    Pause game2(700, 800);
    RenderWindow window(VideoMode(700, 800), "Pause", Default);
    if (sound)
        sound_texture.loadFromFile("Icons/Sound.png");
    else
        sound_texture.loadFromFile("Icons/Muted_Sound.png");
    sound_sprite.setTexture(sound_texture);
    sound_sprite.setPosition(30, 700);
    Sprite back_ground_sprite;
    back_ground_sprite.setTexture(game_back_ground);
    //game.music();
    Event ev;
    int page_number2 = -1;
    while (window.isOpen()) {

        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
                page_number2 = 3;
                page_number = 3;
                break;
            }
            if (ev.MouseMoved)
            {
                if (ev.mouseMove.x >= 237 && ev.mouseMove.x <= 469 && ev.mouseMove.y >= 252 && ev.mouseMove.y <= 305)
                {
                    page_number2 = 0;
                    game2.change_color(page_number2);
                    game2.return_color(page_number2);
                    break;
                }
                else if (ev.mouseMove.x >= 220 && ev.mouseMove.x <= 502 && ev.mouseMove.y >= 402 && ev.mouseMove.y <= 453)
                {
                    page_number2 = 1;
                    game2.change_color(page_number2);
                    game2.return_color(page_number2);
                    break;
                }
                else if (ev.mouseMove.x >= 295 && ev.mouseMove.x <= 406 && ev.mouseMove.y >= 551 && ev.mouseMove.y <= 605)
                {
                    page_number2 = 2;
                    game2.change_color(page_number2);
                    game2.return_color(page_number2);
                    break;
                }
                else
                {
                    game2.return_all_colors();
                }
            }
            if (ev.type == Event::MouseButtonPressed)
            {
                if (ev.mouseButton.button == Mouse::Left)
                {
                    if (ev.mouseButton.x >= 237 && ev.mouseButton.x <= 469 && ev.mouseButton.y >= 252 && ev.mouseButton.y <= 305)
                    {
                        window.close();
                        game_window();
                        //game.music();
                        break;
                    }
                    if (ev.mouseButton.x >= 220 && ev.mouseButton.x <= 502 && ev.mouseButton.y >= 402 && ev.mouseButton.y <= 453)
                    {
                        window.close();
                        game.close();
                        main_menu_window();
                        //game.music();
                        break;
                    }
                    if (ev.mouseButton.x >= 295 && ev.mouseButton.x <= 406 && ev.mouseButton.y >= 551 && ev.mouseButton.y <= 605)
                    {
                        window.close();
                        game.close();
                        page_number = 3;
                        //game.music();
                        break;
                    }
                    if (ev.mouseButton.x >= 30 && ev.mouseButton.x <= 125 && ev.mouseButton.y >= 700 && ev.mouseButton.y <= 793)
                    {
                        if (sound)
                        {
                            sound = false;
                            music.pause();
                        }
                        else
                        {
                            sound = true;
                            music.play();
                        }
                        if (sound)
                        {
                            sound_texture.loadFromFile("Icons/Sound.png");
                        }
                        else
                            sound_texture.loadFromFile("Icons/Muted_Sound.png");
                        sound_sprite.setTexture(sound_texture);
                    }
                }
            }
        }
        window.clear();
        window.draw(back_ground_sprite);
        game2.draw(window);
        window.draw(sound_sprite);
        window.display();
    }
}
void About_Us_window()
{
    RenderWindow window(VideoMode(700, 800), "About Us", Default);
    Event ev;
    Font font;
    Text main_menu,Zeyad_txt, Ziad_txt, Andrew_txt, Abdullah_txt, Nourhan_txt, Naryman_txt, Tarek_txt;
    if (font.loadFromFile("Data/Avara.otf") == false)
    {
        cout << "Error loading Font file!";
        exit(1);
    }
    font.loadFromFile("Data/Avara.otf");
    main_menu.setFont(font);
    main_menu.setCharacterSize(17);
    main_menu.setFillColor(Color::White);
    main_menu.setOutlineColor(Color::Black);
    main_menu.setOutlineThickness(3);
    main_menu.setString("Main Menu >>");
    main_menu.setPosition(575, 775);
    Texture back_ground;
    Sprite back_ground_sprite;
    back_ground.loadFromFile("Icons/back_ground12.png");
    back_ground_sprite.setTexture(back_ground);
   // Texture Zeyad,Ziad,Andrew,Abdullah,Nourhan,Naryman,Tarek;
   // Sprite Zeyad_sprite, Ziad_sprite, Andrew_sprite, Abdullah_sprite, Nourhan_sprite, Naryman_sprite, Tarek_sprite;
   // //Zeyad
   // Zeyad.loadFromFile("Zeyad.jpg");
   // Zeyad_sprite.setTexture(Zeyad);
   // Zeyad_sprite.setPosition(286,290);
   // Zeyad_sprite.setScale(0.33f, 0.33f);
   // Zeyad_txt.setFont(font);
   // Zeyad_txt.setCharacterSize(21);
   // Zeyad_txt.setFillColor(Color::White);
   // Zeyad_txt.setOutlineColor(Color::Black);
   // Zeyad_txt.setOutlineThickness(3);
   // Zeyad_txt.setString("Zeyad . A");
   // Zeyad_txt.setPosition(292, 495);
   // //Ziad
   // Ziad.loadFromFile("Ziad.jpg");
   // Ziad_sprite.setTexture(Ziad);
   // Ziad_sprite.setPosition(500, 297);
   // Ziad_sprite.setScale(0.36f, 0.36f);
   // Ziad_txt.setFont(font);
   // Ziad_txt.setCharacterSize(21);
   // Ziad_txt.setFillColor(Color::White);
   // Ziad_txt.setOutlineColor(Color::Black);
   // Ziad_txt.setOutlineThickness(3);
   // Ziad_txt.setString("Ziad . S");
   // Ziad_txt.setPosition(530, 492);
   // //Abdullah
   // Abdullah.loadFromFile("Abdullah.jpg");
   // Abdullah_sprite.setTexture(Abdullah);
   // Abdullah_sprite.setPosition(390, 560);
   // Abdullah_sprite.setScale(0.43f, 0.43f);
   // Abdullah_txt.setFont(font);
   // Abdullah_txt.setCharacterSize(21);
   // Abdullah_txt.setFillColor(Color::White);
   // Abdullah_txt.setOutlineColor(Color::Black);
   // Abdullah_txt.setOutlineThickness(3);
   // Abdullah_txt.setString("Abdullah");
   // Abdullah_txt.setPosition(400, 760);
   // //Andrew
   // Andrew.loadFromFile("Andrew.jpg");
   // Andrew_sprite.setTexture(Andrew);
   // Andrew_sprite.setPosition(80, 290);
   // Andrew_sprite.setScale(0.3f, 0.3f);
   // Andrew_txt.setFont(font);
   // Andrew_txt.setCharacterSize(21);
   // Andrew_txt.setFillColor(Color::White);
   // Andrew_txt.setOutlineColor(Color::Black);
   // Andrew_txt.setOutlineThickness(3);
   // Andrew_txt.setString("Andrew");
   // Andrew_txt.setPosition(85, 492);
   // //Tarek
   // Tarek.loadFromFile("Tarek.jpg");
   // Tarek_sprite.setTexture(Tarek);
   // Tarek_sprite.setPosition(180, 560);
   // Tarek_sprite.setScale(0.34f, 0.34f);
   // Tarek_txt.setFont(font);
   // Tarek_txt.setCharacterSize(21);
   // Tarek_txt.setFillColor(Color::White);
   // Tarek_txt.setOutlineColor(Color::Black);
   // Tarek_txt.setOutlineThickness(3);
   // Tarek_txt.setString("Tarek");
   // Tarek_txt.setPosition(198, 757);
   // //Nourhan
   // Nourhan.loadFromFile("Nourhan.jpg");
   // Nourhan_sprite.setTexture(Nourhan);
   // Nourhan_sprite.setPosition(410, 30);
   // Nourhan_sprite.setScale(0.3f, 0.3f);
   // Nourhan_txt.setFont(font);
   // Nourhan_txt.setCharacterSize(21);
   // Nourhan_txt.setFillColor(Color::White);
   // Nourhan_txt.setOutlineColor(Color::Black);
   // Nourhan_txt.setOutlineThickness(3);
   // Nourhan_txt.setString("Nourhan");
   // Nourhan_txt.setPosition(404, 225);
   // //Naryman
   // Naryman.loadFromFile("Naryman.jpg");
   // Naryman_sprite.setTexture(Naryman);
   // Naryman_sprite.setPosition(180, 35);
   // Naryman_sprite.setScale(0.44f, 0.44f);
   // Naryman_txt.setFont(font);
   // Naryman_txt.setCharacterSize(21);
   // Naryman_txt.setFillColor(Color::White);
   // Naryman_txt.setOutlineColor(Color::Black);
   // Naryman_txt.setOutlineThickness(3);
   // Naryman_txt.setString("Naryman");
   // Naryman_txt.setPosition(183, 225);
   //Texture image1,image5, image6, image7, image8;
   //Sprite image1_sprite, image2_sprite, image3_sprite, image4_sprite, image5_sprite, image6_sprite, image7_sprite, image8_sprite;
   //image1.loadFromFile("Icons/image 7.png");
   //image1_sprite.setTexture(image1);
   //image1_sprite.setPosition(325, 105);
   //image2_sprite.setTexture(image1);
   //image2_sprite.setPosition(210, 380);
   //image3_sprite.setTexture(image1);
   //image3_sprite.setPosition(428, 378);
   //image4_sprite.setTexture(image1);
   //image4_sprite.setPosition(315, 620);
   //image5.loadFromFile("Icons/image 29.png");
   //image5_sprite.setTexture(image5);
   //image5_sprite.setPosition(510, 570);
   //image5_sprite.setScale(0.75f, 0.75f);
   //image6.loadFromFile("Icons/image 8.png");
   //image6_sprite.setTexture(image6);
   //image6_sprite.setPosition(497, 65);
   //image6_sprite.setScale(0.45f, 0.45f);
   //image7.loadFromFile("Icons/image 1.png");
   //image7_sprite.setTexture(image7);
   //image7_sprite.setPosition(5, 85);
   //image7_sprite.setScale(0.75f, 0.75f);
   //image8.loadFromFile("Icons/image 3.png");
   //image8_sprite.setTexture(image8);
   //image8_sprite.setPosition(25, 610);
    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                page_number = 3;
                window.close();
            }
            if (ev.MouseMoved)
            {
                if (ev.mouseMove.x >= 573 && ev.mouseMove.x <= 690 && ev.mouseMove.y >= 773 && ev.mouseMove.y <= 792)
                {
                    main_menu.setFillColor(Color::Blue);
                    break;
                }
                else
                {
                    main_menu.setFillColor(Color::White);
                }
            }
            if (ev.type == Event::MouseButtonPressed)
            {
                if (ev.mouseButton.button == Mouse::Left)
                {
                    if (ev.mouseButton.x >= 573 && ev.mouseButton.x <= 690 && ev.mouseButton.y >= 773 && ev.mouseButton.y <= 792)
                    {
                        cout << "to main menu" << endl;
                        window.close();
                        main_menu_window();
                    }
                }
            }
        }
        window.clear();
        window.draw(back_ground_sprite);
        //window.draw(Zeyad_sprite);
        //window.draw(Zeyad_txt);
        //window.draw(Ziad_sprite);
        //window.draw(Ziad_txt);
        //window.draw(Abdullah_sprite);
        //window.draw(Abdullah_txt);
        //window.draw(Andrew_sprite);
        //window.draw(Andrew_txt);
        //window.draw(Tarek_sprite);
        //window.draw(Tarek_txt);
        //window.draw(Nourhan_sprite);
        //window.draw(Nourhan_txt);
        //window.draw(Naryman_sprite);
        //window.draw(Naryman_txt);
        //window.draw(image1_sprite);
        //window.draw(image2_sprite);
        //window.draw(image3_sprite);
        //window.draw(image4_sprite);
        //window.draw(image5_sprite);
        //window.draw(image6_sprite);
        //window.draw(image7_sprite);
        //window.draw(image8_sprite);
        window.draw(main_menu);
        window.display();
    }
}
int main()
{
    zezo_atef
        music.openFromFile("Corona-320bit.wav");
    music.play();
    music.setLoop(true);
    music.setVolume(70);
    main_menu_window();
    while (true)
    {
        if (page_number == -1 && mainmenu)
        {
            main_menu_window();
        }
        else if (page_number == 0) {
            //play
            game_window();
        }
        else if (page_number == 1) {
            //scoreborad
            displayScores();
        }
        else if (page_number == 2) {
            //scoreborad
            About_Us_window();
        }
        else if (page_number == 3) {
            //Exit
            break;
        }
    }
    return 0;
}