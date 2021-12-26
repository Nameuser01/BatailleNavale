#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void menu()
{
    cout<<"---------- Menu de s\202l\202ction ----------\n"<<endl;
    cout<<"q  : quitter le programme"<<endl;
    cout<<"lb : lancer une partie contre un bot"<<endl;
    cout<<"ap : afficher votre pseudo"<<endl;
    cout<<"cp : changer de pseudo"<<endl;
    cout<<"h  : afficher l'aide (ce menu)"<<endl;
}


void print_user_board(int user_board[], string name_user)  // affichage des bateaux de l'utilisateur
{
    cout<<"\n\n--- "<<name_user<<" board ---"<<endl;
    for (int a = 0; a < 8; a+=3)
    {
        for (int i = a ; i < (a+3) ; i++)
        {
            if(user_board[i] == 0)  // designe la mer
            {
                cout<<"* ";
            }
            else if(user_board[i] == 1)  // designe une case touchee mais qui ne contient pas de bateau
            {
                // rajouter des if else pour que si i = 0 on ajoute B
                cout<<"0 ";
            }
            else if(user_board[i] == 2)  // designe une case touchee qui contient un bateau
            {
                // rajouter des if else pour que si i = 0 on ajoute C
                cout<<"1 ";
            }
            else
            {
                cout<<"DEBEUG : user_board[i] vaut :"<<user_board[i]<<" : FIN_DEBEUG"<<endl;
            }
        }
        cout<<""<<endl;
    }
}


void print_bot_board(int bot_board[], string name_bot) // affichage des points touchés par l'utilisateur
{
    cout<<"--- "<<name_bot<<" board ---"<<endl;
    for (int a = 0; a < 8; a += 3)
    {
        for (int i = a; i < (a+3); i++)
        {
            if(bot_board[i] == 0) // case inconnue
            {
                cout<<"* ";
            }
            else if (bot_board[i] == 1) // bateau touché
            {
                cout<<"1 ";
            }
            else if (bot_board[i] == 2) // mer touchée
            {
                cout<<"2 ";
            }
        }
        cout<<""<<endl;
    }
}

void game_rules() // Afficher les règles du Jeu
{
        cout<<"Regles du jeu :"<<endl;
        cout<<"Heuuu. Le jeu essaie lui même d'atteindre les règles d'une vrai bataille navale..."<<endl;
}


int main()
{
    string name_user("default_name"), name_bot("Default_value"), namelist[4];
    bool endgame = true, end_partie_1(0);
    namelist[0] = "Aprilbot";
    namelist[1] = "Bender";
    namelist[2] = "nightBot";
    namelist[3] = "MEE6";
    int id_name_bot(0), user_score(0), bot_score(0), max_score(4)/*modify*/, user_board[9], bot_board[9], bot_printed_board[9], boat[3], choix(10), i_rep(0);
    string action_choice = "idk";
    boat[0] = 0;
    boat[1] = 0;
    boat[2] = 0;

    srand((unsigned int)time(0));
    cout << "Quel est ton pseudo ?" << endl;
    cout << "> ";
    cin >> name_user ;
    cout << "\n\n" << endl;
    while(endgame == true)
    {
        menu();
        cout<<"Que voulez vous faire ?"<<endl;
        cout<<"> ";cin>>action_choice; // Si l'entrée est un caractère, ca boucle à l'infini ;-(
        cout<<"\n\n"<<endl;
        if (action_choice == "q" or action_choice == "quit" or action_choice == "exit")  // Quitter le jeu
        {
            cout<<"\n\nFermeture du programme."<<endl;
            endgame = false;
        }
        else if (action_choice == "start") // Lancer une partie
        {
            name_bot = namelist[(rand()%4 +1)];//Tirage au sort du nom du bot
            cout<<name_user<<" tu vas jouer contre le bot "<<name_bot<<endl;

            //Placement des bateaux
            while(boat[0] == boat[1] || boat[0] == boat[2] || boat[1] == boat[2])
            {
                for (int i = 0 ; i < 3; i++)
                {
                    boat[i] = rand()%8;
                }
            }

            for(int y = 0; y < 3; y++)  // (debeug): Affiche les positions des pièces ennemies
            {
                cout<<boat[y]<<" = boat["<<y<<"]"<<endl;
            }

            for (int i = 0 ; i <= 8 ; i++)  // remplissage/reset de la planche de jeu
            {
                user_board[i] = 0;
                bot_board[i] = 0;
                bot_printed_board[i] = 0;
            }
            for (int y = 0; y < 3; y++)
            {
                bot_board[boat[y]] = 1;
            }
            while (user_score < 3 && bot_score < 3)  // Coeur de la partie
            {
                for (int e = 0 ; e < 1 ; e++)  // affichage de la planche de jeu
                {
                    // print_user_board(&user_board[e], name_user);  // affichage de la planche utlisateur
                    print_bot_board(&bot_printed_board[e], name_bot);
                }
                while (choix < 0 || choix > 8)
                {
                    cout<<name_user<<", sur quelle case voulez tirer ?\n> "; cin >> choix;
                }
                if (bot_board[choix] == 0)//watter
                {
                    bot_board[choix] = 2;
                    bot_printed_board[choix] = 2;
                    cout<<"\nLoupé\n"<<endl;
                }
                else if (bot_board[choix] == 1)//batteau ennemi touché
                {
                    bot_board[choix] = 1;
                    bot_printed_board[choix] = 1;
                    user_score += 1;
                    cout<<"\nTouché ! Dans le mille\n"<<endl;
                }
                else
                {
                    cout<<"Erreur de condition"<<endl;
                }
                choix = 10;
            }
            //Fin de la partie reset des plateaux
            for (int i = 0 ; i <= 8 ; i++)
            {
                user_board[i] = 0;
                bot_board[i] = 0;
                bot_printed_board[i] = 0;
            }
            boat[0] = 0;
            boat[1] = 0;
            boat[2] = 0;
            bot_score = 0;
            user_score = 0;
        }
        else if (action_choice == "ap")  // afficher le pseudo
        {
            cout<<"Votre nom en jeu est : "<<name_user<<"\n"<<endl;
        }
        else if (action_choice == "cp")  // Changer son pseudo
        {
            cout<<"Veuillez indiquer votre nouveau nom ci-dessous :"<<endl;
            cout<<"> ";cin>>name_user;
            cout<<"Vous vous appellez maintenant : "<<name_user<<"\n"<<endl;
        }
        else if (action_choice == "rules")  // Afficher les regles du jeu
        {
            cout<<"\n"<<endl;
            game_rules();
        }
        else if (action_choice == "menu")  // afficher le menu
        {
            menu();
        }
        else
        {
            cout<<"Erreur: Mauvaise saisie."<<endl;
            action_choice = "idk";
        }
    }
    return 0;
}
