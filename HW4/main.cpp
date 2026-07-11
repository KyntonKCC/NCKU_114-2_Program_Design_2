#include "Pokemon.cpp"
#include <iostream>

using namespace std;

class Manager {
private:
    vector<Pokemon*> pokemons;
    Boss* boss;
public:
    Manager(){}
    ~Manager(){
        delete boss;
        for(Pokemon* p : pokemons){
            delete p;
        }
        pokemons.clear();
    }
    void create_boss(string name,
                     string type,
                     string weakness,
                     int HP,
                     int attack){
        boss = new Boss(name, type, weakness, HP, attack);
    }
    
    void create_pokemons(){
        pokemons.push_back(new Pikachu());
        pokemons.push_back(new Bulbasaur());
        pokemons.push_back(new Squirtle());
        pokemons.push_back(new Charmander());
        pokemons.push_back(new Clefairy());
    }
    
    bool pokemon_turn(string pokemon){
        Pokemon* now;
        if (pokemon == "Pikachu") {
            now = pokemons[0];
        } else if (pokemon == "Bulbasaur") {
            now = pokemons[1];
        } else if (pokemon == "Squirtle") {
            now = pokemons[2];
        } else if (pokemon == "Charmander") {
            now = pokemons[3];
        } else if (pokemon == "Clefairy") {
            now = pokemons[4];
        } else {
            cout << "Pokemon not found, please enter again!" << endl;
            return false;
        }
        if(now->dead()){
            cout << "This Pokemon has fainted, please send out another Pokemon!" << endl;
            return false;
        }
        pair<int, string> tmp = now->go_attack();
        boss->get_attack(tmp.first, tmp.second);
        return true;
    }
    
    bool boss_turn(string pokemon){
        Pokemon* now;
        if (pokemon == "Pikachu") {
            now = pokemons[0];
        } else if (pokemon == "Bulbasaur") {
            now = pokemons[1];
        } else if (pokemon == "Squirtle") {
            now = pokemons[2];
        } else if (pokemon == "Charmander") {
            now = pokemons[3];
        } else if (pokemon == "Clefairy") {
            now = pokemons[4];
        } else {
            cout << "Pokemon not found, please enter again!" << endl;
            return false;
        }
        if(now->dead()){
            cout << "This Pokemon has fainted, please send out another Pokemon!" << endl;
            return false;
        }
        pair<int, string> tmp = boss->go_attack();
        now->get_attack(tmp.first, tmp.second);
        return true;
    }
    
    void report(){
        cout << "Boss: " << endl;
        boss->report();
        cout << endl;
        cout << "Pokemon: " << endl;
        for(int i = 0;i < 5;i ++)
            pokemons[i]->report();
        cout << endl;
    }
    
    bool gameover(){
        return boss->dead();
    }
};

int main(){
    Manager manager;
    string name;
    string type;
    string weakness;
    int HP;
    int attack;
    cin >> name >> type >> weakness >> HP >> attack;
    manager.create_boss(name, type, weakness, HP, attack);
    manager.create_pokemons();
    
    string input;
    int turn = 0;
    while(cin >> input){
        if(input == "0")
            break;
        if(input == "Report"){
            manager.report();
            continue;
        }
        if(turn == 0){
            if(!manager.pokemon_turn(input))
                continue;
        }
        else {
            if(!manager.boss_turn(input))
                continue;
        }
        if(manager.gameover()){
            cout << "Congratulations! You defeated the BOSS!" << endl;
            break;
        }
        turn = 1 - turn;
    }
    return 0;
}
