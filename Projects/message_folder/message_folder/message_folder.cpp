// message_folder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<new>
#include<memory>
#include<bitset>
#include<fstream>
#include<sstream>
#include<set>

using namespace std;



class Message {
	friend class Folder;
public: // folders is implicitly initialized to the empty set 
		explicit Message(const std::string &str = "") : contents(str) { } // copy control to manage pointers to this Message 
		Message(const Message&); // copy constructor 
		Message& operator=(const Message&); // copy assignment
		~Message(); // destructor 
		// add/remove this Message from the specified Folder 's set of messages 
		void save(Folder&); 
		void remove(Folder&);
		void addFolder(Folder&);
		void remFolder(Folder&);
		void swap(Message &lhs, Message &rhs);
private:
	std::string contents; // actual message text 
	std::set<Folder*> folders{}; // Folder s that have this Message 
	// utility functions used by copy constructor, assignment, and destructor 
	// add this Message to the Folder s that point to the parameter 
	void add_to_Folders(const Message&); // remove this Message from every Folder in folders 
	void remove_from_Folders();
};






class Folder
{
public:
	Folder() {}

	Folder(const Folder &f) : Message_pt(f.Message_pt) {}

	Folder &operator=(const Folder &f)
	{
		auto x = f.Message_pt;
		Message_pt.clear();
		Message_pt = x;
		return *this;
	}

	~Folder()
	{
		Message_pt.clear();
	}

	void addMsg(Message *m)
	{
		Message_pt.insert(m);
	}

	void remMsg(Message *m)
	{
		for each (auto var in Message_pt)
		{
			if ((var->contents) == (m->contents))
			{
				Message_pt.erase(m);
			}
		}

	}


private:
	set<Message*> Message_pt{};

};


void Message::save(Folder &f)
{
	folders.insert(&f); // add the given Folder to our list of Folders
	f.addMsg(this); // add this Message to f 's set of Messages 
}
void Message::remove(Folder &f)
{
	folders.erase(&f); // take the given Folder out of our list of Folders 
	f.remMsg(this); // remove this Message to f 's set of Messages 
}

void Message::addFolder(Folder &f)
{
	folders.insert(&f);
}

void Message::remFolder(Folder &f)
{
	folders.erase(&f);
}

void Message::add_to_Folders(const Message &m)
{
	for (auto f : m.folders) // for each Folder that holds m 
		f->addMsg(this); // add a pointer to this Message to that Folder 
}
Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m); // add this Message to the Folders that point to m 
}
void Message::remove_from_Folders()
{
	for (auto f : folders) // for each pointer in folders 
		f->remMsg(this); // remove this Message from that Folder 
	folders.clear(); // no Folder points to this Message
}
Message::~Message() { remove_from_Folders(); }
Message& Message::operator=(const Message &rhs)
{ // handle self-assignment by removing pointers before inserting them
	remove_from_Folders(); // update existing Folders 
	contents = rhs.contents; // copy message contents from rhs 
	folders = rhs.folders; // copy Folder pointers from rhs 
	add_to_Folders(rhs); // add this Message to those Folders 
	return *this;
}

void Message::swap(Message &lhs, Message &rhs)
{
	using std::swap; // not strictly needed in this case, but good habit 
					 // remove pointers to each Message from their (original) respective Folders 
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	// swap the contents and Folder pointer sets 
	swap(lhs.folders, rhs.folders); // uses swap(set&, set&) 
	swap(lhs.contents, rhs.contents); // swap(string&, string&) 
									  // add pointers to each Message to their (new) respective Folders 
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}







int main()
{
	

    return 0;
}

