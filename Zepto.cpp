// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
//Singleton Classes
class UserIdGenerator{
    int Id=0;
    UserIdGenerator(){}
    public:
    static UserIdGenerator* getInstance(){
        static UserIdGenerator instance;
        return &instance;
    }
    int getUserId(){
        return this->Id++;
    }
};
class ItemIdGenerator{
    int Id = 0;
    ItemIdGenerator(){}
    public:
    static ItemIdGenerator* getInstance(){
        static ItemIdGenerator instance;
        return &instance;
    }
    int getId(){
        return this->Id++;
    }
};
class User{
    int UserId;
    string name;
    long phoneNo;
    string location;
    public:
    User(string name,long phoneNo,string location): 
    UserId(UserIdGenerator::getInstance()->getUserId()),
    name(name),
    phoneNo(phoneNo),
    location(location)
    {}
    int getUserId(){
        return this->UserId;
    }
    string getLocation(){
        return this->location;
    }
    int getPhoneNo(){
        return this->phoneNo;
    }
};
class Item{
    int ItemId;
    string ItemName;
    int cost;
    bool isItemAvailable;
    public:
    Item(string name,int cost,bool available):
    ItemId(ItemIdGenerator::getInstance()->getId()),
    ItemName(name),
    cost(cost),
    isItemAvailable(available){}
    void updateCost(int cost){
        this->cost = cost;
    }
    int getCost(){
        return this->cost;
    }
    int getItemId(){
        return this->ItemId;
    }
    string getItemName(){
        return this->ItemName;
    }
    bool isAvailable(){
        return this->isItemAvailable;
    }
    void makeItUnAvaialble(){
        this->isItemAvailable = false;
    };
    void makeItAvailable(){
        this->isItemAvailable = true;
    };
};
class StoreRepo{
    string location;
    bool open = true;
    vector<Item*>items;
    public:
    StoreRepo(string location):location(location){}
    void addItem(string name,int cost,bool isAvailable = true){
        Item* it = new Item(name,cost,isAvailable);
        items.push_back(it);
    }
    bool isStoreOpen(){
        return this->open;
    }
    void makeStoreClose(){
        this->open = false;
    }
    void makeStoreOpen(){
        this->open = true;
    }
    void showItems(){
        cout<<"ItemId____ItemName____ItemCost"<<endl;
        for(auto i:items){
            cout<<(i->getItemId())<<"----"<<(i->getItemName())<<"----"<<(i->getCost())<<endl;
        }
    }
    Item* getItem(int itemId){
        for(auto i:items){
            if(i->getItemId()==itemId)return i;
        }
        return NULL;
    }
};
class CartRepo{
    unordered_map<Item*,int>items;
    int totalCost;
    public:
    CartRepo(Item* it){
        items[it]++;
        this->totalCost = it->getCost();
    }
    int getCartCost(){
        return this->totalCost;
    }
    void addItem(Item* it){
        items[it]++;
        this->totalCost += it->getCost();
    }
    void removeItem(Item* it){
        this->totalCost -= it->getCost();
        items[it]--;
        if(items[it] == 0){
            items.erase(it);
        }
    }
    void showCart(){
        cout<<"-----------------------Cart Items-----------------------------"<<endl;
        cout<<"ItemId____ItemName____ItemCost"<<endl;
        for(auto j:items){
            auto i = j.first;
            cout<<(i->getItemId())<<"----"<<(i->getItemName())<<"----"<<(i->getCost())<<"-----"<<(j.second)<<endl;
        }
    }
};
class ZeptoUserService{
    User* us1 = NULL;
    CartRepo* cart = NULL;
    StoreRepo* store = NULL;
    string location;
    public:
    ZeptoUserService(string name ,long phoneNo ,string location,StoreRepo* store){
        this->us1 = new User(name,phoneNo,location);
        this->location = location;
        this->store = store;
    }
    void showListOfItems(){
        this->store->showItems();
    }
    void addItem(int itemId){
        if(cart){
            this->cart->addItem(this->store->getItem(itemId));
        }
        else{
            this->cart = new CartRepo(this->store->getItem(itemId));
        }
    }
    void removeItem(int itemId){
        this->cart->removeItem(
            this->store->getItem(itemId)
            );
    }
    void viewCart(){
        this->cart->showCart();
    }
    void buyCart(){
        cout<<"bought items costs of "<<(this->cart->getCartCost())<<endl;
    }
};
int main() {
    //Zepto LLD//
    //Users (id , name , location)
    //Items (id , name , cost , isAvailable)
    //Stores -> (list<Items>,location)
    //cart -> (list<Items>, totalCost)
    //Payment Strategy
    //Delivery partners (IsAvailable)
    
    //initialize
    StoreRepo* HydStore = new StoreRepo("HYD");
    HydStore->addItem("Coconut Water",70);
    HydStore->addItem("Bingo",20);
    HydStore->addItem("Doritos",40);
    HydStore->addItem("Diary Milk",100);
    HydStore->addItem("Pepsi",40);
    //User Interface
    ZeptoUserService* U1 = new ZeptoUserService("zafar",6302016113,"HYD",HydStore);
    //Show all items
        U1->showListOfItems();
        cout<<"--------------------------------------------------------------\n";
    //adding Items
        U1->addItem(1);
        U1->addItem(4);
        U1->viewCart();
        
    //Adding New Items
        HydStore->addItem("Coco Cola",40);
        U1->addItem(5);
        U1->viewCart();
    return 0;
}
