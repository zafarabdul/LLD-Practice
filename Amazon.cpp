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
    string location;
    public:
    User(int phoneNo,string name,string location):
    id(UserIdGenerator::getInstance()->getNextId()),
    location(location),
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
class Item{
    int id;
    int cost;
    bool isAvailable;
    string itemName;
    string description;
    public:
    Item(int cost,string name,string description = "" ,bool isAvailable=true):
    id(ItemIdGenerator::getInstance()->getNextId()),
    cost(cost),
    itemName(name),
    isAvailable(isAvailable),
    description(description){}
    string getItemName(){
        return this->itemName;
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
    unordered_map<Item*,int>items;
    int totalCost;
    public:
    Cart(){
        this->totalCost = 0;
    }
    void printCart(){
        cout<<"--------------------------------------------------------------"<<endl;
        for(auto i:items){
            auto item = i.first;
            int count = i.second;
            cout<<(item->getItemId())<<"------ "<<(item->getItemName())<<" ----- "<<count<<endl;
        }
    }
    void addToCart(Item* it){
        totalCost+=it->getItemCost();
        items[it]++;
    }
    void removeFromCart(Item* it){
        totalCost-=it->getItemCost();
        this->items[it]--;
        if(this->items[it]==0){
            this->items.erase(it);
        }
    }
    void clearCart(){
        this->items.clear();
    }
    int getTotalCost(){
        return this->totalCost;
    }
};
class InventoryService{
    unordered_set<Item*>items;
    public:
    void addItem(string name,int cost,string des=""){
        Item* it = new Item(cost,name,des,true);
        items.insert(it);
    }
    void removeItem(Item* it){
        items.erase(it);
    }
    Item* searchItem(int itemId){
        for(auto i:items){
            if(i->getItemId() == itemId)return i;
        }
        return nullptr;
    }
    void printAllItems(){
        cout<<"--------------------All Items In Amazon-----------------------"<<endl;
        for(auto i:items){
            cout<<(i->getItemId())<<" ------ "<<(i->getItemName())<<endl;
        }
        cout<<"--------------------------------------------------------------"<<endl;
    }
};
class UserServiceManager{
    Cart* cart;
    User* user;
    InventoryService* invent;
    bool isUserCreated(){
        return this->user;
    }
    public:
    UserServiceManager(InventoryService* i):invent(i){}
    void createUser(int phoneNo, string name , string location){
        User* u1 = new User(phoneNo , name , location);
        this->user = u1;
        Cart* c = new Cart();
        this->cart = c;
    }
    void showCart(){
        this->cart->printCart();
    }
    void AddItemToCart(int itemId){
        if(!isUserCreated()){
            cout<<"create user"<<endl;
        }
        this->cart->addToCart(
            this->invent->searchItem(itemId)
            );
    }
    void RemoveItemFromCart(int itemId){
        if(!isUserCreated()){
            cout<<"create user"<<endl;
        }
        this->cart->removeFromCart(
            this->invent->searchItem(itemId)
            );
    }
    void purchase(){
        if(!isUserCreated()){
            cout<<"create user"<<endl;
        }
        cout<<"Bought List is "<<endl;
        this->cart->printCart();
        // this->cart->clearCart();
    }
};
int main() {
    // Amazon LLD
    // user 
    // items
    // cart
    // paymentstrategy
    
    //Set Up The Data
    InventoryService* Is = new InventoryService();
    Is->addItem("Iphone",120000,"mobilePhobe");
    Is->addItem("KitKat",50,"Chocolete");
    Is->addItem("Diary Milk",100,"Chocolete");
    Is->addItem("Bag",1200,"Bag");
    Is->printAllItems();
    
    //using Data
    UserServiceManager* USM1 = new UserServiceManager(Is);
    USM1->createUser(1234567890,"zafar","Hyderbad");
    USM1->AddItemToCart(2);
    USM1->AddItemToCart(2);
    USM1->showCart();
    return 0;
}
