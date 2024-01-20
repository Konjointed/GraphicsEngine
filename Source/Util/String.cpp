#include "String.h"

bool contains(const std::string& s1, const std::string& s2)
{
	return s1.find(s2) != std::string::npos;
}

bool startsWith(const std::string& s1, const std::string& s2) {
	return s1.compare(0, s2.length(), s2) == 0;
}

bool endsWith(const std::string& s1, const std::string& s2) {
    if (s1.length() >= s2.length()) {
        return s1.compare(s1.length() - s2.length(), s2.length(), s2) == 0;
    }
    else {
        return false;
    }
}

void capitalize(std::string& s) {
    if (!s.empty()) {
        s[0] = toupper(s[0]);
    }
    for (size_t i = 1; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
    }
}

int count(const std::string& s1, const std::string& s2) {
    int count = 0;
    size_t pos = s1.find(s2);
    while (pos != std::string::npos) {
        ++count;
        pos = s1.find(s2, pos + s2.length());
    }
    return count;
}

int find(const std::string& s, char val) {
    size_t pos = s.find(val);
    return (pos != std::string::npos) ? static_cast<int>(pos) : -1;
}

int find(const std::string& s1, const std::string& s2) {
    size_t pos = s1.find(s2);
    return (pos != std::string::npos) ? static_cast<int>(pos) : -1;
}

void lower(std::string& s) {
	for (size_t i = 0; i < s.length(); ++i) {
		s[i] = tolower(s[i]);
	}
}

void upper(std::string& s) {
	for (size_t i = 0; i < s.length(); ++i) {
		s[i] = toupper(s[i]);
	}
}