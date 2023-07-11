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

    string renamedFileName = songID + "OG.mp3";
    string renamedFilePath = songPath + renamedFileName;

    bool restoreOriginalFile = false;
    if (GetFileAttributesA(renamedFilePath.c_str()) != INVALID_FILE_ATTRIBUTES) {
        restoreOriginalFile = true;
        SetConsoleTextColor(14);
        cout << "Found existing song with ID " << songID << " and restored the original file." << endl;
    }
    else {
        if (GetFileAttributesA(originalFilePath.c_str()) == INVALID_FILE_ATTRIBUTES) {
            SetConsoleTextColor(12);
            cout << "Couldn't find the original song. Would you like to add the replacement anyway?" << endl;
            cout << "[1] Yes" << endl;
            cout << "[2] No" << endl;
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 2) {
                return;
            }
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
    cout << "Song successfully added. Closing in 3 seconds" << endl;
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
                cout << "[5] Colorful OverNight (Tobu - Colors)" << endl;
                cout << "[6] Delta Interface (Camellia - δ:for the DELTA)" << endl;
                cout << "[7] Doradura (Дора - Дорадура)" << endl;
                cout << "[8] Down Bass (~NK~ DEV - BassDownLow Remix)" << endl;
                cout << "[9] Freedom08 (xi - Freedom Dive)" << endl;
                cout << "[10] High Life (Romos - Magic Touch)" << endl;
                cout << "[11] Killbot (Devin Martin - Killbot (edit))" << endl;
                cout << "[12] Kuzureta (YOASOBI - Racing into the Night)" << endl;
                cout << "[13] Lotus Flower (Radiohead - Lotus Flower)" << endl;
                cout << "[14] Promethean (Inferi - The Promethean Kings)" << endl;
                cout << "[15] Pumped Up Kicks (Foster the People - Pumped Up Kicks (Radio Edit))" << endl;
                cout << "[16] Ragnarok (soclb - Infertehno 2)" << endl;
                cout << "[17] Removed Submission (4cat - All I Do Is Spam (BrokenDiss))" << endl;
                cout << "[18] Superhatemeworld (Marilyn Manson - Resident Evil Main Title Theme)" << endl;
                cout << "[19] The JanuS Miracle (AdvyStyles & others - How to Clutterfunk)" << endl;
                cout << "[20] Triple Six (Jackal Queenston - Cursed)" << endl;
                cout << "[21] Trollmachine (KSLV - Override)" << endl;
                cout << "[22] Troll Level (DJ Zé Pedro - Estrelar)" << endl;
                cout << "[23] Wow (Dustvoxx - Trigger (Zekk remix))" << endl;
                cout << "[24] Xo (aaronmusslewhite - XO (Eden Cover & Remake))" << endl;
                cout << "[150] To go back" << endl;

                string ratedChoice;
                getline(cin, ratedChoice);

                if (ratedChoice == "1") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040973770891993158/509162.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    

                 
                }
                else if (ratedChoice == "2") {
                    DownloadSong("https://cdn.discordapp.com/attachments/899795727268585522/1070439547437060166/1131108.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    break;
                   
                }
                else if (ratedChoice == "3") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040917571333005352/758448.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                   
                      break;
               
                }
                else if (ratedChoice == "4") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040960197146988634/945695.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                   
                    break;
                 
                }
                else if (ratedChoice == "5") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1036232174103445554/604521.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    cout << "Song successfully downloaded! Redirecting to nong installer..." << endl;
                    Sleep(2000);
                    ClearConsoleScreen();
                    break;
                
                }

                else if (ratedChoice == "6") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1036239226422972416/713389.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                  
                    break;
                    
                }
                else if (ratedChoice == "7") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1037016210027597976/1109057.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                
                    break;
                
                }
                else if (ratedChoice == "8") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1034755156702675045/429524.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                
                    break;
             
                }
                else if (ratedChoice == "9") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040762089565847612/735623.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
               
                    break;
          
                }
                else if (ratedChoice == "10") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1036861713737322547/595342.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                
                    break;
            
                }
                else if (ratedChoice == "11") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040917125541412904/464120.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
               
                    break;
        ;
                    }
                else if (ratedChoice == "12") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040918545632079952/1024087.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
               
                    break;
          
                    }
                else if (ratedChoice == "13") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1041081163319627816/861866.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                  
                    break;
    
                    }
                else if (ratedChoice == "14") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1041077884615413780/509014.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                
                    break;

                    }
                else if (ratedChoice == "15") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040944418338914324/627121.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
    
                    break;

                    }
                else if (ratedChoice == "16") {
                        DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040941439871365130/343707.mp3");
                        ClearConsoleScreen();
                        SetConsoleTextColor(14);

                        break;

                        }
                else if (ratedChoice == "17") {
                            DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040946304907493527/691570.mp3");
                            ClearConsoleScreen();
                            SetConsoleTextColor(14);
                            break;
                   
                            }
                else if (ratedChoice == "18") {
                                DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1048837807885533285/1135860.mp3");
                                ClearConsoleScreen();
                                SetConsoleTextColor(14);
                                break;
                            
                                }
                else if (ratedChoice == "19") {
                                    DownloadSong("https://cdn.discordapp.com/attachments/1034605734798835785/1040539911989768290/595773.mp3");
                                    ClearConsoleScreen();
                                    SetConsoleTextColor(14);
                                    break;
                               
                                    }
                else if (ratedChoice == "20") {
                                        DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1098006828295659620/542668.mp3");
                                        ClearConsoleScreen();
                                        SetConsoleTextColor(14);
                                        break;
                                  
                                        }
                else if (ratedChoice == "21") {
                                            DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040969987344580709/1164026.mp3");
                                            ClearConsoleScreen();
                                            SetConsoleTextColor(14);
                                            break;
                                      
                                            }
                else if (ratedChoice == "22") {
                                                DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040969955182657568/500706.mp3");
                                                ClearConsoleScreen();
                                                SetConsoleTextColor(14);
                                                break;
                                           
                                                }
                else if (ratedChoice == "23") {
                                                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040974123138027590/661012.mp3");
                                                    ClearConsoleScreen();
                                                    SetConsoleTextColor(14);
                                                    break;
                                           
                                                    }
                else if (ratedChoice == "24") {
                                                        DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/968938841882898472/766165.mp3");
                                                        ClearConsoleScreen();
                                                        SetConsoleTextColor(14);
                                                        break;
                                              
                                                        }
                else if (ratedChoice == "150") {
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
                    break;
             
                }
                else if (mashupChoice == "2") {
                    DownloadSong("https://cdn.discordapp.com/attachments/1036475805695496297/1119681022712369212/725417.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
            
                }
                else if (mashupChoice == "3") {
                    DownloadSong("https://cdn.discordapp.com/attachments/1036475805695496297/1119684284672913489/620959.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
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
                cout << "[4] Cooks (Still Woozy - Cooks)" << endl;
                cout << "[5] Flutterwonder (Matt R - Flutterwonder)" << endl;
                cout << "[6] Last Resort (AcesToAces - Memory Lane)" << endl;
                cout << "[7] Murder Mitten (I See Stars - Murder Mitten)" << endl;
                cout << "[8] Sadomasochism (無力P - NEXT STAGE)" << endl;
                cout << "[9] The Third Variant (Cyclone - Arcanoid)" << endl;
                cout << "[10] Vsc Verified (Michael Bublé - Haven't Met You Yet)" << endl;
                cout << "[11] Zero Factorial (Bruno E. - A Stranger Thing)" << endl;
                cout << "[150] To go back" << endl;

                string challengeChoice;
                getline(cin, challengeChoice);

                if (challengeChoice == "1") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040506190980972595/818027.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
         
                }
                else if (challengeChoice == "2") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1094234338180218931/346.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
      
                }
                else if (challengeChoice == "3") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1040773976684769360/664232.mp3");
                    ClearConsoleScreen();
                    break;
       
                }
                else if (challengeChoice == "4") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038899016106254367/481793.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
 
                }
                else if (challengeChoice == "5") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038899230963671051/447407.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
 
                }
                else if (challengeChoice == "6") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038899686565744690/673881.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
    
                }
                else if (challengeChoice == "7") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038900456820314243/8800.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
    
                }
                else if (challengeChoice == "8") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038899960739020820/543943.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;

                }
                else if (challengeChoice == "9") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038900983343890512/33.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
                }
                else if (challengeChoice == "10") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1051463813754536026/3333.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);
                    break;
                }
                else if (challengeChoice == "11") {
                    DownloadSong("https://cdn.discordapp.com/attachments/938033986201088020/1038901252177805432/458373.mp3");
                    ClearConsoleScreen();
                    SetConsoleTextColor(14);

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
