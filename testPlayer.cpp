#include <iostream>
#include "Player.h"
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEnginerDriver.cpp"

//using namespace std;

int main()
{












    cout << "player\n";
    


    vector<Territory> territoriesV;
    vector<Territory>* territoriesVptr;
    territoriesVptr = &territoriesV;
    vector<Territory*> territoriesVptrp;
    territoriesVptrp;
    vector<Continent*> c1ptr;
    vector<Continent> c1;

    Territory* t1 = new Territory;
    t1->setName("t1");
    Territory* t2 = new Territory;
    t2->setName("t2");
    Territory* t3 = new Territory;
    t3->setName("t3");
    Territory* t4 = new Territory;
    t4->setName("t4");
    Territory* t5 = new Territory;
    t5->setName("t5");
    Territory* t6 = new Territory;
    t6->setName("t6");
    Player player("userInput");
    player.occupy(t1);

    t1->addAjacentTerritory(t2);
    t1->addAjacentTerritory(t3);
    vector<Territory*> tAdj1 = t1->getAdjacentTerritories();
    string str = tAdj1.at(1)->getName();
    cout << str;
    t1->addAjacentTerritory(t2);
    t1->addAjacentTerritory(t2);


    testPlayer();


    //testGameStates();
    testCards();

/*    {
        Player testPlayer("testPlayer", 0),
            a("Player a", 1),
            b("Player b", 2),
            c("Player c", 3),
            d("Player d", 4),
            defultPlayer;
        std::vector <Player> playerVector;
        playerVector.push_back(a);
        playerVector.push_back(b);
        playerVector.push_back(c);
        playerVector.push_back(d);
        playerVector.push_back(testPlayer);

        cout <<
            testPlayer.getPlayerName() << "\n"
            << a.getPlayerName() << "\n";
        d.attack(a);

        Territory t1("t01");
        Territory t2("t02");
        Territory t3("t03");
        Territory t4("t04");
        Territory t5("t05");
        Territory t6("t06");
        Territory t7("t07");
        Territory t8("t08");

        a.occupy(t1);
        a.occupy(t2);
        a.occupy(t3);
        a.occupy(t4);
        a.occupy(t5);

        //a.displayerOcc();
        cout << a.pid << "\t" << b.pid << "\t" << c.pid << "\t" << a.pid << "\t" << d.pid;
        
        b.occupy(a);
       // b.displayerOcc();
        vector <Territory> occVector = a.toDefend();
        vector<Territory>* ptr = &occVector;
        Player::displayOcc(*ptr);
        cout << a.pid << "\t" << b.pid << "\t" << c.pid << "\t" << a.pid << "\t" << d.pid;

    }
*/


    // defultPlayer.toAttack(playerVector);




}

string displayTerritoryname(vector<Territory*> v) {
    string str = v.at(1)->getName();
    return displayTerritoryname(v);
}
string displayTerritoryname(vector<Territory> v) {
    string str = v.at(1).getName();
    return str;
}