void main()
{
    void self = getlocalvar("self");
    int x = getentityproperty(self, "x");
    int XPos = openborvariant("xpos");
    int Screen = openborvariant("hResolution");
    int offset = 50;
    int anim = getentityproperty(self, "animationID");
	int returning = getlocalvar("returning");
    
    // Solo actuar si el enemigo está en IDLE o WALK (ya se ha levantado)
    if (anim == openborconstant("ANI_IDLE") || anim == openborconstant("ANI_WALK")) {
        
        // Si está demasiado a la derecha, correr hacia la izquierda
        if (x > XPos + Screen + offset) {
            changeentityproperty(self, "velocity", -6, 0, 0);
            setlocalvar("returning", 1); // Marcar que está siendo devuelto
			drawstring(10, 10, 0, "ONMOVEXSCRIPT ACTIVE! " + self);
        }
        // Si está demasiado a la izquierda, correr hacia la derecha
        else if (x < XPos - offset) {
            changeentityproperty(self, "velocity", 6, 0, 0);
            setlocalvar("returning", 1); // Marcar que está siendo devuelto
			drawstring(10, 10, 0, "ONMOVEXSCRIPT ACTIVE! " + self);
        }
        // Si ya está dentro Y estaba siendo devuelto, resetear una sola vez
        else if (returning == 1) {
            changeentityproperty(self, "velocity", 0, 0, 0);
            setlocalvar("returning", 0); // Desmarcar
        }
    }
}