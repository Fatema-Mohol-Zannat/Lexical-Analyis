#include<bits/stdc++.h>
#include<fstream>

using namespace std;
string token[100][100],take="",symbolTbl[100][100],lastkeyword;
int t=0,symbolindex=0;
int checkSpecialSymbol(char s){
    int ans=0;
    char specialSymbol[10]={'(',')','{','}','[',']',',',';'};
    for(int i=0;i<8;i++){
        if(s==specialSymbol[i]){
            token[t][0]=s;
            token[t][1]="Special Symbol";
            if(s=='(') token[t][2]="Opening braces";
            else if(s==')') token[t][2]="Closing braces";
            else if(s=='{') token[t][2]="left curly braces";
            else if(s=='}') token[t][2]="right curly braces";
            else if(s=='[') token[t][2]="left third braces";
            else if(s==']') token[t][2]="right third braces";
            else if(s==',') token[t][2]="comma";
            else if(s==';') token[t][2]="semicolon";
            t++;
            ans=1;
            break;
        }
    }
    return ans;

}
int checkOperator(string s){
    int ans=0;
    string operators[20]={"+","-","*","/","=","++","--","==","!=",">","<",">=","<=","&&","||","!"};
    for(int i=0;i<16;i++){
        if(s==operators[i]){
            ans=1;
            break;
        }
    }
    return ans;
}
void assignOperator(string s){

    token[t][0]=s;
    token[t][1]="operator";
    if(s=="+") token[t][2]="add";
    else if(s=="-") token[t][2]="subtract";
    else if(s=="*") token[t][2]="multiply";
    else if(s=="/") token[t][2]="divide";
    else if(s=="=") token[t][2]="assignment";
    else if(s=="++") token[t][2]="increment";
    else if(s=="--") token[t][2]="decrement";
    else if(s=="==") token[t][2]="equal";
    else if(s=="!=") token[t][2]="not equal";
    else if(s==">") token[t][2]="greater than";
    else if(s=="<") token[t][2]="less than";
    else if(s==">=") token[t][2]="greater equal";
    else if(s=="<=") token[t][2]="less equal";
    else if(s=="&&") token[t][2]="and";
    else if(s=="||") token[t][2]="or";
    else if(s=="!") token[t][2]="not";
    t++;

}
int checkKeywordOrOthers(string s){
    int ans=0;

    string keywords[40]={"int","float","double","return","for","while","do","break","continue",
    "if","else","void","goto","auto","const","default","enum","extern","long","register",
    "short","signed","sizeof","static","struct","switch","typedef","union","unsigned","volatile"};

    for(int i=0;i<30;i++){
        if(s==keywords[i]){
            token[t][0]=s;
            token[t][1]=s;
            token[t][2]="        -";
            lastkeyword=s;
            ans=1;
            break;
        }
    }
    if(ans==0){
        if(s[0]=='0' || s[0]=='1' || s[0]=='2' || s[0]=='3' || s[0]=='4' || s[0]=='5' || s[0]=='6' || s[0]=='7' || s[0]=='8' || s[0]=='9'){
            token[t][0]=s;
            token[t][1]="number";
            token[t][2]="        constant";
        }
        else{
            token[t][0]=s;
            token[t][1]="id";
            token[t][2]="        pointer to symbol table entry";
            ///For symbolTable
            int check=0;
            for(int i=0;i<symbolindex;i++){
                if(s == symbolTbl[i][0]){
                    check=1;
                    break;
                }
            }
            if(check==0){
                symbolTbl[symbolindex][0]=s;
                symbolTbl[symbolindex][1]="id";
                symbolTbl[symbolindex][2]=lastkeyword;

                ostringstream convert;   // stream used for the conversion
                convert <<symbolindex ;      // insert the textual representation of 'Number' in the characters in the stream
                string result = convert.str();

                symbolTbl[symbolindex][3]=result;
                symbolindex++;
            }
        }
    }
    t++;
    ans=1;
    return ans;
}

int main(){

    ifstream in;
    in.open("input.txt");
    int a=0,clearSTARTindex=0,j=0;
    string previousLine="",START,clearSTART;
    while(a<1) // To get you all the lines.
    {
        getline(in,START); // Saves the line in START.
        if (START != previousLine)
        {

            previousLine=START;
            int check=0;
            j=0;
            while(START[j] != '\0'){
                if(isspace(START[j])){
                        if(isspace(clearSTART[clearSTARTindex-1])){
                            j++;
                            continue;
                        }
                }
                clearSTART[clearSTARTindex]=START[j];
                clearSTARTindex++;
                j++;

            }
            clearSTART[clearSTARTindex]=' ';
            clearSTARTindex++;
        }

        else break;

    }
    clearSTART[clearSTARTindex]='\0';
    int takei=0;
    j=0;

    cout<<"----- Input Scanned -----\n"<<endl;
    while(clearSTART[j] != '\0'){
        cout<<clearSTART[j];

        int ans=checkSpecialSymbol(clearSTART[j]);
        string si="";
        si+=clearSTART[j];
        if(ans==0){
            ans=checkOperator(si);
            if(ans==1){
                string saveOperator="";
                saveOperator+=si;
                saveOperator+=clearSTART[j+1];
                ans=checkOperator(saveOperator);
                if(ans==1){
                    assignOperator(saveOperator);
                    j++;
                }
                else assignOperator(si);
                ans=1;
                saveOperator.clear();
            }
        }

        if(isspace(clearSTART[j]) || ans==1){
            //cout<<take<<endl;
            if(!take.empty())   ans=checkKeywordOrOthers(take);
            take.clear();
        }
        else if(ans==0){
            take+=clearSTART[j];
        }
        j++;
    }

    cout<<"\n\n----- OUTPUT -----\n\nTokens Table: "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<" Lexemes"<<"           "<<"Token Name"<<"              "<<"Attribute Value"<<"  "<<endl;
    cout<<"-----------------------------------------------------------------------"<<"\n";
    for(int i=0;i<t;i++){
        cout<<" "<<token[i][0]<<"\t\t"<<token[i][1]<<"\t\t"<<token[i][2]<<endl;
    }

    cout<<"\nSymbol Table :"<<endl;

    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<" Symbol"<<"        "<<"Token"<<"          "<<"Data Type"<<"   "<<"Pointer to symbol table entry"<<endl;
    cout<<"-----------------------------------------------------------------------"<<"\n";
    for(int i=0;i<t;i++){
        cout<<" "<<symbolTbl[i][0]<<"\t\t"<<symbolTbl[i][1]<<"\t\t"<<symbolTbl[i][2]<<"\t\t"<<symbolTbl[i][3]<<endl;
    }

    in.close();
}
