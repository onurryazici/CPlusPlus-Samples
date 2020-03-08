#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;



class Space {
    class Box {
    public:
        class coord {
        public:
            int x;
            int y;
        };
        coord coordination;
        double density = 1;
        double width;
        double height;
        double boxNumber;
        double weight;

        int xStart;
        int xEnd;
        int yStart;
        int yEnd;

        double xCenter;
        double yCenter;
        bool filled;
    };

public:
    Space** spaceObject; // For 2D space
    Space();
    Space(int x, int y)
    {
        maxX = x + 1;
        maxY = y + 1;
        filled = false;

        // Allocating space for 2x2 matrix
        spaceObject = (Space**)malloc(this->maxY * sizeof(Space*));
        for (int i = 0; i < this->maxY; i++)
        {
            spaceObject[i] = (Space*)malloc(this->maxX * sizeof(Space));
        }
        initializeNonFillSpace();


    }
    Box box;
    bool filled = false;
    int boxFlag;
    vector<Space::Box> BoxInfoVector;

    // Space's methods /////////////////////////////////////////////////////////
    void fillRandomBox(int amountOfBox, int maxBoxSize, int boxDensity);
    void printBoxCoordinates();
    void printCenterOfMass();
    void fillCoordinates(int xStart, int xEnd, int yStart, int yEnd, int boxNumber);
    void initializeNonFillSpace();
    void printToFile();
    ////////////////////////////////////////////////////////////////////////////
private:
    int maxX, maxY;
    int getRandomNumber(int maxNumber);
    bool isItCanBeFill(int width, int height, int boxIndex, int x, int y);
};

void Space::printCenterOfMass()
{
    double xCenterOfMass;
    double yCenterOfMass;
    double temp = 0;
    double totalWeight = 0;
    for (int i = 0; i < BoxInfoVector.size(); i++)
    {
        if (BoxInfoVector.at(i).filled == true)
        {
            temp += (double)(BoxInfoVector.at(i).weight) * (double)(BoxInfoVector.at(i).xCenter);
            totalWeight += BoxInfoVector.at(i).weight;
        }
    }

    cout << "According to X :" << (double)(temp / totalWeight) << endl;

    temp = 0;
    totalWeight = 0;
    for (int i = 0; i < BoxInfoVector.size(); i++)
    {
        if (BoxInfoVector.at(i).filled == true)
        {
            temp += (double)(BoxInfoVector.at(i).weight) * (double)(BoxInfoVector.at(i).yCenter);
            totalWeight += BoxInfoVector.at(i).weight;
        }
    }
    cout << "According to Y :" << (double)(temp / totalWeight) << endl;
}

void Space::printBoxCoordinates()
{
    ofstream output("output.txt");
    output << "Object of settled on space.. " << endl;
    for (int k = maxY - 1; k >= 0; k--)
    {
        for (int m = 0; m < maxX; m++)
        {
            output << spaceObject[m][k].boxFlag << "<" << m << "," << k << ">" << "\t";
        }
        output << endl;
    }

    cout << "Status of objects to be settled in space:" << endl;
    for (int i = 0; i < BoxInfoVector.size(); i++)
    {
        if (BoxInfoVector.at(i).filled)
        {
            cout << "Box number \t:" << BoxInfoVector.at(i).boxNumber << endl;
            cout << "Width \t\t:" << BoxInfoVector.at(i).width << endl;
            cout << "Height \t\t:" << BoxInfoVector.at(i).height << endl;
            cout << "Start Point \t:" << "<" << BoxInfoVector.at(i).xStart << "," << BoxInfoVector.at(i).yStart << ">" << endl;
            cout << "End Point \t:" << "<" << BoxInfoVector.at(i).yStart << "," << BoxInfoVector.at(i).yEnd << ">" << endl;
            cout << "State \t\t: Settled" << endl << endl;
        }
        else
        {
            cout << "Box number \t:" << BoxInfoVector.at(i).boxNumber << endl;
            cout << "Width \t\t:" << BoxInfoVector.at(i).width << endl;
            cout << "Height \t\t:" << BoxInfoVector.at(i).height << endl;
            cout << "State \t\t: Unable to settle" << endl << endl;
        }
    }

    cout << "Box number format will be shown as : <x,y> " << endl << endl;
    for (int k = maxY - 1; k >= 0; k--)
    {
        cout << k << " " << "-|" << " " << "\t";
        for (int m = 0; m < maxX; m++)
        {
            cout << spaceObject[m][k].boxFlag << "<" << m << "," << k << ">" << "\t";
        }
        cout << endl;
    }
}

void Space::initializeNonFillSpace()
{
    for (int x = 0; x < maxX; x++)
    {
        for (int y = 0; y < maxY; y++)
        {
            spaceObject[x][y].filled = false;
            spaceObject[x][y].boxFlag = 0;
        }
    }
}

int Space::getRandomNumber(int maxNumber)
{
    return ((rand() % (maxNumber)) + 1);
}

void Space::fillRandomBox(int amountOfBox, int maxBoxSize, int boxDensity)
{
    bool filled = false;
    for (int boxNumber = 0; boxNumber < amountOfBox; boxNumber++)
    {
        int width;
        int height;
        do
        {
            width = getRandomNumber(maxBoxSize);
            height = getRandomNumber(maxBoxSize);
        } while ((width * height) > (maxX * maxY));
        //cout << "width " << width << " height " << height << "box " <<boxNumber+1 << endl;

        for (int x = 0; x <= this->maxX; x++)
        {
            for (int y = 0; y <= this->maxY; y++)
            {
                if (isItCanBeFill(width, height, boxNumber, x, y))
                {
                    fillCoordinates(x, x + width, y, y + height, boxNumber + 1);
                    filled = true;
                    x = maxX;
                    y = maxY;
                }
                else
                {
                    filled = false;
                }
            }
        }

        if (filled != true)
        {
            Space::Box box;
            box.boxNumber = boxNumber;
            box.width = width;
            box.height = height;
            box.weight = width * height;
            box.filled = false;
            BoxInfoVector.push_back(box);
        }
        /*for(int k=maxY-1; k>=0;k--)
        {

            for(int m=0; m<maxX; m++)
            {

                cout << spaceObject[m][k].boxFlag << "<" << m <<"," << k <<">"<< "\t";
            }
            cout << endl;
        }*/
    }
}


bool Space::isItCanBeFill(int width, int height, int boxIndex, int x, int y)
{
    bool result = true;

    if ((x + width) < maxX && (y + height) < maxY)
    {
        for (int w = x; w <= (x + width); w++)
        {
            for (int h = y; h <= (y + height); h++)
            {
                if (spaceObject[w][h].filled)
                {
                    result = false;
                    return false;
                }
            }
        }
    }
    else
    {
        result = false;
    }
    return result;
}
void Space::fillCoordinates(int xStart, int xEnd, int yStart, int yEnd, int boxNumber)
{
    if (xEnd < this->maxX && yEnd < this->maxY)
    {
        for (int yy = yStart; yy <= yEnd; yy++)
        {
            for (int xx = xStart; xx <= xEnd; xx++)
            {
                spaceObject[xx][yy].box.width = xEnd - xStart;
                spaceObject[xx][yy].box.height = yEnd - yStart;
                spaceObject[xx][yy].box.coordination.x = xx;
                spaceObject[xx][yy].box.coordination.y = yy;
                spaceObject[xx][yy].filled = true;
                spaceObject[xx][yy].boxFlag = boxNumber;
            }
        }
    }

    Space::Box box;
    box.width = (xEnd - xStart);
    box.height = (yEnd - yStart);
    box.filled = true;
    box.boxNumber = boxNumber;
    box.weight = (xEnd - xStart) * (yEnd - yStart);
    box.xStart = xStart;
    box.xEnd = xEnd;
    box.yStart = yStart;
    box.yEnd = yEnd;
    box.xCenter = double(xStart + (double)((box.width) / 2.0));
    box.yCenter = double(yStart + (double)((box.height) / 2.0));
    BoxInfoVector.push_back(box);
}

int main()
{
    setlocale(LC_ALL, "turkish");
    srand(time(0)); // for different random numbers
    Space sp(5, 5);
    sp.fillRandomBox(10, 3, 1);
    sp.printBoxCoordinates();
    sp.printCenterOfMass();

    cout << endl;
    system("pause");
}
