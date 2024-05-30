#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;


class Universe;
class Planet;
class Starship;
class Player;



class Universe
{
    private:
    Planet ****universe;
    int x_size;
    int y_size;
    int z_size;

    public:
    Universe();
    Universe(int x, int y, int z);

    int getXSize();
    int getYSize();
    int getZSize();
    Planet *getPlanet(int xc, int yc, int zc); 
    void setPlanet(Planet* inp);
    ~Universe();
};
class Planet
{
    private:
    long planetID;
    int x_coordinate;
    int y_coordinate;
    int z_coordinate;
    Player* owner;
    int health;
    int level;

    public:
    Planet();
    Planet(int xc, int yc, int zc, long i, Player *own);

    void setID(long i);
    void setXCoordinate(int xc);
    void setYCoordinate(int yc);
    void setZCoordinate(int zc);
    void setCoordinates(int xc, int yc, int zc);
    void setLevel(int l);
    void setHealth(int h);
    void setOwner(Player* o);

    long getID();
    int getXCoordinate();
    int getYCoordinate();
    int getZCoordinate();
    int getHealth();
    int getLevel();
    Player* getOwner();

    void recovery();
    int defend();
    
};
class Starship
{
    private:
    long spaceID;
    int level;
    int health;
    string type;
    

    public:
    int (Starship::*attackvalue)(); 
    Starship();
    Starship(long ID, string t);
    void setID(long id);
    void setLevel(int l);
    void setType(string t);
    void setHealth(int h);
    
    int getID();
    int getLevel();
    int getHealth();
    string getType();


    int damage();
    int tank();
    void recover();
};
class Player
{
    private:
    typedef Planet** Owned_planets;
    typedef Starship starships[2];
    long playerID;
    int size;
    Universe* main_universe;
    Owned_planets owned_planets;
    starships starship;
    int xp;
    long total_xp;

    public:
    Player();
    Player(long id, Universe* mu);

    long getPlayerID();
    int getSize();
    long getTotalXP();
    void setID(long i);
    void setXP(int x);
    void setTotalXP(int tx);

    void printStarships();
    void printPlanets();
    void addPlanet(Planet* pl);
    void removePlanet(Planet *pl);
    void upgradePlanet(long planetID);
    void upgradeShip(long spaceID);
    void fight(Planet* pl);
    void explore(int xc, int yc, int zc);

};

int main()
{
    Universe game_universe(3,3,3);
    Planet game_planets[14];

    for(int i = 0;i < 14;i++)
    {
        game_planets[i] = Planet();
        game_planets[i].setID(i+1);
        game_universe.setPlanet(&game_planets[i]);
    }
    Universe *univ_ptr = &game_universe;
    Player players[2] = {Player(1,univ_ptr),Player(2,univ_ptr)};

    cout << "===== Welcome to Sataar Wars =====\n\n";
    cout << "Explore and conquer the 14 planets dispersed around the universe to emerge victorious!\nNote: The universe is of size 3x3x3 (Enter coordinates from 0 to 2)\n\n";
    const int MOVES = 50;
    
    for(int j = 0; j < MOVES;j++)
    {
        for(int i = 0; i < 2;i++)
        {
            char inp;
            do
            {
                cout << "------------------------------\n";
                cout << "Player " << players[i].getPlayerID() << "'s turn!\n";
                cout << "------------------------------\n";
                cout << "1) View Arsenal\n";
                cout << "2) Explore\n";
                cout << "3) Skip turn\n";
                cout << "------------------------------\n";
                cout << "Input: ";
                cin >> inp;
                while (!(inp == '1' || inp == '2' || inp == '3'))
                {
                    cout << "Invalid input\n";
                    cin.clear();
                    cin.ignore();
                    cout << "Enter input again: ";
                    cin >> inp;
                }
                if (inp == '1')
                {
                    players[i].printStarships();
                    players[i].printPlanets();
                }
                else if (inp == '2')
                {
                    cout << "\nPlayer " << players[i].getPlayerID() << " enter coordinates to explore (x y z): ";
                    int x, y, z;
                    cin >> x >> y >> z;
                    players[i].explore(x, y, z);
                }
                else
                {
                    cout << "-------------\n";
                    cout << "Turn SKIPPED\n";
                    cout << "-------------\n\n";
                }
            } while (inp == '1');
        }
    }
    if(players[0].getTotalXP() > players[1].getTotalXP())
    {
        cout << "Player 1 won, with " << players[0].getTotalXP() << " total XP!" << endl;
    }
    else if (players[0].getTotalXP() < players[1].getTotalXP())
    {
        cout << "Player 2 won, with " << players[1].getTotalXP() << " total XP!" << endl;
    }
    else
    {
        cout << "There was a draw betweeen both the players with each having " << players[1].getTotalXP() << endl;
    }
    
    return 0;
}

//UNIVERSE CLASS DEFINITION
Universe::Universe()
{
    universe = nullptr;
    x_size = 0;
    y_size = 0;
    z_size = 0;
}
Universe::Universe(int x, int y, int z)
{
    x_size = x;
    y_size = y;
    z_size = z;
    universe = new Planet***[x_size];
    for(int i = 0; i < x_size;i++)
    {
        universe[i] = new Planet**[y_size];
        for(int j = 0; j < y_size; j++)
        {
            universe[i][j] = new Planet*[z_size];
        }
    }
    for(int i = 0;i < x_size;i++)
    {
        for(int j = 0;j < y_size;j++)
        {
            for(int k = 0; k < z_size;k++)
            {
                universe[i][j][k] = nullptr;
            }
        }
    }
}
Planet* Universe::getPlanet(int xc, int yc, int zc)
{
    return universe[xc][yc][zc];
}
void Universe::setPlanet(Planet* inp)
{
    srand(clock());
    int x_c = rand() % (x_size);
    int y_c = rand() % (y_size);
    int z_c = rand() % (z_size);


    while(universe[x_c][y_c][z_c] != nullptr) 
    {
        x_c = rand() % (x_size);
        y_c = rand() % (y_size);
        z_c = rand() % (z_size);
    }
    inp->setXCoordinate(x_c);
    inp->setYCoordinate(y_c);
    inp->setZCoordinate(z_c);
    universe[x_c][y_c][z_c] = inp;


}
int Universe::getXSize()
{   
    return x_size;
}
int Universe::getYSize()
{
    return y_size;
}
int Universe::getZSize()
{
    return z_size;
}
Universe::~Universe()
{
    for(int i = 0; i < x_size;i++)
    {
        for(int j = 0; j < y_size;j++)
        {
            delete [] universe[i][j];
        }
        delete [] universe[i];
    }
    delete [] universe;
}

//PLANET CLASS DEFINITION
Planet::Planet()
{
    planetID = -1;
    x_coordinate = -1;
    y_coordinate = -1;
    z_coordinate = -1;
    owner = nullptr;
    level = 1 + (rand() % 5);
    health = level*50;
    
}
Planet::Planet(int xc, int yc, int zc, long i, Player* own)
{
    planetID = i;
    x_coordinate = xc;
    y_coordinate = yc;
    z_coordinate = zc;
    owner = own;
    level = 1 + (rand() % 5);
    health = level*50;
}
void Planet::setID(long i)
{
    planetID = i;
}
void Planet::setXCoordinate(int xc)
{
    x_coordinate = xc;
}
void Planet::setYCoordinate(int yc)
{
    y_coordinate = yc;
}
void Planet::setZCoordinate(int zc)
{
    z_coordinate = zc;
}
void Planet::setCoordinates(int xc, int yc, int zc)
{
    x_coordinate = xc;
    y_coordinate = yc;
    z_coordinate = zc;
}
long Planet::getID()
{
    return this->planetID;
}
int Planet::getXCoordinate()
{
    return this->x_coordinate;
}
int Planet::getYCoordinate()
{
    return this->y_coordinate;
}
int Planet::getZCoordinate()
{
    return this->z_coordinate;
}
int Planet::getHealth()
{
    return this->health;
}
int Planet::getLevel()
{
    return this->level;
}
void Planet::recovery()
{
    this->health = (this->level) * 50;
}
int Planet::defend()
{
    return ((this->level) * 30);
}
void Planet::setLevel(int l)
{
    level = l;
}
void Planet::setHealth(int h)
{
    if(h < 0)
    {
        h = 0;
    }
    health = h;
}
void Planet::setOwner(Player* o)
{
    this->owner = o;
}
Player* Planet::getOwner()
{
    return this->owner;
}

//STARSHIP CLASS DEFINITION
Starship::Starship()
{
    spaceID = -1;
    level = 1;
    health = 25 * level;
}
Starship::Starship(long ID, string t)
{
    spaceID = ID;
    level = 1;
    
    type = t;
    if(type == "Tank")
    {
        attackvalue = &Starship::tank;
        health = 75 * level;
    }
    else 
    {
        attackvalue = &Starship::damage;
        health = 25 * level;
    }

}
void Starship::setID(long id)
{
    this->spaceID = id;
}
void Starship::setHealth(int h)
{
    if(h < 0)
    {
        h = 0;
    }
    this->health = h;
}
void Starship::setLevel(int l)
{
    this->level = l;
}
void Starship::setType(string t)
{
    this->type = t;
}
int Starship::getID()
{
    return this->spaceID;
}
int Starship::getLevel()
{
    return this->level;
}
int Starship::getHealth()
{
    return this->health;
}
string Starship::getType()
{
    return this->type;
}
int Starship::damage()
{
    return ((this->level) * 75);
}
int Starship::tank()
{
    return ((this->level) * 25);
}
void Starship::recover()
{
    if(this->getType() == "Tank")
    {
        this->health = level * 75;
    }
    else
    {
        this->health = level * 25;
    }
}

//PLAYER CLASS DEFINITION
Player::Player()
{
    playerID = -1;
    size = 0;
    main_universe = nullptr;
    owned_planets = nullptr;
    starship[0] = Starship(1,"Tank");
    starship[1] = Starship(2,"Damage");
    xp = 0;
    total_xp = 0;
}
Player::Player(long id, Universe* mu)
{
    playerID = id;
    size = 0;
    main_universe = mu;
    starship[0] = Starship(1,"Tank");
    starship[1] = Starship(2,"Damage");
    xp = 0;
    total_xp = 0;
}
void Player::setXP(int x)
{
    xp = x;
}
void Player::setTotalXP(int tx)
{
    total_xp = tx;
}
long Player::getPlayerID()
{
    return this->playerID;
}
int Player::getSize()
{
    return size;
}
long Player::getTotalXP()
{
    return total_xp;
}
void Player::addPlanet(Planet* pl)
{
    Owned_planets temp = new Planet*[size+1];
    for(int i = 0; i < size;i++)
    {
        temp[i] = this->owned_planets[i];
    }
    temp[size] = pl;
    delete [] owned_planets;
    size++;
    owned_planets = new Planet*[size];
    for(int i = 0; i < size;i++)
    {
        owned_planets[i] = temp[i];
    }
    temp = nullptr;
    pl->setOwner(this);
}
void Player::removePlanet(Planet* pl)
{
    bool found = false;
    int index = -1;
    for(int i = 0;i < size;i++)
    {
        if(owned_planets[i] == pl)
        {
            found = true;
            index = i;
        }
    }
    for(int i = index; i < size - 1;i++)
    {
        owned_planets[i] = owned_planets[i+1];
    }
    size--;
    Owned_planets temp = new Planet*[size];
    for(int i = 0; i < size;i++)
    {
        temp[i] = owned_planets[i];
    }
    delete [] owned_planets;
    owned_planets = new Planet*[size];
    for(int i = 0; i < size;i++)
    {
        owned_planets[i] = temp[i];
    }
    temp = nullptr;
}
void Player::upgradePlanet(long planetID)
{
    bool found = false;
    for(int i = 0; i < size;i++)
    {
        if(planetID == (owned_planets[i])->getID())
        {
            found = true;
            if(total_xp - 0.5*xp >= 0 && xp != 0)
            {
                int current_level = owned_planets[i]->getLevel();
                owned_planets[i]->setLevel(current_level+1);
                total_xp = total_xp - (xp*0.5);
                owned_planets[i]->recovery();
                cout << "Upgrade Successful" << endl;
            }
            else
            {
                cerr << "Not enough xp" << endl;
            }
        }
    }
    if(!found)
    {
        cout << "No planet with matching ID found" << endl;
    }
}
void Player::upgradeShip(long spaceID)
{
    bool found = false;
    for(int i = 0;i < 2;i++)
    {
        if(spaceID == starship[i].getID())
        {
            found = true;
            if(total_xp - 2*xp >= 0 && xp != 0)
            {
                int current_level = starship[i].getLevel();
                starship[i].setLevel(current_level+1);
                total_xp = total_xp - (xp*2);
                starship[i].recover();
                cout << "Upgrade Successful" << endl;
            }
            else
            {
                cerr << "Not enough xp" << endl;
            }
            
        }
    }
    if(!found)
    {
        cout << "No planet with matching ID found" << endl;
    }
}
void Player::setID(long i)
{
    this->playerID = i;
}
void Player::fight(Planet* pl)
{
    cout << "Choose which starship to attack with: (0 for tank, 1 for damage): ";
    int s;
    cin >> s;
    while(!(s == 1 || s == 0))
    {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore();
        cout << "Enter input again: ";
        cin >> s;
    }
    

    while(pl->getHealth() > 0 && starship[0].getHealth() > 0 && starship[1].getHealth() > 0)
    {

        int damage = (starship[s].*starship[s].attackvalue)();
        cout << "\nPlanet " << pl->getID() << " was damaged for " << damage << " by " << "Starship " << starship[s].getID() << endl;
        int pl_health = pl->getHealth() - damage;
        pl->setHealth(pl_health);
        if(pl->getHealth() == 0)
        {
            break;
        }
        int pl_damage = pl->defend();
        cout << "Planet " << pl->getID() << " retaliated by attacking Starship " << starship[s].getID() << " for " << pl_damage << endl;
        int st_health = starship[s].getHealth() - pl_damage;
        starship[s].setHealth(st_health);

        cout << "\nRemaining Healths\n";
        cout << "Planet " << pl->getID() << " health = " << pl->getHealth() << endl;
        cout << "Starship " << starship[s].getID() << " health = " << starship[s].getHealth() << "\n\n";
    }
    if(pl->getHealth() == 0)
    {
        cout << "Planet was successfully conquered!\n";
        pl->getOwner()->removePlanet(pl);
        xp = 2 * (starship[s].getLevel());
        cout << xp << " XP gained\n";
        total_xp += xp;
        pl->recovery();
        this->addPlanet(pl);
    }
    else
    {

        cout << "You failed to conquer the planet!\n";
        //pl->recovery();
        int x = 2*pl->getLevel();
        int t = pl->getOwner()->getTotalXP();
        pl->getOwner()->setXP(x);
        pl->getOwner()->setTotalXP(t+x);
        cout << "Player " << pl->getOwner()->getPlayerID() << " gained " << x << " XP for defending their planet! They have " << pl->getOwner()->getTotalXP() << " total XP!\n";

        int index = -1;
        if(starship[0].getHealth() == 0)
        {
            index = 0;
        }
        else
        {
            index = 1;
        }
        int level = starship[index].getLevel() - 1;
        if(level < 1)
        {
            level = 1;
        }
        starship[index].setLevel(level);
        starship[index].recover();
        total_xp -= 2;
        if(total_xp < 0)
        {
            total_xp = 0;
        }
    }


}
void Player::printStarships()
{
    cout << "\n---------------\n";
    cout << "Starships Owned\n";
    cout << "---------------\n";
    for(int i = 0; i < 2;i++)
    {
        cout << "Spaceship " << starship[i].getID() << " - Type: " << starship[i].getType() << ", Health: " << starship[i].getHealth() << ", Damage: " << (starship[i].*starship[i].attackvalue)() << ", Level: " << starship[i].getLevel() << endl;
    }
    cout << endl;                 
}
void Player::printPlanets()
{
    cout << "\n--------------\n";
    cout << "Planets Owned\n";
    cout << "--------------\n";
    if(this->getSize() == 0)
    {
        cout << "No planets owned\n";
    }
    for(int i = 0;i < this->getSize();i++)
    {
        cout << "Planet " << owned_planets[i]->getID() << " - Coordinates: (" << owned_planets[i]->getXCoordinate() << "," << owned_planets[i]->getYCoordinate() << "," << owned_planets[i]->getZCoordinate() << "), Health: " << owned_planets[i]->getHealth() << ", Level: " << owned_planets[i]->getLevel() << endl;
    }
    cout << endl;
}
void Player::explore(int xc, int yc, int zc)
{
    bool skip = false;
    if(xc < 0 || xc >= main_universe->getXSize() || yc < 0 || yc >= main_universe->getYSize() || zc < 0 || zc >= main_universe->getZSize())
    {
        cout << "----------------------------------\n";
        cout << "Invalid Coordinates! Turn SKIPPED\n";
        cout << "----------------------------------\n";
        skip = true;
        return;
    }
    
    Planet *p = main_universe->getPlanet(xc, yc, zc);
    if (p == nullptr)
    {
        cout << "---------------------------------------------------------\n";
        cout << "No planet found at the entered coordinates. Turn SKIPPED\n";
        cout << "---------------------------------------------------------\n";
        skip = true;
    }
    if (!skip)
    {
        if (p->getOwner() == nullptr)
        {
            cout << "-------------------------------------------\n";
            cout << "You found an undiscovered planet of ID " << p->getID() << "!" << endl;
            cout << "Planet Stats - Health = " << p->getHealth() << ", Level = " << p->getLevel() << endl;
            cout << "-------------------------------------------\n";
            cout << "It has been added to your collection and you have gained " << p->getLevel() << " XP!" << endl;
            addPlanet(p);
            xp = 1 * p->getLevel();
            total_xp += xp;
            
        }
        else
        {
            bool own = false;
            if(p->getOwner() == this)
            {
                cout << "You already own this planet\n";
                own = true;
            }
            if (!own)
            {
                cout << "Planet " << p->getID() << " is owned by Player " << p->getOwner()->getPlayerID() << endl;
                cout << "Planet Stats - Health = " << p->getHealth() << ", Level = " << p->getLevel() << endl;
                cout << "Do you want to attack the planet or skip your turn? (Press a for attack and anything else to skip) : ";
                char s;
                cin >> s;
                if (s == 'a')
                {
                    fight(p);
                }
                else
                {
                    cout << "Turn skipped" << endl;
                }
            }
        }
    }
    cout << "You have " << this->getTotalXP() << " total XP.\n";
    cout << "Do you wish to upgrade your planets or starships? (Enter y for yes and n for no): ";
    char o;
    cin >> o;
    while(o == 'y')
    {
        cout << "Do you want to upgrade your starships or planet(s) (Enter s for starships and p for planets): ";
        char o2;
        cin >> o2;
        if(o2 == 's')
        {
            cout << endl;
            // for(int i = 0; i < 2;i++)
            // {
            //     cout << "Spaceship " << starship[i].getID() << " - Type: " << starship[i].getType() << ", Health: " << starship[i].getHealth() << ", Damage: " << (starship[i].*starship[i].attackvalue)() << ", Level: " << starship[i].getLevel() << endl;
            // }
            printStarships();
            cout << endl;
            cout << "Enter the ID of the spaceship you want to upgrade: ";
            long i;
            cin >> i;
            cout << "Upgraded Status: ";
            upgradeShip(i);
            cout << endl;
            for(int j = 0; j < 2;j++)
            {
                if(starship[j].getID() == i)
                {
                    
                    cout << "Spaceship " << starship[j].getID() << " - Type: " << starship[j].getType() << ", Health: " << starship[j].getHealth() << ", Damage: " << (starship[j].*starship[j].attackvalue)() << ", Level: " << starship[j].getLevel() << endl;
                }
            }

        }
        else if(o2 == 'p')
        {
            cout << endl;
            // for(int i = 0; i < size;i++)
            // {
            //     cout << "Planet " << owned_planets[i]->getID() << " - Coordinates: (" << owned_planets[i]->getXCoordinate() << "," << owned_planets[i]->getYCoordinate() << "," << owned_planets[i]->getZCoordinate() << "), Health: " << owned_planets[i]->getHealth() << ", Level: " << owned_planets[i]->getLevel() << endl;
            // }
            // if(size == 0)
            // {
            //     cout << "No planets owned!" << endl;
            // }
            printPlanets();
            cout << endl;
            cout << "Enter the ID of the planet you want to upgrade: ";
            long i;
            cin >> i;
            cout << "Upgraded Status: ";
            upgradePlanet(i);
            cout << endl;
            for(int j = 0; j < size;j++)
            {
                if(owned_planets[j]->getID() == i)
                {
                    
                    cout << "Planet " << owned_planets[j]->getID() << " - Coordinates: (" << owned_planets[j]->getXCoordinate() << "," << owned_planets[j]->getYCoordinate() << "," << owned_planets[j]->getZCoordinate() << "), Health: " << owned_planets[j]->getHealth() << ", Level: " << owned_planets[j]->getLevel() << endl;
                }
            }
        }
        else
        {
            cout << "Invalid input";
        }
        cout << "\nYou have " << this->getTotalXP() << " total XP remaining.\n";
        cout << "Press y to continue upgrading or press anything else to exit: ";
        cin >> o;
    }
}