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
#define RIPPLE_XSHIFT 3
#define RIPPLE_ASHIFT 0
#define WATER_H_FIX 0

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

    // CHECK EXISTENCE
    if ( !is_name(ripple,"defaultmodel",ENT_RIPPLE_FRONT) || !is_for(ripple,self) ) { slv("ripple",NULL()); ripple = glv("ripple"); }
    if ( !is_name(splash,"defaultmodel",ENT_WATER_SPLASH) || !is_for(splash,self) ) { slv("splash",NULL()); splash = glv("splash"); }

    if ( is_on_puddle ) {
        if ( is_on_base ) {
            if ( is_stopped(self) ) { // Se il pg è fermo crea un ripple per volta
                if ( ripple == NULL() || !gep(ripple,"exists") ) ripple = ripple_spawn(self,"ripple_front","ripple_back",ENT_RIPPLE_FRONT,ENT_RIPPLE_BACK,get_water_map()); // spawn ent if not exists (mem ripple in a localvar)
            } else {
                // Se il pg è in movimento crea nuovi ripple dopo il frame X
                if ( ripple == NULL() || !gep(ripple,"exists") ) ripple = ripple_spawn(self,"ripple_front","ripple_back",ENT_RIPPLE_FRONT,ENT_RIPPLE_BACK,get_water_map());
                else {
                    if ( ripple != NULL() ) {
                        if ( gep(ripple,"animpos") >= ripple_frame ) ripple = ripple_spawn(self,"ripple_front","ripple_back",ENT_RIPPLE_FRONT,ENT_RIPPLE_BACK,get_water_map());
                    }
                }  // fine if ripple exists
            } // fine if is_in_movement
        } // fine if is_on_base

        if ( !was_on_puddle && !was_on_base ) {
            slv("splash",spawn_splash(self,ENT_WATER_SPLASH,SPLASH_SOUNDFX,SPLASH_DOWN_START_FRAME)); // splash down
            splash = glv("splash");
        }

        // adjust splash position for speedy moves
        if ( !check_splash_pos(self,glv("splash"),ENT_WATER_SPLASH) ) slv("splash",NULL());
    } else {
        if ( is_stopped(self) ) {
            delete_ripple(self,"ripple_front","ripple_back",ENT_RIPPLE_FRONT,ENT_RIPPLE_BACK);
            slv("ripple",NULL());
            ripple == glv("ripple");
        }
    }

    if ( was_on_puddle && !is_on_base && was_on_base ) {
        slv("splash",spawn_splash(self,ENT_WATER_SPLASH,SPLASH_SOUNDFX,get_water_map())); // splash up
        splash = glv("splash");
    }

    slv("was_on_puddle",is_on_puddle);
    slv("was_on_base",is_on_base);
    slv("ripple",ripple);
    slv("splash",splash);
}

int is_on_puddle(void self) {
    if ( getlocalvar("is_on_water_puddle") > 0 ) return 1;
    else return 0;
}

void ripple_spawn(void self, char ripple_front, char ripple_back, char front_ripple_name, char back_ripple_name, int map) {
    if ( map == NULL() ) map = 0;

    slv(ripple_front,spawnsubentity_relative(front_ripple_name,RIPPLE_XSHIFT,0.1,RIPPLE_ASHIFT+get_water_height()-WATER_H_FIX,self));
    slv(ripple_back,spawnsubentity_relative(back_ripple_name,0,-1.0,0,glv(ripple_front)));

    //changeentityproperty(glv(ripple_front),"parent",self);
    changeentityproperty(glv(ripple_back),"parent",self);

    changeentityproperty(glv(ripple_front),"map",map);
    changeentityproperty(glv(ripple_back),"map",map);

    return glv(ripple_front);
}

int delete_ripple(void self, char ripple_front, char ripple_back, char front_ripple_name, char back_ripple_name) {
    if ( gep(glv(ripple_front),"exists") ) {
        if ( is_name(glv(ripple_front),"defaultmodel",front_ripple_name) && is_for(glv(ripple_front),self) ) { killentity(glv(ripple_front)); }
    }
    slv(ripple_front,NULL());

    if ( gep(glv(ripple_back),"exists") ) {
        if ( is_name(glv(ripple_back),"defaultmodel",back_ripple_name) && is_for(glv(ripple_back),self) ) { killentity(glv(ripple_back)); }
    }
    slv(ripple_back,NULL());

    return 1;
}

void spawn_splash(void self, char water_splash_name, char splash_sound_name, int frame, int map) {
    void splash;
    float base = gep(self,"base");

    if ( map == NULL() ) map = 0;

    splash = spawnsubentity_relative(water_splash_name,RIPPLE_XSHIFT,1,NULL(),self);
    changeentityproperty(splash,"position",NULL(),NULL(),base+RIPPLE_ASHIFT+get_water_height()-WATER_H_FIX);
    changeentityproperty(splash,"parent",self);
    changeentityproperty(splash,"map",map);

    if ( frame != NULL() ) {
        changeentityproperty(splash,"animpos",frame);
        playsample(loadsample(splash_sound_name));
    }

    return splash;
}

// return 0 if it doesn't exists
int check_splash_pos(void self, void splash, char model_name) {
    if ( gep(splash,"exists") ) {
        int anim_pos = gep(splash,"animpos");

        if ( !is_name(splash,"defaultmodel",model_name) || !is_for(splash,self) ) return 0;

        if ( anim_pos <= SPLASH_DOWN_START_FRAME ) {
            float x = gep(self,"x");
            float z = gep(self,"z");
            float a = gep(self,"y");
            float base = gep(self,"base");
            int dir = gep(self,"direction");
            float ex = gep(splash,"x");
            float xshift = RIPPLE_XSHIFT;

            if ( !dir ) xshift *= -1;
            if ( ex != x+xshift ) {
                cep(splash,"position",x+xshift,z+1,base+RIPPLE_ASHIFT+get_water_height()-WATER_H_FIX);
            }
        } // fine if animpos

        return 1;
    } else return 0; // fine if exists
}

int get_water_map() {
    return glv("water_map");
}

int set_water_map(int value) {
    return slv("water_map",value);
}

int get_water_height() {
    return glv("water_height");
}

int set_water_height(float value) {
    slv("water_height",value);
}

int check_puddle(void self, int no_a_flag) {
    int i;

    if ( getglobalvar("in_menu") != 1 && getlevelproperty("type") != 2 ) {
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
                float height = getentityvar(ent, 2);
                float width = getentityvar(ent, 1);
                float depth = getentityvar(ent, 3);
                float new_base, ezhift, exhift;

                if ( height == NULL() ) height = getentityproperty(ent, "height");
                if ( height == NULL() ) height = 0;
                set_water_height(height);
                set_water_map(getentityvar(ent,"map"));

                if (x > ex) exhift = x-ex;
                else exhift = ex-x;

                if ( getentityvar(ent, 0) == "water_puddle" ) {
                    if ( x <= ex+width && x >= ex && z <= ez+2+depth/2 && z >= ez-depth/2 && a <= ebase+2+height && a >= ebase-2 ) {
                        if ( !check_only_flag || check_only_flag == NULL() ) {
                            draw_clipping_transp(self, 140, height, getentityvar(ent,"transp"));
                            clip_character(self, -190, height);
                            setlocalvar("is_on_water_puddle", 1);
                        } else return 1;
                    } else {
                        if ( !check_only_flag || check_only_flag == NULL() ) {
                            if ( getlocalvar("is_on_water_puddle") == 1 ) {
                                reset_water_puddle_clipping(self);
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

int reset_water_puddle_clipping(void self, int shadow_flag) {
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

int reset_water_puddle(void self) {
    if ( glv("was_on_puddle") != NULL() || glv("was_on_base") != NULL() || glv("is_on_water_puddle") != NULL() ) {
        reset_water_puddle_clipping(self);
        setlocalvar("water_puddle_found",NULL());
        slv("was_on_puddle",NULL());
        slv("was_on_base",NULL());
        slv("is_on_water_puddle",NULL());
    }
}

int clip_character(void self, float clipx, float clipy) {
    if ( openborvariant("in_level") ) {
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

            if ( getentityproperty(self,"gfxshadow") ) changeentityproperty(self,"gfxshadow",0);

            changedrawmethod(self, "cliph", 256);
            changedrawmethod(self, "clipw", 512);
            changedrawmethod(self, "clipx", clipx);
            changedrawmethod(self, "clipy", -256-clipy+a-base);

            setdrawmethod(self, 1, 256, 256, 0, 0, 0, 0, 1, 0, 0, 0, 0, colourmap);

            changedrawmethod(NULL(), "enabled", 0);
            changedrawmethod(NULL(), "reset", 1);
            setdrawmethod(NULL(), 0);
    }
}

int draw_clipping_transp(void self, float clipx, float clipy, int transp) {
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

        if ( x == NULL() ) x = getentityproperty(self, "x");
        if ( z == NULL() ) z = getentityproperty(self, "z");
        if ( a == NULL() ) a = getentityproperty(self, "y");
        if ( base == NULL() ) base = getentityproperty(self, "base");
        if ( facing == NULL() ) facing = getentityproperty(self, "direction");
        if ( transp == NULL() ) transp = 0;

        if ( spr != NULL() ) {
            if (facing == 1) facing = 0;
            else facing = 1;

            changedrawmethod(NULL(), "enabled", 1);
            changedrawmethod(NULL(), "reset", 1);

            changedrawmethod(NULL(), "cliph", 356);
            changedrawmethod(NULL(), "clipw", 512);
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

//----------------------------

void spawnsubentity(char ent, float x, float z, float a) {
    void subent;

      clearspawnentry();
      setspawnentry("name", ent);
      subent = spawn();

      changeentityproperty(subent, "position", x, z, a);

    return subent;
}

void spawnsubentity_parent(char ent, float x, float z, float a, void parent) {
    void subent;

      clearspawnentry();
      setspawnentry("name", ent);
      subent = spawn();

      changeentityproperty(subent, "parent", parent);
      changeentityproperty(subent, "position", x, z, a);

    return subent;
}

void spawnsubentity_relative(char ent, float rx, float rz, float ra, void parent) {
    void subent;
    float x, z, a, base;

      clearspawnentry();
      setspawnentry("name", ent);
      subent = spawn();

      if ( getentityproperty(parent,"exists") ) {
          int p_dir = getentityproperty(parent,"direction");

          if (!p_dir) rx *= -1;
          changeentityproperty(subent, "parent", parent);
          x = getentityproperty(parent, "x");
          z = getentityproperty(parent, "z");
          a = getentityproperty(parent, "y");
          base = getentityproperty(parent, "base");
          changeentityproperty(subent, "direction", p_dir);

          changeentityproperty(subent, "parent", parent);
      } else {
          x = 0;
          z = 0;
          a = 0;
      }

      if ( ra != NULL() ) {
        changeentityproperty(subent, "position", x+rx, z+rz, a+ra);
        changeentityproperty(subent, "base", a+ra);
      } else {
        changeentityproperty(subent, "position", x+rx, z+rz, base);
        changeentityproperty(subent, "base", base);
      }

    return subent;
}

int is_on_base(void self) {
    float a = getentityproperty(self,"y");
    float base = getentityproperty(self,"base");

    if ( a <= base ) return 1;
    else return 0;
}

int is_stopped(void self) {
    float xdir = getentityproperty(self,"xdir");
    float zdir = getentityproperty(self,"zdir");
    float tossv = getentityproperty(self,"tossv");

    if ( xdir == 0 && zdir == 0 && tossv == 0 ) return 1;
    else return 0;
}

int is_name(void self, char model, char name) {
    char model_name = getentityproperty(self, model);

    if ( model_name == name ) return 1;
    else return 0;
}

int is_for(void entity, void orig_owner) {
	 void parent = getentityproperty(entity,"parent");
	 void owner = getentityproperty(entity,"owner");
  	void subentity = getentityproperty(entity, "subentity");

  	if ( parent == NULL() ) parent = owner;
  	if ( parent == NULL() ) parent = subentity;

  	if ( orig_owner == parent ) return 1;
    else return 0;
}

