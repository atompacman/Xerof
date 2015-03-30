#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "easylogging++.h"
#include "rapidjson\document.h"
#include "rapidjson\error\en.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "FatalErrorDialog.h"
/*============================================================================||
| Shortcuts for JSON value verification and extraction
|-----------------------------------------------------------------------------||
| - JSON file parsing
| - Node extraction
\=============================================================================*/

using namespace rapidjson;

static Value& parseJSON(Document&   o_Doc,
                        const char* i_JSONFile,
                        const char* i_RootElemName)
{
    // Open file
    std::ifstream file(i_JSONFile);
    if (file.bad()) {
        std::stringstream ss;
        ss << "Could not find JSON file \"" << i_JSONFile << "\"";
        FatalErrorDialog(ss.str());
    }

    // Extract its content as a string
    std::string content((std::istreambuf_iterator<char>(file)),
        (std::istreambuf_iterator<char>()));

    // Parse the JSON DOM
    o_Doc.Parse(content.c_str());
    ParseErrorCode code(o_Doc.GetParseError());
    if (code != kParseErrorNone) {
        std::stringstream ss;
        ss << "File " << i_JSONFile << " is not a valid JSON file: "
            << GetParseError_En(code) << " at " << o_Doc.GetErrorOffset();
        FatalErrorDialog(ss.str());
    }

    // Check if it contains the root elem
    if (!o_Doc.HasMember(i_RootElemName)) {
        std::stringstream ss;
        ss << "JSON file \"" << i_JSONFile << "\" root element is not \"" 
            << i_RootElemName << "\"";
        FatalErrorDialog(ss.str());
    }

    // Return document's root element
    return o_Doc[i_RootElemName];
}

static const Value& getSubElem(const Value& i_Value, const char* i_Elem)
{
    if (!i_Value.HasMember(i_Elem)) {
        std::stringstream ss;
        ss << "Invalid map configuration file: Missing \"" <<
            i_Elem << "\" element";
        FatalErrorDialog(ss.str());
    }
    return i_Value[i_Elem];
}

static UINT getUINT(const Value& i_Value, const char* i_Elem)
{
    const Value& subElem(getSubElem(i_Value, i_Elem));
    if (!subElem.IsUint()) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem <<
            "\" value should be an unsigned integer";
        FatalErrorDialog(ss.str());
    }
    return subElem.GetUint();
}

static double getDouble(const Value& i_Value, const char* i_Elem)
{
    const Value& subElem(getSubElem(i_Value, i_Elem));
    if (!subElem.IsNumber()) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem <<
            "\" value should be a real number";
        FatalErrorDialog(ss.str());
    }
    return subElem.GetDouble();
}

static double getNormDouble(const Value& i_Value, const char* i_Elem)
{
    double value(getDouble(i_Value, i_Elem));
    if (value < 0 || value > 1.0) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem <<
            "\" value should be a real number between 0 and 1";
        FatalErrorDialog(ss.str());
    }
    return value;
}