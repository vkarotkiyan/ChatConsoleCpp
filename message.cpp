#include <string>
#include <ctime>
#include "message.h"
#include "misc.h"
using namespace  std;

// Message ////////////////////////////////////////////////////////////////////
Message::Message(const string& text, const string& from, const string& to, const time_t& dateTime) :
    _text(text), _from(from), _to(to), _dateTime(dateTime) {
}

const string& Message::getText() const {
    return _text;
}

const string& Message::getFrom() const {
    return _from;
}

const string& Message::getTo() const {
    return _to;
}

const std::time_t& Message::getTime() const
{
    return _dateTime;
}
