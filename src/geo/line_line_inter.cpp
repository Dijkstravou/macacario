// provavelmente so faz sentido se T=long double
// qualquer coisa e so reescrever metendo uns casting
// mas a formula eh isso. testado no cses
pt intersect(pt a1, pt d1, pt a2, pt d2) { return a1 + d1 * (((a2 - a1) ^ d2) / (d1 ^ d2)); }