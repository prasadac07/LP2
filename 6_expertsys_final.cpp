#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Original criteria and their weights
string criteria[5] = {"Punctuality", "Productivity", "Teamwork", "Communication", "ProblemSolving"};
float weights[5] = {0.15, 0.30, 0.20, 0.20, 0.15}; 

class Employee
{
public:
    string name;
    float ratings[5];
    float finalScore;

    Employee()
    {
        finalScore = 0;
    }
};

// Suggest improvements based on the lowest performing area
void suggestImprovement(Employee &e)
{
    int minIndex = 0;
    for (int i = 1; i < 5; i++)
    {
        if (e.ratings[i] < e.ratings[minIndex])
        {
            minIndex = i;
        }
    }
    cout << "Suggestion for improvement: " << criteria[minIndex] << ". Focus on improving this area.\n";
}

// Input employee data with enhanced validation
void input(Employee &e)
{
    cout << "Enter employee name (no spaces): ";
    cin >> e.name;

    e.finalScore = 0;

    for (int i = 0; i < 5; i++)
    {
        cout << "Enter rating for " << criteria[i] << " (0 to 10): ";
        cin >> e.ratings[i];

        while (e.ratings[i] < 0 || e.ratings[i] > 10) // Input validation for ratings
        {
            cout << "Invalid rating. Please enter a value between 0 and 10: ";
            cin >> e.ratings[i];
        }

        e.finalScore += e.ratings[i] * weights[i];
    }
}

// Classification based on score
string classifyPerformance(float score)
{
    if (score >= 9.0)
        return "Outstanding";
    else if (score >= 8.0)
        return "Excellent";
    else if (score >= 7.0)
        return "Very Good";
    else if (score >= 6.0)
        return "Good";
    else if (score >= 5.0)
        return "Average";
    else
        return "Needs Improvement";
}

// Display employee performance details
void display(Employee &e)
{
    cout << "Employee: " << e.name << endl;
    cout << "Ratings: ";
    for (int i = 0; i < 5; i++)
    {
        cout << criteria[i] << ": " << e.ratings[i] << " ";
    }
    cout << endl;
    cout << "Final Score: " << e.finalScore << endl;
    cout << "Performance Category: " << classifyPerformance(e.finalScore) << endl;
}

// Employee Comparison based on final score
void compareEmployees(Employee &e1, Employee &e2)
{
    cout << "Comparison of " << e1.name << " and " << e2.name << ":\n";
    cout << e1.name << " Final Score: " << e1.finalScore << " - " << classifyPerformance(e1.finalScore) << endl;
    cout << e2.name << " Final Score: " << e2.finalScore << " - " << classifyPerformance(e2.finalScore) << endl;

    if (e1.finalScore > e2.finalScore)
    {
        cout << e1.name << " performs better.\n";
        cout << e2.name << " needs improvement in certain areas.\n";
        suggestImprovement(e2);
    }
    else if (e1.finalScore < e2.finalScore)
    {
        cout << e2.name << " performs better.\n";
        cout << e1.name << " needs improvement in certain areas.\n";
        suggestImprovement(e1);
    }
    else
    {
        cout << "Both employees have equal performance.\n";
    }
}

// Top and low performers
void displayTopAndLowPerformers(Employee employees[], int n)
{
    Employee topPerformer = employees[0];
    Employee lowPerformer = employees[0];

    for (int i = 1; i < n; i++)
    {
        if (employees[i].finalScore > topPerformer.finalScore)
            topPerformer = employees[i];

        if (employees[i].finalScore < lowPerformer.finalScore)
            lowPerformer = employees[i];
    }

    cout << "\nTop Performer: " << topPerformer.name << " with Final Score: " << topPerformer.finalScore << " - " << classifyPerformance(topPerformer.finalScore) << endl;
    cout << "Low Performer: " << lowPerformer.name << " with Final Score: " << lowPerformer.finalScore << " - " << classifyPerformance(lowPerformer.finalScore) << endl;
}

// Main Function
int main()
{
    int n;
    cout << "Enter number of employees: ";
    cin >> n;

    Employee employees[n];
    
    // Input employee details and record their performance
    for (int i = 0; i < n; i++)
    {
        cout << "Input details for employee " << i + 1 << ":\n";
        input(employees[i]);
    }
    
    // Displaying employee performance details
    cout << "\nEmployee Performance Details:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nDetails for employee " << i + 1 << ":\n";
        display(employees[i]);
    }

    // Display Top and Low Performers
    displayTopAndLowPerformers(employees, n);

    // Comparing two employees based on their final scores
    int emp1, emp2;
    cout << "\nEnter employee numbers (1 to " << n << ") to compare: ";
    cin >> emp1 >> emp2;
    compareEmployees(employees[emp1 - 1], employees[emp2 - 1]);

    return 0;
}
