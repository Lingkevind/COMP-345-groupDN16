//#include <iostream>
//#include "Player.h"
//
////using namespace std;
//
//int main()
//{
//
//    cout << "player\n";
///*    {
//        Player testPlayer("testPlayer", 0),
//            a("Player a", 1),
//            b("Player b", 2),
//            c("Player c", 3),
//            d("Player d", 4),
//            defultPlayer;
//        std::vector <Player> playerVector;
//        playerVector.push_back(a);
//        playerVector.push_back(b);
//        playerVector.push_back(c);
//        playerVector.push_back(d);
//        playerVector.push_back(testPlayer);
//
//        cout <<
//            testPlayer.getPlayerName() << "\n"
//            << a.getPlayerName() << "\n";
//        d.attack(a);
//
//        Territory t1("t01");
//        Territory t2("t02");
//        Territory t3("t03");
//        Territory t4("t04");
//        Territory t5("t05");
//        Territory t6("t06");
//        Territory t7("t07");
//        Territory t8("t08");
//
//        a.occupy(t1);
//        a.occupy(t2);
//        a.occupy(t3);
//        a.occupy(t4);
//        a.occupy(t5);
//
//        //a.displayerOcc();
//        cout << a.pid << "\t" << b.pid << "\t" << c.pid << "\t" << a.pid << "\t" << d.pid;
//        
//        b.occupy(a);
//       // b.displayerOcc();
//        vector <Territory> occVector = a.toDefend();
//        vector<Territory>* ptr = &occVector;
//        Player::displayOcc(*ptr);
//        cout << a.pid << "\t" << b.pid << "\t" << c.pid << "\t" << a.pid << "\t" << d.pid;
//
//    }
//*/
//
//
//    // defultPlayer.toAttack(playerVector);
//    {
//        cout << "welcome!\n comp345 assiignment1 v2" << " now creat new player\n\tplease type your name\n";
//        string userName;
//        cin >> userName;
//       string *nameP = &userName;
//        Player player("userInput",-1);
//        player.setPlayerName(*nameP);
//        cout << "hi!\t" << player.getPlayerName() << "  your player ID is:  " << player.pid;
//        cout << "\nplayer.toAttack()" << "\n";
//      
//           player.displayOcc(player.toAttack());
//        cout << "\nplayer.toDefend()" << "\n";
//      player.displayOcc(player.toDefend());
//
//        player.issueOrder();
//
//    }
//
//
//
//}