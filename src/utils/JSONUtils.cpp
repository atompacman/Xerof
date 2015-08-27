#include <easylogging++.h>
#include <Environment.h>
#include <FatalErrorDialog.h>
#include <JSONUtils.h>
#include <rapidjson\document.h>
#include <rapidjson\error\en.h>

using namespace rapidjson;

Value& parseJSON(Document&          o_Doc,
                 const std::string& i_JSONFile,
                 const std::string& i_RootElemName)
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
    if (!o_Doc.HasMember(i_RootElemName.c_str())) {
        std::stringstream ss;
        ss << "JSON file \"" << i_JSONFile << "\" root element is not \""
            << i_RootElemName << "\"";
        FatalErrorDialog(ss.str());
    }

    // Return document's root element
    return o_Doc[i_RootElemName.c_str()];
}

const Value& parseSubElem(const Value& i_Value, const std::string& i_Elem)
{
    if (!i_Value.HasMember(i_Elem.c_str())) {
        std::stringstream ss;
        ss << "Invalid JSON file: Missing \"" << i_Elem << "\" element";
        FatalErrorDialog(ss.str());
    }
    return i_Value[i_Elem.c_str()];
}

unsigned int parseUINT(const Value& i_Value, const std::string& i_Elem)
{
    const Value& subElem(parseSubElem(i_Value, i_Elem));
    if (!subElem.IsUint()) {
        std::stringstream ss;
        ss <<"Parameter \"" <<i_Elem <<"\" value should be an unsigned integer";
        FatalErrorDialog(ss.str());
    }
    return subElem.GetUint();
}

double parseDouble(const Value& i_Value, const std::string& i_Elem)
{
    const Value& subElem(parseSubElem(i_Value, i_Elem));
    if (!subElem.IsNumber()) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem << "\" value should be a real number";
        FatalErrorDialog(ss.str());
    }
    return subElem.GetDouble();
}

double parseNormDouble(const Value& i_Value, const std::string& i_Elem)
{
    double value(parseDouble(i_Value, i_Elem));
    if (value < 0 || value > 1.0) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem <<
            "\" value should be a real number between 0 and 1";
        FatalErrorDialog(ss.str());
    }
    return value;
}

const std::string parseString(const Value& i_Value, const std::string& i_Elem)
{
    const Value& subElem(parseSubElem(i_Value, i_Elem));
    if (!subElem.IsString()) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem << "\" value should be a string";
        FatalErrorDialog(ss.str());
    }
    return subElem.GetString();
}

Biome parseBiome(const Value& i_Value, const std::string& i_Elem)
{
    auto it(STR_TO_BIOME.find(parseString(i_Value, i_Elem)));
    if (it == STR_TO_BIOME.end()) {
        std::stringstream ss;
        ss << "Parameter \"" << i_Elem << "\" is not a valid environment";
        FatalErrorDialog(ss.str());
    }
    return it->second;
}
