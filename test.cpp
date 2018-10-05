#include "tqdm.h"

int main() {

    int N = 2000;
    tqdm bar;

    std::cout << "Overhead of loop only:" << std::endl;
    for(int i = 0; i < 100000000; i++) {
        bar.progress(i, 100000000);
    }
    bar.finish();


    std::cout << "Basic:" << std::endl;
    bar.reset();
    bar.set_theme_basic();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(1000);
    }
    bar.finish();

    std::cout << "Braille:" << std::endl;
    bar.reset();
    bar.set_theme_braille();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(3000);
    }
    bar.finish();

    std::cout << "Line:" << std::endl;
    bar.reset();
    bar.set_theme_line();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(3000);
    }
    bar.finish();

    std::cout << "Circles:" << std::endl;
    bar.reset();
    bar.set_theme_circle();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(3000);
    }
    bar.finish();

    bar.reset();
    std::cout << "Vertical bars:" << std::endl;
    bar.reset();
    bar.set_theme_vertical();
    for(int i = 0; i < N; i++) {
        bar.progress(i, N);
        usleep(3000);
    }
    bar.finish();

    return 0;
}
