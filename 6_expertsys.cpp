#include <iostream>
#include <bits/stdc++.h>
using namespace std;

string criteria[5] = {"Punctuality", "Productivity", "Teamwork", "Communication", "ProblemSolving"};
float weights[5] = {0.15, 0.30, 0.20, 0.20, 0.15};
class Employee
{
public:
    string name;
    float ratings[5];
    float finalScore;
};
void input(Employee &e)
{
    cout << "Enter employee name (no spaces): ";
    cin >> e.name;

    e.finalScore = 0;
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter rating for " << criteria[i] << " (0 to 10): ";
        cin >> e.ratings[i];

        if (e.ratings[i] < 0 || e.ratings[i] > 10)
        {
            cout << "Invalid rating. Setting to 0.\n";
            e.ratings[i] = 0;
        }
        e.finalScore += e.ratings[i] * weights[i];
    }
}
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

int main()
{
    int n;
    cout << "Enter number of employees: ";
    cin >> n;
    Employee employees[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Input details for employee " << i + 1 << ":\n";
        input(employees[i]);
    }
    cout << "\nEmployee Performance Details:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\nDetails for employee " << i + 1 << ":\n";
        display(employees[i]);
    }

    return 0;
}