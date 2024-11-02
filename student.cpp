#include "./student.h"

Student::Student() {
    this->_number = 1;
    this->_score = 0;
}

Student::Student(unsigned int number, int score) {
    this->_number = number;
    this->_score = score;
}

Student::Student(Student* student) {
    this->_number = student->_number;
    this->_score = student->_score;
}
