#import "data/scripts/lib_water_puddle.c"

void main() {
  void self = getlocalvar("self");

    // ENTITIES COUNT FUNCS
    check_entities(self);

    if ( getlocalvar("water_puddle_found") == 1 ) check_ripple(self);
}

int check_entities(void self) {
    int i = 0;
    int water_puddle_found_flag = 0, water_puddle_is_on = 0;

    if ( openborvariant("in_level") ) {
        if ( getlevelproperty("type") != 2 ) {
            for (i = 0; i < openborvariant("count_entities"); ++i) { // openborconstant("MAX_ENTS")
                void ent = getentity(i);

                if ( getentityproperty(ent, "exists") ) {
                    /// WATER PUDDLE ///
                    if ( getentityvar(ent, 0) == "water_puddle" ) {
                        int anim_id = getentityproperty(self,"animationid");
                        int water_puddle_flag = 0;

                        water_puddle_found_flag = 1;
                        if ( anim_id == openborconstant("ANI_SPAWN") || anim_id == openborconstant("ANI_RESPAWN") ) {
                            int anim_pos = getentityproperty(self,"animpos");
                            if ( anim_pos <= 1 ) water_puddle_flag = 1;
                        }
                        if ( !water_puddle_flag && !water_puddle_is_on ) water_puddle_is_on = check_water_puddle(self, ent);
                        if ( !water_puddle_is_on && getlocalvar("water_puddle_found") != 1 ) setlocalvar("water_puddle_found",1);
                    }
                } // fine if exists
            } // fine for all_ents

            /// WATER PUDDLE RESET ///
            if ( !water_puddle_found_flag || water_puddle_is_on <= 0 ) {
                reset_water_puddle(self);
            }
        } // fine if level prop
    }
}
