#ifndef TAG_HPP_
#define TAG_HPP_

#include <cstdint>
#include <string>
#include <iostream>

namespace nbtpp {
    class nbt;

    enum type : uint8_t {
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

    class tag {
        friend class nbt;
    public:
        tag() : m_name(), m_type(TAG_Undef) {
        }
        virtual ~tag() {
        }

        std::string getName() const {
            return m_name;
        }

        void setName(const std::string& name) {
            m_name = name;
        }

        type getType() const {
            return m_type;
        }
    protected:
        tag(const std::string& name, type type) : m_name(name), m_type(type) {
        }
    private:
        std::string m_name;
        type m_type;
    };

} /* namespace nbtpp */

#include "tags/tagend.hpp"
#include "tags/tagstring.hpp"
#include "tags/tagcompound.hpp"

#endif /* TAG_HPP_ */
