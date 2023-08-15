#define gpp getplayerproperty
#define cpp changeplayerproperty
#define gep getentityproperty
#define cep changeentityproperty
#define ov  openborvariant
#define cv  changeopenborvariant
#define oc  openborconstant
#define clp changelayerproperty
#define glv getlocalvar
#define slv setlocalvar
#define sev setentityvar
#define gev getentityvar
#define sgv setglobalvar
#define ggv getglobalvar

#define SPLASH_SOUNDFX "data/sounds/water_splash01.wav"
#define ENT_WATER_SPLASH "water_splash"
#define ENT_RIPPLE_FRONT "water_ripple_front"
#define ENT_RIPPLE_BACK  "water_ripple_back"
#define RIPPLE_SPAWNING_FRAMES_PAUSE 2
#define SPLASH_DOWN_START_FRAME 2

int check_ripple(void self) {
    int is_on_puddle;
    int is_on_base;
    int was_on_puddle = glv("was_on_puddle");
    int was_on_base = glv("was_on_base");
    void ripple = glv("ripple");
    void splash = glv("splash");
    int ripple_frame = RIPPLE_SPAWNING_FRAMES_PAUSE;

    is_on_puddle = is_on_puddle(self); // check if this ent is on puddle (like stairs)
    is_on_base = is_on_base(self); // or is in "y" of puddle

    if ( is_on_puddle ) {
        if ( is_on_base ) {
            if ( is_stopped(self) ) { // Se il pg è fermo crea un ripple per volta
                if ( ripple == NULL() || !gep(ripple,"exists") ) ripple = ripple_spawn(self,"ripple_front","ripple_back"); // spawn ent if not exists (mem ripple in a localvar)
                else if ( !is_name(ripple,"defaultmodel",ENT_RIPPLE_FRONT) ) { slv("ripple",NULL()); ripple == glv("ripple"); }
            } else {
                // Se il pg è in movimento crea nuovi ripple dopo il frame X
                if ( ripple == NULL() || !gep(ripple,"exists") ) ripple = ripple_spawn(self,"ripple_front","ripple_back");
                else {
                    if ( !is_name(ripple,"defaultmodel",ENT_RIPPLE_FRONT) ) { slv("ripple",NULL()); ripple == glv("ripple"); }
                    if ( ripple != NULL() ) {
                        if ( gep(ripple,"animpos") >= ripple_frame ) ripple = ripple_spawn(self,"ripple_front","ripple_back");
                    }
                }  // fine if ripple exists
            } // fine if is_in_movement
        } // fine if is_on_base

        if ( !was_on_puddle ) {
            slv("splash",spawn_splash(self,SPLASH_DOWN_START_FRAME)); // splash down
            splash = glv("splash");
        }

        // adjust splash position for speedy moves
        if ( !check_splash_pos(self,glv("splash"),ENT_WATER_SPLASH) ) slv("splash",NULL());
    } else {
        //if ( was_on_puddle ) spawn_splash(self); // splash up
        if ( is_stopped(self) ) {
            delete_ripple("ripple_front","ripple_back");
            slv("ripple",NULL());
            ripple == glv("ripple");
        }
    }

    if ( was_on_puddle && !is_on_base && was_on_base ) spawn_splash(self); // splash up
    //if ( !is_on_base && was_on_base ) spawn_splash(self); // splash up

    slv("was_on_puddle",is_on_puddle);
    slv("was_on_base",is_on_base);
    slv("ripple",ripple);
    slv("splash",splash);
}

int is_on_puddle(void self) {
    if ( getlocalvar("is_on_water_puddle") > 0 ) return 1;
    else return 0;
}

void ripple_spawn(void self, char ripple_front, char ripple_back) {
    slv(ripple_front,spawnsubentity_relative(ENT_RIPPLE_FRONT,3,0.1,NULL(),self));
    slv(ripple_back,spawnsubentity_relative(ENT_RIPPLE_BACK,3,-1.0+0.1,NULL(),self));

    return glv(ripple_front);
}

int delete_ripple(char ripple_front, char ripple_back) {
    if ( gep(glv(ripple_front),"exists") ) {
        killentity(glv(ripple_front));
        slv(ripple_front,NULL());
    }
    if ( gep(glv(ripple_back),"exists") ) {
        killentity(glv(ripple_back));
        slv(ripple_back,NULL());
    }

    return 1;
}

void spawn_splash(void self, int frame) {
    void splash;

    splash = spawnsubentity_relative(ENT_WATER_SPLASH,3,1,NULL(),self);
    if ( frame != NULL() ) {
        changeentityproperty(splash,"animpos",frame);
        playsample(loadsample(SPLASH_SOUNDFX));
    }

    return splash;
}

// return 0 if it doesn't exists
int check_splash_pos(void self, void splash, char model_name) {
    if ( gep(splash,"exists") ) {
        int anim_pos = gep(splash,"animpos");
        char defaultmodel = gep(splash,"defaultmodel");

        if ( defaultmodel != model_name ) return 0;

        if ( anim_pos <= SPLASH_DOWN_START_FRAME ) {
            float x = gep(self,"x");
            int dir = gep(self,"direction");
            float ex = gep(splash,"x");
            float xshift = 3;

            if ( !dir ) xshift *= -1;
            if ( ex != x+xshift ) {
                cep(splash,"position",x+xshift,NULL(),NULL());
            }
        } // fine if animpos

        return 1;
    } else return 0; // fine if exists
}

int check_puddle(void self, int no_a_flag) {
    int i;

    if ( getglobalvar("in_menu") != 1 && getlevelproperty("type") != 2 ) { // Waiting, Select
        for (i = 0; i < openborvariant("count_entities"); ++i) { // openborconstant("MAX_ENTS")
            void ent = getentity(i);

            if ( getentityproperty(ent, "exists") ) {
                if ( getentityvar(ent, 0) == "water_puddle" ) {
                    if ( no_a_flag && no_a_flag != NULL() ) return check_water_puddle_no_a(self, ent);
                    else return check_water_puddle(self, ent, 1);
                }
            } // fine if exists
        } // fine for all_ents

        return 0;
    }
}

int check_water_puddle(void self, void ent, int check_only_flag) {
                int p = getentityproperty(self, "playerindex");
                float x = getentityproperty(self, "x");
                float z = getentityproperty(self, "z");
                float a = getentityproperty(self, "y");
                float base = getentityproperty(self, "base");
                float ex = getentityproperty(ent, "x");
                float ez = getentityproperty(ent, "z");
                float ea = getentityproperty(ent, "y");
                float ebase = getentityproperty(ent, "base");
                float height = getentityproperty(ent, "height");
                float width = getentityvar(ent, 1);
                float depth = getentityvar(ent, 3);
                float new_base, ezhift, exhift;

                // Lunghezza della scala
                if (x > ex) exhift = x-ex;
                else exhift = ex-x;

                if ( getentityvar(ent, 0) == "water_puddle" ) {
                    if ( x <= ex+width && x >= ex && z <= ez+2+depth/2 && z >= ez-depth/2 && a <= ebase+2+height && a >= ebase-2 ) {
                        if ( !check_only_flag || check_only_flag == NULL() ) {
                            draw_clipping_transp(self, 140, height+5, 30);
                            clip_character(self, -190, height);
                            setlocalvar("is_on_water_puddle", 1);
                        } else return 1;
                    } else {
                        if ( !check_only_flag || check_only_flag == NULL() ) {
                            if ( getlocalvar("is_on_water_puddle") == 1 ) {
                                reset_water_puddle(self);
                                setlocalvar("is_on_water_puddle", NULL());
                            }
                        } else return 0;
                    } // fine if coords
                }
}

int check_water_puddle_no_a(void self, void ent) {
                float x = getentityproperty(self, "x");
                float z = getentityproperty(self, "z");
                float a = getentityproperty(self, "y");
                float ex = getentityproperty(ent, "x");
                float ez = getentityproperty(ent, "z");
                float ea = getentityproperty(ent, "y");
                float width = getentityvar(ent, 1);
                float depth = getentityvar(ent, 3);

                if ( getentityvar(ent, 0) == "water_puddle" ) {
                    if ( x <= ex+width && x >= ex && z <= ez+2+depth/2 && z >= ez-depth/2 ) {
                        return 1;
                    } else {
                        return 0;
                    } // fine if coords
                }
}

int reset_water_puddle(void self, int shadow_flag) {
    changedrawmethod(NULL(), "enabled", 0);
    changedrawmethod(NULL(), "reset", 1);
    setdrawmethod(NULL(), 0);
    changedrawmethod(self, "enabled", 0);
    changedrawmethod(self, "reset", 1);
    setdrawmethod(self, 0);

    if ( !shadow_flag || shadow_flag == NULL() ) {
        if ( !getentityproperty(self,"gfxshadow") ) changeentityproperty(self,"gfxshadow",1);
    }
}

int clip_character(void self, float clipx, float clipy) {
    /*int anim_id = getentityproperty(self,"animationid");
    int anim_pos = getentityproperty(self,"animpos");

    if ( (anim_id == oc("ANI_SPAWN") || anim_id == oc("ANI_RESPAWN")) && anim_pos <= 1 ) return;*/

    if ( openborvariant("in_level") ) {
        //void spr = getentityproperty(self, "sprite");
        float x = getentityproperty(self, "x");
        float z = getentityproperty(self, "z");
        float a = getentityproperty(self, "y");
        float base = getentityproperty(self, "base");
        int layer = getentityproperty(self, "setlayer");
        float xpos = openborvariant("xpos");
        float ypos = openborvariant("ypos");
        int colourmap = getentityproperty(self, "colourmap");

            changedrawmethod(NULL(), "enabled", 1);
            changedrawmethod(NULL(), "reset", 1);

            //drawstring( 10,190,0,"Var (): "+trunc(xpos));
            if ( getentityproperty(self,"gfxshadow") ) changeentityproperty(self,"gfxshadow",0);

            //changedrawmethod(NULL(), "clip", 10, 20);
            changedrawmethod(self, "cliph", 256); // 75 ----> sono pixel che compongono il quadrato
            changedrawmethod(self, "clipw", 512); // 256 -> se aumento clipw poi devo aumentare anche clipx
            changedrawmethod(self, "clipx", clipx); // -100
            changedrawmethod(self, "clipy", -256-20+a-base); // -100  -> più abbeasi e più tagli
            //changedrawmethod(self, "clipy", -100+a);
            // ####### TOGLI -base se vuoi che cambi il clipy in base a quello!!!

            // (entity, int flag, int scalex, int scaley, int flipx, int flipy, int shiftx, int alpha, int remap, int fillcolor, int rotate, int fliprotate, int transparencybg, void* colourmap, int centerx, int centery);
            //setdrawmethod(self, 1, 256, 256, facing, 0, 0, 6, 1, 0, 0, 0, 0, colourmap); // map: -1 = Use entity's colormap.
            setdrawmethod(self, 1, 256, 256, 0, 0, 0, 0, 1, 0, 0, 0, 0, colourmap); // map: -1 = Use entity's colormap.

            changedrawmethod(NULL(), "enabled", 0);
            changedrawmethod(NULL(), "reset", 1);
            setdrawmethod(NULL(), 0);
    }
}

int draw_clipping_transp(void self, float clipx, float clipy, int transp) {
    /*int anim_id = getentityproperty(self,"animationid");
    int anim_pos = getentityproperty(self,"animpos");

    if ( (anim_id == oc("ANI_SPAWN") || anim_id == oc("ANI_RESPAWN")) && anim_pos <= 1 ) return;*/

    if ( openborvariant("in_level") ) {
        void spr = getentityproperty(self, "sprite");
        float x = getentityvar(self, "x");
        float z = getentityvar(self, "z");
        float a = getentityvar(self, "y");
        float base = getentityvar(self, "base");
        int facing = getentityvar(self, "direction");
        int layer = getentityproperty(self, "setlayer");
        float xpos = openborvariant("xpos");
        float ypos = openborvariant("ypos");
        int colourmap = getentityproperty(self, "colourmap");
        //float transp = 40; //255

        if ( x == NULL() ) x = getentityproperty(self, "x");
        if ( z == NULL() ) z = getentityproperty(self, "z");
        if ( a == NULL() ) a = getentityproperty(self, "y");
        if ( base == NULL() ) base = getentityproperty(self, "base");
        if ( facing == NULL() ) facing = getentityproperty(self, "direction");

        if ( spr != NULL() ) {
            if (facing == 1) facing = 0;
            else facing = 1;

            changedrawmethod(NULL(), "enabled", 1);
            changedrawmethod(NULL(), "reset", 1);

            //drawstring( 10,190,0,"Var (): "+trunc(xpos));

            //changedrawmethod(NULL(), "clip", 10, 20);
            changedrawmethod(NULL(), "cliph", 356);
            changedrawmethod(NULL(), "clipw", 512); // se aumento clipw poi devo aumentare anche clipx
            changedrawmethod(NULL(), "clipx", x-xpos-clipx);
            changedrawmethod(NULL(), "clipy", z-a-ypos-4-clipy);

            changedrawmethod(NULL(), "channelg", transp);
            changedrawmethod(NULL(), "channelr", transp);
            changedrawmethod(NULL(), "channelb", transp);

            // (entity, int flag, int scalex, int scaley, int flipx, int flipy, int shiftx, int alpha, int remap, int fillcolor, int rotate, int fliprotate, int transparencybg, void* colourmap, int centerx, int centery);
            setdrawmethod(NULL(), 1, 256, 256, facing, 0, 0, 6, 1, 0, 0, 0, 0, colourmap); // map: -1 = Use entity's colormap.

            drawsprite(spr, x-xpos, z-a-ypos-4, z+2, layer);

            changedrawmethod(NULL(), "enabled", 0);
            changedrawmethod(NULL(), "reset", 1);
            setdrawmethod(NULL(), 0);
        }

    }
}


int draw_clipping_color(void self, float clipx, float clipy, int color) {
    if ( openborvariant("in_level") ) {
        void spr = getentityproperty(self, "sprite");
        float x = getentityvar(self, "x");
        float z = getentityvar(self, "z");
        float a = getentityvar(self, "y");
        float base = getentityvar(self, "base");
        int facing = getentityvar(self, "direction");
        int layer = getentityproperty(self, "setlayer");
        float xpos = openborvariant("xpos");
        float ypos = openborvariant("ypos");
        int colourmap = getentityproperty(self, "colourmap");
        float exhift;
        //float transp = 40; //255

        if ( x == NULL() ) x = getentityproperty(self, "x");
        if ( z == NULL() ) z = getentityproperty(self, "z");
        if ( a == NULL() ) a = getentityproperty(self, "y");
        if ( base == NULL() ) base = getentityproperty(self, "base");
        if ( facing == NULL() ) facing = getentityproperty(self, "direction");

        if ( spr != NULL() ) {
            if (facing == 1) facing = 0;
            else facing = 1;

            changedrawmethod(NULL(), "enabled", 1);
            changedrawmethod(NULL(), "reset", 1);

            //drawstring( 10,190,0,"Var (): "+trunc(xpos));
            changedrawmethod(NULL(), "tintmode", 1);
            changedrawmethod(NULL(), "tintcolor", color);

            //changedrawmethod(NULL(), "clip", 10, 20);
            changedrawmethod(NULL(), "cliph", 356);
            changedrawmethod(NULL(), "clipw", 256); // se aumento clipw poi devo aumentare anche clipx
            changedrawmethod(NULL(), "clipx", x-xpos-clipx);
            changedrawmethod(NULL(), "clipy", z-a-ypos-4-clipy);

            //changedrawmethod(NULL(), "channelg", transp);
            //changedrawmethod(NULL(), "channelr", transp);
            //changedrawmethod(NULL(), "channelb", transp);

            // (entity, int flag, int scalex, int scaley, int flipx, int flipy, int shiftx, int alpha, int remap, int fillcolor, int rotate, int fliprotate, int transparencybg, void* colourmap, int centerx, int centery);
            setdrawmethod(NULL(), 1, 256, 256, facing, 0, 0, 6, 1, 0, 0, 0, 0, colourmap); // map: -1 = Use entity's colormap.

            drawsprite(spr, x-xpos, z-a-ypos-4, z+2, layer);

            changedrawmethod(NULL(), "enabled", 0);
            changedrawmethod(NULL(), "reset", 1);
            setdrawmethod(NULL(), 0);
        }

    }
}