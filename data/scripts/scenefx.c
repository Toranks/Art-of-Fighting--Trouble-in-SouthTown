void clearL()
{ // Clears all local variables
     clearlocalvar();
}

void noplayerJoin (int iG)
{
// controls if other players can join the game or not
// 1 - players CAN NOT join, 0 play CAN join (@cmd noplayerJoin 1/@cmd noplayerJoin 0)
// remember to set it 0 when you are done, or you will have a 1P only game.
// Douglas Baldan/O Ilusionista - 20/09/14
changeopenborvariant("nojoin", iG);
}

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}

void looper(int Frame, int Limit)
{// Loops current animation
    void self = getlocalvar("self");
    void loop = getlocalvar("Loop" + self);

    if(loop==NULL()){ // Localvar empty?
      setlocalvar("Loop" + self, 0);
      loop = 0;
    } 
   
    if(loop < Limit){ // loops reach limit?
      updateframe(self, Frame); //Change frame
      setlocalvar("Loop" + self, loop+1); // Increment number of loops
    } else if(loop==Limit){ // loops reach limit?
      setlocalvar("Loop" + self, NULL());
    }
}

void DeControl(int P, int Flag)
{// Activates or deactivates control for defined player
// P : Player index starting from 0
// Flag : Control flag
    int Player = getplayerproperty(P, "entity");

    if (Player != NULL()){
      changeentityproperty(Player,"noaicontrol",Flag);
    }
}

void AnimPlayer(int P, void Ani)
{// Forces defined player to play certain animation
// P : Player index starting from 0
// Ani : Animation to play to
    int Player = getplayerproperty(P, "entity");

    if (Player != NULL()){
      performattack(Player, openborconstant(Ani));
    }
}

void AnimPlayer_S(int P, void Ani)
{// Forces defined player to play certain animation if not in Spawn
// P : Player index starting from 0
// Ani : Animation to play to
    int Player = getplayerproperty(P, "entity");

	if (getentityproperty(Player, "animationID") == openborconstant("ANI_SPAWN")){	//Animation match?
	performattack(Player, openborconstant("ANI_SPAWN"));
  	} else if (Player != NULL()){
	performattack(Player, openborconstant(Ani));
  }
}

void IdlPlayer(int P)
{// Forces defined player to go to IDLE
// P : Player index starting from 0
    int Player = getplayerproperty(P, "entity");

    if (Player != NULL()){
      setidle(Player, openborconstant("ANI_IDLE"));
    }
}

void MovePlayer(int P, float Vx, float Vy, float Vz)
{// Forces defined player to move with defined speed
// P : Player index starting from 0
    int Player = getplayerproperty(P, "entity");

    if (Player != NULL()){
      changeentityproperty(Player, "velocity", Vx, Vz, Vy);
    }
}

void MovePcoord(int P)
{// Forces defined player to move with defined speed and coordinate
    int Player = getplayerproperty(P, "entity");
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);

    if(Player!=NULL() && Vx!=NULL() && Vz!=NULL())

    {
      changeentityproperty(Player, "velocity", Vx, Vz);
    }
}



void dash()
{// Dash with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    if( Vx!=NULL() && Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx, Vz); //Move towards target!
    }
}


void targetPos(float Vy, int Tx, int Tz)
{// Targetting certain position before leaping there
//  Vy : Leaping speed
//  Tx : Leaping destination x coordinate
//  Tz : Leaping destination z coordinate
// Used with 'leap' or 'toss2'
    void self = getlocalvar("self");
    float x = getentityproperty(self, "x"); // Get entity's x coordinate
    float z = getentityproperty(self, "z"); // Get entity's z coordinate

    if(Tx < x){
      changeentityproperty(self, "direction", 0); // Face left 
    } else {
      changeentityproperty(self, "direction", 1); // Face right
    }
    setlocalvar("x"+self, (Tx-x)/(20*Vy)); // Calculate Vx then store value in local variable
    setlocalvar("z"+self, (Tz-z)/(20*Vy)); // Calculate Vz then store value in local variable
}


void DirPlayer(int P, int Dir)
{// Changes defined player's direction
// P : Player index starting from 0
// Dir : Direction
    int Player = getplayerproperty(P, "entity");

    if (Player != NULL()){
      changeentityproperty(Player, "direction", Dir);
    }
}