#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student
{
private:
  int rollNumber;
  string name;
  int classLevel;
  float marks;

public:
  Student() {}
  Student(int roll, string n, int cl, float m) : rollNumber(roll), name(n), classLevel(cl), marks(m) {}

  void setData()
  {
    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cin.ignore(); // To ignore the newline character from previous input
    cout << "Enter class level: ";
    cin >> classLevel;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Marks: ";
    cin >> marks;
  }

  void showData() const
  {
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Class Level: " << classLevel << endl;
    cout << "Marks: " << marks << endl;
  }

  int getRollNumber() const
  {
    return rollNumber;
  }

  string getName() const
  {
    return name;
  }

  int getClassLevel() const
  {
    return classLevel;
  }

  float getMarks() const
  {
    return marks;
  }
};

// Function declarations
void addStudent();
void displayAllStudents();
void searchStudent(int roll, int cl);
void deleteStudent(int roll, int cl);

const string FILE_NAME = "students.dat";

int main()
{
  int choice;
  do
  {
    cout << "\n*** Student Management System ***\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Roll Number and classLevel \n";
    cout << "4. Delete Student by Roll Number and classLevel \n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      addStudent();
      break;
    case 2:
      displayAllStudents();
      break;
    case 3:
    {
      int roll;
      cout << "Enter Roll Number to search: ";
      cin >> roll;
      cin.ignore();
      int cl;
      cout << "Enter Class Level of the student: ";
      cin >> cl;
      cin.ignore();
      searchStudent(roll, cl);
      break;
    }
    case 4:
    {
      int roll;
      cout << "Enter Roll Number to delete: ";
      cin >> roll;
      cin.ignore();
      int cl;
      cout << "Enter Class Level of the student: ";
      cin >> roll;
      cin.ignore();
      deleteStudent(roll, cl);
      break;
    }
    case 5:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice! Please try again.\n";
    }
  } while (choice != 5);

  return 0;
}

void addStudent()
{
  Student student;
  student.setData();

  ofstream outFile;
  outFile.open(FILE_NAME, ios::binary | ios::app);
  outFile.write(reinterpret_cast<char *>(&student), sizeof(Student));
  outFile.close();

  cout << "Student record added successfully.\n";
}

void displayAllStudents()
{
  Student student;

  ifstream inFile;
  inFile.open(FILE_NAME, ios::binary);
  if (!inFile)
  {
    cout << "File could not be opened! Press any key...\n";
    cin.ignore();
    cin.get();
    return;
  }

  cout << "\n*** Display All Students ***\n";
  while (inFile.read(reinterpret_cast<char *>(&student), sizeof(Student)))
  {
    student.showData();
    cout << "---------------------\n";
  }
  inFile.close();
}

void searchStudent(int roll, int cl)
{
  Student student;
  bool found = false;

  ifstream inFile;
  inFile.open(FILE_NAME, ios::binary);
  if (!inFile)
  {
    cout << "File could not be opened! Press any key...\n";
    cin.ignore();
    cin.get();
    return;
  }

  while (inFile.read(reinterpret_cast<char *>(&student), sizeof(Student)))
  {
    if (student.getRollNumber() == roll && student.getClassLevel() == cl)
    {
      cout << "\nStudent found:\n";
      student.showData();
      found = true;
      break;
    }
  }
  inFile.close();

  if (!found)
    cout << "Student with Roll Number " << roll << " not found.\n";
}

void deleteStudent(int roll, int cl)
{
  Student student;
  ifstream inFile;
  inFile.open(FILE_NAME, ios::binary);
  if (!inFile)
  {
    cout << "File could not be opened! Press any key...\n";
    cin.ignore();
    cin.get();
    return;
  }

  ofstream outFile;
  outFile.open("Temp.dat", ios::binary);
  while (inFile.read(reinterpret_cast<char *>(&student), sizeof(Student)))
  {
    if (student.getRollNumber() != roll && student.getClassLevel() != cl)
    {
      outFile.write(reinterpret_cast<char *>(&student), sizeof(Student));
    }
  }
  inFile.close();
  outFile.close();

  remove(FILE_NAME.c_str());
  rename("Temp.dat", FILE_NAME.c_str());

  cout << "Student record deleted successfully.\n";
}