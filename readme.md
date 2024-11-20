# Student Management System (SMS)

## Introduction

The **Student Management System (SMS)** is a console-based application designed to securely manage student records. It incorporates a basic authentication system to ensure that only authorized users can access and manipulate student data. This system demonstrates core programming concepts such as data structures, user authentication, and CRUD (Create, Read, Update, Delete) operations in **C programming**.

## Objectives

The primary objectives of this project are:
1. To develop a secure and efficient system for managing student data.
2. To integrate login functionality to restrict unauthorized access.
3. To provide a practical demonstration of programming principles in a structured manner.
4. To enable CRUD operations for student records via a simple user interface.
5. To use a `.csv` file as the database for persistent data storage.

## Scope

The system will offer the following functionalities:

1. **Login Authentication**: Users must enter valid credentials to access the system. Three login attempts are allowed before the program terminates.
2. **Add Student**: Users can add a student's roll number, name, and age to the database.
3. **Delete Student**: Users can remove a student record by searching with the roll number.
4. **View All Students**: Users can view a formatted list of all students.
5. **Add Course**: Users can add, delete, view, and update a student’s courses.
6. **Logout and Exit**: Allows users to log out securely and exit the program.

## Functional Requirements

1. **User Authentication**: The system requires valid credentials (default username/password) to log in.
2. **Data Management**: The system allows for dynamic addition and deletion of up to 100 student records.
3. **Error Handling**: Invalid inputs, nonexistent roll numbers, or login failures are handled gracefully.
4. **User Interface**: The program uses a simple, menu-driven console interface for navigation.

## System Design

**Programming Language**: C

### Key Modules:

1. **Login System**: Ensures only authenticated users can access the system.
2. **CRUD Operations**:
   - **Create** (Add student record)
   - **Read** (View all student records)
   - **Update** (Modify records if needed in future enhancements)
   - **Delete** (Remove student records)
3. **Exit Functionality**: Terminates the program safely.
4. **In-memory Array**: Stores student details temporarily.

## Implementation Details

The system is divided into the following modules:

### 1. Login Module
- Users enter predefined credentials (default: `user`/`pass`).
- The system allows a maximum of three login attempts before terminating.

### 2. Main Menu Module
- Displays options for adding, deleting, or viewing student data.
- The user selects options by entering corresponding numbers.

### 3. Student Module
- Uses a structure to store student data (roll number, name, age).

### 4. Data Manipulation Functions:
- **Add Student**: Appends a new student record to the system.
- **Delete Student**: Searches by roll number and deletes the matching record.
- **View All Students**: Displays all student records in a tabular format.

## Advantages

1. **Security**: Protects the system with a login mechanism.
2. **Simplicity**: Provides a straightforward interface for managing student records.
3. **Educational Value**: Demonstrates practical applications of structures, arrays, and basic authentication in C programming.
4. **Error Handling**: Includes user-friendly messages for invalid inputs or operations.

## Future Enhancements

1. **Persistent Storage**:
   - Save records to a file for reuse between sessions.
   - Load records at program startup.

2. **Dynamic Credential Management**:
   - Allow the admin to change the username and password dynamically.

3. **User Roles**:
   - Introduce multiple user roles (e.g., admin, guest) with varying access levels.

4. **Enhanced Features**:
   - Add sorting and searching capabilities.
   - Expand the system size with dynamic memory allocation.

5. **GUI Implementation**:
   - Develop a graphical user interface (GUI) for enhanced usability.

## Conclusion

This project combines secure access control with essential functionalities, offering a practical solution for managing student records. It serves as a learning platform for understanding programming concepts such as user authentication, data structures, and CRUD operations. With its modular design, the system can be further extended to support advanced features like persistent storage and role-based access control.

## Estimated Timeline

- **Development**: 1 week
- **Testing and Debugging**: 2 days

## Required Resources

- **Tools**: CodeBlocks Software (GCC Compiler)
- **Hardware**: Any machine capable of running a C program

## Proposed by

Md. Asraful Islam
