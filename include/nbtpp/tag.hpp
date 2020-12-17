#ifndef TAG_HPP_
#define TAG_HPP_

#include <cstdint>
#include <string>
#include <iostream>

namespace nbtpp {
    class nbt;

    enum tag_type : uint8_t {
        TAG_End = 0,
        TAG_Byte = 1,
        TAG_Short = 2,
        TAG_Int = 3,
        TAG_Long = 4,
        TAG_Float = 5,
        TAG_Double = 6,
        TAG_Byte_Array = 7,
        TAG_String = 8,
        TAG_List = 9,
        TAG_Compound = 10,
        TAG_Int_Array = 11,
        TAG_Long_Array = 12,
        TAG_Undef = 0xff
    };

    /**
     * NBT tag base.
     *
     * This class has no public constructor, use tag_* classes instead.
     */
    class tag {
        friend class nbt;
    public:
        virtual ~tag() {
        }

        std::string name() const {
            return m_name;
        }

        void name(const std::string& name) {
            m_name = name;
        }

        tag_type type() const {
            return m_type;
        }
    protected:
        tag(const std::string& name, tag_type type) : m_name(name), m_type(type) {
        }
    private:
        std::string m_name;
        tag_type m_type;
    };

}

#include "tags/tagend.hpp"
#include "tags/tagbyte.hpp"
#include "tags/tagshort.hpp"
#include "tags/tagint.hpp"
#include "tags/taglong.hpp"
#include "tags/tagfloat.hpp"
#include "tags/tagdouble.hpp"
#include "tags/tagbytearray.hpp"
#include "tags/tagstring.hpp"
#include "tags/taglist.hpp"
#include "tags/tagcompound.hpp"
#include "tags/tagintarray.hpp"
#include "tags/taglongarray.hpp"

#endif
