int draw0002(float fRatio, float fVector){

    /*
    draw0002 - http://www.caskeys.com/dc/?p=1314#draw0002
    Damon Vaughn Caskey
    2008_05_30
	~2011_03_29
	~2012_08_30

    Returns whole integer from incoming location vector after applying fRatio. Primarily for integrating
	visual scaling (see draw0001 - http://www.caskeys.com/dc/?p=1314#draw0001) with bind functions as
	binding	requires whole numbers for location offsets.

    fRatio:		Ratio to apply. Will almost always be the current scale ratio of a caller.
    fVector:	Vector to be scaled and rounded.
    */

    int iNeg = 0;	//Negative flag.

    //Negative number? If so, the conversions below won't work. Temporarily convert to positive integer.
    if (fVector < 0)
	{
        iNeg    = 1;				//Set negative flag.
        fVector = fVector * -1;		//Convert to positive integer.
    }

    fVector += 0.0;					//Vector must be a float, convert here to make sure.
    fVector *= fRatio;				//Apply scale ratio.
    fVector %= (++fVector);			//Remove decimal (binds fail if not passed a whole integer).

	if (!fVector)					//If calculation produces 0, set to 1.
	{
		fVector = 1;
	}

    if (iNeg)						//Vector was a temporary positive?
	{
        fVector = -fVector;			//Convert to negative integer.
    }

    return fVector;					//Return value.
}