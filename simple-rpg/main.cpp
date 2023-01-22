#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;
void clear(int a = 30)
{
    for(int i {}; i < a; i++)
    {
        cout << endl;
    }
}

void void_input()
{
    string input {};
    getline(cin,input);
    return;
}
vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string piece;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        piece = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(piece);
    }

    res.push_back(s.substr(pos_start));
    return res;
}




class pet
{
public:
    int lvl {1};
    //int xp {};
    int damage {};
    int health {};
    int crit_damage {};
    int max_lvl {100};
    double damage_per_lvl {};
    double health_per_lvl {};
    double crit_damage_per_lvl {};
    void recalculate()
    {
         //------------------exp/lvl
//            while(xp >= pow(lvl+3,2))
//            {
//                xp -= pow(lvl+3,2);
//                lvl++;
//                
//            }
            if(lvl > max_lvl)
            {
                lvl = max_lvl;
            }
            //damage 
            damage = damage_per_lvl * lvl;
            //health
            health = health_per_lvl * lvl;
            //crit_damage
            crit_damage = crit_damage_per_lvl * lvl;
            
            
            
            
    }
};

class weapon
    {
public:
        //int id {};
        int damage {};
        int health {};
    };
    class base_stats
    {
        public:
        int damage {5};
        int health {100};
        int defence {0};
        int crit_damage {3};
    };



class monster_template
    {
public:
        int world {1};
        int health {};
        int damage {};
        int defence {};
        int crit_chance {};
        int droped_gold = 15 + (lvl * 5) + rand() % 20 + (lvl * 5); 
        int droped_xp = 10 + (lvl * 3) + rand() % 10 + (lvl * 3);
        int lvl {1};
        base_stats base {};
        
        
        void recalculate()
        {
            //------------------exp/lvl
//            while(xp >= pow(lvl+1,2))
//            {
//                xp -= pow(lvl+1,2);
//                lvl++;
//                
//            }
            //-------------damage
            damage = base.damage;
            //damage += held_weapon.damage;
            damage += lvl * 2;
            //-------------health
            health = base.health;
            health += lvl * 12;
            //-----------------defence
            defence = base.defence;
            defence += lvl;
            
            
            //cout << lvl;
        }
    };


    class player
    {
        public:
        int health {};
        int damage {};
        int defence {};
        int crit_chance {20};
        int gold {}; 
        int xp {};
        int lvl {1};
        int crit_damage {};
        base_stats base {};
        weapon held_weapon {};
        pet player_pet {};
        
        
        
        
        
        
        
        
        
        
        
        void recalculate()
        {
            player_pet.recalculate();
            //------------------exp/lvl
            while(xp >= pow(lvl+3,2))
            {
                xp -= pow(lvl+3,2);
                lvl++;
                
            }
            //-------------damage
            damage = base.damage;
            damage += held_weapon.damage;
            damage += lvl * 2;
            damage += player_pet.damage;
            //-------------health
            health = base.health;
            health += lvl * 5;
            health += player_pet.health;
            //-----------------defence
            defence = base.defence;
            defence += lvl / 2;
            //----------------crit_damage
            crit_damage = base.crit_damage;
            crit_damage += player_pet.crit_damage;
            
            //cout << lvl;
        }
    };


void loot_system(player &character,monster_template monster)
{
if(rand() % 100 <= 15)
{
    clear();
    weapon droped_weapon;
    
    droped_weapon.damage = rand() % 10 + monster.lvl + 2;
    droped_weapon.health = (rand() % 10 + monster.lvl + 2) * 3 ;
    while(true)
    {
        cout << "do you want to swap your sword" << endl << endl;
        cout << "current sword: " << endl;
        cout << "damage " << character.held_weapon.damage << endl;
        cout << "health " << character.held_weapon.health << endl << endl;
        cout << "droped sword:" << endl;
        cout << "damage " << droped_weapon.damage << endl;
        cout << "health " << droped_weapon.health << endl << endl;
        cout << "2 swap" << endl;
        cout << "1 scrap" << endl;
        int input {};
        cin >> input;
        if(input == 2)
        {
            character.held_weapon.damage = droped_weapon.damage;
            character.held_weapon.health = droped_weapon.health;
            clear();
            cout << "swaped!" << endl;
            return;
        }
        else if(input == 1)
        {
            clear();
            cout << "Item scraped!" << endl;
            character.xp += monster.droped_xp;
            character.gold += monster.droped_gold;
            cout << "you got " << monster.droped_xp << " exp and " << monster.droped_gold << " gold"<< endl;
            void_input();
            return;
        }
        else
        {
            clear();
            cout << "Please input a valid option" << endl;
            void_input();
            clear();
        }
    }
}
    
    
    
}












void hit_handler(player &character,monster_template &monster)
{
    
    
    
    monster.health -= character.damage;  // - (monster.defence * 2);
    character.health -= monster.damage; // - (character.defence * 3);
    
    if(rand() % 100 < character.crit_chance  )
    {
        monster.health -= (character.damage + character.crit_damage) * 1.5; //- monster.defence);
        cout << "critical hit!" << endl;
    }
}

void fight(player &character,monster_template monster)
{
    //int temp {};
    while(true)
    {
        clear();
        //monster.health -= character.damage;
        //character.health -= monster.damage;
        hit_handler(character,monster);
        if(monster.health <= 0)
        {
            character.gold += monster.droped_gold;
            character.xp += monster.droped_xp;
            cout << "battle won\n";
            cout << "you got " << monster.droped_xp << " exp and " << monster.droped_gold << " gold "<< endl;
            void_input();
            loot_system(character,monster);
            clear();
            return;
        }
        else if(character.health <= 0)
        {
            cout << "battle lost\n";
            void_input();
            clear();
            
            return;
        }
        cout << "Monster stats:" << endl;
        cout << "health: " << monster.health << endl;
        cout << "defence: " << monster.defence << endl;
        cout << "damage: " << monster.damage << endl;
        cout << "Player stats:" << endl; 
        cout << "health: " << character.health << endl;
        cout << "defence: " << character.defence << endl;
        cout << "damage: " << character.damage << endl;
        void_input();
    }
    
    
}

int gui()
{
    int a {};
    cout << "choose an option" << endl << endl;
    cout << "1.fight" << endl;
    cout << "2.stats and eq" << endl;
    cout << "3.move to diffrent arena" << endl;
    cout << "4.buying pets" << endl;
    cout << "5.upgrading pets" << endl;
    cout << "6.save" << endl;
    cout << "7.load" << endl;
    cin >> a;
    clear();
    return a;
    
}


void player_eq_wiever(player &character)
{
    
    cout << "Your stats:" << endl << endl << endl;
    cout << "Health " << character.health - character.held_weapon.health  << endl;
    cout << "Defence " << character.defence << endl;
    cout << "Damage " << character.damage - character.held_weapon.damage << endl;
    cout << "LVL " << character.lvl << endl << endl;
    cout << "exp " << character.xp << "/" << pow(character.lvl+3,2) << endl;
    
    
    
    
    cout << "Weapon stats:" << endl;
    cout << "Weapon damage " << character.held_weapon.damage << endl;
    cout << "Weapon health " << character.held_weapon.health << endl << endl;
    cout << "Pet stats:" << endl;
    cout << "Pet health " << character.player_pet.health << "                           Per one lvl " << character.player_pet.health_per_lvl << endl;
    cout << "Pet damage " << character.player_pet.damage << "                           Per one lvl " << character.player_pet.damage_per_lvl << endl;
    cout << "Pet crit chance " << character.player_pet.crit_damage << "                      Per one lvl " << character.player_pet.crit_damage_per_lvl << endl;




    cout << "Overall stats: " << endl;
    cout << "health " << character.health << endl;
    cout << "damage " << character.damage << endl << endl;
    
    
    
    cout << "misc:" << endl; 
    cout << "gold " << character.gold << endl;
    void_input();
    void_input();
    clear();

}

void world_swaper(monster_template &monster)
{
    int input {};
    cout << "select world " << endl;
    cin >> input;
    if(input > 0)
    {
    monster.world = input;
    monster.lvl = 1 + ( monster.world - 1) * 5;
    monster.recalculate();
    cout << "World traveled succesfully" << endl;
    }
    else
    {
    cout << "The world can't be negative!!" << endl;
       
    }
    void_input();
}
void pets_upgrade(player &character)
{
if(character.player_pet.lvl < character.player_pet.max_lvl)
{
    int price = pow(2,character.player_pet.lvl ) * 50;
    int input {};
    if(character.player_pet.health_per_lvl == 0)
    {
        cout << "you don't have a pet" << endl;
        void_input();
        void_input();
        clear();
        return;
    }
    cout << "The cost of pet upgrade is " << price << endl;
    cout << "do you want to buy it " << endl;
    cout << "1.Buy pet" << endl;
    cin >> input;
    if(input == 1)
    {
        if(character.gold >= price)
        {
            character.gold -= price;
            character.player_pet.lvl += 1;
            cout << "upgrade bougth" << endl;
            cout << "pet gained: " << endl;
            cout << "health " << character.player_pet.health_per_lvl << endl;
            cout << "damage " << character.player_pet.damage_per_lvl << endl;
            cout << "crit damage " << character.player_pet.crit_damage_per_lvl << endl;
            return;
            
        }
    }
}
else
{
    cout << "pet is max lvl" << endl;
    void_input();
    return;
}



}
void pets_obtain(player &character)
{
    int input {};
    int cost {};
    int power {};
    clear();
    while(true)
    {
    
    cout << "Pet forge" << endl;
    cout << "What power of pet do you want to forge?" << endl << endl;
    cin >> power;
    if(power < 1)
    {
        clear();
        cout << "the minimum power of pet is 1" << endl;
        cin >> input;
        clear();
        return;
    }
    
        if(power + 3 <= character.lvl )
        {
            
            cost = pow(2,power)*10;
            
                if(character.gold > cost)
                {
                    cout << "cost is " << cost << endl;
                    cout << "do you want co forge pet of power " << power << endl;
                    cout << "1 forge pet" << endl;
                    cout << "2 resign" << endl;
                    cin >> input;
                    clear();
                    if(input == 1)
                    {
                        cout << "Old pet" << endl;
                        cout << "health " << character.player_pet.health_per_lvl << " per lvl" << endl;
                        cout << "damage " << character.player_pet.damage_per_lvl << " per lvl" << endl;
                        cout << "crit damage " << character.player_pet.crit_damage_per_lvl << "per lvl" << endl;
                        
                    character.gold -= cost;
                    character.player_pet.health_per_lvl = (4 + (2 + rand() % 6) * power) / 10;
                    character.player_pet.damage_per_lvl = (2 + (1 + rand() % 2) * power) / 10;
                    character.player_pet.crit_damage_per_lvl = (0.3 + ( (rand() % 5) / 10) )* power;
                    cout << "pet forged!" << endl;
                    cout << "New pet:" << endl;
                    cout << "health " << character.player_pet.health_per_lvl << " per lvl" << endl;
                    cout << "damage " << character.player_pet.damage_per_lvl << " per lvl" << endl;
                    cout << "crit damage " << character.player_pet.crit_damage_per_lvl << " per lvl" << endl;
                    cin >> input;
                    clear();
                    return;
                    }
                    else
                    {
                        cout << "succesfully canceled!" << endl;
                        cin >> input;
                        return;
                    }
                    
                }
                else 
                {
                    cout << "you can't buy this pet!" << endl;
                    cout << "yoy have " << character.gold << " cash and you need " << cost << endl;
                    cout << "you are " <<  cost - character.gold  << " gold short";
                    cin >> input;
                    clear();
                    return;
                }
        
        }   
        else
        {
        cout << "your lvl is too low to forge pet of that power!" << endl; 
        cout << "you need to be at least lvl " << power + 3 << endl;
        cin >> input;
        return;
        }
    }
    
    
}


void export_csv(string filename,player character,monster_template monster)
{
    //filename = "Save1";
    filename = "saves/" + filename + ".txt";
    ofstream file1 (filename);
    
    file1 << character.lvl << "," << character.xp << "," << character.gold << ",";
    file1 << character.held_weapon.damage << "," << character.held_weapon.health <<  ",";
    file1 << character.player_pet.lvl << "," << character.player_pet.damage_per_lvl << "," << character.player_pet.health_per_lvl << "," << character.player_pet.crit_damage_per_lvl << ",";
    file1 << monster.world;
    file1.close();
}
void import_csv(string filename,player &character , monster_template &monster)
{
    vector<string> data ;
    filename = "Saves/" + filename + ".txt";
    ifstream file1(filename);
string chunk {};

    getline(file1,chunk);
    
    data = split(chunk,",");
    
//    for (string a : data)
//    {
//        cout << a << " ";
//        
//    }
    character.lvl = stoi( data.at(0));
    character.xp = stoi( data.at(1));
    character.gold = stoi( data.at(2));
    character.held_weapon.damage = stoi( data.at(3));
    character.held_weapon.health = stoi( data.at(4));
    character.player_pet.lvl = stoi( data.at(5));
    character.player_pet.damage_per_lvl = stod( data.at(6));
    character.player_pet.health_per_lvl = stod( data.at(7));
    character.player_pet.crit_damage_per_lvl = stod( data.at(8));
    monster.world = stoi( data.at(9));

    character.recalculate();
    monster.recalculate();



 
    
}










int main()
{
    
    srand(time(0));
    
    player character {};
    monster_template monster {};
    //import_csv("save1",character,monster);
    //split(",","1233 3,d,3,4,654,3");
    while(true)
    {
        //character.gold += 100000;
        //character.lvl = 1000;
        //cout << rand() << endl;
    
    character.recalculate();
    monster.recalculate();
    monster.damage -= 2;
    
    
    
    
    switch(gui())
    {
        case 1: fight(character,monster); break;
        case 2: player_eq_wiever(character); break;
        case 3: world_swaper(monster); break;
        case 4: pets_obtain(character); break;
        case 5: pets_upgrade(character); break;
        case 6: export_csv("Save1",character,monster); break;
        case 7: import_csv("Save1",character,monster); break;
        default: cout << "invalid option"  << endl;
    }
    
    
    }
    
	// make monster
    //
    //
    //
    //
    //
    //
    //
    //
	return 0;
}
