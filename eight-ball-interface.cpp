#include <iostream>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;

enum Ends { READ, WRITE };

int main () {
	string question = "";
	int questionValue;
	int to8[2];
	int from8[2];
	pid_t pid;
	char response[100];
	string questionValueString;

	// TODO: fork and exec eight-ball
	// TODO: pipe questionValue to eight-ball
	// TODO: pipe eight-ball output to this process

	cin >> question;
	while (question != "QUIT") {
		if (pipe(to8) == -1 || pipe(from8) == -1) {
			cerr << "Pipe failed" << endl;
			return 1;
		}

		pid = fork();
		if (pid == -1) {
			cerr << "Fork failed" << endl;
			return 1;
		}

		if (pid > 0) {
			close(to8[READ]);
			close(from8[WRITE]);

			questionValue = 0;
			for (unsigned int i=0; i<question.length(); i++)
				questionValue += int(question.at(i));
			questionValueString = to_string(questionValue);

			write(to8[WRITE], questionValueString.c_str(), questionValueString.size()+1);
			close(to8[WRITE]);
			wait(NULL);
			read(from8[READ], response, sizeof(response));
		} else {
			close(to8[WRITE]);
			dup2(to8[READ], READ);
			execl("eight-ball", "eight-ball", nullptr);
			close(from8[READ]);
		}
		cin >> question;
	}

	return 0;
}
