#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main () {
    string line, cut, licz1;
    int i,coma=0;
    int count, map=0, licz=0;
    ifstream myfile("C:\\Users\\Windows 8.1\\Documents\\TEXT.TXT");
    ofstream outfile ("C:\\Users\\Windows 8.1\\Documents\\TEXT1.csv");
    if (outfile.is_open())
    {

        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                if(map==0){
                    map++;
                    outfile << line;
                    outfile << "\n";
                    continue;
                }
                for (i = 0; i < line.length(); i++) {
                    if (line[i] != ',') {
                        continue;
                    } else {
                        if (coma != 1) {
                            coma++;
                        } else {
                            count= atoi(line.substr(i+1, i+4).c_str());
                            count=(700-count)/6;
                            ostringstream ss;
                            ss << count;
                            cut= ss.str();
                            //cout << count;
                            //cout << "\n";
                            line.replace((size_t)(i + 1), (size_t)(i+4), cut);
                        }
                    }
                }
                ostringstream s1;
                s1 << licz;
                licz1 = s1.str();
                line = line +','+ licz1;
                  cout << line;
                  cout << "\n";
                coma=0;
                outfile << line;
                outfile << "\n";
                licz++;
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