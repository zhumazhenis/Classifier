//
// Created by Zhumazhenis on 03/03/2018.
//

#include "functions.h"
#include <vector>

using namespace std;

int pc = 0;
int len;
char a = 0;
char b = 0;
int *content;
bool isArithmetic = false;
pair<int, int> hexByte[] = {
        mp(0x00, 1), mp(0x01, 1), mp(0x02, 1), mp(0x03, 2), mp(0x04, 2), mp(0x05, 3),
        mp(0x06, 3), mp(0x07, 3), mp(0x08, 3), mp(0x09, 1), mp(0x0A, 1), mp(0x0B, 1),
        mp(0x0C, 1), mp(0x0D, 1), mp(0x0E, 1), mp(0x0F, 1), mp(0x10, 1), mp(0x11, 1),
        mp(0x12, 1), mp(0x13, 1), mp(0x14, 1), mp(0x15, 1), mp(0x16, 1), mp(0x17, 3),
        mp(0x18, 3), mp(0x19, 3), mp(0x20, 1), mp(0x21, 1), mp(0x22, 1), mp(0x23, 1)
};



map<int, int> values; // map
map<int, int>::iterator it = values.begin();

/* Builds map using hexByte array */
void assignKeys() {
    for (int i = 0; i < sizeof(hexByte) / sizeof(hexByte[0]); i++) {
        values.insert(it, pair<int, int>(hexByte[i].first, hexByte[i].second));
    }
}

/* Task 1: Reads from .hex file, and saves them to dynamic array */
char *getHex(ifstream &fptr) {
    string s;
    fptr >> s;
    len = s.length() / 2;
    if (len == 0)
        return nullptr;
    char *ans = new char[len];
    for (int i = 0; i < len; i++) {
        ans[i] = (char) stoul(s.substr((unsigned int) (2 * i), 2), nullptr, 16);
    }
    fptr.close();
    return ans;
}

/* Task 2: ALU function for arithmetic operations only */
char alu(char a1, char b1, char op) {
    isArithmetic = true;
    int ans = 9999;
    // ADD
    if (op == 0x09)
        ans = ((int) a1 + (int) b1);

    // SUB
    if (op == 0x0A)
        ans = ((int) a1 - (int) b1);

    // MUL
    if (op == 0x0B)
        ans = ((int) a1 * (int) b1);

    // DIV
    if (op == 0x0C)
        ans = ((int) a1 / (int) b1);

    // AND
    if (op == 0x11)
        ans = a1 & b1;

    // OR
    if (op == 0x12)
        ans = a1 | b1;

    // XOR
    if (op == 0x13)
        ans = a1 ^ b1;

    // CMP returns maximum, (but NOT sure, how CMP mnemonic works in Assembly Language)
    if (op == 0x14) {
        if((int)a1 == (int)b1)
            ans = 0;
        else
            ans = 1;
    }

    if ((-128 <= ans) && (ans <= 127)) {
        return (char) ans;
    }

    isArithmetic = false;
}

/* Task 3:  Update PC, which increments by offset */
void updatePC(int offset) {
    pc += offset;
}

/* Task 1: Tests getHex() function */
void testGetHex() {
    cout << "Task 1:\n";
    ifstream myFile = buildFile();
    char *ram = getHex(myFile); // reads from .hex file, and saves them in ram dynamic array (pointer)
    for (int i = 0; i < len; i++) {
        cout << setfill('0') << setw(2) << hex << (int) ((unsigned char) ram[i]) << endl;
    }
    myFile.close();
}

/* Task 2: Test alu() function */
void testAlu() {
    cout << "\nTask 2:\n";
    ifstream myFile = buildFile();
    char *ram = getHex(myFile);

    char a = (char) (0x10);
    char b = (char) (0x04);
    cout << "a = 0x" << hex << (unsigned int) a << ", b = 0x" << (unsigned int) b << endl;
    cout << "Instr: \t" << "Ans:\n";

    for (int i = 0; i < len; i++) {
        cout << uppercase << hex << setfill('0') << setw(2) << (int) (ram[i]) << " \t";
        char c = alu(a, b, ram[i]);
        if (isArithmetic)
            cout << hex << "0x" << (int) c << endl;
        else
            cout << "ERROR!" << endl;
    }
    myFile.close();
}

/* Task 4: Tests Task 4, using getHex() and updatePC() functions */


ifstream buildFile() {
    ifstream myFile;
    string hexFileName;
    cout << "Enter hex file name: ";
    cin >> hexFileName;
    myFile.open(hexFileName);
    return myFile;
}




/* final */



void testTask34() {
    assignKeys();
    cout << "\nTask 3, 4:\n";
    ifstream myFile = buildFile();
    char *ram = getHex(myFile); // function from from Task 1

    cout << "Bytes: \t" << "Instr:" << endl;
    while (pc < len) {
        int offset = values[(int) ram[pc]];
        printf("%dB\t", offset);
        printf("%02x ", (int)ram[pc]);

        if (offset == 3) {
            // char addr = (char) (((int) ram[pc + 1] * 0x100) + (int) ram[pc + 2]);
            printf("%02x%02x ", (int) ram[pc + 1], (int) ram[pc + 2]);

        } else if (offset == 2) {

            printf("%02x ", (int) ram[pc + 1]);

        }
        cout << endl;
        updatePC(offset); // function from Task 3
    }
    myFile.close();
}

/* Task 4: Tests Task 4, using getHex() and updatePC() functions */
void finalFunction() {
    set<int> index;
    a = b = 0;
    assignKeys();
    content = new int[5000];
    cout << "\nFinal result: \n";
    ifstream myFile = buildFile();
    char *ram = getHex(myFile); // function from from Task 1

    cout << "Bytes: \t" << "Instr:\t" << "Reg A:\t" << "Reg B:" << endl;
    while (pc < len) {
        int offset = values[(int) ram[pc]];
        printf("%dB\t", offset);
        printf("%02x ", (int)ram[pc]);

        if (offset == 3) {
            // char addr = (char) (((int) ram[pc + 1] * 0x100) + (int) ram[pc + 2]);
            printf("%02x%02x", (int) ram[pc + 1], (int) ram[pc + 2]);

            switch(ram[pc]) {
                case 0x05:
                    a = content[((int)ram[pc + 1]) * 0x100 + (int)ram[pc + 2]];
                    break;
                case 0x06:
                    b = content[((int)ram[pc + 1]) * 0x100 + (int)ram[pc + 2]];
                    break;
                case 0x07:
                    content[((int) ram[pc + 1]) * 0x100 + (int) ram[pc + 2]] = (int) a;
                    index.insert(((int) ram[pc + 1]) * 0x100 + (int) ram[pc + 2]);
                    break;
                case 0x08:
                    content[((int) ram[pc + 1]) * 0x100 + (int) ram[pc + 2]] = b;
                    index.insert(((int) ram[pc + 1]) * 0x100 + (int) ram[pc + 2]);
                    break;
                case 0x17:
                    ram[pc + 3] = content[((int)ram[pc + 1]) * 0x100 + (int)ram[pc + 2]];
                    break;
                case 0x18:
                    if(a == 0x00)
                        ram[pc + 3] = content[((int)ram[pc + 1]) * 0x100 + (int)ram[pc + 2]];
                    break;
                case 0x19:
                    if(a != 0x00)
                        ram[pc + 3] = content[((int)ram[pc + 1]) * 0x100 + (int)ram[pc + 2]];
                    break;
            }


        } else if (offset == 2) {
            switch(ram[pc]) {
                case 0x03:
                    a = ram[pc + 1];
                    break;
                case 0x04:
                    b = ram[pc + 1];
                    break;
            }
            printf("%02x", (int) ram[pc + 1]);
        }

        char temp = alu(a, b, ram[pc]);
        if(isArithmetic)
            a = temp;
        cout << "\t";
        cout << hex << setfill('0') << setw(2) << (int) ((unsigned char) a);
        cout << "\t";
        cout << hex << setfill('0') <<setw(2) << (int) ((unsigned char) b) << " ";
        cout << endl;
        updatePC(offset); // function from Task 3
    }

    cout << endl;
    for (std::set<int>::iterator it=index.begin(); it!=index.end(); ++it) {
        printf("%02x address: %02x\n", (int) *it, (int) content[*it]);
    }

    myFile.close();
}
