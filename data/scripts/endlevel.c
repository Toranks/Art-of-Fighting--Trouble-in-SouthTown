void main()
{
      saveMaxRush();
      slowmot();
}


void saveMaxRush()
{//Save max rush counter when the level ends
	void player1 = getplayerproperty(0, "entity"); //IDENTIFY PLAYER 1
	void player2 = getplayerproperty(1, "entity"); //IDENTIFY PLAYER 2
	void player3 = getplayerproperty(2, "entity"); //IDENTIFY PLAYER 3
	
	if(player1 != NULL()){ //IS PLAYER 1 PLAYING THE GAME??
		setglobalvar("maxRush1", getentityproperty(player1, "rush_tally")); //SAVE CURRENT PLAYER 1 MAX RUSH COUNT
	}
	if(player2 != NULL()){ //IS PLAYER 2 PLAYING THE GAME??
		setglobalvar("maxRush2", getentityproperty(player2, "rush_tally")); //SAVE CURRENT PLAYER 2 MAX RUSH COUNT
	}
	if(player3 != NULL()){ //IS PLAYER 3 PLAYING THE GAME??
		setglobalvar("maxRush3", getentityproperty(player3, "rush_tally")); //SAVE CURRENT PLAYER 3 MAX RUSH COUNT
	}
}


void slowmot()
{
   setglobalvar("zoomentity", NULL());
   changeopenborvariant("slowmotion", 0);
}