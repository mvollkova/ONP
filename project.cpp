#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a < b ? b : a; }

class String {
private:
    int _size = 0;
    char* str = nullptr;

public:
    char& operator[](int index) {
        return str[index];
    }
    String() {}
    String(int size) : _size{ size } {
        str = new char[_size + 1];
        str[_size] = '\0';
    }
    String(const String& other) {
        this->_size = other._size;
        this->str = new char[_size + 1];

        for (int i = 0; i < other._size; i++)
        {
            this->str[i] = other.str[i];
        }
        this->str[this->_size] = '\0';
    }
    String(const char* other) {
        this->_size = strlen(other);
        this->str = new char[_size + 1];

        for (int i = 0; i < _size; i++)
        {
            this->str[i] = other[i];
        }
        this->str[this->_size] = '\0';
    }
    String& operator =(const String& other) {
        if (this->str != nullptr) {
            delete[] this->str;
        }

        this->_size = other._size;
        this->str = new char[_size + 1];

        for (int i = 0; i < other._size; i++)
        {
            this->str[i] = other.str[i];
        }
        this->str[this->_size] = '\0';

        return *this;
    }
    String& operator =(const char* other) {
        if (this->str != nullptr) {
            delete[] this->str;
        }
        this->_size = strlen(other);
        this->str = new char[_size + 1];

        for (int i = 0; i < _size; i++)
        {
            this->str[i] = other[i];
        }
        this->str[this->_size] = '\0';

        return *this;
    }
    int size() const { return _size; }
    bool empty()const { return _size == 0; }
    int find(char ch) const {
        for (int i = 0; i < _size; i++)
        {
            if (str[i] == ch) {
                return i;
            }
        }
        return -1;
    }
    int find(const char* other) const {
        int otherLen = strlen(other);
        for (int i = 0; i < _size; i++)
        {
            bool isExists = true;
            for (int j = 0; j < otherLen; j++)
            {
                if (str[i + j] != other[j]) {
                    isExists = false;
                    break;
                }
            }
            if (isExists) {
                return i;
            }
        }
        return -1;
    }
    String substr(int start, int count = INT_MAX) const {
        int totalCount = count < _size - start ? count : _size - start;
        String s(totalCount);
        for (int i = start; i < start + totalCount; i++)
        {
            s[i - start] = str[i];
        }
        return s;
    }
    void erase(int start, int count) {
        //String s(_size - count);
        int newSize = _size - count;
        char* newStr = new char[newSize + 1];

        int i;
        for (i = 0; i < start; i++)
        {
            newStr[i] = str[i];
        }
        for (int j = start + count; j < _size; j++, i++)
        {
            newStr[i] = str[j];
        }
        newStr[newSize] = '\0';
        if (str != nullptr) {
            delete[] str;
        }
        str = newStr;
        _size = newSize;
    }
    String* split(int& n, char separator = ' ') const {
        n = 0;
        for (int i = 0; i < _size; i++)
        {
            if (str[i] == separator) {
                n++;
            }
        }

        String* arr = new String[n];
        int tokenIndex = 0;
        String s = *this;
        while (!s.empty())
        {
            if (s[0] == '.') {
                break;
            }
            int spaceIndex = s.find(separator);

            if (spaceIndex == -1) {
                spaceIndex = n;
            }
            if (tokenIndex >= n) break;

            arr[tokenIndex++] = s.substr(0, spaceIndex);
            s.erase(0, spaceIndex + 1);
        }
        return arr;
    }

    bool isNumber()const {
        for (int i = 0; i < _size; i++)
        {
            if (isdigit(str[i]) == false) {
                return false;
            }
        }
        return true;
    }
    int toInt() { return atoi(str); }
    bool operator==(const String& other) const {
        if (_size != other._size) {
            return false;
        }
        for (int i = 0; i < _size; i++)
        {
            if (str[i] != other.str[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !((*this) == other);
    }

    String operator+(const String& other) {
        String sNew(_size + other._size);

        int i;
        for (i = 0; i < _size; i++)
        {
            sNew[i] = str[i];
        }
        for (int j = 0; j < other._size; j++, i++)
        {
            sNew[i] = other.str[j];
        }

        return sNew;
    }
    String& operator+=(const String& other) {
        *this = String(*this + other);
        return *this;
    }
    const char* to_cstr() const { return str; }
    ~String() {
        if (str != nullptr) {
            delete[] str;
        }
    }
    static String IntToString(int num) {
        char buff[10];
        sprintf(buff, "%d", num);
        return String(buff);
    }
    //friend ostream& operator << (ostream& cout, const String& str);
};
class Node {
public:
    Node(const String& data) : data{ data } {
        //this->data = data;
    }
    String data;
    Node* next = nullptr;
};

class Stack {
    Node* root = nullptr;
    int size = 0;

public:
    void push(const String& data) {
        Node* node = new Node(data);
        node->next = root;

        root = node;
        size++;
    }
    String pop() {
        if (empty()) {
            return String();
        }

        Node* temp = root;
        String tempdata = temp->data;

        root = root->next;

        size--;
        delete temp;
        return tempdata;
    }
    String top() {
        if (empty()) {
            return String();
        }

        return root->data;
    }
    bool empty() const { return root == nullptr; }
    void print() const {
        Node* cur = root;
        while (cur != nullptr)
        {
            printf("%s ", cur->data.to_cstr());
            cur = cur->next;
        }
    }
    ~Stack() {
        while (!empty())
        {
            pop();
        }
    }
};

class List {
    int _size = 0;
    Node* root = nullptr;
    Node* tail = nullptr;


public:
    void add(const String& data) {

        Node* node = new Node(data);

        if (root == nullptr) {
            root = node;
        }
        else {
            tail->next = node;
        }
        tail = node;
        _size++;
    }
    int size() { return _size; }
    String printAndBuild(const String& separ, const String& end) {
        String builder;
        Node* cur = root;
        while (cur != nullptr)
        {
            if (!cur->data.empty()) {
                builder += cur->data + " ";
                printf("%s%s", cur->data.to_cstr(), separ.to_cstr());
            }
            cur = cur->next;
        }
        printf("%s", end.to_cstr());
        return builder;
    }
    ~List() {
        while (root != nullptr)
        {
            Node* node = root;
            root = root->next;
            delete node;
        }
    }
};


struct Pair {
    String key;
    int value;
};

int getValueByKey(const String& key, Pair* pairs, const int size) {
    for (size_t i = 0; i < size; i++)
    {
        if (pairs[i].key == key) {
            return pairs[i].value;
        }
    }
    return INT_MAX;
}


String infixToPostfix(const String& infixexpr) {
    //performs the postfix process.

    Pair prec[10]{
        Pair{String("*"), 3},
        Pair{String("/"), 3},
        Pair{String("N"), 4},
        Pair{String("+"), 2},
        Pair{String("-"), 2},
        Pair{String("("), 1},
        Pair{String(","), 1},
        Pair{String("IF"), 3},
        Pair{String("MIN"), 1},
        Pair{String("MAX"), 1},
    };
    Stack opStack;
    List postfixVector;

    int n;
    String* tokens = infixexpr.split(n);

    for (int i = 0; i < n; i++) {
        String token = tokens[i];

        if (token.isNumber()) {
            postfixVector.add(token);
            while (!opStack.empty() && opStack.top() == "N") {
                postfixVector.add(opStack.top());
                opStack.pop();
            }
        }
        else if (token == "(" || token == "MIN" || token == "MAX" || token == "IF") {

            opStack.push(token);
        }
        else if (token == ",") {
            while (opStack.top() != "(" && opStack.top() != ",") {

                if (opStack.top() != "(" && opStack.top() != "," && (getValueByKey(opStack.top(), prec, 10) >= getValueByKey(token, prec, 10))) {
                    postfixVector.add(opStack.top());
                    opStack.pop();
                }

            }
            opStack.push(token);
        }
        else if (token == ")") {
            String topToken;
            topToken = opStack.pop();

            int count = 0;
            while (topToken == ",")
            {
                count++;
                topToken = opStack.pop();
            }

            while (topToken != "(") {
                if (topToken != ",") {
                    postfixVector.add(topToken);
                }
                topToken = opStack.pop();
            }
            topToken = opStack.top();
            if (topToken == "MIN" || topToken == "MAX" || topToken == "IF") {
                String s = topToken == String("IF") ? String() : String::IntToString(count + 1);
                postfixVector.add(topToken + s);
                opStack.pop();
            }

            while (opStack.top() == "N") {
                postfixVector.add(opStack.top());
                opStack.pop();
            }
        }
        else {
            while (!opStack.empty() && (getValueByKey(opStack.top(), prec, 10) >= getValueByKey(token, prec, 10)) && opStack.top() != "N") //while the stack is not empty and
            {
                if (token == "N" && i + 1 < n && tokens[i + 1] == "(") {
                    break;
                }
                postfixVector.add(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        postfixVector.add(opStack.top());
        opStack.pop();
    }
    delete[] tokens;

    return postfixVector.printAndBuild("  ", "\n");
}

String solving(const String& expression) {
    int n;
    String* tokens = expression.split(n);

    Stack solvStack;

    for (int i = 0; i < n; i++)
    {
        String token = tokens[i];

        if (token.isNumber()) {
            solvStack.push(token);
        }
        else {

            printf("%s ", token.to_cstr());
            solvStack.print();
            printf("\n");

            if (token == "*") {
                int value1 = solvStack.pop().toInt();
                int value2 = solvStack.pop().toInt();

                solvStack.push(String::IntToString(value1 * value2));

            }
            else if (token == "/") {
                int value1 = solvStack.pop().toInt();
                int value2 = solvStack.pop().toInt();
                if (value1 == 0) {

                    solvStack.push("ERROR");
                    break;
                }
                else {
                    solvStack.push(String::IntToString(value2 / value1));
                }
            }
            else if (token == "+") {
                int value1 = solvStack.pop().toInt();
                int value2 = solvStack.pop().toInt();

                solvStack.push(String::IntToString(value1 + value2));
            }
            else if (token == "-") {
                int value1 = solvStack.pop().toInt();
                int value2 = solvStack.pop().toInt();

                solvStack.push(String::IntToString(value2 - value1));
            }
            else if (token.find("MAX") != -1) {
                //"MAX4" -> "4" -> 4
                int count = token.substr(3).toInt();
                int minValue = solvStack.top().toInt();
                for (int j = 0; j < count; j++)
                {
                    minValue = max(minValue, solvStack.pop().toInt());
                }

                solvStack.push(String::IntToString(minValue));
            }
            else if (token.find("MIN") != -1) {
                int count = token.substr(3).toInt();
                int minValue = solvStack.top().toInt();
                for (int j = 0; j < count; j++)
                {
                    minValue = min(minValue, solvStack.pop().toInt());
                }

                solvStack.push(String::IntToString(minValue));
            }
            else if (token == "IF") {
                int c = solvStack.pop().toInt();
                int b = solvStack.pop().toInt();
                int a = solvStack.pop().toInt();

                solvStack.push(String::IntToString(a > 0 ? b : c));
            }
            else if (token == "N") {
                int value1 = solvStack.pop().toInt();

                solvStack.push(String::IntToString(-value1));

            }
        }

    }

    delete[] tokens;

    return solvStack.top();
}



int main() {

    int n;
    cin >> n;//\r\n
    char buff[100000];
    cin.getline(buff, 100000);
    for (int i = 0; i < n; i++)
    {
        cin.getline(buff, 100000);
        printf("%s\n\n", solving(infixToPostfix(buff)).to_cstr());//-8
    }


    return 0;
}