#include <iostream>
#include <iterator> // for iterators 
#include <vector> // for vectors 
#include <iomanip>      // std::setw (set field width)
#include <string> // for strings
using namespace std;

//A function has a const TYPE& argument so that is avoided the creation of a new instance and the constructor isn't called
bool isvalidcc(const string&);

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;

	// Declaring iterator to a vector 
	vector<string>::iterator itr;

	//begin() :- This function is used to return the beginning position of the container.
	//end() :- This function is used to return the after end position of the container.
	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " " 
			 << setw(17) << *itr 
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}

/****Test credit card number pattern to see if it is valid.****
 *example: 4 3 8 8 5 7 6 0 1 8 4 0 2 6 2 6
step a:  Double every second digit from right to left. If doubling of a digit results
		 in a two-digit number, add the two digits to get a single digit number.
step b:  Now add all single-digit numbers from Step a:
		 4 + 4 + 8 + 2 + 3 + 1 + 7 + 8 = 37
step c:  Add all digits in the odd places from right to left in the card number:
		6 + 6 + 0 + 8 + 0 + 7 + 8 + 3 = 38
step d:  Sum the results from Step b and Step c:
		37 + 38 = 75
step e: If the result from Step d is divisible by 10, the card number is valid;
		otherwise, it is invalid.  */

bool isvalidcc(const string& tempCCNString){
	int tempSum = 0;
	int evenSum = 0;
	int oddSum = 0;
	int total = 0;
	int evenIndex, oddIndex;

    //evenIndex - 2 because index begins from 0. example: total digits = 15, 从右向左第一个even digit 应该是第二个，也就是从左向右的第14位，however，
	//index从零开始，所以它的index是13， aka （15-2）
	//step a
	for(evenIndex = (tempCCNString.size() - 2); evenIndex >= 0 ; evenIndex -= 2){
		tempSum = 2 * stoi(tempCCNString.substr(evenIndex, 1));

		if(tempSum >= 10){ //step b
			tempSum = tempSum % 10 +1;
			evenSum += tempSum;
		}else{
			evenSum += tempSum;
		}
	}

	//step c
	for(oddIndex = (tempCCNString.size() - 1); oddIndex >= 0; oddIndex -=2 ){
		oddSum += stoi(tempCCNString.substr(oddIndex, 1));
	}

	//step d
	total = evenSum + oddSum;

	//step e
	if(total % 10 == 0){
		return true;
	}else{
		return false;
	}
}

/************ convert string to integer***********************
stoi() function

example:
int main() {
    string pp = "123";

    int num1 = stoi(pp);

    cout << "stoi(\"" << pp << "\") is " << num1 << '\n';
}
*************************************************************/



/*********     Substring   ************************************
string substr (size_t pos, size_t len) const;
Parameters:
	pos: Position of the first character to be copied.
	len: Length of the sub-string.
	size_t: It is an unsigned integral type.

Return value: It returns a string object.

1. The index of the first character is 0 (not 1).
2. If pos is equal to the string length, the function returns an empty string.
3. If pos is greater than the string length, it throws out_of_range. If this happen, there are no changes in the string.
4. If for the requested sub-string len is greater than size of string, then returned sub-string is [pos, size()).

example:
int main() 
{ 
    // Take any string 
    string s1 = "Geeks"; 
  
    // Copy three characters of s1 (starting  
    // from position 1) 
    string r = s1.substr(1, 3); 
  
    // prints the result 
    cout << "String is: " << r; 
  
    return 0; 
} 
Output:

String is: eek  
*************************************************************/