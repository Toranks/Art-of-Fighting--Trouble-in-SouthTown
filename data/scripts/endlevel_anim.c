#import "data/scripts/automv.c"

void main() {
   void self = getlocalvar("self");

float x = getentityvar(self, 5); //move x
float z = getentityvar(self, 6); //move z
float d = getentityvar(self, 7); //face left right
float p = getentityvar(self, 8); //player nº 0 1 2 



   void player = getplayerproperty(p,"entity"); // retrieve player 1 handler

   if ( getentityproperty(player,"exists") ) {
      if ( getentityproperty(player,"noaicontrol") == 0 ) changeentityproperty(player,"noaicontrol",1);
      if ( movetoxz(player,x,z,d,0.5) ) {
         //if ( getentityproperty(player,"noaicontrol") == 1 ) changeentityproperty(player,"noaicontrol",0);
         //drawstring(200,200,0,"player has finished to move on");
         //killentity(self); // to finish the script
      }
   }
}
