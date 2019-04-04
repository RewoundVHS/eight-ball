#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

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

	// Get user input, continue running if not quit
	cin >> question;
	while (question != "QUIT") {

		// Create two pipes
		if (pipe(to8) == -1 || pipe(from8) == -1) {
			cerr << "Pipe failed" << endl;
			return 1;
		}

		// Fork process
		pid = fork();
		if (pid == -1) {
			cerr << "Fork failed" << endl;
			return 1;
		}

		// Convert question to integer representation
		questionValue = 0;
		for (unsigned int i=0; i<question.length(); i++)
			questionValue += int(question.at(i));
		questionValueString = to_string(questionValue);

		// If parent
		if (pid > 0) {
			// Close pipe ends
			close(to8[READ]);
			close(from8[WRITE]);

			// Write to to8 pipe write end
			write(to8[WRITE], questionValueString.c_str(), questionValueString.size()+1);
			// Close to8 write end, wait for child, read response
			close(to8[WRITE]);
			wait(NULL);
			read(from8[READ], response, sizeof(response));

		// If Child
		} else {
			// Close to8 write end, redirect to8 read end to stdin
			close(to8[WRITE]);
			dup2(to8[READ], STDIN_FILENO);

			// Exec eight-ball, close from8 read end
			execl("eight-ball", "eight-ball", nullptr);
			close(from8[READ]);
		}
		cin >> question;
	}

	return 0;
}
