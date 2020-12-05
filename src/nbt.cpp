#include "nbt.hpp"
#include "tag.hpp"
#include "stde/streams/data.hpp"
#include "stde/streams/gzip.hpp"
#include "nbtexception.hpp"

#include <iostream>

using namespace nbtpp;
using namespace stde;

nbt::nbt(std::istream& in) : nbt() {
    load(in);
}

nbt::nbt(std::ifstream& in) : nbt() {
    load(in);
}

nbt::~nbt() {
    if (m_tag != nullptr) {
        delete m_tag;
        m_tag = nullptr;
    }
}

void nbt::load(std::ifstream& in) {
    int pos = in.tellg();
    try {
        streams::gzip_istream g(in);

        m_compressed = true;
        load((std::istream&) g);

    } catch (streams::gzip_exception &e) {
        in.clear();
        in.seekg(pos);

        m_compressed = false;
        load((std::istream&) in);
    }
}

void nbt::load(std::istream& in) {
    if (m_tag != nullptr) {
        delete m_tag;
        m_tag = nullptr;
    }

    m_tag = load_internal(in);
}

tag* nbt::load_internal(std::istream& in) {
    streams::data_istream di(in, streams::endianconv::big);
    di.exceptions(std::ios_base::badbit);

    type tag_type = (type) di.readUnsignedByte();

    if (tag_type == type::TAG_End)
        return new tags::tag_end();

    std::string tag_name = di.readUTF();

    switch (tag_type) {
        case type::TAG_String: {
            std::string value = di.readUTF();
            return new tags::tag_string(tag_name, value);
        }
        case type::TAG_Compound: {
            tag *t;
            tags::tag_compound *comp = new tags::tag_compound(tag_name);
            while (1) {
                t = load_internal(in);
                if (t->getType() == type::TAG_End) {
                    delete t;
                    break;
                }
                comp->insert(t);
            }
            return comp;
        }
        default: {
            throw nbt_exception("invalid tag type " + tag_type);
            tag_type = type::TAG_Undef;
        }
    }

    return new tag(tag_name, tag_type);
}

std::string name_for_type(type t) {
    switch (t) {
        case type::TAG_Byte:
            return "TAG_Byte";
        case type::TAG_Byte_Array:
            return "TAG_Byte_Array";
        case type::TAG_Compound:
            return "TAG_Compound";
        case type::TAG_Double:
            return "TAG_Double";
        case type::TAG_End:
            return "TAG_End";
        case type::TAG_Float:
            return "TAG_Float";
        case type::TAG_Int:
            return "TAG_Int";
        case type::TAG_Int_Array:
            return "TAG_Int_Array";
        case type::TAG_List:
            return "TAG_List";
        case type::TAG_Long:
            return "TAG_Long";
        case type::TAG_Long_Array:
            return "TAG_Long_Array";
        case type::TAG_Short:
            return "TAG_Short";
        case type::TAG_String:
            return "TAG_String";
        default:
            return "TAG_Undef";
    }
}

void nbt::debug() {
    debug(m_tag, 0);
}

void nbt::debug(const tag* data, int indent) {
    std::string ind(indent, ' ');

    std::cout << ind << name_for_type(data->getType()) << "('" << data->getName() << "'): ";

    switch (data->getType()) {
        case type::TAG_String: {
            const tags::tag_string *s = static_cast<const tags::tag_string*>(data);
            std::cout << "'" << s->getValue() << "'" << std::endl;
            break;
        }
        case type::TAG_Compound: {
            const tags::tag_compound *c = static_cast<const tags::tag_compound*>(data);

            std::cout << c->getContent().size() << " entry" << std::endl;
            std::cout << ind << "{" << std::endl;
            for (const tag *i : c->getContent()) {
                debug(i, indent + 1);
            }
            std::cout << ind << "}" << std::endl;
            break;
        }
        default:
            break;
    }
}

void nbt::save(std::ostream& out) {

}
