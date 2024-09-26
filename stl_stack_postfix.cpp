#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;


/*

Charles Hart

*/

double postfix(std::string line){




    stack<double> the_stack;
    int counter = 0;
    //int b=-1;
    bool log10con = true;
    for (int i=0; i<line.length(); i++){
        if (i<line.length()-4){
            if ((line[i]!='l' && line[i+1]!='o' && line[i+2]!='g' && line[i+3]!='1' && line[i+4]!='0')){
                log10con = true;
            }
            else{
                log10con = false;
            }
        }
       
        if (isdigit(line[i]) || (line[i] == '-' && isdigit(line[i + 1])) && log10con){
            string string2;
            int temp=i;
            if (line[i]=='-'){
                string2+=line[i++];
            }
            while (i<line.length() && isdigit(line[i])){
                string2+=line[i++];
            }
            i--;
            if (string2.length() > 15){
                cout << "ERROR" << endl;
                return std::nan("");
            }//no more than 15 digits for double
            double num = stod(string2);
            the_stack.push(num);
        }
        else if (line[i]==' '){
            counter++;//this is here so that the loop will ignore blank spaces without triggering the else condition at the end.
        }
        else if (line[i]=='+' || line[i]=='-' || line[i]=='*' || line[i]=='/' || line[i]=='^'){ //binary
            if (the_stack.size()>=2){
                double binary1 = the_stack.top();
                the_stack.pop();
                double binary2 = the_stack.top();
                the_stack.pop();
                //removes the top two values from the stack for binary operations.
                if (line[i]=='+') {
                    the_stack.push(binary1 + binary2);
                }
                if (line[i]=='-') {
                    the_stack.push(binary2 - binary1);
                }
                if (line[i]=='*') {
                    the_stack.push(binary1 * binary2);
                }
                if (line[i]=='/') {
                    if (binary1 == 0) {
                        cout << "ERROR" << endl;
                        return std::nan(""); //std::nan? 
                    }
                    the_stack.push(binary2 / binary1);
                }
                if (line[i]=='^') {
                    the_stack.push(pow(binary2, binary1));

                }
                //performs operations on the top two values according to the operator read from the file.
                //the double binary2 will be the numerator in division.
            }
            else{
                cout << "ERROR" << endl;
                return std::nan("");
                //if there are less than 2 values in the stack, the operation could not work.
            }
        }
        else if (line[i]=='s' && line[i+1]=='q' && line[i+2]=='r' && line[i+3]=='t'){
            if (the_stack.size()>=1){
                double unary = the_stack.top();
                the_stack.pop();
                if (unary<0){
                    cout << "ERROR" << endl;
                    return std::nan("");
                }
                the_stack.push(sqrt(unary));
            }
        }

        else if (!log10con){//(line[i] == 'l' && line[i + 1] == 'o' && line[i + 2] == 'g' && line[i + 3] == '1' && line[i + 4] == '0') { // unary
            if (the_stack.size()>=1){
                double unary = the_stack.top();
                the_stack.pop();
                if (unary==0){
                    cout << "ERROR" << endl;
                    return std::nan("");
                }
                the_stack.push(log10(unary));
                log10con=true;
                i=line.length(); 
            }
        }

        else if (line[i]=='l' && line[i+1]=='o' && line[i+2]=='g'){ //unary
            if (the_stack.size() >= 1){
                double unary = the_stack.top();
                the_stack.pop();
                if (unary == 0){
                    cout << "ERROR" << endl;
                    return std::nan("");
                }
                the_stack.push(log(unary));
            }
        }
        /*else {
            cout << "ERROR" << endl;
            return std::nan("");
        }*/
    }
    if (the_stack.size() != 1){ //if the stack does not have only one value remaining, it will print error. Should work in place of stack.empty().
        cout << "ERROR" << endl;
        return std::nan("");
    }
    if (the_stack.size() == 1){
        int final = the_stack.top();
        the_stack.pop(); //might not be necessary
        //cout << final << endl;
        return final;
    }
    return std::nan("");
}

int main(int argc, char** argv){
    ifstream inStream;
    string line;


    if (argc < 2) {
        cout << "Please specify filename on command line\n";
        exit(1);
    }

    inStream.open(argv[1]);

    if (inStream.fail()) {
        cout << "Failed to open file\n";
        exit(1);
    }

    while (getline(inStream, line)) {
        cout << postfix(line)  << endl;
    }

    //
    //cout << postfix("4 log10");
    return 1;
}