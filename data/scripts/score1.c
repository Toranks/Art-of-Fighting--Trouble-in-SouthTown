void main()
{
	lifeScore(0);
}

void lifeScore(int player)
{//Custom LifeScore script for add lives, used to avoid native engine LifeScore issue
	void self	  = getplayerproperty(player, "entity");
	int score	  = getplayerproperty(player, "score");
	int lifeScore     = 250000; //DEFINED LIFESCORE TARGET TO ADD EACH LIVE
	int add		  = 1; //HOW MUCH LIVES WILL BE ADDED WHEN SCORE REACHED THE TARGET
	
	//USED TO CHECK IF THE PLAYER IS IN A NEW GAME
	if(getglobalvar("next1up"+player) == NULL() || self == NULL()){
		setglobalvar("next1up"+player, lifeScore);
	}
	
	//USED TO ADD LIVES TO PLAYER
	if(self != NULL()){ //CURRENT PLAYER REMAINS IN GAME??
		while(score >= getglobalvar("next1up"+player)){ //CURRENT SCORE REACHED THE LAST DEFINED TARGET??
			int lives = getplayerproperty(player, "lives"); //CHECK CURRENT LIVES EVERYTIME THIS TASK RUNS
			playsample(openborconstant("SAMPLE_1UP"), 0, 120, 120, 100, 0); //PLAY SAMPLE
			changeplayerproperty(player, "lives", lives+add); //ADD +1 LIVE
			setglobalvar("next1up"+player, getglobalvar("next1up"+player)+lifeScore); //DEFINE AND SAVE THE NEXT TARGET
		}
	}
}