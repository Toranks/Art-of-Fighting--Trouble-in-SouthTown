void nograb(int Flag)
{// Turns grabbable status
    void self = getlocalvar("self");
    changeentityproperty(self, "nograb", Flag);
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
    int LandId = openborconstant("ANI_LAND");

//    setidle(self, LandId);
    performattack(self, LandId);
}
