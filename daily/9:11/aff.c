#include <stdio.h>
#include <float.h>

/* English language letter frequencies. */
const float english[] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

static int allowed_a[] = {9, 21, 15, 19, 7, 23, 11, 5, 17, 25};

static void decode(const char *in, char *out, int a, int b) {
    for (int i = 0; in[i]; i++) {
        int c = in[i] - 'A';
        if (c >= 0 && c < 26)
            out[i] = 'a' +  ((c - b) * a + 676) % 26;
        else
            out[i] = in[i];
    }
}

static double score_string(const char *s) {
    int total = 0;
    double counts[26] = {0.0};
    for (; *s; s++) {
        if (*s >= 'a' && *s <= 'z') {
            counts[*s - 'a']++;
            total++;
        }
    }
    double score = 0.0;
    for (int i = 0; i < 26; i++) {
        double diff = 100 * counts[i] / total - english[i];
        score += diff * diff;
    }
    return score;
}

int main(void) {
    char input[1024];
    char output[1024];
    while (fgets(input, sizeof(input), stdin)) {
        double best = DBL_MAX;
        int best_a, best_b;
        for (int b = 0; b < 26; b++) {
            for (int i = 0; i < 10; i++) {
                int a = allowed_a[i];
                decode(input, output, a, b);
                double score = score_string(output);
                if (score < best) {
                    best_a = a;
                    best_b = b;
                    best = score;
                }
            }
        }
        decode(input, output, best_a, best_b);
        fputs(output, stdout);
    }
}

