void main()
{
    void self = getlocalvar("self");
	void hp = getentityproperty(self,"health");
	void anim = getentityproperty(self,"animationID");
	void attacker = getentityproperty(self,"parent");
  	int plyr = getentityvar(attacker, "player");
	void frame = getentityproperty(self,"animpos");


	int x = getentityproperty(self,"x");
	int z = getentityproperty(self,"z");

	int XPos = openborvariant("xpos");
	int YPos = openborvariant("ypos");
	int Screen = openborvariant("hResolution");
	int Screen2 = openborvariant("vResolution");
		float Vx = getlocalvar("x"+self);
		float Vz = getlocalvar("z"+self);



	if(anim == openborconstant("ANI_IDLE") || anim == openborconstant("ANI_FOLLOW3") || anim == openborconstant("ANI_FOLLOW6"))
	{
   		if( x >= XPos+Screen-190) // right
   		{
        	changeentityproperty(self, "velocity", -0.2, Vz);
   		}
   		else if(x <= XPos+190) // left
   		{
        	changeentityproperty(self, "velocity", 0.2, Vz);
   		}
   		else if( z >= YPos+Screen2-40) // down
   		{
		changeentityproperty(self, "velocity", Vx, -0.1);
   		}
   		else if( z <= YPos+195) // up
   		{
		changeentityproperty(self, "velocity", Vx, 0.1);
   		}

		if (frame >= 0 && playerkeys(plyr, 0, "special"))
		{
			void anim2 = getentityproperty(self,"animationID");

				if (anim2 == openborconstant("ANI_IDLE"))
				{
				performattack(self, openborconstant("ANI_FOLLOW1"));
				}
				else if (anim2 == openborconstant("ANI_FOLLOW3"))
				{
				performattack(self, openborconstant("ANI_FOLLOW4"));
				}
				else if (anim2 == openborconstant("ANI_FOLLOW6"))
				{
				performattack(self, openborconstant("ANI_FOLLOW7"));
				}
		}


		if (frame >= 0 && playerkeys(plyr, 1, "attack"))
		{ 
		changeentityproperty(self, "health", hp+1);
		}
  	}


	if(anim == openborconstant("ANI_FOLLOW1") || anim == openborconstant("ANI_FOLLOW4") || anim == openborconstant("ANI_FOLLOW7"))
	{
   		if( x == 1025 && z == 330 ) // ---entity will stop here
   		{
        	changeentityproperty(self, "velocity", 0, 0);
		changeentityproperty(self, "position", 1025, 330);
   		}

   		else if( x < 1025 && z > 330 ) // ---entity moves right and up
   		{
        	changeentityproperty(self, "velocity", 0.2, -0.1);
   		}
   		else if( x < 1025 && z < 330 ) // ---entity moves right and down
   		{
        	changeentityproperty(self, "velocity", 0.2, 0.1);
   		}
   		else if( x > 1025 && z > 330 ) // ---entity moves left and up
   		{
        	changeentityproperty(self, "velocity", -0.2, -0.1);
   		}
   		else if( x > 1025 && z < 330 ) // ---entity moves left and down
   		{
        	changeentityproperty(self, "velocity", -0.2, 0.1);
   		}
  	}

//-------------------//---break-kill---//--1-win-2-lose------//---------------------

	float out2 = getglobalvar ("brkgo");

   	if( out2 == 1 || out2 == 2)
	{
	killentity(self);
	}
}