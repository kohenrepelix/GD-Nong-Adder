#include <iostream>
#include <string>
#include <Windows.h>
#include <shellapi.h>

using namespace std;

void SetConsoleTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearConsoleScreen()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacterA(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
}


void ReplaceSong()
{
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
        return;
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
            return;
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
        return;
    }

    string newFilePath = songPath + originalFileName;
    if (!CopyFileA(replacementPath.c_str(), newFilePath.c_str(), FALSE)) {
        SetConsoleTextColor(12);
        cout << "Error replacing song: " << GetLastError() << endl;
        return;
    }

    if (restoreOriginalFile) {
        if (!MoveFileExA(renamedFilePath.c_str(), originalFilePath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
            SetConsoleTextColor(12);
            cout << "Error restoring original file: " << GetLastError() << endl;
            return;
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
}

void DownloadSong(const string& url)
{
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    ClearConsoleScreen();
}

void BrowseNongs()
{
    while (true) {
        ClearConsoleScreen();
        SetConsoleTextColor(11);
        cout << "Browsing Nongs" << endl;
        SetConsoleTextColor(15);
        cout << "[1] Rated" << endl;
        cout << "[2] Mashups" << endl;
        cout << "[3] Challenges" << endl;
        cout << "[4] Go back to the main menu" << endl;

        string choice;
        getline(cin, choice);

        if (choice == "4") {
            return;
            }

        if (choice == "1") {
            while (true) {
                ClearConsoleScreen();
                SetConsoleTextColor(11);
                cout << "Browsing Rated Nongs" << endl;
                SetConsoleTextColor(15);
                cout << "[1] Wasureta (Luschka - Kami no Kotoba)" << endl;
                cout << "[2] Unknown (Dom & Roland - Thunder)" << endl;
                cout << "[3] Kowareta (ぬゆり - Fragile)" << endl;
                cout << "[4] Slaughterhouse (Crim3s - Lost (XVA Remix))" << endl;
                cout << "[150] To go back" << endl;

                string ratedChoice;
                getline(cin, ratedChoice);

                if (ratedChoice == "1") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040973770891993158/509162.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (ratedChoice == "2") {
                    DownloadSong("https://cdn.discordapp.com/attachments/899795727268585522/1070439547437060166/1131108.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (ratedChoice == "3") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040917571333005352/758448.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (ratedChoice == "4") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040960197146988634/945695.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (ratedChoice == "BACK") {
                    return;
                }
                else {
                    ClearConsoleScreen();
                    SetConsoleTextColor(12);
                    cout << "Invalid choice. Please try again." << endl;
                    Sleep(1000);
                }
            }
        }
        else if (choice == "2") {
            while (true) {
                ClearConsoleScreen();
                SetConsoleTextColor(11);
                cout << "Browsing Mashup Nongs" << endl;
                SetConsoleTextColor(15);
                cout << "[1] Acheron (djNate - Therodynamix x Flo Rida - Low)" << endl;
                cout << "[2] Cosmic Cyclone (F - 777 - Hydra x IShowSpeed - Shake)" << endl;
                cout << "[3] VSC (Waterflame - Stalker x Maroon 5 - Moves Like Jagger ft.Christina Aguilera)" << endl;
                cout << "[150] To go back" << endl;

                string mashupChoice;
                getline(cin, mashupChoice);

                if (mashupChoice == "1") {
                    DownloadSong("https://cdn.discordapp.com/attachments/1036475805695496297/1119680477587050516/770520.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (mashupChoice == "2") {
                    DownloadSong("https://cdn.discordapp.com/attachments/1036475805695496297/1119681022712369212/725417.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (mashupChoice == "3") {
                    DownloadSong("https://cdn.discordapp.com/attachments/1036475805695496297/1119684284672913489/620959.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (mashupChoice == "150") {
                    return;
                }
                else {
                    ClearConsoleScreen();
                    SetConsoleTextColor(12);
                    cout << "Invalid choice. Please try again." << endl;
                    Sleep(1000);
                }

            }
        }
        else if (choice == "3") {
            while (true) {
                ClearConsoleScreen();
                SetConsoleTextColor(11);
                cout << "Browsing Challenge Nongs" << endl;
                SetConsoleTextColor(15);
                cout << "[1] Final Destination (Tree Palm - Her Name Is ユビンLady)" << endl;
                cout << "[2] Blunder (BobbyBoJanglles - You have to know this (Checkmate in 8))" << endl;
                cout << "[3] Grains of Sand (ANDREW HUANG - 300, 000 NOTE SONG)" << endl;
                cout << "[150] To go back" << endl;

                string challengeChoice;
                getline(cin, challengeChoice);

                if (challengeChoice == "1") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040506190980972595/818027.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (challengeChoice == "2") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1094234338180218931/346.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (challengeChoice == "3") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040773976684769360/664232.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    ReplaceSong();
                    break;
                }
                else if (challengeChoice == "150") {
                    return;
                }
                else {
                    ClearConsoleScreen();
                    SetConsoleTextColor(12);
                    cout << "Invalid choice. Please try again." << endl;
                    Sleep(1000);
                }
            }
        }
        else {
            ClearConsoleScreen();
            SetConsoleTextColor(12);
            cout << "Invalid choice. Please try again." << endl;
            Sleep(1000);
        }

        ClearConsoleScreen();
    }
}

int main()
{
    SetConsoleTitleA("Geometry Dash Song Swapper by Sally Aarons#7075");

    while (true) {
        ClearConsoleScreen();
        SetConsoleTextColor(11);
        cout << "Geometry Dash Song Swapper" << endl;
        SetConsoleTextColor(15);
        cout << "[1] Replace Song with pre-downloaded song" << endl;
        cout << "[2] Browse nongs" << endl;
        cout << "[3] Exit" << endl;

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            ClearConsoleScreen();
            ReplaceSong();
        }
        else if (choice == "2") {
            BrowseNongs();
        }
        else if (choice == "3") {
            ClearConsoleScreen();
            SetConsoleTextColor(14);
            cout << "Exiting the program..." << endl;
            break;
        }
        else {
            ClearConsoleScreen();
            SetConsoleTextColor(12);
            cout << "Invalid choice. Please try again." << endl;
        }

        Sleep(1000);
        ClearConsoleScreen();
    }

    return 0;
}
