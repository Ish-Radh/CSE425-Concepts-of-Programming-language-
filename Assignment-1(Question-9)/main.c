#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//delimiters in C 
bool isDelimiter(char ch) {
   if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
   ch == '/' || ch == ',' || ch == ';' || ch == '<' ||
   ch == '>' || ch == '=' || ch == '(' || ch == ')' ||
   ch == '{' || ch == '}' || ch == '[' || ch == ']')
   return true;
   else return false;
}
//specific symbols operators from delimiters
bool isSymbolOperator(char ch){
   if (ch == '+' || ch == '-' || ch == '*' ||
   ch == '/' || ch == '>' || ch == '<' ||
   ch == '=')
   return true;
   else return false;
}
//Cbraceopen
bool CbraceOpen(char ch){
   if (ch == '{')
   return true;
   else
   return (false);
}

//Cbraceclose
bool CbraceClose(char ch){
   if (ch == '}')
   return true;
   else return false;
}

//parenthesis open
bool ParenthesisOpen(char ch){
   if (ch == '(')
   return true;
   else return (false);
}

// parenthesis close
bool ParenthesisClose(char ch){
   if (ch == ')')
   return true;
 else   return false;
}
//Valid identifiers
bool isIdentifier(char* str){
   if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
   str[0] == '3' || str[0] == '4' || str[0] == '5' ||
   str[0] == '6' || str[0] == '7' || str[0] == '8' ||
   str[0] == '9' || isDelimiter(str[0]) == true)
   return false;
   else return (true);//returns true for valid identifiers in the program
}

//valid keywords
bool isKeyword(char* str) {
   if (!strcmp(str, "int") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||    !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "if")
   || !strcmp(str, "double") || !strcmp(str, "sizeof") || !strcmp(str, "return") || !strcmp(str,"static") || !strcmp(str, "unsigned") || !strcmp(str, "char")
   || !strcmp(str, "float") || !strcmp(str, "void") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "case")
   || !strcmp(str, "long") || !strcmp(str, "extern") || !strcmp(str, "struct") || !strcmp(str, "goto")|| !strcmp(str, "enum")
    || !strcmp(str, "volatile")|| !strcmp(str, "printf")|| !strcmp(str, "register")|| !strcmp(str, "auto")|| !strcmp(str, "union")
    || !strcmp(str, "default")|| !strcmp(str, "break"))
   return true;
  else return (false);
}
//String literals
bool isStringliteral(char ch)
{
    if(ch=="   \"%d\"    "||ch== "  \"%s\"    "||ch=="  \"%d\"   "|| ch==" \" -\" ")
        return true ;
    else return false;

}

//integers
bool isLiteral(char* str) {
   int i, length = strlen(str);

   if (length == 0)//File has no program
   return false;

   for (i = 0; i < length; i++) {
      if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
      && str[i] != '9')
      return false;
   }

}

//Substring formation
char* subString(char* str, int left, int right) {  //left and right are indexes of the first and last characters of the sub-string.
   int i;
   char* subStr = (char*)malloc( sizeof(char) * (right - left + 2));    //right-left=length of the input program
   for (i = left; i <= right; i++)                                       //allocation of memory
      subStr[i - left] = str[i];                //extraction of characters between start and end indexes and copying it to subStr
   subStr[right - left + 1] = '\0';  //termination when \0 reached
   return subStr;  //substring returned
}
//Parsing of the input C program for defination of each component
void lexicalanalysis(char* str) {
   int left = 0, right = 0;
   int length = strlen(str);

while (right <= length && left <= right) {
      if (isDelimiter(str[right]) == false)
      right++;


      if (isDelimiter(str[right]) == true && left == right)
        {
         if (isSymbolOperator(str[right]) == true)//Checks for symbol operators
            printf("<\"%c\",\"symbol-op\">\n",str[right]);


  //Checks for Cbraces
if (CbraceOpen(str[right]) == true)
      printf(" <\"%c\",\"Cbrace-begin\" > \n",str[right]);
if (CbraceClose(str[right]) == true)
      printf("<\"%c\",\"Cbrace-close\">\n",str[right]);

//Checks for string literals
 if (isStringliteral(str[right]) == true)
      printf("<\"%c\",\"String-literal\">\n",str[right]);

 //Checks for parenthesis
if (ParenthesisOpen(str[right]) == true)
       printf("<\"%c\", \"parenthesis-begin\">\n",str[right]);
if (ParenthesisClose(str[right]) == true)
      printf("<\"%c\",\"parenthesis-end\">\n",str[right]);
right++;//increasong index
left = right; //end
}//Checks for keyword
      else if (isDelimiter(str[right]) == true && left != right || (right == length && left != right)) {
         char* subStr = subString(str, left, right - 1);
         if (isKeyword(subStr) == true)
              printf("<\"%s\", \"keyword\">\n",subStr);


         else if (isLiteral(subStr) == true)//checks for the literals/integers
          printf("<\"%s\",\"literal\">\n",subStr);

         else if (isIdentifier(subStr) == true
            && isDelimiter(str[right - 1]) == false)//checks for identifiers
             printf("<\"%s\", \"Identifier\">\n",subStr);
         left = right;
      }
   }
   return;
}


int main(void){

FILE *fptr;//file pointer
char program[3000]; //will store the characters being read from the file
int a=0; //for indexing
char ch;

// opening the file
 if ((fptr = fopen("program.txt", "r")) == NULL)
    {
        printf("Error opening the file");

    }

while((ch=fgetc(fptr))!=EOF)
    {
        if (ch=='\n')
            continue;
        program[a] = ch;//storing the contents of the file in program variable
        a++;
    }
    lexicalanalysis(program);//Calling the function lexical analysis and passing the program for parsing

    fclose(fptr);//closing the file
   return (0);
}
