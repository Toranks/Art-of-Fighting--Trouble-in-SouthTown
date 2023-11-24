void taunt(int add)
{
	void self = getlocalvar("self");
	void MP = getentityproperty(self,"mp");
	int x = getentityproperty(self, "x");
	int z = getentityproperty(self, "z");
	int i = 0;
	int enemies = 0;
	int entity_count = openborvariant("count_entities");
    

	for (i = 0; i < entity_count; ++i) {
            void ent = getentity(i);
			void anim = getentityproperty(ent,"animationID");

		if (getentityproperty(ent, "exists") && getentityproperty(ent,"type") == openborconstant("TYPE_ENEMY") && anim != openborconstant("ANI_DIE") && anim != openborconstant("ANI_FALL") && anim != openborconstant("ANI_FALL2") && anim != openborconstant("ANI_FALL2") && anim != openborconstant("ANI_FALL3") && anim != openborconstant("ANI_FALL4") && anim != openborconstant("ANI_FALL5") && anim != openborconstant("ANI_FALL6") && anim != openborconstant("ANI_FALL7") && anim != openborconstant("ANI_FALL8") && anim != openborconstant("ANI_FALL9") && anim != openborconstant("ANI_FALL10") && anim != openborconstant("ANI_FALL11") && anim != openborconstant("ANI_BURN"))
		{
			float Tx = getentityproperty(ent, "x");
			float Tz = getentityproperty(ent, "z");
			float Disx = Tx - x;
			float Disz = Tz - z;

			 if( Disx >= -50 && Disx <= 50 && Disz >= -50 && Disz <= 50)
			 {
				enemies = enemies+3;
			 }
			 else if( Disx >= -100 && Disx <= 100 && Disz >= -100 && Disz <= 100)
			 {
				enemies = enemies+2;
			 }
			 else if( Disx >= -200 && Disx <= 200 && Disz >= -200 && Disz <= 200)
			 {
				enemies = enemies+1;
			 }
		}
	}
	changeentityproperty(self,"mp", MP+(add*enemies));
}

void changetaunt()
{
	void self = getlocalvar("self");
	void plyr = getentityproperty(self, "playerindex");

	if(playerkeys(plyr, 0, "attack2")){ 
		performattack(self, openborconstant("ANI_FREESPECIAL32"));
	}
}

void attackgrd(int RxMin, int RxMax, int RaMin, int RaMax, int Rz, void Ani)
{// Attack interruption with range check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float a = getentityproperty(self, "a");
    float z = getentityproperty(self, "z");

    if(target!=NULL()){
      float anim2 = getentityproperty(target, "animationID");
      float Tx = getentityproperty(target, "x");
      float Ta = getentityproperty(target, "a");
      float Tz = getentityproperty(target, "z");

      float Disx = Tx - x;
      float Disa = Ta - a;
      float Disz = Tz - z;

      if(Disz < 0)
	{
        Disz = -Disz;
	}

      if( anim2 == openborconstant("ANI_FALL") || anim2 == openborconstant("ANI_FALL2") || anim2 == openborconstant("ANI_FALL9") || anim2 == openborconstant("ANI_FALL10") || anim2 == openborconstant("ANI_FALL4") || anim2 == openborconstant("ANI_BURN"))
      {
      if(Disx >= RxMin && Disx <= RxMax && Disa >= RaMin && Disa <= RaMax && Disz <= Rz) // right
      	{
        performattack(self, openborconstant(Ani)); //Change player animation
      	} 
	else if(Disx >= -RxMax && Disx <= -RxMin && Disa >= RaMin && Disa <= RaMax && Disz <= Rz) // left
      	{
        performattack(self, openborconstant(Ani)); //Change player animation
      	}
      }
    }
}




void limiter(int Limit)
{// Prevents hero from performing the animation if his/her health is less than Limit
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health"); //Get entity's HP.

   if(Health<=Limit) // Don't have enough HP?
   {
     setidle(self); //Don't play the animation.
   }
}

void norun()
{// Turns off running status
    void self = getlocalvar("self");
    changeentityproperty(self, "aiflag", "running", 0);
}


void nograb(int Flag)
{// Turns grabbable status
    void self = getlocalvar("self");
    changeentityproperty(self, "nograb", Flag);
}


void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}

void hpgain(int Give)
{// gives health
    void self = getlocalvar("self");
    int HP = getentityproperty(self,"health");
	 if(HP > 0)
     {
		changeentityproperty(self, "health", HP+Give); //Spend!
	 }
}

void hpgain2(int normal, int hard, int mania)
{// gives health
    void self = getlocalvar("self");
	void mania2 = getglobalvar("mania");
	void hard2 = getglobalvar("hard");
    int HP = getentityproperty(self,"health");

	 if (HP > 0)
	 {
		if (hard2 == 0)
		 {
			changeentityproperty(self, "health", HP+normal); //Spend!
		 }
		else if (mania2 == 0)
		 {
			changeentityproperty(self, "health", HP+hard); //Spend!
		 }
		else if (mania2 == 1)
		 {
			changeentityproperty(self, "health", HP+mania); //Spend!
		 }
	 }
}


void mpgain(int Give)
{// gives mp
    void self = getlocalvar("self");
    int MP = getentityproperty(self,"mp");
    changeentityproperty(self, "mp", MP+Give); //Spend!
}


void spawnGun(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and bind it
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
}

void spawnChild8(void Name, float dx, float dy, float dz, int Num)
{ // Spawn entity and set it as child, store it and bind it
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "parent", self);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
}

void spawnGun2(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun, store it and doesnt bind it, spawn position relative to screen Ani
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn02(Name, dx, dy, dz);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   performattack(Spawn, openborconstant(Ani));
}

void spawnGun4(void Name, float dx, float dy, float dz, int Face, int Num)
{ // Spawn gun, store it and bind it, facing direct
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, Face, 0); // Bind spawned gun
}

void spawnChild5(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun, store it and doesnt bind it, spawn position relative to screen Ani
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn02(Name, dx, dy, dz);
   changeentityproperty(Spawn, "parent", self);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   performattack(Spawn, openborconstant(Ani));
}

void spawnGun5(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun with ani animation, store it and bind it
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   performattack(Spawn, openborconstant(Ani));
}

void spawnChild(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn entity and set it as child with ani animation, store it and bind it
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, dz);
   changeentityproperty(Spawn, "parent", self);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   performattack(Spawn, openborconstant(Ani));
}

void spawnChild7(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn entity and set it as child with ani animation and same map, store it and bind it
   void self = getlocalvar("self");
   void iMap = getentityproperty(self, "map");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, dz);
   changeentityproperty(Spawn, "parent", self);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   changeentityproperty(Spawn, "map", iMap);
   performattack(Spawn, openborconstant(Ani));
}

void spawnGun6(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun, store it and doesnt bind it, spawn position relative to screen Ani
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn05(Name, dx, dy, dz);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   performattack(Spawn, openborconstant(Ani));
}



void spawnGun7(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun with ani animation,bind it, set it has parent
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   changeentityproperty(Spawn, "parent", self);
   performattack(Spawn, openborconstant(Ani));
}

void killgun(int Num, int Flag)
{ // Kill bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
      bindentity(Gun, NULL());
      if(Flag==1){
        damageentity(Gun, self, 10000, 0, openborconstant("ATK_NORMAL"));
	setentityvar(self, Num, NULL());
      } else {
        killentity(Gun);
	setentityvar(self, Num, NULL());
      }
    }
}


void flip()
{// Turns around
    void self = getlocalvar("self");
    int Direction = getentityproperty(self, "direction");

    if (Direction == 0){ //Is entity facing left?                  
      changeentityproperty(self, "direction", 1);
    } else {
      changeentityproperty(self, "direction", 0);
    }
}



void block(int Flag)
{// Turns blocking status
    void self = getlocalvar("self");
    changeentityproperty(self, "aiflag", "blocking", Flag);
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
      setlocalvar("Loop" + self, loop+1); // Increment number of loops
      updateframe(self, Frame); //Change frame
    } else if(loop==Limit){ // loops reach limit?
      setlocalvar("Loop" + self, NULL());
    }
}


void grabcheck()
{// Prevents hero from performing the slam if he/she's not grabbing anyone
   void self = getlocalvar("self");
   void target = getentityproperty(self, "grabbing");

   if(target==NULL())
   {
     setidle(self); //Don't perform the slam.
   }
}

void grabcheck2()
{// Prevents enemy from performing the slam if he/she doesn't have any target
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     performattack(self, openborconstant("ANI_IDLE")); //Don't perform the slam.
   }
}



void dethrown()
{// Disables thrown status
    void self = getlocalvar("self");

    changeentityproperty(self, "attacking", 0);
    changeentityproperty(self, "damage_on_landing", 0);
    changeentityproperty(self, "projectile", 0);
}

void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");
    setidle(self);
}

void anti()
{ // Makes grabbed opponent slighty lifted to air
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     tossentity(target, 1, 0, 0); // Toss opponent a little ;)
   }
}

void anichange(void Ani)
{// Animation changer
    void self = getlocalvar("self");

    changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
}

void anichangeMP(void Ani, int min)
{// Animation changer with MP cost
    void self = getlocalvar("self");
    int MP = getentityproperty(self,"mp");
	
	if(MP >= min){		
    changeentityproperty(self, "mp", MP-min); //Cost
    changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
	}
}


void clearSlam()
{
	void self = getlocalvar("self");
	int id = getentityproperty(self, "animationid");
	changeentityproperty(self,"escapehits",id);
	void target = getlocalvar("Target" + self);
	if(target)
	{
		setlocalvar("Target"+self,NULL());
	}
}


void slamstart()
{ // Slam Starter for grab slams
// Use finish or throw after using this
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);
   clearSlam();


   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
     if(target == NULL() || getentityproperty(target, "dead") == 1){ //USED WHEN PLAYER DIES BY TIME OVER AND THE GRABBER IS THE ENEMY
			setidle(self);
		}else{
			setentityvar(self, "grabbed", target);
		}
   }
   if(target!=NULL())
   {
     damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL7")); // Slam Starter
   }
}

void slamstart2()
{ // Slam Starter for nongrab slams
// Use finish or throw after using this
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "opponent");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL7")); // Slam Starter
   }
}


void slamstart3()
{ // Slam Starter for nongrab slams release if obstacle or nongrab type
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "opponent");
     setlocalvar("Target" + self, target);
   }

   if(target!=NULL())
   {

	if(getentityproperty(target, "type")==openborconstant("TYPE_OBSTACLE") || getentityproperty(target, "subtype")==openborconstant("SUBTYPE_NOTGRAB"))
	{
    performattack(self, openborconstant("ANI_PAIN"));
	bindentity(target, NULL());
	}
	else
   	{
     	damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL7")); // Slam Starter
   	}
  }
}



void position(int Frame, float dx, float dy, float dz, int face)
{ // Modify grabbed entity's position relative to grabber
// Use slamstart 1st before using this
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     updateframe(target, Frame);
     bindentity(target, self, dx, dz, dy, face, 0);
   }
}


void depost(int Gr)
{// Release grabbed entity
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     bindentity(target, NULL());

     if(Gr == 1)
     {
       int x = getentityproperty(target, "x");
       int z = getentityproperty(target, "z");
       changeentityproperty(target, "position", x, z, 0);
     }
   }
}





void antiwall(int Dist, int Move, int Distz)
{// Checks if there is wall at defined distance
// If there is wall, entity will be moved away with defined movement
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int z = getentityproperty(self, "z");
   float H;
   float Hz;
   float Hw;

   if(Direction == 0){ //Is entity facing left?                 
      Dist = -Dist; //Reverse Dist to match facing
      Move = -Move; //Reverse Move to match facing
   }

   H = checkwall(x+Dist,z);
   Hz = checkwall(x+Dist,z+Distz);
   Hw = checkwall(x+Dist,z-Distz);

   if(Hz > 0)
   {
     changeentityproperty(self, "position", x, z-Distz);
   }
   if(Hw > 0)
   {
     changeentityproperty(self, "position", x, z+Distz);
   }

   if(H > 0)
   {
     changeentityproperty(self, "position", x+Move);
   }
}


void antiWallG()
{//Checks distance from the walls, used for grab scripts only
 //If inside of the walls, entity will be moved away with defined movement
	void self 		= getlocalvar("self");
	void target 	= getlocalvar("Target" + self);
	int x 			= getentityproperty(self, "x");
	int Tx 			= getentityproperty(target, "x");
	int z 			= getentityproperty(self, "z");
	int Tz 			= getentityproperty(target, "z");
	float wall 		= checkwall(Tx, Tz);

	if(target != NULL()){
		if(wall){
			changeentityproperty(target, "position", x, z);
			changeentityproperty(target, "velocity", NULL(), 0, NULL());
		}
	}
}


void finish(int Damage, int Type, int x, int y, int z, int Face)
{ // Damage as slam finisher
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);
   int SDir = getentityproperty(target,"direction");
   int MDir;

   if(Face==0){ // Same facing?
       MDir = SDir;
   }

   if(Face==1){ // Opposite facing?

     if(SDir==0){ // Facing left?
       MDir = 1;
     } else { MDir = 0;}
   }

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     int dir = getentityproperty(target,"direction"); //Get opponent's facing direction
     if(dir==0){ // Facing left?
       x = -x;
     }

     if(Type==1)
     {
       damageentity(target, self, Damage, 1, openborconstant("ATK_NORMAL")); // 1st Finisher
     }

     if(Type==2)
     {
       damageentity(target, self, Damage, 1, openborconstant("ATK_NORMAL9")); // 2nd Finisher
     }

     tossentity(target, y, x, z); // Toss opponent ;)
     changeentityproperty(target, "direction", MDir);
	 antiWallG();
     setlocalvar("Target"+self, NULL()); //Clears variable
   }
}

void throw(int Damage, int Type, int Vx, int Vy, int Vz, int Face)
{ // Damage as throw finisher
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);
   int z = getentityproperty(self,"z");
   int SDir = getentityproperty(target,"direction");
   int MDir;

   if(Face==0){ // Same facing?
       MDir = SDir;
   }

   if(Face==1){ // Opposite facing?

     if(SDir==0){ // Facing left?
       MDir = 1;
     } else { MDir = 0;}
   }

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     int dir = getentityproperty(target,"direction"); //Get opponent's facing direction
     if(dir==0){ // Facing left?
       Vx = -Vx;
     }

     if(Type==1)
     {
       damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL")); // 1st throw type
     }

     if(Type==2)
     {
       damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL9")); // 2nd throw type
     }

     if(Type==3)
     {
       damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL2")); // 3rd throw type
     }

     changeentityproperty(target, "attacking", 1);
     changeentityproperty(target, "damage_on_landing", Damage);
     changeentityproperty(target, "projectile", 1);
     changeentityproperty(target, "direction", MDir);

     if(z > (openborconstant("PLAYER_MIN_Z") + openborconstant("PLAYER_MAX_Z")) / 2 ) {
       Vz = -Vz ;
     }

     tossentity(target, Vy, Vx, Vz); // Toss opponent ;)
	 antiWallG();
   }
}



//on hold
void antiwall3(int Dist, int Move, int Distz)
{// Checks if there is wall at defined distance
// If there is wall, entity will be moved away with defined movement
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float H;
   float Hz;

   if(Direction == 0){ //Is entity facing left?                  
      Dist = -Dist; //Reverse Dist to match facing
      Move = -Move; //Reverse Move to match facing
   }

   H = checkplatformbelow(x+Dist,z, 5000);
   Hz = checkplatformbelow(x+Dist,z+Distz, 5000);

   if(Hz >= 1)
   {
     changeentityproperty(self, "position", x, z-Distz);
   }

   if(H >= 1)
   {
     changeentityproperty(self, "position", x+Move);
   }
}


void wallhit(int Dist, int Move, float Vy,int Face)
{// Checks if there is wall at defined distance
   void self = getlocalvar("self");
   int SDir = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int z = getentityproperty(self, "z");
   float H;

   if (SDir == 0){ //Is entity facing left?                  
      Dist = -Dist; //Reverse Dist to match facing
      Move = -Move; //Reverse Move to match facing
   }

   H = checkwall(x+Dist,z);

   if(H > 0)
   {
     tossentity(self, Vy, Move, 0);
     changeentityproperty(self, "direction", Face);
   }
}




void hurt(int Damage)
{ // Damage opponent if health is higher than 20
	void self = getlocalvar("self");
	void target = getlocalvar("Target" + self);
	void target1 = getentityproperty(self, "grabbing");
	void target2 = getentityproperty(self, "opponent");

   if(target!=NULL())
   {
     void THealth = getentityproperty(target,"health");
     if(THealth > 20)
     {
       changeentityproperty(target, "health", THealth - Damage);
	   addScore(self,Damage*5);
     }
   }
   else if (target1 !=NULL())
   {
	  void THealth = getentityproperty(target1,"health");
     if(THealth > 20)
     {
       changeentityproperty(target1, "health", THealth - Damage);
	   addScore(self,Damage*5);
     }
   }
   else if (target2 !=NULL())
   {
	  void THealth = getentityproperty(target2,"health");
     if(THealth > 20)
     {
       changeentityproperty(target2, "health", THealth - Damage);
	   addScore(self,Damage*5);
     }
   }
}


void hurt2(int Damage)
{ // Damage without altering opponent's animation + less damage if opponent has less health
// Mainly used for slams
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     int THealth = getentityproperty(target,"health"); //Get target's health
     int TAniPos = getentityproperty(target,"animpos"); //Get target's animation frame
     if(THealth > Damage)
     {
       damageentity(target, self, Damage, 1, openborconstant("ATK_NORMAL7")); // Damage target with desired damage
       updateframe(target, TAniPos);
	   addScore(self,Damage*5);
     } else {
       int Damage2 = THealth - 1;
       damageentity(target, self, Damage2, 1, openborconstant("ATK_NORMAL7")); //Damage target with less damage
       updateframe(target, TAniPos);
	   addScore(self,Damage2*5);
     }
   }
}


void addScore(void ent,void score)
{
	int  PIndex = getentityproperty(ent,"playerindex");
	int  PScore = getplayerproperty(PIndex, "score");
	changeplayerproperty(PIndex, "score", PScore+score);
}


void degravity(int Ratio)
{// Changes antigravity effect
    void self = getlocalvar("self");
    changeentityproperty(self, "antigravity", Ratio);
}

void move(int dx, int dz,int da)
{ // Moves entity freely and ignores obstacles
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int a = getentityproperty(self,"a"); //Get character's a coordinate
    int dir = getentityproperty(self,"direction"); //Get character's facing direction

     if(dir==0){ // Facing left?
      changeentityproperty(self, "position", x-dx, z+dz, a+da); //Move
     }
     else if(dir==1){ // Facing right?
      changeentityproperty(self, "position", x+dx, z+dz, a+da); //Move
     }
}

void dasher( float Vx, float Vy, float Vz )
{// Dash with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move!
}




void leaper( float Vx, float Vy, float Vz )
{// Leap with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    tossentity(self, Vy, Vx, Vz); //Leap!
}

void leap(float Vely)
{// Leap with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    if( Vx!=NULL() && Vz!=NULL() ){
      tossentity(self, Vely, Vx, Vz); //Leap towards target!
    }
}



void airgo(float Vely)
{// Leap with previously attained speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

	float Vx = getentityvar(self, 5); //velocity x

    	if(dir==0){ // Facing left?
      	Vx = -Vx ;
    	}
    tossentity(self, Vely, Vx); //Move!
}

void tossx(int rec, float Vely)
{//keep momentum when canceling jumps with "J" and "S"
void self = getlocalvar("self");
int x = getlocalvar("tossx" + self);//make a local flag to set x speed
int dir = getentityproperty(self,"direction");//get direction
int id = getentityproperty(self, "animationid");//find what animation is being canceled

if ( rec != NULL() ){
 if ( id == openborconstant("ANI_JUMP")){
 setlocalvar("tossx" + self, 0);}
 else if ( id == openborconstant("ANI_FORWARDJUMP")){
 setlocalvar("tossx" + self, 1);}
 else if ( id == openborconstant("ANI_RUNJUMP")){
 setlocalvar("tossx" + self, 3);}
}
else{
    if(dir==0){ // Facing left?
      x = -x ;}
  {
tossentity(self, Vely, x, 0);//set recorded x speed
  }
 }
}





void stop()
{// Stop hero's movement!
    void self = getlocalvar("self");
    changeentityproperty(self, "velocity", 0, 0, 0); //Stop moving!
}

void clearL()
{// Clears all local variables
     clearlocalvar();
}

void slammed(int Damage)
{
   // Hurt self
    void self = getlocalvar("self");
    damageentity(self, self, Damage, 1, openborconstant("ATK_NORMAL9")); // Slam damage is inserted here
    tossentity(self, 2, 0, 0);
}




void slammed2(int Damage)
{
   // Hurt self
    void self = getlocalvar("self");
    damageentity(self, self, Damage, 0, openborconstant("ATK_NORMAL9")); // Slam damage is inserted here
    
}


void keyint(void Ani, int Frame, void Key, int Hflag, int Limit)
{// Change current animation if proper key is pressed or released
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health");  
    int iDir = getentityproperty(self, "direction");  
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    void iRKey;

      if (Key=="U"){ //Up Required?
        iRKey = playerkeys(iPIndex, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey = playerkeys(iPIndex, 0, "movedown"); // "Down"

      } else if (Key=="F"){ //Forward Required?
         iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
      } else if (Key=="B"){ //Forward Required?
         iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"   

      } else if (Key=="J"){ //Jump Required?
        iRKey = playerkeys(iPIndex, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey = playerkeys(iPIndex, 0, "attack"); // "Attack"
      } else if (Key=="S"){ //Special Required?
        iRKey = playerkeys(iPIndex, 0, "special"); // "Special"
      } else if (Key=="A2"){ //Attack2 Required?
        iRKey = playerkeys(iPIndex, 0, "attack2"); // "Attack2"
      } else if (Key=="A3"){ //Attack3 Required?
        iRKey = playerkeys(iPIndex, 0, "attack3"); // "Attack3"
      } else if (Key=="A4"){ //Attack4 Required?
        iRKey = playerkeys(iPIndex, 0, "attack4"); // "Attack4"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey = !iRKey; //Take the opposite condition
	}

      if ((Health > Limit)&&iRKey){
        changeentityproperty(self, "animation", openborconstant(Ani), 2);
      changeentityproperty(self, "animpos", Frame);
//        updateframe(self, Frame);
      }
}

void keyintall(void Ani, int Frame, void Key, int Hflag, int Limit)
{// Change current animation if proper key is pressed or released by any player
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health");  
    int iDir = getentityproperty(self, "direction");  
    void iRKey;
	void iRKey2;
    void iRKey3;

      if (Key=="U"){ //Up Required?
        iRKey = playerkeys(0, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey = playerkeys(0, 0, "movedown"); // "Down"
      } else if (Key=="F"){ //Forward Required?
         iRKey = playerkeys(0, 0, "moveright"); // "Right"
      } else if (Key=="B"){ //Forward Required?
         iRKey = playerkeys(0, 0, "moveleft"); // "Left"   
      } else if (Key=="J"){ //Jump Required?
        iRKey = playerkeys(0, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey = playerkeys(0, 0, "attack"); // "Attack"
      } else if (Key=="S"){ //Special Required?
        iRKey = playerkeys(0, 0, "special"); // "Special"
      } else if (Key=="A2"){ //Attack2 Required?
        iRKey = playerkeys(0, 0, "attack2"); // "Attack2"
      } else if (Key=="A3"){ //Attack3 Required?
        iRKey = playerkeys(0, 0, "attack3"); // "Attack3"
      } else if (Key=="A4"){ //Attack4 Required?
        iRKey = playerkeys(0, 0, "attack4"); // "Attack4"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey = !iRKey; //Take the opposite condition
	}

      if ((Health > Limit)&&iRKey){
        changeentityproperty(self, "animation", openborconstant(Ani), 2);
      changeentityproperty(self, "animpos", Frame);
//        updateframe(self, Frame);
      }
	  
	        if (Key=="U"){ //Up Required?
        iRKey2 = playerkeys(1, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey2 = playerkeys(1, 0, "movedown"); // "Down"
      } else if (Key=="F"){ //Forward Required?
         iRKey2 = playerkeys(1, 0, "moveright"); // "Right"
      } else if (Key=="B"){ //Forward Required?
         iRKey2 = playerkeys(1, 0, "moveleft"); // "Left"   
      } else if (Key=="J"){ //Jump Required?
        iRKey2 = playerkeys(1, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey2 = playerkeys(1, 0, "attack"); // "Attack"
      } else if (Key=="S"){ //Special Required?
        iRKey2 = playerkeys(1, 0, "special"); // "Special"
      } else if (Key=="A2"){ //Attack2 Required?
        iRKey2 = playerkeys(1, 0, "attack2"); // "Attack2"
      } else if (Key=="A3"){ //Attack3 Required?
        iRKey2 = playerkeys(1, 0, "attack3"); // "Attack3"
      } else if (Key=="A4"){ //Attack4 Required?
        iRKey2 = playerkeys(1, 0, "attack4"); // "Attack4"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey2 = !iRKey2; //Take the opposite condition
	}

      if ((Health > Limit)&&iRKey2){
        changeentityproperty(self, "animation", openborconstant(Ani), 2);
      changeentityproperty(self, "animpos", Frame);
//        updateframe(self, Frame);
      }
	  
	        if (Key=="U"){ //Up Required?
        iRKey3 = playerkeys(2, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey3 = playerkeys(2, 0, "movedown"); // "Down"
      } else if (Key=="F"){ //Forward Required?
         iRKey3 = playerkeys(2, 0, "moveright"); // "Right"
      } else if (Key=="B"){ //Forward Required?
         iRKey3 = playerkeys(2, 0, "moveleft"); // "Left"   
      } else if (Key=="J"){ //Jump Required?
        iRKey3 = playerkeys(2, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey3 = playerkeys(2, 0, "attack"); // "Attack"
      } else if (Key=="S"){ //Special Required?
        iRKey3 = playerkeys(2, 0, "special"); // "Special"
      } else if (Key=="A2"){ //Attack2 Required?
        iRKey3 = playerkeys(2, 0, "attack2"); // "Attack2"
      } else if (Key=="A3"){ //Attack3 Required?
        iRKey3 = playerkeys(2, 0, "attack3"); // "Attack3"
      } else if (Key=="A4"){ //Attack4 Required?
        iRKey3 = playerkeys(2, 0, "attack4"); // "Attack4"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey3 = !iRKey3; //Take the opposite condition
	}

      if ((Health > Limit)&&iRKey3){
        changeentityproperty(self, "animation", openborconstant(Ani), 2);
      changeentityproperty(self, "animpos", Frame);
//        updateframe(self, Frame);
      }
}



void keyflip()
{// Change hero's facing direction if left or right is pressed
    void self = getlocalvar("self");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index

    if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
      changeentityproperty(self, "direction", 0); //Face left
    } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
      changeentityproperty(self, "direction", 1); //Face right
    }
}

void keyflipchild()
{// Change hero's facing direction if left or right is pressed
    void self = getlocalvar("self");
	int Par = getentityproperty(self,"parent"); //Get player index	
    int iPIndex = getentityproperty(Par,"playerindex"); //Get player index

    if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
      changeentityproperty(self, "direction", 0); //Face left
    } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
      changeentityproperty(self, "direction", 1); //Face right
    }
}

void keymove(float V)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -V;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = V;
      }

	if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
	  zdir = -V/2;
	} else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
	  zdir = V/2;
      }

	changeentityproperty(self, "velocity", xdir, zdir);
}

void keymoveall(float V)
{// Move if direction button is pressed by any player
      void self = getlocalvar("self");
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(0, 0, "moveleft")){// Left is pressed?
	  xdir = -V;
	} else if(playerkeys(0, 0, "moveright")){// Right is pressed?
	  xdir = V;
	} else if(playerkeys(1, 0, "moveleft")){// Right is pressed?
	  xdir = -V;
	} else if(playerkeys(1, 0, "moveright")){// Right is pressed?
	  xdir = V;
	} else if(playerkeys(2, 0, "moveleft")){// Right is pressed?
	  xdir = -V;
	} else if(playerkeys(2, 0, "moveright")){// Right is pressed?
	  xdir = V;
	}
	  
	if(playerkeys(0, 0, "moveup")){// Up is pressed?
	  zdir = -V/2;
	} else if(playerkeys(0, 0, "movedown")){// Down is pressed?
	  zdir = V/2;
	} else if(playerkeys(1, 0, "moveup")){// Down is pressed?
	  zdir = -V/2;
	} else if(playerkeys(1, 0, "movedown")){// Down is pressed?
	  zdir = V/2;
	} else if(playerkeys(2, 0, "moveup")){// Down is pressed?
	  zdir = -V/2;
	} else if(playerkeys(2, 0, "movedown")){// Down is pressed?
	  zdir = V/2;
	}

	changeentityproperty(self, "velocity", xdir, zdir);
}


void keychild(float V)
{// Move by parent hero if direction button is pressed
      void self = getlocalvar("self");
      int Par = getentityproperty(self,"parent"); //Get player index	  
      int iPIndex = getentityproperty(Par,"playerindex"); //Get player index
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -V;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = V;
      }

	if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
	  zdir = -V/2;
	} else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
	  zdir = V/2;
      }

	changeentityproperty(self, "velocity", xdir, zdir);
}


void keywlk(float V)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -V;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = V;
      }
	if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
	  zdir = -V/2;
	} else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
	  zdir = V/2;
      }

	changeentityproperty(self, "velocity", xdir, zdir);

}


void spawn01(void vName, float fX, float fY, float fZ)
{
	//Damon Vaughn Caskey
	//Spawns entity next to caller


	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
	
    
	return vSpawn; //Return spawn.
}

void spawnChild4(void vName, float fX, float fY, float fZ)
{
	//Damon Vaughn Caskey
	//Spawns entity next to caller


	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "parent", self);
	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
    
	return vSpawn; //Return spawn.
}

void spawn02(void vName, float fX, float fY, float fZ)
{	//Spawns entity based on left screen edge
	//vName: Model name of entity to be spawned in.
	//fX: X distance relative to left edge
	//fY: Y height from ground
        //fZ: Z location adjustment

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
        int XPos = openborvariant("xpos"); //Get screen edge's x position
        int YPos = openborvariant("ypos"); //Get screen edge's y position

	clearspawnentry(); //Clear current spawn entry.
        setspawnentry("name", vName); //Acquire spawn entity by name.

	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY);
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
	return vSpawn; //Return spawn.
}

void spawn03(void vName, float fX, float fY, float fZ, int Face)
{
	//spawn with facing direction


	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
   	int SDir = getentityproperty(self, "direction");
   	int MDir;

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

   	if(Face==0){ // Same facing?
       	MDir = SDir;
   	}

   	if(Face==1){ // Opposite facing?

     	if(SDir==0){ // Facing left?
      	 MDir = 1;
     		} else { MDir = 0;}
   	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY, Face); //Set spawn location.
	changeentityproperty(vSpawn, "direction", MDir); //Set direction.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
    
	return vSpawn; //Return spawn.
}


void spawn05(void vName, int Tx, int Ty, int Tz)
{
	//Spawns entity based on level panel coordinate

    	void self = getlocalvar("self");
    	float x = getentityproperty(self, "x"); // Get entity's x coordinate
    	float z = getentityproperty(self, "z"); // Get entity's z coordinate
	void vSpawn; //Spawn object.

	clearspawnentry(); //Clear current spawn entry.
        setspawnentry("name", vName); //Acquire spawn entity by name.

        setlocalvar("x"+self, (Tx-x));
        setlocalvar("z"+self, (Tz-z));

	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "position", Tx, Tz, Ty); //Set spawn location.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
	return vSpawn; //Return spawn.
}

void spawn06(void vName, int Tx, int Ty, int Tz, void Ani)
{
	//Spawns entity based on level panel coordinate chosse animation

    	void self = getlocalvar("self");
    	float x = getentityproperty(self, "x"); // Get entity's x coordinate
    	float z = getentityproperty(self, "z"); // Get entity's z coordinate
	void vSpawn; //Spawn object.

	clearspawnentry(); //Clear current spawn entry.
        setspawnentry("name", vName); //Acquire spawn entity by name.

        setlocalvar("x"+self, (Tx-x));
        setlocalvar("z"+self, (Tz-z));

	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "position", Tx, Tz, Ty); //Set spawn location.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints	
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}


void spawnAni(void vName, float fX, float fY, float fZ, void Ani)
{

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
	setspawnentry("name", vName); //Acquire spawn entity by name.

	 if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	 }

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	 vSpawn = spawn(); //Spawn in entity.
	 changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	 changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
	 changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
    	 performattack(vSpawn, openborconstant(Ani)); 
	 return vSpawn; //Return spawn.
}

void spawnChild6(void vName, float fX, float fY, float fZ, void Ani)
{

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
	setspawnentry("name", vName); //Acquire spawn entity by name.

	 if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	 }

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	 vSpawn = spawn(); //Spawn in entity.
	 changeentityproperty(vSpawn, "parent", self);
	 changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints	 
	 changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	 changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    	 performattack(vSpawn, openborconstant(Ani)); 
	 return vSpawn; //Return spawn.
}

void spawnAni2(void Name, float dx, float dy, float dz, int iMap, void Ani)
{ 	 //Spawns entity next to caller with ani animation and map number 
	 //example: @cmd spawnAni2 "haduken" 35 1 1 2 "ANI_FOLLOW1"


   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", iMap);
   performattack(Spawn, openborconstant(Ani));
}

void spawnChild3(void Name, float dx, float dy, float dz, int iMap, void Ani)
{ 	 //Spawns entity next to caller with ani animation and map number 
	 //example: @cmd spawnAni2 "haduken" 35 1 1 2 "ANI_FOLLOW1"


   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "parent", self);
   changeentityproperty(Spawn, "map", iMap);
   performattack(Spawn, openborconstant(Ani));
}

void spawnAni3(void vName, float fX, float fY, float fZ, void Ani)
{
	//Spawns entity based on left screen edge with ani change

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
        int XPos = openborvariant("xpos"); //Get screen edge's x position
        int YPos = openborvariant("ypos"); //Get screen edge's y position

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.



	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY); //Set spawn location.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}


void spawnChild2(void vName, float fX, float fY, float fZ, void Ani)
{
	//Spawns entity based on level panel coordinate

 void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
        int XPos = openborvariant("xpos"); //Get screen edge's x position
        int YPos = openborvariant("ypos"); //Get screen edge's y position

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.



	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "parent", self);
	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY); //Set spawn location.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}

void spawnAni4(void vName, int Tx, int Ty, int Tz, void Ani)
{
	//Spawns entity based on level panel coordinate

    	void self = getlocalvar("self");
    	float x = getentityproperty(self, "x"); // Get entity's x coordinate
    	float z = getentityproperty(self, "z"); // Get entity's z coordinate
	void vSpawn; //Spawn object.

	clearspawnentry(); //Clear current spawn entry.
        setspawnentry("name", vName); //Acquire spawn entity by name.

        setlocalvar("x"+self, (Tx-x));
        setlocalvar("z"+self, (Tz-z));

	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "position", Tx, Tz, Ty); //Set spawn location.
	changeentityproperty(vSpawn, "owner", self); //Set owner for hitpoints
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}



void spawn04(void Name, float dx, float dy, float dz, int iMap)
{ // Spawn certain entity and chosse map number
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", iMap);
}




void spawner(void vName, float fX, float fY, float fZ)
{	//Spawns entity next to caller and set them as child.


	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}



void spawnbind(void Name, float dx, float dy, float dz)
{ // Spawn and bind other entity
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   bindentity(Spawn, self, dx, dz, dy, 0, 0);
}

void spawnbind2(void Name, float dx, float dy, float dz, void Ani)
{ // Spawn and bind other entity with animation
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   performattack(Spawn, openborconstant(Ani));
   bindentity(Spawn, self, dx, dz, dy, 0, 0);
}

void spawnbind3(void Name, float dx, float dy, float dz, void Ani)
{ // Spawn and bind other entity with animation set parent
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   performattack(Spawn, openborconstant(Ani));
   changeentityproperty(Spawn, "parent", self);
   bindentity(Spawn, self, dx, dz, dy, 0, 0);
}



void spawnbind4(void Name, float dx, float dy, float dz, int Dir, int Flag)
{ // Spawn entity and bind it with same animation as caller
   void self = getlocalvar("self");
   void Spawn;
   int iMap = getentityproperty(self,"map");

   Spawn = spawn01(Name, dx, dy, dz);
   changeentityproperty(Spawn, "map", iMap);
   bindentity(Spawn, self, dx, dz, dy, Dir, Flag);
}



void shoot(void Shot, float dx, float dy, float dz)
{ // Shooting projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
   changeentityproperty(vShot, "owner", self); //Set owner for hitpoints

   return vShot;
}


void shooter(void Shot, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{ // Shooting projectile with speed control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = shoot(Shot, dx, dy, dz);
   changeentityproperty(vShot, "velocity", Vx, Vz, Vy);
   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }
   changeentityproperty(vShot, "speed", Vx);
}



void shooter3(void Shot, float dx, float dy, float dz, float Vx, float Vy, float Vz, void Ani)
{ // Shooting projectile with speed control with animation
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = shoot(Shot, dx, dy, dz);
   changeentityproperty(vShot, "velocity", Vx, Vz, Vy);
   changeentityproperty(vShot, "speed", Vx);
   performattack(vShot, openborconstant(Ani)); 
}




void toss(void Bomb, float dx, float dy, float dz)
{ // Tossing bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
   changeentityproperty(Bomb, "owner", self); //Set owner for hitpoints
}


void subscreen(int screen)
{// Set's subject to screen
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_screen", screen);
}


void subminz(int minz)
{// Set's subject to minz
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_minz", minz);
}

void submaxz(int maxz)
{// Set's subject to minz
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_maxz", maxz);
}





void target(float Velx, float Velz, float dx, float dz, int Stop)
{// Targetting opponent before leaping or dashing.
// Velx = x Velocity
// Velz = z Velocity
// dx = x added distance
// dz = z added distance
// Stop = flag to stop moving if no target is found

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");

    if (dir == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
    }

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    if( getlocalvar("T"+self) != NULL()){
      void target = getlocalvar("T"+self);
      float Tx = getentityproperty(target, "x");
      float Tz = getentityproperty(target, "z");

      if(Tx < x){
        changeentityproperty(self, "direction", 0);
      } else {
        changeentityproperty(self, "direction", 1);
      }

      x = x+dx;
      z = z+dz;
      float Disx = Tx - x;
      float Disz = Tz - z;

//Set both distance as positive value
      if(Disx < 0){
        Disx = -Disx;
      }

      if(Disz < 0){
        Disz = -Disz;
      }

// Calculate velocity for targetting
      if(Disz < Disx)
      {
        if(Tx < x){
          setlocalvar("x"+self, -Velx);
        } else { setlocalvar("x"+self, Velx); }

        setlocalvar("z"+self, Velx*(Tz-z)/Disx);
      } else {
        if(Tz < z){
          setlocalvar("z"+self, -Velz);
        } else { setlocalvar("z"+self, Velz); }

        setlocalvar("x"+self, Velz*(Tx-x)/Disz);
      }

    } else {
      if(Stop == 1)
      {
        setlocalvar("z"+self, 0);
        setlocalvar("x"+self, 0);
      } else {
        setlocalvar("z"+self, 0);
        if(dir==0){
          setlocalvar("x"+self, -Velx);
        } else { setlocalvar("x"+self, Velx); }
      }
    }
}


void targetPos(float Vy, int Tx, int Tz)
{// Targetting panel certain position before leaping there
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
    setlocalvar("x"+self, (Tx-x)/(60*Vy)); // Calculate Vx then store value in local variable
    setlocalvar("z"+self, (Tz-z)/(60*Vy)); // Calculate Vz then store value in local variable
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



void paus0001(int iToggle, int iTime){
    //paus0001-Damon Vaughn Caskey-11022009
    //Pause or unpause action for all entities except self.

    void vSelf      = getlocalvar("self");             //Caller    
    int  iETime     = openborvariant("elapsed_time");  //Current time.
    int  iMax       = openborvariant("ent_max");       //Entity count.
    int  iEntity;                                      //Loop counter.
    void vEntity;                                      //Target entity.

    for(iEntity=0; iEntity<iMax; iEntity++)
    {    
        vEntity = getentity(iEntity);		       //entity from current loop.        
        
        if (vEntity != vSelf)
        {
            changeentityproperty(vEntity, "frozen", iToggle);            //frozen.
            changeentityproperty(vEntity, "freezetime", iETime + iTime); //frozentime.
        }
    }    
}



void attack1(int RxMin, int RxMax, int Rz, void Ani)
{// Attack interruption with range check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Tz = getentityproperty(target, "z");
      float Disx = Tx - x;
      float Disz = Tz - z;

      if(Disz < 0){
        Disz = -Disz;
      }

      if( Disx >= RxMin && Disx <= RxMax && Disz <= Rz && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -RxMax && Disx <= -RxMin && Disz <= Rz && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}



void tosser(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{ // Tossing bomb with desired speed
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void Shot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   Shot = projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
   tossentity(Shot, Vy, Vx, Vz);
   changeentityproperty(Shot, "speed", Vx); 
}



void tosser3(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz, void Ani)
{ // Tossing bomb with desired speed with ANI animation
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void Shot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx;
      Vx = -Vx;
   }

   Shot = projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
   tossentity(Shot, Vy, Vx, Vz);
   changeentityproperty(Shot, "speed", Vx);
   performattack(Shot, openborconstant(Ani));
}





