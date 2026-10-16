# Smart Resource Allocation Using Banker's Algorithm

## 1. Abstract
This project implements a resource allocation manager using
Banker's Algorithm. It checks whether resource requests can
be granted without making the system unsafe.

## 2. Problem Statement
Improper allocation of limited resources can lead to deadlocks.
A safe resource allocation strategy is required.

## 3. Objectives
- Calculate the Need matrix.
- Identify safe and unsafe states.
- Find a safe execution sequence.
- Validate resource requests.
- Reject requests that would make the state unsafe.

## 4. Technologies Used
- Operating System: Ubuntu Linux
- Programming Language: C
- Compiler: GCC
- Build Tool: Make
- Version Control: Git and GitHub

## 5. Methodology
The program maintains Available, Allocation, Maximum,
and Need data structures.

The safety algorithm determines whether all processes can
finish. Resource requests are temporarily applied and granted
only if the resulting state remains safe.

## 6. Expected Outcome
The application displays resource matrices, detects safe
states, prints safe sequences, and validates resource requests.

## 7. Conclusion
The project demonstrates how Banker's Algorithm helps
avoid unsafe resource allocation and prevent deadlocks.

## 8. Limitation
This is an educational simulator. It does not control actual
resource allocation performed by the Linux kernel.
