#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>


enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    FILE_END,
};

class Token {
private:
    static const std::string serializedTokens[];
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType type, std::string description, int line);

    TokenType getType() const;
    std::string getDescription() const;
    int getLine() const;

    std::string toString(bool) const;
    friend std::ostream &operator<<(std::ostream &out, const Token &token);
};

#endif // TOKEN_H

