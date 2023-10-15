void zoom()
{
   void vscreen = openborvariant("vscreen");
   int maxz=openborvariant("PLAYER_MAX_Z")+1000;
   int zoom_value=getglobalvar("zoomvalue");
   int zoom_x=getglobalvar("zoomx");
   int zoom_y=getglobalvar("zoomy");
   void ent=getglobalvar("zoomentity");
   int px=getentityproperty(ent,"x") +  zoom_x - openborvariant("xpos");
   int py=getentityproperty(ent,"z") + zoom_y - openborvariant("ypos") - getentityproperty(ent,"a");
   void zoom_scr = getglobalvar("zoomscreen");
   if(!zoom_scr){
      zoom_scr = allocscreen(openborvariant("hResolution"),openborvariant("vResolution"));
      setglobalvar("zoomscreen",zoom_scr);
   }
   clearscreen(zoom_scr);

   //draw what we need 
   drawspriteq(zoom_scr,0,openborconstant("MIN_INT"),maxz,0,0);
   //setup drawMethod
   changedrawmethod(NULL(),"reset",1);
   changedrawmethod(NULL(),"enabled",1);
   changedrawmethod(NULL(),"scalex",zoom_value);
   changedrawmethod(NULL(),"scaley",zoom_value);
   changedrawmethod(NULL(),"centerx",px);
   changedrawmethod(NULL(),"centery",py);
   //Draw the resized customized screen to main screen.
   drawscreen(zoom_scr,px,py, maxz+1);
   changedrawmethod(NULL(),"enabled", 0);
   drawspriteq(vscreen, 0, maxz+1,maxz+1, 0, 0);
   drawspriteq(vscreen, 0, maxz+2,openborconstant("MAX_INT"), 0, 0);
   clearspriteq();
}


void main(){
	void lv1 = getplayerproperty(0, "lives");
	void lv2 = getplayerproperty(1, "lives");
	void lv3 = getplayerproperty(2, "lives");	
	resetMaxRush();
	score();
	if(getglobalvar("zoomentity"))
	{
      zoom();        
	}
	//CLEAR ALL GLOBAL VARIABLES AT TITLE SCREEN
	if(openborvariant("in_titlescreen"))
	{
		clearglobalvar();
	}
	//MAX LIVES TO 15
	if ( lv1 > 15 )
	{
   	changeplayerproperty(0, "lives", 15);
	}
	if ( lv2 > 15 )
	{
   	changeplayerproperty(1, "lives", 15);
	}
	if ( lv3 > 15 )
	{
   	changeplayerproperty(2, "lives", 15);
	}
}

void resetMaxRush()
{//Reset max rush counter in "Stage Complete" screen
	if(openborvariant("in_showcomplete")){
		void player1 = getplayerproperty(0, "entity"); //IDENTIFY PLAYER 1
		void player2 = getplayerproperty(1, "entity"); //IDENTIFY PLAYER 2
		void player3 = getplayerproperty(2, "entity"); //IDENTIFY PLAYER 3
		
		if(player1 != NULL()){ //IS PLAYER 1 PLAYING THE GAME??
			setglobalvar("maxRush1", 0); //RESET PLAYER 1 MAX RUSH COUNT SAVED VALUE TO ZERO
		}
		if(player2 != NULL()){ //IS PLAYER 2 PLAYING THE GAME??
			setglobalvar("maxRush2", 0); //RESET PLAYER 2 MAX RUSH COUNT SAVED VALUE TO ZERO
		}
		if(player3 != NULL()){ //IS PLAYER 3 PLAYING THE GAME??
			setglobalvar("maxRush3", 0); //RESET PLAYER 3 MAX RUSH COUNT SAVED VALUE TO ZERO
		}
	}
}

void score()
{//GLOBAL OPERATIONS
	if(openborvariant("in_showcomplete")){
		changeplayerproperty(0, "disablekeys", openborconstant("FLAG_ATTACK")+openborconstant("FLAG_ATTACK2")+openborconstant("FLAG_ATTACK3")+openborconstant("FLAG_ATTACK4")+openborconstant("FLAG_JUMP")+openborconstant("FLAG_SPECIAL")); //DISABLE KEY FOR PLAYER 1		
		changeplayerproperty(1, "disablekeys", openborconstant("FLAG_ATTACK")+openborconstant("FLAG_ATTACK2")+openborconstant("FLAG_ATTACK3")+openborconstant("FLAG_ATTACK4")+openborconstant("FLAG_JUMP")+openborconstant("FLAG_SPECIAL")); //DISABLE KEY FOR PLAYER 2
		changeplayerproperty(2, "disablekeys", openborconstant("FLAG_ATTACK")+openborconstant("FLAG_ATTACK2")+openborconstant("FLAG_ATTACK3")+openborconstant("FLAG_ATTACK4")+openborconstant("FLAG_JUMP")+openborconstant("FLAG_SPECIAL")); //DISABLE KEY FOR PLAYER 3
		
		//INCREASE SPEED
		if(playerkeys(0, 0, "moveup")){ //P1 HOLD BUTTON
			changeopenborvariant("elapsed_time", openborvariant("elapsed_time")+500);
		}
		else
		if(playerkeys(1, 0, "moveup")){ //P2 HOLD BUTTON
			changeopenborvariant("elapsed_time", openborvariant("elapsed_time")+500);
		}
		else
		if(playerkeys(2, 0, "moveup")){ //P3 HOLD BUTTON
			changeopenborvariant("elapsed_time", openborvariant("elapsed_time")+500);
		}
		
		//GO TO TOTAL SCORE WITHOUT CLOSE THE COMPLETE SCREEN
		if(playerkeys(0, 1, "movedown")){ //P1 PRESS BUTTON
			changeopenborvariant("elapsed_time", openborvariant("elapsed_time")+4000);
		}
		else
		if(playerkeys(1, 1, "movedown")){ //P2 PRESS BUTTON
			changeopenborvariant("elapsed_time", openborvariant("elapsed_time")+4000);
		}
		else
		if(playerkeys(2, 1, "movedown")){ //P3 PRESS BUTTON
			changeopenborvariant("elapsed_time", openborvariant("elapsed_time")+4000);
		}
	}
}