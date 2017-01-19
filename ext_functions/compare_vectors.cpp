// comparator function to sort vectors with qsort
int compare_vectors(const void * a, const void * b)
{
	// this sort so that element 0 is the lowest
	//cout << "\nvector_compare: comparing " << *(double*)a << " and " << *(double*)b << ". Res:  = " << ( *(double*)b - *(double*)a );

	// recast the args
	const Mount *x = *((const Mount **)a);
	const Mount *y = *((const Mount **)b);

	// do the comparison
	if (x->coord_x > y->coord_x)
	  return 1;  //return -1;

	if (x->coord_x == y->coord_x) {
		if (x->coord_y > y->coord_y)
			return 1;
		else
			return -1;
	}


	if (x->coord_x < y->coord_x)
	    return -1;  //return 1;
}
