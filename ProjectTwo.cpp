#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Stores all information for one course.
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Node used by the binary search tree.
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(const Course& newCourse) {
        course = newCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary search tree used to store courses by course number.
class CourseBST {
private:
    Node* root;

    // Inserts a course into the correct location in the BST.
    Node* insert(Node* node, const Course& course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        }
        else if (course.courseNumber > node->course.courseNumber) {
            node->right = insert(node->right, course);
        }
        else {
            // Replace an existing course if the same course number is loaded again.
            node->course = course;
        }

        return node;
    }

    // Searches the BST for a specific course number.
    Node* search(Node* node, const string& courseNumber) const {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }

        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }

        return search(node->right, courseNumber);
    }

    // In-order traversal prints courses from lowest to highest.
    void printInOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        printInOrder(node->left);
        cout << node->course.courseNumber << ", "
             << node->course.title << endl;
        printInOrder(node->right);
    }

    // Frees dynamically allocated tree nodes.
    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    CourseBST() {
        root = nullptr;
    }

    ~CourseBST() {
        destroy(root);
    }

    void insert(const Course& course) {
        root = insert(root, course);
    }

    const Course* findCourse(const string& courseNumber) const {
        Node* result = search(root, courseNumber);

        if (result == nullptr) {
            return nullptr;
        }

        return &(result->course);
    }

    void printCourseList() const {
        printInOrder(root);
    }
};

// Removes spaces from the beginning and end of a string.
string trim(const string& value) {
    size_t start = value.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

// Converts a course number to uppercase so searches are not case-sensitive.
string toUpper(string value) {
    transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) { return static_cast<char>(toupper(c)); });

    return value;
}

// Splits one CSV line into individual fields.
vector<string> splitCSVLine(const string& line) {
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, ',')) {
        fields.push_back(trim(field));
    }

    return fields;
}

// Loads course data from the requested file into the BST.
bool loadCourses(const string& fileName, CourseBST& courses) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file \"" << fileName << "\"." << endl;
        return false;
    }

    string line;
    int lineNumber = 0;
    int courseCount = 0;

    while (getline(inputFile, line)) {
        ++lineNumber;

        if (trim(line).empty()) {
            continue;
        }

        vector<string> fields = splitCSVLine(line);

        // A valid course line must contain at least a course number and title.
        if (fields.size() < 2 || fields[0].empty() || fields[1].empty()) {
            cout << "Formatting error on line " << lineNumber
                 << ": course number and title are required." << endl;
            continue;
        }

        Course course;
        course.courseNumber = toUpper(fields[0]);
        course.title = fields[1];

        for (size_t i = 2; i < fields.size(); ++i) {
            if (!fields[i].empty()) {
                course.prerequisites.push_back(toUpper(fields[i]));
            }
        }

        courses.insert(course);
        ++courseCount;
    }

    inputFile.close();

    if (courseCount == 0) {
        cout << "Error: No valid course data was loaded." << endl;
        return false;
    }

    cout << courseCount << " courses loaded successfully." << endl;
    return true;
}

// Prints one course and the course number/title of each prerequisite.
void printCourseInformation(const CourseBST& courses, const string& requestedNumber) {
    string courseNumber = toUpper(trim(requestedNumber));
    const Course* course = courses.findCourse(courseNumber);

    if (course == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << endl;
    cout << course->courseNumber << ", " << course->title << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites:" << endl;

    for (const string& prerequisiteNumber : course->prerequisites) {
        const Course* prerequisite = courses.findCourse(prerequisiteNumber);

        if (prerequisite != nullptr) {
            cout << prerequisite->courseNumber << ", "
                 << prerequisite->title << endl;
        }
        else {
            // The number is still displayed if a prerequisite is missing from the file.
            cout << prerequisiteNumber
                 << " (course title not found in loaded data)" << endl;
        }
    }
}

// Displays the required menu.
void displayMenu() {
    cout << endl;
    cout << "ABCU Advising Assistance Program" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    CourseBST courses;
    bool dataLoaded = false;
    int choice = 0;

    while (choice != 9) {
        displayMenu();

        // Validate menu input so non-numeric entries do not break the program.
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid option. Please enter 1, 2, 3, or 9." << endl;
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            string fileName;

            cout << "Enter the course data file name: ";
            getline(cin, fileName);

            if (trim(fileName).empty()) {
                cout << "Error: A file name is required." << endl;
                dataLoaded = false;
            }
            else {
                dataLoaded = loadCourses(trim(fileName), courses);
            }
            break;
        }

        case 2:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                cout << endl;
                cout << "Here is a sample schedule:" << endl;
                courses.printCourseList();
            }
            break;

        case 3:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            }
            else {
                string courseNumber;

                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);

                if (trim(courseNumber).empty()) {
                    cout << "Error: A course number is required." << endl;
                }
                else {
                    printCourseInformation(courses, courseNumber);
                }
            }
            break;

        case 9:
            cout << "Thank you for using the ABCU Advising Assistance Program." << endl;
            break;

        default:
            cout << "Invalid option. Please enter 1, 2, 3, or 9." << endl;
            break;
        }
    }

    return 0;
}
