#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Direction: 0 -> East, 1 -> South, 2 -> West, 3 -> North
void getAllPath(vector<vector<int>> &board, int x, int y, int specialCastleX, int specialCastleY,
                vector<string> currPath, vector<vector<string>> &allPaths, int direction)
{
    // Check if the current position is valid or not
    if (x < 0 || y < 0 || x >= 9 || y >= 9 || board[y][x] == -1)
    {
        return;
    }
    cout << currPath.size() << endl;
    // Check if the current position is the special castle
    if (x == specialCastleX && y == specialCastleY && currPath.size() > 1)
    {

        currPath.push_back("Go home to (" + to_string(x + 1) + "," + to_string(y + 1) + ")");
        allPaths.push_back(currPath);
        return;
    }

    int newX = x, newY = y;

    // Move in the current direction
    switch (direction)
    {
    case 0:
        newY++;
        break; // East
    case 1:
        newX++;
        break; // South
    case 2:
        newY--;
        break; // West
    case 3:
        newX--;
        break; // North
    }

    // Try to move forward
    if (newX >= 0 && newX < 9 && newY >= 0 && newY < 9)
    {
        if (board[newY][newX] == 1)
        {
            // Kill and turn left
            board[newY][newX] = -1; // Mark as visited
            currPath.push_back("Kill at (" + to_string(newX + 1) + "," + to_string(newY + 1) + "), then turn left");
            getAllPath(board, newX, newY, specialCastleX, specialCastleY, currPath, allPaths, (direction + 3) % 4);
            currPath.pop_back();
            board[newY][newX] = 1; // Unmark as visited

            // Try jumping
            int jumpX = x, jumpY = y;
            while (true)
            {
                switch (direction)
                {
                case 0:
                    jumpY++;
                    break; // East
                case 1:
                    jumpX++;
                    break; // South
                case 2:
                    jumpY--;
                    break; // West
                case 3:
                    jumpX--;
                    break; // North
                }
                if (jumpX < 0 || jumpX >= 9 || jumpY < 0 || jumpY >= 9 || board[jumpY][jumpX] == 1)
                {
                    break;
                }
            }
            if (jumpX >= 0 && jumpX < 9 && jumpY >= 0 && jumpY < 9)
            {
                currPath.push_back("Jump over to (" + to_string(jumpX + 1) + "," + to_string(jumpY + 1) + ")");
                getAllPath(board, jumpX, jumpY, specialCastleX, specialCastleY, currPath, allPaths, direction);
                currPath.pop_back();
            }
        }
        else
        {
            // Move forward without killing
            currPath.push_back("Move to (" + to_string(newX + 1) + "," + to_string(newY + 1) + ")");
            getAllPath(board, newX, newY, specialCastleX, specialCastleY, currPath, allPaths, direction);
            currPath.pop_back();
        }
    }
}

int main()
{
    // input

    // Create 9x9 chessboard
    vector<vector<int>> board(9, vector<int>(9, 0));

    // Input the number of soldiers
    cout << "Enter the number of soldiers: ";
    int noOfSoldiers;
    cin >> noOfSoldiers;

    if (noOfSoldiers > 9 * 9)
    {
        cout << "Invalid number of soldiers" << endl;
        return 0;
    }

    // Input the soldiers' positions
    for (int i = 1; i <= noOfSoldiers; i++)
    {
        cout << "Enter the position of soldier " << i << " (format: x y): ";
        int x, y;
        cin >> x >> y;
        board[y - 1][x - 1] = 1; // 1 indicates a soldier
    }

    // Input the special castle coordinates
    cout << "Enter the coordinates for your special castle (format: x y): ";
    int specialCastleX, specialCastleY;
    cin >> specialCastleX >> specialCastleY;
    specialCastleY--;
    specialCastleX--;
    board[specialCastleY][specialCastleX] = 2; // 2 indicates the special castle

    vector<vector<string>> allPaths;
    vector<string> currPath;

    // Start searching from the special castle with initial direction East (0)
    getAllPath(board, specialCastleX, specialCastleY, specialCastleX, specialCastleY, currPath, allPaths, 0);

    // Output the paths
    cout << "Found " << allPaths.size() << " paths." << endl;
    for (int i = 0; i < allPaths.size(); ++i)
    {
        cout << "Path " << (i + 1) << ":" << endl;
        cout << "=======" << endl;
        for (const string &step : allPaths[i])
        {
            cout << step << endl;
        }
        cout << endl;
    }

    return 0;
}
