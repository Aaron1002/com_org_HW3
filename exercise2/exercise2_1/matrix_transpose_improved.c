void matrix_transpose(int n, int *dst, int *src) {
    for (int v = 0; v < n; v += 8) 
        for (int u = 0; u < n; u += 8) 
        
            for (int i = v; i < ((v + 8 < n) ? (v + 8) : n); i++)
                for (int j = u; j < ((u + 8 < n) ? (u + 8) : n); j++)
                    dst[i*n + j] = src[i + n*j];
}

// dst: row-major
// scr: column-major
// order remain, but with 8x8 block size