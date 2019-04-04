#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main () {
	string toConvert;

	// Get input, convert to integer
	cin >> toConvert;
	int value = strtol(toConvert.c_str(), NULL, 10);
	value = value % 20;

	// Print eight ball response
	switch (value) {
		case 0: cout << "It is certain." << endl;
			break;
		case 1: cout << "It is decidedly so." << endl;
			break;
		case 2: cout << "Without a doubt." << endl;
			break;
		case 3: cout << "Yes - definitely" << endl;
			break;
		case 4: cout << "You may rely on it." << endl;
			break;
		case 5: cout << "As I see it, yes." << endl;
			break;
		case 6: cout << "Most likely." << endl;
			break;
		case 7: cout << "Outlook good." << endl;
			break;
		case 8: cout << "Yes." << endl;
			break;
		case 9: cout << "Signs point to yes." << endl;
			break;
		case 10: cout << "Reply hazy, try again." << endl;
			break;
		case 11: cout << "Ask again later." << endl;
			break;
		case 12: cout << "Better not tell you now." << endl;
			break;
		case 13: cout << "Cannot predict now." << endl;
			break;
		case 14: cout << "Concentrate and ask again." << endl;
			break;
		case 15: cout << "Don't count on it." << endl;
			break;
		case 16: cout << "My reply is no." << endl;
			break;
		case 17: cout << "My sources say no." << endl;
			break;
		case 18: cout << "Outlook not so good." << endl;
			break;
		case 19: cout << "Very doubtful." << endl;
			break;
	}

	return 0;
}
