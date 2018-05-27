#include "tqdm.h"

int main() {
    int N = 1000;
    tqdm bar;
    std::cout << "Overhead of loop only:" << std::endl;
    for(int i = 0; i < 10000000; i++) {
        bar.progress(i, 10000000);
    }
    std::cout << "Smooth bar:" << std::endl;
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(1000);
    }
    std::cout << "Basic:" << std::endl;
    bar.set_theme_basic();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(1000);
    }
    std::cout << "Arrow:" << std::endl;
    bar.set_theme_arrow();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(1000);
    }
    std::cout << "Circles:" << std::endl;
    bar.set_theme_circle();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(6000);
    }
    return 0;
}
