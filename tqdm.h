#ifndef TQDM_H
#define TQDM_H
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <numeric>
#include <ios>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

class tqdm {
    private:
        std::chrono::time_point<std::chrono::system_clock> t_first = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> t_old = std::chrono::system_clock::now();
        std::vector<double> deq;
        std::vector<const char*> bars = {" ", "▏", "▎", "▍", "▋", "▋", "▊", "▉", "▉"};
        bool in_screen = (system("test $STY") == 0) || (system("test $TMUX") == 0);
        bool is_tty = isatty(1);
        bool use_colors = true;
        bool color_transition = true;
        int width = 40;
        int period = 1;
        int smoothing = 100;
        unsigned long nupdates = 0;

        std::string right_pad = "▏";

        void hsv_to_rgb(float h, float s, float v, int& r, int& g, int& b) {
            if (s < 1e-6) {
                v *= 255.;
                r = v; g = v; b = v;
            }
            int i = (int)(h*6.0);
            float f = (h*6.)-i;
            int p = (int)(255.0*(v*(1.-s)));
            int q = (int)(255.0*(v*(1.-s*f)));
            int t = (int)(255.0*(v*(1.-s*(1.-f))));
            v *= 255;
            i %= 6;
            int vi = (int)v;
            if (i == 0)      { r = vi; g = t;  b = p;  }
            else if (i == 1) { r = q;  g = vi; b = p;  }
            else if (i == 2) { r = p;  g = vi; b = t;  }
            else if (i == 3) { r = p;  g = q;  b = vi; }
            else if (i == 4) { r = t;  g = p;  b = vi; }
            else if (i == 5) { r = vi; g = p;  b = q;  }
        }

    public:
        tqdm() {
            if (in_screen) {
                set_theme_basic();
                color_transition = false;
            }
        }

        void set_theme_arrow() { bars = {" ", "╴", "╾", "━", "━", "━", "━", "━", "─"}; }
        void set_theme_circle() { bars = {" ", "◓", "◑", "◒", "◐", "◓", "◑", "◒", "#"}; }
        void set_theme_basic() {
            bars = {" ", " ", " ", " ", " ", " ", " ", " ", "#"}; 
            right_pad = "|";
        }
        void disable_colors() {
            color_transition = false;
            use_colors = false;
        }

        void progress( int curr, int tot) {
            if (!is_tty) return;
            if(curr%period == 0) {
                nupdates++;
                auto now = std::chrono::system_clock::now();
                double dt = ((std::chrono::duration<double>)(now - t_old)).count();
                double dt_tot = ((std::chrono::duration<double>)(now - t_first)).count();
                t_old = now;
                if (deq.size() >= smoothing) deq.erase(deq.begin());
                deq.push_back(dt);
                double avgdt = std::accumulate(deq.begin(),deq.end(),0.)/deq.size();
                float prate = (float)period/avgdt;
                // learn an appropriate period length to avoid spamming stdout
                // and slowing down the loop 
                if (nupdates > 10 && nupdates % 10 == 0) {
                    period = (int)( std::min(std::max(0.2*pow(10,floor(log10(curr/dt_tot))),10.0), 5e5));
                }
                float peta = (tot-curr)/prate;
                float pct = (float)curr/(tot*0.01);
                if( ( tot - curr ) <= period ) {
                    pct = 100.0;
                    prate = tot/dt_tot;
                    curr = tot;
                    peta = 0;
                }

                float fills = ((float)curr / tot * width);
                int ifills = (int)fills;

                printf("\015 ");
                if (use_colors) {
                    if (color_transition) {
                        // red (hue=0) to green (hue=1/3)
                        int r = 255, g = 255, b = 255;
                        hsv_to_rgb(0.0+0.01*pct/3,0.65,1.0, r,g,b);
                        printf("\033[38;2;%d;%d;%dm ", r, g, b);
                    } else {
                        printf("\033[32m ");
                    }
                }
                for (int i = 0; i < ifills; i++) std::cout << bars[8];
                if (!in_screen and (curr != tot)) printf("%s",bars[(int)(8.0*(fills-ifills))]);
                for (int i = 0; i < width-ifills-1; i++) std::cout << bars[0];
                printf("%s ", right_pad.c_str());
                if (use_colors) printf("\033[1m\033[31m");
                printf("%4.1f%% ", pct);
                if (use_colors) printf("\033[34m");

                std::string unit = "Hz";
                float div = 1.;
                if (prate > 1e6) {
                    unit = "MHz"; div = 1.0e6;
                } else if (prate > 1e3) {
                    unit = "kHz"; div = 1.0e3;
                }
                printf("[%d/%d | %.1f %s | %.0fs<%.0fs] ", curr,tot,  prate/div, unit.c_str(), dt_tot, peta);
                if (use_colors) printf("\033[0m\033[32m\033[0m\015 ");

                if( ( tot - curr ) > period ) fflush(stdout);
                else std::cout << std::endl;

            }
        }
};
#endif
