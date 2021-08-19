#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
class Book            //class used in project
{ char bno[6];
  char bname[50];
  char aname[20];
  public :
  void createbook()
  {cout<<"\nNEW BOOK ENTRY";
   cout<<"\nEnter the book number";
   gets(bno);
   cout<<"\nEnter the name of book";
   gets(bname);
   cout<<"\nEnter the author's name";
   gets(aname);
   cout<<"\nBook created";
  }
  void showbook()
  {cout<<"Book number";
   puts(bno);
   cout<<"Book Name:";
   puts(bname);
   cout<<"Author Name";
   puts(aname);
  }
  void modifybook()
  {cout<<"\nbook no"<<bno;
  cout<<"Modify book name";
  gets(bname);
  cout<<"Modify author's name of book";
  gets(aname);
  }
   char*retbno()
   { return bno;
   }
   void report()
   { cout<<"\n"<<bno<<"\t\t"<<bname<<"\t\t"<<aname<<endl;
   }
 };
 class Student
{ char admno[6];
  char name[20];
  char stbno[6];
  int token;
  public:
  void createstudent()
 { cout<<"New student entry"<<endl;
  cout<<"Enter the admission number";
  gets(admno);
  cout<<"Enter the name of student";
  gets(name);
  stbno[0]='\0';
  cout<<"Student record created";
 }
  void showstudent()
 { cout<<"Admission number";
   puts(admno);
   cout<<"student name";
   puts(name);
   cout<<"\n No. of book issued:"<<token;
   if(token == 1)
     cout<<"Book no."<<stbno;
    }
   void modifystudent()
   {  cout<<"admission no"<<admno;
      cout<<"modify student name";
      gets(name);
  }
    char*retadmno()
    {
      return admno;
    }
    char*retstbno()
    {
    return stbno;
    }
     int rettoken()
    {
      return token;
    }
    void addtoken()
    {token=1;}
    void resettoken()
    {token=0;}
    void getstbno(char t[])
    {
      strcpy(stbno,t);
    }
    void report()
   {cout<<"\n"<<"#"<<admno<<"\t\t"<<name<<"\t\t"<<token<<endl;}
   };
   //class ends here
   //GLOBAL DECLARATION FOR STREAM OBJECT
   fstream fp,fp1;
   Book bk;
   Student st;
   void writebook()
   {char  ch;
    fp.open("book.dat",ios::out|ios::app);
   do
   {  clrscr();
      bk.createbook();
      fp.write((char*)&bk,sizeof(bk));
      cout<<"do you want to add more records(y/n)";
      cin>>ch;
    }while(ch=='y'||ch=='Y');
      fp.close();
   }
    void writestudent()
    {
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
     st.createstudent();
     fp.write((char*)&st,sizeof(st));
     cout<<"do you want to add more records(y/n)";
     cin>>ch;
    }while(ch=='y'||ch=='Y');
     fp.close();
   }
   void displayspb(char n[])
   {
   cout<<"book details";
   int flag=0;
   fp.open("book.dat",ios::in);
   while(fp.read((char*)&bk,sizeof(bk)))
   {
     if(strcmpi(bk.retbno(),n)==0)
     {
      bk.showbook();
      flag=1;
     }
   }
    fp.close();
     if(flag==0)
     cout<<"book doen not exit";
     getch();
     }
     void displaysps(char n[])
     { cout<<"student details";
       int flag=0;
       fp.open("student.dat",ios::in);
       while(fp.read((char*)&st,sizeof(st)))
      {  if((strcmpi(st.retadmno(),n)==0))
	{
	  st.showstudent();
	  flag=1;
	 }
	 }
	 fp.close();
	 if(flag==0)
	 cout<<"student does not exits";
	 getch();
	 }
	 void modifybook()
	{  char n[6];
	   int found=0;
	   clrscr();
	   cout<<"modify book no.";
	   cout<<"enter the book no of the book";
	   cin>>n;
	   fp.open("book.dat",ios::in|ios::out);
	   while(fp.read((char*)&bk,sizeof(bk))&&found==0)
	   {
	   if(strcmpi(bk.retbno(),n)==0)
	   {
	   bk.showbook();
	   cout<<"enter the new details of the book"<<endl;
	   bk.modifybook();
	   int pos=-1*sizeof(bk);
	   fp.seekp(pos,ios::cur);
	   fp.write((char*)&bk,sizeof(bk));
	   cout<<"Record updated";
	   found=1;
	  }
	}
	 fp.close();
	 if(found==0)
	 cout<<"Record not found";
	 getch();
	 }
	 void modifystudent()
	 {  char n[6];
	   int found;
	   clrscr();
	   cout<<"Modify student record";
	   cout<<"Enter the admission no. of student";
	   cin>>n;
	   fp.open("student.dat",ios::in|ios::out);
	 while(fp.read((char*)&st,sizeof(st))&&found==0)
	 {  if(strcmpi(st.retadmno(),n)==0)
	   {st.showstudent();
	    cout<<"Enter the new detail of student";
	    st.modifystudent();
	    int pos=-1*sizeof(st);
	    fp.seekp(pos,ios::cur);
	  fp.write((char*)&st,sizeof(st));
	  cout<<"Record updated";
	  found=1;
	  }
	}
	fp.close();
	if(found==0)
	cout<<"REcord not found";
	getch();
	}
	void deletestudent()
	{ char n[6];
	  int flag=0;
	  clrscr();
	  cout<<"Delete student";
	  cout<<"Enter the admission no. of student you want to delete";
	  cin>>n;
	  fp.open("student.dat",ios::in|ios::out);
	  fstream fp2;
	  fp2.open("temp.dat",ios::out);
	  fp.seekg(0,ios::beg);
	  while(fp.read((char*)&st,sizeof(st)))
	{

	if(strcmpi(st.retadmno(),n)!=0)
	  fp2.write((char*)&st,sizeof(st));
	  else
	  flag=1;
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
	if(flag==1)
	cout<<"record deleted";
	else
	cout<<"record not found";
	getch();
      }
      void deletebook()
      {  char n[6];
	 clrscr();
	 cout<<"delete book";
	 cout<<"enter book no you want to delete";
	 cin>>n;
	 fp.open("book.dat",ios::in|ios::out);
	 fstream fp2;
	 fp2.open("temp.dat",ios::out);
	 fp.seekg(0,ios::beg);
	 while(fp.read((char*)&bk,sizeof(bk)))
	{if(strcmpi(bk.retbno(),n)==0)
	{fp2.write((char*)&bk,sizeof(bk));
	}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("temp.dat","book.dat");
	cout<<"record deleted";
	getch();
	}
	void displayalls()
	{  clrscr();
	   fp.open("student.dat",ios::in);
	   if(!fp)
	   {  cout<<"ERROR! file could not be open";
	   getch();
	   return;
	   }
	   cout<<"student list";
	   cout<<"\nadmission no"<<"\t"<<"name"<<"\t"<<"book issued";
	   while(fp.read((char*)&st,sizeof(st)))
	   {  st.report();
	   }
	   fp.close();
	   getch();
	   }
	   void displayallb()
	   {  clrscr();
	      fp.open("book.dat",ios::in);
	      if(!fp)
	     {cout<<"ERROR!!!!file could not be open";
	      getch();
	      return;
	      }
	    cout<<"BOOK LIST\n";
	    cout<<"BOOK NO "<<"\t"<<"BOOK NAME"<<"\t"<<"AUTHOR";
	  while(fp.read((char*)&bk,sizeof(bk)))
	  {
	    bk.report();
	   }
	   fp.close();
	   getch();

	 }
				 // function to issue book
  void bookissue()
   { char sn[6],bn[6];
     int found=0,flag=0;
     clrscr();
     cout<<"\nBOOK ISSUE...";
     cout<<"\nEnter the student's admission no.";
     cin>>sn;
     fp.open("student.dat",ios::in|ios::out);
     fp1.open("book.dat",ios::in|ios::out);
     while(fp.read((char*)&st,sizeof(st))&&found==0)
    {  if(strcmpi(st.retadmno(),sn)==0)
     {  found=1;
       if(st.rettoken()==0)
     { cout<<"\nEnter the book no.";
     cin>>bn;
     while(fp1.read((char*)&bk,sizeof(bk))&&flag==0)
     {  if(strcmpi(bk.retbno(),bn)==0)
     {   bk.showbook();
	 flag=1;
	 st.addtoken();
	 st.getstbno(bk.retbno());
	 int pos=-1*sizeof(st);
	 fp.seekp(pos,ios::cur);
	 fp.write((char*)&st,sizeof(st));
	 cout<<"\n Book issued successfully. Please note:- Submit the book within a period of 15 days";
     }
    }
      if(flag==0)
      cout<<"book no. does not exist";
    }
      else
      cout<<"You have not returned the last book";
     }
   }

      if(found==0)
       cout<<"Student record does not exist";
       getch();
       fp.close();
       fp1.close();
  }
			    //function to deposit book
  void bookdeposit()
  {
      char sn[6],bn[6];
      int found=0,flag=0,day,fine;
      clrscr();
      cout<<"\nBOOK DEPOSIT";
      cout<<"\ntEnter the student's admission no.";
      cin>>sn;
      fp.open("student.dat",ios::in|ios::out);
      fp1.open("book.dat",ios::in|ios::out);
      while(fp.read((char*)&st,sizeof(st))&&found==0)
      {   if(strcmpi(st.retadmno(),sn)==0)
	{   found=1;
	    if(st.rettoken()==1)
	    {
	    while(fp1.read((char*)&bk,sizeof(bk))&& flag==0)
	  {
		 if(strcmpi(bk.retbno(),st. retstbno())==0)
		{  bk.showbook();
		flag=1;
		cout<<"\nbook deposited in no. of days";
		cin>>day;
	   if(day>15)
      {    fine=(day-15)*1;
	   cout<<"\nFine has to be deposited Rs."<<fine;
      }
	   st.resettoken();
	   int pos=-1*sizeof(st);
	   fp.seekp(pos,ios::cur);
	   fp.write((char*)&st,sizeof(st));
	    cout<<"\nBook deposited successfully";
  }
  }
	   if(flag==0)
	    cout<<"Book no. does not exist";
    }
	   else
	    cout<<"No book is issued.. Please check!!";
    }
   }
	  if(found==0)
	  cout<<"Student record not exist";
	 getch();
	  fp.close();
	  fp1.close();
 }
  void adminmenu()
  {  clrscr();
     int ch2;
     cout<<"\nADMINSTATOR MENU";
     cout<<"\n1.create student record";
     cout<<"\n2.Display all student record";
     cout<<"\n3.Disply specific student record";
     cout<<"\n4.Modify student record";
     cout<<"\n5.Delete student record";
     cout<<"\n6.create book";
     cout<<"\n7.display all book";
     cout<<"\n8.display specific book";
     cout<<"\n9.modify book";
     cout<<"\n10.delete book";
     cout<<"\n11.Back to main menu";
     cout<<"\nEnter your choice(1-11)";
     cin>>ch2;
     switch(ch2)
     {  case 1: clrscr();
	writestudent();
	break;
	case 2: displayalls();
	break;
	case 3: char num[6];
	clrscr();
	cout<<"Please enter your ADMISION number";
	cin>>num;
	displaysps(num);
	break;
	case 4: modifystudent();
	break;
	case 5:deletestudent();
	break;
	case 6: clrscr();
		writebook();
		break;
	case 7: displayallb();
	break;
	case 8:
	{   char num[6];
		   clrscr();
	     cout<<"Enter the book no";
	     cin>>num;
	     displayspb(num);
	     break;
	}
	case 9:modifybook();
	break;
	case 10:deletebook();
	break;
	case 11:return;
	default: cout<<"""";
	}
	adminmenu();
	}
  void main()
  { char ch;

  do
	 { clrscr();
	   cout<<"MAIN MENU"<<endl;
	   cout<<"1.BOOK ISSUE"<<endl;
	   cout<<"2.BOOK DEPOSIT"<<endl;
	   cout<<"3.ADMINISTRATOR MENU"<<endl;
	   cout<<"4.EXIT"<<endl;
	   cout<<"Select your option(1-4)"<<endl;
	   ch=getche();
	   switch(ch)
	 { case '1': clrscr();
		    bookissue();
		    break;
	   case '2': bookdeposit();
		     break;
	   case '3': adminmenu();
		     break;
	   case '4': exit(0);
	   default: cout<<"a";
	}
       }	while(ch!='4');
 }

	    // END OF PROJECT





















































































































































