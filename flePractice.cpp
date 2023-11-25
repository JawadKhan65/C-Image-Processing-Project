
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
    cout << "Patched";
    return add.substr(0, catched); //substring the array to the last occured /

}








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
            

            for (int r = 0; r < Row; r++)
            {
                for (int c = 0; c < Col; c++)
                {
                    CIN >> Data[r][c];
                  
                }
               

            }
            
            
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
                Copy << Data[r][c]<<" ";
                
            }
            Copy << endl;
        }
        Copy.close();
    };

    void SaveAs(char destination[200]) {
        ofstream Saveas(destination);
        Saveas << "P2\n#Created by Hitler" << endl;
        Saveas << Col << " " << Row << endl
            << Depth << endl;
        for (int r = 0; r < Row; r++)
        {
            for (int c = 0; c < Col; c++)
            {
                Saveas << Data[r][c];

            }
            Saveas << endl;
        }
        Saveas.close();
    };
    void Delete() {

        cout << "Enter file location to confirm Deletion : " << endl;
        char location[200];
        cin.getline(location, 200);
        cout << "this is location : " << location <<"  are you sure? enter y/n " << endl;
        char yesNo;
        cin>>yesNo;
        cin.ignore();
        if (yesNo == 'y' || yesNo == 'Y') {
            if (remove(location) != 0) {
                perror("Error deleting file ");
            }
            else {
                cout << "File deleted successfully " << endl;
            }
        }
        
        
    };
    void VerticalFlip() {// it do nothing else taking the center and swapping below and above part
        int temp;
        for (int i = 0; i < Row / 2; i++) {
            for (int j = 0; j < Col; j++) {
                temp = Data[i][j];
                Data[i][j] = Data[Row- 1- i][j];
                Data[Row -1- i][j] = temp;
            }
        }
    };
    void RHorizontalFlip() { // it do nothing else taking the center and swapping left and right part
        int temp;
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col/2; j++) {
                temp = Data[i][j];
                Data[i][j] = Data[i][Col-1-j];
                Data[i][Col - 1 - j] = temp;

            }
        }
    };
    void NegativeEffect() {
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                // Inverting pixel values by subtracting them from the maximum value
                Data[i][j] = Depth - Data[i][j]; // in negative actually the rgb value is inverted
                // 
            }
        }
    }






   
};

int main()
{
    image IM1;
    char Location[200], Destination[200];
    getLocations(Location, Destination);
    IM1.Load(Location); // Loading image
    IM1.VerticalFlip();
    IM1.RHorizontalFlip();
    IM1.NegativeEffect();
    IM1.Copy(Location);

    return 0;
}
