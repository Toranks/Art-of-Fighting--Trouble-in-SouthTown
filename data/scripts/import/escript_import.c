

void spawngrab(float fX, float fY, float fZ,int HPgv, int Num2, int Num)
{	//Spawns.a.grab---set.it.as.child--with.HP.MAX--opponent.plays.follow
	//opponent.follow.Num=1jumpback
	//		  Num=2dashlow
	//HPgv = amount/time/health -> button press to incress once max is reach grabEscape 

	void self = getlocalvar("self");
  	void vtm = getentityproperty(self, "opponent");
  	int plyr = getentityproperty(vtm, "playerindex");
	void hard = getglobalvar("hard");
	void mania = getglobalvar("mania");
	void vSpawn;	
	vSpawn = spawn02("grab"+plyr, fX, fY, fZ);

        if (vSpawn != NULL()) {
            if(hard == 1){
                if(mania == 1){
                changeentityproperty(vSpawn, "maxhealth", HPgv * 1.1);
                } else if (mania == 0) {
                changeentityproperty(vSpawn, "maxhealth", HPgv * 1.05);
                }
            } else if (hard == 0){
                    changeentityproperty(vSpawn, "maxhealth", HPgv);
            }
        setentityvar(vSpawn, "grabgo", Num2);
		setentityvar(self, Num, vSpawn);
		changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
        return vSpawn;
        } else if (vSpawn == NULL()){
                bindentity(vtm, NULL());
        }
}



void blinking(int on)
{// blinks the entity - 1 on - 0 off
    void self = getlocalvar("self");
    changeentityproperty(self, "blink", on);
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

      if( anim2 == openborconstant("ANI_FALL") || anim2 == openborconstant("ANI_FALL2") || anim2 == openborconstant("ANI_FALL9") || anim2 == openborconstant("ANI_FALL10") || anim2 == openborconstant("ANI_FALL4")|| anim2 == openborconstant("ANI_BURN"))
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



void teleonscreen(float dx, void Ani)
{// Teleport on screen
//  dx : Distance to screen edge

    void self = getlocalvar("self");
    int x = getentityproperty(self,"x");
    int XPos = openborvariant("xpos");
    void player = getplayerproperty(0,"entity");
    float px = getentityproperty(player, "x");
    float pz = getentityproperty(player, "z");


    if(x > XPos + 480 + dx){ // Offscreen to the right?
      changeentityproperty(self, "position", px, pz);
      performattack(self, openborconstant(Ani));
    } else if(x < XPos - dx){ // Offscreen to the left?
      changeentityproperty(self, "position", px, pz);
      performattack(self, openborconstant(Ani));
    }
}


void damage_all_enemies(int damage, int drop, void atk_type)
{
 	int  iEntity; 
        void vEntity;
        void self        = getlocalvar("self");
        int  iMax        = openborvariant("ent_max");   
       
     
        for(iEntity=0; iEntity<iMax; iEntity++)
        {


        vEntity = getentity(iEntity);
		 if(getentityproperty(vEntity, "type")==openborconstant("TYPE_ENEMY"))
		 {
		
		 damageentity(vEntity,self,damage,drop,openborconstant(atk_type));
	
		 }
	 }
 }


void nograb(int Flag)
{// Turns grabbable status
    void self = getlocalvar("self");
    changeentityproperty(self, "nograb", Flag);
}

void block(int Flag)
{// Turns blocking status
    void self = getlocalvar("self");
    changeentityproperty(self, "aiflag", "blocking", Flag);
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
     void THealth = getentityproperty(target,"health"); //Get target's health
     if(THealth > Damage)
     {
       changeentityproperty(target, "health", THealth - Damage); //Damage target with desired damage
     } else {
       changeentityproperty(target, "health", 1); //Damage target with less damage
     }
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
     }
   }
   else if (target1 !=NULL())
   {
	  void THealth = getentityproperty(target1,"health");
     if(THealth > 20)
     {
       changeentityproperty(target1, "health", THealth - Damage);
     }
   }
   else if (target2 !=NULL())
   {
	  void THealth = getentityproperty(target2,"health");
     if(THealth > 20)
     {
       changeentityproperty(target2, "health", THealth - Damage);
     }
   }
}



void anichange(void Ani)
{ // Animation changer
    void self = getlocalvar("self");
    changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
}


void hpgain(int Give)
{// gives health
    void self = getlocalvar("self");
    int HP = getentityproperty(self,"health");
	changeentityproperty(self, "health", HP+Give); //Spend!
}

void mpgain(int Give)
{// gives health
    void self = getlocalvar("self");
    int MP = getentityproperty(self,"mp");
    changeentityproperty(self, "mp", MP+Give); //Spend!
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
    } else if(loop>=Limit){ // loops reach limit?
      setlocalvar("Loop" + self, NULL());
    }
}

void grabcheck()
{// Prevents enemy from performing the slam if he/she's not grabbing anyone
   void self = getlocalvar("self");
   void target = getentityproperty(self, "grabbing");

   if(target==NULL())
   {
//     setidle(self); //Don't perform the slam.
     performattack(self, openborconstant("ANI_IDLE")); //Don't perform the slam.
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
     if(target == NULL() || getentityproperty(target, "dead") == 1){
		setidle(self);
	}else{
     setlocalvar("Target" + self, target);
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
   void target = getentityproperty(self, "opponent");
   void closertarget = findtarget(self);
   void model1 = getentityproperty(target, "model");
   void model2 = getentityproperty(closertarget, "model");

  if(target == NULL() || getentityproperty(target, "dead") == 1){
    setidle(self);
	} else{
		if (model2 == "maturenpc" && model1 == "viceplr")
		{
		target = closertarget;
		}
		else if (model2 == "vicenpc" && model1 == "matureplr")
		{
		target = closertarget;
		}
	setlocalvar("Target" + self, target);
	}  

	if(target!=NULL())
	{
	 damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL7")); // Slam Starter
	}
}


void slamstart3()
{ // Slam Starter for nongrab slams release if obstacle 
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);


   if(target==NULL())
   {
    target = getentityproperty(self, "opponent");
	if(target == NULL() || getentityproperty(target, "dead") == 1){
		setidle(self);
	}else{
    setlocalvar("Target" + self, target);
   }
 }
   if(target!=NULL())
   {

	if(getentityproperty(target, "type")==openborconstant("TYPE_OBSTACLE"))
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






void move(int dx, int dz,int da)
{ // Moves entity freely or ignores obstacles
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


void move2(int Tx, int Tz)
{   //puts enemy in certain coordinates on level panel 
    	void self = getlocalvar("self");

    	float x = getentityproperty(self, "x"); // Get entity's x coordinate
    	float z = getentityproperty(self, "z"); // Get entity's z coordinate

        setlocalvar("x"+self, (Tx-x));
        setlocalvar("z"+self, (Tz-z));

        changeentityproperty(self, "position", Tx, Tz, 0); //set coordinate
}



void changemap(int iMap)
{// Change remap
    void self = getlocalvar("self");
    changeentityproperty(self, "map", iMap); //Change remap
}

void degravity(int Ratio)
{// Changes antigravity effect
    void self = getlocalvar("self");
    changeentityproperty(self, "antigravity", Ratio);
}

void thrown()
{// Sets thrown status
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health"); //Get enemy's health

    if(Health > 0){
      changeentityproperty(self, "attacking", 1);
      changeentityproperty(self, "projectile", 1);
    } else {
      changeentityproperty(self, "animation", openborconstant("ANI_FALL")); //Use normal fall
    }
}

void dethrown()
{// Disables thrown status
    void self = getlocalvar("self");

    changeentityproperty(self, "attacking", 0);
    changeentityproperty(self, "damage_on_landing", 0);
    changeentityproperty(self, "projectile", 0);
}

void land()
{// Lands with land animation
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health"); //Get enemy's health
    int LandId = openborconstant("ANI_LAND");

    if(Health > 0){
      performattack(self, LandId);
    } else {
      damageentity(self, self, 1000, 1, openborconstant("ATK_NORMAL")); // Suicide
    }
}

void clearL()
{ // Clears all local variables
     clearlocalvar();
}



void slammed(int Damage)
{ // Hurt self
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health"); //Get entity's health
    if(Health >= Damage){
      damageentity(self, self, Damage, 1, openborconstant("ATK_NORMAL9")); // Damage is inserted here
    } else if(Health > 0 && Health < Damage){
      damageentity(self, self, Health, 1, openborconstant("ATK_NORMAL9")); // Damage self to death
    } 
    tossentity(self, 2, 0, 0);
}

void spawnGun(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and bind it
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
}



void spawnGun2(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and doesnt DOES NOT bind it
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, dz);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
}



void spawnGun3(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and bind it same map
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   changeentityproperty(Spawn, "map", map);
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
}





void spawnGun4(void Name, float dx, float dy, float dz, int Face, int Num)
{ // Spawn gun, store it and bind it, facing direct
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, Face, 0); // Bind spawned gun
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


void spawnGun6(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and doesnt bind it, spawn position relative to screen
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn02(Name, dx, dy, dz);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
}


void spawnGun7(void Name, float dx, float dy, float dz, int Num, int Dir, void Ani)
{ // Spawn gun with ani animation, store it and bind it + facing + follow
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, Dir, 0); // Bind spawned gun
   performattack(Spawn, openborconstant(Ani));
}

void spawnGun8(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun, store it and doesnt DOES NOT bind it with animation
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, dz);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   performattack(Spawn, openborconstant(Ani));
}


void spawnGun9(void Name, float dx, float dy, float dz, float map, float hp, int Num, void Ani)
{ // Spawn gun with ani animation, store it and bind it choose map but not health (even if it's defined)
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   changeentityproperty(Spawn, "map", map);
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   performattack(Spawn, openborconstant(Ani));
}

void spawnGunHP(void Name, float dx, float dy, float dz, float map, float hp, int Num, void Ani)
{ // Spawn gun with ani animation, store it and bind it choose map and health
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   changeentityproperty(Spawn, "maxhealth", hp);
   changeentityproperty(Spawn, "health", hp);
   changeentityproperty(Spawn, "map", map);
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   performattack(Spawn, openborconstant(Ani));
}



void spawnGun10(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun, store it bind it same map with animation
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   changeentityproperty(Spawn, "map", map);
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
   performattack(Spawn, openborconstant(Ani));
}


void spawnGun11(void Name, float dx, float dy, float dz, int Num, void Ani)
{ // Spawn gun with animation,doesnt bind it, spawn position relative to screen
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn02(Name, dx, dy, dz);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
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

void killgrab()
{ // Kill bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, 8);

    if(Gun!=NULL()){
    bindentity(Gun, NULL());
    killentity(Gun);
	setentityvar(self, 8, NULL());
    }
}

void GunControl(int Num, int Flag, float dx, float dy, float dz)
{ // Bind or release bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
      if(Flag==0){
        bindentity(Gun, NULL());
      } else if(Flag==1){
        bindentity(Gun, self, dx, dz, dy, 0);
      }
    }
}

void gunout(int Num)
{ // unbound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
	bindentity(Gun, NULL());
	setentityvar(self, Num, NULL());
	}
}



void dirspeed()
{ // Match facing direction with x velocity
    void self = getlocalvar("self");
    float Vx = getentityproperty(self, "xdir");

    if (Vx < 0){
      changeentityproperty(self, "direction", 0); //Face left!
    } else if (Vx > 0){
      changeentityproperty(self, "direction", 1); //Face right!
    }
}


void spawnM(void Name, float dx, float dy, float dz)
{ // Spawn certain entity with map choose
   void self = getlocalvar("self");
   void Spawn;
   int iMap = getentityproperty(self,"map");
   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", iMap);
}


void spawnM2(void Name, float dx, float dy, float dz, float map)
{ // Spawn certain entity with map choose
   void self = getlocalvar("self");
   void Spawn;
   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", map);
}

void spawnAnimap(void Name, float dx, float dy, float dz, void Ani)
{ // spawn entity with same map chosse animation
	void self = getlocalvar("self");
	void Spawn;
	int iMap = getentityproperty(self,"map");
	Spawn = spawn01(Name, dx, dy, 0);
	changeentityproperty(Spawn, "map", iMap);
	performattack(Spawn, openborconstant(Ani));
}

void spawnDebris(void Name, float dx, float dy, float dz, void Ani)
{ // spawn entity with same map chosse animation and falling from the sky on a random position
	void self = getlocalvar("self");
	void Spawn;
	int ry = rand()%100+350;
	int rx = rand()%480+480;
	int iMap = getentityproperty(self,"map");
	Spawn = spawn01(Name, dx, dy, 0);
	changeentityproperty(Spawn, "map", iMap);
	changeentityproperty(Spawn, "position", rx, ry, 800);
	performattack(Spawn, openborconstant(Ani));
}



void spawn01(void vName, float fX, float fY, float fZ)
{
	//spawn01 (Generic spawner)
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

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
	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY); //Set spawn location.
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
    
	return vSpawn; //Return spawn.
}


void spawn04(void vName, float fX, float fY, float fZ, void Ani)
{
	//Spawns entity based on left screen edge with animation

	void self = getlocalvar("self");
	void vSpawn; //Spawn object.
        int XPos = openborvariant("xpos");
        int YPos = openborvariant("ypos");

	clearspawnentry();
      	setspawnentry("name", vName);

	vSpawn = spawn();
	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY);
    	performattack(vSpawn, openborconstant(Ani)); 
	return vSpawn;
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
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn
}


void spawname(void vName, float fX, float fY, float fZ, void aka)
{	// Spawn entity with name give

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry();
	setspawnentry("name", vName);

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.
	changeentityproperty(vSpawn, "position", fX, fZ, fY);
	changeentityproperty(vSpawn, "direction", iDirection);
	changeentityproperty(vSpawn, "name", aka);
	return vSpawn; //Return spawn.
}


void spawname2(void vName, float fX, float fY, float fZ, void aka)
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
	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY); //Set spawn location.
	changeentityproperty(vSpawn, "name", aka);
	return vSpawn; //Return spawn.
}




void spawnAniname(void Name, float dx, float dy, float dz)
{ // spawn entity perform caller name attack 
	void self = getlocalvar("self");
	void Spawn;
	void go1 = getentityproperty(self,"name");
	Spawn = spawn01(Name, dx, dy, 0);
	performattack(Spawn, openborconstant(go1));
}


void spawnAniname2(int Tx, int Ty, int Tz, void Ani)
{// Spawns in level panel with same name has caller wit AniAnimation
	void self = getlocalvar("self");
	void vSpawn;
	void vName = getentityproperty(self,"name");
    	float x = getentityproperty(self, "x");
    	float z = getentityproperty(self, "z");
	clearspawnentry();
        setspawnentry("name", vName);
        setlocalvar("x"+self, (Tx-x));
        setlocalvar("z"+self, (Tz-z));
	vSpawn = spawn();
	changeentityproperty(vSpawn, "position", Tx, Tz, Ty);
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn;
}


void spawnAniname3(int Tx, int Ty, int Tz, void Ani)
{// Spawns in level panel with same name has caller wit AniAnimation
	void self = getlocalvar("self");
	void vSpawn;
	void vName = getentityproperty(self,"name");
    	Tx = Tx + getentityproperty(self, "x");
    	Ty = Ty + getentityproperty(self, "a");
    	Tz = Tz + getentityproperty(self, "z");
	clearspawnentry();
        setspawnentry("name", vName);
	vSpawn = spawn();
	changeentityproperty(vSpawn, "position", Tx, Tz, Ty);
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn;
}


void spawnAniname4(void Name, float dx, float dy, float dz)
{ // spawn entity perform caller name attack 
	void self = getlocalvar("self");
	void Spawn;
	void go1 = getentityproperty(self,"name");
	Spawn = spawn01(Name, dx, dy, 0);
	changeentityproperty(Spawn, "parent", self);
	performattack(Spawn, openborconstant(go1));
}




void spawnAni(void vName, float fX, float fY, float fZ, void Ani)
{
	 //spawnB (Generic spawner) + Specific animation + velocities
	 //Damon Vaughn Caskey + Douglas Baldan/O Ilusionista
	 //07/06/2007 - 30/05/2013
	 //
	 //Spawns entity next to caller.
	 //
	 //vName: Model name of entity to be spawned in.
	 //fX: X location adjustment.
	 //fZ: Y location adjustment.
      //fY: Z location adjustment.

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
    	 performattack(vSpawn, openborconstant(Ani)); 
	 return vSpawn; //Return spawn.
}


void spawnAni2(void vName, float fX, float fY, float fZ, void Ani)
{
	//Spawns entity based on left screen edge
	//
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

	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY); //Set spawn location.
	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}

void spawnChild3(void vName, float fX, float fY, float fZ, void Ani)
{ 	//Spawns entity based on left screen edge
	//
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

	changeentityproperty(vSpawn, "parent", self);
	changeentityproperty(vSpawn, "position", fX + XPos, fZ + YPos, fY); //Set spawn location.
	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.


}

void spawnAni3(void vName, int Tx, int Ty, int Tz, void Ani)
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
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}

void spawnChild2(void vName, int Tx, int Ty, int Tz, void Ani)
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
	changeentityproperty(vSpawn, "parent", self);
    	performattack(vSpawn, openborconstant(Ani));
	return vSpawn; //Return spawn.
}


void spawner(void vName, float fX, float fY, float fZ)
{	//Spawns entity next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}

void spawner2(void vName, float fX, float fY, float fZ)
{//Spawns entity next to caller with same remap as spawner's.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iMap = getentityproperty(self, "map");
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "map", iMap); //Use same remap as spawner's.
    
	return vSpawn; //Return spawn.
}


void spawner3(void vName, float fX, float fY, float fZ)
{	//Spawns entity relative to screen and set them as child 
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn02(vName, fX, fY, fZ); //Spawn in entity.

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


void spawnbind2(void Name, float dx, float dy, float dz, int Face)
{ // Spawn and bind other entity with facing direction control
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, dz);
   bindentity(Spawn, self, dx, dz, dy, Face, 0);
}


void spawnbind3(void Name, float dx, float dy, float dz)
{ // Spawn and bind other entity with facing direction control and same remap 
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, dz);
   changeentityproperty(Spawn, "map", map);
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


void spawnbind5(void Name, float dx, float dy, float dz, float map)
{ // Spawn and bind other entity with map choose
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, dz);
   changeentityproperty(Spawn, "map", map);
   bindentity(Spawn, self, dx, dz, dy, 0, 0);
}


void spawnbind6(void Name, float dx, float dy, float dz, void Ani)
{ // Spawn and bind other entity with animation
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   bindentity(Spawn, self, dx, dz, dy, 0, 0);
   performattack(Spawn, openborconstant(Ani));
}



void unbind ()
// unbind entity 24.09.2013 - Douglas Baldan - O Ilusionista
// Usage: @cmd unbind
{
   void    vSelf   = getlocalvar("self");
   bindentity(vSelf, NULL());
}


void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");

    setidle(self, openborconstant("ANI_IDLE"));
}


void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}


void shoot3(void Shot, float dx, float dy, float dz, void Ani)
{ // Shooting targetted projectile with animation
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float Vx = getlocalvar("x"+self);
   float Vz = getlocalvar("z"+self);
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);

   if( Vx!=NULL() && Vz!=NULL() ){
     changeentityproperty(vShot, "velocity", Vx, Vz); //Move projectile towards target!
     if (Vx < 0 && Direction == 1){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 0);
     } else if(Vx > 0 && Direction == 0){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 1); 
     }
     if ( Vx < 0 ){ //Is Vx negative?
       Vx = -Vx;
     }
     changeentityproperty(vShot, "speed", Vx);
     performattack(vShot, openborconstant(Ani)); 
   }
}



void shoot2(void Shot, float dx, float dy, float dz)
{ // Shooting targetted projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float Vx = getlocalvar("x"+self);
   float Vz = getlocalvar("z"+self);
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);

   if( Vx!=NULL() && Vz!=NULL() ){
     changeentityproperty(vShot, "velocity", Vx, Vz); //Move projectile towards target!
     if (Vx < 0 && Direction == 1){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 0);
     } else if(Vx > 0 && Direction == 0){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 1);
     }
     if ( Vx < 0 ){ //Is Vx negative?
       Vx = -Vx;
     }
     changeentityproperty(vShot, "speed", Vx);
   }
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

void shooter2(void Shot, float dx, float dy, float Vx, float Vy)
{ // Shooting special projectile with speed control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = spawn01(Shot, dx, dy, 0);
   changeentityproperty(vShot, "velocity", Vx, 0, Vy);
   return vShot;
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
}

void toss2(void Bomb, float dx, float dy, float dz, float Vy)
{ // Tossing targetted bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float Vx = getlocalvar("x"+self)/2;
   float Vz = getlocalvar("z"+self)/2;
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);

   if( Vx!=NULL() && Vz!=NULL() ){
     tossentity(vShot, Vy, Vx, Vz); //Toss projectile towards target!
     if (Vx < 0 && Direction == 1){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 0);
     } else if(Vx > 0 && Direction == 0){ //Is projectile moving back?
       changeentityproperty(vShot, "direction", 1);
     }
     if ( Vx < 0 ){ //Is Vx negative?
       Vx = -Vx;
     }
     changeentityproperty(vShot, "speed", Vx);
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






void tosser2(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz, int Face)
{ // Tossing bomb with desired speed
   void self = getlocalvar("self");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   int SDir = getentityproperty(self, "direction");
   int MDir;
   void Shot;

   	if(Face==0){ // Same facing?
       	MDir = SDir;
   	}

   	if(Face==1){ // Opposite facing?

     	if(SDir==0){ // Facing left?
      	 MDir = 1;
     		} else { MDir = 0;}
   	}

   Shot = projectile(Bomb, x+dx, z+dz, y+dy, 0, 1, 0, Face);
   changeentityproperty(Shot, "direction", MDir); //Set direction.
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






void tosser4(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz, int iMap)
{ // Tossing bomb with desired speed and map
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
   changeentityproperty(Shot, "map", iMap); //Change remap
   tossentity(Shot, Vy, Vx, Vz);
   changeentityproperty(Shot, "speed", Vx); 
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


void target2(float Velx, float Velz, float dx, float dz, int Stop)
{// Targetting opponent before leaping or dashing move horizontal.
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

  //      setlocalvar("z"+self, Velx*(Tz-z)/Disx);
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



void targetrgt(float Velx, float Velz, float dx, float dz, int Stop)
{// Targetting opponent before leaping or dashing and force face entity right.
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






void targetL(float Vy, float dx, float dz)
{// Targetting opponent before performing targetted leap attack
// Vy = y Velocity
// dx = x added distance
// dz = z added distance

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
      setlocalvar("x"+self, (Tx-x)/(22*Vy));
      setlocalvar("z"+self, (Tz-z)/(22*Vy));

    } else {
      setlocalvar("z"+self, 0);
      setlocalvar("x"+self, 0);
    }
}


void target0(float Velx, float Vely, float Tx, float Ty, float dx, float dy, void Vel, int Flip)
{// Basic Targetting certain coordinate before dashing
// Velx = Desired x Velocity
// Vely = Desired y Velocity
// Tx = target x coordinate
// Ty = target y coordinate
// dx = x added distance
// dy = y added distance
// Vel = Desired output

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Vx;
    float Vy;

    if(Flip == 1){
      if(Tx < x){
        changeentityproperty(self, "direction", 0);
      } else {
        changeentityproperty(self, "direction", 1);
      }
    }

    x = x+dx;
    y = y+dy;
    float Disx = Tx - x;
    float Disy = Ty - y;

//Set both distance as positive value
    if(Disx < 0){
      Disx = -Disx;
    }

    if(Disy < 0){
      Disy = -Disy;
    }

// Calculate velocity for targetting
    if(Disy < Disx)
    {
      if(Tx < x){
        Vx = -Velx;
      } else { Vx = Velx; }

      Vy = Velx*(Ty-y)/Disx;
    } else {
      if(Ty < y){
        Vy = -Vely;
      } else { Vy = Vely; }

      Vx = Vely*(Tx-x)/Disy;
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "y"){
      return Vy;
    }
}

void stopPos(int Tx1, int Tx2, int Tz1, int Tz2)
{// stops at certain square coordinates
    void self = getlocalvar("self");


	int XPos = openborvariant("xpos"); //Get screen edge's position
	int YPos = openborvariant("ypos"); // Get camera y position

	float x = getentityproperty(self, "x"); // Get entity's x coordinate
	float z = getentityproperty(self, "z"); // Get entity's z coordinate

	Tx1 = Tx1+XPos;
	Tx2 = Tx2+XPos;
	Tz1 = Tz1+YPos;
	Tz2 = Tz2+YPos;


    if(Tx1 >= Tx2 && Tz1 >= Tz2){
    changeentityproperty(self, "velocity", 0, 0, 0); //Stop moving!
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
    setlocalvar("x"+self, (Tx-x)/(20*Vy)); // Calculate Vx then store value in local variable
    setlocalvar("z"+self, (Tz-z)/(20*Vy)); // Calculate Vz then store value in local variable
}



void targetCam(float Vy, int Tx, int Tz)
{// Targetting certain position before leaping there
//  Vy : Leaping speed
//  Tx : Leaping destination x coordinate
//  Tz : Leaping destination z coordinate
    void self = getlocalvar("self");
    float x = getentityproperty(self, "x"); // Get entity's x coordinate
    float z = getentityproperty(self, "z"); // Get entity's z coordinate
    int XPos = openborvariant("xpos"); //Get screen edge's position
    int YPos = openborvariant("ypos"); // Get camera position
    Tx=Tx+XPos;
    Tz=Tz+YPos;


    if(Tx < x){
      changeentityproperty(self, "direction", 0); // Face left 
    } else {
      changeentityproperty(self, "direction", 1); // Face right
    }
    setlocalvar("x"+self, (Tx-x)/(20*Vy)); // Calculate Vx then store value in local variable
    setlocalvar("z"+self, (Tz-z)/(20*Vy)); // Calculate Vz then store value in local variable
}

void targetbind(void Name, float Vy, int Tx, int Tz)
{// Targetting certain position before leaping there
//  Name : entity name to be spawned
//  Tx : Leaping destination x coordinate
//  Tz : Leaping destination z coordinate
    void self = getlocalvar("self");
    void Spawn;
    float x = getentityproperty(self, "x"); // Get entity's x coordinate
    float z = getentityproperty(self, "z"); // Get entity's z coordinate
    int XPos = openborvariant("xpos"); //Get screen edge's position
    int YPos = openborvariant("ypos"); // Get camera position
    Tx=Tx+XPos;
    Tz=Tz+YPos;


    if(Tx < x){
      changeentityproperty(self, "direction", 0); // Face left 
    } else {
      changeentityproperty(self, "direction", 1); // Face right
    }
    setlocalvar("x"+self, (Tx-x)/(20*Vy)); // Calculate Vx then store value in local variable
    setlocalvar("z"+self, (Tz-z)/(20*Vy)); // Calculate Vz then store value in local variable
    Spawn = spawn01(Name, Tx, Tz, 0);
    bindentity(Spawn, Tx, Tz, 0, 0, 0);
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

void dash4()
{// Dash with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    if( Vx!=NULL()){
      changeentityproperty(self, "velocity", Vx); //Move towards target!
    }
}



void dash2(float Vy)
{// Dash with previously attained speed + flying speed
// Used by Jetpacks to prevent diving to ground and to fly back up
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vz = getlocalvar("z"+self);
    if( Vx!=NULL() && Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move towards target!
    }
}

void dash3(float Vx, float Vy)
{// Dash with previously attained z speed + defined x and y speed
// Used by Jetpacks to continue moving after diving
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");
    float Vz = getlocalvar("z"+self);

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    if( Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move!
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



void dasher2( float Vx, float Vy, float Vz, int Face )
{// Dash with desired speed and facing direction
    void self = getlocalvar("self");

    changeentityproperty(self, "velocity", Vx, Vz, Vy, Face, 0); //Move!
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




void dodgez( float Vx, float Vy, float Vz )
{// Dodge by moving up or down depending on z location
    void self = getlocalvar("self");
    int z = getentityproperty(self, "z");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    if(z > (openborconstant("PLAYER_MIN_Z") + openborconstant("PLAYER_MAX_Z")) / 2 ) {
      Vz = -Vz ;
    }

    if( Vx!=NULL() && Vy!=NULL() && Vz!=NULL() ){
      changeentityproperty(self, "velocity", Vx, Vz, Vy); //Dodge away!
    }
}

void dodgeleapz( float Vx, float Vy, float Vz )
{// Dodge by leaping up or down depending on z location
    void self = getlocalvar("self");
    int z = getentityproperty(self, "z");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    if(z > (openborconstant("PLAYER_MIN_Z") + openborconstant("PLAYER_MAX_Z")) / 2 ) {
      Vz = -Vz ;
    }

    if( Vx!=NULL() && Vy!=NULL() && Vz!=NULL() ){
      tossentity(self, Vy, Vx, Vz); //Dodge and leap away!
    }
}

void teledodgez( float dx, float dy, float dz )
{// Dodge by teleporting up or down depending on z location
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int a = getentityproperty(self,"a"); //Get character's a coordinate
    int dir = getentityproperty(self,"direction"); //Get character's facing direction
    float H;
    int FZ;

    if(z > (openborconstant("PLAYER_MIN_Z") + openborconstant("PLAYER_MAX_Z")) / 2 ) {
      dz = -dz ;
    }
    FZ = z+dz;

    if(dir==0){ // Facing left?
      dx = -dx ;
    }

    if((z + dz) > openborconstant("PLAYER_MAX_Z")) {
      FZ = openborconstant("PLAYER_MAX_Z");
    } else if((z + dz) < openborconstant("PLAYER_MIN_Z")) {
      FZ = openborconstant("PLAYER_MIN_Z");
    }

    H = checkwall(x+dx,FZ);

    if(H > 0){ // Is there a wall on teleport destination?
      dx = -dx ;
    }

    changeentityproperty(self, "position", x+dx, FZ, a+dy); //Teleport away!
}

void teletarget(int dx, int dy, int dz)
{// Targetting opponent then teleport to target
    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");

    if(dir==0){ // Facing left?
      dx = -dx ;
    }

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    if( getlocalvar("T"+self) != NULL()){
      void target = getlocalvar("T"+self);
      int Tx = getentityproperty(target, "x");
      int Tz = getentityproperty(target, "z");

      changeentityproperty(self, "position", Tx+dx, Tz+dz, dy); //Teleport to target!
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


void stop()
{// Stop enemy's movement!
    void self = getlocalvar("self");
    changeentityproperty(self, "velocity", 0, 0, 0); //Stop moving!
}

void riseattack(int Rx, int Rz, void Ani)
{// Riseattack with range check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Tz = getentityproperty(target, "z");
      float Disx = Tx - x;
      float Disz = Tz - z;

      if(Disx < 0){
        Disx = -Disx;
      }
      if(Disz < 0){
        Disz = -Disz;
      }

      if( Disx <= Rx && Disz <= Rz ) // Target within range?
      {
        if(Tx < x){
          changeentityproperty(self, "direction", 0);
        } else {
          changeentityproperty(self, "direction", 1);
        }
        changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
      } 
    }
}

void riseattack2(int Rx, int Rz, float Velx, float Velz, void Ani)
{// Riseattack with range check + targetting
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Tz = getentityproperty(target, "z");
      float Disx = Tx - x;
      float Disz = Tz - z;

      if(Disx < 0){
        Disx = -Disx;
      }
      if(Disz < 0){
        Disz = -Disz;
      }

      if( Disx <= Rx && Disz <= Rz ) // Target within range?
      {
        if(Tx < x){
          changeentityproperty(self, "direction", 0);
        } else {
          changeentityproperty(self, "direction", 1);
        }

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
        changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
      }
    }
}



void damage(int hp,char ani)
{
		void self=getlocalvar("self");
		if (getentityproperty(self,"health")<=(getentityproperty(self,"maxhealth")*hp/100))
		{
		changeentityproperty(self,"animation",openborconstant(ani));
		}
}



void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");
    setidle(self, openborconstant("ANI_IDLE"));
}




void damage2()
{
    void self = getlocalvar("self");
    int Flag = getlocalvar("Flag" + self);
    int MHealth = getentityproperty(self,"maxhealth"); //get max hp
    int PHealth = 100*getentityproperty(self,"health")/MHealth; //work out hp percentage

 if(Flag == NULL()){
   Flag=0;
 }

if(PHealth<=20 && Flag < 3){performattack(self, openborconstant("ANI_FOLLOW11"));
 }
else if(PHealth<=50 && Flag < 2){performattack(self,openborconstant("ANI_FOLLOW10"));
 }
else if(PHealth<=80 && Flag < 1){performattack(self, openborconstant("ANI_FOLLOW9"));
 }

}




void jonydam()
{ 
    void self = getlocalvar("self");
    int MHealth = getentityproperty(self,"maxhealth"); //get max hp
    int PHealth = 100*getentityproperty(self,"health")/MHealth; //work out hp percentage
    float aggro = getentityproperty(self, "aggression");
    void difficulty = getglobalvar("hard");

if(PHealth<=15 && aggro == 250){performattack(self, openborconstant("ANI_FOLLOW17"));
 }
else if(PHealth<=25 && aggro == 225){performattack(self,openborconstant("ANI_FOLLOW16"));
 }
else if(PHealth<=45 && aggro == 200){performattack(self,openborconstant("ANI_FOLLOW15"));
 }
else if(PHealth<=55 && aggro == 175){performattack(self,openborconstant("ANI_FOLLOW14"));
 }
else if(PHealth<=75 && aggro == 150){performattack(self,openborconstant("ANI_FOLLOW13"));
 }
else if(PHealth<=85 && aggro == 100){performattack(self,openborconstant("ANI_FOLLOW12"));
 }
}



void damchg()
{ 
    void self = getlocalvar("self");
    int MHealth = getentityproperty(self,"maxhealth"); //get max hp
    int PHealth = 100*getentityproperty(self,"health")/MHealth; //work out hp percentage


    float change = getentityvar(self, 5);


if(PHealth<=45 && change == 3){performattack(self, openborconstant("ANI_FOLLOW17"));
 }
else if(PHealth<=70 && change == 2){performattack(self,openborconstant("ANI_FOLLOW16"));
 }
else if(PHealth<=90 && change == 1){performattack(self,openborconstant("ANI_FOLLOW15"));
 }
}


void damchg2()
{ 
    void self = getlocalvar("self");
    int MHealth = getentityproperty(self,"maxhealth"); //get max hp
    int PHealth = 100*getentityproperty(self,"health")/MHealth; //work out hp percentage
    float change = getscriptvar("flagg" + self); 

if(PHealth<=50 && change == 3){performattack(self, openborconstant("ANI_FOLLOW17"));
 }
else if(PHealth<=70 && change == 2){performattack(self,openborconstant("ANI_FOLLOW16"));
 }
else if(PHealth<=90 && change == 1){performattack(self,openborconstant("ANI_FOLLOW15"));
 }
}


void damchg3()
{ 
    void self = getlocalvar("self");
    int MHealth = getentityproperty(self,"maxhealth"); //get max hp
    int PHealth = 100*getentityproperty(self,"health")/MHealth; //work out hp percentage
    float aggro = getentityproperty(self, "aggression"); 

if(PHealth<=25 && aggro == 70){performattack(self, openborconstant("ANI_FOLLOW17"));
 }
else if(PHealth<=50 && aggro == 50){performattack(self,openborconstant("ANI_FOLLOW16"));
 }
else if(PHealth<=75 && aggro == 30){performattack(self,openborconstant("ANI_FOLLOW15"));
 }
}


void layer(int layer)
{// Set's enemy's layer
    void self = getlocalvar("self");
    changeentityproperty(self, "setlayer", layer);
}

void subscreen(int screen)
{// Set's subject to screen
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_screen", screen);
}

void subhole(int hole)
{// Set's subject to hole
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_hole", hole);
}

void subwall(int wall)
{// Set's subject to wall
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_wall", wall);
}

void subplat(int plat)
{// Set's subject to platform
    void self = getlocalvar("self");
    changeentityproperty(self, "subject_to_platform", plat);
}

void lifesp(int tm)
{// Set's lifespan time use delay values 1000
    void self = getlocalvar("self");
    changeentityproperty(self, "lifespancountdown", tm);
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




void attack2(int RxMin, int RxMax, int RaMin, int RaMax, void Ani)
{// Attack interruption with range A check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float a = getentityproperty(self, "a");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Ta = getentityproperty(target, "a");
      float Disx = Tx - x;
      float Disz = Ta - a;



      if( Disx >= RxMin && Disx <= RxMax && Disz >= RaMin && Disz <= RaMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -RxMax && Disx <= -RxMin && Disz >= RaMin && Disz <= RaMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}



void attack3(int RxMin, int RxMax, int RzMin, int RzMax, void Ani)
{// Attack interruption with range ZZZzz check
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


      if( Disx >= RxMin && Disx <= RxMax && Disz >= RzMin && Disz <= RzMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } 
	else if( Disx >= -RxMax && Disx <= -RxMin && Disz >= RzMin && Disz <= RzMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}

void attack4(int RxMin, int RxMax, int RaMin, int RaMax, int RzMin, int RzMax, void Ani)
{// Attack interruption with allrange
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float a = getentityproperty(self, "a");
    float z = getentityproperty(self, "z");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Ta = getentityproperty(target, "a");
      float Tz = getentityproperty(target, "z");
      float Disx = Tx - x;
      float Disa = Ta - a;
      float Disz = Tz - z;

 //     if(Disz < 0){
 //      Disz = -Disz;
 //    }


      if( Disx >= RxMin && Disx <= RxMax && Disa >= RaMin && Disa <= RaMax && Disz >= RzMin && Disz <= RzMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } 
	else if( Disx >= -RxMax && Disx <= -RxMin && Disa >= RaMin && Disa <= RaMax && Disz >= RzMin && Disz <= RzMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}


void spawncounttype(void Name, void vType, float dx, float dy, float dz, float nr)
{ // Spawns entity until number is >
  // example @cmd spawncounttype "insect" "count_enemies" 1 350 1 4  
     void self = getlocalvar("self");
     int ene = openborvariant(vType);
     void Spawn;
     if(ene < nr){
     Spawn = spawn01(Name, dx, dy, 0);
     }
}


void countani(void Ani, void vType, float nr)
{ // Spawns entity until number is >
  // example @cmd countani "ANI_FOLLOW1" "count_enemies" 1  
     void self = getlocalvar("self");
     int ene = openborvariant(vType);
     void Spawn;
     if(ene <= nr){
     changeentityproperty(self, "animation", openborconstant(Ani));
     }
}


void lifeaggr (int Percent, int Aggr)
// Check the life and change the aggression if the health falls below defined percentage (only for MANIA)

{
     void self = getlocalvar("self");
	 void difficulty = getglobalvar("mania");
     int MHealth = getentityproperty(self,"maxhealth");
     int Health = getentityproperty(self,"health");

      if(Health*100 <= Percent*MHealth && difficulty == 1){
        changeentityproperty(self, "aggression", Aggr);
      }	
}
