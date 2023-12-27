#include "symbolTable.h"


   

void pointerPrintNothing(void *data)
{
}
   
void pointerPrintAddr(void *data)
{
    printf("0x%016llx ", (unsigned long long int)(data));
}
   
void pointerPrintLongInteger(void *data)
{
    printf("%18lld ", (unsigned long long int)(data));
}
   
void pointerPrintStr(void *data)
{
    printf("%s ", (char *)(data));
}


Scope::Scope(std::string newname) {
    name = newname;
    debugFlg = false;
}


Scope::~Scope() {
}

std::string Scope::scopeName() {
    return name;
}

void Scope::debug(bool state) {
    debugFlg = state;
}


void Scope::print(void (*printData)(void *)) {
    printf("Scope: %-15s -----------------\n", name.c_str());
    for (std::map<std::string , void *>::iterator it=symbols.begin(); it!=symbols.end(); it++) {
        printf("%20s: ", (it->first).c_str());
        printData(it->second);
        printf("\n");
    }
    
}


void Scope::applyToAll(void (*action)(std::string , void *)) {
    for (std::map<std::string , void *>::iterator it=symbols.begin(); it!=symbols.end(); it++) {
        action(it->first, it->second);
    }
}


bool Scope::insert(std::string sym, void *ptr) {
    if (symbols.find(sym) == symbols.end()) {
        if (debugFlg) printf("DEBUG(Scope): insert in \"%s\" the symbol \"%s\".\n",
                             name.c_str(),
                             sym.c_str());
        if (ptr==NULL) {
            printf("ERROR(SymbolTable): Attempting to save a NULL pointer for the symbol '%s'.\n",
                   sym.c_str());
        }
        symbols[sym] = ptr;
        return true;
    }
    else {
        if (debugFlg) printf("DEBUG(Scope): insert in \"%s\" the symbol \"%s\" but symbol already there!\n", name.c_str(), sym.c_str());
        return false;
    }
}

void *Scope::lookup(std::string sym) {
    if (symbols.find(sym) != symbols.end()) {
        if (debugFlg) printf("DEBUG(Scope): lookup in \"%s\" for the symbol \"%s\" and found it.\n", name.c_str(), sym.c_str());
        return symbols[sym];
    }
    else {
        if (debugFlg) printf("DEBUG(Scope): lookup in \"%s\" for the symbol \"%s\" and did NOT find it.\n", name.c_str(), sym.c_str());
        return NULL;
    }
}

bool Scope::debugFlg;





SymbolTable::SymbolTable()
{
    debugFlg = false;
    enter((std::string )"Global");
}


void SymbolTable::debug(bool state)
{
    debugFlg = state;
}


int SymbolTable::depth()
{
    return stack.size();
}


void SymbolTable::print(void (*printData)(void *))
{
    printf("===========  Symbol Table  ===========\n");
    for (std::vector<Scope *>::iterator it=stack.begin(); it!=stack.end(); it++) {
        (*it)->print(printData);
    }
    printf("===========  ============  ===========\n");
}


void SymbolTable::enter(std::string name)
{
    if (debugFlg) printf("DEBUG(SymbolTable): enter scope \"%s\".\n", name.c_str());
    stack.push_back(new Scope(name));
}


void SymbolTable::leave()
{
    if (debugFlg) printf("DEBUG(SymbolTable): leave scope \"%s\".\n", (stack.back()->scopeName()).c_str());
    if (stack.size()>1) {
        delete stack.back();
        stack.pop_back();
    }
    else {
        printf("ERROR(SymbolTable): You cannot leave global scope.  Number of scopes: %d.\n", (int)stack.size());
    }
}


void * SymbolTable::lookup(std::string sym)
{
    void *data;
    std::string name;

    data = NULL;      for (std::vector<Scope *>::reverse_iterator it=stack.rbegin(); it!=stack.rend(); it++) {
        data = (*it)->lookup(sym);
        name = (*it)->scopeName();
        if (data!=NULL) break;
    }

    if (debugFlg) {
        printf("DEBUG(SymbolTable): lookup the symbol \"%s\" and ", sym.c_str());
        if (data) printf("found it in the scope named \"%s\".\n", name.c_str());
        else printf("did NOT find it!\n");
    }

    return data;
}


void * SymbolTable::lookupGlobal(std::string sym)
{
    void *data;

    data = stack[0]->lookup(sym);
    if (debugFlg) printf("DEBUG(SymbolTable): lookup the symbol \"%s\" in the Globals and %s.\n", sym.c_str(),
                         (data ? "found it" : "did NOT find it"));

    return data;
}


bool SymbolTable::insert(std::string sym, void *ptr)
{
    if (debugFlg) {
        printf("DEBUG(symbolTable): insert in scope \"%s\" the symbol \"%s\"",
               (stack.back()->scopeName()).c_str(), sym.c_str());
        if(ptr==NULL) printf(" WARNING: The inserted pointer is NULL!!");
        printf("\n");
    }

    return (stack.back())->insert(sym, ptr);
}


bool SymbolTable::insertGlobal(std::string sym, void *ptr)
{
    if (debugFlg) {
        printf("DEBUG(Scope): insert the global symbol \"%s\"", sym.c_str());
        if(ptr==NULL) printf(" WARNING: The inserted pointer is NULL!!");
        printf("\n");
    }

    return stack[0]->insert(sym, ptr);
}


// Apply function to each simple in the local scope.   The function gets both the
// string and the associated pointer.
void SymbolTable::applyToAll(void (*action)(std::string , void *))
{
    stack[stack.size()-1]->applyToAll(action);
}


// Apply function to each simple in the global scope.   The function gets both the
// string and the associated pointer.
void SymbolTable::applyToAllGlobal(void (*action)(std::string , void *))
{
    stack[0]->applyToAll(action);
}




// // // // // // // // // // // // // // // // // // // // 
//
// Some tests
//


std::string words[] = {"alfa", "bravo", "charlie", "dog", "echo", "foxtrot", "golf"};
int wordsLen = 7;



int counter;
void countSymbols(std::string sym, void *ptr) {
    counter++;
    printf("%d %20s: ", counter, sym.c_str());
    pointerPrintAddr(ptr);
    printf("\n");
 }



/*
int main()
{
    Scope s("global");

    s.debug(true);
    s.insert("dog", (char *)"woof");
    s.insert("cat", (char *)"meow");
    printf("%s\n", (char *)(s.lookup("cat")));
    printf("%s\n", (char *)(s.lookup("dog")));

    if (s.lookup("fox")==NULL) printf("not found\n");
    else printf("found\n");
    s.print(pointerPrintAddr);
    s.print(pointerPrintStr);

    SymbolTable st;
    st.debug(true);

    printf("Print symbol table.\n");
    st.print(pointerPrintStr);
    st.insert("alfa", (char *)"ant"); 
    st.insert("bravo", (char *)"bat"); 
    st.insert("charlie", (char *)"cob"); 

    st.enter("First");
    st.insert("charlie", (char *)"cow"); 
    st.enter((std::string )"Second");
    st.insert("delta", (char *)"dog"); 
    st.insertGlobal("echo", (char *)"elk"); 

    printf("Print symbol table.\n");
    st.print(pointerPrintStr);


    printf("This is how you might use insert and lookup in your compiler.\n");
    st.leave();    // second no longer exists
    st.enter((std::string )"Third");
    if (st.insert("charlie", (char *)"cat")) printf("success\n"); else  printf("FAIL\n");
    if (st.insert("charlie", (char *)"pig")) printf("success\n"); else  printf("FAIL\n"); 
    if (st.lookup("charlie")) printf("success\n"); else  printf("FAIL\n"); 
    if (st.lookup("mirage")) printf("success\n"); else  printf("FAIL\n"); 

    printf("Print symbol table.\n");
    st.print(pointerPrintStr);
    fflush(stdout);

    printf("\nGeneral Lookup\n");
    for (int i=0; i<wordsLen; i++) {
        void *data;

        if ((data = st.lookup(words[i]))==NULL) printf("%s: %s\n", words[i].c_str(), (char *)"NULL");
        else printf("%s: %s\n", words[i].c_str(), (char *)data);
    }

    printf("\nGlobal Lookup\n");
    for (int i=0; i<wordsLen; i++) {
        void *data;

        if ((data = st.lookupGlobal(words[i]))==NULL) printf("%s: %s\n", words[i].c_str(), (char *)"NULL");
        else printf("%s: %s\n", words[i].c_str(), (char *)data);
    }

    printf("Test that apply works.\n");
    counter = 0;
    st.applyToAllGlobal(countSymbols);
    printf("Number of global symbols: %d\n", counter);

    st.insert((char *)"gnu", (char *)"goat");
    st.lookup((char *)"gnu");

    st.insertGlobal((char *)"gnu", (char *)"grebe");
    st.lookup((char *)"gnu");
    st.lookupGlobal((char *)"gnu");

    return 0;
}
*/



