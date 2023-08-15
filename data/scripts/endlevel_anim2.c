#import "data/scripts/automv2.c"

void main() {
   void self = getlocalvar("self");

float x = getentityvar(self, 5); //move x
float z = getentityvar(self, 6); //move z
float d = getentityvar(self, 7); //face left right
float p = getentityvar(self, p); //player nº 0 1 2 



   void ene = getentityproperty(p,"entity"); // retrieve player 1 handler

   if ( getentityproperty(p,"exists") ) {
      if ( getentityproperty(ene,"noaicontrol") == 0 ) changeentityproperty(ene,"noaicontrol",1);
      if ( movetoxz(ene,x,z,d,0.5) ) {
         //if ( getentityproperty(ene,"noaicontrol") == 1 ) changeentityproperty(ene,"noaicontrol",0);
         drawstring(200,200,0,"player has finished to move on");
         //killentity(self); // to finish the script
      }
   }

}
