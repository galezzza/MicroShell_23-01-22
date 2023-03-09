#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

int stepen(int a, int b){
    if(b!=0){
        if(b!=1){
            int c=a;
            for(int i=0; i<b-1; i++){
                a=a*c;
            }
            return a;
        }
        else{
            return a;
        }
    } else{
        return 1;
    }
}
int dayNumber(int day, int month, int year){
    day++;
    int age=year/100;
    int ageco, codeyear, dayofweak;
    int t[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
    if(age%4==0){
        ageco=6;
    }
    if(age%4==1){
        ageco=4;
    }
    if(age%4==2){
        ageco=2;
    }
    if(age%4==3){
        ageco=0;
    }
    codeyear=(ageco+(year%100)+((year%100)/4))%7;
    dayofweak=(day+t[month]+codeyear)%7;
    if(year%4==0){
        if(month<2){
            dayofweak--;
        }
    }
    dayofweak=dayofweak-2;
    if(dayofweak<0){
        dayofweak=dayofweak+7;
    }
    return dayofweak;
}
void KALENDAR(int month, int year){
    int countofdays;
    int k, daynumber;
    printf("MONTH:%d\nYEAR:%d\n", month+1, year);
    daynumber = dayNumber(0, month, year);
    if((month==0)(month==2)(month==4)(month==6)(month==7)(month==9)(month==11)){
        countofdays=31;
    }
    if(month==1){
        if(year%4==0){
            countofdays=29;
        }
        else{
            countofdays=28;
        }
    }
    if((month==3)(month==5)(month==8)(month==10)){
        countofdays=30;
    }
    printf("  Mon  Tue  Wed  Thu  Fri  Sat  Sun\n");
    for ( k = 0; k < daynumber; k++){
        printf("     ");
    }
    for (int j = 1; j <= countofdays; j++) {
        printf("%5d", j);
        if (++k > 6) {
            k = 0;
            printf("\n");
        }
    }
    printf("\n");
}
void CAL(char komanda[100]){
    int kolprobel=0, i=0;
    time_t now;
    struct tm* current_time;
    now = time(NULL);
    current_time = localtime(&now);
    while (komanda[i]!= '\0') {
        if (komanda[i] == ' ') {
            kolprobel++;
        }
        i++;
    }
    if(kolprobel>0){
        char nadkomanda[100];
        char *schowek;
        char *podraz;
        char *argv[3];
        argv[1]=NULL;
        int j=0;
        strcpy(nadkomanda, &komanda[4]);
        schowek = strtok( nadkomanda, "\n");
        podraz = strtok(schowek, " ");
        while (podraz!=NULL) {
            argv[j]=podraz;
            j++;
            podraz=strtok(NULL, " ");
        }
        if(argv[1]!=NULL){
            int e;
            int ee;
            for(int p=0; p< strlen(argv[0]); p++){
                if(argv[0][p]<48){
                    e=1;
                }
                if(argv[0][p]>57){
                    e=1;
                }
            }
            for(int p=0; p< strlen(argv[1]); p++){
                if(argv[1][p]<48){
                    ee=1;
                }
                if(argv[1][p]>57){
                    ee=1;
                }
            }
            if(e!=1){
                if(ee!=1){
                    int b=0;
                    for(int o=0; o<strlen(argv[0]);o++){
                        int a;
                        a=argv[0][strlen(argv[0])-1-o]-'0';
                        b=b+a*stepen(10, o);
                    }
                    int c=0;
                    for(int o=0; o<strlen(argv[1]);o++){
                        int a;
                        a=argv[1][strlen(argv[1])-1-o]-'0';
                        c=c+a*stepen(10, o);
                    }
                    KALENDAR(b-1, c);
                }
                else{
                    printf("error: invalid option %s\n", argv[1]);
                }
            }
            else{
                printf("error: invalid option %s\n", argv[0]);
            }
        }
        else{
            int e;
            for(int p=0; p< strlen(argv[0]); p++){
                if(argv[0][p]<48){
                    e=1;
                }
                if(argv[0][p]>57){
                    e=1;
                }
            }
            if(e!=1){
                int b=0;
                for(int o=0; o<strlen(argv[0]);o++){
                    int a;
                    a=argv[0][strlen(argv[0])-1-o]-'0';
                    b=b+a*stepen(10, o);
                }
                for(int y=0;y<12;y++){
                    KALENDAR(y, b);
                    printf("\n");
                }
            }
            else{
                printf("error: invalid option %s\n", argv[0]);
            }
        }
    }else{
        KALENDAR(current_time->tm_mon, current_time->tm_year+1900);
    }
}
void DATE(char komanda[100]){
    char nadkomanda[100];
    char *schowek;
    time_t now;
    struct tm* current_time;
    now = time(NULL);
    current_time = localtime(&now);
    strcpy(nadkomanda, &komanda[5]);
    schowek = strtok( nadkomanda, "\n");
    for (int u=0, j; schowek[u] != '\0'; u++) {
        while (!(schowek[u]!=' ')&& !(schowek[u] == '\0')) {
            for (j = u; schowek[j] != '\0'; j++) {
                schowek[j] = schowek[j + 1];
            }
            schowek[j] = '\0';
        }
    }
    if((strcmp(schowek, "+%D")==0)(strcmp(schowek, "+%d")==0)(strcmp(schowek, "+%a")==0)(strcmp(schowek, "+%A")==0)(strcmp(schowek, "+%h")==0)(strcmp(schowek, "+%b")==0)(strcmp(schowek, "+%B")==0)(strcmp(schowek, "+%m")==0)(strcmp(schowek, "+%y")==0)(strcmp(schowek, "+%Y")==0)(strcmp(schowek, "+%T")==0)(strcmp(schowek, "+%M")==0)(strcmp(schowek, "+%H")==0)(strcmp(schowek, "+%S")==0)){
        if(strcmp(schowek, "+%D")==0){
            if(current_time->tm_mon+1<10){
                if(current_time->tm_mday<10){
                    printf("0%d/0%d/%d\n",current_time->tm_mon+1, current_time->tm_mday, current_time->tm_year - 100);
                } else{
                    printf("0%d/%d/%d\n",current_time->tm_mon+1, current_time->tm_mday, current_time->tm_year - 100);
                }
            }
            else{
                if(current_time->tm_mday){
                    printf("%d/0%d/%d\n",current_time->tm_mon+1, current_time->tm_mday, current_time->tm_year - 100);
                } else{
                    printf("%d/%d/%d\n",current_time->tm_mon+1, current_time->tm_mday, current_time->tm_year - 100);
                }
            }
        }
        if(strcmp(schowek, "+%d")==0){
            if(current_time->tm_mday<10){
                printf("0%d\n",current_time->tm_mday);
            } else{
                printf("%d\n",current_time->tm_mday);
            }
        }
        if(strcmp(schowek, "+%a")==0){
            if(current_time->tm_wday==0){
                printf("Sun\n");
            }
            if(current_time->tm_wday==1){
                printf("Mon\n");
            }
            if(current_time->tm_wday==2){
                printf("Tue\n");
            }
            if(current_time->tm_wday==3){
                printf("Wed\n");
            }
            if(current_time->tm_wday==4){
                printf("Thu\n");
            }
            if(current_time->tm_wday==5){
                printf("Fri\n");
            }
            if(current_time->tm_wday==6){
                printf("Sat\n");
            }
        }
        if(strcmp(schowek, "+%A")==0){
            if(current_time->tm_wday==0){
                printf("Sunday\n");
            }
            if(current_time->tm_wday==1){
                printf("Monday\n");
            }
            if(current_time->tm_wday==2){
                printf("Tuesday\n");
            }
            if(current_time->tm_wday==3){
                printf("Wednesday\n");
            }
            if(current_time->tm_wday==4){
                printf("Thursday\n");
            }
            if(current_time->tm_wday==5){
                printf("Friday\n");
            }
            if(current_time->tm_wday==6){
                printf("Saturday\n");
            }
        }
        if((strcmp(schowek, "+%h")==0)(strcmp(schowek, "+%b")==0)){
            if(current_time->tm_mon==0){
                printf("Jan\n");
            }
            if(current_time->tm_mon==1){
                printf("Feb\n");
            }
            if(current_time->tm_mon==2){
                printf("Mar\n");
            }
            if(current_time->tm_mon==3){
                printf("Apr\n");
            }
            if(current_time->tm_mon==4){
                printf("May\n");
            }
            if(current_time->tm_mon==5){
                printf("Jun\n");
            }
            if(current_time->tm_mon==6){
                printf("Jul\n");
            }
            if(current_time->tm_mon==7){
                printf("Aug\n");
            }
            if(current_time->tm_mon==8){
                printf("Sep\n");
            }
            if(current_time->tm_mon==9){
                printf("Oct\n");
            }
            if(current_time->tm_mon==10){
                printf("Nov\n");
            }
            if(current_time->tm_mon==11){
                printf("Dec\n");
            }
        }
        if(strcmp(schowek, "+%B")==0){
            if(current_time->tm_mon==0){
                printf("January\n");
            }
            if(current_time->tm_mon==1){
                printf("February\n");
            }
            if(current_time->tm_mon==2){
                printf("March\n");
            }
            if(current_time->tm_mon==3){
                printf("April\n");
            }
            if(current_time->tm_mon==4){
                printf("May\n");
            }
            if(current_time->tm_mon==5){
                printf("June\n");
            }
            if(current_time->tm_mon==6){
                printf("July\n");
            }
            if(current_time->tm_mon==7){
                printf("August\n");
            }
            if(current_time->tm_mon==8){
                printf("September\n");
            }
            if(current_time->tm_mon==9){
                printf("October\n");
            }
            if(current_time->tm_mon==10){
                printf("November\n");
            }
            if(current_time->tm_mon==11){
                printf("December\n");
            }
        }
        if(strcmp(schowek, "+%m")==0){
            if(current_time->tm_mon+1<10){
                printf("0%d\n",current_time->tm_mon+1);
            } else{
                printf("%d\n",current_time->tm_mon+1);
            }
        }
        if(strcmp(schowek, "+%y")==0){
            printf("%d\n",current_time->tm_year - 100);
        }
        if(strcmp(schowek, "+%Y")==0){
            printf("%d\n",current_time->tm_year + 1900);
        }
        if(strcmp(schowek, "+%T")==0){
            if(current_time->tm_hour<10){
                if(current_time->tm_min<10){
                    if(current_time->tm_sec<10){
                        printf("0%d:0%d:0%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                    else{
                        printf("0%d:0%d:%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                }else{
                    if(current_time->tm_sec<10){
                        printf("0%d:%d:0%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                    else{
                        printf("0%d:%d:%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                }
            }
            else{
                if(current_time->tm_min<10){
                    if(current_time->tm_sec<10){
                        printf("%d:0%d:0%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                    else{
                        printf("%d:0%d:%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                }else{
                    if(current_time->tm_sec<10){
                        printf("%d:%d:0%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                    else{
                        printf("%d:%d:%d\n",current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
                    }
                }
            }
        }
        if(strcmp(schowek, "+%H")==0){
            printf("%d\n", current_time->tm_hour);
        }
        if(strcmp(schowek, "+%M")==0){
            printf("%d\n",current_time->tm_min);
        }
        if(strcmp(schowek, "+%S")==0){
            printf("%d\n",current_time->tm_sec);
        }
    }
    else{
        printf("date : invalid date '%s'\n", schowek);
    }
}
void blue () {
    printf("\033[1;34m");
}
void green () {
    printf("\033[1;32m");
}
void resetcolor () {
    printf("\033[0m");
}
void EXEC(char komanda[100]){
    pid_t pid;
    char * schowek;
    schowek=strtok(komanda, "\n");
    char *podraz;
    int i =0;
    int f;
    char *argv[16];
    podraz = strtok(schowek, " ");
    while (podraz!=NULL) {
        argv[i]=podraz;
        i++;
        podraz=strtok(NULL, " ");
    }
    argv[i]=NULL;
    pid=fork();
    if(pid==0){
        f=execvp(argv[0], argv);
        if(f==-1){
            perror("");
        }
    }
    else{
        if(argv[i]==NULL){
            waitpid(pid, NULL, 0);
        }
    }
}
void CD(char komanda[100]){
    char nadkomanda[100];
    char *schowek;
    int kolprobel=0;
    int a;
    char *buffer;
    buffer = getcwd( NULL, 0 );
    strcat(buffer, "/");
    int i = 0;
    int f;
    while (komanda[i]!= '\0') {
        if (komanda[i] == ' ') {
            kolprobel++;
            if(kolprobel==1){
                a=i;
            }
        }
        i++;
    }
    if(kolprobel>0){
        strcpy(nadkomanda, &komanda[a]);
        schowek = strtok( nadkomanda, "\n");
        for (int u=0, j; schowek[u] != '\0'; u++) {
            while (!(schowek[u]!=' ')&& !(schowek[u] == '\0')) {
                for (j = u; schowek[j] != '\0'; j++) {
                    schowek[j] = schowek[j + 1];
                }
                schowek[j] = '\0';
            }
        }
        if(strcmp(schowek, "~")==0){
            schowek=getenv("HOME");
            chdir(schowek);
        }
        if(strcmp(schowek, ".")==0){
        }
        if(strcmp(schowek, "..")==0){
            chdir(schowek);
        }
        if(strcmp(schowek, "-")==0){
            //chdir();
        }
        if(schowek[0]=='\0'){
            schowek=getenv("HOME");
            chdir(schowek);
        }
        else{
            if(schowek[0]!='/'){
                strcat(buffer, schowek);
                f=chdir(buffer);
                if(f==-1){
                    fprintf(stderr, "%s : %s\n", schowek, strerror(errno));
                }
            }
            else{
                f=chdir(schowek);
                if(f==-1){
                    fprintf(stderr, "%s : %s\n", schowek, strerror(errno));
                }
            }
        }
    }
    else{
        schowek = getenv("HOME");
        chdir(schowek);
    }
}
void EXIT() {
    exit(EXIT_SUCCESS);
}
void HELP(){
    printf("\n*** MicroShell SOP *** \nAutor: Yahor Haleznik\n\n");
}
void path(){
    char *buffer;
    char tilde[10];
    char *usr=getenv("HOME");
    char ussr[strlen(usr)];
    int i=0;
    int a;
    while (usr[i]!= '\0') {
        if (usr[i] == '/') {
            a=i;
        }
        i++;
    }
    strcpy(ussr, &usr[a+1]);
    buffer = getcwd( NULL, 0 );
    if(strlen(buffer)>= strlen(usr)){
        strncpy(tilde, buffer, strlen(usr));
        if(strcmp(tilde,usr)==0){
            strcpy(buffer, &buffer[strlen(usr)]);
            printf("[");
            blue();
            printf("%s", ussr);
            resetcolor();
            printf(":");
            green();
            printf("~%s",buffer);
            resetcolor();
            printf("]$ ");
        }
        else{
            printf("[");
            blue();
            printf("%s", ussr);
            resetcolor();
            printf(":");
            green();
            printf("%s",buffer);
            resetcolor();
            printf("]$ ");
        }
    }
    else{
        printf("[");
        blue();
        printf("%s", ussr);
        resetcolor();
        printf(":");
        green();
        printf("%s",buffer);
        resetcolor();
        printf("]$ ");
    }
    free(buffer);
}
void POISKKOMANDY(char komanda[100]){
    int i=0;
    int kolprobel=0;
    char podkomanda[100];
    while(komanda[i]!='\0'){
        if (komanda[i] == ' '){
            kolprobel++;
        }
        i++;
    }
    if (kolprobel>0){
        sscanf(komanda,"%s[^' ']", podkomanda);
        if((strcmp(podkomanda, "exit")==0)(strcmp(podkomanda, "help")==0)(strcmp(podkomanda, "cd")==0)(strcmp(podkomanda, "date")==0)(strcmp(podkomanda, "cal")==0)){
            if(strcmp(podkomanda, "help")==0){
                HELP();
            }
            if(strcmp(podkomanda, "date")==0){
                DATE(komanda);
            }
            if(strcmp(podkomanda, "cal")==0){
                CAL(komanda);
            }
            if(strcmp(podkomanda, "cd")==0){
                CD(komanda);
            }
            if(strcmp(podkomanda, "exit")==0){
                EXIT();
            }
        }
        else {
            EXEC(komanda);
        }
    }
    else{
        sscanf(komanda,"%s[^\n]", podkomanda);
        if((strcmp(podkomanda, "exit")==0)(strcmp(podkomanda, "help")==0)(strcmp(podkomanda, "cd")==0)(strcmp(podkomanda, "date")==0)||(strcmp(podkomanda, "cal")==0)){
            if(strcmp(podkomanda, "help")==0){
                HELP();
            }
            if(strcmp(podkomanda, "date")==0){
                time_t now;
                time(&now);
                printf("%s", ctime(&now));
            }
            if(strcmp(podkomanda, "cal")==0){
                CAL(komanda);
            }
            if(strcmp(podkomanda, "cd")==0){
                CD(komanda);
            }
            if(strcmp(podkomanda, "exit")==0){
                EXIT();
            }
        }
        else {
            EXEC(komanda);
        }
    }
}
int main(){
    char stroka[100];
    int poka=0;
    while(poka!=1){
        path();
        fgets (stroka, 100, stdin);
        POISKKOMANDY(stroka);
    }
}