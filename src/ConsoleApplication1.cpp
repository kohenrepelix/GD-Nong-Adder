#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleTitleA("Geometry Dash Song Swapper by Sally Aarons#7075");
    string songID;
    cout << "Enter the ID of the song you want to replace: ";
    getline(cin, songID);

    char* localAppData;
    size_t len;
    _dupenv_s(&localAppData, &len, "LOCALAPPDATA");
    string songPath = localAppData;
    songPath += "\\GeometryDash\\";

    string originalFileName = songID + ".mp3";
    string originalFilePath = songPath + originalFileName;

    if (GetFileAttributesA(originalFilePath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        cout << "Could not find a song with ID " << songID << endl;
        return 1;
    }

    string renamedFileName = songID + "OG.mp3";
    string renamedFilePath = songPath + renamedFileName;

    bool restoreOriginalFile = false;
    if (GetFileAttributesA(renamedFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {
        restoreOriginalFile = true;
        cout << "Found existing song with ID " << songID << " and restored the original file." << endl;
    }
    else {
        if (!MoveFileA(originalFilePath.c_str(), renamedFilePath.c_str())) {
            cout << "Error renaming original file: " << GetLastError() << endl;
            return 1;
        }
        cout << "Renamed original song file with ID " << songID << " to " << renamedFileName << endl;
    }

    string replacementPath;
    cout << "Enter the path to the replacement mp3 file: ";
    getline(cin, replacementPath);

    if (GetFileAttributesA(replacementPath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        cout << "Could not find replacement file " << replacementPath << endl;
        return 1;
    }

    string newFilePath = songPath + originalFileName;
    if (!CopyFileA(replacementPath.c_str(), newFilePath.c_str(), FALSE)) {
        cout << "Error replacing song: " << GetLastError() << endl;
        return 1;
    }

    if (restoreOriginalFile) {
        if (!MoveFileExA(renamedFilePath.c_str(), originalFilePath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
            cout << "Error restoring original file: " << GetLastError() << endl;
            return 1;
        }
        cout << "Replaced song with ID " << songID << " and restored the original file." << endl;
    }
    else {
        cout << "Song successfully replaced!" << endl;
    }
    return 0;
}
