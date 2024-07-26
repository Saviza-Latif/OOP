
#include<iostream>
#include<fstream>
using namespace std;
class Hepler
{
public:
	static int stringlenght(char* str)
	{
		int c = 0;
		while (str[c] != '\0')//terminate when char is null
		{
			c++;
		}
		return c;
	}
	static void StringCopy(char*& dest, char*& src) {
		int i = 0;
		for (; src[i] != '\0'; i++)
		{

			dest[i] = src[i];
		}
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(char* str)
	{
		int i = 0;
		int l = stringlenght(str);
		while (str[i] == 32 || str[i] == '\t')
		{
			for (int j = 0; j < l; j++)
			{
				str[j] = str[j + 1];
			}
			l--;
			i++;
		}
		l = stringlenght(str);
		while (str[l - 1] == 32 || str[l - 1] == '\t')
		{
			str[l - 1] = str[l];
			l--;
		}
		char* newStr = new char[stringlenght(str) + 1];// make new array of lenght of array in parameter


		StringCopy(newStr, str);// copy in temp
		return newStr;
	}
	static bool compare(char* temp, char* temp1)//compare two strings
	{
		for (int i = 0; temp1[i] != 0; i++)
		{
			if (temp[i] != temp1[i])
			{
				return false;
			}
		}
		return true;
	}
	
};
class page;
class post;
class user;
class object;             // classes
class comment;
class activity;
class memory;
class date;
class object
{
private:
	char* ID;

public:
	object()
	{
		ID = 0;

	}
	virtual void printview()
	{
		//virtual function
	}
	virtual void printcurrentuser()
	{
		// virtual function
	}
	virtual void timelineadded(post* ptr)
	{
		// virtual function of timelineadded
	}
	void setID(char* Id) // setter for ID
	{
		ID = Id;
	}
	char* getID()   //getter for ID
	{
		return ID;
	}
	virtual~object()// destructor 
	{

		if (ID)
		{
			delete ID;
			
		}
	}


};

class activity
{

private:
	char* value;
	int type;

public:
	activity()
	{
		value = 0;
		type = 0;
	}

	~activity()
	{
		if (value)
		{
			delete value;
			
		}
	}

	void readActivityfromfile(ifstream& fin)
	{
		fin >> type;
		char temp[80];
		fin.getline(temp, 80);
		value = Hepler::GetStringFromBuffer(temp);   //reading value from file
	}

	void activityview()
	{
		if (type == 1)
		{
			cout << " is feeling " << value << endl;
		}
		if (type == 2)
		{
			cout << " is thinking about " << value << endl;
		}
		if (type == 3)
		{
			cout << " is making " << value << endl;
		}
		if (type == 4)
		{
			cout << " is celeberating " << value << endl;
		}
	}


};

class date
{
private:
	int day;
	int month;
	int year;
public:

	date()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	static date currentdate;    // static current date
	static void setcurrentdate(int d, int m, int y)
	{
		currentdate.day = d;
		currentdate.month = m;
		currentdate.year = y;
	}

	void readDatefromfile(ifstream& fin)    // reading date from file
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}

	void printdate()      //printing of date(11/12/2010)
	{
		cout << day << "/" << month << "/" << year << endl;
	}
	
	bool comparedate(int i)
	{
		if (i == 1)//for simple compare a date.timeline
		{
			if ((day == currentdate.day || day + 1 == currentdate.day))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (i == 2)//for memory compare a date
		{
			if (day == currentdate.day && month == currentdate.month && year != currentdate.year)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (i == 3)
		{
			if ((day == currentdate.day || day + 1 == currentdate.day) && month == currentdate.month)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	

	int getyear()
	{
		return year;   //getter  
	}
};
date date::currentdate;//initializing currentdate(static)

class comment
{

private:
	char* ID;
	object* commentby;
	char* text;

public:

	comment()  //constructor
	{
		ID = 0;
		commentby = 0;
		text = 0;
	}

	~comment()//destructor
	{
		if (ID)
		{
			delete ID;
			ID = 0;
		}
		if (text)
		{
			delete text;
			text = 0;
		}
	}

	void setcommentby(object* obj)
	{
		commentby = obj;     //setter
	}

	void readcommentfromfile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		ID = Hepler::GetStringFromBuffer(temp);    // reading Id
	}

	void readcommentText(ifstream& fin)
	{
		char temp[100];
		fin.getline(temp, 80);
		text = Hepler::GetStringFromBuffer(temp);  //reading text
	}

	void printview()
	{
		commentby->printcurrentuser();   //print current user name
		cout << "  wrote: \"";
		cout << text << "\"" << endl;   // print text
	}

	void setcomment(char* temp)
	{
		text = Hepler::GetStringFromBuffer(temp);   // add comment
	}




};

class post
{

private:
	char* ID;
	char* text;
	date sharedDate;
	comment** commented;
	object* sharedby;
	object** likedby;
	activity* act;
	int type;
	int likedcount;
	int commentcount;

public:
	post()  //constructor
	{
		ID = 0;
		text = 0;
		commented = 0;
		sharedby = 0;
		likedby = 0;
		act = 0;
		type = 0;
		likedcount = 0;
		commentcount = 0;
	}

	 ~post() //destructor
	{
		if (ID)
		{
			delete[] ID;
			
		}
		if (text)
		{
			delete[] text;
			
		}
		if (commented)
		{
			for (int i = 0; i < commentcount; i++)
			{
				if (commented[i])
				{
					delete commented[i];
				}
			}
			delete commented;  
		}
		if (likedby)
		{

			delete[] likedby;
			
		}
		if (act)
		{
			delete act;
			
		}
	}

	
	void setvalues(char* txt, object* share)
	{
		text = Hepler::GetStringFromBuffer(txt);
		sharedby = share;
		sharedDate = date::currentdate;
	}

	char* getid()
	{
		return ID;    //getter
	}

	void setshared(object* obj)     //store the ptr of user or page who share post
	{
		sharedby = obj;
	}

	void readpostfromfile(ifstream& fin)
	{
		act = new activity;
		fin >> type;
		char temp[100];
		fin >> temp;
		ID = Hepler::GetStringFromBuffer(temp);    // reading ID
		sharedDate.readDatefromfile(fin);          // reading date( function of date class)
		fin.getline(temp, 100);
		fin.getline(temp, 100);
		text = Hepler::GetStringFromBuffer(temp);   // reading text
		if (type == 2)
		{
			
			act->readActivityfromfile(fin);         // reading activity( function of activity class)
		}
	}

	void setliked(object* obj)
	{
		if (likedby == 0)    //when we have to add first likedby
		{
			likedby = new object * [10];
			likedby[likedcount] = obj;
			likedcount++;


		}
		else
		{
			likedby[likedcount] = obj;
			likedcount++;
		}
	}
	void addcomment(comment* ptr)
	{
		if (commented == 0)          //when we have to add first comment
		{
			commented = new comment * [10];
			commented[commentcount] = ptr;
			commentcount++;

		}
		else
		{
			commented[commentcount] = ptr;
			commentcount++;
		}
	}

	bool compareddated(int i)
	{
		if (i == 1)
		{
			if (sharedDate.comparedate(1))//timeline
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (i == 2)
		{
			if (sharedDate.comparedate(2))//memory
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (i == 3)
		{
			if (sharedDate.comparedate(3))//homepage
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
	}

	virtual void printviewpost()
	{
		cout << "---";
		sharedby->printcurrentuser();
		if (type == 2)
			act->activityview();
		if (type == 1)
			cout << " shared ";
		cout << "\"" << text << "\"";
		sharedDate.printdate();
		for (int i = 0; i < commentcount; i++)
		{
			commented[i]->printview();
		}
	}
	object* getsharedby()
	{
		return sharedby;
	}



	int getyear()
	{
		int g = sharedDate.getyear();
		return g;
	}

	char* gettext()
	{
		return text;
	}

	void printpost()
	{

		cout << "---";
		sharedby->printcurrentuser();
		if (type == 2)
			act->activityview();
		if (type == 1)
			cout << " shared ";
		cout << "\"" << text << "\"";
		sharedDate.printdate();
	}

	void viewlikedlist()
	{
		cout << "\n\npost liked by\n\n";
		if (likedcount == 0)
		{
			cout << "No one liked the post\n";
		}
		else
		{
			for (int i = 0; i < likedcount; i++)
			{
				likedby[i]->printview();
				cout << "\n";
			}
		}
	}

	void likeapost(object* obj)
	{
		if (likedby == 0)
		{
			likedby = new object * [10];
			likedby[likedcount] = obj;
			likedcount++;
		}
		else
		{
			if (likedcount < 10)
			{
				likedby[likedcount] = obj;
				likedcount++;
			}
		}
	}
};
class memory :public post
{
	post* posted;

public:

	memory()
	{
		posted = 0;
	}

	~memory()
	{
		
	}

	void printviewpost()
	{
		cout << "---";  getsharedby()->printcurrentuser(); cout << "  " << gettext() << "  ";
		date::currentdate.printdate();
		cout << "\n " << date::currentdate.getyear() - posted->getyear() << " Years Ago\n";
		posted->printpost();
	}

	memory(post* ptr, char* temp, object* shared) :post()
	{
		posted = ptr;
		
		setvalues(temp, shared);
	}
};

class page :public object
{

private:

	post** timeline;
	int postcount;
	char* title;

public:
	page() //constructor
	{
		timeline = 0;
		postcount = 0;

		title = 0;
	}

	~page() //destructor
	{

		if (title)
		{
			delete title;
			
		}
		if (timeline)
		{
			for (int i = 0; i < postcount; i++)
			{
				if (timeline[i])
				{
					delete timeline[i];
				}
			}
			delete[]timeline;   //loop
			
		}

	}



	void readdatafromfile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;

		char* id = Hepler::GetStringFromBuffer(temp);   //reading ID
		setID(id);
		fin.getline(temp, 80);
		title = Hepler::GetStringFromBuffer(temp);      //reading title
	}

	void timelineadded(post* ptr)            // add post to timeline
	{
		if (timeline == 0)    //when first post have to add
		{
			timeline = new post * [10];
			timeline[postcount] = ptr;
			postcount++;
		}
		else
		{

			timeline[postcount] = ptr;
			postcount++;
		}
	}

	void printview()
	{
		cout << getID();
		cout << " " << title << " ";
	}

	void printcurrentuser()
	{

		cout << " " << title << " ";
	}

	void printpagepost()
	{
		for (int j = 0; j < postcount; j++)
		{
			if (timeline[j]->compareddated(1))   //compare dates with current date
			{
				timeline[j]->printviewpost();
			}
		}
	}

	void printapage()
	{
		printview();
		cout << endl;
		for (int j = 0; j < postcount; j++)
		{

			timeline[j]->printviewpost();

		}
	}
};
class user :public object
{
private:

	char* fname;
	char* lname;
	page** likedpages;
	user** friends;
	int pagecount;
	int friendcount;
	post** timeline;
	int postcount;

public:
	user()  //constructor
	{

		fname = 0;
		lname = 0;
		likedpages = 0;
		friends = 0;
		pagecount = 0;
		friendcount = 0;
		timeline = 0;
		postcount = 0;

	}

	~user() //destructor
	{

		if (fname)
		{
			delete fname;
			
		}
		if (lname)
		{
			delete lname;
			
		}
		if (likedpages)
		{

			delete[] likedpages;
			
		}
		if (friends)
		{

			delete[] friends;
			
		}
		if (timeline)
		{
			for (int i = 0; i < postcount; i++)
			{
				if (timeline[i])
				{
					delete timeline[i];
				}
			}
			delete[]timeline;
		}


	}

	bool postexist(char* p)
	{
		for (int i = 0; i < postcount; i++)
		{
			if (Hepler::compare(timeline[i]->getid(), p))
			{
				return true;
			}

		}
		return false;
	}

	void readdatafromfile(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		char* id = Hepler::GetStringFromBuffer(temp);  // reading ID
		setID(id);
		fin >> temp;
		fname = Hepler::GetStringFromBuffer(temp);    // reading first name
		fin >> temp;
		lname = Hepler::GetStringFromBuffer(temp);      // reading last name
	}

	void likepage(page* pageptr) // like the pages by user
	{
		if (likedpages == 0)   // when the user have to store first likepage
		{
			likedpages = new page * [10];
			likedpages[pagecount] = pageptr;
			pagecount++;
		}
		else
		{
			likedpages[pagecount] = pageptr;
			pagecount++;
		}
	}

	void friendadded(user* userptr) // add friends of user 
	{
		if (friends == 0)        // when the user have to store first friend
		{
			friends = new user * [10];
			friends[friendcount] = userptr;
			friendcount++;
		}
		else
		{
			friends[friendcount] = userptr;
			friendcount++;
		}
	}

	void timelineadded(post* ptr)            // add post to timeline
	{
		if (timeline == 0)    //when first post have to add
		{
			timeline = new post * [10];
			timeline[postcount] = ptr;
			postcount++;
		}
		else
		{

			timeline[postcount] = ptr;
			postcount++;
		}
	}

	void printcurrentuser()
	{
		cout << fname << " " << lname; //printing first and last name;

	}

	void printview()
	{
		cout << getID() << " ";
		cout << fname << " ";
		cout << lname;
	}

	void printlikedpages()
	{
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << "command:            view liked pages\n";
		cout << fname << " " << lname << "   likedpages\n\n\n";
		if (pagecount == 0)
		{
			cout << "No likedPage\n";
		}
		else
		{
			for (int i = 0; i < pagecount; i++)
			{
				likedpages[i]->printview();    //printing pages 
				cout << "\n";
			}
		}
		cout << "\n\n\n";
	}
	void printfriendlist()
	{

		cout << "\nCommand:           View Friend List\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << fname << " " << lname << "   friendlist\n\n\n";
		int i = 0;
		if (friendcount == 0)
		{
			cout << "No friends\n";
		}
		else
		{
			for (; i < friendcount;)
			{
				friends[i]->printview();    //printing friends
				i++;
				cout << "\n";
			}
		}

	}

	void viewhomepage()
	{
		cout << "Command:      ViewHomepage\n";
		cout << "--------------------------------------------------------------------------------------------------------------";
		cout << "\n" << fname << " " << lname << " - Homepage\n\n\n";
		for (int i = 0; i < friendcount; i++)
		{

			for (int j = 0; j < friends[i]->postcount; j++)
			{
				if (friends[i]->timeline[j]->compareddated(3))
				{
					friends[i]->timeline[j]->printviewpost();   //printing posts by friends
					cout << "\n\n";
				}
			}
		}
		for (int i = 0; i < pagecount; i++)
		{

			likedpages[i]->printpagepost(); //fuction in page class which compared it with date and print the post by pages
			cout << "\n\n";


		}
	}

	void viewtimeline()
	{
		cout << "Command:      ViewTimeline\n";
		cout << "--------------------------------------------------------------------------------------------------------------";


		cout << "\n" << fname << " " << lname << " - Timeline\n\n\n";

		for (int i = 0; i < postcount; i++)
		{

			post* p = timeline[i];

			if (p->compareddated(1))
			{
				timeline[i]->printviewpost();  //print posts 

				cout << "\n\n";
			}
		}
	}

	void seeyourmemories()  //show your memories
	{
		cout << "Command:                   SeeYourMemories()\n";
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.";
		for (int i = 0; i < postcount; i++)
		{
			if (timeline[i]->compareddated(2))
			{
				cout << "\nOn this Day\n";
				cout << date::currentdate.getyear() - timeline[i]->getyear();  //diff of years
				cout << " Years Ago\n\n";
				timeline[i]->printviewpost();
			}
		}
	}

	void memoryaddedtimeline(post* tempmemory)
	{
		postcount++;
		post** temp = nullptr;
		if (timeline)
		{
			temp = timeline;
		}
		timeline = new post * [postcount];
		timeline[0] = tempmemory;
		int p = postcount - 1;
		if (temp)
		{
			for (int i = 0; i < p; i++)

				timeline[i + 1] = temp[i];

			delete[]temp;

		}
	}

	void sharedamemory(post* temp, char* tempText)
	{

		object* shared = temp->getsharedby();
		memory* sharememory = new memory(temp, tempText, shared);
		this->memoryaddedtimeline(sharememory);


	}
};


class app
{

private:
	page** pagelist;
	user** userlist;
	post** postlist;
	comment** commentlist;
	int totalcomment;
	int totalpages;
	int totalposts;
	int totalusers;

public:
	app()//constructor of app
	{
		pagelist = 0;
		userlist = 0;
		postlist = 0;
		commentlist = 0;
		totalcomment = 0;
		totalusers = 0;
		totalpages = 0;
		totalposts = 0;
	}

	~app()
	{
		if (userlist)//deallocation of userlist
		{
			for (int i = 0; i < totalusers; i++)
			{
				if (userlist[i])
					delete userlist[i];
			}
			delete[] userlist;
		}
		if (pagelist)//deallocation of pagelist
		{
			for (int i = 0; i < totalpages; i++)
			{
				delete pagelist[i];
			}
			delete[] pagelist;
		}
		if (commentlist)//deallocation of commentlist
		{
			
			delete[] commentlist;
		}
		if (postlist)//deallocation of postlist
		{
			
			delete[] postlist;
		}

	}

	void loadpagefromfile(const char* filename) //to load page
	{
		ifstream fin(filename);
		if (fin.is_open())    //open file
		{

			fin >> totalpages;         //taking totalpages 
			pagelist = new page * [totalpages + 1];   //allocatation
			int i = 0;
			for (; i < totalpages; i++)
			{
				pagelist[i] = new page();
				pagelist[i]->readdatafromfile(fin);    // function of page class
			}
			pagelist[i] = 0;
			fin.close();
		}
		else
		{
			cout << "file is closed\n";
		}

	}

	void loaduserfromfile(const char* filename) // to load user
	{
		ifstream fin(filename);
		if (fin.is_open())    //open file
		{
			char*** friendIDs = 0;

			fin >> totalusers;               // reading total user
			friendIDs = new char** [totalusers];
			userlist = new user * [totalusers + 1];
			int i = 0;
			char temp[80];
			for (; i < totalusers; i++)
			{
				userlist[i] = new user();
				userlist[i]->readdatafromfile(fin);     // function of user class
				fin >> temp;
				int j = 0;


				friendIDs[i] = new char* [10];
				while (temp[0] != '-' || temp[1] != '1')
				{

					friendIDs[i][j] = Hepler::GetStringFromBuffer(temp);

					j++;
					fin >> temp;
				}
				friendIDs[i][j] = NULL;
				fin >> temp;
				if (temp[0] != '-' || temp[1] != '1')
				{
					while (temp[0] != '-' || temp[1] != '1')
					{

						page* PagePtr = searchById(temp);    //search the page by it id and return ptr 
						userlist[i]->likepage(PagePtr);      // add ptr to the likedpage of user
						fin >> temp;
					}
				}
			}
			userlist[i] = 0;
			int k = 0;
			for (int i = 0; i < totalusers; i++)
			{

				while (friendIDs[i][k] != NULL)
				{
					user* userptr = searchuserbyID(friendIDs[i][k]);   //search the user by it id and return ptr 
					userlist[i]->friendadded(userptr);                  // add ptr to the friends of user
					delete friendIDs[i][k];
					k++;


				}

				k = 0;


			}
			for (int i = 0; i < totalusers; i++)
			{
				delete[]friendIDs[i];
			}
			delete[]friendIDs;
			fin.close();
		}
		else
		{
			cout << "file is closed\n";
		}

	}

	void loadpostfromfile(const char* filename) // to load post
	{
		ifstream fin(filename);
		if (fin.is_open())     //open file
		{

			fin >> totalposts;        //reading total posts
			postlist = new post * [totalposts + 1];
			int i = 0;
			for (; i < totalposts; i++)
			{
				postlist[i] = new post;
				postlist[i]->readpostfromfile(fin);            //function of post class
				char temp[80];
				fin >> temp;

				if (temp[0] == 'u')
				{
					object* objectptr = searchuserbyID(temp);    //search the user by it id and return ptr 
					postlist[i]->setshared(objectptr);           // set sharedby with this ptr
					objectptr->timelineadded(postlist[i]);       // add every post to the timeline of user
				}
				else
				{
					object* objectptr = searchById(temp); // search the page by it id and return ptr
					postlist[i]->setshared(objectptr);    // set sharedby with this ptr
					objectptr->timelineadded(postlist[i]);      // add every post to the timeline of page
				}
				fin >> temp;
				while (temp[0] != '-' || temp[1] != '1')
				{
					if (temp[0] == 'u')
					{
						object* objectptr = searchuserbyID(temp);
						postlist[i]->setliked(objectptr);
					}
					else
					{
						object* objectptr = searchById(temp);
						postlist[i]->setliked(objectptr);
					}
					fin >> temp;
				}

			}
			postlist[i] = nullptr;
			fin.close();
		}
		else
		{
			cout << "file is closed\n";
		}
	}

	void loadcommentfromfile(const char* filename)//to load comments
	{
		ifstream fin(filename);

		if (fin.is_open())   //file open
		{

			char temp[80];

			fin >> totalcomment;    //reading total comments
			char** postid = new char* [totalcomment];

			commentlist = new comment * [totalcomment + 1];
			int i = 0;
			for (; i < totalcomment; i++)
			{
				commentlist[i] = new comment;
				commentlist[i]->readcommentfromfile(fin);   //function of comment to read comments

				fin >> temp;
				postid[i] = Hepler::GetStringFromBuffer(temp);  // reading the post id which comment

				fin >> temp;
				if (temp[0] == 'u')
				{
					object* objectptr = searchuserbyID(temp);   // search by user id and return ptr
					commentlist[i]->setcommentby(objectptr);   // setting who comment
				}
				else
				{
					object* objectptr = searchById(temp);   // search by page id and return ptr
					commentlist[i]->setcommentby(objectptr); // setting who comment
				}
				commentlist[i]->readcommentText(fin);
			}
			commentlist[i] = nullptr;
			int j = 0;
			for (; j < totalcomment; j++)
			{
				post* postptr = searchpostbyID(postid[j]);
				postptr->addcomment(commentlist[j]);
			}
			for (int i = 0; i < totalcomment; i++)
			{
				delete[] postid[i];
			}
			delete[]postid;
			fin.close();

		}

		else
		{
			cout << "file is closed\n";
		}

	}

	page* searchById(char* temp)//to search page by id and return ptr of that page
	{


		char* pageid = 0;
		for (int j = 0; pagelist[j] != 0; j++)
		{
			char* pageid = pagelist[j]->getID();
			if (Hepler::compare(pageid, temp))
			{
				return pagelist[j];
			}
		}
		delete pageid;
	}

	user* searchuserbyID(char* temp) //to search user by id and return ptr of that user
	{

		char* userid = 0;
		for (int j = 0; j < totalusers; j++)
		{
			userid = userlist[j]->getID();

			if (Hepler::compare(userid, temp))
			{
				return userlist[j];
			}

		}
		delete[]userid;


	}

	post* searchpostbyID(char* temp) //to search a post by id and return ptr of that post
	{
		char* postid = 0;
		for (int j = 0; j < totalposts; j++)
		{
			postid = postlist[j]->getid();

			if (Hepler::compare(postid, temp))
			{
				return postlist[j];
			}

		}
		delete[]postid;
	}

	void load()//to load data fro files
	{
		loadpagefromfile("page.txt");
		loaduserfromfile("user.txt");
		loadpostfromfile("post.txt");
		loadcommentfromfile("comment.txt");
	}

	void run()
	{

		load();
		cout << "Command:                      Set Current System Date ";
		date::currentdate.setcurrentdate(15, 11, 2017);
		date::currentdate.printdate();
		cout << "\nSystem Date ";
		date::currentdate.printdate();

		char name[4] = "u7";

		user* currentuser = searchuserbyID(name);
		cout << "\nCommand:       Set current user " << currentuser->getID() << "\n ";
		currentuser->printcurrentuser();
		cout << " successfully set as Current User\n";
		currentuser->printfriendlist();
		currentuser->printlikedpages();
		currentuser->viewhomepage();
		currentuser->viewtimeline();
		char temp[80] = "post5";
		post* p = searchpostbyID(temp);
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		cout << "Command:   ViewLikedList"<<p->getid();
		cout << "\n-------------------------------------------------------------------------------------------------------------\n";
		p->viewlikedlist();
		p->likeapost(currentuser);
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		cout << "Command:   ViewLikedList"<<p->getid();
		cout << "\n-------------------------------------------------------------------------------------------------------------\n";
		p->viewlikedlist();
		char temp1[80] = "post4";
		p = searchpostbyID(temp1);
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		cout << "Command: PostComment(post4, Good Luck for your Result)\n";
		cout << "Command: ViewPost(post4)\n";
		cout << "-------------------------------------------------------------------------------------------------------------\n\n\n";
		p->printviewpost();
		comment* commentadd;
		commentadd = new comment;
		char tempcomment[] = "Thanks for the wishes";
		commentadd->setcomment(tempcomment);
		commentadd->setcommentby(currentuser);
		char temp2[80] = "post8";
		p = searchpostbyID(temp2);
		p->addcomment(commentadd);
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		cout << "Command: PostComment(post8, Thanks for the wishes))\n";
		cout << "Command: ViewPost(post8)\n";
		cout << "-------------------------------------------------------------------------------------------------------------\n\n\n";
		p->printviewpost();
		char temp3[7] = "post10";
		p = searchpostbyID(temp3);
		char tempt[80] = "Never thought I will be specialist in this field ...";


		cout << "\n-------------------------------------------------------------------------------------------------------------\n";
		currentuser->seeyourmemories();

		if (currentuser->postexist(temp3))
		{
			cout << "\n-------------------------------------------------------------------------------------------------------------\n";
			cout << "Command:    ShareMemory(post10,\"Never thought I will be specialist in this field \"\n";
			
			currentuser->sharedamemory(p, tempt);
			currentuser->viewtimeline();
		}
		char temper[5] = "p1";

		page* paged = searchById(temper);
		cout << "\n-------------------------------------------------------------------------------------------------------------\n";
		cout << "command:               pageview \"" << paged->getID() << "\"\n";
		cout << "\n-------------------------------------------------------------------------------------------------------------\n";
		paged->printapage();

		char name3[4] = "u11";
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		
		currentuser = searchuserbyID(name3);
		cout << "Command:       Set current user \"" << currentuser->getID() << "\"\n";
		currentuser->printcurrentuser();
		cout << " successfully set as Current User\n";
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		currentuser->viewhomepage();
		currentuser->viewtimeline();
		

	}
};
int main()
{
	app fb;
	fb.run();
}
