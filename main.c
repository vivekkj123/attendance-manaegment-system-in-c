#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
int main(){
	int n;
	FILE* rollList; char ch;
	rollList = fopen("roll-list", "r");
	system("clear");
	welcome: printf("========================================\n\n\tAttendance Management System\n\n========================================");
	printf("\n1. Take Attendance \n2. Edit Student Details \n3. View Attendance \n4. Exit");
	printf("\n\nEnter your choice:");
	scanf("%d", &n);
	switch(n){
		case 1: 
			system("clear");
			char temp;
			int absentees[50],  num=0;
			char date[20], file_name[30]="Absents/report-";
			FILE* abs_file;
			system("clear");
			printf("Enter Date in dd-mm-yy format(Eg: 20-06-22)");
			scanf("%s", date);
			do {
				ch = fgetc(rollList);
				printf("%c",ch);
			} while (ch != EOF);
			 fclose(rollList);
			printf("Enter Roll number of Absentees (Input 0 when finished):");
			for(int i=0;i<50;i++){
				scanf("%c", &temp);
					if(temp == '0'){
						break;
					}
				absentees[i] = temp;
				num++;
			}
			FILE * roll = fopen("roll-list", "r");
			char line[256];
			strcat(file_name, date);
			strcat(file_name, ".txt");
			abs_file = fopen(file_name, "w");
		    while (fgets(line, sizeof(line), roll)){
			char *str = malloc(strlen(line)+1);
		    strcpy(str, line);
		    char* pch = strtok (line," ");
		        for(int i=0; i<2; i++){
		        	if(absentees[i]==*pch){
						printf(str);
						fprintf(abs_file,"%s", str);
						fprintf(abs_file, "\n");	        	
					}
		        }
		    }
			fclose(roll);
			printf("Absentees Data Saved Succesfully");
			// for(int i=0;i<num;i++){
				// fprintf(abs_file,"%d", absentees[i]);
				// fprintf(abs_file, "\n");
			// }
			fclose(abs_file);
		break;
		case 2:
		break;
		case 3:
		break;
		case 4: 
			system("clear");
			exit(0);
		break;
		default: 
			system("clear");
			printf("\033[0;31m Invalid input \n\n\n \033[0m");
			goto welcome;
	}
	return 0;
}
