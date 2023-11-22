
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
void inputlocation(char Location[])
{
	cout << "Enter the Location of the file" <<
		" for example D:\\folder\\file" << endl;
	cin.getline(Location, 200);
}
void inputDestination(char  destination[])
{
	cout << "Enter the Destination of the file " << endl;
	cin.getline(destination, 200);
}
void getLocations(char location[], char destination[])
{
	do
	{
		inputlocation(location);
		inputDestination(destination);
	} while (strcmp(location, destination) == 0);

}

struct image
{
	int Col, Row, Depth;
	int Data[400][400];
	char Comment[100];
	char MagicNumber[10];
	void Load(char FileLocation[])
	{
		ifstream CIN(FileLocation);
		CIN.getline(MagicNumber, 4);
		for (int i = 0; Comment[i] != '\0'; i++)
		{
			CIN >> Comment[i];
		}
		CIN >> Row >> Col >> Depth;
	}
};

int main()
{
	image IM1, IM2;
	char Location[200], Destination[200];
	getLocations(Location, Destination);
	IM1.Load(Location);

}
