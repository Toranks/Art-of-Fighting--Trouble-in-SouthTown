void main()
{
	void self = getlocalvar("self");
	void attacker = getentityproperty(self,"parent");
   	void victim2 = getentityvar(self, "target");
    void realvictim = getentityproperty(attacker, "opponent");
	void attackerani = getentityproperty(attacker,"animationID");
	void victimani = getentityproperty(victim2,"animationID");
	void realvictimani = getentityproperty(realvictim,"animationID");
	void plyr = getentityproperty(realvictim, "playerindex");
  	int victim = getentityvar(self, "player");
	int HP = getentityproperty(self,"health");
	int victimHP = getentityproperty(victim2,"health");
	int HPmax = getentityproperty(self,"maxhealth");
	int x1 = getentityproperty(attacker,"x");
	int z1 = getentityproperty(attacker,"z");
    int escape = getentityvar(self, "grabgo");
	void iUp = playerkeys(victim, 1, "moveup");
	void iDown = playerkeys(victim, 1, "movedown");
	void iLeft = playerkeys(victim, 1, "moveleft");
	void iRight = playerkeys(victim, 1, "moveright");
	void iJump = playerkeys(victim, 1, "jump");
	void iSpecial = playerkeys(victim, 1, "special");
	void iAttack = playerkeys(victim, 1, "attack");
		
  if (attacker == NULL() && victim2 == NULL()) {
        if  (realvictim != NULL() && escape == 1) {
		changeentityproperty(realvictim, "position", x1, z1);
        changeentityproperty(realvictim, "velocity", NULL(), 0, NULL());
     	performattack(realvictim, openborconstant("ANI_FOLLOW15"));
    	bindentity(realvictim, NULL());
        } else if (realvictim != NULL() && escape == 2) {
		changeentityproperty(realvictim, "position", x1, z1);
        changeentityproperty(realvictim, "velocity", NULL(), 0, NULL());
     	performattack(realvictim, openborconstant("ANI_FOLLOW16"));
    	bindentity(realvictim, NULL());
        }
		killentity(self);

    } else if (plyr != victim) {
    	setidle(attacker, openborconstant("ANI_IDLE"));
     	bindentity(victim2, NULL());
		killentity(self);

    } else if (attackerani == openborconstant("ANI_IDLE")) {
     	bindentity(victim2, NULL());
		killentity(self);
		
    } else if (victimani == openborconstant("ANI_SPECIAL") || realvictimani == openborconstant("ANI_SPECIAL")) {
    	setidle(attacker, openborconstant("ANI_IDLE"));
     	bindentity(victim2, NULL());
		killentity(self);

    } else if (victimHP < 1 && victim2 != NULL()) {
		changeentityproperty(victim2, "position", x1, z1);
        changeentityproperty(victim2, "velocity", NULL(), 0, NULL());
     	performattack(victim2, openborconstant("ANI_DIE"));
    	setidle(attacker, openborconstant("ANI_IDLE"));
     	bindentity(victim2, NULL());
		killentity(self);

    } else if (HP > 1 && victim2 == NULL()) {
		setidle(attacker, openborconstant("ANI_IDLE"));
        if  (realvictim != NULL() && escape == 1) {
            changeentityproperty(realvictim, "position", x1, z1);
            changeentityproperty(realvictim, "velocity", NULL(), 0, NULL());
            performattack(realvictim, openborconstant("ANI_FOLLOW15"));
            bindentity(realvictim, NULL());
        } else if (realvictim != NULL() && escape == 2) {
            changeentityproperty(realvictim, "position", x1, z1);
            changeentityproperty(realvictim, "velocity", NULL(), 0, NULL());
            performattack(realvictim, openborconstant("ANI_FOLLOW16"));
            bindentity(realvictim, NULL());
        }
		killentity(self);
        
	} else if(HP>=HPmax && escape == 1){
		changeentityproperty(victim2, "position", x1, z1);
        changeentityproperty(victim2, "velocity", NULL(), 0, NULL());
     	performattack(victim2, openborconstant("ANI_FOLLOW15"));
    	setidle(attacker, openborconstant("ANI_IDLE"));
     	bindentity(victim2, NULL());
     	performattack(attacker, openborconstant("ANI_PAIN8"));
		killentity(self);

	} else if(HP>=HPmax && escape == 2){
		changeentityproperty(victim2, "position", x1, z1);
        changeentityproperty(victim2, "velocity", NULL(), 0, NULL());
     	performattack(victim2, openborconstant("ANI_FOLLOW16"));
    	setidle(attacker, openborconstant("ANI_IDLE"));
     	bindentity(victim2, NULL());
    	performattack(attacker, openborconstant("ANI_PAIN8"));
		killentity(self);

	} else if(iUp || iDown || iLeft || iRight || iJump || iSpecial || iAttack){// button is pressed?
    	
		changeentityproperty(self, "health", HP+1);

   }// end checking valid pointers
}
