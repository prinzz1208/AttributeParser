#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define fop first
#define sop second
#define ll long long int
#define vi vector<ll>
#define vs vector<string>
#define print(a) cout << a

#define sync ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define test(string,a) cout<<string<<a

#define FEI(el,s) for(int el : s)
#define FOR(index,a,n) for (ll index = a; index < n; index++)
#define FORD(index,a,n) for (ll index = a; index >= n; index--)
#define NL cout<<"\n"
#define TAB '\t'


struct Tag {
	string tagName;
	vector<pair<string,string>> attributes;
	Tag* next;
};

enum Flags {
	TagFlag,
	AttrFlag,
	ValueFlag,
	ClosingTagFlag,
	NoFlag
};


class AttributeParser {
	public:
		
		Flags flag = NoFlag;
		Tag* headTag = NULL;
		Tag* currentTag;
		stack<Tag*> tagStack;
		vector<Tag*> tagList;
		
		// parse one line at a time
		void parse(string line){
			//test("Inside Parse line:",line);
			//NL;
			string temp = "";
			string tag, attr, value;
			vector<pair<string,string>> attributes;
			for(char s: line){				
				switch(s){
					case '<':
						flag = TagFlag;
						break;
					
					case ' ':
						if(flag == TagFlag) {
							tag = temp;
							//test("tag:",tag);
							//NL;
							temp = "";
							flag = AttrFlag;
						}
						else if(flag == NoFlag) {
							flag = AttrFlag;
						}
						
						break;

					case '=':
						break;
						
					case '"':
						if(flag == AttrFlag) {
							attr = temp;
							//test("attr:",attr);
							//NL;


							temp = "";
							flag = ValueFlag;								
						}
						else if(flag == ValueFlag) {
							value = temp;
							temp = "";
							//test("value:",value);							
							//NL;
							
							attributes.pb(mk(attr,value));	
	
							resetFlag();
						}
						break;
						
					case '>':
						if(flag == NoFlag){							
							currentTag = new Tag();
							currentTag->tagName = tag;
							currentTag->attributes = attributes;
							if(headTag == NULL){
								headTag = currentTag;
							}
							tagStack.push(currentTag);
							resetFlag();
						}
						else if(flag == ClosingTagFlag){
							
							
							Tag* topTag = tagStack.top();
							tagStack.pop();
							if(!tagStack.empty()){
								Tag* topTag2 = tagStack.top();
								topTag2->next = topTag;
							}
							if(tagStack.empty()){
								tagList.pb(topTag);
							}														
							resetFlag();
						}
						break;
					
					case '/':
						flag = ClosingTagFlag;
						break;
					default:
						temp+=s;
				}
				
				
			}
			
		}
		
		// parse one query at a time
		void parseQueryAndPrintResult(string line){
			
			string temp = "";
			//test("Inside Parse Query line:",line);
			//NL;
			queue<string> chainTags;
			resetFlag();
			for(char s: line) {
				switch(s){
					case '.': {
						chainTags.push(temp);
						temp = "";
						break;
					}
					case '~': {
						chainTags.push(temp);
						temp = "";
						break;
					}
					
					default:
						temp+=s;
				}
			}
			string value = temp;
			printQueryResult(chainTags,value);
		}
		
		void printQueryResult(queue<string> chainTags, string value) {
			string currentTagName = "";
			Tag* currentTag = NULL;
			
			
			while(!chainTags.empty()){
				currentTagName = chainTags.front(); 
				//test("currentTagName:",currentTagName);
				//NL;
				chainTags.pop();
				if(currentTag == NULL){
					// to find tag from tagList
					for( Tag* temp: tagList){
						if(temp->tagName == currentTagName){
							currentTag = temp;
							break;
						}
					}				
				}else{
					if(currentTag->next == NULL || currentTag->next->tagName != currentTagName){
						NL;
						print("Not Found!");
						return;
					}else{
						currentTag = currentTag->next;
					}
				}
			}
			if(currentTag != NULL) {
				string ans = "";
				for(pair<string,string> p : currentTag->attributes){
					//NL;
					//test("attributes:",p.fop);
					//NL;
					if(p.fop == value){
						ans = p.sop;
						break;
					}
					
				}
				//vector<pair<string,string>>::iterator it = find_if(currentTag->attributes.begin(),currentTag->attributes.end(),[&value] (const pair<string,string> s) { return s.fop == value; } );
				//cout<<it;		
				NL;
				if(ans != ""){
					print(ans);
				}else{
					print("Not Found!");
				}
			}	
		}
		
		void resetFlag() {
			flag = NoFlag;
		}
};


int main(){
	
	AttributeParser ap;
	string input,input2;
	int n,q;
	cin >> n;
	cin >> q;
	getline(cin,input);
	//cin >> input;
	while(n-- && getline(cin,input)){
		ap.parse(input);
	}
	//NL;
	//if(ap.headTag != NULL) {
		//print(ap.headTag->tagName);
	//}
	//NL;
	while(q--){
		getline(cin,input2);
		ap.parseQueryAndPrintResult(input2);
	}
	
	
}

