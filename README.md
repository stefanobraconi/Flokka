# Flokka
Flokka, a simple text analyzer / parser written in C++
by Stefano Braconi, 2021 calico.vae@gmail.com

Why?
I wanted to create this simple library in order to have a token recognition system with the possibility of relating them to each other.

The source...
All the classes are inserted in the "flokka" namespace to effectively separate the use of the library with any third party programs that will make it their own. 

In facts...
an arbitrarily long string which can also be an entire text file is split into n user-defined tokens. 
There are some definitions of tokens used by the analyzer that cannot be redefined, these are: 

Typology SYS    :: system type tokens
token EOL;	    :: when the analyzer found a end of line in textfile 
token ATOM      :: atomic element, also call "anything is no number or user registered token..."
token TAB	      :: for retrieving horizontal tab

token INT	      :: token retrieved is a integer 
token FLOAT     :: token retrieved is a float
note fot INT & FLOAT, the analyzed value will not be converted in true int or float, but a functions are defined for simplify the job for you

token STRING    :: this is a plain string contained in a container (ex "...")

Use:

you need to declare a database of user defined type of tokens:
flokka::dbtoken tokens;

and you need the parsed elements analyzed:
vector <flokka::parse_element> parsed;

definition of tokens "types", example:
  tokens.add_type("keywords");
  tokens.add_type("identifiers");
  tokens.add_type("symbols");
  tokens.add_type("operators");
  tokens.add_type("separator");

definition of real tokens, example:
  tokens.add_token("if","keywords",1,+1, false);
  tokens.add_token("endif","keywords",1,-1, false);
  tokens.add_token("cycle","keywords",2,1, false);
  tokens.add_token("endcycle","keywords",2,-1, false);
  tokens.add_token("main","keywords",3,1, false);
  tokens.add_token("endmain","keywords",3,-1, false);
  tokens.add_token("print","keywords",4,0, false);
  tokens.add_token("\u0022","separator",5,0, true); // "
  tokens.add_token("<","operators",10,0, false);
  tokens.add_token("==","operators",11,0, false);
  tokens.add_token("=","operators",20,0, false);
  tokens.add_token("+","operators",30,0, false);
  tokens.add_token("(","symbols",40,1, false);
  tokens.add_token(")","symbols",40,-1, false);
  
 add_token(primary key, type, relation code, relation shift, container)
 
 primary key: the unique value that the analyzer will look for in the text 
 type: the user type
 relation code: this is a user defined code to relate tokens with other tokens..
 
 



object typology
  
class token 
class dbtoken
class parse_element
class cstatus
  
  void flokka_start(string data, dbtoken token_list,vector <parse_element> &element, char decimal_divisor);
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

