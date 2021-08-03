# Flokka
### a simple text analyzer / parser written in C++
#### by Stefano Braconi, 2021 calico.vae@gmail.com
<p>I wanted to create this simple library in order to have a token recognition system with the possibility of relating them to each other.</p>
<p>All the classes are inserted in the "flokka" namespace to effectively separate the use of the library with any third party programs that will make it their own.</p>
<p>The analyzer process an arbitrarily long string which can also be an entire text file is split into n user-defined tokens. </p>
<hr>

Namespace:</br>
<code>flokka::dbtoken <user defined tokens database></code>
  
### <p>API reference</p>
#### **<code>dbtoken::add_type( "univoque new type" string)</code>**
example:<br/>
<code>flokka::dbtoken t;</code> database declaration<br/>
<code>t.add_type("keywords");</code> adding types...<br/>
<code>t.add_type("identifiers");</code><br />
<code>t.add_type("symbols");</code><br />
<code>t.add_type("operators");</code><br />
<hr>
	
	
  
dbtoken.add_token( <univoque token name> string, <name of type defined with "add_type()"> string
  
 
  
