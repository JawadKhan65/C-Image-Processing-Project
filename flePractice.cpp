
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;
void inputlocation(char Location[200]) // Taking Location where the Image is located
{
    cout << "Enter the Location of the file"
         << " for example D:\\folder\\file" << endl;
    cin.getline(Location, 200);
    
}
void inputDestination(char destination[200]) // Taking input to save at what location
{
    cout << "Enter the Destination of the file " << endl;
    cin.getline(destination, 200);
    

}
void getLocations(char location[200], char destination[200]) // checking the provided locations must not be same.
{
    do
    {
        inputlocation(location);
        inputDestination(destination);
    } while (strcmp(location, destination) == 0);
}


//getting routes for copy images extraction of directory
string Extraction(char location[200]) {
    
    string add = location;
    int length = add.length();
    int catched=0;
    for (int i = length; i >= 0; i--)
    {
        if (add[i] == '/') {
            catched = i;
            break;
        }
    }
    return add.substr(0, catched); //substring the array to the last occured /
}
// Manipulation

void VerticalFlip(int img[400][400]);
void Transpose(int img[400][400]);
void centerFlip(int image[400][400]);
// Copy & Delete
void Delete(char location[200]);


struct image
{
    int Col, Row, Depth;
    int Data[400][400];
    char Comment[100];
    char MagicNumber[10];

    void Load(char FileLocation[200])
    {
       
        
        ifstream CIN;   
        CIN.open(FileLocation);

        if (CIN.is_open())
        {
            CIN.getline(MagicNumber, 4);
            CIN.getline(Comment, 99);
            CIN >> Col >> Row >> Depth;
            cout << Col << Row << Depth;

            for (int r = 0; r < Row; r++)
            {
                for (int c = 0; c < Col; c++)
                {
                    CIN >> Data[r][c];
                    cout << Data[r][c]<<"  ";
                }
               

            }
            cout << endl << "Done with it" << endl;;
        }
        else
        {
            cout << "File failed to open." << endl;
            // Handle the failure to open the file
        }

        CIN.close();
    }
    void Copy(char FileLocation[])
    {
        
        string location = Extraction(FileLocation);
        string tag = "/Copy.pgm";
        string rebuild = location + tag;

        ofstream Copy(rebuild);
        Copy << "P2\n#Created by Hitler" << endl;
        Copy << Col << " " << Row << endl
             << Depth << endl;
        for (int r = 0; r < Row; r++)
        {
            for (int c = 0; c < Col; c++)
            {
                Copy << Data[r][c];
                
            }
            Copy << endl;
        }
        Copy.close();
    };

    void SaveAs(char destination[200]) {

    };
};

int main()
{
    image IM1;
    char Location[200], Destination[200];
    getLocations(Location, Destination);
    IM1.Load(Location); // Loading image
    IM1.Copy(Location);
    
    

    return 0;
}
