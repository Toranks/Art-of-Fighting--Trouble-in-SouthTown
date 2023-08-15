
float abs(float num) {
    if (num < 0) num *= -1;

    return num;
}



int movetoxz(void player, float dir_x, float dir_z, int final_direction) {
    float x = getentityproperty(ene, "x");
    float z = getentityproperty(ene, "z");
    float a = getentityproperty(ene, "y");
    float base = getentityproperty(ene, "base");
    float threshold = 0.99; // precisione
    float speed = getentityproperty(ene,"speed");
    float speed_x, speed_z;

    if ( getentityproperty(ene, "animationid") != openborconstant("ANI_SPAWN") && getentityproperty(ene, "animationid") != openborconstant("ANI_RESPAWN") ) {
        if ( a != base ) changeentityproperty(ene, "position", x, z, base);

        if ( x > dir_x-threshold && x < dir_x+threshold  ) {
            speed_x = 0;
        } else if ( x < dir_x+threshold ) { // pg deve andare a destra
            if ( getentityproperty(ene, "animationid") != openborconstant("ANI_WALK") ) changeentityproperty(ene, "animation", openborconstant("ANI_WALK"));
            changeentityproperty(ene, "direction", 1);
            speed_x = speed;
            if ( (dir_x-x) <= threshold ) speed_x = (dir_x-x)*(2/3); // Impostiamo la velocità proprio uguale alla distanza che manca
        } else if ( x > dir_x-threshold ) { // pg deve andare a sinistra
            if ( getentityproperty(ene, "animationid") != openborconstant("ANI_WALK") ) changeentityproperty(ene, "animation", openborconstant("ANI_WALK"));
            changeentityproperty(ene, "direction", 0);
            speed_x = -1*speed;
            if ( (x-dir_x) <= threshold ) speed_x = -1*(x-dir_x)*(2/3);
        }

        // Diamo la priorità all'animazione UP/DOWN
        if ( z > dir_z-threshold && z < dir_z+threshold  ) {
            speed_z = 0;
        } else if ( z < dir_z+threshold ) { // pg deve andare giù
            if ( getentityproperty(ene, "animationid") != openborconstant("ANI_DOWN") ) changeentityproperty(ene, "animation", openborconstant("ANI_DOWN"));
            speed_z = speed/2;
            if ( (dir_z-z) <= threshold ) speed_z = (dir_z-z)*(2/3);
        } else if ( z > dir_z-threshold ) { // pg deve andare su
            if ( getentityproperty(ene, "animationid") != openborconstant("ANI_UP") ) changeentityproperty(ene, "animation", openborconstant("ANI_UP"));
            speed_z = -1*(speed/2);
            if ( (z-dir_z) <= threshold ) speed_z = -1*(z-dir_z)*(2/3);
        }

        if ( speed_x == 0 && speed_z == 0 ) {
            changeentityproperty(ene, "velocity", speed_x, speed_z, NULL());
            if ( getentityproperty(ene, "animationid") != openborconstant("ANI_IDLE") ) changeentityproperty(ene, "animation", openborconstant("ANI_IDLE"));
            changeentityproperty(ene, "direction", final_direction);

            return 1;
        }

        changeentityproperty(ene, "velocity", speed_x, speed_z, NULL());
    } // fine if spawn

  return 0;
}

