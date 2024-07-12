#include <iostream>
#include <string>

using namespace std;


char shiftChar(char letter, int shift_value)
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //check that letter is valid, upper or lower
    //65-90, 97-122
    if ((letter < 65 || letter > 90) && (letter < 97 || letter > 122))
    {
        return letter;
    }

   
   else
   {
        //if greater than 25, subtract 26 until it's between 0 and 25
        //if less than -25, add 26 until it's between -25 and 0
        while (shift_value > 25)
        {
            shift_value -= 26;
        }

        while (shift_value < -25)
        {
            shift_value += 26;
        }
    


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //integers for how far from boundary, use to go from a to z or z to a when wrapping around alphabet
    int upper_bound_distance;
    int lower_bound_distance;
    
    //if capital, set boundaries
    if (letter >= 65 && letter <= 90)
    {
        upper_bound_distance = 90 - letter;
        lower_bound_distance = letter - 65;
    }

    //if lower case, set boundaries
    if (letter >= 97 && letter <= 122)
    {
        upper_bound_distance = 122 - letter;
        lower_bound_distance = letter - 97;
    }



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //wrap around function
    
    //positive shift
    if (shift_value > 0 && (upper_bound_distance - shift_value < 0))
    {
        shift_value = shift_value - 26;
    }

    //negative shift
    if (shift_value < 0 && (lower_bound_distance + shift_value < 0))
    {
        shift_value = shift_value + 26;
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //update and return new_letter

    char new_letter;

    new_letter = letter + shift_value;

    return new_letter;


   }
}
int getDoubleKeyShiftValue(string key1, string key2)
{
    if (key1 == "" || key2 == "")
    {
        return 0;
    }

    //do a loop that parses through each letter of word 1 and check it against each letter of word 2
    //if they match, counter goes up 1

else
{
    int length1 = key1.length();
    int length2 = key2.length();
    int shift = 0;

    for (int i = 0; i < length1; i++)
    {

        for (int j = 0; j < length2; j++)
        {
            if (key1[i] == key2[j])
            {
                shift++;
            }
        }
    }

    return shift;
}
}


string getLayer1MessageEncryption(string message, int method_choice, string key1, string key2)
{

    //check for blank message
    if (message == "")
    {
        return "";
    }

    //check for wrong method choice
    else if (method_choice != 1 && method_choice != 2)
    {
        return message;
    }

    //check for blank key
    else if (method_choice == 2 && (key1 == "" || key2 == ""))
    {
        return message;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
        //method 1 shift = 13
        //loop shiftChar for each letter of message, set to new message

        //initialize newmessage to be same lenght as message
        string original_message = message;

        //method 1
        if (method_choice == 1)
        {
            for (int i = 0; i < message.length(); i++)
            {
                original_message[i] = shiftChar(message[i], 13);
            }

            return original_message;
        }



        else
        {
            //method 2, do get double shift value to find shift value, then use same loop as method 1

            int shift_value = getDoubleKeyShiftValue(key1, key2);

            for (int i = 0; i < message.length(); i++)
            {
                original_message[i] = shiftChar(message[i], shift_value);
            }

            return original_message;

        }

    }
}
string getLayer1MessageDecryption(string encrypted_message, int method_choice, string key1, string key2)
{
    //do same this as encryption except instead of left shift, just do right shift for 26-shift_value
    //for shift value 13, new shift value is 26-13 = 13, so just shift again
    //for shift value 5, new shift is 21. ex a --> f -back-> a



    //check for blank message
    if (encrypted_message == "")
    {
        return "";
    }

    //check for wrong method choice
    else if (method_choice != 1 && method_choice != 2)
    {
        return encrypted_message;
    }

    //check for blank key
    else if (method_choice == 2 && (key1 == "" || key2 == ""))
    {
        return encrypted_message;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    else
    {
        //method 1 shift = 13
        //loop shiftChar for each letter of message, set to new message

        //initialize newmessage to be same lenght as message
        string new_message = encrypted_message;

        //method 1
        //shift 13 again
        if (method_choice == 1)
        {
            for (int i = 0; i < encrypted_message.length(); i++)
            {
                new_message[i] = shiftChar(encrypted_message[i], 13);
            }

            return new_message;
        }



        else
        {
            //method 2, do get double shift value to find shift value, then use same loop as method 1
            //shift value = 26 - shift function

            int shift_value = 26 - getDoubleKeyShiftValue(key1, key2);

            for (int i = 0; i < encrypted_message.length(); i++)
            {
                new_message[i] = shiftChar(encrypted_message[i], shift_value);
            }

            return new_message;

        }

    }
}

string getLayer2MessageEncryption(string message, string key_phrase)
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //initial checks
    if (message == "")
    {
        return message;
    }

    else if (key_phrase == "")
    {
        return message;
    }

    else
    {
        //function that parses though each letter
        //after a space " " the next letter is indexed as the shift
        //number of shifts is the num spaces + 1
        //if not a letter after the space, return original message (do traverse before shift operation)
        
        /*
            1. traverse and check for num spaces
            2. set num_spaces + 1 = num_shifts
            3. make an empty string with length num_shifts
            4. parse though key_phrase, when " ", next letter is set to the a spot on the string
            5. if any of the string chars != a letter, return message
            6. turn each letter of valid keyword into its shift number (a=0 --> z=25)
            7. else do the shiftChar function
                -counter loop that goes from i = 0 --> length on message.length()
                -where shift value loops from shift_1 --> shift_x
                    -and if x = last shift value, reset x to 1
        */

       // 1.
       int num_spaces = 0;

       //if first char is a space, subtract 1 from num space to counteract the next function
       if (key_phrase[0] == ' ')
       {
        num_spaces--;
       }

       for (int i = 1; i < key_phrase.length(); i++)
       {
            //also if the next char is a space then it doesnt run (no double spaces)
            
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                num_spaces++;
            }
       }

        // 2.
        int num_shifts = num_spaces + 1;

        // 3.
        //starts empty (length 0) and adds a space " " for each character the string should hold
        string keyword = "";

        for (int i = 0; i < num_shifts; i++)
        {
            keyword = keyword + " ";
        }


        // 4.
        //if character at index i is a space ' ', next letter (key_phrase[i+1]) gets stored into keyword
        //very first letter of key_phrase is first letter of keyword no matter what

        //sets first letter as long as it isn't a space

        int j = 0;


        if (key_phrase[0] != ' ')
        {
            keyword[0] = key_phrase[0];
            j = 1;
        }

        
        for (int i = 1; i < key_phrase.length(); i++)
        {
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                keyword[j] = key_phrase[i];
                j++;
            }
        }


        // 5.
        bool bad_keyword = false;

        for (int i = 0; i < keyword.length(); i++)
        {
            //if outside of both range of upper and lower case, return message
            if ((keyword[i] < 65 || keyword[i] > 90) && (keyword[i] < 97 || keyword[i] > 122))
            {
                bad_keyword = true;
            }
        }        
        
        if (bad_keyword == true)
        {
            return message;
        }

        else
        {
            // 6.
            //make a loop that parses each character, subtract 0 to make it an int, then subtract 65 if it's capital or 97 if its lowercase so that a, A = 0
            //then set a variable equal to that value
            //and do the shiftChar function. Set a new string to be the length of the message. Set each shifted char at the same place of the new string
            //the inner loop should do the shift key and the outer should do the shift char with that key


            //creates new_message and makes it the same length as message
            string new_message = "";
            for (int i = 0; i < message.length(); i++)
            {
                new_message = new_message + " ";
            }


            // 7.
            int shift = 0;
            int keyword_length = keyword.length();
            int x = 0;

            for (int i = 0; i < message.length(); i++)
            {
                
                
                //sets shift value for each keyword character
                //resets loop when it gets to the end

                //istead of converting lowercase in keyword to uppercase (adding keyword[i] - 35))
                //just do lowercase - 90 and uppercase - 65, so shifted(a) = shifted(A) = 0, shifted(b) = shifted(B) = 1 etc


                    if (isupper(keyword[x]))
                    {
                        shift = keyword[x] - 65;
                    }

                    if (islower(keyword[x]))
                    {
                        shift = keyword[x] - 97;
                    }

                    //if not a valid letter for message[i], shift = 0
                    if (!(isalpha(message[i])))
                    {
                        shift = 0;
                    }
                    
                    

                    //increment x when x < length of keyword only if the character at message[i] is a letter
                    //when x gets added up to the length, reset x to 0
                        //loop for keyword
                    if ((x < keyword_length) && (isalpha(message[i])))
                    {
                        x++;
                    }
                    if (x == keyword_length)
                    {
                        x = 0;
                    }
                    

                    
                    
                    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                //do shift for character message[i] and use the shift
                //if not a letter, shift is 0
                //set equal to new_message at same [i]


                new_message[i] = shiftChar(message[i], shift);

            
                
            }
        
            return new_message;


        }

        
    }
}
string getLayer2MessageDecryption(string encrypted_message, string key_phrase)
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //initial checks
    if (encrypted_message == "")
    {
        return encrypted_message;
    }

    else if (key_phrase == "")
    {
        return encrypted_message;
    }

    else
    {
        //***************************************************************************************************************************
        /*           NOTE FOR THIS FUNCTION:
        
                    This function is copy and paste from getLayer2Encryption (Q5)
                    What i did to decrypt:
                        1. change the parameter/variable names
                            - message --> encrypted_message
                            - new_message --> message
                        
                        2. I turned the shift into it's negative value (see "NOTE ON SHIFT" under step 7 near the bottom of this function)
                            so if the encryption had a shift of 3 at point message[i]
                            then if I do a negative shift (shift = -3) at encrypted_message[i] i will get message[i]
                            so i said shift = 0 - (old shift)
                            where old shift is the copy/paste shift function from the encryption function
        
        */




        //function that parses though each letter
        //after a space " " the next letter is indexed as the shift
        //number of shifts is the num spaces + 1
        //if not a letter after the space, return original message (do traverse before shift operation)
        
        /*
            1. traverse and check for num spaces
            2. set num_spaces + 1 = num_shifts
            3. make an empty string with length num_shifts
            4. parse though key_phrase, when " ", next letter is set to the a spot on the string
            5. if any of the string chars != a letter, return message
            6. turn each letter of valid keyword into its shift number (a=0 --> z=25)
            7. else do the shiftChar function
                -counter loop that goes from i = 0 --> length on message.length()
                -where shift value loops from shift_1 --> shift_x
                    -and if x = last shift value, reset x to 1
        */

       // 1.
       int num_spaces = 0;

       //if first char is a space, subtract 1 from num space to counteract the next function
       if (key_phrase[0] == ' ')
       {
        num_spaces--;
       }

       for (int i = 1; i < key_phrase.length(); i++)
       {
            //also if the next char is a space then it doesnt run (no double spaces)
            
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                num_spaces++;
            }
       }

        // 2.
        int num_shifts = num_spaces + 1;

        // 3.
        //starts empty (length 0) and adds a space " " for each character the string should hold
        string keyword = "";

        for (int i = 0; i < num_shifts; i++)
        {
            keyword = keyword + " ";
        }


        // 4.
        //if character at index i is a space ' ', next letter (key_phrase[i+1]) gets stored into keyword
        //very first letter of key_phrase is first letter of keyword no matter what

        //sets first letter as long as it isn't a space

        int j = 0;


        if (key_phrase[0] != ' ')
        {
            keyword[0] = key_phrase[0];
            j = 1;
        }

        
        for (int i = 1; i < key_phrase.length(); i++)
        {
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                keyword[j] = key_phrase[i];
                j++;
            }
        }


        // 5.
        bool bad_keyword = false;

        for (int i = 0; i < keyword.length(); i++)
        {
            //if outside of both range of upper and lower case, return message
            if ((keyword[i] < 65 || keyword[i] > 90) && (keyword[i] < 97 || keyword[i] > 122))
            {
                bad_keyword = true;
            }
        }        
        
        if (bad_keyword == true)
        {
            return encrypted_message;
        }

        else
        {
            // 6.
            //make a loop that parses each character, subtract 0 to make it an int, then subtract 65 if it's capital or 97 if its lowercase so that a, A = 0
            //then set a variable equal to that value
            //and do the shiftChar function. Set a new string to be the length of the message. Set each shifted char at the same place of the new string
            //the inner loop should do the shift key and the outer should do the shift char with that key


            //creates new_message and makes it the same length as message
            string message = "";
            for (int i = 0; i < encrypted_message.length(); i++)
            {
                message = message + " ";
            }


            // 7.
            int shift = 0;
            int keyword_length = keyword.length();
            int x = 0;

            for (int i = 0; i < encrypted_message.length(); i++)
            {
                
                
                //sets shift value for each keyword character
                //resets loop when it gets to the end

                //istead of converting lowercase in keyword to uppercase (adding keyword[i] - 35))
                //just do lowercase - 90 and uppercase - 65, so shifted(a) = shifted(A) = 0, shifted(b) = shifted(B) = 1 etc



                // NOTE ON SHIFT in explanation at tope of function getLayer2Decryption
                    if (isupper(keyword[x]))
                    {
                        shift = 0 - (keyword[x] - 65);
                    }

                    if (islower(keyword[x]))
                    {
                        shift = 0 - (keyword[x] - 97);
                    }

                    //if not a valid letter for message[i], shift = 0
                    if (!(isalpha(encrypted_message[i])))
                    {
                        shift = 0;
                    }
                    
                    

                    //increment x when x < length of keyword only if the character at message[i] is a letter
                    //when x gets added up to the length, reset x to 0
                        //loop for keyword
                    if ((x < keyword_length) && (isalpha(encrypted_message[i])))
                    {
                        x++;
                    }
                    if (x == keyword_length)
                    {
                        x = 0;
                    }
                    

                    
                    
                    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                //do shift for character message[i] and use the shift
                //if not a letter, shift is 0
                //set equal to new_message at same [i]


                message[i] = shiftChar(encrypted_message[i], shift);

            
                
            }
        
            return message;


        }

        
    }
}

string getLayer3MessageEncryption(string message)
{
    //1. if blank return message
    //2. parse through each letter
    //3. if certain letter, replace with symbol

    /*
    a <-> @
    b <-> &
    c <-> (
    d <-> )
    e <-> 3
    h <-> #
    i <-> !
    j <-> ;
    k <-> \
    l <-> 7
    m
    n
    o <-> 0
    p
    q
    r
    s <-> $
    t <-> 7
    u
    v
    w <-> ?
    x <-> +
    y <-> 
    z <-> 2
    " " <-> _
    */

    int length = message.length();

    if (message == "")
    {
        return message;
    }

    //need to cover

    else
    {
        for (int i = 0; i < length; i++)
        {
            if (message[i] == 'a')
            {
                message[i] = '@';
            }

            else if (message[i] == 'b')
            {
                message[i] = '&';
            }

            else if (message[i] == 'c')
            {
                message[i] = '(';
            }

            else if (message[i] == 'd')
            {
                message[i] = ')';
            }

            else if (message[i] == 'e')
            {
                message[i] = '3';
            }

            else if (message[i] == 'h')
            {
                message[i] = '#';
            }

            else if (message[i] == 'i')
            {
                message[i] = '!';
            }

            else if (message[i] == 'j')
            {
                message[i] = ';';
            }

            else if (message[i] == 'k')
            {
                message[i] = '\\';
            }

            else if (message[i] == 'l')
            {
                message[i] = '|';
            }

            else if (message[i] == 'o')
            {
                message[i] = '0';
            }

            else if (message[i] == 's')
            {
                message[i] = '$';
            }

            else if (message[i] == 't')
            {
                message[i] = '7';
            }

            else if (message[i] == 'w')
            {
                message[i] = '?';
            }

            else if (message[i] == 'x')
            {
                message[i] = '+';
            }

            else if (message[i] == 'z')
            {
                message[i] = '2';
            }

            else if (message[i] == ' ')
            {
                message[i] = '_';
            }

            /////////////////////////////////////////////////////////////////////

            else if (message[i] == '@')
            {
                message[i] = 'a';
            }

            else if (message[i] == '&')
            {
                message[i] = 'b';
            }

            else if (message[i] == '(')
            {
                message[i] = 'c';
            }

            else if (message[i] == ')')
            {
                message[i] = 'd';
            }

            else if (message[i] == '3')
            {
                message[i] = 'e';
            }

            else if (message[i] == '#')
            {
                message[i] = 'h';
            }

            else if (message[i] == '!')
            {
                message[i] = 'i';
            }

            else if (message[i] == ';')
            {
                message[i] = 'j';
            }

            else if (message[i] == '\\')
            {
                message[i] = 'k';
            }

            else if (message[i] == '|')
            {
                message[i] = 'l';
            }

            else if (message[i] == '0')
            {
                message[i] = 'o';
            }

            else if (message[i] == '$')
            {
                message[i] = 's';
            }

            else if (message[i] == '7')
            {
                message[i] = 't';
            }

            else if (message[i] == '?')
            {
                message[i] = 'w';
            }

            else if (message[i] == '+')
            {
                message[i] = 'x';
            }

            else if (message[i] == '2')
            {
                message[i] = 'z';
            }

            else if (message[i] == '_')
            {
                message[i] = ' ';
            }
            
        }
        return message;
    }


}
string getLayer3MessageDecryption(string encrypted_message)
{
    
    int length = encrypted_message.length();

    if (encrypted_message == "")
    {
        return encrypted_message;
    }

    //need to cover

    else
    {
        for (int i = 0; i < length; i++)
        {
            if (encrypted_message[i] == 'a')
            {
                encrypted_message[i] = '@';
            }

            else if (encrypted_message[i] == 'b')
            {
                encrypted_message[i] = '&';
            }

            else if (encrypted_message[i] == 'c')
            {
                encrypted_message[i] = '(';
            }

            else if (encrypted_message[i] == 'd')
            {
                encrypted_message[i] = ')';
            }

            else if (encrypted_message[i] == 'e')
            {
                encrypted_message[i] = '3';
            }

            else if (encrypted_message[i] == 'h')
            {
                encrypted_message[i] = '#';
            }

            else if (encrypted_message[i] == 'i')
            {
                encrypted_message[i] = '!';
            }

            else if (encrypted_message[i] == 'j')
            {
                encrypted_message[i] = ';';
            }

            else if (encrypted_message[i] == 'k')
            {
                encrypted_message[i] = '\\';
            }

            else if (encrypted_message[i] == 'l')
            {
                encrypted_message[i] = '|';
            }

            else if (encrypted_message[i] == 'o')
            {
                encrypted_message[i] = '0';
            }

            else if (encrypted_message[i] == 's')
            {
                encrypted_message[i] = '$';
            }

            else if (encrypted_message[i] == 't')
            {
                encrypted_message[i] = '7';
            }

            else if (encrypted_message[i] == 'w')
            {
                encrypted_message[i] = '?';
            }

            else if (encrypted_message[i] == 'x')
            {
                encrypted_message[i] = '+';
            }

            else if (encrypted_message[i] == 'z')
            {
                encrypted_message[i] = '2';
            }

            else if (encrypted_message[i] == ' ')
            {
                encrypted_message[i] = '_';
            }

            /////////////////////////////////////////////////////////////////////

            else if (encrypted_message[i] == '@')
            {
                encrypted_message[i] = 'a';
            }

            else if (encrypted_message[i] == '&')
            {
                encrypted_message[i] = 'b';
            }

            else if (encrypted_message[i] == '(')
            {
                encrypted_message[i] = 'c';
            }

            else if (encrypted_message[i] == ')')
            {
                encrypted_message[i] = 'd';
            }

            else if (encrypted_message[i] == '3')
            {
                encrypted_message[i] = 'e';
            }

            else if (encrypted_message[i] == '#')
            {
                encrypted_message[i] = 'h';
            }

            else if (encrypted_message[i] == '!')
            {
                encrypted_message[i] = 'i';
            }

            else if (encrypted_message[i] == ';')
            {
                encrypted_message[i] = 'j';
            }

            else if (encrypted_message[i] == '\\')
            {
                encrypted_message[i] = 'k';
            }

            else if (encrypted_message[i] == '|')
            {
                encrypted_message[i] = 'l';
            }

            else if (encrypted_message[i] == '0')
            {
                encrypted_message[i] = 'o';
            }

            else if (encrypted_message[i] == '$')
            {
                encrypted_message[i] = 's';
            }

            else if (encrypted_message[i] == '7')
            {
                encrypted_message[i] = 't';
            }

            else if (encrypted_message[i] == '?')
            {
                encrypted_message[i] = 'w';
            }

            else if (encrypted_message[i] == '+')
            {
                encrypted_message[i] = 'x';
            }

            else if (encrypted_message[i] == '2')
            {
                encrypted_message[i] = 'z';
            }

            else if (encrypted_message[i] == '_')
            {
                encrypted_message[i] = ' ';
            }
            
        }
        return encrypted_message;
    }
}

string getChainEncryption(string message, int method_choice, string key1, string key2, string key_phrase)
{
    /*
        plan:

        1.1. do checks valid message, method choice, keys, and valid keyword from keyphrase
        1.2. borrow keyword validity check fromgetLayer2MessageEncryption
        2. do layer 1 encryption with (message, method_choice, key1, key2) and set that string = key_phrase
        3. do layer 2 encryption with (message, key_phrase)
        4. set the layer 2 encryption to new_message and return it
    */

   // 1.
   //checks for valid message, method, and keys
   if (message == "")
   {
    return message;
   }

   else if (method_choice != 1 && method_choice != 2)
   {
    return message;
   }

   else if (method_choice == 2 && (key1 == "" || key2 == ""))
   {
    return message;
   }

   else if (key_phrase == "")
   {
    return message;
   }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//borrowing keyword validity check from getLayer2MessageEncryption
//because when ran the function without this check it did not return message
//copy and paste so the notes are the same as from getLayer2MessageEncryption


int num_spaces = 0;

       //if first char is a space, subtract 1 from num space to counteract the next function
       if (key_phrase[0] == ' ')
       {
        num_spaces--;
       }

       for (int i = 1; i < key_phrase.length(); i++)
       {
            //also if the next char is a space then it doesnt run (no double spaces)
            
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                num_spaces++;
            }
       }

        // 2.
        int num_shifts = num_spaces + 1;

        // 3.
        //starts empty (length 0) and adds a space " " for each character the string should hold
        string keyword = "";

        for (int i = 0; i < num_shifts; i++)
        {
            keyword = keyword + " ";
        }


        // 4.
        //if character at index i is a space ' ', next letter (key_phrase[i+1]) gets stored into keyword
        //very first letter of key_phrase is first letter of keyword no matter what

        //sets first letter as long as it isn't a space

        int j = 0;


        if (key_phrase[0] != ' ')
        {
            keyword[0] = key_phrase[0];
            j = 1;
        }

        
        for (int i = 1; i < key_phrase.length(); i++)
        {
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                keyword[j] = key_phrase[i];
                j++;
            }
        }


        // 5.
        bool bad_keyword = false;

        for (int i = 0; i < keyword.length(); i++)
        {
            //if outside of both range of upper and lower case, return message
            if ((keyword[i] < 65 || keyword[i] > 90) && (keyword[i] < 97 || keyword[i] > 122))
            {
                bad_keyword = true;
            }
        }        
        
        if (bad_keyword == true)
        {
            return message;
        }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




   else
   {
        // 2. and 3.
        string intermediate_message1 = getLayer1MessageEncryption(message, method_choice, key1, key2);
        string intermediate_message2 = getLayer2MessageEncryption(intermediate_message1, key_phrase);
        string new_message = getLayer3MessageEncryption(intermediate_message2);

        return new_message;

   }
}
string getChainDecryption(string encrypted_message, int method_choice, string key1, string key2, string key_phrase)
{
    /*
        1. use same code from step 1 in getChainEncryption
        2. do get layer 2 decryption, set equal to intermediate message
        3. do get layer 1 decyrption, set equal to message
        4. cout message
    */

   // 1.
   //checks for valid message, method, and keys
   if (encrypted_message == "")
   {
    return encrypted_message;
   }

   else if (method_choice != 1 && method_choice != 2)
   {
    return encrypted_message;
   }

   else if (method_choice == 2 && (key1 == "" || key2 == ""))
   {
    return encrypted_message;
   }

   else if (key_phrase == "")
   {
    return encrypted_message;
   }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//borrowing keyword validity check from getLayer2MessageEncryption
//because when ran the function without this check it did not return message
//copy and paste so the notes are the same as from getLayer2MessageEncryption


int num_spaces = 0;

       //if first char is a space, subtract 1 from num space to counteract the next function
       if (key_phrase[0] == ' ')
       {
        num_spaces--;
       }

       for (int i = 1; i < key_phrase.length(); i++)
       {
            //also if the next char is a space then it doesnt run (no double spaces)
            
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                num_spaces++;
            }
       }

        // 2.
        int num_shifts = num_spaces + 1;

        // 3.
        //starts empty (length 0) and adds a space " " for each character the string should hold
        string keyword = "";

        for (int i = 0; i < num_shifts; i++)
        {
            keyword = keyword + " ";
        }


        // 4.
        //if character at index i is a space ' ', next letter (key_phrase[i+1]) gets stored into keyword
        //very first letter of key_phrase is first letter of keyword no matter what

        //sets first letter as long as it isn't a space

        int j = 0;


        if (key_phrase[0] != ' ')
        {
            keyword[0] = key_phrase[0];
            j = 1;
        }

        
        for (int i = 1; i < key_phrase.length(); i++)
        {
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                keyword[j] = key_phrase[i];
                j++;
            }
        }


        // 5.
        bool bad_keyword = false;

        for (int i = 0; i < keyword.length(); i++)
        {
            //if outside of both range of upper and lower case, return message
            if ((keyword[i] < 65 || keyword[i] > 90) && (keyword[i] < 97 || keyword[i] > 122))
            {
                bad_keyword = true;
            }
        }        
        
        if (bad_keyword == true)
        {
            return encrypted_message;
        }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        // 2., 3., and 4.
    else
    {
        // string intermediate_message1 = getLayer2MessageDecryption(encrypted_message, key_phrase);
        // string intermediate_message2 = getLayer1MessageDecryption(intermediate_message1, method_choice, key1, key2);
        // string message = getLayer3MessageDecryption(intermediate_message2);

        string intermediate_message1 = getLayer3MessageDecryption(encrypted_message);
        string intermediate_message2 = getLayer2MessageDecryption(intermediate_message1, key_phrase);
        string message = getLayer1MessageDecryption(intermediate_message2, method_choice, key1, key2);

        return message;

    }

}

bool badKeyword(string key_phrase)
{
    int num_spaces = 0;

       //if first char is a space, subtract 1 from num space to counteract the next function
       if (key_phrase[0] == ' ')
       {
        num_spaces--;
       }

       for (int i = 1; i < key_phrase.length(); i++)
       {
            //also if the next char is a space then it doesnt run (no double spaces)
            
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                num_spaces++;
            }
       }

        // 2.
        int num_shifts = num_spaces + 1;

        // 3.
        //starts empty (length 0) and adds a space " " for each character the string should hold
        string keyword = "";

        for (int i = 0; i < num_shifts; i++)
        {
            keyword = keyword + " ";
        }


        // 4.
        //if character at index i is a space ' ', next letter (key_phrase[i+1]) gets stored into keyword
        //very first letter of key_phrase is first letter of keyword no matter what

        //sets first letter as long as it isn't a space

        int j = 0;


        if (key_phrase[0] != ' ')
        {
            keyword[0] = key_phrase[0];
            j = 1;
        }

        
        for (int i = 1; i < key_phrase.length(); i++)
        {
            if (key_phrase[i-1] == ' ' && key_phrase[i] != ' ')
            {
                keyword[j] = key_phrase[i];
                j++;
            }
        }


        // 5.
        bool bad_keyword = false;

        for (int i = 0; i < keyword.length(); i++)
        {
            //if outside of both range of upper and lower case, return message
            if ((keyword[i] < 65 || keyword[i] > 90) && (keyword[i] < 97 || keyword[i] > 122))
            {
                bad_keyword = true;
            }
        }        
        
        return bad_keyword;
}
int main()
{

    /*
    for menu, loop the menu options while input isn't 7 (exit)
    use a switch to access each option
        default says it's invalid (if not a valid input)
        option 4 is *important*
            must choose layer 1, layer 2, or chain encryption
                if using layer 1 (or chain) choose between key encryption or shift by 13

    */


    string navigate_string;
    int navigate_number;

    string choice_string = "";
    int choice_number;

    string method_choice_string = "";
    int method_choice_number = 0;

    string key1 = "";
    string key2 = "";
    string key_phrase = "";

    string message_to_encrypt;
    string message_to_decrypt;

    string message;
    


    do
    {  
    cout << endl;
    cout << "Please input 1-7 followed by enter to navigate the menu:" << endl;
    cout << "1. Set Encryption Key 1" << endl;
    cout << "2. Set Encryption Key 2" << endl;
    cout << "3. Set Key Phrase" << endl;
    cout << "4. Select Encryption Method" << endl;
    cout << "5. Encrypt Message" << endl;
    cout << "6. Decrypt Message" << endl;
    cout << "7. Exit Program" << endl;
    getline(cin, navigate_string);

    //to counteract error from stoi for a non-integer, i first check that the input is a valid option as a string before converting
    //ok to do because there are only 7 correct options
    if (navigate_string != "1" && navigate_string != "2" && navigate_string != "3" && navigate_string != "4" && navigate_string != "5" && navigate_string != "6" && navigate_string != "7")
    {
        //setting to 0 makes the loop run until navigate_number is 1-7
        navigate_number = 0;
    }

    //store integer if valid string 1-7
    else
    {
        navigate_number = stoi(navigate_string);
    }


    //switch for the 7 options
    switch (navigate_number)
    {  

// 1. key 1 input
        case 1:
            do 
            {

                //valid key check (not blank)
                cout << endl;
                cout << "Enter First key:" << endl;
            getline(cin, key1);

            if (key1 == "")
            {
                cout << "Invalid key" << endl;
            }

            //successful when valid
            else
            {
                cout << endl;
                cout << "Successfully set first encryption key to " << key1 << endl;
            }
            } while (key1 == "");
        break;


// 2. key 2 input
        case 2: 
            do 
            {

                //valid key check
                cout << endl;
                cout << "Enter Second key:" << endl;
            getline(cin, key2);

            if (key2 == "")
            {
                cout << "Invalid key" << endl;
            }

            else
            {
                cout << endl;
                cout << "Successfully set second encryption key to " << key2 << endl;
            }
            } while (key2 == "");

        break;



        
// 3. keyphrase input
        case 3:
            do 
            {
                //input keyphrase
                cout << endl;
                cout << "Enter keyphrase:" << endl;
            getline(cin, key_phrase);

            //make sure it isn't blank
            if (key_phrase == "")
            {
                cout << "Invalid keyphrase" << endl;
            }

            //run badkeyword function that check if the keyword from the keyphrase is valid (no special characters)
            //if no valid, cout invalid keyphrase and ask again
            else if (badKeyword(key_phrase) == true)
            {
                cout << "Invalid keyphrase" << endl;
                cout << endl;
            }

            else
            {
                cout << endl;
                cout << "Successfully set encryption keyphrase to " << key_phrase << endl;
            }
            //condition that loop keeps running if keyphrase is blank or keyword is bad
            } while (key_phrase == "" || badKeyword(key_phrase) == true);
        break;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 4:
            do
            {
                //cout options, take input
                cout << endl;
                cout << "Please input 1-3 to decide encryption technique." << endl;
                cout << "1. Layer 1 Message Encryption" << endl;
                cout << "2. Layer 2 Message Encryption" << endl;
                cout << "3. Chain Encryption" << endl;
                getline(cin, choice_string);

                //store as int only if input as a string is a valid option
                //set choice number to 0 so the loops keeps running until valid input
                if (choice_string != "1" && choice_string != "2" && choice_string != "3")
                {
                    choice_number = 0;
                }

                else
                {
                    choice_number = stoi(choice_string);
                }
                
                //cout invalid if not 1, 2, 3
                if (choice_number != 1 && choice_number != 2 && choice_number != 3)
                {
                    cout << endl;
                    cout << "Invalid encryption choice" << endl;
                }

                //success statement
                else
                {
                    cout << endl;
                    cout << "Successfully set encryption type to " << choice_number << endl;
                    

                    //if choice 2 (layer 2 only), method_choice is not needed but because it must still be input for case 5 to run
                    //i set it to -1 as a placeholder
                    //if method 2 is chosen, but later changed to 1 or 3 method choice will have to be changed (happens below)
                    if (choice_number == 2)
                    {
                        method_choice_number = -1;
                    }


                    if (choice_number == 1 || choice_number == 3)
                    {
                        do
                        {
                            //cout and getline for choice in layer 1
                            //if invalid, set method_choice to so it keeps looping until 1 or 2
                            cout << endl;
                            cout << "Please input 1-2 to decide Layer-1 encryption technique." << endl;
                            cout << "1. Shift by 13" << endl;
                            cout << "2. Shift by mixed keys" << endl;

                            getline(cin, method_choice_string);

                            if (method_choice_string != "1" && method_choice_string != "2")
                            {
                                method_choice_number = 0;
                            }

                            else
                            {
                                method_choice_number = stoi(method_choice_string);
                                cout << endl;
                                cout << "Successfully set method choice to " << method_choice_number << endl;
                                
                            }

                            
                            //invalid if not 1 or 2
                            if (method_choice_number != 1 && method_choice_number != 2)
                            {
                                cout << "Invalid encryption choice" << endl;
                                cout << endl;
                            }

                            //inner loop (layer 1/chain) keeps running until method_choice is valid
                        } while (method_choice_number != 1 && method_choice_number != 2);
                    }
                }
            //outer loop (any encryption type) keeps running until valid choice 1, 2, 3
            } while (choice_number != 1 && choice_number != 2 && choice_number != 3);

        break;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 5.

        case 5:

        //only useable if method choice, keys, and keyphrase are entered
        //technically keys are not needed for layer 2 method choice and keyphrase not needed for layer 1 but the github says to make it needed no matter whatmethod is chosen
        if (method_choice_number == 0 || key1 == "" || key2 == "" || key_phrase == "")
        {
            cout << endl;
            cout << "You cannot do this until you set both keys, keyphrase, and choose an encryption method" << endl;
            
        }

        //if useable, do encryption
        else
        {
            cout << endl;
            cout << "Enter your message to encrypt:" << endl;
            getline(cin, message_to_encrypt);
            
            //choice 1 (layer 1)
            if (choice_number == 1)
            {
                message = getLayer1MessageEncryption(message_to_encrypt, method_choice_number, key1, key2);
                cout << endl;
                cout << "Your encrypted message is:" << endl;
                cout << message << endl;
            }

            //choice 2 (layer 2)
            if (choice_number == 2)
            {
                message = getLayer2MessageEncryption(message_to_encrypt, key_phrase);
                cout << endl;
                cout << "Your encrypted message is:" << endl;
                cout << message << endl;
            }

            //choice 3 (chain)
            if (choice_number == 3)
            {
                message = getChainEncryption(message_to_encrypt, method_choice_number, key1, key2, key_phrase);
                cout << endl;
                cout << "Your encrypted message is:" << endl;
                cout << message << endl;
            }



        }

        break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 6.


        case 6: 
        //decryption, same as case 5 encryption just with messages to decrypt amd decrypt functions
            if (method_choice_number == 0 || key1 == "" || key2 == "" || key_phrase == "")
        {
            cout << endl;
            cout << "You cannot do this until you set both keys, keyphrase, and choose an encryption method" << endl;
            
        }

        else
        {
            cout << endl;
            cout << "Enter your message to decrypt:" << endl;
            getline(cin, message_to_decrypt);
            
            if (choice_number == 1)
            {
                message = getLayer1MessageDecryption(message_to_decrypt, method_choice_number, key1, key2);
                cout << endl;
                cout << "Your decrypted message is:" << endl;
                cout << message << endl;
            }

            if (choice_number == 2)
            {
                message = getLayer2MessageDecryption(message_to_decrypt, key_phrase);
                cout << endl;
                cout << "Your decrypted message is:" << endl;
                cout << message << endl;
            }

            if (choice_number == 3)
            {
                message = getChainDecryption(message_to_decrypt, method_choice_number, key1, key2, key_phrase);
                cout << endl;
                cout << "Your decrypted message is:" << endl;
                cout << message << endl;
            }



        }

        break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 7.

        //cute goodbye statement when exit is chosen
        case 7: cout << "Goodbye." << endl;
        break;


        default: cout << "Invalid input" << endl;
    }







}
//all the menu options keep running until exit is chosen
while (navigate_number != 7);
return 0;
}

