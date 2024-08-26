// Tb da pra pegar um ponto O arbitrario e ir somando as areas
// (com sinal) dos triangulos formados por O e cada par de pontos
// consecutivos do poligono
ld area(const vector<pt>& fig) {
    ld res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        pt p = i ? fig[i - 1] : fig.back();
        pt q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return abs(res) / 2;
}