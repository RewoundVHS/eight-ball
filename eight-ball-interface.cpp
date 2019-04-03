#include <iostream>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main () {
	string question;
	int questionValue;
	int fd1[2];
	int fd2[2];
	pid_t pid;

	if (pipe(fd1) == -1 || pipe(fd2) == -1) {
		cerr << "Pipe failed" << endl;
		return 1;
	}

	pid = fork();

	if (pid == -1) {
		cerr << "Pipe failed" << endl;
		return 1;
	}

	//TODO: fork and exec eight-ball
	//TODO: pipe questionValue to eight-ball
	//TODO: pipe eight-ball output to this process

	if (pid > 0) {

		while (question != "QUIT") {
			questionValue = 0;

			cin >> question;

			for (unsigned int i=0; i<question.length(); i++)
				questionValue += int(question.at(i));

		}
	}

	return 0;
}
