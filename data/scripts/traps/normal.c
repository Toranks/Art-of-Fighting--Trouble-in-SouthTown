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
				// Fuego arriba, enemigo abajo, cerca en Z y X
                if(z1 > z2 && rangeZBelow < 25 && rangeX > -100 && rangeX < 100){
                    changeentityproperty(self, "animation", openborconstant("ANI_JUMP"));
                    tossentity(self, 2, 0, 1);
                }
                // Fuego arriba, enemigo abajo, Z entre 11 y 35, X entre -120 y 120
                else if(z1 > z2 && rangeZBelow > 25 && rangeZBelow < 50 && rangeX > -120 && rangeX < 120){
                    changeentityproperty(self, "aimove", openborconstant("AIMOVE1_AVOID"));
                }
                // Fuego abajo, enemigo arriba, cerca en Z y X
                else if(z2 > z1 && rangeZAbove < 25 && rangeX > -100 && rangeX < 100){
                    changeentityproperty(self, "animation", openborconstant("ANI_JUMP"));
                    tossentity(self, 2, 0, -1);
                }
                // Fuego abajo, enemigo arriba, Z entre 11 y 35, X entre -120 y 120
                else if(z2 > z1 && rangeZAbove > 25 && rangeZAbove < 50 && rangeX > -120 && rangeX < 120){
                    changeentityproperty(self, "aimove", openborconstant("AIMOVE1_AVOID"));
                }
                // Fuera de rango: comportamiento normal
                else if(rangeZBelow > 50 || rangeZAbove > 50 || rangeX > 120 || rangeX < -120){
                    changeentityproperty(self, "aimove", openborconstant("AIMOVE1_NORMAL"));
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
