//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_DATA_H
#define GAMETOWER_DATA_H

#include <iostream>
#include <fstream>
#include "Map.h"
#include "Player.h"
#include "Behavior.h"

bool dataExist(const string& name) {
    string fileName = name + ".dat";
    std::ifstream dataFile(fileName);
    bool isOpen = dataFile.is_open();
    dataFile.close();
    return isOpen;
}

void saveData(Player &player) {
    // create data
    std::ofstream dataFile(player.getName() + ".dat");
    // player main attributes
    dataFile << player.getHP() << ' ' << player.getName() << endl;
    // player position
    dataFile << player.getPos().line << ' ' << player.getPos().column << endl;
    // player backpack
    dataFile << "B" << endl;
    player.getBackpack().showItemList(dataFile);
    // player word list
    dataFile << "W" << endl;
    player.showWordList(dataFile);
    // player map
    dataFile << "M" << endl;
    player.getMap().showMap(dataFile);
}

void init(Player& player) {
    string name;
    cout << "������������֣�";
    cin >> name;
    if (dataExist(name))
    {
        // if data exists, ask for loading
    }
    else
    {
        saveData(player);
    }
}

void loadGame(Player &player);
void loadData(Player &player)
{
    if (dataExist(player.getName()))
    {
        // if data exists, ask for loading
        std::ifstream dataFile(player.getName() + ".dat");
        // player main attributes
        int hp;
        string name;
        dataFile >> hp >> name;
        player.setHP(hp);
        player.setName(name);
        // player position
        int line, column;
        dataFile >> line >> column;
        player.setPos(line, column);
        // player backpack
        string type;
        dataFile >> type;
        if (type == "B")
        {
            player.getBackpack().loadItemList(dataFile);
        }
        // player word list
        dataFile >> type;
        if (type == "W")
        {
            player.loadWordList(dataFile);
        }
        // player map
        dataFile >> type;
        if (type == "M")
        {
            player.getMap().loadMap(dataFile);
        }
    }
    else
    {
        // data does not exist, create new data
        cout << "���ݲ����ڣ������´浵" << endl;
        saveData(player);
    }
}

void newGame(Player &player) {
    system("cls");
    loadGame(player);
    system("pause");
}

void loadGame(Player &player) {
    loadData(player);
    Map::printMap();
    onMap(player);
    saveData(player);
    goodbye();
    system("pause");
}




#endif //GAMETOWER_DATA_H