void matrix_transpose(int n, int *dst, int *src) {
    for (int v=0; v<n/8; v++) 
        for (int u=0; u<n/8; u++) 
            for (int i=0; i<8; i++)
                for (int j=0; j<8; j++)
                    dst[v*8 + u*8*n + i*n + j] = src[8*n*v + 8*u + i + n*j];
    }