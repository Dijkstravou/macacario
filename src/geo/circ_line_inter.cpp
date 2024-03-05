int circ_line_inter(ld r, ld a, ld b, ld c, pt& p1, pt& p2) {
	// Retorna a quantidade de pontos. Salva em p1 e p2. Se só tem 1, p2 não muda
	
	ld x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
	ld dif = c*c-r*r*(a*a+b*b);
	if(dif > EPS) return 0;
	if(dif > -EPS) { // |dif| ~= 0
		p1.x = x0, p1.y = y0;
		return 1;
	}
	ld d = r*r - c*c/(a*a+b*b);
	ld mult = sqrt(d/(a*a+b*b));
	p1.x = x0 + b*mult;
	p2.x = x0 - b*mult;
	p1.y = y0 - a*mult;
	p2.y = y0 + a*mult;
	return 2;
}
