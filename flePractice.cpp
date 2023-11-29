
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
void inputlocation(char Location[200]) // Taking Location where the Image is located
{
    cout << "Enter the Location of the file"
         << " for example D:/folder/file" << endl;
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
    cout << "Executing..." << endl;
    string add = location;
    int length = add.length();
    int catched=length-4;
    /*for (int i = length; i >= 0; i--)
    {
        if (add[i] == '/' || add[i] == '\\') {
            catched = i;
            break;
        }
    }*/

    cout << "Copied." << endl;
    return add.substr(0, catched); //substring the array to the last occured /

}


struct Image
{
    int Col, Row, Depth;
    unsigned int Data[400][400];
    char Comment[100];
    char MagicNumber[10];

    int Load(char FileLocation[200])
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
            return -1;
            // Handle the failure to open the file
        }
        if (CIN.fail())
            return -2;

        CIN.close();
        return 0;

    }
    void Copy(char FileLocation[])
    {
        
        string location = Extraction(FileLocation);
        string tag = "Copy.pgm";
        string rebuild = location + tag;
        
        ofstream Copy(rebuild);
        Copy << "P2\n#Created by Hitler" <<" " << system("date") << endl;
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

    int Save(char destination[200]) {
        ofstream Saveas(destination);
        Saveas << "P2\n#Created by Hitler" << endl;
        Saveas << Col << " " << Row << endl
            << Depth << endl;
        for (int r = 0; r < Row; r++)
        {
            for (int c = 0; c < Col; c++)
            {
                Saveas << Data[r][c]<<" ";

       
            }
            Saveas << endl;
        }
        Saveas.close();
        
        return 0;
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
                Data[i][j] = ((Depth)-Data[i][j]); // in negative actually the rgb value is inverted
                // 
            }
        }
    }
    void Blackpoint() {
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                // Inverting pixel values by subtracting them from the maximum value
                Data[i][j] =  12+(Data[i][j]); // in negative actually the rgb value is inverted
                // 
            }
        }
        
    }
    void LinearCont() {
        int min = 255;
        int max = 0;
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++) {
                if (Data[i][j] < min) {
                    min = Data[i][j];
                }
                if (Data[i][j] > max) {
                    max = Data[i][j];
                }

            }
        }
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++)
            {
                Data[i][j] = (Data[i][j] - min) * 255;
            }

        }
        
    }
    void Derivative() {
        int minVal = Data[0][0];
        int maxVal = Data[0][0];

        // Csb se phle derivatives along x jitna difference hoga wo derivative hoga

        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col - 1; ++j) {
                // derivative calculate krta hua

                int derivative = Data[i][j + 1] - Data[i][j];

                //  min and max values ka check 
                if (derivative < minVal) {
                    minVal = derivative;
                }
                if (derivative > maxVal) {
                    maxVal = derivative;
                }

                // Store the derivative value
                Data[i][j] = derivative;
            }
            // akhri column zero krta hua ... 
            Data[i][Col - 1] = 0;
        }

        // tasweer ko grey krna k lya thora sa makeup
        // upr min max k zariya aik customized range tk ka derivative
        // simple to fit pixels in between 0-255
        int range = maxVal - minVal;
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                Data[i][j] = ((Data[i][j] - minVal) * 255) / range;
            }                // min se differ         // 0-255 k lya scale 
        }
        // Now, the Data array holds the adjusted derivative values within 0-255 range
    }
    void IncreaseBrightness() {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                int newValue = Data[i][j] * 3;
                Data[i][j] = (newValue > 255) ? 255 : newValue;
            }
        }
    }

    void Mean(int ratio=3) {
        int matrix_size = ratio;
        int square = matrix_size * matrix_size;

        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++) {
                //taking median 
                int mean = 0;
                for (int row = -matrix_size/2; row < matrix_size/2; row++)
                {
                    for (int col = -matrix_size / 2; col < matrix_size / 2; col++) {

                        // find width and height
                        int height = i + row;
                        int width = j + col;
                        if ((height >= 0 && width >= 0) && (height < Row && width < Col)) {
                            mean += Data[height][width];
                        }

                    }
                }
                Data[i][j] = mean / square;
            }
        }
    }
    void Median() {
        int matrix_size = 3;

        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                int value[9];
                int index = 0;

                for (int row = -matrix_size / 2; row <= matrix_size / 2; row++) {
                    for (int col = -matrix_size / 2; col <= matrix_size / 2; col++) {
                        int height = i + row;
                        int width = j + col;

                        if ((height >= 0 && width >= 0) && (height < Row && width < Col)) {
                            value[index++] = Data[height][width];
                        }
                    }
                }

                // Sort the values to find the median using a more efficient sorting algorithm
                for (int k = 0; k < index - 1; k++) {
                    for (int l = 0; l < index - k - 1; l++) {
                        if (value[l] > value[l + 1]) {
                            int temp = value[l];
                            value[l] = value[l + 1];
                            value[l + 1] = temp;
                        }
                    }
                }

                int median;
                if (index % 2 == 0) {
                    median = (value[index / 2] + value[index / 2 - 1]) / 2; // If even number of elements
                }
                else {
                    median = value[index / 2]; // If odd number of elements
                }

                Data[i][j] = median;
            }
        }
    }
    void RotateImageClockwise()
    {
        int temp;
        for (int layer = 0; layer < Row / 2; layer++) {
            int first = layer;
            int last = Row - 1 - layer;
            for (int i = first; i < last; i++) {
                int offset = i - first;
                // Save top
                temp = Data[first][i];
                // Left -> Top
                Data[first][i] = Data[last - offset][first];
                // Bottom -> Left
                Data[last - offset][first] = Data[last][last - offset];
                // Right -> Bottom
                Data[last][last - offset] = Data[i][last];
                // Top -> Right
                Data[i][last] = temp;
            }
        }
    }
    
    void RotateImageByAngle(double angle)
    {
        const double PI = 3.141519;
        double radians = angle * PI / 180.0; // Convert angle to radians
        double cosine = cos(radians);
        double sine = sin(radians);

        // Create a temporary matrix to store rotated values
        

        // Find the center of the image
        double cx = static_cast<double>(Col - 1) / 2.0; // Col and row are int so make
        double cy = static_cast<double>(Row - 1) / 2.0;//them double

        // Traverse the original matrix and apply rotation
        for (int y = 0; y < Row; ++y)
        {
            for (int x = 0; x < Col; ++x)
            {
                // Translate coordinates to the center
                double xFromCenter = x - cx;// image - center allong x
                double yFromCenter = y - cy;//image - center along y

                // Apply rotation formula
                int newX = static_cast<int>(xFromCenter * cosine - yFromCenter * sine + cx); 
                int newY = static_cast<int>(xFromCenter * sine + yFromCenter * cosine + cy);

                // Check bounds and assign values to the temporary matrix
                if (newX >= 0 && newX < Col && newY >= 0 && newY < Row)
                {
                    Data[newY][newX] = Data[y][x];
                }
            }
        }

        
       
    }
   



    


};
int Menu(char menuFile[]) {
    ifstream IN;
    IN.open(menuFile);
    if (!IN.is_open())
        return -1;
    char MenuItems[30][100];
    char TotalItems[10];
    int Choices, userChoice;

    IN.getline(TotalItems, 8);

    Choices = atoi(TotalItems);

    for (int i = 1; i <= Choices; i++) {
        IN.getline(MenuItems[i - 1], 99);
    }
    IN.close();

    do {
        for (int i = 0; i < Choices; i++) {
            cout << i + 1 << "\t" << MenuItems[i] << endl;
        }
        cout << " Enter Your Choice (1 - " << Choices << " ) ";
        cin >> userChoice;
    } while (userChoice < 1 || userChoice > Choices);

    return userChoice;
}

int main()
{
    Image Images;
    int ActiveImage = 0;
    int ErrorCode = 0;
    int choice;
    char menufile[] = "D:/designs/Main.txt";
    char ImageFileName[100];
    int saveCheck = 0;

    do {

        choice = Menu(menufile);

            char ImageFileName1[100];
        if (1 == choice) {
            cout << "Specify File Name (format: D:/folder/file)";
            cin >> ImageFileName1;

            ErrorCode = Images.Load(ImageFileName1);
            if (ErrorCode == 0) {
                cout << "File Loaded Successfully  " << endl;
            }
            else {
                cout << "Load Error: Code " << ErrorCode << endl;
            }
        }
        else if (2 == choice) {

            cout << "Specify File Name (format: D:/folder/file) ";
            cin >> ImageFileName;
            ErrorCode = Images.Save(ImageFileName);
            if (ErrorCode == 0) {
                saveCheck++;
                cout << "File Saved as " << ImageFileName << endl;
            }
            else {
                cout << "Save Error: Code " << ErrorCode << endl;
            }
        }
        else if (3 == choice) {
            Images.RHorizontalFlip();
            cout << "You need to save the changes " << endl;
        }else if (4 == choice) {
            Images.VerticalFlip();
            cout << "You need to save the changes " << endl;
        }
        else if (5 == choice) {
            Images.Derivative();
            cout << "You need to save the changes " << endl;
        }else if (6 == choice) {
            Images.Blackpoint();
            cout << "You need to save the changes " << endl;
        }
        else if (7 == choice) {
            int ratio;
            cout << "Enter Ratio for blur e.g 1X =3 , 2X = 4" << endl;
            cin >> ratio;
            Images.Mean(ratio);
            cout << "You need to save the changes " << endl;
        }else if (8 == choice) {
            
            Images.Median();
            cout << "You need to save the changes " << endl;
        }else if (9== choice) {
            
            Images.IncreaseBrightness();
            cout << "You need to save the changes " << endl;
        } else if (10 == choice) {
                Images.LinearCont();
            
            cout << "You need to save the changes " << endl;
        }else if (11 == choice) {
            double angle;
            cout << "enter an angle : ";
            cin >> angle;
            Images.RotateImageByAngle(angle);
            
            cout << "You need to save the changes " << endl;
        }else if (12 == choice) {
           
            Images.RotateImageClockwise();
            cout << "You need to save the changes " << endl;
        }else if (13 == choice) {
           
            Images.Copy(ImageFileName1);
            cout << "You need to save the changes " << endl;
        } else if (14 == choice) {
            if(saveCheck>0)
                 system(ImageFileName);
            else
            {
                cout << "You have not saved File yet .";
            }
           
        }

    } while (choice != 15);

    return 0;
}
