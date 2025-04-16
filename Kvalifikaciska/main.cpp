#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;


class MultipleChoiceQuestion {
private:
    char correctAnswer;
    int points;

public:
    MultipleChoiceQuestion() {
        points=1;
        correctAnswer='A';
    }
    MultipleChoiceQuestion(char correctAnswer) {
        this->correctAnswer=correctAnswer;
        points=1;
    }
    MultipleChoiceQuestion(char correctAnwse, int points) {
        this->points=points;
        this->correctAnswer=correctAnwse;
    }
    float answer(char choice) {
        if (choice==correctAnswer)
            return points;
        else
            return points-(points*1.25);
    }

    void print () {
        cout << "Correct answer: " << correctAnswer << " Points: " << points << endl;
    }

    // TODO answer method
};

int main() {

    MultipleChoiceQuestion mcq;

    int testCase;
    char correctAnswer;
    int points;
    while (cin >> testCase){
        if (testCase==1){
            cout << "Constructor with 1 argument test" << endl;
            cin >> correctAnswer;
            mcq = MultipleChoiceQuestion(correctAnswer);
        } else if (testCase==2){
            cout << "Constructor with 2 arguments test" << endl;
            cin >> correctAnswer >> points;
            mcq = MultipleChoiceQuestion(correctAnswer, points);
        } else if (testCase==3){
            cout << "print() method test" << endl;
            mcq.print();
        } else {
            char answer;
            cin >> answer;
            cout << "answer("<<answer<<") method test" << endl;
            cout << mcq.answer(answer) << endl;
        }
    }
    return 0;
}



