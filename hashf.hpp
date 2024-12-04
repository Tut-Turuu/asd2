typedef unsigned int size_t;


size_t hashf(const char * s) {
    size_t res = 0;
    size_t tmp = 0;
    int i = 0;
    while (s[i] != '\0') {
        for (int j = 0; j < 3; ++j) {
            tmp += s[i];
            tmp = tmp << 8;
        }
        tmp += s[i];
        // for (int j = 0; j < 8; ++j) {
        //     res += tmp;
        //     tmp = tmp << 1;
        // }
        res += tmp;
        tmp = 0;
        ++i;
    }
    return res;
}