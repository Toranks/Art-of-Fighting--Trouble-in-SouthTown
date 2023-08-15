#import "data/scripts/shadowtrail.c"

void main()
{
	void player = getlocalvar("self");
	void anim = getentityproperty(player,"animationID");
	void lv = getplayerproperty(player, "lives");
	check_shadow_trail(player);


	if ( anim == openborconstant("ANI_FREESPECIAL27") || anim == openborconstant("ANI_FREESPECIAL26"))
	{
	set_shad_trail_flag(player,1);
    	} 
	else if ( anim == openborconstant("ANI_FREESPECIAL27") || anim == openborconstant("ANI_FREESPECIAL26"))
	{
 	set_shad_trail_flag(player,0);
	} 
	else if ( anim != openborconstant("ANI_FREESPECIAL27") || anim == openborconstant("ANI_FREESPECIAL26"))
	{
        set_shad_trail_flag(player,0);
	}
}