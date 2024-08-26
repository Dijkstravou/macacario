// testado no cses
// dei override no == de pontos pra o de long double
bool opposite_vecs(pt v1, pt v2) { return abs(abs(ang(v1, v2)) - PI) < EPS; }

bool checa_ponto_segmento(pt ext1, pt ext2, pt testa) {
    if (ext1 == testa || ext2 == testa) return true;
    if (opposite_vecs(testa - ext1, testa - ext2)) return true;
    return false;
}

bool checa_intersec_segmento(pt p1, pt p2, pt p3, pt p4) {
    pt d1 = p1 - p2;
    pt d2 = p3 - p4;
    if (abs(d1 ^ d2) < EPS) {
        if (checa_ponto_segmento(p1, p2, p3) || checa_ponto_segmento(p1, p2, p4) ||
            checa_ponto_segmento(p3, p4, p1) || checa_ponto_segmento(p3, p4, p2)) {
            return true;
        }
        return false;
    }
    pt inter = intersect(p1, d1, p3, d2);
    if (checa_ponto_segmento(p1, p2, inter) && checa_ponto_segmento(p3, p4, inter)) {
        return true;
    }
    return false;
}