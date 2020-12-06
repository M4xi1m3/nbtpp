#include "nbt.hpp"
#include "tag.hpp"
#include "stde/streams/data.hpp"
#include "stde/streams/gzip.hpp"
#include "nbtexception.hpp"

#include <iostream>
#include <assert.h>

using namespace nbtpp;
using namespace stde;

nbt::nbt(std::istream& in) : nbt() {
    load(in);
}

nbt::nbt(std::ifstream& in) : nbt() {
    load_file(in);
}

nbt::~nbt() {
    if (m_tag != nullptr) {
        delete m_tag;
        m_tag = nullptr;
    }
}

void nbt::load_file(std::ifstream& in) {
    int pos = in.tellg();
    try {
        streams::gzip_istream g(in);

        load((std::istream&) g);

        m_compression = g.type() == streams::gzip_streambuf::zlib ? zlib : gzip;

    } catch (streams::gzip_exception &e) {
        in.clear();
        in.seekg(pos);

        load((std::istream&) in);
    }
}

static tag* load_internal(streams::data_istream& di, tag_type force_type = tag_type::TAG_Undef) {
    tag_type type = force_type;
    std::string tag_name = "";

    if (type == tag_type::TAG_Undef) {
        type = (tag_type) di.readUnsignedByte();

        if (type == tag_type::TAG_End)
            return new tags::tag_end();
        tag_name = di.readUTF();
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
                if (t->type() == tag_type::TAG_End) {
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
        }
    }
    // Normally never reached.
    assert(false);
    return nullptr;
}

void nbt::load(std::istream& in) {
    if (m_tag != nullptr) {
        delete m_tag;
        m_tag = nullptr;
    }

    streams::data_istream di(in, streams::endianconv::big);
    di.exceptions(std::ios_base::badbit);

    m_tag = load_internal(di);
    m_compression = uncompressed;
}

std::string nbtpp::name_for_type(tag_type t) {
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

static void debug_internal(std::ostream& out, const tag* data, int indent, bool unnamed) {
    std::string ind(indent * 2, ' ');

    out << ind << name_for_type(data->type());
    if (unnamed)
        out << "(None): ";
    else
        out << "('" << data->name() << "'): ";

    switch (data->type()) {
        case tag_type::TAG_Byte: {
            const tags::tag_byte *s = static_cast<const tags::tag_byte*>(data);
            out << +s->value() << "\n";
            break;
        }
        case tag_type::TAG_Short: {
            const tags::tag_short *s = static_cast<const tags::tag_short*>(data);
            out << +s->value() << "\n";
            break;
        }
        case tag_type::TAG_Int: {
            const tags::tag_int *s = static_cast<const tags::tag_int*>(data);
            out << s->value() << "\n";
            break;
        }
        case tag_type::TAG_Long: {
            const tags::tag_long *s = static_cast<const tags::tag_long*>(data);
            out << s->value() << "\n";
            break;
        }
        case tag_type::TAG_Float: {
            const tags::tag_float *s = static_cast<const tags::tag_float*>(data);
            out << s->value() << "\n";
            break;
        }
        case tag_type::TAG_Double: {
            const tags::tag_double *s = static_cast<const tags::tag_double*>(data);
            out << s->value() << "\n";
            break;
        }
        case tag_type::TAG_Byte_Array: {
            const tags::tag_bytearray *s = static_cast<const tags::tag_bytearray*>(data);
            out << "[" << s->value().size() << " bytes]" << "\n";
            break;
        }
        case tag_type::TAG_String: {
            const tags::tag_string *s = static_cast<const tags::tag_string*>(data);
            out << "'" << s->value() << "'" << "\n";
            break;
        }
        case tag_type::TAG_List: {
            const tags::tag_list *l = static_cast<const tags::tag_list*>(data);

            out << l->value().size() << " entry" << "\n";
            out << ind << "{" << "\n";
            for (const tag *i : l->value()) {
                debug_internal(out, i, indent + 1, true);
            }
            out << ind << "}" << "\n";
            break;
        }
        case tag_type::TAG_Compound: {
            const tags::tag_compound *c = static_cast<const tags::tag_compound*>(data);

            out << c->value().size() << " entry" << "\n";
            out << ind << "{" << "\n";
            for (const tag *i : c->value()) {
                debug_internal(out, i, indent + 1, false);
            }
            out << ind << "}" << "\n";
            break;
        }
        case tag_type::TAG_Int_Array: {
            const tags::tag_intarray *s = static_cast<const tags::tag_intarray*>(data);
            out << "[" << s->value().size() << " ints]" << "\n";
            break;
        }
        case tag_type::TAG_Long_Array: {
            const tags::tag_longarray *s = static_cast<const tags::tag_longarray*>(data);
            out << "[" << s->value().size() << " longs]" << "\n";
            break;
        }
        default:
            break;
    }
}

void nbt::debug(std::ostream& out) {
    debug_internal(out, m_tag, 0, false);
}

void nbt::save_file(std::ofstream& out) {
    switch (m_compression) {
        case gzip: {
            streams::gzip_ostream g(out, streams::gzip_streambuf::gzip);
            save(g);
            break;
        }
        case zlib: {
            streams::gzip_ostream g(out, streams::gzip_streambuf::zlib);
            save(g);
            break;
        }
        default: {
            save(out);
            break;
        }
    }
}

static void save_internal(streams::data_ostream& out, const tag* the_tag, tag_type force_type = tag_type::TAG_Undef) {
    tag_type type = force_type;

    if (type == tag_type::TAG_Undef) {
        type = the_tag->type();
        out.writeUnsignedByte(type);
        out.writeUTF(the_tag->name());
    } else {
        if (type != the_tag->type()) {
            throw nbt_exception("invalid data, trying to put tag of type " + name_for_type(the_tag->type()) + " in list of " + name_for_type(type) + ".");
        }
    }


    switch (type) {
        case tag_type::TAG_Byte: {
            const tags::tag_byte *s = static_cast<const tags::tag_byte*>(the_tag);
            out.writeByte(s->value());
            break;
        }
        case tag_type::TAG_Short: {
            const tags::tag_short *s = static_cast<const tags::tag_short*>(the_tag);
            out.writeShort(s->value());
            break;
        }
        case tag_type::TAG_Int: {
            const tags::tag_int *s = static_cast<const tags::tag_int*>(the_tag);
            out.writeInt(s->value());
            break;
        }
        case tag_type::TAG_Long: {
            const tags::tag_long *s = static_cast<const tags::tag_long*>(the_tag);
            out.writeLong(s->value());
            break;
        }
        case tag_type::TAG_Float: {
            const tags::tag_float *s = static_cast<const tags::tag_float*>(the_tag);
            out.writeFloat(s->value());
            break;
        }
        case tag_type::TAG_Double: {
            const tags::tag_double *s = static_cast<const tags::tag_double*>(the_tag);
            out.writeDouble(s->value());
            break;
        }
        case tag_type::TAG_Byte_Array: {
            const tags::tag_bytearray *s = static_cast<const tags::tag_bytearray*>(the_tag);
            out.writeInt(s->value().size());
            for (const int8_t i : s->value()) {
                out.writeByte(i);
            }
            break;
        }
        case tag_type::TAG_String: {
            const tags::tag_string *s = static_cast<const tags::tag_string*>(the_tag);
            out.writeUTF(s->value());
            break;
        }
        case tag_type::TAG_List: {
            const tags::tag_list *l = static_cast<const tags::tag_list*>(the_tag);
            out.writeUnsignedByte(l->content_type());
            out.writeInt(l->value().size());
            for (const tag* t : l->value()) {
                save_internal(out, t, l->content_type());
            }

            break;
        }
        case tag_type::TAG_Compound: {
            const tags::tag_compound *c = static_cast<const tags::tag_compound*>(the_tag);
            for (const tag* t : c->value()) {
                save_internal(out, t);
            }
            out.writeUnsignedByte(tag_type::TAG_End);
            break;
        }
        case tag_type::TAG_Int_Array: {
            const tags::tag_intarray *s = static_cast<const tags::tag_intarray*>(the_tag);
            out.writeInt(s->value().size());
            for (const int32_t i : s->value()) {
                out.writeInt(i);
            }
            break;
        }
        case tag_type::TAG_Long_Array: {
            const tags::tag_longarray *s = static_cast<const tags::tag_longarray*>(the_tag);
            out.writeInt(s->value().size());
            for (const int64_t i : s->value()) {
                out.writeLong(i);
            }
            break;
        }
        default:
            break;
    }
}

void nbt::save(std::ostream& out) {
    if (m_tag == nullptr)
        return;

    streams::data_ostream dout(out, streams::endianconv::big);
    dout.exceptions(std::ios_base::badbit);

    save_internal(dout, m_tag);
}
