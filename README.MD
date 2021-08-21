# Flokka
### a simple text analyzer / parser written in C++
#### by Stefano Braconi, 2021 calico.vae@gmail.com
wanted to create this simple library in order to have a token recognition system with the possibility of relating them to each other.
All the classes are inserted in the "flokka" namespace to effectively separate the use of the library with any third party programs that will make it their own.
The analyzer process an arbitrarily long string which can also be an entire text file is split into n user-defined tokens. 


Namespace:
```
flokka
```

#### API reference
```
dbtoken::add_type(type)
```

Add a new typology.
**type** (string) is the name of typology

example:

```c++
flokka::dbtoken t; // database declaration
t.add_type("keywords"); //adding types...
t.add_type("identifiers");
t.add_type("symbols");
t.add_type("operators");
```

---
```c++
dbtoken::add_token(name, type, relation code, relation shift, is container?)
```

Add a new token.
**name** (string) is the name of tokens.
**type** (string) is the typology/category associates.
**relation code** (number) is a numerical code who link the token with another tokens who have same code.
relation shift (number) i

example:

```c++
t.add_token("if","keywords",1,+1, false);
t.add_token("endif","keywords",1,-1, false);
t.add_token("print","keywords",4,0, false);
t.add_token("\u0022","separator",5,0, true); // "
```

about relation code... 
this parameter is used to relate two tokens and to create a hierarchy:

"if" tokens shift +1 and "endif" with same relation code, shift -1

---

```c++
flokka_analyzer::start(code, database of tokens)
```

Start parser.
**code** (string) is the text-based source to be analyzed
**database of tokens** (dbtoken) the tokens previously declared

---

```c++
flokka_analyzer::delete_tokens(name of token)
```

This function delete all tokens "name of token" from analyzed content.

example:

```c++
string program;
load("test.txt", program); 	// load textual file in 'program'
flokka::flokka_analyzer fk; // declare the analyzer
fk.start(program,t);		// start analyzer
fk.delete_tokens("\u0022");	// delete ALL tokens with the value " (quotes)
```

---

The analyzed text is contained in a vector named "parsed", you can interact with it through these functions:

```c++
flokka_analyzer::parsed[]::get_deep()
```

Return a number identify the status of token in relation of all parsed tokens.
This function works in relation to the number of relation shift but is globally and does not depend on the relation code 

---

```c++
flokka_analyzer::parsed[]::get_value()
```

Return the value of token (parsed string)

---

```c++
flokka_analyzer::parsed[]::get_token_value()
```

Return the token code

---

```c++
flokka_analyzer::parsed[]::get_token_type()
```

Return the typology of token

---

```c++
flokka_analyzer::parsed[]::get_token_relation_code()
```

Return the relation code of token

---

```c++
flokka_analyzer::parsed[]::get_token_relation_shift()
```

Returns the number of steps to change the relationship state with other tokens 

---

```c++
flokka_analyzer::parsed[]::get_status()
```

Returns the current state in relation to the other tokens with the same relation code 

---

```c++
flokka_analyzer::parsed[]::get_token_is_container()
```

Returns a true / false value indicating whether the token is a container, for example the quotes of a string 

---

```c++
flokka_analyzer::parsed[]::set_decimal_divisor(divisor)
```

Set the decimal divisor, example , for Italy . for USA

---

```c++
load(namefile, &stringdata)
```

Load "namefile" in stringdata.

