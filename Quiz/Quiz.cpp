#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;


struct Question {
	string questionText;
	string answers[3];
	int correctAnswer; // correct answer (1-3)
};

bool isCorrect(Question question, int answer) {
	return answer == question.correctAnswer;
};

int main()
{
	Question questions[4];
	int userAnswer, correctAnswers = 0, incorrectAnswers = 0;

	// Question 1
	questions[0].questionText = "Which is the smallest country?";
	questions[0].answers[0] = "USA";
	questions[0].answers[1] = "India";
	questions[0].answers[2] = "Vatican City";
	questions[0].correctAnswer = 3;

	// Question 2
	questions[1].questionText = "Which is the biggest animal in the world?";
	questions[1].answers[0] = "Elephant";
	questions[1].answers[1] = "Blue Whale";
	questions[1].answers[2] = "Great White Shark";
	questions[1].correctAnswer = 2;

	// Question 3
	questions[2].questionText = "How many elements are in the periodic table?";
	questions[2].answers[0] = "118 elements";
	questions[2].answers[1] = "119 elements";
	questions[2].answers[2] = "120 elements";
	questions[2].correctAnswer = 1;

	// Question 4
	questions[3].questionText = "(x+3)(x-2) = 0. Find x";
	questions[3].answers[0] = "x = -3";
	questions[3].answers[1] = "x = 2";
	questions[3].answers[2] = "All of the above.";
	questions[3].correctAnswer = 3;

	// Loop through questions
	for (Question question : questions) {
		cout << question.questionText << endl;
		for (int j = 0; j < 3; j++) {
			cout << j+1 << ". " << question.answers[j] << endl;
		};
		
		cout << "Choose 1-3: ";
		cin >> userAnswer;

		if (isCorrect(question, userAnswer)) {
			correctAnswers++;
			cout << "Correct!\n" << endl;
		}
		else {
			incorrectAnswers++;
			cout << "Incorrect!\n" << endl;
		}
	};

	cout << "You got " << correctAnswers << " correct answers and " << incorrectAnswers << " incorrect answers." << endl;

	system("pause");
}
