
#ifndef TABLES_H
#define TABLES_H

extern const short bit_of_mod_4_x_3[52];
extern const short bit_of_div_4[52];

extern const short flush[8192];
extern const short noflush5[6175];
extern const short noflush6[18395];
extern const short noflush7[49205];
extern const short noflush8[120055];
extern const short noflush9[270270];
extern const unsigned char suits[4609];

extern const unsigned int choose[53][10];
extern const int dp[5][14][10];

extern const char* rank_description[7463][2];

extern const short noflush_plo4[11238500];
extern const short flush_plo4[4099095];

#endif  // TABLES_H