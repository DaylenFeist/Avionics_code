const char* datalog_fmt = "time, state, kx134_x, kx134_y, kx134_z, bmp280_alt";

int init_SD();
int write_to_sd_card(const char* str);