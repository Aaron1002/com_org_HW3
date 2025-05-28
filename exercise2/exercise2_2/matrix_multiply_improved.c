void matrix_multiply(int *a, int *b, int *output, int i,
                           int k, int j) {
    for (int ii = 0; ii < i; ii += 8)   // ii for a's & c's row move (down move)
        for (int kk = 0; kk < k; kk += 8)   // kk for a block's row move (right move)   
            for (int jj = 0; jj < j; jj += 8)   // jj for b block's row move (right move)
                
                for (int iii = ii; iii < ((ii + 8 < i) ? (ii + 8) : i); ++iii)  // iii for a's & c's column move
                    for (int kkk = kk; kkk < ((kk + 8 < k) ? (kk + 8) : k); ++kkk)  // kkk for b's column move
                        for (int jjj = jj; jjj < ((jj + 8 < j) ? (jj + 8) : j); ++jjj)  // jjj for b's & c's row move 
                            output[iii * j + jjj] += a[iii * k + kkk] * b[kkk * j + jjj];
}

// c[0] += a[0] * b[0]
// c[1] += a[0] * b[1]
// c[2] += a[0] * b[2]

// c[0] += a[1] * b[3]
// c[1] += a[1] * b[4]
// c[2] += a[1] * b[5]