#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
struct Imran {

    int Cols, Rows, Depth;

    int Data[400][400];
    char comment[100];
    char magic[10];
    void Load(char c[]){
        //
        // file read 

        })
};

int main() {
    /*ifstream imageFile("D:/designs/ideogram3.jpeg", ios::binary);
    ofstream textFile("D:/file.txt");
    

    if (!imageFile.is_open() || !textFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    char byte;
    textFile << " ConverterX\n size\n";
    while (imageFile.get(byte)) {
        textFile << static_cast<unsigned int>(static_cast<unsigned char>(byte)) << " ";
    } 
    imageFile.close();
    textFile.close();


    string line;
    int rows = 0;
    int columns = 0;
    ifstream text("D:/file.txt");
   
    while (getline(text, line)) {
        istringstream iss(line);
        int count = 0;
        while (iss >> count) {
            ++columns;
        }
        ++rows;
    }

    text.close();

    cout << "Rows: " << rows << endl;
    cout << "Columns: " << columns / rows << endl;*/

    
    


    return 0;
}
