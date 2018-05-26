#include "tqdm.h"

int main() {
    int N = 20000;
    tqdm bar;
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(200);
    }
    return 0;
}
