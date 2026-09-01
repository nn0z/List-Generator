#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void loadingAnimation() {
    cout << "\nProcessing";
    for(int i=0; i<3; i++) {
        cout << ".";
        Sleep(500);
    }
    cout << endl;
}

bool fileExists(const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

bool canWrite(const string& path) {
    ofstream test((path + "test.txt").c_str(), ios::app);
    bool can = test.good();
    test.close();
    return can;
}

int getValidNumber(string prompt) {
    int num;
    while(true) {
        cout << prompt;
        cin >> num;
        if(cin.fail() || num < 1) {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(12);
            cout << "Invalid input! Please enter a positive number." << endl;
            setColor(7);
        } else {
            break;
        }
    }
    return num;
}

string generateStrongPassword(int length) {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";
    string password = "";
    for(int i=0; i<length; i++) {
        password += chars[rand() % chars.length()];
    }
    return password;
}

string intToString(int num) {
    ostringstream ss;
    ss << num;
    return ss.str();
}

void showStatistics(int count, string type, string filepath) {
    cout << "\n========== STATISTICS ==========" << endl;
    setColor(10);
    cout << "Total Entries Generated: " << count << endl;
    cout << "Type: " << type << endl;
    cout << "File Location: " << filepath << endl;
    setColor(7);
    cout << "=================================" << endl;
}

vector<string> removeDuplicates(vector<string> vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    return vec;
}

int countEntries(const string& filename) {
    ifstream file(filename.c_str());
    if(!file) return 0;
    string line;
    int count = 0;
    while(getline(file, line)) {
        if(!line.empty()) {
            count++;
        }
    }
    file.close();
    return count;
}

int main()
{
    srand(time(0));
    
    int i=0;
    int j=0;
    int re;
    int cho;
    int user_size;
    string domain;
    string pass;
    string filename;
    string currentFilePath = "";
    string random = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789!@#$%&";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    while(true) {
        cout << "" << endl;
        setColor(7);
        cout << "        +-+-+-+--+-+--+-+" << endl;
        setColor(14);
        cout << "        | I N F E R N O |" << endl;
        setColor(7);
        cout << "        +-+-+-+--+-+--+-+" << endl;
        cout << "-----------------------------------" << endl;
        setColor(11);
        cout << "[1] Create Email With Passwords" << endl;
        cout << "[2] Create Email Without Passwords" << endl;
        cout << "[3] Create User With Passwords" << endl;
        cout << "[4] Create User without Passwords" << endl;
        cout << "[5] Add Passwords To a Custom List" << endl;
        setColor(13);
        cout << "[6] Generate Random Passwords Only" << endl;
        cout << "[7] Merge Two Lists" << endl;
        cout << "[8] Remove Duplicates From List" << endl;
        cout << "[9] Search For Specific Entry" << endl;
        cout << "[10] Count Entries In File" << endl;
        cout << "[11] Export To CSV Format" << endl;
        cout << "[12] Clear Screen & Start Over" << endl;
        setColor(12);
        cout << "[13] Exit Program" << endl;
        setColor(7);
        cout << "[?]-> ";
        cin >> cho;
        
        cin.ignore(1000, '\n');
        
        if(cho >= 1 && cho <= 6) {
            cout << "Enter the filename to save (without extension): ";
            getline(cin, filename);
            
            cout << "\nSave Location:" << endl;
            cout << "[1] Downloads Folder" << endl;
            cout << "[2] Desktop Folder" << endl;
            cout << "[3] Custom Path" << endl;
            cout << "Choose (1-3): ";
            int location;
            cin >> location;
            cin.ignore(1000, '\n');
            
            string basePath;
            
            switch(location) {
                case 1:
                    basePath = "C:\\Users\\" + string(getenv("USERNAME")) + "\\Downloads\\";
                    break;
                case 2:
                    basePath = "C:\\Users\\" + string(getenv("USERNAME")) + "\\Desktop\\";
                    break;
                case 3:
                    cout << "Enter full path (e.g., D:\\MyFiles\\): ";
                    getline(cin, basePath);
                    if(basePath[basePath.length()-1] != '\\') basePath += '\\';
                    break;
                default:
                    basePath = "C:\\Users\\" + string(getenv("USERNAME")) + "\\Downloads\\";
            }
            
            string fullPath = basePath + filename + ".txt";
            
            if(!canWrite(basePath)) {
                setColor(12);
                cout << "No write permission in this directory!" << endl;
                setColor(7);
                continue;
            }
            
            if(fileExists(fullPath)) {
                cout << "\nFile exists! What to do?" << endl;
                cout << "[1] Overwrite (delete old)" << endl;
                cout << "[2] Append (add to end)" << endl;
                cout << "[3] Create backup & overwrite" << endl;
                cout << "[4] Cancel" << endl;
                cout << "Choose (1-4): ";
                int fileAction;
                cin >> fileAction;
                cin.ignore(1000, '\n');
                
                if(fileAction == 4) {
                    setColor(10);
                    cout << "Operation cancelled." << endl;
                    setColor(7);
                    continue;
                }
                
                if(fileAction == 3) {
                    string backupPath = fullPath + ".backup";
                    ifstream src(fullPath.c_str());
                    ofstream dst(backupPath.c_str());
                    if(src && dst) {
                        dst << src.rdbuf();
                        setColor(10);
                        cout << "Backup created: " << backupPath << endl;
                        setColor(7);
                    }
                    src.close();
                    dst.close();
                }
            }
            
            currentFilePath = fullPath;
            
            switch(cho)
            {
                case 1:
                {
                    ofstream file(fullPath.c_str(), ios::trunc);
                    if(!file) {
                        setColor(12);
                        cout << " Failed To Open The File !" << endl;
                        setColor(7);
                        continue;
                    }
                    
                    cout << "[" << cho << "] Enter The Domain [gmail, hotmail, outlook]: ";
                    cin >> domain;
                    
                    re = getValidNumber("[" + intToString(cho) + "] Enter The Size of List: ");
                    
                    cout << "[" << cho << "] Enter The Password (or 'random' for auto-generate): ";
                    cin >> pass;
                    if(pass == "random") {
                        int passLen = getValidNumber("Enter password length (default 8): ");
                        if(passLen < 1) passLen = 8;
                        pass = generateStrongPassword(passLen);
                        setColor(10);
                        cout << "Generated password: " << pass << endl;
                        setColor(7);
                    }
                    
                    loadingAnimation();
                    
                    for(i=0; i<re; i++) {
                        int length = random.length();
                        char randomchar1 = random[rand() % length];
                        char randomchar2 = random[rand() % length];
                        char randomchar3 = random[rand() % length];
                        char randomchar4 = random[rand() % length];
                        file << randomchar1 << randomchar2 << randomchar3 << randomchar4 
                             << "@" << domain << ".com:" << pass << endl;
                    }
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Saved to: " << fullPath << endl;
                    showStatistics(re, "Email with Passwords", fullPath);
                    file.close();
                    break;
                }
                
                case 2:
                {
                    ofstream file(fullPath.c_str(), ios::trunc);
                    if(!file) {
                        setColor(12);
                        cout << " Failed To Open The File !" << endl;
                        setColor(7);
                        continue;
                    }
                    
                    cout << "[" << cho << "] Enter The Domain [gmail, hotmail, outlook]: ";
                    cin >> domain;
                    
                    re = getValidNumber("[" + intToString(cho) + "] Enter The Size of List: ");
                    
                    loadingAnimation();
                    
                    for(i=0; i<re; i++) {
                        int length = random.length();
                        char randomchar1 = random[rand() % length];
                        char randomchar2 = random[rand() % length];
                        char randomchar3 = random[rand() % length];
                        char randomchar4 = random[rand() % length];
                        file << randomchar1 << randomchar2 << randomchar3 << randomchar4 
                             << "@" << domain << ".com" << endl;
                    }
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Saved to: " << fullPath << endl;
                    showStatistics(re, "Email without Passwords", fullPath);
                    file.close();
                    break;
                }
                
                case 3:
                {
                    ofstream file(fullPath.c_str(), ios::trunc);
                    if(!file) {
                        setColor(12);
                        cout << " Failed To Open The File !" << endl;
                        setColor(7);
                        continue;
                    }
                    
                    user_size = getValidNumber("[" + intToString(cho) + "] Enter The Size of User (2-5): ");
                    if(user_size < 2 || user_size > 5) {
                        setColor(12);
                        cout << "Invalid size! Using default (4)" << endl;
                        setColor(7);
                        user_size = 4;
                    }
                    
                    re = getValidNumber("[" + intToString(cho) + "] Enter The Size of List: ");
                    
                    cout << "[" << cho << "] Enter The Password (or 'random' for auto-generate): ";
                    cin >> pass;
                    if(pass == "random") {
                        int passLen = getValidNumber("Enter password length (default 8): ");
                        if(passLen < 1) passLen = 8;
                        pass = generateStrongPassword(passLen);
                        setColor(10);
                        cout << "Generated password: " << pass << endl;
                        setColor(7);
                    }
                    
                    loadingAnimation();
                    
                    for(i=0; i<re; i++) {
                        string username = "";
                        for(j=0; j<user_size; j++) {
                            username += random[rand() % random.length()];
                        }
                        file << username << ":" << pass << endl;
                    }
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Saved to: " << fullPath << endl;
                    showStatistics(re, "User with Passwords", fullPath);
                    file.close();
                    break;
                }
                
                case 4:
                {
                    ofstream file(fullPath.c_str(), ios::trunc);
                    if(!file) {
                        setColor(12);
                        cout << " Failed To Open The File !" << endl;
                        setColor(7);
                        continue;
                    }
                    
                    user_size = getValidNumber("[" + intToString(cho) + "] Enter The Size of User (2-5): ");
                    if(user_size < 2 || user_size > 5) {
                        setColor(12);
                        cout << "Invalid size! Using default (4)" << endl;
                        setColor(7);
                        user_size = 4;
                    }
                    
                    re = getValidNumber("[" + intToString(cho) + "] Enter The Size of List: ");
                    
                    loadingAnimation();
                    
                    for(i=0; i<re; i++) {
                        string username = "";
                        for(j=0; j<user_size; j++) {
                            username += random[rand() % random.length()];
                        }
                        file << username << endl;
                    }
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Saved to: " << fullPath << endl;
                    showStatistics(re, "User without Passwords", fullPath);
                    file.close();
                    break;
                }
                
                case 5:
                {
                    string line;
                    vector<string> lines;
                    
                    ifstream readFile(fullPath.c_str());
                    if(!readFile) {
                        setColor(12);
                        cout << "Failed To Open The File !" << endl;
                        setColor(7);
                        break;
                    }
                    
                    cout << "[" << cho << "] Enter The Password: ";
                    cin >> pass;
                    cout << "--------------------------------" << endl;
                    
                    while(getline(readFile, line)) {
                        if(!line.empty()) {
                            lines.push_back(line);
                        }
                    }
                    readFile.close();
                    
                    if(lines.empty()) {
                        setColor(12);
                        cout << "File is empty!" << endl;
                        setColor(7);
                        break;
                    }
                    
                    loadingAnimation();
                    
                    ofstream writeFile(fullPath.c_str(), ios::trunc);
                    if(!writeFile) {
                        setColor(12);
                        cout << "Failed To Open The File !" << endl;
                        setColor(7);
                        break;
                    }
                    
                    for(unsigned int k=0; k<lines.size(); k++) {
                        writeFile << lines[k] << ":" << pass << endl;
                    }
                    writeFile.close();
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Added passwords to: " << fullPath << endl;
                    showStatistics(lines.size(), "Password Added to List", fullPath);
                    break;
                }
                
                case 6:
                {
                    ofstream file(fullPath.c_str(), ios::trunc);
                    if(!file) {
                        setColor(12);
                        cout << " Failed To Open The File !" << endl;
                        setColor(7);
                        continue;
                    }
                    
                    re = getValidNumber("[" + intToString(cho) + "] Enter The Number of Passwords: ");
                    
                    int passLen = getValidNumber("Enter password length (default 8): ");
                    if(passLen < 1) passLen = 8;
                    
                    cout << "Include special characters? [y/n]: ";
                    char special;
                    cin >> special;
                    
                    loadingAnimation();
                    
                    for(i=0; i<re; i++) {
                        string password;
                        if(special == 'y' || special == 'Y') {
                            password = generateStrongPassword(passLen);
                        } else {
                            string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
                            for(j=0; j<passLen; j++) {
                                password += chars[rand() % chars.length()];
                            }
                        }
                        file << password << endl;
                    }
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Saved to: " << fullPath << endl;
                    showStatistics(re, "Random Passwords", fullPath);
                    file.close();
                    break;
                }
            }
            
            cout << "\nPress Enter to continue...";
            cin.get();
            system("cls");
        }
        
        else if(cho >= 7 && cho <= 11) {
            cout << "Enter the full path of the file: ";
            
            string filePath;
            getline(cin, filePath);
            
            if(!fileExists(filePath)) {
                setColor(12);
                cout << "File not found: " << filePath << endl;
                setColor(7);
                cout << "\nPress Enter to continue...";
                cin.get();
                system("cls");
                continue;
            }
            
            currentFilePath = filePath;
            
            switch(cho)
            {
                case 7:
                {
                    string list2Path;
                    cout << "Enter the full path of second list file: ";
                    getline(cin, list2Path);
                    
                    ifstream file1(filePath.c_str());
                    ifstream file2(list2Path.c_str());
                    
                    if(!file1 || !file2) {
                        setColor(12);
                        cout << "Could not open one or both files!" << endl;
                        setColor(7);
                        break;
                    }
                    
                    string mergedPath = filePath;
                    size_t dotPos = mergedPath.find(".txt");
                    if(dotPos != string::npos) {
                        mergedPath.insert(dotPos, "_merged");
                    } else {
                        mergedPath += "_merged.txt";
                    }
                    
                    ofstream mergedFile(mergedPath.c_str(), ios::trunc);
                    if(!mergedFile) {
                        setColor(12);
                        cout << "Failed to create merged file!" << endl;
                        setColor(7);
                        break;
                    }
                    
                    string line;
                    int count = 0;
                    
                    loadingAnimation();
                    
                    while(getline(file1, line)) {
                        if(!line.empty()) {
                            mergedFile << line << endl;
                            count++;
                        }
                    }
                    
                    while(getline(file2, line)) {
                        if(!line.empty()) {
                            mergedFile << line << endl;
                            count++;
                        }
                    }
                    
                    file1.close();
                    file2.close();
                    mergedFile.close();
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Merged " << count << " entries" << endl;
                    cout << "Saved to: " << mergedPath << endl;
                    setColor(7);
                    break;
                }
                
                case 8:
                {
                    ifstream readFile(filePath.c_str());
                    if(!readFile) {
                        setColor(12);
                        cout << "Failed To Open The File !" << endl;
                        setColor(7);
                        break;
                    }
                    
                    vector<string> lines;
                    string line;
                    
                    while(getline(readFile, line)) {
                        if(!line.empty()) {
                            lines.push_back(line);
                        }
                    }
                    readFile.close();
                    
                    int originalSize = lines.size();
                    vector<string> uniqueLines = removeDuplicates(lines);
                    
                    ofstream writeFile(filePath.c_str(), ios::trunc);
                    if(!writeFile) {
                        setColor(12);
                        cout << "Failed To Open The File !" << endl;
                        setColor(7);
                        break;
                    }
                    
                    for(unsigned int k=0; k<uniqueLines.size(); k++) {
                        writeFile << uniqueLines[k] << endl;
                    }
                    writeFile.close();
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Removed " << (originalSize - uniqueLines.size()) 
                         << " duplicates" << endl;
                    cout << "Remaining entries: " << uniqueLines.size() << endl;
                    setColor(7);
                    break;
                }
                
                case 9:
                {
                    ifstream searchFile(filePath.c_str());
                    if(!searchFile) {
                        setColor(12);
                        cout << "Failed To Open The File !" << endl;
                        setColor(7);
                        break;
                    }
                    
                    string searchTerm;
                    cout << "Enter search term: ";
                    getline(cin, searchTerm);
                    
                    string line;
                    int found = 0;
                    
                    cout << "\n========== SEARCH RESULTS ==========" << endl;
                    while(getline(searchFile, line)) {
                        if(line.find(searchTerm) != string::npos) {
                            setColor(14);
                            cout << line << endl;
                            setColor(7);
                            found++;
                        }
                    }
                    searchFile.close();
                    
                    setColor(10);
                    cout << "=====================================" << endl;
                    cout << "Found " << found << " entries matching '" << searchTerm << "'" << endl;
                    setColor(7);
                    break;
                }
                
                case 10:
                {
                    int count = countEntries(filePath);
                    setColor(10);
                    cout << "=====================================" << endl;
                    cout << "File: " << filePath << endl;
                    cout << "Total Entries: " << count << endl;
                    cout << "=====================================" << endl;
                    setColor(7);
                    break;
                }
                
                case 11:
                {
                    ifstream readFile(filePath.c_str());
                    if(!readFile) {
                        setColor(12);
                        cout << "Failed To Open The File !" << endl;
                        setColor(7);
                        break;
                    }
                    
                    string csvPath = filePath;
                    size_t dotPos = csvPath.find(".txt");
                    if(dotPos != string::npos) {
                        csvPath.replace(dotPos, 4, ".csv");
                    } else {
                        csvPath += ".csv";
                    }
                    
                    ofstream csvFile(csvPath.c_str(), ios::trunc);
                    if(!csvFile) {
                        setColor(12);
                        cout << "Failed to create CSV file!" << endl;
                        setColor(7);
                        break;
                    }
                    
                    string line;
                    int count = 0;
                    
                    loadingAnimation();
                    
                    csvFile << "Username,Password" << endl;
                    
                    while(getline(readFile, line)) {
                        if(!line.empty()) {
                            size_t pos = line.find(':');
                            if(pos != string::npos) {
                                string user = line.substr(0, pos);
                                string passw = line.substr(pos + 1);
                                csvFile << user << "," << passw << endl;
                            } else {
                                csvFile << line << "," << endl;
                            }
                            count++;
                        }
                    }
                    
                    readFile.close();
                    csvFile.close();
                    
                    setColor(10);
                    cout << "[!]-> COMPLETE - Exported " << count << " entries to CSV" << endl;
                    cout << "CSV saved to: " << csvPath << endl;
                    setColor(7);
                    break;
                }
            }
            
            cout << "\nPress Enter to continue...";
            cin.get();
            system("cls");
        }
        
        else if(cho == 12) {
            system("cls");
            setColor(10);
            cout << "Screen cleared!" << endl;
            setColor(7);
            Sleep(1000);
            system("cls");
        }
        
        else if(cho == 13) {
            setColor(10);
            cout << "\nThank you for using INFERNO!" << endl;
            setColor(7);
            break;
        }
        
        else {
            setColor(12);
            cout << "Invalid choice! Please try again." << endl;
            setColor(7);
            Sleep(1500);
            system("cls");
        }
    }
    
    return 0;
}
