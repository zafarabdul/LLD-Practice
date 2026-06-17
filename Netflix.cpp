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
        this->Repo->removeMovie(
            this->Repo->getMovieById(id)
            );
    }
    void showLists(){
        cout<<"------------------------List Of Movies------------------------"<<endl;
        cout<<"Recently Added Movies"<<endl;
        for(auto i:(this->Repo->getRecentMovies())){
            printMovie(i);
        }
        for(auto i:(this->Repo->getAllGenres())){
            
            cout<<"--- "<<i<<" Movies To Watch ---"<<endl;
            for(auto j:(this->Repo->getMovieByGenre(i))){
                printMovie(j);
            }
        }
        cout<<"-----------------------List All Movies------------------------"<<endl;
        for(auto i:(this->Repo->getAllMovies())){
            printMovie(i);
        }
    }
};
class NetflixManager{
    MovieService* MovieSer = nullptr;
    public:
    NetflixManager(){
        this->MovieSer = new MovieService();
    }
    void addMovie(string name,string genre,vector<string>l){
        this->MovieSer->addMovie(name,genre,l);
    }
    void removeMovie(int id){
        this->MovieSer->removeMovie(id);
    }
    void openHomePage(){
        this->MovieSer->showLists();
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
    NetflixManager* NM = new NetflixManager();
    NM->addMovie("KGF","ACTION",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("RRR","ACTION",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("LOVE TODAY","DRAMA",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("AVATAR","SCIENCE FANTASY",{"HINDI","TELUGU","KANNADA"});
    NM->addMovie("OBSESSION","HORROR",{"ENGLISH"});
    NM->openHomePage();
    return 0;
}
