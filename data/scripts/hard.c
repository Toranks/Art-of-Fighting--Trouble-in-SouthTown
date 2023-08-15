void main()
  {
    void self = getlocalvar("self");
    void difficulty = getglobalvar("hard");

    if(difficulty == 0){
      killentity(self);
    }
  }