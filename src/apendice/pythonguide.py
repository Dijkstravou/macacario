if judge:
    import io,os
    input = io.BytesIO(os.read(0,os.fstat(0).st_size)).readline

import sys

sys.stdout.write('Hello')
sys.setrecursionlimit(10**9)