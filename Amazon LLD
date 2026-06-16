// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

//Singleton Patterns
class UserIdGenerator{
    int id = 0;
    UserIdGenerator(){};
    public:
    static UserIdGenerator* getInstance(){
        static UserIdGenerator instance;
        return &instance;
    }
    int getNextId(){
        return this->id++;
    }
};
class ItemIdGenerator{
    int id = 0;
    ItemIdGenerator(){};
    public:
    static ItemIdGenerator* getInstance(){
        static ItemIdGenerator instance;
        return &instance;
    }
    int getNextId(){
        return this->id++;
    }
};
class User{
    int id;
    int phoneNo;
    string name;
    public:
    User(int phoneNo,string name):
    id(UserIdGenerator::getInstance()->getNextId()),
    phoneNo(phoneNo),name(name){}
    string getName(){
        return this->name;
    }
    int getId(){
        return this->id;
    }
    int getPhoneNo(){
        return this->phoneNo;
    }
};
class Items{
    int id;
    int cost;
    bool isAvailable;
    string itemName;
    stirng description;
    public:
    Item(int cost,string name,string description = "" ,bool isAvailable=true):
    id(ItemIdGenerator::getInstance()->getId()),
    cost(cost),
    itemName(name),
    description(description){}
    string getItemName(){
        return this->ItemName;
    }
    string getItemdes(){
        return this->description;
    }
    int getItemId(){
        return this->id;
    }
    int getItemCost(){
        return this->cost;
    }
    void makeUnAvailable(){
        this->isAvailable = false;
    }
    void makeAvailable(){
        this->isAvailable = true;
    }
    bool getAvailablity(){
        return this->isAvailable;
    }
};
class Cart{
    vector<Items*>items;
    int totalCost = 0;
    
};
int main() {
    // Amazon LLD
    // user 
    // items
    // cart
    // paymentstrategy
    
    return 0;
}
