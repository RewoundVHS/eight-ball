#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

const int BUF_SIZE = 1000;
enum Ends { READ, WRITE };

int main () {
	string question = "";
	int to8[2];
	int from8[2];
	pid_t pid;
	char response[100];
	string questionValueString;

	// Get user input, continue running if not quit
	getline(cin, question);
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
		int questionValue = 0;
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
			int len = read(from8[READ], response, BUF_SIZE);
			len = min(len, BUF_SIZE-1);
			response[len] = char(0);
			cout << response << endl;

		// If Child
		} else {
			// Close to8 write end, redirect to8 read end to stdin
			close(to8[WRITE]);
			dup2(to8[READ], STDIN_FILENO);
			// Close from8 read end, redirect from8 write end to stdout
			close(from8[READ]);
			dup2(from8[WRITE], STDOUT_FILENO);

			// Exec eight-ball, close from8 read end
			execl("eight-ball", "eight-ball", nullptr);
		}
		getline(cin, question);
	}

	return 0;
}
