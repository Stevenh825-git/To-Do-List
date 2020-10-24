//Steven Hernandez
//Project 2
//Task: Create a basic file editor


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<ctype.h>
using namespace std;

void To_Do_List(string file_name);


//reads the file chosen, and prints its contents
void Show_file(string file){
	ifstream myfile(file);
	string line;
	while(getline(myfile,line))
	{
		cout << line << endl;
	}

	myfile.close();
}



//adds the appropriate strings to the vector.  These are the first two choices people will pick from at the start of the program.
void set_startup_options(vector<string> & option){
	option.push_back("Edit"); //fills the vector
	option.push_back("View");
	option.push_back("Quit");
}

//displays the options people can choose from at the start of  the program.
void show_startup_options(vector<string> option){

	for(int i = 0;i < option.size(); i ++){
		cout << i << " \"" <<option[i] << "\""<< endl;
	} //displays the elements
}


void from_scratch(string file_name)
{
	ofstream To_Do (file_name, ios::out | ios::trunc);

	To_Do <<"\t" << "To-Do List" << endl;

	To_Do << "-------------------------------" << endl;

	cout <<"To Quit: Enter Q" << endl << endl;

	while(1){
		string line;
		getline(cin,line);

		if(line =="Q" | line =="q"){
			break;
		}
		else if(line != ""){
			To_Do << "\t" << "-"<< line << endl;
		}
	}
	To_Do.close();
}

//allows users to expand the file
void continue_file(string file_name)
{
	ofstream To_Do (file_name, ios::out | ios::app);


	cout <<"To Quit: Enter Q" << endl << endl;


	while(1){
		string line;
		getline(cin,line);

		if(line =="Q" || line =="q"){
			break;
		}
		else if(line != ""){
			To_Do << "\t" << "-"<< line << endl;
		}
	}
	To_Do.close();
}


//this function stores all the lines of a file into elements of a vector
vector<string> file_into_vector(ifstream & myfile){
	vector<string> file_lines;
	string line;

	while(getline(myfile,line)) //while it goes through each line
	{
		file_lines.push_back(line); //add an element to the element
	}
	return file_lines; //return the vector
}



//shows all the elements of the vector storing the files lines
void display_lines(vector<string> file_lines)
{
	cout << endl;
	for(int i = 0; i < file_lines.size(); i++)
	{
		cout << i << file_lines[i] << endl;
	}
}



//puts all the lines into the file, including any oens that have or have not been updated
void updated_file(vector<string> file_vector, string file_name)
{
	ofstream To_Do (file_name, ios::out | ios::trunc); //trunc removes all lines
	for(int i = 0;i < file_vector.size(); i ++)
	{
			To_Do << file_vector[i] << endl; //adds all the lines back into the file in a for loop
	}
}

//the To-Do List's lines can be edited here
void edit_file(string file_name)
{
		ifstream myfile(file_name);
		//This uses the file name, so it can be accessible through myfile

		vector<string> file_vector = file_into_vector(myfile); //store the file's lines into a vector

		if(file_vector.size() != 0){ //if statement is to make sure there are even lines to edit at all in the file

			display_lines(file_vector); //shows the lines

			int line_number;
			string new_line;

			while(1){
				cout << "Which line will you like to edit?" << endl;
				cin >> line_number;


				//make sure the user inputs a valid line number
				while(cin.fail() || (line_number < 0 || line_number >= file_vector.size())){
					cin.clear();
					cin.ignore(100000,'\n');

					cout << endl;

					display_lines(file_vector);
					cout << "Line doesn't exist. Enter the appropriate line number." << endl << endl;

					cin >> line_number;
				}


				cout << "Write the new line. Or enter Q to quit" << endl;

				cin.clear();
				cin.ignore();

				getline(cin,new_line);

				if(new_line == "Q" || new_line == "q"){
					break;
				}
				//if(new_line != ""){
				else{
					new_line = "\t-" + new_line;
					file_vector[line_number] = new_line; //adds the new line to the vector
					updated_file(file_vector,file_name); //stores the updated line
					display_lines(file_vector); //shows the new file

				}
			}
		}
		else{
			cout << "There are no lines to edit." << endl << endl;
			cin.ignore(100000, '\n');
		}
			myfile.close();
}


//asks the user if they want to keep tinkering with the file, if so it will run the To-Do List function again

void keep_going(string file_name){
	cout << "Would you like to make any more changes? If so, enter Y. Capitalization doesn't matter. Otherwise enter any other character." << endl;
	string final_decision = "";
	getline(cin,final_decision);

	if(final_decision == "y" | final_decision == "Y")
	{
		To_Do_List(file_name);

	}
}

//Sets the name for the file. Stores whatever the user inputs into the variable passed by reference.

void set_file_name(string & file_name)
{
	cout << "Would you like to name your own file, or use the default name: To-Do List?" << endl;

	cout << "Enter 1 for your own file name, or 2 for default" << endl;

	int choice;
	cin >> choice;

	//make sure input is correct
	while(cin.fail() or (choice > 2 || choice < 1)){
		cin.clear();
		cin.ignore(100000, '\n');

		cout << endl << "Error. Try again." << endl;

		cout << "Enter 1 for your own file name, 2 for default." << endl;

		cin >> choice;
	}


	switch(choice){
	case(1):
		cout << "Enter the file name: " << endl;

		cin.ignore();
		getline(cin,file_name);

		//The user inputs the file and it is stored in the variable.
		break;
	case(2):
		file_name = "To-Do List"; //If they chose to use the default name.
		break;
	}
}

//creates an output file, called To-Do list. The user can add whatever they want to the file.
void To_Do_List(string file_name)
{



	cout << "Would you like to edit, add, or start from scratch?" << endl << endl;
	cout << "Enter 1 to edit, 2 to add, 3 from scratch, or 4 to quit." << endl;

	int decision;
	cin >> decision;

	//loop to make sure the input is correct
	while(cin.fail() or (decision > 4 || decision < 1)){
		cin.clear();
		cin.ignore(100000, '\n');

		cout << "Error. Try again." << endl;

		cout << "Enter 1 to edit, 2 to add, 3 from scratch, or 4 to quit." << endl;

		cin >> decision;
	}


	switch(decision){
	case(1): //edit
			edit_file(file_name);
			keep_going(file_name);


			break;
	case(2): //continue
			continue_file(file_name);

			cout << "This is the current file: " << endl;
			Show_file(file_name);
			cout << endl << endl;
			keep_going(file_name);
			break;
	case(3)://start from scratch
			from_scratch(file_name);
			cout << "This is the current file: " << endl;
			Show_file(file_name);
			cout << endl << endl;
			keep_going(file_name);
			break;
	case(4):
			break;
	}

}





int main(){
	cout << "Welcome. You can choose to view or edit a To-Do List text file. Here are your options: " << endl;



	vector <string> choices;
	//creates a vector that will be filled with the user's options
	set_startup_options(choices);
	show_startup_options(choices);
	//calls a function that will fill the vector and display its elements.

	int option;
	cin >> option;

	while(cin.fail() or (option > 2 || option < 0)){
		cin.clear();
		cin.ignore(100000, '\n');

		cout << "Error. Try again." << endl;

		show_startup_options(choices);

		cin >> option;
	}

	string file_name; //file's name

	switch(option){
	case(0):
	//	cout << "Chosen 0." << endl << endl;


		set_file_name(file_name); //sets the appropriate name for the file

		To_Do_List(file_name); //call the function to start working on the document

		break;
	case(1):
		set_file_name(file_name); //ask for the file name
		Show_file(file_name); //show the file
		keep_going(file_name); //ask if there is anything else they wish to do
		break;
	case(2):
		break;
	}

	return 0;
}
