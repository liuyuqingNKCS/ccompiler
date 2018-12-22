#pragma once
#ifndef DUP_H
#define DUP_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
using namespace std;
int offset = 0;
int struct_width;
string struct_name;
struct typenode
{
    int addr;
    int width;
    string name;
    typenode *left;
    typenode *right;
    typenode(string n = "", int w = 0)
    {
        name = n;
        left = NULL;
        right = NULL;  
        width = w;
        addr = offset;
    }
    void copy(const typenode &type)
    {
        name = type.name;
        width = type.width;
        left = type.left;
        right = type.right;
    }
};

void traverse(typenode *root)
{
    if (root != NULL)
        cout << root->name << endl;
    if (root->left != NULL)
    {
        cout << "left ";
        traverse(root->left);
    }
    if (root->right != NULL)
    {
        cout << "right ";
        traverse(root->right);
    }
}
stack<typenode*> rtn_stmt;
typenode *type;
typenode *type2;
typenode *type3 = new typenode("fun");
typenode *type4 = new typenode("pointer");
string var_name;
string fun_name;
bool flag = false;

typenode unsignednode("unsigned", 4);
typenode shortnode("short", 2);
typenode intnode("int", 4);
typenode longnode("long", 8);
typenode floatnode("float", 4);
typenode doublenode("double", 8);
typenode charnode("char", 1);
typenode voidnode("void");
typenode signednode("signed", 4);
typenode boolnode("bool", 1);
map<string, typenode *> auto_define_type;
stack<typenode *> struct_stack;

vector<string> v_argument_list;

struct varmap
{
    int name;
    varmap *parent;
    map<string, typenode *> vartable;
    varmap(int n = 0, varmap *p = NULL)
    {
        name = n;
        parent = p;
    }
};

varmap *varmap_temp;
vector<varmap *> s; //fuhao-table
struct node
{
    int id;
    string name;
    double dvalue;
    int length;
    node **children;
    typenode type;
    string code;
    varmap *args;
    node(string n = "")
    {
        length = 0;
        name = n;
    }
};

bool isComputable(string s)
{
    if (s == "int" || s == "float" || s == "double" ||
        s == "unsigned" || s == "signed" || s == "short" || s == "char")
        return true;
    else
        return false;
}

bool isInteger(string s)
{
    if (s == "int" || s == "unsigned" || s == "signed" || s == "short" || s == "char")
        return true;
    else
        return false;
}

typenode* create_struct(string name){
    int width_sum = 0;
    map<string, typenode*>::iterator iter;
    typenode *temp_ptr;
    typenode *temp1;
    typenode *temp2;
    typenode *temp3 = new typenode("?");
    for (iter = varmap_temp->vartable.begin(); iter != varmap_temp->vartable.end(); ++iter)
    {
        cout << iter->first << ' ' << iter->second->name << ' ';
        temp_ptr = new typenode(string(iter->first));
        typenode *root = new typenode("X");
        root->left = temp_ptr;
        root->right = iter->second;
        cout << iter->second->width << '%';
        width_sum += iter->second->width;
        struct_stack.push(root);
		}
		cout<<endl;
		while(struct_stack.size()>=1){
			cout<<struct_stack.size()<<endl;
			if(struct_stack.size() !=1){
				temp1 = struct_stack.top();struct_stack.pop();
				temp2 = struct_stack.top();struct_stack.pop();
				typenode* temp_ptr2 = new typenode("X");
				temp_ptr2->left = temp1;
				temp_ptr2->right = temp2;											
				struct_stack.push(temp_ptr2);				
			}
			else{
				temp3 = struct_stack.top();struct_stack.pop();
				break;
			}
		}
		typenode* temp = new typenode("record");
		temp->left = temp3;
        struct_width = temp->width = width_sum;
        traverse(temp);
		return auto_define_type[name] = temp;
}

typenode *search(string myname, int i)
{
    if (s[i]->vartable.count(myname) > 0)
    {
        // cout<<"s[i]->vartable[myname]"<<s[i]->vartable[myname]->name<<endl;
        cout<<myname<<" yes in "<<i<<endl;
        traverse(s[i]->vartable[myname]);
            //traverse_vartable(i);
            //traverse(s[i]->vartable[myname]);
        return s[i]->vartable[myname];
    }
    else
    {
        if (s[i]->vartable.count(myname) == 0 && i > 0)
        {
            //cout<<endl<<"not bottom!!!"<<endl;
            i--;
            return search(myname, i);
        }
        else{
            cout << "Cannot find " << myname<<"!"<<endl;
            return NULL;
        }
    }
}

void traverse_vartable(int i, string tab = "--")
{
        cout<<endl<<i<<tab<<endl;
        map<string, typenode*>::iterator iter;
		for(iter = s[i]->vartable.begin(); iter!=s[i]->vartable.end(); ++iter)
        {
            cout << iter->first << ' ' << iter->second->name << ' ' << iter->second->addr << ' ' << iter->second->width;
        }
        if(i>0){
            i--; 
            traverse_vartable(i, tab + "--");           
       }    
}
void wFlag(typenode &node)
{
    if (flag)
    {
        type2 = &node;
        flag = false;
    }
    else
    {
        type = &node;
        flag = true;
    }
}
typenode *rFlag()
{
    typenode *tmp = new typenode();
    if (flag == true)
    {
        (*tmp).copy(*type);
        //cout<<"tmp.name"<<tmp.name<<endl;
        //cout<<"tmp.left"<<tmp.left->name<<endl;
        return tmp;
    }
    else
    {
        (*tmp).copy(*type2);
        return tmp;
    }
}


// #define ERROR 0
// #define VOID 13
// #define MAIN 2
// #define LP 3
// #define RP 4
// #define LBRACE 5
// #define RBRACE 6
// #define TYPE 7
// #define ID 8
// #define SEMICOL 9
// #define FOR 10
// #define ASSIGN 11
// #define NUMBER 12
// #define COMPARISON 13
// #define ADD 14
// #define MINUS 15
// #define IF 16
// #define ANNOTATION 17
// #define MUTIPLY 18
// #define DIVIDE 19
// #define THEN 20
// #define BREAK 21
// #define CASE 22
// #define CONST 23
// #define CONTINUE 24
// #define DEFAULT 25
// #define DO 26
// #define ELSE 27
// #define ENUM 28
// #define EXTERN 29
// #define GOTO 30
// #define RETURN 31
// #define REGISTER 32
// #define SIGNED 33
// #define SIZEOF 34
// #define STATIC 35
// #define STRUCT 36
// #define SWITCH 37
// #define TYPEDEF 38
// #define UNION 39
// #define UNSIGNED 40
// #define VOLATILE 41
// #define WHILE 42
// #define COLON 43
// #define LITERAL 44
// #define LOGIC 45
// #define BOOLOP 46
// #define LSQUBRAC 47
// #define RSQUBRAC 48
string Words[] = {
    "ERROR", "VOID", "MAIN", "LP", "RP", "LBRACE", "RBRACE", "TYPE", "ID",
    "SEMICOL", "FOR", "ASSIGN", "NUMBER", "COMPARISON", "ADD", "MINUS", "IF",
    "ANNOTATION", "MUTIPLY", "DIVIDE", "THEN", "BREAK", "CASE", "CONST",
    "CONTINUE", "DEFAULT", "DO", "ELSE", "ENUM", "EXTERN", "GOTO", "RETURN",
    "REGISTER", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDE",
    "UNION ", "UNSIGN", "VOLATI", "WHILE", "COLON", "LITERAL", "LOGIC",
    "BOOLOP", "LSQUBRAC", "RSQUBRAC"};
struct Symbol
{
    Symbol(int word, string element, int line, void *value = NULL) : word(word), element(element), value(value), line(line)
    {
        if (value)
            value = new string(element);
    }
    int word;
    string element;
    void *value;
    int line;
};
vector<Symbol> symbols;
// void reserve(int word, string element, int line = Line)
// {
//     for (int i = 0; i < symbols.size(); i++)
//         if (symbols[i].element == element)
//         {

//             return;
//         }
//     switch (word)
//     {
//     case ID:
//         symbols.push_back(Symbol(word, element, line));
//         symbols.back().value = &symbols.back().value;
//         return;
//     case NUMBER:
//     case LITERAL:
//         symbols.push_back(Symbol(word, element, line, &element));
//         return;
//     default:
//         return;
//     }
// }
#endif