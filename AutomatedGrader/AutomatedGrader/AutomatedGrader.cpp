
// Automated Grader 
#include "pch.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


//function prototypes
void print_header();
void print_footer(double average);
void print_student(const std::string &student, int score);
int process_response(const std::string &response, const std::string &answer_key);

//this function print the header of the output
void print_header() {
	std::cout << std::setw(15) << std::left << "Student"
		<< std::setw(5) << "Score" << std::endl;
	std::cout << std::setw(20) << std::setfill('-') << "" << std::endl;
	std::cout << std::setfill(' ');
}

//this function print the footer of the output
void print_footer(double average) {
	std::cout << std::setw(20) << std::setfill('-') << "" << std::endl;
	std::cout << std::setfill(' ');
	std::cout << std::setw(15) << std::left << "Average score"
		<< std::setw(5) << std::right << average;
}

//print student name in the left and the score in the right side
void print_student(const std::string &student, int score) {
	std::cout << std::setprecision(1) << std::fixed;
	std::cout << std::setw(15) << std::left << student
		<< std::setw(5) << std::right << score << std::endl;
}

// return the number of correct responses
int process_response(const std::string &response, const std::string &answer_key) {
	int score{ 0 };
	for (size_t i = 0; i < answer_key.size(); ++i) {
		if (response.at(i) == answer_key.at(i))
			score++;
	}
	return score;
}

int main() {
	std::ifstream in_file;
	std::string answer_key{};
	std::string name{};
	std::string response{};
	int running_sum{ 0 };
	int total_students{ 0 };
	double average_score{ 0.0 };

	in_file.open("responses.txt");
	if (!in_file) {
		std::cerr << "Problem opening file" << std::endl;
		return 1;
	}

	//scan first line of responses.txt file which is answer-key
	in_file >> answer_key;

	//output the header
	print_header();

	//use while loop to read the name of student and their answer respectely
	while (in_file >> name >> response) {
		++total_students;
		int score = process_response(response, answer_key);
		running_sum += score;
		print_student(name, score);
	}

	//avoid divsion of O
	if (total_students != 0)
		average_score = static_cast<double>(running_sum) / total_students;

	print_footer(average_score);

	in_file.close();
	std::cout << std::endl << std::endl;
	return 0;
}

