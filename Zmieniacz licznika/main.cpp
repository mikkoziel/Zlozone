#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main () {
    string line, cut;
    int i,coma=0;
    int count = 0;
    ifstream myfile("C:\\Users\\Windows 8.1\\Desktop\\Studia\\Semestr 5\\Zlożone SC\\1Ostateczna wersja projektu\\Statystyki\\TEXT1.csv");
    ofstream outfile ("C:\\Users\\Windows 8.1\\Desktop\\Studia\\Semestr 5\\Zlożone SC\\1Ostateczna wersja projektu\\Statystyki\\TEXT.csv");
    if (outfile.is_open())
    {

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            for (i = 0; i < line.length(); i++) {
                if (line[i] != ',') {
                    continue;
                } else {
                    if (coma != 2) {
                        coma++;
                    } else {
                        ostringstream ss;
                        ss << count;
                        cut= ss.str();
                        //cout << cut;
                        //cout << "\n";
                        line.replace((size_t)(i + 1), (size_t)(line.length() - 1), cut);
                    }
                }
            }
            cout << line;
            cout << "\n";
            coma=0;
            outfile << line;
            outfile << "\n";
            count++;
            //cout << count;
            //cout << "\n";
        }




          myfile.close();
        } else cout << "Unable to open file";
        outfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}