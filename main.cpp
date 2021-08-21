// FLOKKA DRIVER

#include <iostream>
#include <iomanip>
#include "flokka\flokka.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	flokka::dbtoken t; // declare a tokens database
	flokka::parse_element temp;
	vector <flokka::parse_element> parsed;
	try {
		t.add_type("keywords");
		t.add_type("identifiers");
		t.add_type("symbols");
		t.add_type("operators");
		t.add_type("separator");
		/*
		 add_token(value,type,code,shift,iscontainer)
		 <code> MUST BE > 0!!! negative code are reserved!
		 */

		t.add_token("if","keywords",1,+1, false);
		t.add_token("endif","keywords",1,-1, false);

		t.add_token("cycle","keywords",2,1, false);
		t.add_token("endcycle","keywords",2,-1, false);

		t.add_token("main","keywords",3,1, false);
		t.add_token("endmain","keywords",3,-1, false);

		t.add_token("print","keywords",4,0, false);

		t.add_token("\u0022","separator",5,0, true); // "

		t.add_token("<","operators",10,0, false);
		t.add_token("==","operators",11,0, false);
		t.add_token("=","operators",20,0, false);

		t.add_token("+","operators",30,0, false);


		t.add_token("(","symbols",40,1, false);
		t.add_token(")","symbols",40,-1, false);
		//t.sort();

		string program;
		load("test.txt", program);
		flokka::flokka_analyzer fk;
		fk.start(program,t);
        fk.delete_tokens("\u0022");
		//flokka::flokka_start(program,t, parsed,'.');
		for (int i=0; i<fk.parsed.size(); i++) {
		cout<<left<<setw(6)<<fk.parsed[i].get_deep()<<setw(20)<<fk.parsed[i].get_value()<<setw(20)<<fk.parsed[i].get_token_value()<<setw(20)<<fk.parsed[i].get_token_type()<<setw(12)<<fk.parsed[i].get_token_relation_code()<<setw(12)<<fk.parsed[i].get_token_relation_shift()<<setw(12)<<fk.parsed[i].get_status()<<setw(12)<<fk.parsed[i].get_token_is_container()<<endl;
		}
		
		/*
				//whois test
				string test="0.3";
				int n=whois(test, '.');
				cout<<endl<<test<<" is a ";
				switch (n) {
					case 0:
						cout<<"string"<<endl;
						break;
					case 1:
						cout<<"integer"<<endl;
						break;
					case 2:
						cout<<"float"<<endl;
						break;
				}
		*/
	} catch (runtime_error &e) {
		cerr << e.what() << endl;
		return -1;
	}
	return 0;
}