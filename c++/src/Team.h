#ifndef TEAM_H
#define TEAM_H

class Team{
    private:
        unsigned int teamNum = 9999;
        int totalDistrictPoints = 0;
        Team* nextTeam = nullptr;
    
    public:
        Team(unsigned int t, int p) : teamNum(t), totalDistrictPoints(p) {;} 

        //Getters
        unsigned int getTeamNum(){ return teamNum; };
        int getTotalDistrictPoints() { return totalDistrictPoints; };
        Team* getNextTeam(){ return nextTeam; };

        //Setters
        void setTeamNum(unsigned int num){ teamNum = num; };
        void setTotalDistrictPoints(int points){ totalDistrictPoints = points; };
        void setNextTeam(Team* team){ nextTeam = team; };
};

class TeamNode{
    private:
        TeamNode* nextTeamNode;
        TeamNode* previousTeamNode;
        Team currentTeam;
    
    public:
        TeamNode(TeamNode* next, TeamNode* previous, Team current) : nextTeamNode(next), 
                previousTeamNode(previous), currentTeam(current) {;}
 
        //Getters
        TeamNode* getNextTeamNode() { return nextTeamNode; };
        TeamNode* getPreviousTeamNode() { return previousTeamNode; };
        Team getCurrentTeam() { return currentTeam; };

        //Setters
        void setNextTeamNode(TeamNode* node) { nextTeamNode = node; };
        void setPreviousTeamNode(TeamNode* node) { previousTeamNode = node; };
        void setTeam(Team team) { currentTeam = team; };

};

void insertNewTeam(Team* newTeam);
void printAllTeams();
int getTeamPoints(unsigned int teamNum);
void removeAllTeams();
int getNumberOfTeamsInList();


#endif