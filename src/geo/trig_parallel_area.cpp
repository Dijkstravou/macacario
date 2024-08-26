// no cp algorithms esse T era int
T signed_area_parallelogram(pt p1, pt p2, pt p3) { return (p2 - p1) ^ (p3 - p2); }

double triangle_area(pt p1, pt p2, pt p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

bool clockwise(pt p1, pt p2, pt p3) { return signed_area_parallelogram(p1, p2, p3) < 0; }

bool counter_clockwise(pt p1, pt p2, pt p3) { return signed_area_parallelogram(p1, p2, p3) > 0; }