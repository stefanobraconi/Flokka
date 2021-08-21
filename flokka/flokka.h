// FLOKKA HEADER

#ifndef __FLOKKA_H_INCLUDED__
#define __FLOKKA_H_INCLUDED__

#include <vector>
#include <algorithm>
#include <fstream>

//#include <iostream> //sort

#define MAXSTRINGVALUE 500
#define NO_CONTROL_CODE 0	// for xstrwtok function.
#define YES_CONTROL_CODE 1	// ^^^

using namespace std;

namespace flokka {
	// This class is for declare category, example: keyword, identifier, constant, string, special, op, null.....
	class typology {
		private:
			vector<string> data; // Must no duplicate element!
		public:
			// typology(string value);
			void add(string _value); // Added with control of duplicates
			int get_index(string _value); // if exist return index, also return -1
			// bool remove(int position);
			// bool remove(string _value); // search & destroy, if don't exist return false
			string get(int position);
	};

	class token {
		private:
			string value;		// primary key
			string type;		// typology...
			int relation_code;	// this code is for relativize token with other tokens..
			int relation_shift;	// Value changer in relation with other tokens
			bool iscontainer;	// is a container? Example " build a string.. "bla bla bla"
		public:
			token();
			token(typology dbt, string _type, string _value, int _relationcode, int _relationshift, bool _iscontainer);
			string get_type();
			int get_relation_code(); // can you declare a relation with another token example: IF relationcode 345   THEN relationcode 345    IF relationshift +1    THEN relationshift -1
			int get_relation_shift();
			string get();
			bool is_container();
			bool operator==(const token &op);
			token& operator=(const token& other);
	};

	class dbtoken {
		private:
			typology db_type;
			vector <token> db_token;
		public:
			dbtoken();
			void add_type(string _value);
			void add_token( string _value, string _type, int _relationcode, int _relationshift, bool _iscontainer);
			int search_token(string _value);
			string get_token_value(int position);
			string get_token_type(int position);
			int get_token_relation_code(int position);
			int get_token_relation_shift(int position);
			bool get_token_is_container(int position);
			token get_token(int position);
			void sort(); // selection sort, this is extremely necessary!! I explain this in readme...
			int dim();
	};

	class parse_element {
		private:
			string value;
			token tok;
			token search_token(dbtoken &token_list);
			int status; //tokencode status shift
			int deep;
		public:
			parse_element();
			string get_value();
			void set_token(string _value, dbtoken token_list);
			string get_token_value();
			int get_token_relation_code();
			int get_token_relation_shift();
			bool get_token_is_container();
			string get_token_type();
			void set_status(int _relation_shift);
			int get_status();
			void set_value(string _value,dbtoken &token_list);
			parse_element& operator=(const parse_element& other);
			int get_deep();
			void set_deep(int shift);
	};

	class flokka_analyzer{
		private:
			char decimal_divisor;
		public:
		    vector <parse_element> parsed;
			flokka_analyzer();
			void start(string data, dbtoken token_list);
			int delete_tokens(string tok);
			void set_decimal_divisor(char _divisor);
	};

	void flokka_start(string data, dbtoken token_list,vector <parse_element> &element, char decimal_divisor);

	class cstatus {
		private:
			struct list {
				int relation_code;
				int status;
			};
			vector <list> db_code;
		public:
			void change(int _relation_code, int value);
			int get_status(int _relation_code);
	};
}

// int getindex(vector<auto> data, auto value);
// int veclen(vector<auto> data);
void string_to_array(char text[],string str);
void strdelch(char *str, char value);
bool strwchk(char *word, char *str, int position);
int xstrwtok_check(char *target, int idx_target, char controlsymbol[][MAXSTRINGVALUE], int nsymbol, char *ret_control);
int xstrwtok(char *codeline, char controlsymbol[][MAXSTRINGVALUE], int nsymbol, char parsed[][MAXSTRINGVALUE]);
void load(string namefile, string &data);
int whois(string subject, char separator); // 0: string 1: integer  2: float
extern "C" int str_to_int(char *value);
extern "C" int ex(int number, int exp);
extern "C" float str_to_float(char *value, char div);

#endif // __XSTRING_H_INCLUDED__