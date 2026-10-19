# CS-300 Data Structures and Algorithms

## Course Overview

Throughout CS-300, I learned how different data structures and algorithms affect the efficiency and performance of software. For Project One, I analyzed vectors, hash tables, and binary search trees to determine which structure would work best for a college advising application. For Project Two, I developed a C++ program that loads course information, displays courses in alphanumeric order, and allows users to search for individual courses and their prerequisites.

## What was the problem you were solving in the projects for this course?

The goal of these projects was to develop an advising assistance program for ABCU that would help academic advisors access course information. The program needed to read course data from a file, display a complete list of courses in alphanumeric order, and allow users to search for a specific course and view its prerequisites. In Project One, I evaluated different data structures to determine which would be the most efficient for these tasks. In Project Two, I implemented the program using C++ and a binary search tree.

## How did you approach the problem? Consider why data structures are important to understand.

I started by reviewing the program requirements and breaking them into smaller tasks. I compared vectors, hash tables, and binary search trees by analyzing their run-time performance, memory requirements, and ability to organize course information. Each structure had advantages and disadvantages. Vectors were simple to use but required additional sorting and linear searches. Hash tables provided efficient average lookup times but did not maintain courses in order. I selected a binary search tree because an in-order traversal could display the courses alphabetically by course number without requiring a separate sorting operation. This project helped me understand that choosing the right data structure can significantly affect how efficiently a program operates.

## How did you overcome any roadblocks you encountered while going through the activities or project?

One challenge was understanding how the different data structures affected program performance and deciding which one would best meet the requirements. Breaking down the pseudocode and comparing the run-time complexity of each approach helped me make that decision. When developing Project Two, I also had to consider how the program would handle invalid input, missing files, and incorrectly formatted course information. I approached these challenges by separating the program into smaller functions, checking input before processing it, and including error messages to help users understand what went wrong. Working through these problems helped me become more comfortable troubleshooting and thinking through different scenarios before assuming the program would work correctly.

## How has your work on this project expanded your approach to designing software and developing programs?

This project helped me realize how important it is to think about the organization of data before writing the actual code. In the past, I might have focused primarily on getting a program to perform the required functions. Now, I understand that the data structure and algorithms I choose can affect performance, scalability, and how easily the application can be maintained. Comparing different approaches before implementing the program helped me make a more informed design decision. I also learned the importance of considering both the user's needs and the technical requirements when developing a software solution.

## How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

Working on these projects reinforced the importance of organizing code into smaller functions and using meaningful names and comments. In Project Two, I separated tasks such as loading course data, searching for a course, printing the course list, and displaying the menu. This made the program easier to follow and would allow individual functions to be updated without rewriting the entire application. I also included input validation and error handling to make the program more reliable. Moving forward, I plan to continue writing organized, readable code while considering how future changes could affect the program. I believe these practices will help me develop software that is easier to maintain, troubleshoot, and expand.
