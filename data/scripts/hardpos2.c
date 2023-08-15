void main()
  {
    void self = getlocalvar("self");
    void difficulty = getglobalvar("hard");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int XPos = openborvariant("xpos");
	
    changeentityproperty(self, "position", x - XPos);
    performattack(getlocalvar("self"), openborconstant("ANI_FOLLOW10"));

    if(difficulty == 0){
      killentity(self);
    }
  }