#ifndef STATEMENTNODES_HPP
#define STATEMENTNODES_HPP

#include "Node.hpp"

class Break : public Node
{
    public :
        Break(const int tokenLineNumber);

        std::string printTokenString() const;
};

class Compound : public Node
{
    public :

        Compound(const int tokenLineNumber);

        std::string printTokenString() const;
};


class For : public Node
{
    public :

        For(const int tokenLineNumber);

        std::string printTokenString() const;
};

class If : public Node
{
    public :

        If(const int tokenLineNumber);

        std::string printTokenString() const;
};


class Range : public Node
{
    public :

        Range(const int tokenLineNumber);

        std::string printTokenString() const;
};

class Return: public Node
{
    public :

        Return(const int tokenLineNumber);

        std::string printTokenString() const;
};

class While : public Node
{
    public :

        While(const int tokenLineNumber);

        std::string printTokenString() const;
};

#endif