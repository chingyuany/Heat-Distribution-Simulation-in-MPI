#include "../include/printcolors.h"

void print_colors(float s[][SIZE])
{
    FILE *fp;
    fp = fopen("./output/output.pnm", "w");
    fprintf(fp, "P3\n%d %d\n15\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (s[i][j] > 250)
            {
                fprintf(fp, "%s", RED);
            }
            else if (s[i][j] > 180 && s[i][j] <= 250)
            {
                fprintf(fp, "%s", ORANGE);
            }
            else if (s[i][j] > 120 && s[i][j] <= 180)
            {
                fprintf(fp, "%s", YELLOW);
            }
            else if (s[i][j] > 80 && s[i][j] <= 120)
            {
                fprintf(fp, "%s", LTGREEN);
            }
            else if (s[i][j] > 60 && s[i][j] <= 80)
            {
                fprintf(fp, "%s", GREEN);
            }
            else if (s[i][j] > 50 && s[i][j] <= 60)
            {
                fprintf(fp, "%s", LTBLUE);
            }
            else if (s[i][j] > 40 && s[i][j] <= 50)
            {
                fprintf(fp, "%s", BLUE);
            }
            else if (s[i][j] > 30 && s[i][j] <= 40)
            {
                fprintf(fp, "%s", DARKTEAL);
            }
            else if (s[i][j] > 20 && s[i][j] <= 30)
            {
                fprintf(fp, "%s", BROWN);
            }
            else
            {
                fprintf(fp, "%s", BLACK);
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    system("convert ./output/output.pnm ./output/output.gif");
}