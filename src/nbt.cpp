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

    streams::data_istream di(in, streams::endianconv::big);
    di.exceptions(std::ios_base::badbit);

    m_tag = load_internal(di);
}

#include <iostream>

tag* nbt::load_internal(streams::data_istream& di, tag_type force_type) {
    tag_type type = force_type;
    std::string tag_name = "";

    if (type == tag_type::TAG_Undef) {
        type = (tag_type) di.readUnsignedByte();

        std::cout << type << std::endl;

        if (type == tag_type::TAG_End)
            return new tags::tag_end();
        tag_name = di.readUTF();
        std::cout << tag_name << std::endl;
    }

    switch (type) {
        case tag_type::TAG_Byte: {
            int8_t value = di.readByte();
            return new tags::tag_byte(tag_name, value);
        }
        case tag_type::TAG_Short: {
            int16_t value = di.readShort();
            return new tags::tag_short(tag_name, value);
        }
        case tag_type::TAG_Int: {
            int32_t value = di.readInt();
            return new tags::tag_int(tag_name, value);
        }
        case tag_type::TAG_Long: {
            int64_t value = di.readLong();
            return new tags::tag_long(tag_name, value);
        }
        case tag_type::TAG_Float: {
            float value = di.readFloat();
            return new tags::tag_float(tag_name, value);
        }
        case tag_type::TAG_Double: {
            double value = di.readDouble();
            return new tags::tag_double(tag_name, value);
        }
        case tag_type::TAG_Byte_Array: {
            tags::tag_bytearray *list = new tags::tag_bytearray(tag_name);
            int32_t list_length = di.readInt();
            for (int i = 0; i < list_length; i++) {
                int8_t val = di.readByte();
                list->append(val);
            }
            return list;
        }
        case tag_type::TAG_String: {
            std::string value = di.readUTF();
            return new tags::tag_string(tag_name, value);
        }
        case tag_type::TAG_List: {
            tag_type list_type = (tag_type) di.readUnsignedByte();
            int32_t list_length = di.readInt();
            tags::tag_list *list = new tags::tag_list(tag_name, list_type);

            for (int i = 0; i < list_length; i++) {
                list->append(load_internal(di, list_type));
            }
            return list;
        }
        case tag_type::TAG_Compound: {
            tag *t;
            tags::tag_compound *comp = new tags::tag_compound(tag_name);
            while (1) {
                t = load_internal(di);
                if (t->getType() == tag_type::TAG_End) {
                    delete t;
                    break;
                }
                comp->insert(t);
            }
            return comp;
        }
        case tag_type::TAG_Int_Array: {
            tags::tag_intarray *list = new tags::tag_intarray(tag_name);
            int32_t list_length = di.readInt();
            for (int i = 0; i < list_length; i++) {
                int32_t val = di.readInt();
                list->append(val);
            }
            return list;
        }
        case tag_type::TAG_Long_Array: {
            tags::tag_longarray *list = new tags::tag_longarray(tag_name);
            int64_t list_length = di.readInt();
            for (int i = 0; i < list_length; i++) {
                int64_t val = di.readLong();
                list->append(val);
            }
            return list;
        }
        default: {
            throw nbtpp::nbt_exception("invalid tag type " + std::to_string((int) type));
            type = tag_type::TAG_Undef;
        }
    }

    return new tag(tag_name, type);
}

std::string name_for_type(tag_type t) {
    switch (t) {
        case tag_type::TAG_Byte:
            return "TAG_Byte";
        case tag_type::TAG_Byte_Array:
            return "TAG_Byte_Array";
        case tag_type::TAG_Compound:
            return "TAG_Compound";
        case tag_type::TAG_Double:
            return "TAG_Double";
        case tag_type::TAG_End:
            return "TAG_End";
        case tag_type::TAG_Float:
            return "TAG_Float";
        case tag_type::TAG_Int:
            return "TAG_Int";
        case tag_type::TAG_Int_Array:
            return "TAG_Int_Array";
        case tag_type::TAG_List:
            return "TAG_List";
        case tag_type::TAG_Long:
            return "TAG_Long";
        case tag_type::TAG_Long_Array:
            return "TAG_Long_Array";
        case tag_type::TAG_Short:
            return "TAG_Short";
        case tag_type::TAG_String:
            return "TAG_String";
        default:
            return "TAG_Undef";
    }
}

void nbt::debug() {
    debug(m_tag, 0);
}

void nbt::debug(const tag* data, int indent) {
    std::string ind(indent * 2, ' ');

    std::cout << ind << name_for_type(data->getType()) << "('" << data->getName() << "'): ";

    switch (data->getType()) {
        case tag_type::TAG_Byte: {
            const tags::tag_byte *s = static_cast<const tags::tag_byte*>(data);
            std::cout << +s->value() << std::endl;
            break;
        }
        case tag_type::TAG_Short: {
            const tags::tag_short *s = static_cast<const tags::tag_short*>(data);
            std::cout << +s->value() << std::endl;
            break;
        }
        case tag_type::TAG_Int: {
            const tags::tag_int *s = static_cast<const tags::tag_int*>(data);
            std::cout << s->value() << std::endl;
            break;
        }
        case tag_type::TAG_Long: {
            const tags::tag_long *s = static_cast<const tags::tag_long*>(data);
            std::cout << s->value() << std::endl;
            break;
        }
        case tag_type::TAG_Float: {
            const tags::tag_float *s = static_cast<const tags::tag_float*>(data);
            std::cout << s->value() << std::endl;
            break;
        }
        case tag_type::TAG_Double: {
            const tags::tag_double *s = static_cast<const tags::tag_double*>(data);
            std::cout << s->value() << std::endl;
            break;
        }
        case tag_type::TAG_Byte_Array: {
            const tags::tag_bytearray *s = static_cast<const tags::tag_bytearray*>(data);
            std::cout << "[" << s->value().size() << " bytes]" << std::endl;
            break;
        }
        case tag_type::TAG_String: {
            const tags::tag_string *s = static_cast<const tags::tag_string*>(data);
            std::cout << "'" << s->value() << "'" << std::endl;
            break;
        }
        case tag_type::TAG_List: {
            const tags::tag_list *l = static_cast<const tags::tag_list*>(data);

            std::cout << l->value().size() << " entry" << std::endl;
            std::cout << ind << "{" << std::endl;
            for (const tag *i : l->value()) {
                debug(i, indent + 1);
            }
            std::cout << ind << "}" << std::endl;
            break;
        }
        case tag_type::TAG_Compound: {
            const tags::tag_compound *c = static_cast<const tags::tag_compound*>(data);

            std::cout << c->value().size() << " entry" << std::endl;
            std::cout << ind << "{" << std::endl;
            for (const tag *i : c->value()) {
                debug(i, indent + 1);
            }
            std::cout << ind << "}" << std::endl;
            break;
        }
        case tag_type::TAG_Int_Array: {
            const tags::tag_intarray *s = static_cast<const tags::tag_intarray*>(data);
            std::cout << "[" << s->value().size() << " ints]" << std::endl;
            break;
        }
        default:
            break;
    }
}

void nbt::save(std::ostream& out) {

}
