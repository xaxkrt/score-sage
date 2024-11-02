#ifndef _STUDENT_H_
#define _STUDENT_H_

class Student {
  public:
    unsigned int _number;
    int _score;

    Student();
    Student(unsigned int number, int score);
    Student(Student* student);
};

#endif // !_STUDENT_H_
