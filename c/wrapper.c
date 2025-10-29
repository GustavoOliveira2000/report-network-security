double mw_log_double (double A) {
    // compute hash
    uint64_t A_bits = * (uint64_t*) &A;
    uint64_t hash_64_bits = A_bits;
    uint64_t hash_32_bits = (hash_64_bits ^ (hash_64_bits >> 32));
    uint64_t hash_16_bits = (hash_32_bits ^ (hash_32_bits >> 16));
    hash_16_bits = hash_16_bits & 0xffff;
    // lookup and return if hit
    if (mw_log_double_table[hash_16_bits][0] == A_bits) {
        return * (double*) &mw_log_double_table[hash_16_bits][1];
    }
    // call original and update table if miss
    double result = log(A);
    mw_log_double_table[hash_16_bits][0] = A_bits;
    mw_log_double_table[hash_16_bits][1] = * (uint64_t*) &result;
    return result;
}