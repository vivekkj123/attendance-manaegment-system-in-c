// Header Files 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> // For String Operations
#include <malloc.h> // For allocating memory
#include <time.h> // For getting today's date
// Function Declarations
void take_attendance(); 
void add_student();
void delete_student();
int main()
{
	int n;
	system("clear"); // Clears the terminal
	// Main menu
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
		// For exiting program
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
	int absentees[50], num = 0, n;
	char date[20], file_name[30] = "Reports/report-";
	FILE *abs_file;
	system("clear");
	printf(" 1. Take Attendance For Today\n 2. Enter Previous Attendance data");
	printf("\nEnter your choice:");
	scanf("%d", &n);
	if(n==1){
		time_t t = time(NULL); // Get Current Date and time
		struct tm tm = *localtime(&t);
		sprintf(date, "%d-%02d-%02d",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900); // For setting current date to variable
	}else{
	// For Manually inputting date from user
	printf("Enter Date in dd-mm-yy format(Eg: 20-06-22)");
	scanf("%s", date);
	}
	system("clear");
	// Prints Roll list
	do
	{
		ch = fgetc(rollList);
		printf("%c", ch);
	} while (ch != EOF);
	fclose(rollList);
	// Input number of absentees
	printf("Enter Roll number of Absentees (Input 0 when finished):");
	for (int i = 0; i < 50; i++)
	{
		scanf("%c", &temp);
		if (temp == '0') // If 0 is inputted, break the loop
		{
			break;
		}
		absentees[i] = temp;
		num++;
	}
	FILE *roll = fopen("roll-list", "r");
	FILE *template = fopen("template.html", "r"); // Template File
	char line[256];
	strcat(file_name, date); // Append date to file name
	strcat(file_name, ".html"); // Append file format (HTML) to file name
	abs_file = fopen(file_name, "w+"); // Open the report file
	while (fgets(line, sizeof(line), roll)) // Loop through each line of roll list
	{
		int absent = 0;
		char *str = malloc(strlen(line) + 1);
		strcpy(str, line); // Copies original line to variable str
		char *pch = strtok(line, " "); // Splits roll number from each line
		// Copy template to report file
		char c = fgetc(template);
		while (c != EOF)
		{
			if (c == '^') // If character ^ is found, replace it with date
			{
				fprintf(abs_file, "%s", date);
				c = fgetc(template);
			}
			else		// Else copy contents of template file to report file by character by character
			{
				fputc(c, abs_file);
				c = fgetc(template);
			}
		}
		for(int j=0; j<sizeof(absentees); j++){ // Loop through absentees array
			if (absentees[j] == *pch){  // If any of the member of absentees array is matched with roll no. from roll list, mark them as absent else present
				fprintf(abs_file, "<tr><td class='absent'><span></span>%s<span>❌</span></td></tr> \n", str);
				absent=1;
				break;
			}
		}
		if(absent==0)
		{
			fprintf(abs_file, "<tr><td class='present'><span></span>%s<span>✔️</span></td></tr> \n", str);

		}
	}
	fprintf(abs_file, "</table></body></html>"); // Add closing tags to report file
	fclose(roll);
	printf("Absentees Data Saved Succesfully");
	fclose(abs_file);
	char command[25] = "firefox "; // Command for opening report file
	strcat(command, file_name); // append file name to command
	system(command); // Run the command
	system("clear");
}
void add_student()
{
	FILE *roll;
	int rollNo;
	char name[50];
	roll = fopen("roll-list", "a"); // Open roll list in append mode
	printf("Enter New Student Roll Number:");
	scanf("%d%*c", &rollNo);
	printf("Enter New Student Name:");
	fgets(name, 50, stdin);
	fprintf(roll, "%d. %s", rollNo, name); // Append new student to roll list
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
	// print roll list to terminal
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(rollList);
	}
	fclose(rollList);
	printf("Enter the roll no. of student to be deleted:");
	// get no. of student to be deleted
	scanf("%c\n", &delRoll);
	delRoll = getc(stdin);
	rollList = fopen("roll-list", "r");
	FILE *temp = freopen("temp", "w+", stdout); // Temporary file for writing data
	while (fgets(line, sizeof(line), rollList)) // Loop through each elements of roll list
	{
		char *str = malloc(strlen(line) + 1);
		strcpy(str, line); // copy original line to str for writing it to temp file
		char *pch = strtok(line, " "); // split ,ine to get roll no of student
		if (delRoll != *pch)
		{
			fflush(temp);
			printf("%s", str); // only write original line to temp file if delroll!=splitted roll no.
		}
	}
	freopen("/dev/tty", "a", stdout); //Bring back to standard terminal
	remove("roll-list"); // Remove roll list fille
	rename("temp", "roll-list"); // Rename temp file to roll-list 
}
