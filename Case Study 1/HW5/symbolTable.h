#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

void pointerPrintNothing(void *data);
void pointerPrintAddr(void *data);
void pointerPrintLongInteger(void *data);
void pointerPrintStr(void *data);





class Scope {
private:
    static bool debugFlg;                          std::string name;                              std::map<std::string , void *> symbols;
public:
    Scope(std::string newname);
    ~Scope();
    std::string scopeName();                       void debug(bool state);                        void print(void (*printData)(void *));         void applyToAll(void (*action)(std::string , void *));      bool insert(std::string sym, void *ptr);                                                      void *lookup(std::string sym);                                                            };




class SymbolTable {
private:
    std::vector<Scope *> stack;
    bool debugFlg;

public:
    SymbolTable();
    void debug(bool state);                              int depth();                                         void print(void (*printData)(void *));               void enter(std::string name);                        void leave();                                        void *lookup(std::string sym);                                                                            void *lookupGlobal(std::string sym);                                                                      bool insert(std::string sym, void *ptr);                                                                  bool insertGlobal(std::string sym, void *ptr);                                                            void applyToAll(void (*action)(std::string , void *));            void applyToAllGlobal(void (*action)(std::string , void *));  };

#endif
