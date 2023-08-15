void main()
  {
    void self = getlocalvar("self");
    void difficulty = getglobalvar("mania");

    if(difficulty == 0){
      killentity(self);
    }
  }