#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const string MAIN_MENU_TEXT = "Press 1 to add a to-do item\nPress 2 to remove a to-do item\nPress 3 to show your to-do list\nPress 4 to clear the to-do list\nPress 5 to exit the app";

const string ADD_TODO_ITEM_TEXT = "Type name for to-do item: ";
const string REMOVE_TODO_ITEM_TEXT = "Type name to remove to-do item: ";
const string CLEAR_TODO_LIST_TEXT = "To-do list has been cleared.";
const string SHOW_TODO_LIST_TEXT = "To-do list is as follows: ";

const string MAX_ITEMS_REACHED_TEXT = "You have reached the max items, remove or clear to-do items to add another.";
const string DUPLICATE_ENTRY_TEXT = "You already have this to-do list entry.";
const string NO_MATCHING_ENTRY_TEXT = "Could not find a to-do list with the name: ";
const string RETURN_TO_MAIN_MENU_TEXT = "Press enter to return to the main menu.";

const string OUTPUT_FILE_NAME = "ToDoList.txt";
const string TEMP_FILE_NAME = "temp.txt";

const int MAX_TODO_ITEMS = 10;

vector<string> todoItems;

void ReturnToMainMenuPrompt(){
    cout << RETURN_TO_MAIN_MENU_TEXT << endl;
    cin.get();
}

void ShowDuplicateError(){
    cout << DUPLICATE_ENTRY_TEXT << endl;
    ReturnToMainMenuPrompt();
}

void ShowTooManyItemsError(){
    cout << MAX_ITEMS_REACHED_TEXT << endl;
    ReturnToMainMenuPrompt();
}

void GetToDoList(){
    todoItems.clear();

    ifstream inputFile(OUTPUT_FILE_NAME.c_str());

    string line;

    while(getline(inputFile, line)){
        todoItems.push_back(line);
    }
    
    inputFile.close();
}

void ShowToDoList(){
    GetToDoList();

    int index = 0;

    cout << SHOW_TODO_LIST_TEXT << endl;
    for(string item : todoItems){
        index++;
        cout << index << ": " << item << endl;
    }

    ReturnToMainMenuPrompt();
}

string ShowMainMenu(){
    string answer;

    cout << MAIN_MENU_TEXT << endl;

    getline(cin, answer);

    return answer;
}

bool IsThereDuplicateItem(string toDoItem){
    for (string items : todoItems){
        if (items == toDoItem) return true;
    }

    return false;
}

void AddToDoItem(){
    if (todoItems.size() - 1 == MAX_TODO_ITEMS){
        ShowTooManyItemsError();
        return;
    }

    string toDoItem;

    cout << ADD_TODO_ITEM_TEXT << endl;
    getline(cin, toDoItem);

    if(IsThereDuplicateItem(toDoItem)) {
        ShowDuplicateError();
        return;
    }

    todoItems.push_back(toDoItem);

    ofstream outputFile;
    outputFile.open(OUTPUT_FILE_NAME.c_str(), ios::app);
    outputFile << toDoItem.c_str() << "\n";
    outputFile.close();

    ShowToDoList();
}

void ClearToDoList(){
    todoItems.clear();

    ofstream outputFile;
    outputFile.open(OUTPUT_FILE_NAME.c_str());
    outputFile.clear();
    outputFile.close();

    cout << CLEAR_TODO_LIST_TEXT << endl;
    ReturnToMainMenuPrompt();
}

void RemoveToDoItem(){
    int index = 0;
    string itemToRemove;
    cout << REMOVE_TODO_ITEM_TEXT << endl;

    getline(cin, itemToRemove);

        for (string item : todoItems){
        index++;

        if (item == itemToRemove){
            todoItems.erase(todoItems.begin() + index);

            cout << "Removed " << itemToRemove << " Successfully." << endl;
            break;
        }
    }

    ifstream inputFile(OUTPUT_FILE_NAME.c_str());
    string line;

    if(!inputFile) {
        cerr << "There was an error opening the file";
        inputFile.close();
        return;
    }

    ofstream outputFile(TEMP_FILE_NAME.c_str());

    while(getline(inputFile, line)){
        if(line != itemToRemove)
        {
            outputFile << line << std::endl;
        }
    }

    outputFile.close();
    inputFile.close();

    remove(OUTPUT_FILE_NAME.c_str());

    if(rename(TEMP_FILE_NAME.c_str(), OUTPUT_FILE_NAME.c_str()) != 0){
        cerr << "Error renaming the file" << endl;
    };

    ShowToDoList();
}

int main(){
    GetToDoList();

    for(;;) {
        string answer;

        answer = ShowMainMenu();

        // Main loop for app
        if (answer == "1"){
            AddToDoItem();
        }
        else if (answer == "2"){
            RemoveToDoItem();
        }
        else if (answer == "3"){
            ShowToDoList();
        }
        else if (answer == "4"){
            ClearToDoList();
        }
        else if (answer == "5"){
            break;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }

}