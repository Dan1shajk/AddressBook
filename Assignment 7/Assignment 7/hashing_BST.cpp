//Danish Shakil
//Assignment 7
//11/27/15




#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class BST_Node												
{
public:

	string lastname, firstname, address, phone_number;			

	BST_Node  *lchild, *rchild;									

};

class Clients_Info_BST											
{
public:

	Clients_Info_BST();										
	Clients_Info_BST(const Clients_Info_BST &);		//not implemented			
	~Clients_Info_BST();										         
	void Insert(const string & s);								
	void Insert(BST_Node * & node, const string & s);		
	void Remove(const string & s);								
	void Remove(BST_Node * & node, const string & s);		
	BST_Node * inorder_succ(BST_Node * node);					
	void Print();												
	void Print_Inorder(BST_Node *root);							
	BST_Node * Search(const string & s);						
	BST_Node * Search_Aux(BST_Node * & node, const string & s);	
	string Write();												
	string Write_Inorder(BST_Node *root);						


private:

	BST_Node *root;											

};

class Client_Address_Book
{
public:
	Client_Address_Book();										
	Client_Address_Book(const Client_Address_Book &);		
	~Client_Address_Book();										
	void Insert(const string & s);								
	void Remove(const string & s);								
	void Update(const string & s);								
	void Print_BST(const string & s);							
	void Print_Hash_Table();									
	void Print_Hash_Table_to_File(const string & filename);		
	BST_Node * Search(const string & s);						
	unsigned int Hash_Function(const string & s);				

private:
	int capacity;										

	Clients_Info_BST   *hash_table;								

};



int main()

{

	Client_Address_Book My_Book;
	My_Book.Insert("Bullard Lofton 777 Glades Road 207-2780");
	My_Book.Remove("Bullard Lofton");
	My_Book.Insert("Bullard Lofton 777 Glades Road 207-2780");


	My_Book.Update("1 Bullard Lofton Comb Harry 555 Palmetto Park Road 555-3444");
	My_Book.Insert("Bullard Lofton 777 Glades Road 207-2780");
	My_Book.Update("2 Bullard Lofton Blart Paul 555 Palmetto Park Road");
	My_Book.Update("3 Blart Paul 5661 Fun St 123-4567");
	My_Book.Update("4 Blart Paul Micenzie Mick 000-0000");
	My_Book.Update("5 Micenzie Mick Mcdonald Ronald");
	My_Book.Update("6 Mcdonald Ronald 6969 Uranus Way");
	My_Book.Update("7 Mcdonald Ronald 696-6969");


	My_Book.Print_BST("B");
	My_Book.Print_Hash_Table();



	Client_Address_Book Your_Book = My_Book;	//Copy Constructor not implemented

	My_Book.Print_Hash_Table_to_File("sorted_client_address_bk.txt");

	return 0;
}






//*************************************************************************************
//Name:  Clients_Info_BST (Default)
//Precondition: No precondition
//Postcondition: A BST with the root being NULL 
//Description:  This will allocate memory and set the data members of a BST
//
//*************************************************************************************
Clients_Info_BST::Clients_Info_BST()
{
	root = NULL;
}

//*************************************************************************************
//Name:  Clients_Info_BST (Copy Constructor)
//Precondition: A BST
//Postcondition: A copy of a BST
//Description:  This will make a deep copy of a BST
//
//*************************************************************************************
Clients_Info_BST::Clients_Info_BST(const Clients_Info_BST &)
{
	cout << "Not implemented" << endl << endl;
}

//*************************************************************************************
//Name:  Clients_Info_BST (Destructor)
//Precondition: A BST
//Postcondition: Deleted BST
//Description:  This will give the memory given to the BST back to the system
//
//*************************************************************************************
Clients_Info_BST::~Clients_Info_BST()
{
	delete root;
}

//*************************************************************************************
//Name:  Clients_Info_BST::Insert
//Precondition: A BST with n elements
//Postcondition: A BST with n+1
//Description:  This function send the root of the BST to the Insert_Aux function
//
//*************************************************************************************
void Clients_Info_BST::Insert(const string & s)
{
	Insert(root, s);
}

//*************************************************************************************
//Name:  Clients_Info_BST::Insert_Aux
//Precondition: A BST with n elements
//Postcondition: A BST with n+1
//Description:  This function will add a element to the BST by using the BST property
//
//*************************************************************************************
void Clients_Info_BST::Insert(BST_Node * & node, const string & s)
{

	string first;
	string last;
	string number;
	string addr;
	int x = 0;
	int y = 0;
	int z = 0;

	x = s.find(" ", 0);
	last = s.substr(0, x);
	x++;
	y = s.find(" ", x);
	first = s.substr(x, (y - x));
	y++;
	z = s.length() - 8;
	addr = s.substr(y, (z - y));
	number = s.substr(z, 8);

	if (node == NULL)
	{
		node = new BST_Node;

		x = s.find(" ", 0);
		node->lastname = s.substr(0, x);
		x++;

		y = s.find(" ", x);
		node->firstname = s.substr(x, (y - x));
		y++;

		z = s.length() - 8;
		node->address = s.substr(y, (z - y));

		node->phone_number = s.substr(z, 8);

		node->lchild = NULL;
		node->rchild = NULL;
	}
	else if (node->lastname > last)
	{
		Insert(node->lchild, s);
	}
	else if (node->lastname < last)
	{
		Insert(node->rchild, s);
	}
	else
	{
		if (node->firstname > first)
		{
			Insert(node->lchild, s);
		}
		else if (node->firstname < first)
		{
			Insert(node->rchild, s);
		}
	}
}

//*************************************************************************************
//Name:  Clients_Info_BST::Remove
//Precondition: A BST with n elements
//Postcondition: A BST with n-1 elements 
//Description:  This function will send the root of the BST to the Remove_Aux function
//
//*************************************************************************************
void Clients_Info_BST::Remove(const string & s)
{
	Remove(root, s);
}

//*************************************************************************************
//Name:  Clients_Info_BST::Remove_Aux
//Precondition: A BST with n elements
//Postcondition: A BST with n-1 elements
//Description:  This function will remove an element from the BST while maintaining the BST property
//
//*************************************************************************************
void Clients_Info_BST::Remove(BST_Node * & node, const string & s)
{
	string last;
	string first;
	int x = 0;
	int y = 0;

	x = s.find(" ", 0);
	last = s.substr(0, x);
	x++;
	y = s.find(" ", x);
	first = s.substr(x, (y - x));
	y++;

	if (node == NULL)
	{
		cout << "Nothing to do -- tree is empty" << endl << endl;
	}
	else if (node->lastname > last)
	{
		Remove(node->lchild, s);
	}
	else if (node->lastname < last) 
	{
		Remove(node->rchild, s);
	}
	else  
	{
		BST_Node *ptr;

		if (node->firstname == first)
		{
			if (node->lchild == 0)  
			{
				ptr = node->rchild;
				delete node;
				node = ptr;
			}
			else if (node->rchild == 0)  
			{
				ptr = node->lchild;
				delete node;
				node = ptr;
			}
			else   
			{
				ptr = inorder_succ(node);
				node->lastname = ptr->lastname;
				node->firstname = ptr->firstname;
				node->address = ptr->address;
				node->phone_number = ptr->phone_number;
				Remove(node->rchild, ptr->lastname);
			}
		}
		else
		{
			if (node->firstname > first)
			{
				Remove(node->lchild, s);
			}
			else if (node->firstname < first) 
			{
				Remove(node->rchild, s);
			}
		}
	}
}

//*************************************************************************************
//Name:  Clients_Info_BST::inorder_succ
//Precondition: Original node
//Postcondition: The node following right after the original node 
//Description:  This function will find the successor node of the orginal node for removing purposes
//
//*************************************************************************************
BST_Node * Clients_Info_BST::inorder_succ(BST_Node * node)
{
	BST_Node * ptr = node->rchild;

	while (ptr->lchild != 0)
	{
		ptr = ptr->lchild;
	}

	return ptr;
}

//*************************************************************************************
//Name:  Clients_Info_BST::Print
//Precondition: No precondition
//Postcondition: Printed BST in order
//Description:  This function will send the root of the BST to the Print_Inorder function
//
//*************************************************************************************
void Clients_Info_BST::Print()
{
	Print_Inorder(root);
}

//*************************************************************************************
//Name:  Clients_Info_BST
//Precondition: No precondition
//Postcondition: Printed BST inorder 
//Description:  This function will print a BST in order
//
//*************************************************************************************
void Clients_Info_BST::Print_Inorder(BST_Node *root)
{
	if (root != NULL)
	{
		Print_Inorder(root->lchild);
		cout <<"Last Name: "<< root->lastname << endl;
		cout <<"First Name: " << root->firstname << endl;
		cout <<"Address: " << root->address << endl;
		cout <<"Phone NUmber: " << root->phone_number << endl << endl;
		Print_Inorder(root->rchild);
	}
}

//*************************************************************************************
//Name:  Clients_Info_BST::Search
//Precondition: No precondition
//Postcondition: A node from a BST 
//Description:  This function will send the root to the Search_Aux function
//
//*************************************************************************************
BST_Node * Clients_Info_BST::Search(const string & s)
{
	BST_Node *ptr = Search_Aux(root, s);

	return ptr;
}

//*************************************************************************************
//Name:  Clients_Info_BST::Search_Aux
//Precondition: No precondition
//Postcondition: A node from a BST  
//Description:  This function will search for a node in a BST
//
//*************************************************************************************
BST_Node * Clients_Info_BST::Search_Aux(BST_Node * & node, const string & s)
{
	string last;
	string first;
	int x = 0;
	int y = 0;

	x = s.find(" ", 0);
	last = s.substr(0, x);
	x++;
	y = s.find(" ", x);
	first = s.substr(x, (y - x));
	y++;


	if (node == NULL)
	{
		BST_Node *emptyPTR = new BST_Node;
		cout << "Client not found" << endl << endl;
		return emptyPTR;
	}
	else if (node->lastname > last)
	{
		BST_Node *temp = Search_Aux(node->lchild, s);

		if (temp->lastname != "")
		{
			return temp;
		}
		
	}
	else if (node->lastname < last) 
	{
		BST_Node *temp = Search_Aux(node->rchild, s);

		if (temp->lastname != "")
		{
			return temp;
		}
		
	}
	else  
	{
		if (node->firstname == first)
		{
			return node;
			cout << "Client found!" << endl << endl;
			
		}
		else
		{
			if (node->firstname > first)
			{

				BST_Node *temp = Search_Aux(node->lchild, s);

				if (temp->lastname != "")
				{
					return temp;
				}
			}
			else if (node->firstname < first) 
			{
				BST_Node *temp = Search_Aux(node->rchild, s);

				if (temp->lastname != "")
				{
					return temp;
				}
			}
		}
	}
}

//*************************************************************************************
//Name:  Clients_Info_BST::Write
//Precondition: No precondition
//Postcondition: BST to a file 
//Description:  This function will send the root of the BST to Write_Inorder function
//
//*************************************************************************************
string Clients_Info_BST::Write()
{
	string key;

	key = Write_Inorder(root);
	return key;
}

//*************************************************************************************
//Name:  Clients_Info_BST::Write_Inorder
//Precondition: No precondition
//Postcondition: BST to a file   
//Description:  This function will write a BST to a file
//
//*************************************************************************************
string Clients_Info_BST::Write_Inorder(BST_Node *root)
{
	string key = "";

	if (root != NULL)
	{
		Write_Inorder(root->lchild);
		key += root->lastname + " ";
		key += root->firstname + " ";
		key += root->address + " ";
		key += root->phone_number + "\n" + "\n";
		Write_Inorder(root->rchild);

		return key;
	}
	return key = +"";
}




//*************************************************************************************
//Name:  Client_Address_Book (Default)
//Precondition: No precondition
//Postcondition: A hashtable with BSTs  
//Description:  This will allocate memory and set the data members of a hashtable
//
//*************************************************************************************
Client_Address_Book::Client_Address_Book()
{
	cout << "In the Client_Address_Book--Default Constuctor Invoked" << endl;

	capacity = 26;

	hash_table = new Clients_Info_BST[capacity];

	string s;

	ifstream ifile;

	ifile.open("client_address_data.txt");

	while (!ifile.eof())
	{
		getline(ifile, s);

		if (s != "")
		{
			Insert(s);
		}
	}
	ifile.close();
}

//*************************************************************************************
//Name:  Client_Address_Book (Copy Constructor)
//Precondition: A hashtable
//Postcondition: A copy of a hashtable
//Description:  This will make a deep copy of a hashtable
//
//*************************************************************************************
Client_Address_Book::Client_Address_Book(const Client_Address_Book &)
{
	cout << "In Client_Address_Book-Copy Constuctor" << endl;

	cout << "Not implemented" << endl << endl;
}

//*************************************************************************************
//Name:  ~Client_Address_Book (Destructor)
//Precondition: A hashtable
//Postcondition: Deleted hashtable
//Description:  This will give the memory given to the hashtable back to the system
//
//*************************************************************************************
Client_Address_Book::~Client_Address_Book()
{
	cout << "In the Client_Address_Book--Destuctor " << endl;

	delete[] hash_table;
}

//*************************************************************************************
//Name:  Client_Address_Book::Insert
//Precondition: n elements in a hashtable
//Postcondition: n+1 elements in a hashtable 
//Description:  This function will search for which index to place an element and then insert it into that index
//
//*************************************************************************************
void Client_Address_Book::Insert(const string & s)
{
	cout << "In the Client_Adress_Book insert" << endl;

	int index = Hash_Function(s);

	hash_table[index].Insert(s);
}

//*************************************************************************************
//Name:  Client_Address_Book::Remove
//Precondition: n elements in a hashtable
//Postcondition: n-1 elements in a hashtable 
//Description:  This function will search for an element at a index and then delete it from the hash table
//
//*************************************************************************************
void Client_Address_Book::Remove(const string & s)
{
	cout << "In the Client_Address_Book--Remove" << endl;

	int index = Hash_Function(s);

	hash_table[index].Remove(s);

}

//*************************************************************************************
//Name:  Client_Address_Book::Update
//Precondition: Unchanged element
//Postcondition: Changed element 
//Description:  This function will search for an element at a index and then change its data members within a hashtable
//
//*************************************************************************************
void Client_Address_Book::Update(const string & s)
{
	cout << "In the Client_Address_Book--Update" << endl;

	string key = s;

	int command = 0;

	key[0] -= 48;
	key[0] = key[0] % 10;
	command = key[0];

	key.erase(0, 2);


	if (command == 1)
	{
		string first;
		string newFirst;
		string last;
		string newLast;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;
		int X = 0;
		int Y = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		X = key.find(" ", y);
		newLast = key.substr(y, (X - y));
		X++;
		Y = key.find(" ", X);
		newFirst = key.substr(X, (Y - X));
		z = key.length() - 8;
		addr = key.substr(Y, (z - Y));
		number = key.substr(z, 8);

		const string rName = last + " " + first;

		Remove(rName);

		key.erase(0, (rName.length() + 1));

		Insert(key);

	}
	else if (command == 2)
	{
		string first;
		string newFirst;
		string last;
		string newLast;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;
		int X = 0;
		int Y = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		X = key.find(" ", y);
		newLast = key.substr(y, (X - y));
		X++;
		Y = key.find(" ", X);
		newFirst = key.substr(X, (Y - X));
		z = key.length();
		addr = key.substr(Y, z);

		const string sName = last + " " + first;

		BST_Node * ptr = Search(sName);

		number = ptr->phone_number;
		const string nEntry = newLast + " " + newFirst + " " + addr + " " + number;

		Remove(sName);
		Insert(nEntry);
	}
	else if (command == 3)
	{
		string first;
		string last;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		z = key.length() - 8;
		addr = key.substr(y, (z - y));
		number = key.substr(z, 8);

		const string sName = last + " " + first;

		BST_Node * ptr = Search(sName);

		ptr->phone_number = number;
		ptr->address = addr;
	}
	else if (command == 4)
	{
		string first;
		string newFirst;
		string last;
		string newLast;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;
		int X = 0;
		int Y = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		X = key.find(" ", y);
		newLast = key.substr(y, (X - y));
		X++;
		Y = key.find(" ", X);
		newFirst = key.substr(X, (Y - X));
		Y++;
		number = key.substr(Y, key.length());

		const string sName = last + " " + first;

		BST_Node * ptr = Search(sName);

		addr = ptr->address;
		const string nEntry = newLast + " " + newFirst + " " + addr + " " + number;

		Remove(sName);
		Insert(nEntry);

	}
	else if (command == 5)
	{
		string first;
		string newFirst;
		string last;
		string newLast;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;
		int X = 0;
		int Y = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		X = key.find(" ", y);
		newLast = key.substr(y, (X - y));
		X++;
		Y = key.find(" ", X);
		newFirst = key.substr(X, (Y - X));

		const string sName = last + " " + first;

		BST_Node * ptr = Search(sName);

		number = ptr->phone_number;
		addr = ptr->address;
		const string nEntry = newLast + " " + newFirst + " " + addr + " " + number;

		Remove(sName);
		Insert(nEntry);
	}
	else if (command == 6)
	{
		string first;
		string last;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		z = key.length();
		addr = key.substr(y, z);

		const string sName = last + " " + first;

		BST_Node * ptr = Search(sName);

		ptr->address = addr;
	}
	else if (command == 7)
	{
		string first;
		string last;
		string number;
		string addr;
		int x = 0;
		int y = 0;
		int z = 0;

		x = key.find(" ", 0);
		last = key.substr(0, x);
		x++;
		y = key.find(" ", x);
		first = key.substr(x, (y - x));
		y++;
		z = key.length();
		number = key.substr(y, z);

		const string sName = last + " " + first;

		BST_Node * ptr = Search(sName);

		ptr->phone_number = number;
	}
	else
	{
		cout << "Unkwown Command!" << endl << endl;
	}
}

//*************************************************************************************
//Name:  Client_Address_Book::Print_BST
//Precondition: No precondition
//Postcondition: Print a single BST 
//Description:  This function will print a single BST at a certain index in the hashtable
//
//*************************************************************************************
void Client_Address_Book::Print_BST(const string & s)
{
	if (s == "A")
	{
		hash_table[0].Print();
	}
	else if (s == "B")
	{
		hash_table[1].Print();
	}
	else if (s == "C")
	{
		hash_table[2].Print();
	}
	else if (s == "D")
	{
		hash_table[3].Print();
	}
	else if (s == "E")
	{
		hash_table[4].Print();
	}
	else if (s == "F")
	{
		hash_table[5].Print();
	}
	else if (s == "G")
	{
		hash_table[6].Print();
	}
	else if (s == "H")
	{
		hash_table[7].Print();
	}
	else if (s == "I")
	{
		hash_table[8].Print();
	}
	else if (s == "J")
	{
		hash_table[9].Print();
	}
	else if (s == "K")
	{
		hash_table[10].Print();
	}
	else if (s == "L")
	{
		hash_table[11].Print();
	}
	else if (s == "M")
	{
		hash_table[12].Print();
	}
	else if (s == "N")
	{
		hash_table[13].Print();
	}
	else if (s == "O")
	{
		hash_table[14].Print();
	}
	else if (s == "P")
	{
		hash_table[15].Print();
	}
	else if (s == "Q")
	{
		hash_table[16].Print();
	}
	else if (s == "R")
	{
		hash_table[17].Print();
	}
	else if (s == "S")
	{
		hash_table[18].Print();
	}
	else if (s == "T")
	{
		hash_table[19].Print();
	}
	else if (s == "U")
	{
		hash_table[20].Print();
	}
	else if (s == "V")
	{
		hash_table[21].Print();
	}
	else if (s == "W")
	{
		hash_table[22].Print();
	}
	else if (s == "X")
	{
		hash_table[23].Print();
	}
	else if (s == "Y")
	{
		hash_table[24].Print();
	}
	else if (s == "Z")
	{
		hash_table[25].Print();
	}
	else
	{
		cout << s << endl << endl;
	}

}

//*************************************************************************************
//Name:  Client_Address_Book::Print_Hash_Table
//Precondition: No precondition
//Postcondition: Print the entirety of the hashtable
//Description:  This function will print all of the BST in the hashtable
//
//*************************************************************************************
void Client_Address_Book::Print_Hash_Table()
{
	cout << "In the Client_Address_Book--Print_Hash_Table" << endl;

	for (int i = 0; i < 26; i++)
	{
		hash_table[i].Print();
	}
}

//*************************************************************************************
//Name:  Client_Address_Book::Print_Hash_Table_to_File
//Precondition: No precondition
//Postcondition: File with clients sorted 
//Description:  This function will write the whole hashtable to a file
//
//*************************************************************************************
void Client_Address_Book::Print_Hash_Table_to_File(const string & filename)
{
	cout << "In the Client_Address_Book--Print_Hash_Table_to_File Invoked" << endl;

	ofstream wfile;
	wfile.open(filename);

	for (int i = 0; i < 26; i++)
	{
		wfile << hash_table[i].Write();
	}


	wfile.close();

}

//*************************************************************************************
//Name:  Client_Address_Book::Search
//Precondition: No precondition
//Postcondition: An index to search within
//Description:  This functon will find an index to start a search for a client
//
//*************************************************************************************
BST_Node * Client_Address_Book::Search(const string & s)
{
	cout << "In the Client_Address_Book--Search Invoked" << endl;

	int index = Hash_Function(s);

	BST_Node * ptr = hash_table[index].Search(s);

	if (ptr == 0)
	{

		return ptr;
	}
	else
	{
		return ptr;
	}
}

//*************************************************************************************
//Name:  Client_Address_Book::Hash_Function
//Precondition: No precondition
//Postcondition: An index
//Description:  This function will determine which index each letter will be assigned to
//
//*************************************************************************************
unsigned int Client_Address_Book::Hash_Function(const string & s)
{

	string temp = s;

	int val = 0;

	temp[0] -= 65;
	temp[0] = temp[0] % 26;

	val = temp[0];

	return val;
}