#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<algorithm>

using namespace std;
const int MAX_SIZE = 26;
const int CASE = 'a';

class node{
    public:
        node *parent =NULL;
        node *children[MAX_SIZE]={};
        int occurrences;
        bool isWord;
        string meaning;
        string synonyms;
        string antonyms;
};

class DictionaryTrie{
    private:
        node *trie;


    public:
    int count;
    
	DictionaryTrie(){
	    trie=new node;
    	count=0;
}

    void InsertWord(const char* word, string mean, string syn, string ant){
    node *curr=trie;

    while(*word!='\0'){
        if(curr->children[*word-CASE]==NULL){
            curr->children[*word-CASE]=new node();
            curr->children[*word-CASE]->parent=curr;
}

        curr=curr->children[*word-CASE];
        ++word;
    }

    ++curr->occurrences;
    if(curr->occurrences==1){
            count++;
}
    curr->isWord=true;
    curr->meaning=mean;
    curr->synonyms=syn;
    curr->antonyms=ant;
}

	node* SearchMe(const char* word){
    node *curr=Search(trie,word);
    return curr;
}

    node* Search(node* T,const char* word){
    while(*word!='\0'){
        if(T->children[*word-CASE]!=NULL){
            T=T->children[*word-CASE];
            ++word;
        }
        else return NULL;

    }
    return (T->isWord)?T:NULL;
}


    void DeleteWord(const char* word,string str){
    node *curr=Search(trie,word);

    if(curr!=NULL){

            string sent;
            ifstream inFile("Dictionary.txt");
            ofstream outFile("OutFile.txt");
            while(getline(inFile,sent)){
                if(sent!=str)
                if(sent!=curr->meaning)
                if(sent!=curr->synonyms)
                if(sent!=curr->antonyms)
                    outFile<<sent<<"\n";
            }
            inFile.close();
            outFile.close();
            remove("Dictionary.txt");
            rename("Outfile.txt","Dictionary.txt");
   
            count--;
            curr->isWord=false;
            --curr->occurrences;
            node *par=NULL;
            bool IsLeaf=true;

            for(int i=0;i<MAX_SIZE;i++){
                if(curr->children[i]!=NULL){
                    IsLeaf=false;
                    break;
    }
        }

            while(curr->parent!=NULL&&IsLeaf&&(!curr->isWord)){
                par=curr->parent;
                for(int i=0;i<MAX_SIZE;i++){
                    if(par->children[i]==curr){
                        par->children[i]=NULL;
                        delete curr;
                        curr=par;
            }
                    else if(par->children[i]!=NULL){
                        IsLeaf=false;
                        break;
                }
            }
            }
        }
        else
            cout<<"Word is not here."<<endl;
}

};

void titledisplay(){
	cout<<"\t\t\t    --------------------------------"<<endl;
	cout<<"\t\t\t\t***DIGITAL DICTIONARY***"<<endl;
	cout<<"\t\t\t    --------------------------------"<<endl;

}

bool ValidWord(string word){
    int i=0;
    while(word[i]){
        if(!isalpha(word[i]))
            return false;
        i++;
    }
    return true;
}

const char* convertString(string str){
    const char *S=str.c_str();
    return S;
}


void InsertNewWord(DictionaryTrie &tree){
    system("cls");
    titledisplay();
    string word,meaning,synonyms,antonyms;
    string temp;
    getline(cin,temp);

    f:
    cout<<"Enter new word:";
    getline(cin,word,'\n');


    if(!ValidWord(word)){
        system("cls");
        cout<<"Word contains invalid characters"<<endl;
        goto f;
    }
    //transforms full string to lowercase
    transform(word.begin(), word.end(), word.begin(),::tolower);
       
	cout<<"Enter meaning:";
    getline(cin,meaning,'\n');

    cout<<"Enter Synonyms:";
    getline(cin,synonyms,'\n');

    cout<<"Enter Antonyms:";
    getline(cin,antonyms,'\n');


    if(tree.SearchMe(convertString(word))==NULL){
        tree.InsertWord(convertString(word),meaning,synonyms,antonyms);
        cout<<"Word has been added to dictionary."<<endl;
		cout<<"Press any key to return ";
		cin.ignore();
		cin.get();
		system("cls");
		titledisplay();
        
        ofstream inFile;
        inFile.open("Dictionary.txt", fstream::app);
        inFile << word <<"\n"<< meaning <<"\n"<< synonyms <<"\n"<< antonyms <<endl;
        inFile.close();
}
    else{
    	cout<<"Word already exists in dictionary."<<endl;
    	cout<<"Press any key to return ";
		cin.ignore();
		cin.get();

    	system("cls");
		titledisplay();
    	
    	
	}

}


void History(string word){
    
    ofstream outFile;
    outFile.open("History.txt",fstream::app);
    outFile<<word<<endl;
    outFile.close();
}

void SearchHistory(){
    system("cls");
    titledisplay();
    string word;
    cout<<"History:"<<endl;
    cout<<"---------------- "<<endl;
    ifstream inFile("History.txt");
    while(inFile>>word){
        cout<<word<<endl;
    }
    inFile.close();
    cout<<"---------------- "<<endl;
    cout<<"Press any key to return"<<endl;
    cin.ignore();
    cin.get();
    system("cls");
    //return;
}

void WordCount(DictionaryTrie &T){
    system("cls");
    titledisplay();
    cout<<"Total number of words:"<<T.count<<endl;
    cout<<"-------------------------"<<endl;
    cout<<"Press any key to return ";
    cin.ignore();
    cin.get();
    system("cls");
    titledisplay();
}

void NoOfWords(DictionaryTrie &T){
    ofstream outFile("No Of Words.txt");
    outFile<<T.count<<endl;
    outFile.close();
}

void SearchWord(DictionaryTrie &tree){
    system("cls");
    titledisplay();
    node* N;
    string word;
    f:
    cout<<"Search a word meaning:";
    cin>>word;

    if(!ValidWord(word)){
        system("cls");
        cout<<"Word contains invalid characters"<<endl;
        goto f;
    }
    //transforms full string to lowercase
    transform(word.begin(), word.end(), word.begin(),::tolower);

    N=tree.SearchMe(convertString(word));
    if(N!=NULL){

        History(word);

        cout <<"Meaning:"<<N->meaning<<endl;
        cout<<"Synonyms:"<<N->synonyms<<endl;
		cout<<"Antonyms:"<<N->antonyms<<endl;
		cout<<"-----------------------------\n"<<endl;
		cout<<"Press any key to return ";
		cin.ignore();
		cin.get();
		system("cls");
		titledisplay();
}
    else
    {
		cout<<"Word doesn't exist in dictionary."<<endl;
		cout<<"Press any key to return ";
		cin.ignore();
		cin.get();
		    	
        system("cls");
        titledisplay();
        
    }



}


void DeleteWord(DictionaryTrie &T){
    system("cls");
    titledisplay();
    string word,temp;
    f:
    cout<<"Enter the word to delete:"<<endl;
    cin>>word;

    if(!ValidWord(word)){
        system("cls");
        cout<<"Word contains invalid characters"<<endl;
        goto f;
    }
    //transforms full string to lowercase
    transform(word.begin(),word.end(),word.begin(),::tolower);
    
    T.DeleteWord(convertString(word),word);
    system("cls");
    cout<<"The word has been deleted."<<endl;

}

int main(){
    vector<char> word;
    string str,meaning,synonyms,antonyms;
    DictionaryTrie T;
    int num,ch;
    bool x=true;

    ifstream inFile("No Of Words.txt");
    inFile>>num;
    inFile.close();

    ifstream inFile1("Dictionary.txt");
    for(int i=0;i<num;i++){
        getline(inFile1,str);
        getline(inFile1,meaning);
        getline(inFile1,synonyms);
        getline(inFile1,antonyms);
        T.InsertWord(convertString(str),meaning,synonyms,antonyms);
    }
    inFile1.close();
	titledisplay();
    while(x){
        cout<<"_________________________________"<<endl;
		cout<<"\n---------Dictionary Menu---------"<<endl;
		cout<<"1) Search word meaning"<<endl;
		cout<<"2) Insert a word in dictionary"<<endl;
		cout<<"3) Delete a word from dictionary"<<endl;
		cout<<"4) View search history"<<endl;
		cout<<"5) Total number of words in dictionary"<<endl;
		cout<<"6) Exit"<<endl;
		cout<<"_________________________________"<<endl;	
		cout<<"Type any number from the menu above to view the options:";
        cin>>ch;
        switch(ch){
        case 1:
            SearchWord(T);
            break;
            
        case 2:
            InsertNewWord(T);
            break;
            
        case 3:
            DeleteWord(T);
            break;

        case 4:
            SearchHistory();
            break;

        case 5:
            WordCount(T);
            break;

        case 6 :
            x=false;
		
        NoOfWords(T);
        
        }
    }
}
