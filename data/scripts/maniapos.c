void main()
  {
    void self = getlocalvar("self");
    void difficulty = getglobalvar("mania");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int XPos = openborvariant("xpos");
	
    changeentityproperty(self, "position", x - XPos);

    if(difficulty == 0){
      killentity(self);
    }
  }