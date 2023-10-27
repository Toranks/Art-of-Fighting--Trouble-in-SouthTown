// Removes scroll pos effect
void main()
{
    void self = getlocalvar("self"); //Get calling entity.
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int XPos = openborvariant("xpos");
    void difficulty = getglobalvar("mania");
	
    changeentityproperty(self, "position", x - XPos);
    performattack(getlocalvar("self"), openborconstant("ANI_FOLLOW12"));

    if(difficulty == 0){
      killentity(self);
    }
}
