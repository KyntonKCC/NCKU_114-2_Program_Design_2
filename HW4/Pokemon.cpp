#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

class Pokemon {
protected:
    string name;
    string type;
    string weakness;
    int HP;
    int attack;
public:
    Pokemon() = default;
    virtual ~Pokemon() = default;
    
    virtual pair<int, string> go_attack() = 0;
    virtual void get_attack(int damage, string type) = 0;
    bool dead(){ return HP <= 0; }
    
    void report(){
        cout << "Name: " << name << endl;
        cout << "HP: " << HP << endl;
    }
};

class Boss {
private:
    string name;
    string type;
    string weakness;
    int HP;
    int attack;
public:
    Boss(string name,
         string type,
         string weakness,
         int HP,
         int attack)
         : name(name), type(type), weakness(weakness), HP(HP), attack(attack){}
    pair<int, string> go_attack(){
        // TODO
        return {attack, type};
    }
    void get_attack(int damage, string type){
        // TODO
        int total_damage = damage;
        if(type == weakness)
            total_damage *= 2;
        HP -= total_damage;
        if(HP < 0) 
            HP = 0;
    }
    bool dead(){ return HP <= 0; }

    void report(){
        cout << "Name: " << name << endl;
        cout << "HP: " << HP << endl;
    }
};

class Pikachu : public Pokemon{
    // TODO
public:
    Pikachu(){
        name = "Pikachu";
        type = "Electric";
        weakness = "Ground";
        HP = 300;
        attack = 80;
    }
    
    pair<int, string> go_attack() override{
        return {attack, type};
    }
    
    void get_attack(int damage, string type) override{
        int total_damage = damage;
        bool is_weakness = (type == weakness);
        
        if(is_weakness)
            total_damage *= 2;
        HP -= total_damage;
        if(HP > 0){
            if(is_weakness){
                HP += 30;
                if(HP > 300) 
                    HP = 300;
            }
        }else{
            HP = 0;
        }
    }
};

class Bulbasaur : public Pokemon{
    // TODO
public:
    Bulbasaur(){
        name = "Bulbasaur";
        type = "Grass";
        weakness = "Fire";
        HP = 300;
        attack = 60;
    }
    
    pair<int, string> go_attack() override{
        return {attack, type};
    }
    
    void get_attack(int damage, string type) override{
        int total_damage = damage;
        bool is_weakness = (type == weakness);
        
        if(is_weakness)
            total_damage *= 2;
        if(is_weakness && total_damage >= HP){
            HP = 1;
        }else{
            HP -= total_damage;
            if(HP < 0) 
                HP = 0;
        }
    }
};

class Squirtle : public Pokemon{
    // TODO
private:
    bool shield_active = false;
public:
    Squirtle(){
        name = "Squirtle";
        type = "Water";
        weakness = "Electric";
        HP = 300;
        attack = 60;
    }
    
    pair<int, string> go_attack() override {
        shield_active = true;
        return {attack, type};
    }
    
    void get_attack(int damage, string type) override {
        int total_damage = damage;
        if(type == weakness)
            total_damage *= 2;
        if(shield_active){
            total_damage /= 2;
            shield_active = false;
        }
        HP -= total_damage;
        if(HP < 0) 
            HP = 0;
    }
};

class Charmander : public Pokemon{
    // TODO
private:
    bool enraged = false;
public:
    Charmander(){
        name = "Charmander";
        type = "Fire";
        weakness = "Water";
        HP = 300;
        attack = 80;
    }
    
    pair<int, string> go_attack() override{
        int actual_attack = attack;
        if (enraged) {
            actual_attack *= 2;
            enraged = false;
        }
        return {actual_attack, type};
    }
    
    void get_attack(int damage, string type) override{
        int total_damage = damage;
        if(type == weakness)
            total_damage *= 2;
        HP -= total_damage;
        if(HP < 0)
            HP = 0;
        else
            enraged = true;
    }
};

class Clefairy : public Pokemon{
    // TODO
public:
    Clefairy(){
        name = "Clefairy";
        type = "Fairy";
        weakness = "Steel";
        HP = 500;
        attack = 60;
    }
    
    pair<int, string> go_attack() override{
        HP += 150;
        if(HP > 500) 
            HP = 500;
        return {attack, type};
    }
    
    void get_attack(int damage, string type) override{
        int total_damage = damage;
        if(type == weakness)
            total_damage *= 2;
        HP -= total_damage;
        if(HP < 0) 
            HP = 0;
    }
};
