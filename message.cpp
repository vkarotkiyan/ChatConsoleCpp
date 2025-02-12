#include <string>
#include "message.h"
using namespace  std;

// Message ////////////////////////////////////////////////////////////////////
Message::Message(const std::string& text, const std::string& from, const std::string& to) : 
    _text(text), _from(from), _to(to){ }
const std::string& Message::getText() const {
    return _text;
}
const std::string& Message::getFrom() const {
    return _from;
}
const std::string& Message::getTo() const {
    return _to;
}

