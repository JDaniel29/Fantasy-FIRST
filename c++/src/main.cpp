#include "Team.h"
#include <curl/curl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <unistd.h>

#include "../libs/json.hpp"

using namespace std;
using json = nlohmann::json;

FILE* callTheBlueAlliance(string competitionKey);
void parseTempFile(FILE* tempFile);
void scoreLineup(string inputFileName);

int main(int argc, char* argv[]) {
    //Check to make sure we have a valid input file
    string inputFileName;
    string competitionKey;
    int currentIteration = 0;

    if (argc == 1) {
        cout << "Please enter the valid name of an input file: ";
        cin >> inputFileName;

        cout << "Please Enter the Competition Key: ";
        cin >> competitionKey;
    } else if (argc == 2) {
        if (strcmp(argv[1], "ExamplePicks.input") == 0) {
            cout << "Please enter the valid name of an input file: ";
            cin >> inputFileName;
        }
        cout << "Please Enter the Competition Key: ";
        cin >> competitionKey;
    } else if (argc >= 3) {
        if (strcmp(argv[1], "ExamplePicks.input") == 0) {
            cout << "Please enter the valid name of an input file: ";
            cin >> inputFileName;
        }

        if (strcmp(argv[2], "example") == 0) {
            cout << "Please Enter the Competition Key: ";
            cin >> competitionKey;
        }
    } else {
        inputFileName = argv[1];
        competitionKey = argv[2];
    }

    while (1) {
        system("clear");
        cerr << "Current Iteration: " << currentIteration << endl;

        time_t my_time = time(NULL);
        cerr << "Current Timestamp: " << ctime(&my_time) << endl;

        //Step 1: Get the Data from Blue Alliance
        FILE* tempFile = callTheBlueAlliance(competitionKey);

        if (tempFile == NULL) {
            cout << "Fatal Error. See Error Log" << endl;
            return -1;
        }
        //Step 2: Save that Data into a String OR Straight-up Parse with Modern-JSON
        parseTempFile(tempFile);

        //Step 3: Run and Score Lineup
        scoreLineup(inputFileName);

        cout << "Updated as of: " << ctime(&my_time) << endl;

        usleep(5 * 1000000);

        currentIteration++;

        cerr << "========" << endl;
    }

    return 0;
}

FILE* callTheBlueAlliance(string competitionKey) {
    curl_global_init(CURL_GLOBAL_ALL); //Initialize CURL

    CURL* myHandle;  //Handle for Requests
    CURLcode result; //Result of Curl Retrieval

    FILE* tempFile = NULL; //Temporary File

    myHandle = curl_easy_init(); //Initialize the Handle

    if (myHandle) {                      //If the Handle is Initialized Succesfully
        struct curl_slist* chunk = NULL; //Headers List

        //Add the Headers for The Blue Alliance API
        chunk = curl_slist_append(chunk, "accept: application/json");
        chunk = curl_slist_append(chunk, "X-TBA-Auth-Key: biuWVtbepPQnfgdMwPJnAmomoCm8Uw0VaO1UBdHsWzKJJCTOdUUprjHEsSIss01i");

        //Get the Temporary File we use to hold the data
        tempFile = fopen("tempFile.txt", "w+");

        if (tempFile != NULL) {
            curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, tempFile);
        } else {
            cerr << "ERROR WRITING TO TEMPFILE.txt" << endl;
            return NULL;
        }

        //Set the URL and Header for the Request
        string url = "https://www.thebluealliance.com/api/v3/event/2020" + competitionKey + "/district_points";

        cerr << "URL: " << url << endl;

        curl_easy_setopt(myHandle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(myHandle, CURLOPT_HTTPHEADER, chunk); //Headers
        curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, NULL);

        result = curl_easy_perform(myHandle); //Try to get the result

        if (result != CURLE_OK) {
            free(tempFile);
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result) << endl;
        } else {
            cerr << "No Errors in Reading Data" << endl;
        }

        curl_easy_cleanup(myHandle);
        curl_slist_free_all(chunk);
    }

    return tempFile;
}

void parseTempFile(FILE* tempFile) {
    string stringifiedFile = ""; //File to be converted to string
    char currentLine[1000];

    rewind(tempFile);         //Restart Temp File
    while (!feof(tempFile)) { //Parse the entire file

        fgets(currentLine, 1000, tempFile);
        stringifiedFile += currentLine;
    }

    auto jsonparsed = json::parse(stringifiedFile); //This value will hold the parsed file.

    for (auto& x : jsonparsed["points"].items()) { //Part we care about.
        auto key = x.key();

        unsigned int teamNum = stoi(key.substr(3));
        int totalDistrictPoints = x.value()["total"];

        insertNewTeam(new Team(teamNum, totalDistrictPoints));
    }

    fclose(tempFile);
}

void scoreLineup(string inputFileName) {
    char continueLooping;
    string teamName;

    ifstream inputFile(inputFileName);

    inputFile.clear();
    inputFile.seekg(0);

    if (inputFile.is_open() == false) {
        cout << "Error Opening input File: " << inputFileName << endl;
        return;
    }

    do {
        int numTeams, currentTeamNum, totalPoints = 0;

        inputFile >> teamName;
        inputFile >> numTeams; //Read Number of Teams

        //TODO: Adjust to work in a linked list way
        int* teamNumbers = new int[4];
        double* teamScores = new double[4];

        for (int i = 0; i < numTeams; i++) {
            inputFile >> currentTeamNum; //Read Current Team Number

            teamNumbers[i] = currentTeamNum;
            teamScores[i] = getTeamPoints(currentTeamNum);

            totalPoints += getTeamPoints(currentTeamNum);
        }

        cout << teamName << "'s Linuep" << endl;
        cout << " Team # | District Points" << endl;
        for (int i = 0; i < numTeams; i++) {
            cout << " " << left << setw(6) << teamNumbers[i] << " | " << teamScores[i] << endl;
        }
        cout << "Total Points: " << totalPoints << endl
             << endl;
        ;

        inputFile >> continueLooping;
    } while (continueLooping != 'q');
}