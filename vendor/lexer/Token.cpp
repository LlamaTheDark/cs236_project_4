#include "Token.h"
#include <utility>
#include <sstream>

const std::string Token::serializedTokens[] = {
        "COMMA",
        "PERIOD",
        "Q_MARK",
        "LEFT_PAREN",
        "RIGHT_PAREN",
        "COLON",
        "COLON_DASH",
        "MULTIPLY",
        "ADD",
        "SCHEMES",
        "FACTS",
        "RULES",
        "QUERIES",
        "ID",
        "STRING",
        "COMMENT",
        "UNDEFINED",
        "EOF"
};

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = std::move(description);
    this->line = line;
}

TokenType Token::getType() const {
    return this->type;
}

std::string Token::getDescription() const {
    return this->description;
}

int Token::getLine() const {
    return this->line;
}

std::string Token::toString(bool err=false) const {
    std::ostringstream s;
    if(err)
        s << "(" << *this << ",\"" << this->getDescription() << "\"," << this->getLine() << ")";
    else
        s << *this;
    return s.str();
}

std::ostream &operator<<(std::ostream &out, const Token &token) {
    out << Token::serializedTokens[static_cast<int>(token.type)];
    return out;
}