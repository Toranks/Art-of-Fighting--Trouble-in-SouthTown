void main()
{//Load saved max rush counter and apply when the level starts
	void player1 = getplayerproperty(0, "entity"); //IDENTIFY PLAYER 1
	void player2 = getplayerproperty(1, "entity"); //IDENTIFY PLAYER 2
	void player3 = getplayerproperty(2, "entity"); //IDENTIFY PLAYER 3
	
	if(player1 != NULL()){ //IS PLAYER 1 PLAYING THE GAME??
		changeentityproperty(player1, "rush_tally", getglobalvar("maxRush1")); //CHANGE PLAYER 1 MAX RUSH COUNT WITH LOADED VALUE
	}
	if(player2 != NULL()){ //IS PLAYER 2 PLAYING THE GAME??
		changeentityproperty(player2, "rush_tally", getglobalvar("maxRush2")); //CHANGE PLAYER 2 MAX RUSH COUNT WITH LOADED VALUE
	}
	if(player3 != NULL()){ //IS PLAYER 3 PLAYING THE GAME??
		changeentityproperty(player3, "rush_tally", getglobalvar("maxRush3")); //CHANGE PLAYER 3 MAX RUSH COUNT WITH LOADED VALUE
	}
}