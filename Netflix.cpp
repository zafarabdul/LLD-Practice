// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
class MovieIdGenerator{
    int movieId=0;
    MovieIdGenerator(){}
    public:
    static MovieIdGenerator* getInstance(){
        static MovieIdGenerator Instance;
        return &Instance;
    }
    int getId(){
        return this->movieId++;
    }
};
class UserIdGenerator{
    int id=0;
    UserIdGenerator(){}
    public:
    static UserIdGenerator* getInstance(){
        static UserIdGenerator Instance;
        return &Instance;
    }
    int getId(){
        return this->id++;
    }
};
class Movie{
    int movieId;
    string MovieName;
    string genre;
    vector<string>languages;
    public:
    Movie(string name,string genre,vector<string>languages):
    movieId(MovieIdGenerator::getInstance()->getId()),
    MovieName(name),genre(genre),languages(languages){};
    int getMovieId(){
        return this->movieId;
    }
    string getMovieName(){
        return this->MovieName;
    }
    string getGenre(){
        return this->genre;
    }
    vector<string>& getLanguages(){
        return this->languages;
    }
};
class MovieRepo{
    unordered_map<int,Movie*>movies;
    unordered_map<string,vector<Movie*>>ByGenre;
    unordered_map<string,vector<Movie*>>ByLanguage;
    deque<Movie*>newlyAdded;
    public:
    void addMovie(Movie* mv){
        if(!mv)return;
        movies[mv->getMovieId()]=mv;
        ByGenre[mv->getGenre()].push_back(mv);
        for(auto i:mv->getLanguages()){
            ByLanguage[i].push_back(mv);
        }
        newlyAdded.push_front(mv);
        while(newlyAdded.size()>4){
            newlyAdded.pop_back();
        }
    }
    void removeMovie(Movie* mv){
        if(!mv)return;
        movies.erase(mv->getMovieId());
        auto& vec = ByGenre[mv->getGenre()];
        vec.erase(
            remove(vec.begin(), vec.end(), mv),
            vec.end()
        );
        for(auto i:(mv->getLanguages())){
            auto& j = ByLanguage[i];
            j.erase(
                remove(j.begin(), j.end(), mv),
                j.end()
            );
        }
        newlyAdded.erase(
            remove(newlyAdded.begin(), newlyAdded.end(), mv),
            newlyAdded.end()
        );
    }
    vector<Movie*> getAllMovies(){
        vector<Movie*> ret;
        for(auto i:movies)ret.push_back(i.second);
        return ret;
    }
    Movie* getMovieById(int id){
        if(movies.find(id)!=movies.end()){
            return movies[id];
        }
        return nullptr;
    }
    deque<Movie*>& getRecentMovies(){
        return this->newlyAdded;
    }
    vector<Movie*> getMovieByGenre(string Genre){
        if(ByGenre.find(Genre)!=ByGenre.end()){
            return ByGenre[Genre];
        }
        return {};
    }
    vector<Movie*> getMovieByLanguage(string lang){
        if(ByLanguage.find(lang)!=ByLanguage.end()){
            return ByLanguage[lang];
        }
        return {};
    }
    vector<string> getAllGenres(){
        vector<string> ret;
        for(auto i:ByGenre)ret.push_back(i.first);
        return ret;
    }
};
class MovieService{
    MovieRepo* Repo = nullptr;
    void printMovie(Movie* mv){
        cout<<(mv->getMovieId())<<" ------ "<<(mv->getMovieName())<<" ------ "<<(mv->getGenre())<<endl;
    }
    public:
    MovieService(){
        this->Repo = new MovieRepo();
    }
    void addMovie(string name,string genre,vector<string>&l){
        this->Repo->addMovie(new Movie(name,genre,l));
    }
    void removeMovie(int id){
        Movie* mv = this->Repo->getMovieById(id);
        if(mv){
            this->Repo->removeMovie(mv);
        }
    }
    void showLists(vector<Movie*>&movies){
        cout<<"------------------------List Of Movies------------------------"<<endl;
        cout<<"New Movies On Netflix"<<endl;
        for(auto i:(this->Repo->getRecentMovies())){
            printMovie(i);
        }
        if(movies.size()){
            cout<<"Recently Watched Movies"<<endl;
            for(auto i:movies){
                printMovie(i);
            }
        }
        for(auto i:(this->Repo->getAllGenres())){
            cout<<endl;
            cout<<"--- "<<i<<" Movies To Watch ------------------------------"<<endl;
            for(auto j:(this->Repo->getMovieByGenre(i))){
                printMovie(j);
            }
        }
        cout<<"-----------------------List All Movies------------------------"<<endl;
        for(auto i:(this->Repo->getAllMovies())){
            printMovie(i);
        }
    }
    Movie* getMovieById(int id){
        return this->Repo->getMovieById(id);
    }
};
class Subscription{
    public:
    virtual int getCost() = 0;
    virtual bool canWatch(string device,int count) = 0;
};
class MobilePlan:public Subscription{
    int cost = 149;
    int maxWatch = 1;
    vector<string> supportedDevices = {"MOBILE"};
    public:
    bool canWatch(string device,int count) override{
        return device == "MOBILE" && count<=maxWatch;
    }
    int getCost() override {
        return this->cost;
    }
};
class BasicPlan:public Subscription{
    int cost = 199;
    int maxWatch = 1;
    vector<string> supportedDevices = {"MOBILE","TV","COMPUTER","TABLET"};
    public:
    bool canWatch(string device,int count) override {
        bool canW = false;
        for(auto i:(this->supportedDevices)){
            if(i == device){
                canW = true;
                break;
            }
        }
        return canW && count<=maxWatch;
    }
    int getCost() override {
        return this->cost;
    }
};
class StandardPlan:public Subscription{
    int cost = 499;
    int maxWatch = 2;
    vector<string> supportedDevices = {"MOBILE","TV","COMPUTER","TABLET"};
    public:
    bool canWatch(string device,int count) override{
        bool canW = false;
        for(auto i:(this->supportedDevices)){
            if(i == device){
                canW = true;
                break;
            }
        }
        return canW && count<=maxWatch;
    }
    int getCost() override {
        return this->cost;
    }
};
class PremiumPlan:public Subscription{
    int cost = 649;
    int maxWatch = 4;
    vector<string> supportedDevices = {"MOBILE","TV","COMPUTER","TABLET"};
    public:
    bool canWatch(string device,int count) override {
        bool canW = false;
        for(auto i:(this->supportedDevices)){
            if(i == device){
                canW = true;
                break;
            }
        }
        return canW && count<=maxWatch;
    }
    int getCost() override {
        return this->cost;
    }
};
class User{
    int userId;
    string gmail;
    string password;
    int liveUsers = 0;
    Subscription* subscriptionId;
    vector<Movie*>History;
    public:
    User(string gmail,string password):
    userId(UserIdGenerator::getInstance()->getId()),
    gmail(gmail),password(password),liveUsers(0)
    {
        this->subscriptionId = nullptr;
    }
    vector<Movie*>& getHistory(){
        return (this->History);
    }
    string getGmail(){
        return this->gmail;
    }
    bool isPasswordSame(string password){
        return (this->password) == password;
    }
    int getUserCount(){
        return this->liveUsers;
    }
    void incUserCount(){
        this->liveUsers++;
    }
    void decUserCount(){
        this->liveUsers--;
    }
    void addMovie(Movie* mv){
        this->History.push_back(mv);
    }
    void setSubscription(Subscription* sub){
        this->subscriptionId = sub;
    }
    void unSetSubscription(){
        this->subscriptionId = nullptr;
    }
    bool canViewDevice(string device,int count=1){
        if(!isSubscribed())return false;
        if(this->subscriptionId->canWatch(device,count))return true;
        return false;
    }
    bool isSubscribed(){
        return (this->subscriptionId != nullptr);
    }
};
class UserRepo{
    vector<User*>users;
    public:
    User* addUser(string gmail,string password){
        if(this->isDuplicateUser(gmail))return nullptr;
        User* u = new User(gmail,password);
        users.push_back(u);
        return u;
    }
    void removeUser(User* u){
        for(int i=0;i<(this->users.size());i++){
            if(u == this->users[i]){
                swap(this->users[i],this->users[(this->users.size())-1]);
                this->users.pop_back();
                return;
            }
        }
    }
    bool isDuplicateUser(string gmail){
        for(auto i:users){
            if(i->getGmail() == gmail)return true;
        }
        return false;
    }
    User* getUser(string gmail , string password){
        for(auto i:(this->users)){
            if(i->getGmail() == gmail && i->isPasswordSame(password))return i;
        }
        return nullptr;
    }
};
class NetflixManager{
    MovieService* MovieSer = nullptr;
    UserRepo* userRepo = nullptr;
    User* currUser = nullptr;
    string device = "";
    bool isLoggedIn(){
        if(currUser){
            return true;
        }
        return false;
    }
    void printWatching(Movie* mv){
        cout<<"----------------Playing-------------"<<endl;
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"Currently Watching ------ "<<(mv->getMovieName())<<" ------------------------ "<<endl;
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"---------------------------------------------------------"<<endl;
    }
    public:
    NetflixManager(){
        this->MovieSer = new MovieService();
        this->userRepo = new UserRepo();
    }
    void addMovie(string name,string genre,vector<string>l){
        this->MovieSer->addMovie(name,genre,l);
    }
    void removeMovie(int id){
        this->MovieSer->removeMovie(id);
    }
    void openHomePage(){
        if(!this->isLoggedIn())return;
        this->MovieSer->showLists(
            this->currUser->getHistory()
            );
    }
    void login(string gmail,string password,string device){
        if(isLoggedIn())return;
        currUser = userRepo->getUser(gmail,password);
        if(!currUser){
            cout<<"user or password does not exist"<<endl;
            return;
        }
        this->device = device;
        this->currUser->incUserCount();
    }
    void signUp(string gmail,string password,string device){
        if(isLoggedIn()){
            cout<<"Already Logged In";
            return;
        }
        currUser = userRepo->addUser(gmail,password);
        if(!currUser){
            cout<<"user already exists"<<endl;
            return;
        }
        this->currUser->incUserCount();
        this->device = device;
    }
    void logout(){
        this->currUser->decUserCount();
        this->currUser = nullptr;
    }
    void playVideo(int id){
        // clearScreen();
        if(this->isLoggedIn() && this->currUser->isSubscribed() && this->currUser->canViewDevice(this->device,this->currUser->getUserCount())){
            Movie* movie = this->MovieSer->getMovieById(id);
            if(movie){
                this->currUser->addMovie(movie);
                printWatching(movie);
            }
            else cout<<"Movie Not Found"<<endl;
        }
        else {
            if((this->isLoggedIn()))cout<<"No Subscription Plan"<<endl;
            else cout<<"Please Login"<<endl;
        }
    }
    void subscribe(string plan){
        if(this->isLoggedIn()){
            Subscription* sc = nullptr;
            if(plan == "MOBILE"){
                sc = new MobilePlan();
            }
            else if(plan == "BASIC"){
                sc = new BasicPlan();
            }
            else if (plan == "STANDARD"){
                sc = new StandardPlan();
            }
            else if (plan == "PREMIUM"){
                sc = new PremiumPlan();
            }
            else {
                cout<<"No Such Plan";
                return;
            }
            this->currUser->setSubscription(sc);
        }
        else cout<<"User Not Logged In"<<endl;
    }
};
int main() {
    // Netflix LLD
    // MovieService
        // MovieRepo(movieId,moviegenre,movieLanguages,movieName)
    // UserService
        // User (UserId , UserEmail , UserPassword , UserSub , UserWatchList ,UserHistory) 
        // User Login Or SignUp ->(Check Subscribtion Plan)?(Open):(Payment Page);
    // PaymentService
        // PaymentStrategy
        // PaymentPan
        
    //Movie Setup
    NetflixManager* NM = new NetflixManager();
    NM->addMovie("KGF","ACTION",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("RRR","ACTION",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("LOVE TODAY","DRAMA",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("AVATAR","SCIENCE FANTASY",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("OBSESSION","HORROR",{"ENGLISH"});
    
    //User Setup
    NM->signUp("mohammed-abdul-zafar@gmail.com","12345","MOBILE");
    NM->logout();
    NM->login("mohammed-abdul-zafar@gmail.com","12345","MOBILE");
    
    //Buy Subscription
    NM->subscribe("BASIC");
    
    NM->openHomePage();
    
    int id;
    cout<<endl<<endl;
    // repeat it for watching movies
    // {
    cout<<"----------enter id to watch: ";
    cin>>id;
    NM->playVideo(id);
    // }
    cout<<"----------enter id to watch: ";
    cin>>id;
    NM->playVideo(id);
    
    // U can see watch history here
    NM->openHomePage();
    
    return 0;
}
