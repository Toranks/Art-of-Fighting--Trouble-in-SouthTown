void main()
  {
    void self = getlocalvar("self");
    void difficulty = getglobalvar("hard");
	
	performattack(self, openborconstant("ANI_FOLLOW9"));

    if(difficulty == 0){
      killentity(self);
    }
  }