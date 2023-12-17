

void main()
{
    void self = getlocalvar("self");
    void trap = findtarget(self);
    void isfire = getentityproperty(trap, "defaultname");
 
    if(isfire == "potfire" || isfire == "potfire2" || isfire == "potfire3")
    {
        void anim = getentityproperty(self, "animationID"); //GET THE CURRENT ANIMATION
        int z1 = getentityproperty(self, "z"); //ENEMY
        int z2 = getentityproperty(trap, "z"); //NPC TRAP
        int x1 = getentityproperty(self, "x"); //ENEMY
        int x2 = getentityproperty(trap, "x"); //NPC TRAP
        int rangeZBelow = (z1 - z2);
        int rangeZAbove = (z2 - z1);
        int rangeX = (x1 - x2);

        
        //CHECK IF THE ENEMY IS IN THE WALK ANIMATION
        if(anim == openborconstant("ANI_WALK") || anim == openborconstant("ANI_RUN"))
        {
            //FIRE TRAP IS AT THE TOP OF THE Z BOUNDARY AND ENEMY IS BELOW (LESS THAN 33 PIXELS)
            if(z1 > z2 && rangeZBelow < 33 && (-120 < rangeX < 120)){ //CHECK RANGE
                changeentityproperty(self, "animation", openborconstant("ANI_JUMP")); //CHANGE ANIMATION
                tossentity(self, 2, 0, 2);
            }
            //FIRE TRAP IS AT THE TOP OF THE Z BOUNDARY AND ENEMY IS BELOW (BETWEEN 33 AND 60 PIXELS)
            else if(z1 > z2 && rangeZBelow > 33 && rangeZBelow < 60 && (-200 < rangeX < 200)){ //CHECK RANGE
                changeentityproperty(self, "aimove", openborconstant("AIMOVE1_AVOID"));
            }
            //FIRE TRAP IS AT THE BOTTOM Z BOUNDARY AND ENEMY IS ABOVE (LESS THAN 33 PIXELS)
            else if(z2 > z1 && rangeZAbove < 33 && (-120 < rangeX < 120)){ //CHECK RANGE
                changeentityproperty(self, "animation", openborconstant("ANI_JUMP")); //CHANGE ANIMATION
                tossentity(self, 2, 0, -2);
            }
            //FIRE TRAP IS AT THE BOTTOM Z BOUNDARY AND ENEMY IS ABOVE (BETWEEN 33 AND 60 PIXELS)
            else if(z2 > z1 && rangeZAbove > 33 && rangeZBelow < 60 && (-200 < rangeX < 200)){ //CHECK RANGE
                changeentityproperty(self, "aimove", openborconstant("AIMOVE1_AVOID"));
            }
            else
            {
                //ANY OTHER SITUATION BUT THE NEAREST TARGET IS THE FIRE TRAP
                changeentityproperty(self, "aimove", openborconstant("AIMOVE1_NORMAL"));   
            }
        }
    }
    else
    {
        //ANY OTHER SITUATION
        changeentityproperty(self, "aimove", openborconstant("AIMOVE1_NORMAL"));   
    }
}

