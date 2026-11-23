#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

struct Student
{
    int rollNo;
    string name;
    int age;
    string course;
};

// Read student records from file
vector<Student> loadStudents()
{
    vector<Student> students;
    ifstream file("students.txt");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        Student s;
        string roll, age;

        getline(ss, roll, '|');
        getline(ss, s.name, '|');
        getline(ss, age, '|');
        getline(ss, s.course, '|');

        try
        {
            s.rollNo = stoi(roll);
            s.age = stoi(age);
            students.push_back(s);
        }
        catch (...)
        {
            continue;
        }
    }

    file.close();
    return students;
}

// Save student records to file
void saveStudents(vector<Student> students)
{
    ofstream file("students.txt");

    for (int i = 0; i < students.size(); i++)
    {
        file << students[i].rollNo << "|"
             << students[i].name << "|"
             << students[i].age << "|"
             << students[i].course << endl;
    }

    file.close();
}

// Add student
void addStudent()
{
    vector<Student> students = loadStudents();

    Student s;

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].rollNo == s.rollNo)
        {
            cout << "Roll Number already exists!\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Course: ";
    getline(cin, s.course);

    students.push_back(s);

    saveStudents(students);

    cout << "\nStudent Added Successfully!\n";
}

// Display students
void displayStudents()
{
    vector<Student> students = loadStudents();

    if (students.empty())
    {
        cout << "\nNo Student Records Found!\n";
        return;
    }

    cout << "\n========== STUDENT RECORDS ==========\n";

    for (int i = 0; i < students.size(); i++)
    {
        cout << "\nRoll Number : " << students[i].rollNo;
        cout << "\nName        : " << students[i].name;
        cout << "\nAge         : " << students[i].age;
        cout << "\nCourse      : " << students[i].course;
        cout << "\n-------------------------------------\n";
    }
}

// Update student
void updateStudent()
{
    vector<Student> students = loadStudents();

    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].rollNo == roll)
        {
            cout << "Enter New Name: ";
            getline(cin, students[i].name);

            cout << "Enter New Age: ";
            cin >> students[i].age;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter New Course: ";
            getline(cin, students[i].course);

            found = true;
            break;
        }
    }

    if (found)
    {
        saveStudents(students);
        cout << "\nStudent Updated Successfully!\n";
    }
    else
    {
        cout << "\nStudent Not Found!\n";
    }
}

// Delete student
void deleteStudent()
{
    vector<Student> students = loadStudents();

    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].rollNo == roll)
        {
            students.erase(students.begin() + i);
            found = true;
            break;
        }
    }

    if (found)
    {
        saveStudents(students);
        cout << "\nStudent Deleted Successfully!\n";
    }
    else
    {
        cout << "\nStudent Not Found!\n";
    }
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n     STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Update Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\n====================================";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "\nThank You for Using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 5);

    return 0;
}