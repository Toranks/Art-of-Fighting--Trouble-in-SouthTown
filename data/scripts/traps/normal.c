void main()
{
    void self = getlocalvar("self");

	int  iMax = openborvariant("count_entities");	//Entity count.
	int  iEntity;				//Loop counter
	void vEntity;				//Target entity

	for(iEntity=0; iEntity<iMax; iEntity++)
	{    
		vEntity = getentity(iEntity);	//entity from current loop.   
		void isfire = getentityproperty(vEntity, "defaultname");

		if(isfire == "potfire" || isfire == "potfire2" || isfire == "potfire3") //IS THE ENTITY A FIRE?
		{
			void anim = getentityproperty(self, "animationID"); //GET THE CURRENT ANIMATION
			int z1 = getentityproperty(self, "z"); //ENEMY
			int z2 = getentityproperty(vEntity, "z"); //NPC TRAP
			int x1 = getentityproperty(self, "x"); //ENEMY
			int x2 = getentityproperty(vEntity, "x"); //NPC TRAP
			int rangeZBelow = (z1 - z2);
			int rangeZAbove = (z2 - z1);
			int rangeX = (x1 - x2);

			setlocalvar("thereisfire", 1); //THERE IS ANY FIRE
			
			//CHECK IF THE ENEMY IS IN THE WALK OR RUN ANIMATION
			if(anim == openborconstant("ANI_WALK") || anim == openborconstant("ANI_RUN"))
			{
				//FIRE TRAP IS AT THE TOP OF THE Z BOUNDARY AND ENEMY IS BELOW (LESS THAN 35 PIXELS ON Z, LESS THAN 100 ON X)
				if(z1 > z2 && rangeZBelow < 35 && (-100 < rangeX < 100)){ //CHECK RANGE
					changeentityproperty(self, "animation", openborconstant("ANI_JUMP")); //JUMP BELOW
					tossentity(self, 2, 0, 1);
				}
				//FIRE TRAP IS AT THE TOP OF THE Z BOUNDARY AND ENEMY IS BELOW (BETWEEN 35 AND 60 PIXELS ON Z, LESS THAN 120 ON X)
				else if(z1 > z2 && 35 < rangeZBelow < 60 && (-120 < rangeX < 150)){ //CHECK RANGE
					changeentityproperty(self, "aimove", openborconstant("AIMOVE1_AVOID")); //AVOID BEHAVIOR
				}
				//FIRE TRAP IS AT THE BOTTOM Z BOUNDARY AND ENEMY IS ABOVE (LESS THAN 35 PIXELS ON Z, LESS THAN 100 ON X)
				else if(z2 > z1 && rangeZAbove < 35 && (-100 < rangeX < 100)){ //CHECK RANGE
					changeentityproperty(self, "animation", openborconstant("ANI_JUMP")); //JUMP ABOVE
					tossentity(self, 2, 0, -1);
				}
				//FIRE TRAP IS AT THE BOTTOM Z BOUNDARY AND ENEMY IS ABOVE (BETWEEN 35 AND 60 PIXELS ON Z, LESS THAN 120 ON X)
				else if(z2 > z1 && (35 < rangeZAbove < 60) && (-120 < rangeX < 120)){ //CHECK RANGE
					changeentityproperty(self, "aimove", openborconstant("AIMOVE1_AVOID")); //AVOID BEHAVIOR
				}
				//FIRE TRAP IS FURTHER THAN 60 PIXELS ON Z, OR 120 ON X
				else if(rangeZBelow > 60 || rangeZAbove > 60 || rangeX > 120 || rangeX < -120) //CHECK RANGE
				{
					changeentityproperty(self, "aimove", openborconstant("AIMOVE1_NORMAL")); //NORMAL BEHAVIOR
				}
			}
		}
	}
	if (getlocalvar("thereisfire") != 1){
		changeentityproperty(self, "aimove", openborconstant("AIMOVE1_NORMAL")); //DEFAULT BEHAVIOR		
	}
	else
	{
		setlocalvar("thereisfire", 0); //RESET FIRE COUNT
	}
}
