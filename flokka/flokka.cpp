// FLOKKA SOURCE

#include "flokka.h"

//using namespace std;  ONLY in H

/*
// Function to print the
// index of an element
int getindex(vector<auto> data, auto value) {
	auto it = find(data.begin(), data.end(), value);
	// If element was found
	if (it != data.end()) {
		// calculating the index
		// of K
		int index = it - data.begin();
		return index;
	} else {
		// If the element is not
		// present in the vector
		return -1;
	}
}

int veclen(vector<auto> data) {
	auto it=data.end()-data.begin();
	return it;
}
*/

// CSTATUS CLASS CODE

void flokka::cstatus::change(int _relation_code, int _value) {
	list tmp;
	//deep+=vvalue;
	if (db_code.size()==0) {
		tmp.relation_code=_relation_code;
		tmp.status=_value;
		db_code.push_back(tmp);
	} else {

		for (int i=0; i<db_code.size(); i++) {
			if (db_code[i].relation_code==_relation_code) {
				db_code[i].status+=_value;
				return;
			}


		}
		tmp.relation_code=_relation_code;
		tmp.status=_value;
		db_code.push_back(tmp);
	}
}


int flokka::cstatus::get_status(int _relation_code) {
	for (int i=0; i<db_code.size(); i++) {
		if (db_code[i].relation_code==_relation_code) return db_code[i].status;
	}
	return -1;
}

/*
int flokka::cstatus::getdeep()
{
 return deep;
}*/

// TYPOLOGY CLASS SOURCE

void flokka::typology::add(string _value) {
	vector<string>::iterator value;  // or bestu use auto declaration
	value=find(data.begin(), data.end(), _value);
	if(value != data.end()) {  //std::find
		// if elem exists in the vector
		// cerr<<"flokka::typology::add() = Element already exists : "<<getindex(data,entry)<<" - "<<*value<<endl;
		// cout<<"flokka::typology::add() = Element already exists : "<<value-data.begin()<<" - "<<*value<<endl;  // SAME AS TOP!
		string errmsg="flokka::typology::add() = Element already exists : "+to_string(value-data.begin())+" - "+*value;
		throw runtime_error(errmsg);
		//return false;
	} else {
		data.push_back(_value);
		//return true;
	}
}

int flokka::typology::get_index(string _value) {
	// std::vector<string>::iterator it = find(data.begin(), data.end(), value); // same as bottom but auto is best
	auto it = find(data.begin(), data.end(), _value); // best use auto!
	if (it != data.end()) {
		int index = it - data.begin();
		return index;
	} else {
		return -1;
	}
}

/*
bool flokka::typology::remove(int position) {
	if (data.begin()+position < data.end()) {
		data.erase (data.begin()+position);
		return true;
	} else return false;
}
*/

string flokka::typology::get(int position) {
	if (data.begin()+position < data.end()) {
		return data[position];
	} else throw runtime_error("flokka::typology::get() = Position over limit");
}

// TOKEN CLASS SOURCE
flokka::token::token() {

}

flokka::token::token(typology dbt, string _type, string _value, int _relationcode, int _relationshift, bool _iscontainer) {
	int pos=dbt.get_index(_type);
	if (pos==-1) {
		string msg="flokka::token::token() = <"+_type+"> Typology don't exist";
		throw runtime_error(msg);
	}
	/*
	if (_relationcode<0){
		string msg="flokka::token::token() = code: <"+_relationcode+"> not allowed! Must > 0";
		throw runtime_error(msg);

	}*/
	type=_type;
	value=_value;
	relation_code=_relationcode;
	relation_shift=_relationshift;
	iscontainer=_iscontainer;
}

string flokka::token::get_type() {
	return type;
}

int flokka::token::get_relation_code() {
	return relation_code;
}

int flokka::token::get_relation_shift() {
	return relation_shift;
}

string flokka::token::get() {
	return value;
}
bool flokka::token::is_container() {
	return iscontainer;
}

bool flokka::token::operator==(const token &op) {
	if (type==op.type && value==op.value && relation_code==op.relation_code && relation_shift==op.relation_shift ) return true;
	else return false;
}

flokka::token &flokka::token::operator=(const token& other) {
	// Guard self assignment
	if (this == &other)   return *this;
	type=other.type;
	value=other.value;
	relation_code=other.relation_code;
	relation_shift=other.relation_shift;
	iscontainer=other.iscontainer;
	return *this;
}

// DBTOKEN CLASS SOURCE

flokka::dbtoken::dbtoken() {
	// SET SYSTEM TYPE & TOKENS
	add_type("SYS");
	add_token("EOL","SYS",-1,0,0);	// for set end of line
	add_token("ATOM","SYS",-2,0,0);	// atomic element, also call "anything is non a number or user registered token..."!!!
	add_token("TAB","SYS",-3,0,0);	// for set horizontal tab
	add_token("INT","SYS",-4,0,0);	// for set if this element is a INT (note: value remain a string! The user can convert the value.
	add_token("FLOAT","SYS",-5,0,0);	// ^^^^^ FLOAT
	add_token("STRING","SYS",-6,0,0);// this i a plain string contained in a container (ex "...")
}

void flokka::dbtoken::add_type(string _value) {
	db_type.add(_value);
}

void flokka::dbtoken::sort() {
	token swap;
	string test;
	string org;
	for (int i=0; i<db_token.size(); i++) {
		for (int j=i; j<db_token.size(); j++) {
			test=db_token[j].get();
			org=db_token[i].get();
			if (test.length()>org.length()) {
				swap=db_token[j];
				db_token[j]=db_token[i];
				db_token[i]=swap;
			}
		}
	}
}

void flokka::dbtoken::add_token( string _value, string _type, int _relationcode, int _relationshift, bool _iscontainer) {
	int size=db_token.size();
	for (int i=0; i<size; i++) {
		if (_value==db_token[i].get()) {
			string msg="flokka::dbtoken::addtoken() = <"+_value+"> Already exist";
			throw runtime_error(msg);
		}
	}
	db_token.push_back(token(db_type,_type,_value,_relationcode,_relationshift, _iscontainer));
	sort();
}

int flokka::dbtoken::search_token(string _value) {
	int size=db_token.size();
	for (int i=0; i<size; i++)
		if (_value==db_token[i].get()) return i;
	return -1;
}

string flokka::dbtoken::get_token_value(int position) {
	if (position>db_token.size()) {
		string msg="flokka::dbtoken::gettoken_value() = <"+to_string(position)+"> don't exist";
		throw runtime_error(msg);
	}
	return db_token[position].get();
}

string flokka::dbtoken::get_token_type(int position) {
	if (position>db_token.size()) {
		string msg="flokka::dbtoken::gettoken_value() = <"+to_string(position)+"> don't exist";
		throw runtime_error(msg);
	}
	return db_token[position].get_type();
}

int flokka::dbtoken::get_token_relation_code(int position) {
	if (position>db_token.size()) {
		string msg="flokka::dbtoken::gettoken_value() = <"+to_string(position)+"> don't exist";
		throw runtime_error(msg);
	}
	return db_token[position].get_relation_code();
}

int flokka::dbtoken::get_token_relation_shift(int position) {
	if (position>db_token.size()) {
		string msg="flokka::dbtoken::gettoken_value() = <"+to_string(position)+"> don't exist";
		throw runtime_error(msg);
	}
	return db_token[position].get_relation_shift();
}

bool flokka::dbtoken::get_token_is_container(int position) {
	if (position>db_token.size()) {
		string msg="flokka::dbtoken::gettoken_value() = <"+to_string(position)+"> don't exist";
		throw runtime_error(msg);
	}
	return db_token[position].is_container();
}

flokka::token flokka::dbtoken::get_token(int position) {
	if (position>db_token.size()) {
		string msg="flokka::dbtoken::gettoken_value() = <"+to_string(position)+"> don't exist";
		throw runtime_error(msg);
	}
	return db_token[position];
}

int flokka::dbtoken::dim() {
	return db_token.size();
}

// PARSE_ELEMENT SOURCE

flokka::parse_element::parse_element() {
	value="none";
	typology fake_tab;
	fake_tab.add("SYS");
	token fake_tok(fake_tab,"SYS","ATOM",-2,0, false);
	//addtoken("TXT","sys",-2,0,0);
	tok=fake_tok;
	status=0;
	deep=0;
}

flokka::token flokka::parse_element::search_token(dbtoken &list) {
	typology fake_tab;
	fake_tab.add("SYS");
	//token fake_tok(fake_tab,"text","text",0,0, false);
	token fake_tok(fake_tab,"SYS","ATOM",-2,0, false);
	int n=list.search_token(value);
	if (n==-1) {
		return fake_tok;
	} else {
		return list.get_token(n);
	}
}

string flokka::parse_element::get_value() {
	return value;
}

void flokka::parse_element::set_token(string _value, dbtoken token_list) {
	//	<buffer.tok=t.gettoken(t.searchtoken("FLATSTRING"));
	tok=token_list.get_token(token_list.search_token(_value));
}

void flokka::parse_element::set_value(string _value,dbtoken &list) {
	value=_value;
	tok=search_token(list);
	status=0;
	deep+=tok.get_relation_shift();
}

string flokka::parse_element::get_token_value() {
	return tok.get();
}

flokka::parse_element &flokka::parse_element::operator=(const parse_element& other) {
	// Guard self assignment
	if (this == &other)   return *this;
	tok=other.tok;
	value=other.value;
	status=other.status;
	deep=other.deep;
	return *this;
}

int flokka::parse_element::get_token_relation_code() {
	return tok.get_relation_code();
}
int flokka::parse_element::get_token_relation_shift() {
	return tok.get_relation_shift();
}
bool flokka::parse_element::get_token_is_container() {
	return tok.is_container();
}

string flokka::parse_element::get_token_type() {
	return tok.get_type();
}

void flokka::parse_element::set_status(int relation_shift) {
	status+=relation_shift;
}

int flokka::parse_element::get_status() {
	return status;
}

int flokka::parse_element::get_deep() {
	return deep;
}

void  flokka::parse_element::set_deep(int shift) {
	deep=shift;
}

// FLOKKA_ANALYZER SOURCE

flokka::flokka_analyzer::flokka_analyzer(){
	decimal_divisor='.';
}	

int flokka::flokka_analyzer::delete_tokens(string tok){
    bool flag=false;
    if (parsed.size()==0) return flag;
	for (int i=0; i<parsed.size(); i++){
		if (parsed[i].get_token_value()==tok){
			parsed.erase(parsed.begin()+i);
			i=0;
			flag=true;
		}
	}
	return flag;

}

void flokka::flokka_analyzer::set_decimal_divisor(char _divisor){
	decimal_divisor=_divisor;
}

void flokka::flokka_analyzer::start(string data, dbtoken token_list){
	flokka_start(data, token_list,parsed, decimal_divisor);
}





void string_to_array(char text[],string str) {
	int dim=str.length();
	int idx;
	for (idx=0; idx<dim; idx++) text[idx]=str[idx];
	text[idx]='\0';
}

// from xstring.h

void strdelch(char *str, char value) {
	int idxsource=0;
	int idxdest = 0;
	char strdest[strlen(str)+1];
	while (str[idxsource] != '\0') {
		if (str[idxsource]!=value) {
			strdest[idxdest]=str[idxsource];
			idxdest++;
		}
		idxsource++;
	}
	strdest[idxdest] = '\0';
	strcpy(str, strdest);
}

bool strwchk(char *word, char *str, int position) {
	int len = strlen(str);
	if (len - strlen(word) < strlen(word))
		return false;
	if (position > len)
		return false;
	int idxcomp = 0;
	for (int idx = position; idx < position + strlen(word); idx++) {
		if (word[idxcomp] != str[idx])
			return false;
		idxcomp++;
	}
	return true;
}

int xstrwtok_check(char *target, int idx_target, char controlsymbol[][MAXSTRINGVALUE], int nsymbol, char *ret_control) {
	for (int i=0; i<nsymbol; i++) {
		if(strwchk(controlsymbol[i], target, idx_target)==true) {
			strcpy(ret_control,controlsymbol[i]);   // return controlcode found in *ret_control
			return strlen(ret_control);				// ... and the length of *ret_control
		}
	}
	ret_control[0]='\0';
	return 0;
}

int xstrwtok(char *codeline, char controlsymbol[][MAXSTRINGVALUE], int nsymbol, char parsed[][MAXSTRINGVALUE]) {
	// Insert escape commands....
	int syselement=2;
	strcpy(controlsymbol[nsymbol],"\n"); // LINE FEED
	strcpy(controlsymbol[nsymbol+1],"\t"); // TAB
	int idx_cl=0; // codeline source index
	int idx_parse=0;
	int idx_v=0;
	int flag=0; // control word found!
	char control_code[MAXSTRINGVALUE]; // control word found is here
	int laststatus=NO_CONTROL_CODE; // set last state in "the last cycle have not found a controlcode
	while (codeline[idx_cl]!='\0') {
		flag=xstrwtok_check(codeline,idx_cl,controlsymbol,nsymbol+syselement,control_code);
		if (flag==0) { // no control relationcode found the copy the character
			parsed[idx_parse][idx_v]=codeline[idx_cl];
			idx_cl++;
			idx_v++;
			laststatus=NO_CONTROL_CODE; // setting last status
		} else { // control relationcode found
			if (idx_parse>0 && laststatus==NO_CONTROL_CODE) { // if last cycle is not a controlcode terminate last string.
				parsed[idx_parse][idx_v]='\0';
				idx_parse++; // ... go in another new split element.
			}
			strcpy(parsed[idx_parse],control_code);
			idx_cl+=strlen(control_code); // or idx_cl+=flag;
			idx_v=0;
			laststatus=YES_CONTROL_CODE;
			idx_parse++;
		}
	}
	return idx_parse+1;
}

// file management

void load(string namefile, string &data) {
	fstream input;
	input.open(namefile,ios::in);
	if (!input) throw runtime_error("fstream: file error");
	char rd;
	while (!input.eof()) {
		//input>>rd; // don't read escape sequence!
		input.get(rd); // read escape sequence
		data+=rd;
	}
	input.close();
}

int whois(string subject, char separator) {
	bool sepfound=false;
	bool allnumberfound=true;
	for (int i=0; i<subject.length() && allnumberfound==true ; i++) {
		if (subject[i]>=48 && subject[i]<=57 || subject[i]==separator) allnumberfound=true;
		else allnumberfound=false;
	}
	for (int i=0; i<subject.length() && sepfound==false ; i++) {
		if (subject[i]==separator) sepfound=true;
	}
	if (subject[0]==separator || subject[subject.length()-1]==separator) {
		sepfound=false;
		allnumberfound=false;
	}
	if  (sepfound==true && allnumberfound==true) return 2;
	if  (sepfound==false && allnumberfound==true) return 1;
	return 0;
}

extern "C" int str_to_int(char *value) {
	int sum=0;
	int exp=1;
	int idx=strlen(value)-1;
	for (; idx>=0; idx--) {
		sum+=(value[idx]-'0')*exp;
		exp*=10;
	}
	return sum;
}

extern "C" int ex(int number, int exp) {
	int result=number;
	for (int i=0; i<exp; i++) {
		result*=number;
	}
	return result;
}

extern "C" float str_to_float(char *value, char div) {
	float res;
	char real[40];
	char decimal[40];
	float realf;
	float decf;
	int id=0;
	int iv;
	for (iv=0; iv<strlen(value) && value[iv]!=div; iv++) {

		if (value[iv]!=div) {
			real[id]=value[iv];
			id++;
		} else 	real[id]='\0';
	}
	iv++;
	id=0;
	for(; iv<strlen(value); iv++) {

		decimal[id]=value[iv];
		id++;
	}
	decimal[id]='\0';
	realf=(int)str_to_int(real);
	decf=(int)str_to_int(decimal);
	decf=decf/(1*ex(10,strlen(decimal)-1));
	res=realf+decf;
	//std::cout<<real<<" , "<<decimal<<std::endl<<std::endl<<res<<std::endl;
	return res;
}

void flokka::flokka_start(string data, dbtoken t,vector <parse_element> &element, char decimaldivisor) {
	flokka::parse_element temp;
	flokka::cstatus stat; // status traceback
	char code_c[MAXSTRINGVALUE];
	string_to_array(code_c,data);
	char token[30][MAXSTRINGVALUE];
	char parsed[100][MAXSTRINGVALUE];
	int n=t.dim();

	for (int i=0; i<t.dim(); i++)  {
		string_to_array(token[i],t.get_token_value(i));
	}

	//cout<<endl<<endl<<"------------- 1st passage -------------"<<endl<<endl;

	vector <flokka::parse_element> p;

	int ntok=xstrwtok(code_c, token, n, parsed);

	for (int i=0; i<ntok; i++) {
		temp.set_value(parsed[i],t);
		p.push_back(temp);
	}

	// 2nd passage in P for retriveving containers (ex:strings)
	// cout<<endl<<endl<<"------------- 2nd passage -------------"<<endl<<endl;
	vector <flokka::parse_element> p2;
	string temporary;
	flokka::parse_element buffer;
	bool flagcontainer=false;
	int codecontainer;
	for (int i=0; i<p.size(); i++) {
		if (flagcontainer==false) {
			if (p[i].get_token_is_container()==true) {
				flagcontainer=true;
				p2.push_back(p[i]);
			} else {
				string delblk=p[i].get_value();
				delblk.erase(remove(delblk.begin(), delblk.end(), ' '), delblk.end());  // if not a string in container, delete all blank.
				parse_element eol;
				switch(delblk[0]) {
					case 9: // escape \t
						eol.set_value("TAB",t);
						p2.push_back(eol);
						break;
					case 10: // escape \n
						eol.set_value("EOL",t);
						p2.push_back(eol);
						break;
					default:
						p[i].set_value(delblk,t);
						//int pos=t.searchtoken("FLATSTRING");
						//p[i].tok=t.gettoken(pos);
						p2.push_back(p[i]);
				}
			}
		} else {
			int ctrl;
			if (p[i].get_token_is_container()==true && p[i+1].get_token_is_container()==false) ctrl=1;
			if (p[i].get_token_is_container()==true && p[i+1].get_token_is_container()==true) ctrl=2; // repeating character, also in string...
			if (p[i].get_token_is_container()==false) ctrl=3;
			switch (ctrl) {
				case 1:
					flagcontainer=false;
					buffer.set_value(temporary,t);
					buffer.set_token("STRING",t); // RESERVED FOR CONTAINER TOKEN
					p2.push_back(buffer);
					p2.push_back(p[i]);
					temporary="";
					break;
				case 2:
					temporary+=p[i].get_value();
					i++;
					break;
				case 3:
					string delblk=p[i].get_value();
					//if (p[i].gettoken_type()!="text")	delblk.erase(remove(delblk.begin(), delblk.end(), ' '), delblk.end());  // toglieamo tutti gli spazi se non ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¨ una stringa
					temporary+=delblk;
					break;
			}
		}
	}
	//	cout<<endl<<endl<<"------------- 3rd passage -------------"<<endl<<endl;

	vector <flokka::parse_element> p3;
	for (int i=0; i<p2.size(); i++) {
		temporary=p2[i].get_value();
		temporary.erase(remove(temporary.begin(), temporary.end(), ' '), temporary.end());
		if (temporary.length()>0) p3.push_back(p2[i]);
	}
	for (int i=0; i<p3.size(); i++) {
		element.push_back(p3[i]);
	}
	// Deep calculator
	int actualdeep=0;

	for (int i=0; i<element.size(); i++) {
		// stat
		stat.change(element[i].get_token_relation_code(),element[i].get_token_relation_shift());
		if (stat.get_status(element[i].get_token_relation_code())!=-1)	element[i].set_status(stat.get_status(element[i].get_token_relation_code()));
		actualdeep+=element[i].get_token_relation_shift();
		element[i].set_deep(actualdeep);
		// discretize ATOM elements in atom/int/float, example: atom can be a function or variable...
		if (element[i].get_token_value()=="ATOM") {
			int def=whois(element[i].get_value(),decimaldivisor);
			switch (def) {
				case 0:
					element[i].set_token("ATOM", t);
					break;
				case 1:
					element[i].set_token("INT", t);
					break;
				case 2:
					element[i].set_token("FLOAT", t);
					break;
			}
		}
	}

}