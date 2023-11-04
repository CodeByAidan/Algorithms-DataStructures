#include <cstring>
#include <iostream>

class charstring {
public:
	explicit charstring(const char* str) {
        size_t len = strlen(str) + 1;
        data = new char[len];
        strcpy_s(data, len, str);
    }

    charstring(const charstring& other) {
        size_t len = strlen(other.data) + 1;
        data = new char[len];
        strcpy_s(data, len, other.data);
    }

    ~charstring() {
        delete[] data;
    }

    charstring& operator=(const charstring& other) {
        if (this != &other) {
            size_t len = strlen(other.data) + 1;
	        auto* temp = new char[len];
            strcpy_s(temp, len, other.data);
            delete[] data;
            data = temp;
        }
        return *this;
    }

	charstring operator+(const charstring& other) const {
		size_t len = strlen(data) + strlen(other.data) + 1;
		auto* temp = new char[len];
		strcpy_s(temp, len, data);
		strcat_s(temp, len, other.data);
		return charstring(temp);
	}

    friend std::ostream& operator<<(std::ostream& os, const charstring& str);

private:
    char* data;
};

std::ostream& operator<<(std::ostream& os, const charstring& str) {
    os << str.data;
    return os;
}