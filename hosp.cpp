#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<process.h>
#include<windows.h>
#define WINDOWS 1

void clrscr()
{
  #ifdef WINDOWS
  system("cls");
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}
COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left corner of the screen
void gotoxy(int x,int y)
 {
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

using namespace std;

class patient
{

	int pat_id;
	char name[20];
	char blood_group[5];
	long int phn;

public:
	void getpatientdata();
	void showpatientdata();
	void modifypatientdata();
	void searchpatientdata();
	int getID()
	{
	    return pat_id;
	}
};

//the main class that will be used for storing the patient data
void addpatient( patient p)
{
	fstream f;
	f.open("patient.txt", ios::app| ios::binary);
	// if the file cannot be opened
	if(!f)
	{
		cout<< "\n The file could not be opened";
		exit(1);
	}
	//write the contents to the file
	f.write((char *)&p, sizeof(p));
	//close the file
	f.close();
	cout<< "\n The patient has been added to the database.";
	return;
}

void displaypatients( )
{
	fstream f;
	patient p;
	f.open("patient.txt", ios::in|ios::binary);
	//if the file cannot be opened
	if(!f)
	{
		cout<< "\n The file cannot be opened";
		exit(1);
	}
	//moving the file get pointer to the beginning of the file
	f.seekg(0);
	//reading records from the file till we reach the end of file
	while(f)
		{
            if(!f.read((char *)&p, sizeof(p))) break;
                p.showpatientdata();
        }
	//close the file
	f.close();
	return;
}


//function that reads the patient data from the user
void patient::getpatientdata()
{
	cout<<" \n\n\t\t\tCreate New Patient Record ";

	cout<<"\nEnter Patient ID : ";
	cin>>pat_id;

	cout<<"\nEnter Patient Name : ";
	cin>>name;

	cout<<"\nEnter Patient Blood Group : ";
	cin>>blood_group;

	cout<<"\nEnter Patient Phone Number  : ";
	cin>>phn;

	return;
}

//function that displays the patient data to the user
void patient::showpatientdata()
{
	cout<<"\nPatient ID\t: "<<pat_id;
	cout<<"\nPatient Name\t: "<<name;
	cout<<"\nBlood Group\t: "<<blood_group;
	cout<<"\nPatient Phone Number\t: "<<phn;
	cout<<"\n\n";
	return;
}

//function that will modify an existing record in the database
void patient::modifypatientdata( )
{
	//nname, nid,nphn,nblood are the new details to be entered
	int nid;
	char nname[20], nblood[5];
	long int nphn;
	//enter the new details for the patient
	cout<< "Enter the new details:(type the new details, or press . to retain the old one)" ;
	cout<< "\n Enter the new patient ID: ";
	cin >> nid;
	cout<< "\n Enter the new patient name: ";
	cin>> nname;
	cout<< "\n Enter the new blood group of the patient: ";
	cin>> nblood;
	cout<< "\n Enter the new phone number of the patient: (Enter 1 to retain old one)";
	cin>> nphn;
    //modify the existing record
    if(strcmp(nname,".")!=0)
        strcpy(name, nname);
    if(strcmp(nblood,".")!=0)
        strcpy(blood_group,nblood);
    pat_id = nid;
    if(nphn!=1)
        phn = nphn;
    return;
}

void searchpatientdata(patient p)
{
	fstream f;
	int found = 0;
	f.open("patient.txt", ios::in|ios::binary);
	if(!f)
		{
			cout<<"\n The file could not be opened.";
			exit(1);
		}
	int id;
	cout<< "\n Enter the patient ID that you want to search for: ";
	cin>>id;
	while(!f.eof())
	{
		f.read((char*)&p, sizeof(p));
		if(id==p.getID())
		{
			found=1;
			cout<<"\n The record has been found. The details are:";
			p.showpatientdata();
		}
		if(!found)
			cout<< "the patient ID is incorrect or the record does not exist.";
	}
	//close the file
	f.close();
}

//the main function that gets called when the program starts execution
int main()
{
	clrscr();

	//display certain information initially
	gotoxy(20,18);
	cout<<"\tProgram Developed by :-";
	gotoxy(28,22);
	cout<<"\tSushmita Nair, Harshveen Kaur, Rutuja Karhade\n";
	gotoxy(25,28);
	cout<<"Press Any Key to Continue";
	getch();

	//the main tasks start here
	clrscr();
	int a=0;
	while(a!=5){
		cout<<"\n =============================================================================\n";
		cout<<"\t\t\t Hospital Record Management\n";
		cout<<"\n =============================================================================\n";
		cout<<"\n\t 1 . Add a patient record to the Database:";
		cout<<"\n\t 2 . Display all patient Records in Database:";
		cout<<"\n\t 3 . Modify a patient record in Database";
		cout<<"\n\t 4 . Search the database for a patient record";
		cout<<"\n\t 5 . Exit ";
		cout<<"\n\n\n\tEnter your Choice:";
		cin>>a;

		switch (a)
		{
			case 1: //add a new patient record to the database:
				{
					clrscr();
					patient p1;
					p1.getpatientdata();
					addpatient(p1);
					cout<< "nack in main";
					break;
				}

			case 2:
				{
					cout<<"\n\n PATIENT DATABASE:";
					displaypatients();
					break;
				}
			case 3:
				{
					patient p1;
					int pos, id, found=0;
					cout<< "Enter the PatientID of the patient whose details have to be modified: ";
                    cin>>id;
					fstream f;
                    f.open("patient.txt", ios::in|ios::out|ios::binary);
                    //check if file has been opened
                    if(!f)
                    {
                        cout<< "\n The file could not be opened.";
                        exit(1);
                    }
                    //if file has been opened, till the end of file is reached
                    while(!f.eof())
                    {
                        //before reading a record, its beginning position is determined with tellg
                        pos = f.tellg();
                        f.read((char *)&p1, sizeof(p1));
                        if(p1.getID()==id)
                        {
                            p1.modifypatientdata();
                            f.seekg(pos);
                            f.write((char*)&p1, sizeof(p1));
                            found=1;
                            break;
                        }
                    }
                    if(!found)
                        cout<< "\n Record not found";
                    //close the file
                    f.close();
					break;
				}
			case 4:
				{
					patient p1;
					searchpatientdata( p1);
					break;
				}
            case 5:
                {
                    cout<< "\n Goodbye";
                    break;
                }
			default:
				{
					cout<<"\n\tWrong input \n";
					break;
				}
        }
    }
getch();
return 0;
}
