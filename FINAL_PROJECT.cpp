#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include<random>
#include <curl/curl.h>

size_t WriteCallback(void* git contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::string selectCategory(const std::vector<std::pair<std::string,int>>& categories)
{
    std::cout << "Select a category:" << std::endl;
    for (const auto& pair: categories) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    int choice;
    std::cin >> choice;
    for (const auto& pair: categories){
        if (choice ==pair.second)
		{  std::string number=std::to_string(choice);
		   return number;} }
        std::cout << "Invalid choice. Defaulting to first category." << std::endl;
        return "9"; // Return the first category by default
    }
std::pair<std::vector<std::string>, std::vector<std::string>> getQuestionsAndAnswersFromAPI(const std::string& url,const std::string& category, const std::string& difficulty)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    
    // Construct URL with difficulty level
    std::string apiUrl = url + "&category=" + category + "&difficulty=" + difficulty;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::vector<std::string> questions;
        std::vector<std::string> answers;

        size_t pos = 0;
        while ((pos = readBuffer.find("\"question\":\"", pos)) != std::string::npos) {
            pos += sizeof("\"question\":\"") - 1;
            size_t endPos = readBuffer.find("\"", pos);
            if (endPos == std::string::npos) break;
            std::string question = readBuffer.substr(pos, endPos - pos);
            questions.push_back(question);
            pos = endPos + 1;
        }

        pos = 0;
        while ((pos = readBuffer.find("\"correct_answer\":\"", pos)) != std::string::npos) {
            pos += sizeof("\"correct_answer\":\"") - 1;
            size_t endPos = readBuffer.find("\"", pos);
            if (endPos == std::string::npos) break;
            std::string answer = readBuffer.substr(pos, endPos - pos);
            answers.push_back(answer);
            pos = endPos + 1;
        }

        return {questions, answers};
    }
    return {{}, {}};
}
int Player1=0;
int Player2=0;
void playRound(int roundNumber, const std::vector<std::string>& questions, const std::vector<std::string>& answers)
{
    std::cout << "Round " << roundNumber << std::endl;
    int score1 = 0;
    int score2=0;
    std::cout<<"player one:"<<std::endl;
    for (size_t i = 0; i < questions.size()/2; ++i) {
		std::string playerAnswer;
        std::cout << "Question " << (i + 1) << ": " << questions[i] << std::endl;
        std::cout << "Your answer: ";
        std::cin>>playerAnswer;
        std::string correctAnswer = answers[i];
        std::cout << "Correct answer: " << correctAnswer << std::endl;
        std::cout << "Player answer: " << playerAnswer << std::endl;

        if (playerAnswer == correctAnswer) {
            std::cout << "Correct!" << std::endl;
            score1++;
        } else {
            std::cout << "Incorrect!" << std::endl;
        }}
        std::cout<<"SCORE OF THE ROUND:"<<score1<<std::endl;
        int k=5;
        std::cout<<"player tow:"<<std::endl;
		for (size_t i =5;i< questions.size(); ++i) {
		std::string playerAnswer;
        std::cout << "Question " << (i - k+1) << ": " << questions[i] << std::endl;
        std::cout << "Your answer: ";
        std::cin>>playerAnswer;
        std::string correctAnswer = answers[i];
        std::cout << "Correct answer: " << correctAnswer << std::endl;
        std::cout << "Player answer: " << playerAnswer << std::endl;

        if (playerAnswer == correctAnswer) {
            std::cout << "Correct!" << std::endl;
            score2++;
        } else {
            std::cout << "Incorrect!" << std::endl;
        }}
        std::cout<<"SCORE OF THE ROUND:"<<score2<<std::endl;
        if (score1<score2)
          Player2++;
        else if(score1>score2)
          Player1++;
    
    
    std::cout << "Round " << roundNumber << " Player one: " << Player1  << "  Player tow:" << Player2 << std::endl;
       
}
int Player=0;
int playRound1(int roundNumber, const std::vector<std::string>& questions, const std::vector<std::string>& answers)
{   int score=0;
    std::cout << "Round " << roundNumber << std::endl;
    std::cout<<"respond to THE QUESTIONS:"<<std::endl;
    for (size_t i = 0; i < questions.size(); ++i) {
		std::string playerAnswer;
        std::cout << "Question " << (i + 1) << ": " << questions[i] << std::endl;
        std::cout << "Your answer: ";
        std::cin>>playerAnswer;
        std::string correctAnswer = answers[i];
        std::cout << "Correct answer: " << correctAnswer << std::endl;
        std::cout << "Player answer: " << playerAnswer << std::endl;

        if (playerAnswer == correctAnswer) {
            std::cout << "Correct!" << std::endl;
            score++;
        } else {
            std::cout << "Incorrect!" << std::endl;
        }}
        std::cout<<"SCORE OF THE ROUND:"<<score<<std::endl;
        if(score>6){
		    Player++;}
		return score;}
    

int main()
{   while(true)
    {int n;
    std::cout<<"choose a number (1 or 2) for: tow player/one player."<<std::endl;
    std::cin>>n;
    std::string apiUrl = "https://opentdb.com/api.php?amount=10&type=multiple";
    // Fetch questions for easy difficulty
    std::string difficulty;
    std::string category;
    std::vector<std::pair<std::string,int>> categories ={{"General Knowledge",9},{"Entertainment: Books",10},{"Entertainment: Film",11},{"Entertainment: Music",12},{"Entertainment: Musicals &Theatres",13},{"Entertainment: Television",14},{"Entertainment: Video Games",15},{"Entertainment: Board Games",16},{"Science & Nature",17},{"Science: Computers",18},{"Science: Mathematics",19},{"Mythology",20}, {"Sports",21}, {"Geography",22}, {"History",23}, {"Politics",24}, {"Art",25},{"Celebrities",26},{"Animals",27},{"Vehicles",28},{"Entertainment:Comics",29},{"Science:Gadgets",30},{"Entertainment: Japanese Anime & Manga",31},{"Entertainment: Cartoon & Animations",32}} ;
    switch(n){
	case 1:
	for (int round = 1; round <= 4; ++round) {
    if (round%2!=0)
        {std::cout<<"player one enter the level of questions:easy,medium or hard:";
        std::cin>>difficulty;
		category = selectCategory(categories);}
    else
       {std::cout<<"player two enter the level of questions:easy,medium or hard:";
        std::cin>>difficulty;
		category = selectCategory(categories);} 
	auto [questions, answers] = getQuestionsAndAnswersFromAPI(apiUrl,category,difficulty);

    if (questions.empty() || answers.empty()) {
        std::cerr << "Failed to get questions or answers from API" << std::endl;
        return 1;
    }
    	
        playRound(round, questions, answers);
    }
     if (Player1==Player2){
     	while(Player1==Player2){
       std::vector<std::string>options={"easy","medium","hard"};
	   std::random_device rd1;
	   std::mt19937 gen1(rd1());
	   std::uniform_int_distribution<>dis1(0,options.size()-1);
	   int random_index=dis1(gen1);
	   difficulty=options[random_index];
	   std::random_device rd2;
	   std::mt19937 gen2(rd2());
	   std::uniform_int_distribution<>dis2(9,32);
	   int random_index1=dis2(gen2);
	   category=std::to_string(random_index1);
	   std::cout<<"***Golden Round***"<<std::endl;
	   std::cout<<"category:"<<category<<std::endl;
	   std::cout<<"difficulty:"<<difficulty<<std::endl;
	   auto [questions, answers] = getQuestionsAndAnswersFromAPI(apiUrl,category,difficulty);

    if (questions.empty() || answers.empty()) {
        std::cerr << "Failed to get questions or answers from API" << std::endl;
        return 1;
    }
	playRound(0, questions, answers);}
	 }
	if(Player1>Player2)
       std::cout<<"PLAYER ONE IS THE WINNER!"<<std::endl;
    else if(Player1<Player2)
       std::cout<<"PLAYER TOW IS THE WINNER!"<<std::endl; 
    break;
    case 2:
    	int score1=0;
		int score2=0;
		int score3=0;
    for (int round = 1; round <= 3; ++round) {	
       std::random_device rd3;
	   std::mt19937 gen3(rd3());
	   std::uniform_int_distribution<>dis3(9,32);
	   int random_index2=dis3(gen3);
	   category=std::to_string(random_index2);
	   std::cout<<"enter the difficulty:"<<std::endl;
	   std::cin>>difficulty;
	   auto [questions, answers] = getQuestionsAndAnswersFromAPI(apiUrl,category,difficulty);
	   if (questions.empty() || answers.empty()) {
        std::cerr << "Failed to get questions or answers from API" << std::endl;
        return 1;
    } if(difficulty=="easy")
	    score1=playRound1(round, questions, answers);
	  else if(difficulty=="medium")
	    score2=playRound1(round, questions, answers);
	  else
	    score3=playRound1(round, questions, answers);
	    }
	 std::cout<<"HIGH SCORE"<<Player<<std::endl<<score1<<" "<<score2<<" "<<score3<<std::endl;
	     
	break;
	   }
}
}

