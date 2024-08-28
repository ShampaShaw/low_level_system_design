#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Student {
protected: 
    string name;
    int id;
    map<string, double> grades;

public:
    Student(string n, int i) : name(n), id(i) {}  // Constructor

    // Getter for name
    string getName() const {
        return name;
    } 

    // Setter for name
    void setName(const string& n) {
        name = n;
    }

    // Getter for ID
    int getId() const {
        return id;
    }

    // Setter for ID
    void setId(int i) {
        id = i;
    }

    // Getter for grades
    map<string, double> getGrades() const {
        return grades;
    }

    // Setter for grades
    void setGrades(const map<string, double>& g) {
        grades = g;
    }

    // Add grade
    virtual void addGrade(const string& course, double grade) {
        grades[course] = grade;
    }

    // Display grades
    virtual void displayGrades() const {
        cout << "Grades for " << name << " (ID: " << id << "):" << endl;
        for (const auto& grade : grades) {
            cout << "Course: " << grade.first << " | " << "Grade: " << grade.second << endl;
        }
    }

    virtual ~Student() {}  // Virtual destructor
};

// Derived class: UnderGraduate
class UnderGraduate : public Student {
public:
    UnderGraduate(string n, int i) : Student(n, i) {}

    // Add grade
    void addGrade(const string& course, double grade) override {
        grades[course] = grade;
    }

    // Display grades
    void displayGrades() const override {
        cout << "UnderGraduate Student " << name << " (ID: " << id << ")" << endl;
        Student::displayGrades();
    }
};

// Derived class: Graduate
class Graduate : public Student {
public:
    Graduate(string n, int i) : Student(n, i) {}

    // Add grade
    void addGrade(const string& course, double grade) override {
        grades[course] = grade;
    }

    // Display grades
    void displayGrades() const override {
        cout << "Graduate Student " << name << " (ID: " << id << ")" << endl;
        Student::displayGrades();
    }
};

// Class: Courses
class Courses {
private:
    string courseName;
    vector<Student*> students;

public:
    Courses(string name) : courseName(name) {}

    void enrollStudent(Student* student) {
        students.push_back(student);
    }

    void assignGrades(int studentId, double grade) {
        for (auto& student : students) {
            if (student->getId() == studentId) {  // Correct condition
                student->addGrade(courseName, grade);
                break;
            }
        }
    }

    // Display grades
    void displayGrade() const {
        cout << "Grades for Course: " << courseName << endl;
        for (auto& student : students) {
            student->displayGrades();
        }
    }
};

int main() {
    UnderGraduate uStudent("Alice", 1);
    Graduate gStudent("Bob", 2);

    Courses course("Mathematics");

    course.enrollStudent(&uStudent);
    course.enrollStudent(&gStudent);

    course.assignGrades(1, 85.0);
    course.assignGrades(2, 90.5);  // This is fine since assignGrades accepts double

    course.displayGrade();

    return 0;
}
