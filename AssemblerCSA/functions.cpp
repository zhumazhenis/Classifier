//
// Created by Zhumazhenis on 26/01/2018.
//
#include "functions.h"

using namespace std;

/* Defining vairables */

string error;
char c[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
string s[] = {"NOP", "MOV", "ADD", "SUB", "MUL", "DIV", "INC", "DEC", "AND", "OR",
              "XOR", "CMP", "CLR", "JMP", "JZ", "JNZ", "CPL", "XCHG", "HLT", ""};

string s2[] = {"", "A,B", "B,A", "A,#X", "B,#X", "A,Address", "B,Address", "Address,A", "Address,B", "Address"};

string keys[] = {
        "NOP ", "MOV A,B", "MOV B,A", "MOV A,#X", "MOV B,#X", "MOV A,Address", "MOV B,Address", "MOV Address,A",
        "MOV Address,B", "ADD A,B", "SUB A,B", "MUL A,B", "DIV A,B", "INC A", "INC B", "DEC A", "DEC B", "AND A,B",
        "OR A,B", "XOR A,B", "CMP A,B", "CLR A", "CLR B", "JMP Address", "JZ Address", "JNZ Address", "CPL A", "CPL B",
        "XCHG A,B", "HLT "
};

set<char> addressSet(c, c + sizeof(c) / sizeof(c[0]));
set<string> mnemSet(s, s + sizeof(s) / sizeof(s[0]));
set<string> operandSet(s2, s2 + sizeof(s2) / sizeof(s2[0]));

pair<string, int> hexByte[] = {
        mp("00", 1), mp("01", 1), mp("02", 1), mp("03", 2), mp("04", 2), mp("05", 3),
        mp("06", 3), mp("07", 3), mp("08", 3), mp("09", 1), mp("0A", 1), mp("0B", 1),
        mp("0C", 1), mp("0D", 1), mp("0E", 1), mp("0F", 1), mp("10", 1), mp("11", 1),
        mp("12", 1), mp("13", 1), mp("14", 1), mp("15", 1), mp("16", 1), mp("17", 3),
        mp("18", 3), mp("19", 3), mp("20", 1), mp("21", 1), mp("22", 1), mp("23", 1)
};

map<string, pair<string, int>> values;
map<string, pair<string, int>>::iterator it = values.begin();

void assignKeys() {
    for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
        values.insert(it, pair<string, pair<string, int>>(keys[i], hexByte[i]));
    }
}

///////////////////////////////////////////////////////////////////////

/* Defining functions */

void process() {
    assignKeys();

    int n;
    cout << "ASSEMBLY to HEXADECIMAL converter program\n\nEnter the number of files: ";
    cin >> n;
    cout << "\n";
    string fileName[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << " filename: ";
        cin >> fileName[i];
    }

    for (int i = 0; i < n; i++) {
        toHex(fileName[i]);
    }
    cout << "\n\n";
    system("pause");
}

string getMnemonic(ifstream &fptr) {
    string s;
    fptr >> s;
    return s;
}

string getOperand(ifstream &fptr) {
    string operand = "", temp;
    while (fptr.peek() == ' ' || fptr.peek() == '\t')
        fptr.get();
    while (fptr.peek() != '\n' && !fptr.eof()) {
        if ((bool) (fptr >> temp)) {
            if (!operand.empty()) {
                if (operand.back() != ',' && temp[0] != ',') {
                    operand.append(" ");
                }
            }
            operand.append(temp);
        }
        while (fptr.peek() == ' ' || fptr.peek() == '\t')
            fptr.get();
    }
    return operand;
}

string normOperand(string operand) {

    if (isData(operand)) {
        for (long long int i = operand.length() - 1; i >= 0; i--) {
            if (operand[i] != '#') {
                operand.erase(operand.begin() + i);
            } else {
                operand.append("X");
                break;
            }
        }
    }

    if (isAddress(operand)) {
        string temp = "Address";
        operand.erase(0, 4);
        operand = temp.append(operand);
    } else if (operand.length() >= 5 &&
               isAddress(operand.substr(operand.length() - 4, 4))) {

        operand.erase(operand.length() - 4, 4);
        operand.append("Address");
    }
    return operand;
}

bool isMnemonic(string mnemonic) {
    return mnemSet.find(mnemonic) != mnemSet.end();
}

bool isOperand(string operand) {
    return operandSet.find(operand) != operandSet.end();
}

bool isAddress(string s) {
    for (int i = 0; i < 4; i++) {
        if (!(addressSet.find(s[i]) != addressSet.end()))
            return false;
    }
    return true;
}

bool isData(string s) {
    for (int i = (int) s.length() - 1; i >= 0; i--) {
        if (s[i] == '#') {
            string a = "";
            a = s.substr((unsigned int) i + 1, s.length() - 1 - i);
            if (a.length() > 2) {
                return false;
            } else if (a.length() == 2) {
                return (addressSet.find(a[0]) != addressSet.end()) &&
                       (addressSet.find(a[1]) != addressSet.end());
            } else if (a.length() == 1) {
                return addressSet.find(a[0]) != addressSet.end();
            }

            return false;
        }
    }
    return false;
}

string extract(string operand) {
    string data = "";
    if (isData(operand)) {
        for (int i = (int) operand.length() - 1; i >= 0; i--) {
            if (operand[i] != '#') {
                string temp = string(1, operand[i]);
                temp.append(data);
                data = temp;

            } else {
                if (data.length() == 1) {
                    string temp = "0";
                    temp.append(data);
                    data = temp;
                }
                return data;
            }
        }
    } else if (isAddress(operand.substr(0, 4))) {
        return operand.substr(0, 4);
    } else if (operand.length() > 4 &&
               isAddress(operand.substr(operand.length() - 4, 4))) {
        return operand.substr(operand.length() - 4, 4);
    }
    return "";
}

void toHex(string inFileName) {

    ifstream fptr;
    ofstream outFile;
    string outName = inFileName.substr(0, inFileName.length() - 3);
    outName.append("hex");

    fptr.open(inFileName);
    if (!(fptr.is_open())) {
        cout << "\n\n\"" << inFileName << "\" could not open!";
        return;
    }

    string mnemonic, operand, ans = "", copyOperand, temp = "", tempError = "";
    int line = 1, bytes = 0;
    while (!fptr.eof()) {
        mnemonic = getMnemonic(fptr);
        if (!mnemonic.length()) {
            break;
        }
        copyOperand = getOperand(fptr);
        operand = normOperand(copyOperand);

        if (!isMnemonic(mnemonic)) {
            tempError = "There is no such mnemonic ";
            tempError.append(mnemonic);
            tempError.append("; ");
        }
        if (!isOperand(operand)) {
            tempError.append("There is no such operand ");
            tempError.append(copyOperand);
            tempError.append("; ");
        }

        temp.append(mnemonic);
        temp.append(" ");
        temp.append(operand);

        if (values.count(temp)) {
            ans.append(values[temp].first);
            ans.append(extract(copyOperand));
            bytes += values[temp].second;
        } else if (tempError.length() == 0) {
            tempError.append(mnemonic);
            tempError.append(" mnemonic does not support operand ");
            tempError.append(copyOperand);
            tempError.append(";");
        }

        if (tempError.length() > 0) {
            temp = to_string(line);
            temp.append(" line: ");
            temp.append(tempError);
            temp.append("\n");
            tempError = temp;
        }

        error.append(tempError);
        tempError = "";
        temp = "";
        line++;
    }

    fptr.close();
    outFile.open(outName, ofstream::out | ofstream::trunc);

    if (error.length()) {
        cout << "\n\n\"" << inFileName << "\" has error following line(s):\n" << error;
        outFile << error;
    } else {
        cout << "\n\n\"" << outName << "\" succeeded: " << ans << "; \tnumber of bytes: " << bytes;
        outFile << ans;
    }

    outFile.close();
    error = "";
}