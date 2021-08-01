# Flokka
Flokka, a simple text analyzer / parser written in C++
by Stefano Braconi, 2021 calico.vae@gmail.com

Why?
I wanted to create this simple library in order to have a token recognition system with the possibility of relating them to each other.

The source...
All the classes are inserted in the "flokka" namespace to effectively separate the use of the library with any third party programs that will make it their own. 

In facts...
an arbitrarily long string which can also be an entire text file is split into n user-defined tokens. 

