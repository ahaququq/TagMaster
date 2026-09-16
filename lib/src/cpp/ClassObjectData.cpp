#include "ClassObjectData.hpp"

#include <sstream>
#include "ClassDef.hpp"
#include "Native/StringData.hpp"
#include "Utils/Text.hpp"

ClassObjectData::ClassObjectData() {

}

std::vector<ClassObjectData::FieldValue> ClassObjectData::getNamed(const ClassRef& type) const {
    std::vector<FieldValue> out;

    ClassDef def = type.getDefinition();

    for (int i = 0; i < def.named.size(); i++) {
        ClassRef type = def.named[i].type;
        Object value = Object(StringData("[Missing Default]"));
        if (named.size() > i && named[i]) value = *named[i];
        else if (def.named[i].def) value = *def.named[i].def;
        out.emplace_back(FieldValue{def.named[i].name, type, value});
    }

    return out;
}

std::string ClassObjectData::toString(const ClassRef& type, int indent) const {
    std::ostringstream os;

    os << type.getName();

    std::vector<FieldValue> fields = getNamed(type);

    if (!fields.empty()) {
        os << "(\n";
        for (auto field : fields) {
            os << ind(indent) << "var " << field.name;
            os << ": " << field.type.getName() << " = ";
            os << field.value.toString(field.type, indent + 1) << "\n";
        }
        os << ind(indent - 1) << ")";
    }


    return os.str();
}

ClassObjectData& ClassObjectData::operator+(Object value) {
    named.emplace_back(value);
    return *this;
}

ClassObjectData& ClassObjectData::operator+(std::nullptr_t) {
    named.emplace_back();
    return *this;
}