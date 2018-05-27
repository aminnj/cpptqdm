#include "tqdm.h"

int main() {
    int N = 1000;
    tqdm bar;
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(1000);
    }
    bar.set_theme_arrow();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(1000);
    }
    bar.set_theme_circle();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(6000);
    }
    return 0;
}
