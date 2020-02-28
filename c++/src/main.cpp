#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>

#include "../libs/json.hpp"

using namespace std;

int getData();

int main(){
    //Step 1: Get the Data from Blue Alliance
    int resultRead = getData();

    //Step 2: Save that Data into a String OR Straight-up Parse with Modern-JSON

    return resultRead;
}

int getData(){
    curl_global_init( CURL_GLOBAL_ALL ); //Initialize CURL
    
    CURL* myHandle;  //Handle for Requests
    CURLcode result; //Result of Curl Retrieval

    myHandle = curl_easy_init(); //Initialize the Handle

    if(myHandle){ //If the Handle is Initialized Succesfully 
        struct curl_slist *chunk = NULL; //Headers List

        //Add the Headers for The Blue Alliance API
        chunk = curl_slist_append(chunk, "accept: application/json");
        chunk = curl_slist_append(chunk, "X-TBA-Auth-Key: biuWVtbepPQnfgdMwPJnAmomoCm8Uw0VaO1UBdHsWzKJJCTOdUUprjHEsSIss01i");

        //Get the Temporary File we use to hold the data
        FILE* tempFile = NULL;
        tempFile = fopen("tempFile.txt", "w");

        if(tempFile != NULL){
            curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, tempFile);
        } else {
            cout << "ERROR WRITING TO TEMPFILE.txt" << endl;
            return -1;
        }

        //Set the URL and Header for the Request
        curl_easy_setopt(myHandle, CURLOPT_URL, "https://www.thebluealliance.com/api/v3/event/2020ohmv/district_points");
        curl_easy_setopt(myHandle, CURLOPT_HTTPHEADER, chunk); //Headers
        curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, NULL);

        result = curl_easy_perform(myHandle); //Try to get the result

        if(result != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        } else {
            cout << "No Errors in Reading Data" << endl;
        }

        curl_easy_cleanup(myHandle);
        curl_slist_free_all(chunk);
        free(tempFile);
    }

    return 0;
}