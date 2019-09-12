/*	Project : Library Automation
	Group Members(Name + CMS ID):

		1) Farhaan Mukarram (246582)
		2) Muhammad Talha Qadir (249918)
		3) Muhammad Umer (246302)
*/

#include <stdio.h>
#include<string.h>

// Structure definitions
struct Book {
	char Title[100];
	char Author[100];
	char Dept[100];
	char Status[50];

};

struct Member {
	char Name[100];
	char ID[100];
	char PrevBooks[15][100];
	char CurrentBooks[5][100];
};

// Function definitions
void PrintMenu() {		// Function to print menu
	printf("\n\t 1. Issue book\n");
	printf("\t 2. Return book\n");
	printf("\t 3. List of all the books\n");
	printf("\t 4. List of books by author\n");
	printf("\t 5. List of books by department\n");
	printf("\t 6. List of issued books by person.\n");
	printf("\t 7. Insert a new book\n");
	printf("\t 8. Add a new member\n");
	printf("\t 9. Delete a member\n");
	printf("\t10. List of Members\n");
	printf("\t 0. Quit\n\n");
}

void PrintBookList() {		// Function to read and print all books from file
	FILE *fout = fopen("Books.bin", "rb");		// Open Books.bin file in binary read mode
	struct Book b;
	int i = 0;
	if (!fout) {		// If file pointer returned NULL
		printf("\n\tUnable to open books file!");
		return 0;
	}
	printf("\n");
	while (fread(&b, sizeof(struct Book), 1, fout) == 1) {		// Read and display records till end of file	
		i++;		// Increment book counter
		printf("\t%d.\tTitle : ", i);
		puts(b.Title);
		printf("\t\tAuthor : ");
		puts(b.Author);
		printf("\t\tDepartment : ");
		puts(b.Dept);
		printf("\t\tStatus : ");
		puts(b.Status);
		printf("\n");

	}
	fclose(fout);		// Close file
}

void InsertNewBook(int choice, char book_name[], char auth_name[]) {		// Function to add new book to the file
	char temp[100];
	FILE *fin = fopen("Books.bin", "ab");		// Open Books.bin file in binary append mode
	struct Book b;
	switch (choice) {
	case 1:
		strcpy(b.Dept, "Computer Science");
		break;
	case 2:
		strcpy(b.Dept, "Engineering");
		break;
	case 3:
		strcpy(b.Dept, "Non-fiction");
		break;
	case 4:
		strcpy(b.Dept, "Mathematics");
		break;
	}
	strcpy(b.Title, book_name);			// Copy attributes to structure
	strcpy(b.Author, auth_name);
	strcpy(b.Status, "Available");
	fwrite(&b, sizeof(struct Book), 1, fin);		// Write record to file		
	fclose(fin);		// Close file
	printf("\n\tRecord successfully added to file...");
}

void PrintBooksByDept(int choice)		// Function to print books of a specific department
{
	char dep[50];		// Declaration of local variables
	int found = 0,i=0;
	struct Book c;
	FILE *fin = fopen("Books.bin", "rb");		// Open Books.bin file in binary read mode
	if (!fin) {		// If  file pointer returned NULL
		printf("\n\tUnable to open books file!");
		return 0;
	}
	switch (choice) {
	case 1:
		strcpy(dep, "Computer Science");
		break;
	case 2:
		strcpy(dep, "Engineering");
		break;
	case 3:
		strcpy(dep, "Non-fiction");
		break;
	case 4:
		strcpy(dep, "Mathematics");
		break;
	}
	printf("\n");
	while (fread(&c, sizeof(struct Book), 1, fin) == 1) {		// Read records till end of file
		if ((strcmp(c.Dept, dep)) == 0) {		// If department is found, print book details
			i++;		// Increment book counter
			printf("\t%d.\tTitle : ",i);
			puts(c.Title);
			printf("\t\tAuthor : ");
			puts(c.Author);
			printf("\t\tDepartment : ");
			puts(c.Dept);
			printf("\t\tStatus : ");
			puts(c.Status);
			printf("\n");
			found = 1;
		}
	}
	if (!found)		// If no book for department found
	{
		printf("\n\tNo books in department were found... ");

	}
	fclose(fin);		// Close file

}

void PrintBooksByAuthor(char auth_name[]) {		// Function to print all books by an author			
	int found = 0,i=0;		// Declaration of local variables
	struct Book c;
	FILE *fin = fopen("Books.bin", "rb");
	if (!fin)		// If file pointer returned NULL
	{
		printf("\n\tUnable to open books file!");
	}
	printf("\n");
	while (fread(&c, sizeof(struct Book), 1, fin) == 1) {
		if ((strcmp(c.Author, auth_name)) == 0) {		// If author name found, print book details	
			i++;		// Increment book counter
			printf("\t%d.\tTitle : ",i);
			puts(c.Title);
			printf("\t\tAuthor : ");
			puts(c.Author);
			printf("\t\tDepartment : ");
			puts(c.Dept);
			printf("\t\tStatus : ");
			puts(c.Status);
			printf("\n");
			found = 1;
		}
	}
	if (!found)		// If author name not found
	{
		printf("\n\tNo record for author found!");

	}
	fclose(fin);		// Close file
}

void PrintMembersList() {		// Function to print list of all members
	struct Member m;		// Declaration of local variables
	int i = 0;
	FILE *fin = fopen("Members.bin", "rb");		// Open Members.bin in binary read mode
	if (!fin)		// If file pointer returned NULL
	{
		printf("\n\tUnable to open ");
		return 0;
	}
	while (fread(&m, sizeof(struct Member), 1, fin) == 1)		// Read and display records till end of file
	{
		i++;		// Increment member counter
		printf("\n\t%d.\tName : ",i);
		puts(m.Name);
		printf("\t\tID : ");
		puts(m.ID);
	}
	if (i == 0) {		// If file is empty
		printf("\n\tNo members currently added!");
	}
	fclose(fin);		// Close file
}

void PrintBooksByMem(char temp[]) {		// Function to print all books issued by a member
	struct Member m;		// Declaration of local variables
	int k = 0;
	FILE *fin = fopen("Members.bin", "rb");
	if (!fin)		// If file pointer returned NULL
	{
		printf("\n\tUnable to open file...");
		return 0;
	}
	int mem_exists = SearchMember(temp);		// Call function to search member using member ID
	if (!mem_exists) {		// If no record for member was found
		printf("\n\tNo record for member found!");
	}
	else {
		printf("\n");
		while (fread(&m, sizeof(struct Member), 1, fin) == 1)		// Read records till end of file
		{
			if ((strcmp(m.ID, temp)) == 0) {		// If record is found
				for (int i = 0; i < 5; i++) {
					if ((strcmp(m.CurrentBooks[i], " ")) == 0) {		// If array contents at index are blank
						continue;
					}
					else {
						k++;		// Increment book counter
						printf("\t%d. ", k);
						puts(m.CurrentBooks[i]);
					}
				}
			}

		}
		fclose(fin);		// Close file
		if (k == 0) {		// If book count is 0
			printf("\tNo books have currently been issued");
		}
	}
}

void AddNewMember(char name[], char ID[]) {		// Function to add a new member
	char temp[100];		// Declaration of local variables
	struct Member m;
	FILE *fin = fopen("Members.bin", "ab");		// Open Members.bin in binary append mode
	int mem_exists = SearchMember(ID);
	if (mem_exists == 1) {		// If member ID has already been issued
		printf("\n\tMember ID already taken!");
	}
	else {
		strcpy(m.Name, name);		// Copy attributes
		strcpy(m.ID, ID);
		for (int i = 0; i < 5; i++) {
			strcpy(m.CurrentBooks[i], " ");		// Initialize current books list		
		}
		for (int i = 0; i < 15; i++) {
			strcpy(m.PrevBooks[i], " ");		// Initialize previous books list
		}
		fwrite(&m, sizeof(struct Member), 1, fin);		// Write record to file
		fclose(fin);		// Close file
		printf("\n\tNew member successfully added...");
	}
}

void DeleteMember(char temp[]) {		// Function to delete a member
	int found = 0;		// Declaration of local variables
	struct Member m;
	struct Book a;		
	int mem_exists = SearchMember(temp);		// Call function to search for member using ID
	if (!mem_exists) {		// If member not found
		printf("\n\tNo record for member found!");
	}
	else {
		FILE *fout = fopen("Members.bin", "rb");		// Open Members.bin in binary read mode
		FILE *fin = fopen("temp.bin", "wb");		// Open temp.bin in binary write mode
		if (!fout) {		// If file pointer to Members.bin returned NULL
			printf("\n\tUnable to open members file!");
			return 0;
		}
		while (fread(&m, sizeof(struct Member), 1, fout) == 1)		// Read records till end of file
		{
			if (strcmp(temp, m.ID) == 0)		// If record is found
			{
				for (int i = 0; i < 5; i++) {
					if ((strcmp(m.CurrentBooks[i], " ") == 0)) {		// If list of current books is blank
						continue;
					}
					else {
						found = 1;
					}
				}
			}
			else
			{
				fwrite(&m, sizeof(struct Member), 1, fin);		// Write record to temp.bin
			}
		}
		fclose(fout);		// Close Members.bin file
		fclose(fin);		// Close temp.bin file
		if (found) {		// If member to be deleted has issued books
			printf("\n\tPlease return issued books!\n");

		}
		else{
			printf("\n\tMember successfully deleted...");
	}
		remove("Members.bin");		// Delete Members.bin
		rename("temp.bin", "Members.bin");		// Rename temp.bin to Members.bin		
	}
}

void IssueBook(char book_name[], char mem_id[]) {		// Function to issue book to a member
	struct Book b;		// Declaration of local variables
	struct	Member m;
	struct Member temp_m;
	int i = 0, issued = 0, free = 0, prev_issued = 0;
	FILE *fin, *fout;
	int book_exists = SearchBook(book_name);		// Function call to search for a book by book name	
	int mem_exists = SearchMember(mem_id);		// Function call to search for a member by member ID
	if ((book_exists == 1) && (mem_exists == 1)) {		// If both book and member exist
		fin = fopen("Books.bin", "rb+");		// Open Books.bin for reading and writing
		fout = fopen("Members.bin", "rb+");		// Open Members.bin for reading and writing
		while ((fread(&m, sizeof(struct Member), 1, fout) == 1) && (issued == 0))		// Read records until end of  Members.bin file and until book isn't issued
		{
			if ((strcmp(m.ID, mem_id)) == 0)		// If member record found
			{
				for (int i = 0; i < 5; i++)
				{
					if ((strcmp(m.CurrentBooks[i], " ")) == 0)		// If free slots in list of current books
					{
						free++;		// Increment free slots counter
						while ((fread(&b, sizeof(struct Book), 1, fin) == 1))		// Read records until end of Books.bin file
						{
							if ((strcmp(b.Title, book_name)) == 0) {		// If book record found
								for (int j = 0; j < 5; j++) {
									if ((strcmp(m.PrevBooks[j], b.Title)) == 0) {		// If book has previously been issued
										prev_issued = 1;
										break;
									}
								}
								if ((strcmp(b.Status, "Available") == 0) && (prev_issued == 0)) {		// If book available to issue						
									issued = 1;
									strcpy(m.CurrentBooks[i], b.Title);		// Copy attributes
									strcpy(b.Status, "Issued");
									fseek(fout, -sizeof(m), SEEK_CUR);		// Set file pointer to Members.bin to beginning of member record
									fwrite(&m, sizeof(m), 1, fout);		// Write record to Members.bin									
									fseek(fin, -sizeof(b), SEEK_CUR);		// Set file pointer to Books.bin to beginning of book record
									fwrite(&b, sizeof(b), 1, fin);		// Write record to Books.bin
									printf("\n\tBook successfully issued...");
									fclose(fout);		// Close Members.bin
									fclose(fin);		// Close Books.bin
									break;
								}
								else if (prev_issued == 1) {		// If book was previously issued
									printf("\n\t\Book has been issued previously!");
								}
								else {		// If book has been issued to another member
									printf("\n\tBook not available to issue!");
								}
							}
						}
					}

				}
			}
		}
		if (free == 0) {		// If no free slots in list of current books
			printf("\n\tNo more books can be issued");
		}
	}
	else {
		if ((mem_exists == 0) && (book_exists == 1)) {		// If member not found
			printf("\n\tMember record not found!");
		}
		else if ((book_exists == 0) && (mem_exists == 1)) {		// If book not found
			printf("\n\tBook record not found!");
		}
		else if ((book_exists == 0) && (mem_exists == 0)) {		// If both book and member not found
			printf("\n\tNo record for book and member found!");
		}
	}
}

void ReturnBook(char book_name[], char mem_id[]) {		// Function to return book to library
	struct Book b;		// Declaration of local variables
	struct	Member m;
	FILE *fin, *fout;	
	int returned = 0;
	int book_exists = SearchBook(book_name);		// Call function to search for book using book name
	int mem_exists = SearchMember(mem_id);		// Call function to search for member using member ID
	if ((book_exists == 1) && (mem_exists == 1)) {		// If both book and member exist
		fin = fopen("Books.bin", "rb+");		// Open Books.bin for reading and writing 
		fout = fopen("Members.bin", "rb+");		// Open Members.bin for reading and writing
		while ((fread(&m, sizeof(struct Member), 1, fout) == 1) && (returned == 0))		// Read records until end of Members.bin file and 
																						// until book isn't returned
		{
			if ((strcmp(m.ID, mem_id)) == 0)		// If member record found
			{
				for (int i = 0; i < 5; i++)
				{
					if ((strcmp(m.CurrentBooks[i], book_name)) == 0)		// If book found in list of current books
					{
						while ((fread(&b, sizeof(struct Book), 1, fin) == 1))		// Read records until end of Books.bin file
						{
							if ((strcmp(b.Title, book_name)) == 0)		// If book found in file
							{
								returned = 1;
								strcpy(m.CurrentBooks[i], " ");		// Copy attributes
								strcpy(b.Status, "Available");
								for (int j = 0; j < 15; j++) {
									if ((strcmp(m.PrevBooks[j], " ")) == 0) {		// If free slot in list of previous books
										strcpy(m.PrevBooks[j], b.Title);
										break;
									}
								}
								fseek(fout, -sizeof(m), SEEK_CUR);		// Set file pointer of Members.bin to beginning of member record
								fwrite(&m, sizeof(m), 1, fout);		// Write record to Members.bin
								fseek(fin, -sizeof(b), SEEK_CUR);		// Set file pointer of Books.bin to beginning of books record
								fwrite(&b, sizeof(b), 1, fin);		// Write record to Books.bin
								printf("\n\tBook successfully returned...");
								fclose(fout);		// Close Members.bin file
								fclose(fin);		// Close Books.bin file
								break;
							}
						}
					}

				}
			}
		}

	}
	else {
		if ((mem_exists == 0) && (book_exists == 1)) {		// If member not found
			printf("\n\tMember record not found!");
		}
		else if ((book_exists == 0) && (mem_exists == 1)) {		// If book not found
			printf("\n\tBook record not found!");
		}
		else if ((book_exists == 0) && (mem_exists == 0)) {		// If both book and member not found
			printf("\n\tNo record for book and member found!");
		}
	}	
}

int SearchBook(char book_name[]) {		// Function to search Books.bin for a book by book name
	FILE *fptr = fopen("Books.bin", "rb");		// Open Books.bin in binary read mode
	struct Book b;
	if (!fptr) {		// If file pointer returned NULL
		printf("\n\tUnable to open books file!");
		return -1;
	}
	while ((fread(&b, sizeof(struct Book), 1, fptr))) {		// Read records till end of file
		if ((strcmp(b.Title, book_name) == 0)) {		// If record is found
			fclose(fptr);		// Close file
			return 1;
		}
	}
	fclose(fptr);		// Close file 
	return 0;
}

int SearchMember(char mem_id[]) {		// Function to search Members.bin for a member by member ID		
	FILE *fptr = fopen("Members.bin", "rb");		// Open Members.bin in binary read mode
	struct Member m;
	if (!fptr) {		// If file pointer returned NULL
		printf("\n\tUnable to open members file!");
		return -1;
	}
	while ((fread(&m, sizeof(struct Member), 1, fptr))) {		// Read records till end of file
		if ((strcmp(m.ID, mem_id) == 0)) {		// If record is found
			fclose(fptr);		// Close file
			return 1;
		}
	}
	fclose(fptr);		// Close file
	return 0;
}

// Main starts here
void main() {
	int choice = 0, dept_choice = 0, book_choice = 0;		// Declaration of local variables
	char mem_name[100], mem_ID[100], temp_book[100], temp_mem[100], auth_name[100], book_name[100];
	do {
		system("cls");		// Clear console screen
		PrintMenu();		// Call function to print menu
		printf("\tEnter your choice : ");
		scanf("%d", &choice);		// Input choice
		getchar();		// Read new line
		switch (choice) {
		case 0:		// Quit
			printf("\n\tExiting program...");
			break;

		case 1:		// Issue book
			printf("\n\tEnter member's ID : ");
			gets(mem_ID);		// Input member ID 
			printf("\tEnter book title : ");
			gets(book_name);		// Input book name
			IssueBook(book_name, mem_ID);		// Call function to issue book
			break;
		case 2:		// Return book
			printf("\n\tEnter member's ID : ");
			gets(mem_ID);		// Input member ID 
			printf("\tEnter book title : ");
			gets(book_name);		// Input book name
			ReturnBook(book_name, mem_ID);		// Call function to return issued book
			break;
		case 3:		// Print all books
			PrintBookList();		// Call function to print list of all books
			break;

		case 4:		// Prink books by author
			printf("\n\tEnter author's name : ");
			gets(auth_name);		// Input author's name
			PrintBooksByAuthor(auth_name);		// Call function to print all books by an author
			break;

		case 5:		// Print books by department
			dept_choice = 0;
			printf("\t\n\t Which department would you like to access?\n ");
			printf("\n\t1. Computer Science");
			printf("\n\t2. Engineering");
			printf("\n\t3. Non-fiction");
			printf("\n\t4. Mathematics");
			printf("\n\n\tEnter your choice : ");
			scanf("%d", &dept_choice);		// Input department choice
			PrintBooksByDept(dept_choice);		// Call function to print all books in a department
			break;

		case 6:
			printf("\n\tEnter member's ID : ");
			gets(mem_ID);		// Input member ID
			PrintBooksByMem(mem_ID);		// Call function to print all books issued to a member
			break;

		case 7:		// Insert new book			
			book_choice = 0;
			printf("\t\n\t Which department would you like to add the book to ?\n ");
			printf("\n\t1. Computer Science");
			printf("\n\t2. Engineering");
			printf("\n\t3. Non-fiction");
			printf("\n\t4. Mathematics");
			printf("\n\n\tEnter your choice : ");
			scanf("%d", &book_choice);		// Input book choice
			getchar();
			printf("\n\tEnter title : ");
			gets(book_name);		// Input book name
			printf("\tEnter author : ");
			gets(auth_name);		// Input author name
			InsertNewBook(book_choice, book_name, auth_name);		// Call function to insert new book
			break;

		case 8:		// Add a new member
			printf("\n\tEnter member's name : ");
			gets(mem_name);		// Input member name
			printf("\tEnter member's ID : ");
			gets(mem_ID);		// Input member ID
			AddNewMember(mem_name, mem_ID);		// Call function to add new member
			break;

		case 9:		// Delete a member
			printf("\n\tEnter member ID : ");
			gets(mem_ID);		// Input member ID 
			DeleteMember(mem_ID);		// Call function to delete member
			break;

		case 10:		// Print list of all members
			PrintMembersList();		// Call function to print list of all members
			break;

		default:
			printf("\n\tInvalid Input!\n");
		}
		getch();		// Hold screen until keypress
	} while (choice != 0);
}

