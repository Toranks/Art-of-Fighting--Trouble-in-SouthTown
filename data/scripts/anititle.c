//Title Animation, based on Volcanic's code, by CRxTRDude

#ifndef TITLE_ANI
#define	TOTALANIFRAME 7 //the number of frames the animation has.
#define TITLE_ANI 0	//the variable that holds the array together.
#endif

void loadTitleAni()
{
	//command to load the animation from frames.
	//set up variables
	void i,j;
	void titleani=getindexedvar(TITLE_ANI);
	//do we have something in TITLE_ANI?
	if(!titleani)
	{
		log("-- Setting up game... ----------\n\n");
		//Grab the variable defined from anisprite
		log("Loading title background sprites... ");
		titleani=array(TOTALANIFRAME);
		//for loop to grab the background sprite.
		for(i=0;i<TOTALANIFRAME;i++)
		{
			set(titleani,i,loadsprite("data/title/"+i+".gif"));
		}
		setindexedvar(TITLE_ANI,titleani);
		log("Done!\n");
		log("\n-- LOG: Game proper ---------------------------\n\n");		
	}
}

void inTitleLoop(int enable)
{
		loadTitleAni(); //load the title animation first
		if (enable==1)
		{		
			void titleani=getindexedvar(TITLE_ANI); //get the array
			void time=openborvariant("elapsed_time"); //get time from engine
			void framed = TOTALANIFRAME;             
			void spr=get(titleani,time%(TOTALANIFRAME*framed)/framed);
			
			changedrawmethod(NULL(), "reset", 1);
			changedrawmethod(NULL(), "enabled", 1);
			changedrawmethod(NULL(), "alpha", 6);
			drawsprite(spr,0,0,1); //draw the sprite using the content of array with time
			changedrawmethod(NULL(), "reset", 1);
			changedrawmethod(NULL(), "enabled", 0);
			
			drawstring(176,257,0,"Game by Dantedevil 2015");
		}
}

void titleCleanup()
{
	void i;
	void titleani=getindexedvar(TITLE_ANI);
	
	if (titleani){
		log("Clearing title background sprites... ");
		for(i=0;i<TOTALANIFRAME;i++)
		{
			free(get(titleani,i));
		}
		free(titleani);
		log("Done!\n");
	}
}
