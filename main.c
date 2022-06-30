#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
void take_attendance();
void add_student();
void delete_student();
int main()
{
	int n;
	system("clear");
welcome:
	printf("========================================\n\n\tAttendance Management System\n\n========================================");
	printf("\n1. Take Attendance \n2. Edit Student Details \n3. Exit");
	printf("\n\nEnter your choice:");
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		take_attendance();
		break;
	case 2:
		int n;
		system("clear");
		printf("1. Add Student\n2. Delete Student \n3. Go Back \n Enter your choice:");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			add_student();
			goto welcome;
			break;
		case 2:
			delete_student();
			goto welcome;
			break;
		case 3:
			system("clear");
			goto welcome;
		default:
			printf("Invalid Input");
		}
		break;
	case 3:
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
void take_attendance()
{
	FILE *rollList;
	rollList = fopen("roll-list", "r");
	system("clear");
	char temp, ch;
	int absentees[50], num = 0;
	char date[20], file_name[30] = "Absents/report-";
	FILE *abs_file;
	system("clear");
	printf("Enter Date in dd-mm-yy format(Eg: 20-06-22)");
	scanf("%s", date);
	do
	{
		ch = fgetc(rollList);
		printf("%c", ch);
	} while (ch != EOF);
	fclose(rollList);
	printf("Enter Roll number of Absentees (Input 0 when finished):");
	for (int i = 0; i < 50; i++)
	{
		scanf("%c", &temp);
		if (temp == '0')
		{
			break;
		}
		absentees[i] = temp;
		num++;
	}
	FILE *roll = fopen("roll-list", "r");
	FILE *template = fopen("template.html", "r");
	char line[256];
	strcat(file_name, date);
	strcat(file_name, ".html");
	abs_file = fopen(file_name, "w+");
	while (fgets(line, sizeof(line), roll))
	{
		int absent = 0;
		char *str = malloc(strlen(line) + 1);
		strcpy(str, line);
		char *pch = strtok(line, " ");
		char c = fgetc(template);
		// Copy template to report file
		while (c != EOF)
		{
			if (c == '^')
			{
				fprintf(abs_file, "%s", date);
				c = fgetc(template);
			}
			else
			{
				fputc(c, abs_file);
				c = fgetc(template);
			}
		}
		// Write date to html
		// if(str=="DATE"){
		// fprintf(abs_file, "%s", date);
		// }
		// Copy absentees data to report
		// if (absentees[i] == *pch)
		// {
		// 	fprintf(abs_file, "<tr><td class='absent'>%s</td></tr> \n", str);
		// }
		// else
		// {
		// 	fprintf(abs_file, "<tr><td class='present'>%s</td></tr> \n", str);
		// }
		for(int j=0; j<sizeof(absentees); j++){
			if (absentees[j] == *pch){
				fprintf(abs_file, "<tr><td class='absent'>%s</td></tr> \n", str);
				absent=1;
				break;
			}
		}
		if(absent==0)
		{
			fprintf(abs_file, "<tr><td class='present'>%s</td></tr> \n", str);

		}
	}
	fprintf(abs_file, "</table></body></html>");
	fclose(roll);
	printf("Absentees Data Saved Succesfully");
	fclose(abs_file);
}
void add_student()
{
	FILE *roll;
	int rollNo;
	char name[50];
	roll = fopen("roll-list", "a");
	printf("Enter New Student Roll Number:");
	scanf("%d%*c", &rollNo);
	printf("Enter New Student Name:");
	fgets(name, 50, stdin);
	fprintf(roll, "%d. %s", rollNo, name);
	printf("Student Saved Succesfully");
	fclose(roll);
	system("clear");
}
void delete_student()
{
	FILE *rollList = fopen("roll-list", "r");
	char c, delRoll;
	char line[256];
	c = fgetc(rollList);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(rollList);
	}
	fclose(rollList);
	printf("Enter the roll no. of student to be deleted:");
	scanf("%c\n", &delRoll);
	delRoll = getc(stdin);
	rollList = fopen("roll-list", "r");
	FILE *temp = freopen("temp", "w+", stdout);
	while (fgets(line, sizeof(line), rollList))
	{
		char *str = malloc(strlen(line) + 1);
		strcpy(str, line);
		char *pch = strtok(line, " ");
		if (delRoll != *pch)
		{
			fflush(temp);
			printf("%s", str);
		}
	}
	freopen("/dev/tty", "a", stdout);
	remove("roll-list");
	rename("temp", "roll-list");
}
