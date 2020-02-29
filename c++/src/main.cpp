#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include <string>

#include "../libs/json.hpp"

using namespace std;
using json = nlohmann::json;

FILE* callTheBlueAlliance();
void parseTempFile(FILE* tempFile);



int main(){
    //Step 1: Get the Data from Blue Alliance
    FILE* tempFile = callTheBlueAlliance();

    if(tempFile == NULL){
        return -1;
    }

    //Step 2: Save that Data into a String OR Straight-up Parse with Modern-JSON    
    parseTempFile(tempFile);


    return 0;
}

FILE* callTheBlueAlliance(){
    curl_global_init( CURL_GLOBAL_ALL ); //Initialize CURL
    
    CURL* myHandle;  //Handle for Requests
    CURLcode result; //Result of Curl Retrieval

    
    FILE* tempFile = NULL; //Temporary File

    myHandle = curl_easy_init(); //Initialize the Handle



    if(myHandle){ //If the Handle is Initialized Succesfully 
        struct curl_slist *chunk = NULL; //Headers List

        //Add the Headers for The Blue Alliance API
        chunk = curl_slist_append(chunk, "accept: application/json");
        chunk = curl_slist_append(chunk, "X-TBA-Auth-Key: biuWVtbepPQnfgdMwPJnAmomoCm8Uw0VaO1UBdHsWzKJJCTOdUUprjHEsSIss01i");

        //Get the Temporary File we use to hold the data
        tempFile = fopen("tempFile.txt", "w+");

        if(tempFile != NULL){
            curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, tempFile);
        } else {
            cout << "ERROR WRITING TO TEMPFILE.txt" << endl;
            return NULL;
        }

        //Set the URL and Header for the Request
        string competitionKey = "gagai";
        string url = "https://www.thebluealliance.com/api/v3/event/2020" + competitionKey  + "/district_points";

        cout << "URL: " << url << endl;

        curl_easy_setopt(myHandle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(myHandle, CURLOPT_HTTPHEADER, chunk); //Headers
        curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, NULL);

        result = curl_easy_perform(myHandle); //Try to get the result

        if(result != CURLE_OK){
        free(tempFile);
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        } else {
            cout << "No Errors in Reading Data" << endl;
        }

        curl_easy_cleanup(myHandle);
        curl_slist_free_all(chunk);
    }

    return tempFile;
}

void parseTempFile(FILE* tempFile){
    string pointsFile = "";
    char currentLine[1000];

    rewind(tempFile); //Start again at the start of the file

    int numIterations = 0;
    while(currentLine != "  \"tiebreakers\": {" && !feof(tempFile)){
        fgets(currentLine, 1000, tempFile);
        numIterations++;

        if(numIterations % 200 == 0){ //Warning just in case so I know where this is ending
            cout << "Warning: Reached " << numIterations << " iterations." << endl;
        }

        pointsFile += currentLine;
    }

    if(feof(tempFile)){
        cout << "Reached End of File" << endl;
    }

    //cout << pointsFile;
    

}