#include <SFML/Graphics.hpp>
#include <SFMl/Audio.hpp>
#include <vector>
#include <iostream>
#include <iterator>
#include "CardObj.h"
#include "TextObj.h"
#include <algorithm>
#include <chrono>
#include <random>


using namespace sf;
using namespace std;

unsigned text_seed = std::chrono::system_clock::now().time_since_epoch().count();
unsigned storey_seed = std::chrono::system_clock::now().time_since_epoch().count();

int window_width = 900;
int window_height = 1600;
int total_card_num = 0;
int num_of_type = 7;
int num_of_card_set_per_type = 0;

float card_side_length = 70.f;

std::vector<Texture> card_faces;


enum game_status {
    main_menu,
    in_game,
    win,
    fail
};

void card_insertion(std::vector<CardObj>& target, CardObj card) {
    std::cout << "in insertion card type: " << card.get_card_type() << '\n';
    if (target.size() <= 1)
        target.push_back(card);
    else {
        for (auto i = target.begin(); i != target.end(); ++i) {
            std::cout << "type in selected: " << i->get_card_type() << " type in card: " << card.get_card_type() << '\n';
            if (i->get_card_type() == card.get_card_type()) {
                std::cout << "Insert at: " << distance(target.begin(), i) + 1 << '\n';
                target.insert(i + 1, card); //insert at the back of the same card
                break;
            }
            else if (i == target.end() - 1) {
                target.push_back(card);
                break;
            }
            else
                continue;
        }
    }
}


std::vector<CardObj> init_storey(int total, int types, int npr, int npc) { //npr = num per row
    if ((total / types) % 3 != 0)
        cout << "error: (total / types) % 3 != 0" << endl;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<CardObj> cards;
    for (int i = 0; i != types; ++i) {
        for (int j = 0; j != total / types; ++j) {
            int type = i + 1;
            CardObj t_cards(70.f, type);
            switch (type) {
            case 1: t_cards.setFillColor(Color::Red); break;
            case 2: t_cards.setFillColor(Color::Blue); break;
            case 3: t_cards.setFillColor(Color::Yellow); break;
            case 4: t_cards.setFillColor(Color::Green); break;
            }
            cards.push_back(t_cards);
        }
    }

    //std::random_shuffle(cards.begin(), cards.end());
    
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    for (int i = 0; i != npr; ++i) {
        for (int j = 0; j != npc; ++j) {
            cards[i * npc + j].setPosition((float)(72 * i + 42 * (i + 1)), 42 * (j + 1) + 72 * j);
        }
    }

    return cards;
}

std::vector<CardObj> init_all_cards(int total, int types, int npr, int npc) { //npr = num per row
    if ((total / types) % 3 != 0)
        throw "error: (total / types) % 3 != 0";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<CardObj> cards;
    for (int i = 0; i != types; ++i) {
        for (int j = 0; j != total / types; ++j) {
            int type = i + 1;
            CardObj t_cards(card_side_length, type);
            switch (type) {
                case 1: t_cards.setFillColor(Color::Red); break;
                case 2: t_cards.setFillColor(Color::Blue); break;
                case 3: t_cards.setFillColor(Color::Yellow); break;
                case 4: t_cards.setFillColor(Color::Green); break;
            }
            cards.push_back(t_cards);
        }
    }

    //std::random_shuffle(cards.begin(), cards.end());

    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    for (int i = 0; i != npr; ++i) {
        for (int j = 0; j != npc; ++j) {
            cards[i * npc + j].setPosition((float)(72 * i + 42 * (i + 1)), 42 * (j + 1) + 72 * j);
        }
    }

    return cards;
}


std::vector<CardObj> init_every_cards(int total, int types) {
    if ((total / types) % 3 != 0)                                       //both offsets should be over 72, both spaces should be over 42;
        throw "error: (total / types) % 3 != 0";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<CardObj> cards;
    for (int i = 0; i != types; ++i) {
        for (int j = 0; j != total / types; ++j) {
            int type = i + 1;
            CardObj t_cards(70.f, type);
            switch (type) {
            case 1: t_cards.setFillColor(Color::Red); break;
            case 2: t_cards.setFillColor(Color::Blue); break;
            case 3: t_cards.setFillColor(Color::Yellow); break;
            case 4: t_cards.setFillColor(Color::Green); break;
            }
            cards.push_back(t_cards);
        }
    }


    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    return cards;
}


std::vector<CardObj> init_every_cards_2(int total, int types, vector<vector<int> > level_data) {
    if ((total / types) % 3 != 0)
        cout << "error: (total / types) % 3 != 0" << endl;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<CardObj> cards;
    int id = 0;
    for (int i = 0; i != types; ++i) {
        for (int j = 0; j != total / types; ++j) {
            int type = i + 1;
            CardObj t_cards(70.f, type);
            switch (type) {
                case 1: t_cards.setTexture(&card_faces[0]); break;
                case 2: t_cards.setTexture(&card_faces[1]); break;
                case 3: t_cards.setTexture(&card_faces[2]); break;
                case 4: t_cards.setTexture(&card_faces[3]); break;
                case 5: t_cards.setTexture(&card_faces[4]); break;
                case 6: t_cards.setTexture(&card_faces[5]); break;
                case 7: t_cards.setTexture(&card_faces[6]); break;
            }
            t_cards.set_card_id(id++);
            cards.push_back(t_cards);
        }
    }

    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));

    int pointer = 0;
    int storey_level = -1;
    for (auto i : level_data) {
        int npr = i[0];
        int npc = i[1];
        int h_offset = i[2];
        int v_offset = i[3];
        int h_space_to_edge = i[4];
        int v_space_to_edge = i[5];
        ++storey_level;
        int end = pointer + npc * npr;
        while (pointer < end && pointer < cards.size()) {
            cards[pointer].set_card_storey(storey_level);
            int m = (pointer % (npc * npr)) % npr;
            int n = (pointer % (npc * npr)) / npr;
            int x = h_offset * m + h_space_to_edge + 70 * m; // card length + space
            int y = v_offset * n + v_space_to_edge + 70 * n;
            cards[pointer].setPosition((float) x, (float)y);

            for (int before = 0; before != pointer && storey_level > 0; ++before) {
                if(cards[pointer].getGlobalBounds().intersects(cards[before].getGlobalBounds()) && cards[before].get_card_availability()) {
                    Color current_color = cards[before].getFillColor();
                    current_color.r *= 0.5f;
                    current_color.g *= 0.5f;
                    current_color.b *= 0.5f;
                    cards[before].setFillColor(current_color);
                    cards[before].set_card_availability(false);
                }
            }
            ++pointer;
        }
    }

    cout << "Card pile initiated!" << endl;

    return cards;
}


void reveal_cards(vector<CardObj>::iterator& current, vector<CardObj>& cards) {
    vector<CardObj*> overlapped;

    for (auto &i : cards) {
        if(i.get_card_id() != current->get_card_id() && i.getGlobalBounds().intersects(current->getGlobalBounds())){
            overlapped.push_back(&i);
        }
    }

    for (const auto& i : overlapped) {
        cout << "?!" << endl;
        bool availability = true;
        for (auto j : cards) {
            //cout << "!" << endl;
            if (j.get_card_id() != current->get_card_id() && j.get_card_storey() > i->get_card_storey() && i->getGlobalBounds().intersects(j.getGlobalBounds())) {
                availability = false;
                cout << "!" << endl;
            }

        }

        if (availability) {
            Color current_color = i->getFillColor();
            current_color.r /= 0.5f;
            current_color.g /= 0.5f;
            current_color.b /= 0.5f;
            i->setFillColor(current_color);
            i->set_card_availability(availability);
        }

    }
}

vector<vector<int> > level_generate() {
    vector<vector<int> > rslt;
    int storey;
    storey = (storey_seed % (16 - 8)) + 8;

    for (int i = 0; i != storey; ++i) {
        unsigned npr_seed = std::chrono::system_clock::now().time_since_epoch().count();
        unsigned npc_seed = std::chrono::system_clock::now().time_since_epoch().count();
        unsigned space_seed = std::chrono::system_clock::now().time_since_epoch().count();
        vector<int> temp;
        int npr = (npr_seed % (7 - 4)) + 4;
        int npc = (npc_seed % (11 - 4)) + 4;
        int h_offset = (npr_seed % (window_width - 150 - npr * 70)) / npr > 40 ?
                       (npr_seed % (window_width - 150 - npr * 70)) / npr : 40;
        int v_offset = (npc_seed % (window_height - 300 - npc * 70)) / npc > 40 ?
                       (npc_seed % (window_height - 300 - npc * 70)) / npc > 40 : 40;
        int h_space_to_edge = space_seed % 120 > 40 ? space_seed % 120 : 40;
        int v_space_to_edge = space_seed % 150 > 40 ? space_seed % 150 : 40;
        temp.push_back(npr);
        temp.push_back(npc);
        temp.push_back(h_offset);
        temp.push_back(v_offset);
        temp.push_back(h_space_to_edge);
        temp.push_back(v_space_to_edge);
        rslt.push_back(temp);
        total_card_num += npr * npc;
    }

    while (num_of_type * 3 + num_of_type * 3 * num_of_card_set_per_type < total_card_num) {
        ++num_of_card_set_per_type;
    }

    return rslt;
}





int main() {
    RenderWindow window(VideoMode(window_width, window_height), L"鸡了个鸡");
    window.setFramerateLimit(200);

    cout << "Window created!" << endl;

    std::vector<CardObj> each_storey_of_cards;
    //std::vector<std::vector<CardObj> > pile;
    std::vector<CardObj> all_cards;
    std::vector<CardObj> selected;
    std::vector<vector<int> > all_levels;

    std::vector<TextObj> win_text_arr;

    Music main_theme;
    main_theme.openFromFile("../Assets/main_theme.wav");
    main_theme.setVolume(35);
    main_theme.setLoop(true);
    main_theme.play();

    SoundBuffer click_sound_buffer0;
    SoundBuffer erase_sound_buffer0;
    click_sound_buffer0.loadFromFile("../Assets/click0.wav");
    erase_sound_buffer0.loadFromFile("../Assets/erase0.wav");

    Sound click_sound0, erase_sound0;
    click_sound0.setBuffer(click_sound_buffer0);
    click_sound0.setVolume(20);
    erase_sound0.setBuffer(erase_sound_buffer0);
    erase_sound0.setVolume(30);



    Font start_game_font;
    start_game_font.loadFromFile("../Assets/Hiragino Sans GB.ttc");

    TextObj start_game_text(start_game_font, L"鸡了个鸡，\n按enter开始游戏", Color::Black, 70, 100.f, 500.f);

    TextObj win_game_text0(start_game_font, L"个人练习生", Color::Black, 80, 100.f, 650.f);
    TextObj win_game_text1(start_game_font, L"唱，跳，rap，篮球", Color::Black, 80, 70.f, 650.f);
    TextObj win_game_text2(start_game_font, L"鸡你实在是太美", Color::Black, 80, 100.f, 650.f);

    win_text_arr.push_back(win_game_text0);
    win_text_arr.push_back(win_game_text1);
    win_text_arr.push_back(win_game_text2);

    std::shuffle(win_text_arr.begin(), win_text_arr.end(), std::default_random_engine(text_seed));

    TextObj fail_game_text(start_game_font, L"你打篮球像cxk", Color::Black, 90, 90.f, 600.f);

    Texture bkg_image;
    bkg_image.loadFromFile("../Assets/background.jpg");
    RectangleShape background;
    background.setSize(Vector2f(window_width, window_height));
    background.setTexture(&bkg_image);




    for (int i = 0; i != num_of_type; ++i) {
        string file_name = "../Assets/card";
        Texture temp_tex;
        temp_tex.loadFromFile(file_name + to_string(i) + ".jpg");
        card_faces.push_back(temp_tex);
    }


    game_status current_status = main_menu;


    int num_per_row = 6;
    int num_per_col = 6;
    int num_total = 36;
    int num_types = 3;
    int num_storey = 2;
    Vector2i mouse_pos;

    //game level data:
    vector<int> storey0 = {4, 6, 50, 50, 40, 100};
    vector<int> storey1 = {6, 6, 70, 42, 50, 70};
    vector<int> storey2 = {4, 6, 100, 60, 62, 72};


    all_levels.push_back(storey0);
    all_levels.push_back(storey1);
    all_levels.push_back(storey2);

    all_levels = level_generate();

    cout << "Level data loaded" << endl;

    //all_cards = init_every_cards(36, 3);

    //all_cards = init_every_cards_2(84, 7, all_levels);
    all_cards = init_every_cards_2(total_card_num, num_of_type, all_levels);


    cout << "All cards set!" << endl;

    //each_storey_of_cards = init_storey(num_total, num_types, num_per_row, num_per_col);


    Clock clock;
    int time_interval = 0, elapsed = 0;

    while (window.isOpen()) {

        if (current_status == main_menu) {
            Event main_menu_event;
            while (window.pollEvent(main_menu_event)) {
                if (main_menu_event.type == Event::Closed)
                    window.close();
                if (main_menu_event.type == Event::KeyPressed) {
                    if (main_menu_event.key.code == Keyboard::Enter)
                        current_status = in_game;
                }
            }

            window.clear(Color::White);
            window.draw(background);
            window.draw(start_game_text);
            window.display();
        }


        if (current_status == in_game) {
            Event event;
            while (window.pollEvent(event)) {

                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                    window.close();

                if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) {
                    cout << "Left button pressed" << endl;
                    click_sound0.play();
                    auto mouse_pos = Mouse::getPosition(window);
                    //std::cout << "Mouse position x: " << mouse_pos.x << " position y: " << mouse_pos.y << '\n';
                    for (auto i = all_cards.begin(); i != all_cards.end(); ++i) {
                        int x1 = i->getPosition().x;
                        int x2 = x1 + 70;
                        int y1 = i->getPosition().y;
                        int y2 = y1 + 70;
                        //std::cout << "card " << std::distance(cards.begin(), i) << " position x1, x2, y1, y2" << x1 << " " << x2 << " " << y1 << " " << y2 << '\n';
                        if (mouse_pos.x >= x1 && mouse_pos.x <= x2 && mouse_pos.y >= y1 && mouse_pos.y <= y2 && i->get_card_availability()) {
                            i->setScale(1.5f, 1.5f);
                        }

                        if (mouse_pos.x >= x1 && mouse_pos.x <= x2 && mouse_pos.y >= y1 && mouse_pos.y <= y2)
                            cout << "In pile ID: " << i->get_card_id() << endl;
                    }
                }

                if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {

                    //cout << "Left button released, timer started!" << endl;
                    clock.restart();

                    auto mouse_pos = Mouse::getPosition(window);
                    //std::cout << "Mouse position x: " << mouse_pos.x << " position y: " << mouse_pos.y << '\n';

                    for (auto i = all_cards.begin(); i != all_cards.end();) {
                        int x1 = i->getPosition().x;
                        int x2 = x1 + 70;
                        int y1 = i->getPosition().y;
                        int y2 = y1 + 70;
                        //std::cout << "card " << std::distance(cards.begin(), i) << " position x1, x2, y1, y2" << x1 << " " << x2 << " " << y1 << " " << y2 << '\n';
                        if (mouse_pos.x >= x1 && mouse_pos.x <= x2 && mouse_pos.y >= y1 && mouse_pos.y <= y2 && i->get_card_availability()) {
                            //std::cout << "card type: " << i->get_card_type() << '\n';
                            i->setScale(1, 1);
                            card_insertion(selected, *i);

                            reveal_cards(i, all_cards);
                            //std::cout << "Selected size: " << selected.size() << '\n';
                            //cout << "i is: #" << distance(all_cards.begin(), i) << endl;
                            i = all_cards.erase(i);
                            //cout << "After erasing" << endl;
                            //cout << "i is2: #" << distance(all_cards.begin(), i) << endl;
                        }
                        else ++i;
                    }
                }
                //cout << "Event is: " << event.type << endl;
            }

            //cout << "Out event loop" << endl;

            //update
            window.clear(Color::White);
            window.draw(background);
            //draw card pile
            for (auto i : all_cards) {
                window.draw(i);

            }


            //draw selected slots
            if (!selected.empty()) {
                for (int i = 0; i != selected.size(); ++i) {
                    selected[i].setPosition(50.f + 72 * i + 25 * (i + 1), 1300.f);
                    window.draw(selected[i]);
                }

                if (selected.size() >= 3) {
                    window.display();
                    int start = 0, end = 0;
                    for (int i = 0; i != selected.size() - 2; ++i) {
                        start = 0, end = 0;
                        if ((selected[i].get_card_type() == selected[i + 1].get_card_type()) &&
                            (selected[i + 1].get_card_type() == selected[i + 2].get_card_type())) {
                            start = i;
                            end = i + 3;
                            selected[i].setScale(1.2f, 1.2f);
                            selected[i + 1].setScale(1.2f, 1.2f);
                            selected[i + 2].setScale(1.2f, 1.2f);
                            erase_sound0.play();
                            break;
                        }
                    }

                    time_interval = clock.getElapsedTime().asMilliseconds();

                    if (time_interval > 100) {
                        selected.erase(selected.begin() + start, selected.begin() + end);
                        if (selected.size() > 8) {
                            current_status = fail;
                        }
                    }

                }
            }

            if (selected.size() < 3)
                window.display();

            if (!all_cards.size() && !selected.size()) {
                current_status = win;
            }
        }

        if (current_status == win) {
            Event win_game_event;
            while (window.pollEvent(win_game_event)) {

                if (win_game_event.type == Event::Closed)
                    window.close();

                if (win_game_event.type == Event::KeyPressed && win_game_event.key.code == Keyboard::Escape)
                    window.close();
            }

            window.clear(Color::White);
            window.draw(background);
            window.draw(win_text_arr[0]);
            window.display();
        }


        if (current_status == fail) {
            Event end_game_event;
            while (window.pollEvent(end_game_event)) {

                if (end_game_event.type == Event::Closed)
                    window.close();

                if (end_game_event.type == Event::KeyPressed && end_game_event.key.code == Keyboard::Escape)
                    window.close();
            }

            window.clear(Color::White);
            window.draw(background);
            window.draw(fail_game_text);
            window.display();
        }



    }
    return 0;
}




