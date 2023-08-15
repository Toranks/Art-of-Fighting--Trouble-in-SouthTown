


int draw_clipping(void self, float clipx, float clipy, int color) {
    if ( openborvariant("in_level") ) {
        void spr = getentityproperty(self, "sprite");
        float x = getentityproperty(self, "x");
        float z = getentityproperty(self, "z");
        float a = getentityproperty(self, "a");
        float base = getentityproperty(self, "base");
        int facing = getentityproperty(self, "direction");
        int layer = getentityproperty(self, "setlayer")+2;
        float xpos = openborvariant("xpos");
        float ypos = openborvariant("ypos");
        int colourmap = getentityproperty(self, "colourmap");
        float xshift;
        //float transp = 256;

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
            changedrawmethod(NULL(), "clipw", 256);
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

