#include "lm.helloworld.pb.h"
#include <fstream>
#include <iostream>

using namespace std;

void ListMsg(const lm::helloworld & msg)
{
	cout << msg.id() << endl;
	cout << msg.str() << endl;
}

int writer()
{
	lm::helloworld msg1;
	msg1.set_id(101);
	msg1.set_str("hello");

	// Write the new address book back to disk. 
	fstream output("./log.txt", ios::out | ios::trunc | ios::binary);

	if (!msg1.SerializeToOstream(&output)) {
		cout << "Failed to write msg." << endl;
		return -1;
	}

	return 0;
}

int reader()
{
	lm::helloworld msg1;
	fstream input("./log.txt", ios::in | ios::binary);
	if (!msg1.ParseFromIstream(&input)) {
		cerr << "Failed to parse address book." << endl;
		return -1;
	}
	ListMsg(msg1);
	
	return 0;
}

int main(void)
{
	writer();
	reader();
}