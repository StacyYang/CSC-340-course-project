#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

vector<string> partOfSpeech = {"noun", "pronoun", "adjective", "verb", "adverb", "preposition", "conjunction", "interjection"};
vector<string> words;

bool containsKey(string);
bool containsPOS(string);
string convertLowerCase(string);
string convertUpperCase(string);
int inputNumberCount(string, string, string);
void printAll(multimap<string, vector<string>>, string); //only one input : keyword
void printDistinct(multimap<string, vector<string>>, string); // two inputs: keyword && distinct
void printPOS(multimap<string, vector<string>>, string, string); //two inputs: keyword && part of speech
void printPOSDistinct(multimap<string, vector<string>>, string, string); //threee inputs: keyword && part of speech && distinct

int main(){

	cout << "! Opening data file... ./Data.CS.SFSU.txt" << endl;
	fstream ioFile;
	string line;
	ioFile.open("Data.CS.SFSU.txt", ios::in);
	cout << "! Loading data..." << endl;

	multimap<string, vector<string>> wordbank;
	while(getline(ioFile, line)) {

		stringstream ssline{line};
		string wordName, secondPart, description, definition, wordPrint;
		string csc = "csc";
		vector<string> definitionList;
		getline(ssline, wordName, '|');
			wordPrint = wordName;
			if(wordPrint.find(csc) != string::npos){//npos: greatest value possible
				wordPrint = convertUpperCase(wordPrint);
			}else{
				wordPrint[0] = static_cast<char>(toupper(wordPrint[0]));
			}
			//cout<<"this is keyword " << wordPrint<<endl;
		while(getline(ssline, secondPart, '|')){
			stringstream ssPOS{secondPart};
			string pOfSpeech;
			getline(ssPOS, pOfSpeech, ' ');
			getline(ssPOS, description, '|');
			definition = description.substr(description.find('-') + 5);
			string catString = wordPrint + " [" + pOfSpeech + "] : " + definition;
			definitionList.push_back(catString);
		}
		wordbank.insert(pair <string, vector<string>> (wordName, definitionList));
		words.push_back(wordName);
		// for(int i = 0; i < definitionList.size(); i++ ) {
	 	// 	cout<< i << " : "  <<definitionList[i]<<endl;
	 	// }
	}

	/*   How to print out all values in multimap<string, vector<string>>

	for(multimap<string, vector<string>>:: const_iterator itr{wordbank.begin()}; itr != wordbank.end(); ++itr){
		cout << "this is keyword: " << itr->first<< "  " <<endl;

	 	vector<string>::const_iterator itVec;
	 	for (itVec = itr->second.begin(); itVec != itr->second.end(); ++itVec){
	 	cout << *itVec << endl;
	 	}
	 	cout<<endl;
	 }
	}*/
	
	 

	cout << "! Loading completed..." << endl;
	cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
	ioFile.close();
	cout << "----- DICTIONARY 340 C++ -----" << endl;

	
	bool searchState = true;
	while(searchState) {
		string userInput;
		string inputWord, inputPOS, inputThird, inputF;
		cout << "Search: ";

		getline(cin, userInput);
		if(userInput.compare("!Q") == 0){
			searchState = false;
			cout << "\n-----THANK YOU-----" << endl;
			exit(0);
		}
		userInput = convertLowerCase(userInput);
		stringstream tokens{userInput};
		tokens >> inputWord;
		tokens >> inputPOS;
		tokens >> inputThird;

		int inputNum = inputNumberCount(inputWord, inputPOS, inputThird);

		if(inputNum == 0 || inputNum > 3){
			cout << " \n Please enter a search key (and a part of speech and/or distinct." << endl;
		}
		
		if(containsKey(inputWord)){
			if(inputNum == 1){
				printAll(wordbank, inputWord);
			}

			if(inputNum == 2 && (inputPOS.compare("distinct") == 0 || containsPOS(inputPOS))){
				if(containsPOS(inputPOS)){
					printPOS(wordbank, inputWord, inputPOS);
				}else{
					printDistinct(wordbank, inputWord);
					continue;
				}
			}else if(inputNum == 2 && inputPOS.compare("distinct") != 0){
				cout << "\t|"<<endl;
				cout << "\t<2nd argument must be a part of speech or \"distinct\">" << endl;
				cout << "\t|"<<endl;
				continue;
			}

			if(inputNum == 3){
				if(!containsPOS(inputPOS)){
					cout << "\t|"<<endl;
					cout << "\t<2nd argument must be a part of speech or \"distinct\">" << endl;
					cout << "\t|"<<endl;
					continue;
				}else if(inputThird.compare("distinct") == 0){
					printPOSDistinct(wordbank, inputWord, inputPOS);
				}else if(inputThird.compare("distinct") != 0){
					cout << "\t|"<<endl;
					cout << "\t<The third argument only support \"distinct\" for now>" << endl;
					cout << "\t|"<<endl;
					continue;
				}
			}
		}else{
				cout << "\t|"<<endl;
				cout << "\t<Not found>"<<endl;
				cout << "\t|"<<endl;
		}
	}
	return 0;
}

bool containsKey(string str){
	if( find(words.begin(), words.end(), str) != words.end()){
		return true;
	}else{
		return false;
	}
}

bool containsPOS(string str){
	if( find(partOfSpeech.begin(), partOfSpeech.end(), str) != partOfSpeech.end()){
		return true;
	}else{
		return false;
	}
}

//tolower(char) only takes a char at a time.
string convertLowerCase(string tempString){
	char ch;
	for(int i = 0; i < tempString.length(); i++){
		ch = static_cast<char>(tolower(tempString[i]));
		tempString[i] = ch;
	}
	return tempString;
}

string convertUpperCase(string tempString){
	char ch;
	for(int i = 0; i < tempString.length(); i++){
		ch = static_cast<char>(toupper(tempString[i]));
		tempString[i] = ch;
	}
	return tempString;
}

int inputNumberCount(string inputWord, string inputPOS, string inputThird){
	int count = 0;
	if(!inputWord.empty()){ 
		count++;
	}
	if(!inputPOS.empty()){ 
		count++;
	}
	if(!inputThird.empty()){ 
		count++;
	}
	return count;
}

void printAll(multimap<string, vector<string>> wordbank, string inputWord){  
	string searchKey = inputWord;
	for(auto itr = wordbank.begin(); itr != wordbank.end(); ++itr){
		if(itr->first == searchKey){
			cout << "\t|" << endl;
			vector<string>::const_iterator itVec;
	 		for (itVec = itr->second.begin(); itVec != itr->second.end(); ++itVec){
				sort(itr->second.begin(), itr->second.end());
	 			cout << "\t" << *itVec << endl;
	 		}
			cout << "\t|" << endl;
		}
	}
}

void printDistinct(multimap<string, vector<string>> wordbank, string inputWord){
	string searchKey = inputWord;
	for(auto itr = wordbank.begin(); itr != wordbank.end(); ++itr){
		if(itr->first == searchKey){
			vector<string>::iterator ip;
			sort(itr->second.begin(), itr->second.end());
			ip = unique(itr->second.begin(), itr->second.end());
			itr->second.resize(distance(itr->second.begin(), ip));
			cout << "\t|" << endl;
	 		for (ip = itr->second.begin(); ip != itr->second.end(); ++ip){
	 			cout << "\t" << *ip << endl;
	 		}
			cout << "\t|" << endl;
		}
	}
}

void printPOS(multimap<string, vector<string>>wordbank, string inputWord, string inputPOS){
	string searchKey = inputWord;
	string pos = "[" + inputPOS + "]";
	int i = 0;
	for(auto itr = wordbank.begin(); itr != wordbank.end(); ++itr){
		if(itr->first == searchKey){
			cout << "\t|" << endl;
			vector<string>::const_iterator itVec;
			sort(itr->second.begin(), itr->second.end());
	 		for (itVec = itr->second.begin(); itVec != itr->second.end(); ++itVec){
				if(itVec ->find(pos) != string::npos){
					i++;
				}
	 		}
			if(i == 0){
				cout << "\t<Not found>" << endl;
			}else{
				for (itVec = itr->second.begin(); itVec != itr->second.end(); ++itVec){
					if(itVec ->find(pos) != string::npos){
						cout << "\t" << *itVec << endl;
					}
	 			}
			}
			cout << "\t|" << endl;
		}
	}
}

void printPOSDistinct(multimap<string, vector<string>>wordbank, string inputWord, string inputPOS){
	string searchKey = inputWord;
	string pos = "[" + inputPOS + "]";
	int i = 0;
	for(auto itr = wordbank.begin(); itr != wordbank.end(); ++itr){
		if(itr->first == searchKey){
			cout << "\t|" << endl;
			vector<string>::iterator ip;
			sort(itr->second.begin(), itr->second.end());
			ip = unique(itr->second.begin(), itr->second.end());
			itr->second.resize(distance(itr->second.begin(), ip));
			for (ip = itr->second.begin(); ip != itr->second.end(); ++ip){
				if(ip->find(pos) != string::npos){
					i ++;
				}
	 		}
			if(i == 0){
				cout << "\t<Not found>" << endl;
			}else{
				for (ip = itr->second.begin(); ip != itr->second.end(); ++ip){
					if(ip ->find(pos) != string::npos){
						cout << "\t" << *ip << endl;
					}
	 			}
			}
			cout << "\t|" << endl;
		}
	}
}



