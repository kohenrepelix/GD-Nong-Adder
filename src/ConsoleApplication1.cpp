#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;


void SetConsoleTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
    SetConsoleTitleA("Geometry Dash Song Swapper by Sally Aarons#7075");

    SetConsoleTextColor(11); 
    cout << "Enter the ID of the song you want to replace: ";
    SetConsoleTextColor(15); 
    string songID;
    getline(cin, songID);

    char* localAppData;
    size_t len;
    _dupenv_s(&localAppData, &len, "LOCALAPPDATA");
    string songPath = localAppData;
    songPath += "\\GeometryDash\\";

    string originalFileName = songID + ".mp3";
    string originalFilePath = songPath + originalFileName;

    if (GetFileAttributesA(originalFilePath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        SetConsoleTextColor(12);
        cout << "Could not find a song with ID " << songID << endl;
        return 1;
    }


    string renamedFileName = songID + "OG.mp3";
    string renamedFilePath = songPath + renamedFileName;

    bool restoreOriginalFile = false;
    if (GetFileAttributesA(renamedFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {
        restoreOriginalFile = true;
        SetConsoleTextColor(14); 
        cout << "Found existing song with ID " << songID << " and restored the original file." << endl;
    }
    else {
        if (!MoveFileA(originalFilePath.c_str(), renamedFilePath.c_str())) {
            SetConsoleTextColor(12); 
            cout << "Error renaming original file: " << GetLastError() << endl;
            return 1;
        }
        SetConsoleTextColor(10);
        cout << "Renamed original song file with ID " << songID << " to " << renamedFileName << endl;
    }

    SetConsoleTextColor(11);
    cout << "Enter the path to the replacement mp3 file: ";
    SetConsoleTextColor(15);
    string replacementPath;
    getline(cin, replacementPath);


    if (GetFileAttributesA(replacementPath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        SetConsoleTextColor(12); 
        cout << "Could not find replacement file " << replacementPath << endl;
        return 1;
    }


    string newFilePath = songPath + originalFileName;
    if (!CopyFileA(replacementPath.c_str(), newFilePath.c_str(), FALSE)) {
        SetConsoleTextColor(12); 
        cout << "Error replacing song: " << GetLastError() << endl;
        return 1;
    }

    if (restoreOriginalFile) {
        if (!MoveFileExA(renamedFilePath.c_str(), originalFilePath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
            SetConsoleTextColor(12); 
            cout << "Error restoring original file: " << GetLastError() << endl;
            return 1;
        }
        SetConsoleTextColor(14);
        cout << "Replaced song with ID " << songID << " and restored the original file." << endl;
    }
    else {
        SetConsoleTextColor(10);
        cout << "Song successfully replaced!" << endl;
    }

    SetConsoleTextColor(14);
    cout << "Nong successfully added. Closing in 3 seconds" << endl;
    Sleep(3000);

    return 0;
}
