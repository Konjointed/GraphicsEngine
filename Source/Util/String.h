#pragma once

#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <vector>

// https://medium.com/theleanprogrammer/creating-custom-utility-header-files-in-c-b72a05fa05ef
bool contains(const std::string& s1, const std::string& s2);
bool startsWith(const std::string& s1, const std::string& s2);
bool endsWith(const std::string& s1, const std::string& s2);
void capitalize(std::string& s);
int count(const std::string& s1, const std::string& s2);
int find(const std::string& s, char val);
int find(const std::string& s1, const std::string& s2);
//int findLastOccurence(string s, char val);
//int findLastOccurence(string s, string val);
//bool isalnum(string s);
//bool isalpha(string s);
//bool isdigit(string s);
//bool islower(string s);
//bool isupper(string s);
//bool istitle(string s);
void lower(const std::string& s);
void upper(const std::string& s);
//vector<string> split(string s, char c = ' ');
//void swapcase(string& s);
//void title(string& s);
//void replace(string& s, char c, char k);
//void replace(string& s, string c, string k);