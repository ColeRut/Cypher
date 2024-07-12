------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -Wall -Werror -Wpedantic -std=c++17 cypher.cpp
Run: ./a.out
------------------------
DEPENDENCIES
------------------------
cypher.cpp must be in be directory in order to compile.
------------------------
SUBMISSION INFORMATION
------------------------
Author: Cole Rutkowski
------------------------
ABOUT THIS PROJECT
------------------------
This project presents multi-layered encryption and decryption 
program. There are 3 layers of encryption, the last of which
is only available when doing a chain encyrption. The first
layer has two options: a ROT13 cypher or a Caesar cypher
determined by the two keywords input into the program. 
The second layer involves a Caesar cypher with varying
rotation values that depends on the key phrase entered.
The chain encyrption first encrypts a message with the 
layer 1 encryption technique, then encrypts this intermediate
phrase with the layer 2 encryption technique. Afterwards,
the layer 3 technique is applied, which substitutes specifiic
alpha characters for numeric and special characters for a 
fully encrypted message.