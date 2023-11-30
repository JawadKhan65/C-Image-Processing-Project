
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
    void RotateImageAntiClockwise()
    {
        int temp;
        for (int layer = 0; layer < Row / 2; layer++) {
            int first = layer;
            int last = Row - 1 - layer;
            for (int i = first; i < last; i++) {
                int offset = i - first;
                // Save top
                temp = Data[i][first];
                // Left -> Top
                Data[i][first] = Data[first][last - offset];
                // Bottom -> Left
                Data[first][last - offset] = Data[last-offset][last];
                // Right -> Bottom
                Data[last - offset][last] = Data[last][i];
                // Top -> Right
                Data[last][i] = temp;
            }
        }
    }
    
    void RotateImageByAngle(double angle) {
        const double PI = 3.141519;
        double radians = angle * PI / 180.0; // Convert angle to radians
        double cosine = cos(radians);
        double sine = sin(radians);

        // Create a temporary matrix to store rotated values
        int** rotatedData = new int* [Row];
        for (int i = 0; i < Row; i++) {
            rotatedData[i] = new int[Col];
        }

        // Find the center of the image
        double cx = static_cast<double>(Col - 1) / 2.0;
        double cy = static_cast<double>(Row - 1) / 2.0;

        // Traverse the original matrix and apply rotation
        for (int y = 0; y < Row; y++) {
            for (int x = 0; x < Col; x++) {
                // Translate coordinates to the center
                double xFromCenter = x - cx;
                double yFromCenter = y - cy;

                // Apply rotation formula
                double newX = xFromCenter * cosine - yFromCenter * sine + cx;
                double newY = xFromCenter * sine + yFromCenter * cosine + cy;

                // Check bounds and assign values to the temporary matrix
                if (newX >= 0 && newX < Col && newY >= 0 && newY < Row) {
                    rotatedData[static_cast<int>(newY)][static_cast<int>(newX)] = Data[y][x];
                }
            }
        }

        // Copy rotated data back to the original matrix
        for (int y = 0; y < Row; ++y) {
            for (int x = 0; x < Col; ++x) {
                Data[y][x] = rotatedData[y][x];
            }
        }

        // Deallocate temporary matrix
        for (int i = 0; i < Row; ++i) {
            delete[] rotatedData[i];
        }
        delete[] rotatedData;
    }
    // Assuming ImageData represents the image as a 2D array

// Apply a general linear filter to the image
    void LinearFilter(int input) {
        
        double kernel[3][3];
        
        if (input == 1 )
        {
            ifstream Sharpen("D:/designs/sharpen.txt");
            if (Sharpen.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Sharpen >> kernel[i][j])) {
                            // Handle the case where there are not enough values in the file
                            // Or an error occurs while reading from the file
                            // This might involve breaking out of the loop or handling the error accordingly
                        }
                    }
                }
            }
            Sharpen.close(); // Close the file after reading
        }
        else if (input == 2 )
        {
            ifstream Blur("D:/designs/blur.txt");
            if (Blur.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Blur >> kernel[i][j])) {
                            // Handle the case where there are not enough values in the file
                            // Or an error occurs while reading from the file
                            // This might involve breaking out of the loop or handling the error accordingly
                        }
                    }
                }
            }
            Blur.close(); // Close the file after reading
        }else if (input == 3 )
        {
            ifstream Edge("D:/designs/edge.txt");
            if (Edge.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Edge >> kernel[i][j])) {
                            // Handle the case where there are not enough values in the file
                            // Or an error occurs while reading from the file
                            // This might involve breaking out of the loop or handling the error accordingly
                        }
                    }
                }
            }
            Edge.close(); // Close the file after reading
        }else if (input == 4 )
        {
            ifstream Neg("D:/designs/negative.txt");
            if (Neg.is_open()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (!(Neg >> kernel[i][j])) {
                            // Handle the case where there are not enough values in the file
                            // Or an error occurs while reading from the file
                            // This might involve breaking out of the loop or handling the error accordingly
                        }
                    }
                }
            }
            Neg.close(); // Close the file after reading
        }
        
        
        // Printing the contents of the kernel array
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << kernel[i][j] << " ";
            }
            cout << endl;
        }
        vector<vector<int>> temporary;
        temporary.clear();
        temporary.resize(Row, vector<int>(Col, 0));
      
        for (int y = 1; y < Row - 1; y++) {
            for (int x = 1; x < Col - 1; x++) {
                float sum = 0.0;

                // Convolution: Multiply and accumulate pixel values based on the filter kernel
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        sum += Data[y + i][x + j] * kernel[i + 1][j + 1];
                    }
                }
                temporary[y][x] = sum;

            }
        }
        for (int y = 1; y < Row - 1; ++y) {
            for (int x = 1; x < Col - 1; ++x) {
                Data[y][x] = temporary[y][x];
            }
        }

    }
    void ScaleUp(vector<vector<int>>& Data, int factor) {
        int height = Data.size();
        int width = Data[0].size();

        int scaledH = height * factor;
        int scaledW = width * factor;

        vector<vector<int>> scaledData(scaledH, vector<int>(scaledW, 0));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int p = 0; p < factor; p++) {
                    for (int q = 0; q < factor; q++) {
                        scaledData[i * factor + p][j * factor + q] = Data[i][j];
                    }
                }
            }
        }

        Data = scaledData; // Update the original Data with the scaled-up data
    }

    void ScaleDown(vector<vector<int>>& Data, int factor) {
        int height = Data.size();
        int width = Data[0].size();

        int scaledH = height / factor;
        int scaledW = width / factor;

        vector<vector<int>> scaledData(scaledH, vector<int>(scaledW, 0));

        for (int i = 0; i < scaledH; i++) {
            for (int j = 0; j < scaledW; j++) {
                int sum = 0;
                for (int k = 0; k < factor; k++) {
                    for (int l = 0; l < factor; l++) {
                        sum += Data[i * factor + k][j * factor + l];
                    }
                }
                scaledData[i][j] = sum / (factor * factor);
            }
        }

        Data = scaledData; // Update the original Data with the scaled data
    }
   
    void SD(int factor) {
        ScaleDown(Data, factor);
    }
    void SU(int factor) {
        ScaleUp(Data, factor);
    }
    void Tobinary() {
        // thresholding technique
        int threshold = 130;
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++) {
                Data[i][j] = (Data[i][j] > threshold) ? 1 : 0;
            }
        }
    }
    void TI(vector<vector<int>>& Data, int dx, int dy) {
        int height = Data.size();
        int width = Data[0].size();

        vector<vector<int>> translatedImage(height, vector<int>(width, 0));

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int new_i = i + dy;
                int new_j = j + dx;

                // Check if the new position is within the image bounds
                if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width) {
                    translatedImage[new_i][new_j] = Data[i][j];
                }
            }
        }

        Data = translatedImage; // Update the original image with the translated image
    }
    void translateImage(int dx, int dy) {
        TI(Data, dx, dy);
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
            cout << "You need to save the changes " << endl;
        }else if (4 == choice) {
            Images[ActiveImage].LinearCont();
            cout << "You need to save the changes " << endl;
        }
        else if (5 == choice) {

            Images[ActiveImage].LinearFilter(1);
            cout << "You need to save the changes " << endl;
        }else if (6 == choice) {
            Images[ActiveImage].Tobinary();
            cout << "You need to save the changes " << endl;
        }
        else if (7 == choice) {
            /*int ratio;
            cout << "Enter Ratio for blur e.g 1X =3 , 2X = 4" << endl;
            cin >> ratio;
            Images[ActiveImage].Mean(ratio);*/
            cout << endl<<"Enter the size how many time you want to increase: ";
            int multi;
            cin >> multi;
            Images[ActiveImage].SU(multi);
            cout << "You need to save the changes " << endl;
        }else if (8 == choice) {
            cout << endl << "Enter the size how many time you want to increase: ";
            int Reducer;
            cin >> Reducer;
            Images[ActiveImage].SD(Reducer);
            
            cout << "You need to save the changes " << endl;
        }else if (9== choice) {
            
            Images[ActiveImage].RotateImageClockwise();
            cout << "You need to save the changes " << endl;
        } else if (10 == choice) {
            Images[ActiveImage].RotateImageAntiClockwise();
            
            cout << "You need to save the changes " << endl;
        }else if (11 == choice) {
            double angle;
            cout << "enter an angle : ";
            cin >> angle;
            Images[ActiveImage].RotateImageByAngle(angle);
            
            cout << "You need to save the changes " << endl;
        }else if (12 == choice) {
           
            Images[ActiveImage].RHorizontalFlip();
            cout << "You need to save the changes " << endl;
        }else if (13 == choice) {
            int opt = 1;
            Images[ActiveImage].VerticalFlip();
            cout << "You need to save the changes " << endl;
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


            Images[ActiveImage].Row = cw;
            Images[ActiveImage].Col = ch;
            Images[ActiveImage].CropImage(x,y,cw,ch);
            
            cout << "You need to save the changes " << endl;
        } else if (15 == choice) {
            if (saveCheck > 0) {
                cout << Images[ActiveImage].Col << endl;
                cout << Images[ActiveImage].Row;
                system(ImageFileName);
            }
            else
            {
                cout << "You have not saved File yet .";
            }
           
        } else if (16 == choice) {
            if (saveCheck > 0) {
                cout << Images[ActiveImage].Col << endl;
                cout << Images[ActiveImage].Row;
                system(ImageFileName);
            }
            else
            {
                cout << "You have not saved File yet .";
            }
           
        } 
        else if (17 == choice) {
            cout << "Enter Blur factor (1X = 3, 2X = 6 ... 10X = 30) ";
            int fct;
            cin >> fct;
            Images[ActiveImage].Mean(fct);
           
        } 
        else if (18 == choice) {
            
            Images[ActiveImage].Median();
           
        }
        else if (19 == choice) {
            
            Images[ActiveImage].LinearFilter(1);
           
        }else if (20 == choice) {
            
            Images[ActiveImage].LinearFilter(2);
           
        }else if (21 == choice) {
            
            Images[ActiveImage].LinearFilter(3);
           
        }else if (22 == choice) {
            
            Images[ActiveImage].Derivative();
           
        }else if (23 == choice) {
            
            Images[ActiveImage].LinearFilter(4);
           
        }else if (24 == choice) {
            cout << "Enter Translation X-axis : ";
            int tx;
            cin >> tx;
            cout << endl;
            cout << "Enter Y-axis : ";
            int ty;
            cin >> ty;

            Images[ActiveImage].translateImage(tx,ty);
           
        }
        
        else if (25 == choice) {
            if (saveCheck > 0) {
                cout << Images[ActiveImage].Col << endl;
                cout << Images[ActiveImage].Row;
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
