//
// Created by ahmed on 5/16/2023.
//

#ifndef GRAPHICSPROJ_CLIP_H
#define GRAPHICSPROJ_CLIP_H

#endif //GRAPHICSPROJ_CLIP_H

//using namespace std;

//const int INSIDE = 0; // 0000
//const int LEFT = 1;   // 0001
//const int RIGHT = 2;  // 0010
//const int BOTTOM = 4; // 0100
//const int TOP = 8;    // 1000

int arr[4]={0,0,0,0};
//l r b t

 int x_min = 50;
 int y_min = 50;
 int x_max = 100;
 int y_max = 100;
int code1[4]={0,0,0,0};
int code2[4]={0,0,0,0};

int answer[4];
void  cohenSutherland(double x1, double y1, double x2, double y2) {
code1[0]=0;
code1[1]=0;
code1[2]=0;
code1[3]=0;
code2[0]=0;
code2[1]=0;
code2[2]=0;
code2[3]=0;
    if (x1 < x_min) {
        code1[0]=1;
    } else if (x1 > x_max) {
        code1[1]=1;
    }
    if (y1 < y_min) {
        code1[2]=1;
    } else if (y1 > y_max) {
        code1[3]=1;
    }


    if (x2 < x_min) {
        code2[0]=1;
    } else if (x2 > x_max) {
        code2[1]=1;
    }
    if (y2 < y_min) {
        code2[2]=1;
    } else if (y1 > y_max) {
        code2[3]=1;
    }

    printf("%d%d%d%d\n ",code1[0],code1[1],code1[2],code1[3]);
    printf("%d%d%d%d\n ",code2[0],code2[1],code2[2],code2[3]);

    int ans[4]={int (x1),int(y1),int(x2),int(y2)};
int t=7;
    while (t--) {
        printf("   %d%d%d%d\n ",code1[0],code1[1],code1[2],code1[3]);
        printf("first  %d%d%d%d\n ",code1[0],code1[1],code1[2],code1[3]);

        printf("   %d%d%d%d\n ",code2[0],code2[1],code2[2],code2[3]);
        if ( code1[0]==0&&code1[1]==0&&code1[2]==0&&code1[3]==0 && code2[0]==0&&code2[1]==0&&code2[2]==0&&code2[3]==0   ) {
            printf("in\n ");
            // both endpoints inside rectangle

            answer[0]= ans[0];
            answer[1]= ans[1];
            answer[2]= ans[2];
            answer[3]= ans[3];
            break;
        } else if ((code1[0]==code2[0]&&code2[0]==1)||(code1[1]==code2[1]&&code2[1]==1) ||(code1[2]==code2[2]&&code2[2]==1) ||(code1[3]==code2[3]&&code2[3]==1)) { // both endpoints outside rectangle
            printf("out\n ");
            ans[0]=-1;ans[1]=-1;ans[2]=-1;ans[3]=-1;
            break;
        } else {int ch;
            printf("both\n ");
            double x, y;
            int code_out[4];
            if(code1[0]==0&&code1[1]==0&&code1[2]==0&&code1[3]==0){ch=2;
                printf("b\n ");
            code_out[0]=code2[0];
            code_out[1]=code2[1];
            code_out[2]=code2[2];
            code_out[3]=code2[3];
            }
            else{ch=1;
                printf("a\n ");
                code_out[0]=code1[0];
                code_out[1]=code1[1];
                code_out[2]=code1[2];
                code_out[3]=code1[3];
            }

      //              int * code_out = code1 ? code1 : code2;
            printf("%d%d%d%d\n ",code_out[0],code_out[1],code_out[2],code_out[3]);
            if (code_out[3]==1) {           // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
                printf("foo2\n ");


            } else if (code_out[2]==1) { // point is below the clip rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
                printf("ta7t\n ");

            } else if (code_out[1]==1) {  // point is to the right of clip rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
                printf("right\n ");

            } else if (code_out[0]==1) {   // point is to the left of clip rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
                printf("left\n ");

            }

            if (ch == 1) {
                x1 = x;ans[0]=x;
                y1 = y;ans[1]=y;

                 code1[0]=0;
                 code1[1]=0;
                 code1[2]=0;
                 code1[3]=0;


                if (x1 < x_min) {
                    code1[0]=1;
                } else if (x1 > x_max) {
                    code1[1]=1;
                }
                if (y1 < y_min) {
                    code1[2]=1;
                } else if (y1 > y_max) {
                    code1[3]=1;
                }
                printf("first  %d%d%d%d\n ",code1[0],code1[1],code1[2],code1[3]);

            } else {
                x2 = x;ans[2]=x;
                y2 = y;ans[3]=y;

                code2[0]=0;
                code2[1]=0;
                code2[2]=0;
                code2[3]=0;


                if (x2 < x_min) {
                    code2[0]=1;
                } else if (x2 > x_max) {
                    code2[1]=1;
                }
                if (y2 < y_min) {
                    code2[2]=1;
                } else if (y1 > y_max) {
                    code2[3]=1;
                }
                printf("%d%d%d%d\n ",code2[0],code2[1],code2[2],code2[3]);



            }
        }
    }

}

