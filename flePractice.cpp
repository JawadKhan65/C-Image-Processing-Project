
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
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
    char ImageFileName[100];
    vector<vector<int>> Data;
    
    int Col, Row, Depth;
    vector<char> comment;

    bool imageLoaded;
    bool imageModified;


    int Load(char ImageName[]) {

        ifstream FCIN(ImageName);

        if (!FCIN.is_open())
            return -1;

        char MagicNumber[5];
        char Comment[100];

        FCIN.getline(MagicNumber, 4);
        FCIN.getline(Comment, 100);
        FCIN >> Col >> Row >> Depth;

        Data.clear();
        Data.resize(Row, vector<int>(Col, 0));

        for (int r = 0; r < Row; r++)
            for (int c = 0; c < Col; c++)
                FCIN >> Data[r][c];

        if (FCIN.fail())
            return -2;

        FCIN.close();
        imageLoaded = true;
        imageModified = false;
        
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
        int min = 255; // white
        int max = 0;// black
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++) {
                if (Data[i][j] < min) {
                    min = Data[i][j];//simple if anything more brighter
                        // checking if any thing less than assigned min
                }
                if (Data[i][j] > max) {
                    // same as above anything more darker than dark 0
                    max = Data[i][j];
                }

            }
        }
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++)
            {
                Data[i][j] = (Data[i][j] - min) * 255;
                //replaced the new values by subtracting white color any
                // multiplying max depth

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
    void IncreaseBrightness(int factor) {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                int newValue = Data[i][j] * factor;
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
                        int width = j + col;//height check and width check
                        if ((height >= 0 && width >= 0) && (height < Row && width < Col)) {
                            mean += Data[height][width];//replacing sum at every index
                        }

                    }
                }
                Data[i][j] = mean / square;// mean filtering sum to mean by dividing
            }
        }
    }
    void Median() {
        int matrix_size = 3;

        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                int value[9];//array for later sorting
                int index = 0;//index for incrementation

                for (int row = -matrix_size / 2; row <= matrix_size / 2; row++) {
                    for (int col = -matrix_size / 2; col <= matrix_size / 2; col++) {
                        int height = i + row;// same boundary check not excede the matrix
                        int width = j + col;
                        // width height check here
                        if ((height >= 0 && width >= 0) && (height < Row && width < Col)) {
                            value[index++] = Data[height][width];//placement
                        }
                    }
                }

                // Sort the values to find the median using a more efficient sorting algorithm
                for (int k = 0; k < index - 1; k++) {
                    for (int l = 0; l < index - k - 1; l++) {
                        if (value[l] > value[l + 1]) {
                            int temp = value[l];//bubble sort
                            value[l] = value[l + 1];
                            value[l + 1] = temp;
                        }
                    }
                }

                int median;
                if (index % 2 == 0) {
                    //for evens
                    median = (value[index / 2] + value[index / 2 - 1]) / 2; // If even number of elements
                }
                else {
                    //for odds
                    median = value[index / 2]; // If odd number of elements
                }

                Data[i][j] = median;
            }
        }
    }
    void RotateImageClockwise() {
        vector<vector<int>> temp(Col, vector<int>(Row, 0)); // Create a temporary vector with swapped dimensions

        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                temp[j][Row - i - 1] = Data[i][j]; // Rotate clockwise
                //transpose
            }
        }

        // Update Data with the rotated image
        Data = temp;
    }

    void RotateImageAntiClockwise()
    {
        vector<vector<int>> temp(Col, vector<int>(Row, 0)); // Create a temporary vector with swapped dimensions

        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                temp[Col-j-1][i] = Data[i][j]; // Rotate anticlockwise
                //transpose along cols
            }
        }

        // Update Data with the rotated image
        Data = temp;
    }
   
    
    void RotateImageByAngle(double angle) {
        
       
            const double PI = 3.141592;
            double Radians = angle * PI / 180.0;// changing angle into radians for cmath

            double cosTheta = cos(Radians);// horizontal angle
            double sinTheta = sin(Radians);//vertical angle

            double centerX = static_cast<double>(Col) / 2.0; // finding center along X
            double center_alongY = static_cast<double>(Row) / 2.0;// finding center along Y

            // Calculating the dimensions of the rotated image 
            int rotatedCols = abs(cosTheta) * Col + abs(sinTheta) * Row;
            int rotatedRows = abs(sinTheta) * Col + abs(cosTheta) * Row;
            // new vector to get rotated image
            vector<vector<int>> rotatedData(rotatedRows, vector<int>(rotatedCols, 0));

            //loop to rotate
            for (int r = 0; r < rotatedRows; ++r) {
                for (int c = 0; c < rotatedCols; ++c) {
                    double rotx = c - centerX - (rotatedCols - Col) / 2.0; // difference from center of onPoint index along x
                    double roty = r - center_alongY - (rotatedRows - Row) / 2.0;// difference from center of onPoint index along Y

                    double changedX = rotx * cosTheta + roty * sinTheta + centerX;// new location difference from center
                    double changedY = -rotx * sinTheta + roty * cosTheta + center_alongY;

                    int x = changedX;//house 
                    int y = changedY;
                    int x1 = x + 1;//house neighbour you got it
                    int y1 = y + 1;

                    if (x >= 0 && x1 < Col && y >= 0 && y1 < Row) {
                        double locX1 = changedX - x;// toget new values of rotated image
                        double locX0 = 1.0 - locX1;
                        double locY1 = changedY - y;
                        double locY0 = 1.0 - locY1;

                        rotatedData[r][c] = locY0 * (locX0 * Data[y][x] + locX1 * Data[y][x1])
                            + locY1 * (locX0 * Data[y1][x] + locX1 * Data[y1][x1]);
                    }
                }
            }

            
            Col = rotatedCols;// changing orignal Cols
            Row = rotatedRows;// changing orignal Rows
            Data = rotatedData;
            
        
    }
   

// Apply a general linear filter to the image
    void LinearFilter(int input) {
        
        double Filter_Kernel[3][3];// filter Filter_Kernel 3x3
        
        if (input == 1 )
        {
            //reading sharpen kernel 
            // 0 -1 0 -1 5 -1 0 -1 0 from file

            ifstream Sharpen("D:/designs/sharpen.txt");
            if (Sharpen.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Sharpen >> Filter_Kernel[i][j])) {
                            // error accordingly
                        }
                    }
                }
            }
            Sharpen.close(); // Close the file after reading
        }
        else if (input == 2 )
        {
            //reading blur kernel from file 
            //  0.1 0.1 0.1
            //  0.1 0.1 0.1
            //  0.1 0.1 0.1 
            ifstream Blur("D:/designs/blur.txt");
            if (Blur.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Blur >> Filter_Kernel[i][j])) {
                            //ngl
                        }
                    }
                }
            }
            Blur.close(); // Close the file after reading
        }else if (input == 3 )
        {
            //reading edge detection filter from file
            // -1 -1 -1
            //  -1 8 -1
            //  -1 -1 -1 
            ifstream Edge("D:/designs/edge.txt");
            if (Edge.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Edge >> Filter_Kernel[i][j])) {
                            // brb
                        }
                    }
                }
            }
            Edge.close(); // Close the file after reading
        }else if (input == 4 )
        {
            // negative filter reading from file
            // -1 -1 -1 
            // 0 0 0 
            // 1 1 1 
            ifstream Neg("D:/designs/negative.txt");
            if (Neg.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Neg >> Filter_Kernel[i][j])) {
                           //
                        }
                    }
                }
            }
            Neg.close(); // Close the file after reading
        }
        
        
       
        vector<vector<int>> temporary;
        temporary.clear();
        temporary.resize(Row, vector<int>(Col, 0));// outline assigning of size
      
        for (int y = 1; y < Row - 1; y++) {
            for (int x = 1; x < Col - 1; x++) {
                float sum = 0.0;

                // Convolution: Multiply and accumulate pixel values based on the filter Filter_Kernel ----- for hashir
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        sum += Data[y + i][x + j] * Filter_Kernel[i + 1][j + 1];// getting kernel fitted into image
                    }
                }
                temporary[y][x] = sum;

            }
        }
        for (int y = 1; y < Row - 1; ++y) {
            for (int x = 1; x < Col - 1; ++x) {
                Data[y][x] = temporary[y][x];// replacing
            }
        }

    }
    void ScaleUp(vector<vector<int>>& Data, int factor) {
        int height = Data.size();// rows
        int width = Data[0].size();//cols

        int scaledH = height * factor;//new rows
        int scaledW = width * factor;// new cols
        // new vector to save img
        vector<vector<int>> scaledData(scaledH, vector<int>(scaledW, 0));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int p = 0; p < factor; p++) {
                    for (int q = 0; q < factor; q++) {
                         scaledData[i * factor + p][j * factor + q] = Data[i][j];// scaling image
                        //row pixel getting bigger] also col one
                    }
                }
            }
        }

        Data = scaledData; // Update the original Data with the scaled-up data
    }


    

    void ScaleDown(vector<vector<int>>& Data, int factor) {
        int height = Data.size();//row
        int width = Data[0].size();//col

        int scaledH = height / factor;//new size of row
        int scaledW = width / factor;//ew size of col for downing

        //vector for replacement
        vector<vector<int>> scaledData(scaledH, vector<int>(scaledW, 0));

        for (int i = 0; i < scaledH; i++) {
            for (int j = 0; j < scaledW; j++) {
                int sum = 0;
                int count = 0;

                // Calculate the boundaries for the current group
                int rowStart = i * factor;
                int rowEnd = min(rowStart + factor, height);
                int colStart = j * factor;
                int colEnd = min(colStart + factor, width);

                // Calculate sum within the current group
                for (int row = rowStart; row < rowEnd; row++) {
                    for (int col = colStart; col < colEnd; col++) {
                        sum += Data[row][col];
                        count++;
                    }
                }

                // Average the sum for the scaled data
                scaledData[i][j] = (count > 0) ? sum / count : 0; // Avoid division by zero
            }
        }

        Data = scaledData; // Update the original Data with the scaled data
    }
    



    //SD not getting called  also SU if i have not deleted yet
    void SD(int factor) {
        ScaleDown(Data, factor);
    }
    void Tobinary() {
        // thresholding technique
        //check if any value if greater than that thres val then make the pixel 1 
        //else 0
        int threshold = 130;
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++) {
                Data[i][j] = (Data[i][j] >= threshold) ? Depth : 0;
            }
        }
    }
    void translateImage( int dx, int dy) {
       int height = Data.size(); // row
        int width = Data[0].size(); // col

        // Create a translated image with extended dimensions
        vector<vector<int>> translatedImage(height + 2 * dy, vector<int>(width + 2 * dx, 185)); // Fill extended area with white (assuming 255 represents white)

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int new_i = i + dy; // Calculate new index for rows
                int new_j = j + dx; // Calculate new index for columns

                // Check if the new position is within the translated image bounds
                if (new_i >= 0 && new_i < height + 2 * dy && new_j >= 0 && new_j < width + 2 * dx) {
                    translatedImage[new_i][new_j] = Data[i][j]; // Fill actual image pixels
                }
            }
        }

        Data = translatedImage; // Update the image data with the translated image
    }
    


    
    void crop(vector<vector<int>>& image, int x, int y, int cropWidth, int cropHeight) {
        int height = image.size();
        int width = image[0].size();

        // Check if the crop region is within the image bounds
        if (x < 0 || y < 0 || x + cropWidth > width || y + cropHeight > height) {
            cout << "Crop region is out of bounds." << endl;
            return;
        }

        vector<vector<int>> croppedImage(cropHeight, vector<int>(cropWidth, 0));

        for (int i = y; i < y + cropHeight; ++i) {
            for (int j = x; j < x + cropWidth; ++j) {
                croppedImage[i - y][j - x] = image[i][j];
            }
        }

        image = croppedImage; // Update the original image with the cropped image
    }
    void CropImage(int x, int y, int cw, int ch)
    {
        crop(Data, x, y, cw, ch);
    }
    void CombineTop(vector<vector<int>>& Data1, vector<vector<int>>& Data2) {
        int h_1 = Data1.size();
        int h_2 = Data2.size();
        int w_1 = Data1[0].size();
        int w_2 = Data2[0].size();

        int sumOFCOls = h_1 + h_2;
        int sumOFROWS = max(w_1, w_2); // Use the maximum width of both images

        vector<vector<int>> Combination(sumOFCOls, vector<int>(sumOFROWS, 0));

        // Copy Data1 to the top section of Combination
        for (int i = 0; i < h_1; ++i) {
            for (int j = 0; j < w_1; ++j) {
                Combination[i][j] = Data1[i][j];
            }
        }

        // Copy Data2 to the bottom section of Combination
        for (int i = 0; i < h_2; ++i) {
            for (int j = 0; j < w_2; ++j) {
                Combination[i + h_1][j] = Data2[i][j]; // Adjust the row index to start after Data1's height
            }
        }

        Data = Combination; // Assign the combined image to Data
    } 
    void CombineSide(vector<vector<int>>& Data1, vector<vector<int>>& Data2) {
        int h_1 = Data1.size();
        int h_2 = Data2.size();
        int w_1 = Data1[0].size();
        int w_2 = Data2[0].size();

        int summationW= w_1 + w_2;
        int summationH = max(h_1, h_2); // Use the maximum width of both images

        vector<vector<int>> Combination(summationH, vector<int>(summationW, 0));

        // Copy Data1 to the top section of Combination
        for (int i = 0; i < h_1; ++i) {
            for (int j = 0; j < w_1; ++j) {
                Combination[i][j] = Data1[i][j];
            }
        }

        // Copy Data2 to the bottom section of Combination
        for (int i = 0; i < h_2; ++i) {
            for (int j = 0; j < w_2; ++j) {
                Combination[i][j+w_1] = Data2[i][j]; // Adjust the row index to start after Data1's height
            }
        }

        Data = Combination; // Assign the combined image to Data
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
    Image Images[2];
    int ActiveImage = 0;
    int tocombine = 1;
    int ErrorCode = 0;
    int choice;
    char menufile[] = "D:/designs/Main.txt";
    char ImageFileName[100];
    bool FileModified = false;
    int saveCheck = 0;

    do {

        choice = Menu(menufile);

            char ImageFileName1[100];
        if (1 == choice) {
            cout << "Specify File Name (format: D:/folder/file)";
            cin >> ImageFileName1;

            ErrorCode = Images[ActiveImage].Load(ImageFileName1);
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
            ErrorCode = Images[ActiveImage].Save(ImageFileName);
            if (ErrorCode == 0) {
                saveCheck++;
                cout << "File Saved as " << ImageFileName << endl;
            }
            else {
                cout << "Save Error: Code " << ErrorCode << endl;
            }
        }
        else if (3 == choice) {
            cout << endl << "Enter to which factor you want to increase Brightness(1 - 5) ";
            int factor;
            cin >> factor;
            if (factor > 5) {
                cout << "Please Enter within or 5" << endl;
                cin >> factor;
            }

            Images[ActiveImage].IncreaseBrightness(factor);
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (4 == choice) {
            Images[ActiveImage].LinearCont();
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }
        else if (5 == choice) {

            Images[ActiveImage].LinearFilter(1);
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (6 == choice) {
            Images[ActiveImage].Tobinary();
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }
        else if (7 == choice) {
            
            cout << endl<<"Enter the size how many time you want to increase: ";
            int multi;
            cin >> multi;
            Images[ActiveImage].ScaleUp(Images[ActiveImage].Data,multi);
            Images[ActiveImage].Row *=multi ;
            Images[ActiveImage].Col *= multi;

            
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (8 == choice) {
            cout << endl << "Enter the size how many time you want to reduce : ";
            int Reducer;
            cin >> Reducer;
            Images[ActiveImage].ScaleDown(Images[ActiveImage].Data,Reducer);
            Images[ActiveImage].Row /= Reducer;
            Images[ActiveImage].Col /= Reducer;
          
            
            
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (9== choice) {
            
            Images[ActiveImage].RotateImageClockwise();
            int temp = Images[ActiveImage].Row;
            Images[ActiveImage].Row = Images[ActiveImage].Col;
            Images[ActiveImage].Col = temp;
            cout << "------------------------You need to save your file--------------------------- " << endl;
        } else if (10 == choice) {
            Images[ActiveImage].RotateImageAntiClockwise();
            int temp = Images[ActiveImage].Row;
            Images[ActiveImage].Row = Images[ActiveImage].Col;
            Images[ActiveImage].Col = temp;
            
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (11 == choice) {
            double angle;
            cout << "enter an angle : ";
            cin >> angle;
            Images[ActiveImage].RotateImageByAngle(angle);
            
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (12 == choice) {
           
            Images[ActiveImage].RHorizontalFlip();
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (13 == choice) {
            int opt = 1;
            Images[ActiveImage].VerticalFlip();
            cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (14 == choice) {
            cout << "Enter the x-axis start of crop ";
            int x;
            cin >> x;
            cout << endl;
            cout << "Enter the y-axis start of crop ";
            int y;
            cin >> y;
            cout << endl;

            cout << "Enter the crop width  ";
            int cw;
            cin >> cw;
            cout << endl;

            cout << "Enter the crop height ";
            int ch;
            cin >> ch;
            cout << endl;
            int checkX = Images[ActiveImage].Row - x;
            int checkY = Images[ActiveImage].Col - y;
            if (cw > checkX || ch > checkY) {
                cout << "-------------- Value Error : Please Enter Values Carefully -------------------" << endl;
            }
            else {

                Images[ActiveImage].Row = cw;
                Images[ActiveImage].Col = ch;
                Images[ActiveImage].CropImage(x, y, cw, ch);

                cout << "------------------------You need to save your file--------------------------- " << endl;
            }
            
            
        } else if (15 == choice) {
            
                cout << "Add path of image to add ";
                char combineloc[200];
                cin >> combineloc;
                Images[tocombine].Load(combineloc);
                Images[ActiveImage].CombineSide(Images[ActiveImage].Data, Images[tocombine].Data);
                
                int x1 = Images[ActiveImage].Data[0].size();
                int x2 = Images[tocombine].Data[0].size();
                
                int x = max(x1, x2);
                
                
                Images[ActiveImage].Row = Images[ActiveImage].Data.size();
                Images[ActiveImage].Col = x;
                
                    cout << "------------------------You need to save your file--------------------------- " << endl;
                

           
        } else if (16 == choice) {
            cout << "Add path of image to add ";
            char combinelocS[200];
            cin >> combinelocS;
            Images[tocombine].Load(combinelocS);
            Images[ActiveImage].CombineTop(Images[ActiveImage].Data, Images[tocombine].Data);

            int x1 = Images[ActiveImage].Data[0].size();
            int x2 = Images[tocombine].Data[0].size();

            int x = max(x1, x2);


            Images[ActiveImage].Row = Images[ActiveImage].Data.size();
            Images[ActiveImage].Col = x;
            
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        } 
        else if (17 == choice) {
            cout << "Enter Blur factor (1-10) ";
            int fct;
            cin >> fct;
            if (fct > 10) {
                cout << "Please Enter within or 10" << endl;
                cin >> fct;
            }
            Images[ActiveImage].Mean((fct*3));
            
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        } 
        else if (18 == choice) {
            
            Images[ActiveImage].Median();
           
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        }
        else if (19 == choice) {
            
            Images[ActiveImage].LinearFilter(1);
            
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        }else if (20 == choice) {
            
            Images[ActiveImage].LinearFilter(2);
            
                cout << "------------------------You need to save your file--------------------------- " << endl;
        }else if (21 == choice) {
            
            Images[ActiveImage].LinearFilter(3);
           
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        }else if (22 == choice) {
            
            Images[ActiveImage].Derivative();
            
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        }else if (23 == choice) {
            
            Images[ActiveImage].LinearFilter(4);
           
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        }else if (24 == choice) {
            cout << "Your image Rows : " << Images[ActiveImage].Row << " " << "Yor Image Columns : " << Images[ActiveImage].Col << endl;
            cout << "Enter Translation X-axis : ";
            int tx;
            cin >> tx;
            cout << endl;
            cout << "Enter Y-axis : ";
            int ty;
            cin >> ty;

            Images[ActiveImage].translateImage(tx,ty);
           
                cout << "------------------------You need to save your file--------------------------- " << endl;
           
        }
        
        else if (25 == choice) {
            if (saveCheck>0) {
               
                system(ImageFileName);
            }
            else
            {
                cout << "You have not saved File yet .";
            }
           
        }

    } while (choice != 26);

    return 0;
}
