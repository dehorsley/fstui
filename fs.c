static void fs(void) 
{
	unsigned int i, n, nx, ny, nw, nh, aw, ah, cols, rows;

	Client *c;

	unsigned int headerh     = 7,
		     headerlbarw = 95,
		     footerh     = 10,
		     footerrbarw = waw/2, // including left border
		     rbarw       = 23;    // including left border

	unsigned int wahe = wah - headerh - footerh,
		     wawe = waw - rbarw,
		     waxe = wax,
		     waye = way + headerh;


	for (n = 0, c = nextvisible(clients); c; c = nextvisible(c->next))
		if (!c->minimized)
			n++;

	if (n == 0) return;

	c = nextvisible(clients);
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;

	// Footer left
	resize(c, wax, waye+wahe, waw-footerrbarw, footerh);
	if (--n == 0) return;
	c = nextvisible(c->next);
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;

	// Footer right
	resize(c, wax+waw-footerrbarw+1, waye+wahe, footerrbarw-1, footerh);
	mvvline(waye+wahe, wax+waw-footerrbarw, ACS_VLINE, footerh);
	mvaddch(waye+wahe, wax+waw-footerrbarw, ACS_TTEE);
	if (--n == 0) return;
	c = nextvisible(c->next);
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;
	

	// Header right 
	resize(c, wax+waw-(waw-headerlbarw-1), way, (waw-headerlbarw-1), headerh);
	mvvline(way, wax+headerlbarw, ACS_VLINE, headerh);
	mvaddch(way, wax+headerlbarw, ACS_TTEE);

	if (--n == 0) return;
	c = nextvisible(c->next);
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;

	// Header left
	resize(c, wax, way, headerlbarw, headerh);

	if (--n == 0) return;
	c = nextvisible(c->next);
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;


	// Right bar
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;
	mvvline(waye, waxe + wawe, ACS_VLINE, wahe);
	mvaddch(waye, waxe + wawe, ACS_TTEE);
	resize(c, waxe + wawe + 1, waye, rbarw-1, wahe);
	if (--n == 0) return;
	c = nextvisible(c->next);
	while (c && c->minimized)
		c = nextvisible(c->next);
	if (!c) return;



	// Standard tile
	unsigned int m, mw, mh, th;
	m  = MAX(1, MIN(n, screen.nmaster));
	mw = n == m ? wawe : screen.mfact * wawe;
	mh = wahe / m;
	th = n == m ? 0 : wahe / (n - m);
	nx = waxe;
	ny = waye;

	for (i = 0; c; c = nextvisible(c->next)) {
		if (c->minimized)
			continue;
		if (i < m) {	/* master */
			nw = mw;
			nh = (i < m - 1) ? mh : (waye + wahe) - ny;
		} else {	/* tile window */
			if (i == m) {
				ny = waye;
				nx += mw;
				mvvline(ny, nx, ACS_VLINE, wahe);
				mvaddch(ny, nx, ACS_TTEE);
				nx++;
				nw = wawe - mw -1;
			}
			nh = (i < n - 1) ? th : (waye + wahe) - ny;
			if (i > m)
				mvaddch(ny, nx - 1, ACS_LTEE);
		}
		resize(c, nx, ny, nw, nh);
		ny += nh;
		i++;
	}

	/* Fill in nmaster intersections */
	if (n > m) {
		ny = waye + mh;
		for (i = 1; i < m; i++) {
			mvaddch(ny, nx - 1, ((ny - 1) % th ? ACS_RTEE : ACS_PLUS));
			ny += mh;
		}
	}
}
