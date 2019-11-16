	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* PROC loop */

	case 3: // STATE 1
		;
		((P0 *)this)->a = trpt->bup.oval;
		;
		goto R999;

	case 4: // STATE 2
		;
		((P0 *)this)->b = trpt->bup.oval;
		;
		goto R999;

	case 5: // STATE 4
		;
		((P0 *)this)->b = trpt->bup.oval;
		;
		goto R999;

	case 6: // STATE 8
		;
		((P0 *)this)->b = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 7: // STATE 12
		;
		p_restor(II);
		;
		;
		goto R999;
	}

